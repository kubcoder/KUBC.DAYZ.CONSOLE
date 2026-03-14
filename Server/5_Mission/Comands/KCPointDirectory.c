class KCPointDirectory:KCDirectory
{
    
    /// @brief глобальный файл точек которые доступны всем пользователям
    const string GLOBAL_FILE_NAME = "SharedPoints.json";

    /// @brief Корневая папка класса мода
    const string MOD_PATH = "Points";

    void KCPointDirectory()
    {
        pathNames.Insert(MOD_PATH);
    }

    string GetFileName()
    {
        return GetName(GLOBAL_FILE_NAME);
    }

    string GetFileName(PlayerBase user)
    {
        return GetName(user.GetIdentity().GetPlainId() + ".json");
    }

}