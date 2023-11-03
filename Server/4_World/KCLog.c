#ifndef KUBC_LOG
/** @brief перечисление уровня мессаги в логе*/
enum KCLogLogLevel
{
    Info,
    Warning,
    Error
}
/** @brief Вспомогательный класс для записи сообщений в логи
*   Нужен для того что бы в логах (скриптов или администратора) 
*   были красивые сообщения в формате:
*   [Уровень][Источник] сообщение.
    
*   Например так:
*   SCRIPT       : [Info][KUBC.ITEMS]Файл настроек сохранения наборов итемов сущесвтует
*   SCRIPT       : [Info][KUBC.ITEMS]Начинаем создание справочника итемов
*   SCRIPT       : [Info][KUBC.ITEMS]Категории загружены, начинаем подготовку файла итемов
*/
class KCLog
{
    /** @brief Записать сообщение в лог выполнения скриптов (*.log)
    *   @param Source - какой класс или мод сформировал сообщение
    *   @param Message - текст сообщения который нужно записать в лог
    *   @param Level - уровень сообщения (информация, предупреждение или ошибка)
    */
    static void Write(string Source, string Message, KCLogLogLevel Level = KCLogLogLevel.Info)
    {
        string msg = GetText(Level);
        if (Source!="")
        {
            msg += "[" + Source + "]";
        }
        Print(msg + Message);
    }
    /** @brief Записать сообщение в лог администратора (*.AMD)
    *   @param Source - какой класс или мод сформировал сообщение
    *   @param Message - текст сообщения который нужно записать в лог
    *   @param Level - уровень сообщения (информация, предупреждение или ошибка)
    */
    static void WriteADM(string Source, string Message, KCLogLogLevel Level = KCLogLogLevel.Info)
    {
        string msg = GetText(Level);
        if (Source!="")
        {
            msg += "[" + Source + "]";
        }
        GetGame().AdminLog(msg + Message);
    }
    /** @brief Получить уровень записи в текстовом представлении (*.log)*/
    static string GetText(KCLogLogLevel level)
    {
        switch (level)
        {
            case KCLogLogLevel.Info:
                return "[Info]";
            case KCLogLogLevel.Warning:
                return "[Warning]";
        }
        return "[Error]";
    }
}
#define KUBC_LOG
#endif