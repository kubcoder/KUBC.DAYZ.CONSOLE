modded class MissionServer
{
    /** @brief  Инициализируем настройки мода.
    *           В частности создаем структуру папочек, и файлы настроек 
                по умолчанию.
    */
    override void OnInit()
    {
        KCGlChatSettings.CreatePaths();
        KCCmd.CreatePaths();
        RegisterCommand(KCUserCmdGod.CMD_NAME, new KCUserCmdGod());
        RegisterCommand(KCUserCmdHeal.CMD_NAME, new KCUserCmdHeal());
        RegisterCommand(KCUserCmdTime.CMD_NAME, new KCUserCmdTime());
        RegisterCommand(KCUserCmdWeather.CMD_NAME, new KCUserCmdWeather());
        RegisterCommand(KCUserCmdSP.CMD_NAME, new KCUserCmdSP());
        RegisterCommand(KCUserCmdJump.CMD_NAME, new KCUserCmdJump());
        super.OnInit();      
    }
    /** @brief  ловим события на стороне сервера. Среди потока всех возможных
    *           выделяем события когда игрок отправляет текстовое сообщение в чат
    */
    override void OnEvent(EventType eventTypeId, Param params)  
    {
        if (eventTypeId==ChatChannelEventTypeID)
        {
            KCGlChat.Log("Поймали событие Канала");
        }
        if (eventTypeId==ChatMessageEventTypeID)
        {
            KCGlChat.Log("Поймали событие чата");
            ChatMessageEventParams chat = ChatMessageEventParams.Cast(params);
            if (chat)
            {
                
                if (chat.param3.Get(0)==KCTextCmd.CMD_PREFIX)
                {
                    PlayerBase From = KCPlayer.Find(chat.param2);
                    if (From)
                    {
                        int len = chat.param3.Length() - 1;
                        string cmdText = chat.param3.Substring(1, len);
                        KCTextCmd cmdData = KCTextCmd.FromChat(cmdText);
                        if (cmdData)
                        {
                            KCUserCMD currentCommand = CommandDictonary.Get(cmdData.Name);
                            if (currentCommand)
                            {
                                currentCommand.Execute(From, cmdData);
                            }
                        }
                    }
                }
                else
                {
                    KCGlChat.Execute(chat);
                }                
            }
        }
        super.OnEvent(eventTypeId,params);
    }
    /** @brief справочник команд сервера*/
    ref map<string, ref KCUserCMD> CommandDictonary = new map<string, ref KCUserCMD>();

    /** @brief Зарегистрировать команду
    *   @param Name Имя команды
    *   @param command класс команды
    */
    void RegisterCommand(string Name, KCUserCMD command)
    {
        KCCmd.Log("Добавлена команда [" + Name + "]");
        CommandDictonary.Insert(Name, command);
        string sFileName = KCUserCMDAccess.GetFileName(Name);
        if (!FileExist(sFileName))
        {
            KCCmd.Log("Создаем файл настройки доступа по умолчанию для команды [" + Name + "]");            
            KCUserCMDAccess acces = new KCUserCMDAccess();
            JsonFileLoader<KCUserCMDAccess>.JsonSaveFile( sFileName, acces);
        }
        else
        {
            KCCmd.Log("Файл настройки команды [" + Name + "] существует на диске"); 
        }
    }


}