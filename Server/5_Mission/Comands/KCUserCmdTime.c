/** @brief Команда управлением времени на сервере*/
class KCUserCmdTime : KCUserCMD
{
    static const string CMD_NAME = "time";

    static const string MORNING = "morning";
    static const string DAY = "day";
    static const string EVENING = "evening";
    static const string NIGHT = "night";

    
    override string GetName()
    {
        return KCUserCmdTime.CMD_NAME;
    }

    override bool OnExecute(PlayerBase user, KCTextCmd data)
    {
        int year, month, day, hour, minute;
        GetGame().GetWorld().GetDate(year, month, day, hour, minute);
        if (data.Arg.Count()>0)
        {
            if (data.Arg[0] == DAY)
            {
                hour = 12;
                minute = 0;
                GetGame().GetWorld().SetDate(year, month, day, hour, minute);
                KCPlayer.SendMessage(user, "", "сейчас будет день");
                return true;
            }
            if (data.Arg[0] == MORNING)
            {
                hour = 8;
                minute = 0;
                GetGame().GetWorld().SetDate(year, month, day, hour, minute);
                KCPlayer.SendMessage(user, "", "сейчас будет утро");
                return true;
            }
            if (data.Arg[0] == EVENING)
            {
                hour = 18;
                minute = 0;
                GetGame().GetWorld().SetDate(year, month, day, hour, minute);
                KCPlayer.SendMessage(user, "", "сейчас будет вечер");
                return true;
            }
            if (data.Arg[0] == NIGHT)
            {
                hour = 0;
                minute = 0;
                GetGame().GetWorld().SetDate(year, month, day, hour, minute);
                KCPlayer.SendMessage(user, "", "сейчас будет ночь");
                return true;
            }
            if (data.Arg.Count()>1)
            {
                hour = data.Arg[0].ToInt();
                minute = data.Arg[1].ToInt();
                GetGame().GetWorld().SetDate(year, month, day, hour, minute);
                KCPlayer.SendMessage(user, "", "Устанавливается время " + hour.ToStringLen(2) + ":" + minute.ToStringLen(2));
                return true;
            }
        }
        KCPlayer.SendMessage(user,"", day.ToStringLen(2) + "." + month.ToStringLen(2) + "." + year.ToStringLen(4) + " " + hour.ToStringLen(2) + ":" + minute.ToStringLen(2));
        return true;
    }
}