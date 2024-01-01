/** @brief настройки глобального чата*/
class KCGlChatSettings
{
    /** @brief Включение глобального чата*/
    bool Enable = true;
    /** @brief Тип доступа к чату*/
    KCAccessType Access = KCAccessType.All;
    
    /** @brief Список игроков. Белый или черный список в зависимости от Access*/
    ref TStringArray Players = new TStringArray();

    /** @brief Список символов в начале строки которые отключают отправку в глобальный чат*/
    ref TStringArray ExecuteSymbols = new TStringArray();

    /** @brief Проверить на исключение строки из чата
    *   @param Message текст сообщения полученный из чата
    */
    bool ExecuteMessage(string Message)
    {
        if (ExecuteSymbols)
        {
            foreach(string eString:ExecuteSymbols)
            {
                if (eString[0]==Message[0])
                {
                    return true;
                }
            }
        }
        return false;
    }
    /** @brief Проверяем находится ли игрок в списке игроков
    *   @param Message текст сообщения полученный из чата */
    bool InList(PlayerBase player)
    {
        foreach(string sid:Players)
        {
            if(player.GetIdentity().GetPlainId()==sid)
            {
                return true;
            }
        }
        return false;
    }
    /** @brief Имя файла настроек*/
    static const string FILE_NAME = "GlobalChat.json";
    /** @brief Корневая папка разработчика */
    static const string ROOT_PATH = "KUBC";
    /** @brief Корневая папка класса мода */
    static const string MOD_PATH = "CHAT";
    
    /** @brief Полный путь к папке мода */
    static string GetSettingsPath()
    {
        return "$profile:"+ROOT_PATH + "\\" + MOD_PATH;
    }

    /** @brief Получить полный путь к файлу настроек*/
    static string GetFileName()
    {
        return GetSettingsPath() + "\\" + FILE_NAME;
    }

    

    
    /** @brief Создаем папку мода и файл настроек если он не существует*/
    static void CreatePaths()
    {
        MakeDirectory("$profile:"+ROOT_PATH);
        MakeDirectory(GetSettingsPath());
        string sFile = KCGlChatSettings.GetFileName();
        if(!FileExist(sFile))
        {
            KCGlChat.Log("Файл настроек глобального чата не существует, создаем файл по умолчанию");
            KCGlChatSettings dFile = new KCGlChatSettings();
            JsonFileLoader<KCGlChatSettings>.JsonSaveFile( sFile, dFile);
        }
    }
    

    /** Получить текущие настройки глобального чата */
    static KCGlChatSettings Get()
    {
        KCGlChatSettings current;
        JsonFileLoader<KCGlChatSettings>.JsonLoadFile(KCGlChatSettings.GetFileName(), current);
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