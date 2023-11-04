/** @brief Команда перемещения игрока по карте */
class KCUserCmdJump : KCUserCMD
{
    static const string CMD_NAME = "jump";

    override string GetName()
    {
        return KCUserCmdJump.CMD_NAME;
    }

    override bool OnExecute(PlayerBase user, KCTextCmd data)
    {
        if (data.Arg[0] == ">")
        {
            return JumpTo(user, data);
            
        }
        if (data.Arg[0]=="<")
        {
            return TeleportPlayer(user, data);
            
        }
        if (data.Arg[0]=="^")
        {
            return JumpUp(user, data);
            
        }
        KCPlayer.SendMessage(user,"","Неправильный формат команды!");
        return false;
    }
    /** @brief путешествуем по карте*/
    bool JumpTo(PlayerBase player, KCTextCmd data)
    {
        if (data.Player != null)
        {
            player.SetPosition(data.Player.GetPosition());
            return true;
        }
        TStringArray sVector = new TStringArray;
        data.ExtText.Split(",", sVector);
        vector target;
        if (sVector.Count()==3)
        {
            string tString = sVector[0] + " " + sVector[1] + " " + sVector[2];
            target = tString.ToVector();
            if (target!=vector.Zero)
            {
                if (target[1]==0)
                {
                    target[1] = GetGame().SurfaceY(target[0],target[2]);
                }
                player.SetPosition(target);
                return true;
            }
        }
        float delta = data.ExtText.ToFloat();
        if (delta>0)
        {
            target = player.GetPosition() + delta * player.GetDirection();
            float Y = GetGame().SurfaceY(target[0], target[2]);
            if (target[1]<Y)
            {
                target[1]=Y;
            }
            player.SetPosition(target);
            return true;
        }
        string sLine = data.ExtText;
        sLine.ToLower();
        TPointMap sPoints = KCUserCmdSP.GetPoints(KCUserCmdSP.GetUserFileName(player));
        KCPoint point = sPoints.Get(sLine);
        if (point)
        {
            player.SetPosition(point.Position);
            player.SetOrientation(point.Orientation);
            return true;
        }
        sPoints = KCUserCmdSP.GetPoints(KCUserCmdSP.GetGlobalFileName());
        point = sPoints.Get(sLine);
        if (point)
        {
            player.SetPosition(point.Position);
            player.SetOrientation(point.Orientation);
            return true;
        }
        KCPlayer.SendMessage(player, "", "Не получилось понять куда вас кинуть");
        return false;
    }

    /** @brief прыгаем в верх*/
    bool JumpUp(PlayerBase player, KCTextCmd data)
    {
        float delta = data.ExtText.ToFloat();
        vector target = player.GetPosition();
        target[1] = target[1] + delta;
        player.SetPosition(target);
        return true;
    }
    /** @brief Телепортируем игрока к админу*/
    bool TeleportPlayer(PlayerBase player, KCTextCmd data)
    {
        if(data.Player != null)
        {
            data.Player.SetPosition(player.GetPosition());
            return true;
        }
        else
        {
            KCPlayer.SendMessage(player,"","Игрок [" + data.ExtText + "] не найден");
            return false;
        }
    }
}