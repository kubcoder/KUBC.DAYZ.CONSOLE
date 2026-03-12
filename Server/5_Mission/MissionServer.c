modded class MissionServer
{
    /// @brief Экземпляр обрабатывающий глобальный чат
    private ref KCGlChat globalChat;

    /// @brief Движок команд игроков
    private ref KCCmd usersCmd;

    /// @brief Менеджер сохраненных точек
    private ref KCPointManager pointManager;
    
    /// @brief  Инициализируем настройки мода.
    ///         В частности создаем структуру папочек, и файлы настроек 
    ///         по умолчанию.
    override void OnInit()
    {
        ChekPlatform();
        globalChat = new KCGlChat();
        usersCmd = new KCCmd();
        usersCmd.RegisterCommand(KCUserCmdGod.CMD_NAME, new KCUserCmdGod());
        usersCmd.RegisterCommand(KCUserCmdHeal.CMD_NAME, new KCUserCmdHeal());
        usersCmd.RegisterCommand(KCUserCmdTime.CMD_NAME, new KCUserCmdTime());
        usersCmd.RegisterCommand(KCUserCmdWeather.CMD_NAME, new KCUserCmdWeather());
        pointManager = new KCPointManager();
        usersCmd.RegisterCommand(KCUserCmdSP.CMD_NAME, new KCUserCmdSP(pointManager));
        usersCmd.RegisterCommand(KCUserCmdJump.CMD_NAME, new KCUserCmdJump());
        super.OnInit();   
    }

    /// @brief Проверяем под какой платформой запустились
    ///        Данный метод нужен что бы понять почему мод не работает
    ///        где то... гребаання кросплатформенность.
    private void ChekPlatform()
    {
        #ifdef PLATFORM_WINDOWS
        KCLog.Write("KUBC","Сервер собран для Windows");
        return;
        #endif
        #ifdef PLATFORM_LINUX
        KCLog.Write("KUBC","Сервер собран для Linux");
        return;
        #endif
        KCLog.Write("KUBC","Не смогли определить платформу, работа мода не гарантируется", KCLogLevel.Error);
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
                DoChat(chat);                
            }
        }
        super.OnEvent(eventTypeId,params);
    }

    private void DoChat(ChatMessageEventParams chat)
    {
        if (usersCmd)
        {
            if (usersCmd.Execute(chat))
            {
                return;
            }
        }
        if (globalChat)
        {
            globalChat.Execute(chat);
        }        
    }
}