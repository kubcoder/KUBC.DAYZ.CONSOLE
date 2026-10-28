/// @brief Инструмент загрузки настроек мода
class KCGlChatColorSettingsFactory
{

    ref KCGlChatColorSettings Config;

    /// @brief Инициализация фабрики настроек
    void KCGlChatColorSettingsFactory()
    {
        KCGlChatDirectory directory = new KCGlChatDirectory();
        Config = new KCGlChatColorSettings();
        string configFile = directory.GetConfigFileName();
        if(!FileExist(configFile))
        {
            KCLog.Write("KCPlayer","Файл настроек глобального чата не существует", KCLogLevel.Warning);            
        }
        else
        {
            JsonFileLoader<KCGlChatColorSettings>.JsonLoadFile(configFile, Config);
        }
        KCLog.Write("KCPlayer","Уведомления игрокам, включая глобальный чат будут отображатся цветом:" + Config.ChatColor);     
    }


    
}