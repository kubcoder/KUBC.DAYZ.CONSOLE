/// @brief Инструмент работы с файлами
class KCDirectory
{
    /// @brief Массив пути к папке
    ref TStringArray pathNames;

    void KCDirectory()
    {
        pathNames = new TStringArray();
        pathNames.Insert("KUBC");
    }

    /// @brief Создать структуру папок
    void CreatePaths()
    {
        for(int i=0; i< pathNames.Count(); i++)
        {
            MakeDirectory(GetName(i));
        }
    }

    /// @brief Получить полный путь к директории
    /// @param i уровень вложености
    /// @return полный путь в соответсвии с платформой
    string GetName(int i)
    {
        string result = "$profile:";
        for(int j=0; j <= i;j++)
        {
            if (j==0)
            {
                result += pathNames.Get(j);
            }
            else
            {
                   
                result += GetSeparator() + pathNames.Get(j);
            }
        }
        return result;
    }
    /// @brief Получить имя папки
    /// @return Полное название папки
    string GetName()
    {
        return GetName(pathNames.Count() - 1);
    }

    /// @brief Получить полное имя файла
    /// @param fileName имя файла
    /// @return полное название файла
    string GetName(string fileName)
    {
        return GetName() + GetSeparator() + fileName;
    }
    /// @brief Получить сепаратор пути файла в соответсвии с платформой
    /// @return 
    string GetSeparator()
    {
        #ifdef PLATFORM_WINDOWS
        return "\\";
        #endif
        #ifdef PLATFORM_LINUX
        return "/";
        #endif
        return "??";
    }
}