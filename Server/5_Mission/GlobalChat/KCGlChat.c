#ifndef KUBC_CHAT
/** @brief Базовый класс модуля глобального чата, содержит все необходимые константы и инструментарий запись в лог */
class KCGlChat
{
    /** @brief название модуля отображаемое в логах*/
    static const string MOD_NAME = "KUBC.CHAT";

    static void Log(string Message, KCLogLogLevel Level = KCLogLogLevel.Info)
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
                    switch(sett.Access)
                    {
                        case KCAccessType.All:
                            SendToAll(From, message);
                            break;
                        case KCAccessType.WhiteList:
                            if (sett.InList(From))
                            {
                                SendToAll(From, message);
                            }
                            break;
                        case KCAccessType.BlackList:
                            if (!sett.InList(From))
                            {
                                SendToAll(From, message);
                            }
                            break;
                    }
                }
                else
                {
                    KCGlChat.Log("Не нашли отправителя, сообщение пришло от [" + chat.param2 + "], текст сообщения ["+message+"]", KCLogLogLevel.Error);
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
        if (player)
        {
            string From = player.GetIdentity().GetName();
            array<Man> players = new array<Man>; 
            GetGame().GetPlayers(players);
            foreach(Man m:players)
            {
                PlayerBase reciver = PlayerBase.Cast(m);
                if(reciver)
                {
                    if (reciver != player)
                    {
                        KCPlayer.SendMessage(reciver, From, Message);
                    }
                }
            }
        }
    }

}
#define KUBC_CHAT
#endif