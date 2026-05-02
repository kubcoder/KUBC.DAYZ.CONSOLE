/** @brief Команда перемещения игрока по карте */
class KCUserCmdJump : KCUserCMD
{
    const string CMD_NAME = "jump";

    override string GetName()
    {
        return KCUserCmdJump.CMD_NAME;
    }

    ref KCPointManager pointManager;

    void KCUserCmdJump(KCPointManager manager)
    {
        pointManager = manager;
    }

    override bool Execute(KCTextCmd data)
    {
        if (data.Arg[0] == ">")
        {
            return JumpTo(data);
            
        }
        if (data.Arg[0]=="<")
        {
            return TeleportPlayer(data);
            
        }
        if (data.Arg[0]=="^")
        {
            return JumpUp(data);
            
        }
        data.MessageOwner("Неправильный формат команды!");
        return false;
    }
    
    /// @brief путешествуем по карте
    bool JumpTo(KCTextCmd data)
    {
        if (data.Player != null)
        {
            data.Owner.SetPosition(data.Player.GetPosition());
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
                data.Owner.SetPosition(target);
                return true;
            }
        }
        float delta = data.ExtText.ToFloat();
        if (delta>0)
        {
            target = data.Owner.GetPosition() + delta * data.Owner.GetDirection();
            float Y = GetGame().SurfaceY(target[0], target[2]);
            if (target[1]<Y)
            {
                target[1]=Y;
            }
            data.Owner.SetPosition(target);
            return true;
        }
        string sLine = data.ExtText;
        sLine.ToLower();
        if (pointManager.Teleport(data.Owner, sLine))
        {
            return true;
        }
        data.MessageOwner("Не получилось понять куда вас переместить");
        return false;
    }

    /// @brief прыгаем в верх
    bool JumpUp(KCTextCmd data)
    {
        float delta = data.ExtText.ToFloat();
        vector target = data.Owner.GetPosition();
        target[1] = target[1] + delta;
        data.Owner.SetPosition(target);
        return true;
    }

    /// @brief Телепортируем игрока к админу
    bool TeleportPlayer(KCTextCmd data)
    {
        if(data.Player != null)
        {
            data.Player.SetPosition(data.Owner.GetPosition());
            return true;
        }
        else
        {
            data.MessageOwner("Игрок [" + data.ExtText + "] не найден");
            return false;
        }
    }
}