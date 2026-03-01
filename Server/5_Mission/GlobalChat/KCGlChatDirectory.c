/// @brief Инструменты работы с папкой мода
class KCGlChatDirectory:KCDirectory
{
    /// @brief Корневая папка класса мода
    static const string MOD_PATH = "CHAT";

    /// @brief Имя файла настроек
    static const string FILE_NAME = "GlobalChat.json";

    void KCGlChatDirectory()
    {
        pathNames.Insert(MOD_PATH);
    }

    /// @brief Получить полное имя файла конфигурации
    /// @return 
    string GetConfigFileName()
    {
        return GetName(FILE_NAME);
    }
}