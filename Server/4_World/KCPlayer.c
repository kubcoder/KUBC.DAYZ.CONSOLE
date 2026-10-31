#ifndef KUBC_PLAYER
/** @brief Инструменты работы с игроками */
class KCPlayer
{
	static ref KCGlChatColorSettingsFactory options = new KCGlChatColorSettingsFactory();

    /** @brief Выполняем поиск игрока
	*	@param name имя или PlainID игрока
	*/
    static PlayerBase Find(string name) 
	{
		PlayerBase p;
		name.ToLower();
		name.ToLower();
		int i =0;
		//Получаем список всех игроков на сервере
		array<Man> players = new array<Man>; 
		GetGame().GetPlayers(players);
		//Поочередно перебираем каждого игрока
		for (i = 0; i < players.Count(); i++ ) 
		{
			//Берем конкретного игрока сервера
			p = PlayerBase.Cast(players.Get(i));
			if((p)&&(p.GetIdentity()))
			{
				string pn = p.GetIdentity().GetName();
				pn.ToLower();
				if(pn == name)
				{
					if (NameIsDuplicated(p.GetIdentity().GetName()))
					{
						KCLog.Write("KCPlayer","Дублирование имени игрока ["+name+"]", KCLogLevel.Warning);
						return NULL;//Имя задублировано, возвращаем NULL
					}
					return p;//Если совпало то возращаем экземпляр игрока 
				}
				if(p.GetIdentity().GetPlainId()==name) 
					return p;//Если совпало то возращаем экземпляр игрока 
			}
		}
		//Если пришли сюда то игрока с указанным именем или PlainID сейчас нет на сервере, возвращаем пустоту
		return NULL;
	}

	/** @brief Проверить на дублирование никнейма
	*	@param name никнейм игрока
	*	@return истина если никнейм игрока дублируется
	*/
	static bool  NameIsDuplicated(string name)
	{
		//Получаем список всех игроков на сервере
		array<Man> players = new array<Man>; 
		GetGame().GetPlayers(players);
		int count = 0;
		PlayerBase p;
		name.ToLower();
		for (int i = 0; i < players.Count(); i++ )
		{
			p = PlayerBase.Cast(players.Get(i));
			if((p)&&(p.GetIdentity()))
			{
				string pn = p.GetIdentity().GetName();
				pn.ToLower();
				if(pn == name)
				{
					count++;
				}
			}
		}
		return count > 1;
	}

    /** @brief: Отправляем мессагу игроку
    *	@param player - кому мессага
    *	@param From - от кого, можно не указывать
    *	@param Message - текст сообщения
    */
    static void SendMessage(PlayerBase player, string From, string Message)
    {
        string msg = Message;
        if (From!="")
        {
            msg = From + ":" + Message;
        }
        player.Message(msg, options.Config.ChatColor);
    }
}
#define KUBC_PLAYER
#endif