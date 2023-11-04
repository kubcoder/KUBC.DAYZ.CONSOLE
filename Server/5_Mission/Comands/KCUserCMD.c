#ifndef KUBC_USER_CMD
/** @brief шаблонный класс команды консоли*/
class KCUserCMD
{
	/** @brief Выполнить команду
	*	@param user какой игрок выполнил команду
	*	@param data данные текстовой команды
	*	@return истина если команда успешно выполнена. 
	*/
	bool Execute(PlayerBase user, KCTextCmd data)
	{
		KCUserCMDAccess access = KCUserCMDAccess.GetAccess(data.Name);
		if (access.Garanted(user))
		{
			Log("Выполнил команду", user);
			return OnExecute(user, data);
		}
		else
		{
			Log("Пытался выполнить команду. Доступ запрещен", user, KCLogLogLevel.Error);
		}
		return false;
	}
	/** @brief 	Получить имя команды.
	*			Данный метод должен быть перегружен в классе кокретной команды
	*	@return имя команды, которое будет использоваться в логах.
	*/
	string GetName()
	{
		return "";
	}
	/** @brief Выполнить запись сообщения в лог выполнения скриптов от имени команды
	*	@param Message - текст сообщение
	*	@param player - игрок который выполнил команду
	*	@param Level - уровень сообщения
	*/
	void Log(string Message, PlayerBase player = NULL, KCLogLogLevel Level = KCLogLogLevel.Info)
	{
		string msg = "[" + GetName() + "]";
		if (player!=NULL)
		{
			msg += "[" + player.GetIdentity().GetName() + "(" + player.GetIdentity().GetPlainId() + ")]";
		}
		KCCmd.Log(msg + "." + Message, Level);
	}
	/** @brief 	Метод вызывается когда необходимо выполнить команду на стороне сервера
	*			Проверка доступа игрока уже выполнена, и у игрока точно есть доступ к команде.
	*			В лог скриптов уже выполнили запись что такой то игрок выполнил команду.
	*			Метод должен быть перегружен в классе конкретной команды
	*	@param user игрок вызвавший команду
	*	@param data данные команды
	*	@return в коде выполнения необходимо вернуть истину если команда выполнена успешно,
	*			или ложь если при выполнении команды возникли проблемки.
	*/
	bool OnExecute(PlayerBase user, KCTextCmd data)
	{
		return false;
	}
}
#define KUBC_USER_CMD
#endif
