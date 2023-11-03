modded class MissionServer
{
    /** @brief  Инициализируем настройки мода.
    *           В частности создаем структуру папочек, и файлы настроек 
                по умолчанию.
    */
    override void OnInit()
    {
        KCGlChatSettings.CreatePaths(); 
        super.OnInit();      
    }
    /** @brief  ловим события на стороне сервера. Среди потока всех возможных
    *           выделяем события когда игрок отправляет текстовое сообщение в чат
    */
    override void OnEvent(EventType eventTypeId, Param params)  
    {
        if (eventTypeId==ChatMessageEventTypeID)
        {
            ChatMessageEventParams chat = ChatMessageEventParams.Cast(params);
            if (chat)
            {
                //TODO: Тут сделать проверку на префикс команды
                //      и только если не команда вызывать глобальный чат
                KCGlChat.Execute(chat);
            }
        }
        super.OnEvent(eventTypeId,params);
    }
}