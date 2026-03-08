/// @brief Базовый класс модуля команд, содержит все необходимые константы и инструментарий запись в лог 
class KCCmd
{
    /// @brief имя модуля в логах
    static const string MOD_NAME = "KUBC.CMD";
    
    /// @brief выполнить запись в лог скриптов от имени модуля команд
    /// @param Message - текст сообщения
    /// @param Level - уровень сообщения
    static void Log(string Message, KCLogLevel Level = KCLogLevel.Info)
    {
        KCLog.Write(MOD_NAME, Message, Level);
    }

    /// @brief Фабрика команд
    private ref KCTextCmdFactory cmdFactory;

    /// @brief Фабрика доступа к командам
    private ref KCUserCMDAccessFactory accessFactory;

    /// @brief справочник команд сервера
    private ref map<string, ref KCUserCMD> commandDictonary;

    void KCCmd()
    {
        cmdFactory = new KCTextCmdFactory();
        accessFactory = new KCUserCMDAccessFactory();
        commandDictonary = new map<string, ref KCUserCMD>();
    }

    /// @brief Зарегистрировать команду
    /// @param Name Имя команды
    /// @param command класс команды
    void RegisterCommand(string name, KCUserCMD command)
    {
        Log("Добавлена команда [" + name + "]");
        commandDictonary.Insert(name, command);
        accessFactory.ChekCmdConfig(name);
    }

    /// @brief Попытаться выполнить текстовую команду
    /// @param chat параметры сообщения чата
    /// @return истина, если была команда
    bool Execute(ChatMessageEventParams chat)
    {
        KCTextCmd cmd = cmdFactory.Get(chat);
        if (cmd)
        {
            KCUserCMD currentCommand = commandDictonary.Get(cmd.Name);
            if (currentCommand)
            {
                KCUserCMDAccess access = accessFactory.GetAccess(cmd.Name);
                if (access.Garanted(cmd.Owner))
                {
                    Log("Пользователь [" + cmd.Owner.GetIdentity().GetName() + "(" + cmd.Owner.GetIdentity().GetPlainId() + ")] выполняет команду [" + cmd.Name + "]");
                    currentCommand.Execute(cmd);
                    return true;
                }
                else
                {
                    Log("Пользователь [" + cmd.Owner.GetIdentity().GetName() + "(" + cmd.Owner.GetIdentity().GetPlainId() + ")] не имеет доступа к команде [" + cmd.Name + "]", KCLogLevel.Warning);
                }
                
            }
        }
        return false;
    }
}