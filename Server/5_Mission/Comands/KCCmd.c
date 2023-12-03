#ifndef KUBC_CMD
/** Базовый класс модуля команд, содержит все необходимые константы и инструментарий запись в лог */
class KCCmd
{
    /** @brief имя модуля в логах*/
    static const string MOD_NAME = "KUBC.CMD";
    
    /** @brief выполнить запись в лог скриптов от имени модуля команд
    *   @param Message - текст сообщения
    *   @param Level - уровень сообщения
    */
    static void Log(string Message, KCLogLevel Level = KCLogLevel.Info)
    {
        KCLog.Write(MOD_NAME, Message, Level);
    }

    /** @brief Корневая папка разработчика*/
    static const string ROOT_PATH = "KUBC";

    /** @brief Корневая папка мода*/
    static const string MOD_PATH = "CMD";

    /** @brief Создаем папку мода и файл настроек если он не существует */
    static void CreatePaths()
    {
        MakeDirectory("$profile:"+ROOT_PATH);
        MakeDirectory(GetSettingsPath());
    }
    /** @brief получить полный путь к папке настроек команд
    *   @return строка пути папки с настройками команд
    */
    static string GetSettingsPath()
    {
        return "$profile:"+ROOT_PATH + "\\" + MOD_PATH;
    }
}
#define KUBC_CMD
#endif