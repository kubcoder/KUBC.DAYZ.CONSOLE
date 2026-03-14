/// @brief Фабрика текстовых команд
class KCTextCmdFactory
{
    /// @brief  Символ префикса перед командой
    const string CMD_PREFIX = "/";

    KCTextCmd Get(string TextCMD)
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

    KCTextCmd Get(ChatMessageEventParams chat)
    {
        if (chat.param3.Get(0)==CMD_PREFIX)
        {
            PlayerBase from = KCPlayer.Find(chat.param2);
            if (from)
            {
                int len = chat.param3.Length() - 1;
                string cmdText = chat.param3.Substring(1, len);
                KCTextCmd cmd = Get(cmdText);
                if (cmd)
                {
                    cmd.Owner = from;
                    return cmd;
                }
            }
        }
        return NULL;
    }
}