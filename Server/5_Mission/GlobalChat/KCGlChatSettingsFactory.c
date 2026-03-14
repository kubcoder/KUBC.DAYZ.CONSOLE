/// @brief Инструмент загрузки настроек мода
class KCGlChatSettingsFactory
{
    /// @brief Рабочая директория мода
    ref KCGlChatDirectory directory;

    /// @brief Полное имя файла конфигурации
    string configFile;
    /// @brief Инициализация фабрики настроек
    void KCGlChatSettingsFactory()
    {
        directory = new KCGlChatDirectory();
        InitConfig();
    }

    /// @brief Инициализируем конфигурацию
    private void InitConfig()
    {
        directory.CreatePaths();
        configFile = directory.GetConfigFileName();
        if(!FileExist(configFile))
        {
            KCGlChat.Log("Файл настроек глобального чата не существует, создаем файл по умолчанию");
            KCGlChatSettings dFile = new KCGlChatSettings();
            JsonFileLoader<KCGlChatSettings>.JsonSaveFile(configFile, dFile);
        }
    }

    /// @brief Загрузить настройки из файла конфигурации
    /// @return Конфигурация глобального чата
    KCGlChatSettings Get()
    {
        KCGlChatSettings current;
        JsonFileLoader<KCGlChatSettings>.JsonLoadFile(configFile, current);
        if (current)
        {
            return current;
        }
        else
        {
            KCGlChat.Log("Не смогли загрузить файл настроек глобального чата", KCLogLevel.Error);
            return new KCGlChatSettings();
        }
    }

}