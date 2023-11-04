class KCUserCmdWeather : KCUserCMD
{
    static const string CMD_NAME = "weather";
    static const string RAIN = "r";
    static const string FOG = "f";
    static const string OVERCAST = "o";
    
    static const string CLEAR = "clear";


    override string GetName()
    {
        return KCUserCmdWeather.CMD_NAME;
    }
    override bool OnExecute(PlayerBase user, KCTextCmd data)
    {
        Weather w = GetGame().GetWeather();
        Overcast o = w.GetOvercast();
		Fog f = w.GetFog();
		Rain r = w.GetRain();
        KCPlayer.SendMessage(user, "" , "Fog:" + f.GetActual());
        KCPlayer.SendMessage(user, "" ,  "Overcast:" + o.GetActual());
        KCPlayer.SendMessage(user, "" ,  "Rain:" + r.GetActual());
        if (data.Arg.Count()>0)
        {
            if (data.Arg[0]==CLEAR)
            {
                r.Set(0, 1,1);
                o.Set(0, 1,1);
                f.Set(0, 1,1);
                KCPlayer.SendMessage(user,"", "Устанавливается ясная погода"); 
                return true;
            }
            
        }
        int pIndex = data.Arg.Find(RAIN);
        if (pIndex>-1)
        {
            if (data.Arg.Count()>pIndex+1)
            {
                float newRain = data.Arg[pIndex+1].ToFloat();
                float actRain = r.GetActual();
                r.Set(newRain, 1,1);
                KCPlayer.SendMessage(user,"", "Rain:" + actRain + "->" + newRain); 
            }
        }
        pIndex = data.Arg.Find(OVERCAST);
        if (pIndex>-1)
        {
            if (data.Arg.Count()>pIndex+1)
            {
                float newOvercast = data.Arg[pIndex+1].ToFloat();
                float actOvercast = o.GetActual();
                o.Set(newOvercast, 1,1);
                KCPlayer.SendMessage(user,"", "Overcast:" + actOvercast + "->" + newOvercast); 
            }
        }
        pIndex = data.Arg.Find(FOG);
        if (pIndex>-1)
        {
            if (data.Arg.Count()>pIndex+1)
            {
                float newFog = data.Arg[pIndex+1].ToFloat();
                float actFog = f.GetActual();
                f.Set(newFog, 1,1);
                KCPlayer.SendMessage(user,"", "Fog:" + actFog + "->" + newFog); 
            }
        }
        return true;
    }
}