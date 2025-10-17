#ifndef KUBC_CHAT
/** @brief Базовый класс модуля глобального чата, содержит все необходимые константы и инструментарий запись в лог */
class KCGlChat
{
    /** @brief название модуля отображаемое в логах*/
    static const string MOD_NAME = "KUBC.CHAT";

    /** @brief выполнить запись в лог скриптов от имени модуля чата
    *   @param Message - текст сообщения
    *   @param Level - уровень сообщения
    */
    static void Log(string Message, KCLogLevel Level = KCLogLevel.Info)
    {
        KCLog.Write(MOD_NAME, Message, Level);
    }
    /** @brief Выполняем обработку чата
    *   @param chat данные текстового сообщения
    */
    static void Execute(ChatMessageEventParams chat)
    {
        KCGlChatSettings sett = KCGlChatSettings.Get();
        if (sett.Enable)
        {
            string message = chat.param3;
            if (!sett.ExecuteMessage(message))
            {
                PlayerBase From = KCPlayer.Find(chat.param2);
                if (From)
                {
                    string toPlayers = string.Format(sett.MessageFormat, chat.param2, message);
                    switch(sett.Access)
                    {
                        case KCAccessType.All:
                            SendToAll(From, toPlayers);
                            break;
                        case KCAccessType.WhiteList:
                            if (sett.InList(From))
                            {
                                SendToAll(From, toPlayers);
                            }
                            break;
                        case KCAccessType.BlackList:
                            if (!sett.InList(From))
                            {
                                SendToAll(From, toPlayers);
                            }
                            break;
                    }
                }
                else
                {
                    KCGlChat.Log("Не нашли отправителя, сообщение пришло от [" + chat.param2 + "], текст сообщения ["+message+"]", KCLogLevel.Error);
                }
            }
        }
    }
    /** @brief Кидаем мессагу всем игрокам сервера
    *   @param player от кого мессага, если тут будет NULL сообщение отправлено не будет
    *   @param Message текст сообщения
    */
    static void SendToAll(PlayerBase player, string Message)
    {
        if ((player)&&(player.GetIdentity()))
        {
            string From = player.GetIdentity().GetName(); 
            array<Man> players = new array<Man>; 
            GetGame().GetPlayers(players);
            Param1<string> pt = new Param1<string>(Message);
            foreach(Man m:players)
            {
                PlayerBase reciver = PlayerBase.Cast(m);
                if((reciver)&&(reciver.GetIdentity()))
                {
                    if (reciver != player)
                    {
                        GetGame().RPCSingleParam(reciver, ERPCs.RPC_USER_ACTION_MESSAGE, pt, true, reciver.GetIdentity());
                    }
                }
            }
        }
    }

}
#define KUBC_CHAT
#endif