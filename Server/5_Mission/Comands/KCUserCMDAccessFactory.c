/// @brief Фабрика конфигурации команд пользователя
class KCUserCMDAccessFactory
{
    private ref KCUserCMDAccessDirectory accessDirectory;

    void KCUserCMDAccessFactory()
    {
        accessDirectory = new KCUserCMDAccessDirectory();
        accessDirectory.CreatePaths();
    }

    /// @brief Получить настройки команды
    /// @param cmdName - имя текстовой команды
    /// @return настройки текстовой команды, если их почему то нет на диске
    ///         будет возвращен экземпляр с настройками по умолчанию.
    KCUserCMDAccess GetAccess(string cmdName)
    {
        KCUserCMDAccess access;
        JsonFileLoader<KCUserCMDAccess>.JsonLoadFile( accessDirectory.GetConfigFileName(cmdName), access);
        if (access)
            return access;
        return new KCUserCMDAccess();
    }

    /// @brief Проверить наличие файла конфигурации команды
    ///        если файлика нет, то он будет создан
    /// @param cmdName имя команды
    void ChekCmdConfig(string cmdName)
    {
        string configFileName = accessDirectory.GetConfigFileName(cmdName);
        if (!FileExist(configFileName))
        {
            KCCmd.Log("Создаем файл настройки доступа по умолчанию для команды [" + cmdName + "]");            
            KCUserCMDAccess acces = new KCUserCMDAccess();
            JsonFileLoader<KCUserCMDAccess>.JsonSaveFile( configFileName, acces);
        }
        else
        {
            KCCmd.Log("Файл настройки команды [" + cmdName + "] существует на диске"); 
        }
    }
}