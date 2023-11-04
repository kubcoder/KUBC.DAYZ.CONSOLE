/** @brief Команда лечения игрока*/
class KCUserCmdHeal : KCUserCMD
{
    static const string CMD_NAME = "heal";
    
    static const string ALL = "*";
    static const string BASE = "+";
    static const string BONE = "b";
    static const string CRANK = "a";
    static const string ENERGY = "e";
    static const string COLD = "t";
    static const string DRINK = "d";
    
    override string GetName()
    {
        return KCUserCmdHeal.CMD_NAME;
    }
    override bool OnExecute(PlayerBase user, KCTextCmd data)
    {
        if (!data.Player)
        {
            data.Player = user;
        }
        int pIndex = data.Arg.Find(BASE);
        if((pIndex>-1)||(data.Arg[0]==ALL))
        {
            BaseHeal(data.Player, user.GetIdentity().GetName());
        }
        pIndex = data.Arg.Find(BONE);
        if((pIndex>-1)||(data.Arg[0]==ALL))
        {
            BoneHeal(data.Player, user.GetIdentity().GetName());
        }
        pIndex = data.Arg.Find(CRANK);
        if((pIndex>-1)||(data.Arg[0]==ALL))
        {
            CrankHeal(data.Player, user.GetIdentity().GetName());
        }
        pIndex = data.Arg.Find(ENERGY);
        if((pIndex>-1)||(data.Arg[0]==ALL))
        {
            EnergyHeal(data.Player, user.GetIdentity().GetName());
        }
        pIndex = data.Arg.Find(COLD);
        if((pIndex>-1)||(data.Arg[0]==ALL))
        {
            TemperatureHeal(data.Player, user.GetIdentity().GetName());
        }
        pIndex = data.Arg.Find(DRINK);
        if((pIndex>-1)||(data.Arg[0]==ALL))
        {
            DrinkHeal(data.Player, user.GetIdentity().GetName());
        }
        return true;
    }
    void BaseHeal(PlayerBase target, string From="")
    {
        target.SetHealth(target.GetMaxHealth("", ""));
        target.SetHealth("","Blood", target.GetMaxHealth("","Blood"));
        target.SetHealth("","Shock", target.GetMaxHealth("","Shock"));
        if (target.GetBleedingManagerServer())
        {
            int attempts = 0;
            int cuts = target.GetBleedingManagerServer().m_BleedingSources.Count();

            while(cuts > 0)
            {
                attempts++;
                if (attempts > 15)
                    return;

                if (target.GetBleedingManagerServer())
                {
                    target.GetBleedingManagerServer().RemoveMostSignificantBleedingSource();
                    cuts--;
                }
            }
        }
        KCPlayer.SendMessage(target, From, "Вам оказана медицинская помощь");
    }

    void BoneHeal(PlayerBase target, string From="")
    {
        target.SetHealth("LeftLeg","Health",target.GetMaxHealth("LeftLeg", "Health"));
        target.SetHealth("RightLeg","Health",target.GetMaxHealth("RightLeg", "Health"));
        target.SetHealth("RightFoot","Health",target.GetMaxHealth("RightFoot", "Health"));
        target.SetHealth("LeftFoot","Health",target.GetMaxHealth("LeftFoot", "Health"));
        KCPlayer.SendMessage(target, From, "Все переломы срослись");
    }

    void CrankHeal(PlayerBase target, string From="")
    {
        target.RemoveAllAgents();
        KCPlayer.SendMessage(target, From, "Вас избавили от всех болезней");
    }

    void EnergyHeal(PlayerBase target, string From="")
    {
        target.GetStatEnergy().Set(target.GetStatEnergy().GetMax());   
        target.GetStatDiet().Set(target.GetStatDiet().GetMax());
        KCPlayer.SendMessage(target, From, "Вас накормили до отвала");
    }

    void TemperatureHeal(PlayerBase target, string From="")
    {
        target.GetStatHeatComfort().Set(target.GetStatHeatComfort().GetMax());
        target.GetStatTremor().Set(target.GetStatTremor().GetMin());
        target.GetStatWet().Set(target.GetStatWet().GetMin());
        target.GetStatSpecialty().Set(target.GetStatSpecialty().GetMax());
        target.GetStatHeatBuffer().Set(target.GetStatHeatBuffer().GetMax());
        KCPlayer.SendMessage(target, From, "Вас обогрели");
    }

    void DrinkHeal(PlayerBase target, string From="")
    {
        target.GetStatWater().Set(target.GetStatWater().GetMax());
        KCPlayer.SendMessage(target, From, "Вас напоили");
    }
}