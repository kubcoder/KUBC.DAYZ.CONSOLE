#ifndef KUBC_PLAYER
/** @brief Инструменты работы с игроками */
class KCPlayer
{
    /** @brief Выполняем поиск игрока
	*	@param name имя или PlainID игрока
	*/
    static PlayerBase Find(string name) 
	{
		PlayerBase p;
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
			if(p)
			{
				string pn = p.GetIdentity().GetName();
				pn.ToLower();
				if(pn == name) 
					return p;//Если совпало то возращаем экземпляр игрока 
				if(p.GetIdentity().GetPlainId()==name) 
					return p;//Если совпало то возращаем экземпляр игрока 
			}
		}
		//Если пришли сюда то игрока с указанным именем или PlainID сейчас нет на сервере, возвращаем пустоту
		return NULL;
	}

    /** @brief: Отправляем мессагу игроку
    *	@param player - кому мессага
    *	@param From - от кого, можно не указывать
    *	@param Message - текст сообщения
    */
    static void SendMessage(PlayerBase player, string From, string Message)
    {
        Param1<string> pt;
        if (From!="")
        {
            pt = new Param1<string>(From + ":" + Message);
        }
        else
        {
            pt = new Param1<string>(Message);
        }
        
		GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, pt, true, player.GetIdentity());
    }
}
#define KUBC_PLAYER
#endif