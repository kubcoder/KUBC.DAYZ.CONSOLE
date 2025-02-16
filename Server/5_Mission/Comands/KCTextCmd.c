#ifndef KUBC_TEXT_CMD
/** @brief Класс расшифровки сообщения чата в данные команды */
class KCTextCmd
{
    /** @brief  Символ префикса перед командой */
    static const string CMD_PREFIX = "/";
    /** @brief  название команды*/
    string Name = string.Empty;
    /** @brief  аргументы команды*/
    ref TStringArray Arg = new TStringArray();
    /** @brief  игрок к которому применить команду*/
    PlayerBase Player = NULL;
    /** @brief  Никнейм игрока кому выдать результаты команды
    *           В эту строку сбрасывается никнейм игрока, после чего
    *           выполняется поиск кому же применить команду.
    */
    string ExtText = string.Empty;

    /** @brief создать данные команды из сообщения чата*/
    static KCTextCmd FromChat(string TextCMD)
    {
        KCTextCmd result = new KCTextCmd();
        TStringArray tokens = new TStringArray;
        TextCMD.Split(" ", tokens);
        if (tokens.Count()>0)
        {
            result.Name = tokens[0];
            result.Name.ToLower();
            if (tokens.Count()>1)
            {
                TStringArray args = new TStringArray;
                tokens[1].Split(":", result.Arg);
            }
            if (tokens.Count()>2)
            {
                for(int i=2; i<tokens.Count(); i++)
                {
                    result.ExtText = result.ExtText + tokens.Get(i) + " ";
                }
                result.ExtText = result.ExtText.Trim();
            }
            result.Player = KCPlayer.Find(result.ExtText);
            return result;
        }
        return NULL;
    }

    /** @brief найти целочисленный аргумент с указаным именем
    *   @param name имя аргумента
    *   @param default значение по умолчанию
    *   @return целочисленое значение искомого аргумента 
    *           если аргумент не найден, то возвращается значение default
    */
    int GetInt(string name, int default=0)
    {
        string sValue = GetValue(name);
        if (sValue!="")
        {
            return sValue.ToInt();
        }
        return default;
    }

    /** @brief Получить значение аргумента в виде числа с плавающей точкой
    *   @param name имя аргумента
    *   @param default значение по умолчанию
    *   @return значение искомого аргумента если аргумент не найден, 
    *           то возвращается значение default
    */
    float GetFloat(string name, float default=0)
    {
        string sValue = GetValue(name);
        if (sValue!="")
        {
            return sValue.ToFloat();
        }
        return default;
    }
    /** @brief Найти значение аргумента
    *   @param name имя аргумента
    *   @return значение искомого аргумента в виде строки, 
    *           если аргумент не найден, то возвращается пустая строка
    */
    string GetValue(string name)
    {
        int fLen = name.Length();
        foreach(string arg:Arg)
        {
            int Len = arg.Length();
            if(Len>(fLen+1))
            {
                string aName = arg.Substring(0, fLen);
                if (aName==name)
                {
                    
                    Len -= fLen;
                    Len -= 1;
                    return arg.Substring(fLen+1, Len);
                }
            }
        }
        return "";
    }

    /** @brief определить есть ли в тексте команды указанный аргумент
    *   @param name имя аргумента
    *   @return Истина, если аргумент был найден.
    */
    bool ContainsArg(string name)
    {
        int fLen = name.Length();
        foreach(string arg:Arg)
        {
            /*
            TStringArray argItems = new TStringArray;
            TextCMD.Split("=", argItems);
            
            if(arg.Length()>=fLen)
            {
                string aName = arg.Substring(0, fLen);
                if (aName==name)
                {
                    return true;
                }
            }*/
        }
        return false;
    }
}
#define KUBC_TEXT_CMD
#endif