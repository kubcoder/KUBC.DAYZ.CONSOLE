/** @brief команда включения/отключения режима "бога"*/
class KCUserCmdGod : KCUserCMD
{
    
    static const string CMD_NAME = "god";
    
    override string GetName()
    {
        return KCUserCmdGod.CMD_NAME;
    }

    override bool Execute(KCTextCmd data)
    {
        if (data.Arg[0] == "on")
        {
            data.Owner.SetAllowDamage(false);
            data.MessageOwner("Вы стали богом");
            
        }
        else
        {
            data.Owner.SetAllowDamage(true);
            data.MessageOwner("Вы перестали быть богом");
        }
        return true;
    }
}