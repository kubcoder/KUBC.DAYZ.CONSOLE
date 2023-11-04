/** @brief команда включения/отключения режима "бога"*/
class KCUserCmdGod : KCUserCMD
{
    
    static const string CMD_NAME = "god";
    
    override string GetName()
    {
        return KCUserCmdGod.CMD_NAME;
    }

    override bool OnExecute(PlayerBase user, KCTextCmd data)
    {
        if (data.Arg[0] == "on")
        {
            user.SetAllowDamage(false);
            KCPlayer.SendMessage(user,"","Вы стали богом");
        }
        else
        {
            user.SetAllowDamage(true);
            KCPlayer.SendMessage(user,"","Вы перестали быть богом");
        }
        return true;
    }

}