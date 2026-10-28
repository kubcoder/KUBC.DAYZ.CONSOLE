/// @brief Команда тестирования сообщений игроку со стороны сервера
class KCMsgCMD : KCUserCMD
{
    static const string CMD_NAME = "msg";

    override string GetName()
    {
        return KCMsgCMD.CMD_NAME;
    }

    override bool Execute(KCTextCmd data)
    {
        string style = "colorStatusChannel";
        if(data.Arg.Count()>0)
        {
            style = data.Arg[0];
        }
        data.GetTarget().Message("Тестовое сообщение", style);
        return true;
    }
}