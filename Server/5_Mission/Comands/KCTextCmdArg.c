/// @brief Аргумент текстовой команды
class KCTextCmdArg
{
    /// @brief Имя аргумента
    string Name = "";

    /// @brief Значение аргумента
    string Value = "";
    
    /// @brief Проверить наличие значения аргумента
    /// @return истина если значение не пустое
    bool HasValue()
    {
        return Value != "";
    }

    /// @brief Создать аргумент из элемента строки команды
    /// @param argument строка которая определена как аргумент
    void KCTextCmdArg(string argument)
    {
        TStringArray data = new TStringArray;
        argument.Split("=", data);
        Name = data[0];
        if (data.Count()>1)
        {
            Value = data[1];
        }
    }
}