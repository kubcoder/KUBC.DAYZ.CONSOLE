/// @brief Директория работы с командами
class KCUserCMDAccessDirectory:KCDirectory
{
    /// @brief Корневая папка класса мода
    static const string MOD_PATH = "CMD";

    void KCUserCMDAccessDirectory()
    {
        pathNames.Insert(MOD_PATH);
    }

    /// @brief Получить имя файла настроек команды 
    /// @param cmdName - имя текстовой команды
    /// @return полный путь к файлу настроек команды
    string GetConfigFileName(string cmdName)
    {
        return GetName(cmdName + ".json");
    }

}