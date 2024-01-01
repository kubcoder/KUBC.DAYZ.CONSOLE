/** @brief Команда сохранения точек положения игрока на диске сервера */
class KCUserCmdSP : KCUserCMD
{
    /** @brief Название команды */
    static const string CMD_NAME = "sp";
    /** @brief Папка в которой хранятся данные точек которые сохраняет юзер*/
    static const string PATH_NAME = "Points";
    /** @brief глобальный файл точек которые доступны всем пользователям*/
    static const string GLOBAL_FILE_NAME = "SharedPoints.json";

    /** @brief атрибут указывающий что нужно работать с глобальным списоком точек*/
    static const string ATT_GLOBAL = "g";
    /** @brief атрибут указывающий что нужно перезаписать точку*/
    static const string ATT_OWERWRITE = "r";

    static string GetPath()
    {
        return "$profile:"+KCCmd.ROOT_PATH + "\\" + KCUserCmdSP.PATH_NAME;
    }

    void KCUserCmdSP()
    {
        MakeDirectory("$profile:"+KCCmd.ROOT_PATH);
        MakeDirectory(KCUserCmdSP.GetPath());
    }

    override string GetName()
    {
        return KCUserCmdSP.CMD_NAME;
    }

    override bool OnExecute(PlayerBase user, KCTextCmd data)
    {
        if ((data.Arg.Count()>0)&&(data.Arg[0]!=""))
        {
            string FileName = "";
            if (data.ContainsArg(ATT_GLOBAL))
            {
                FileName = GetGlobalFileName();
            }
            else
            {
                FileName = GetUserFileName(user);
            }
            TPointMap points = GetPoints(FileName);
            string pointName = data.Arg[0];
            pointName.ToLower();
            KCPoint point = points.Get(pointName);
            if (point)
            {
                if (data.ContainsArg(ATT_OWERWRITE))
                {
                    point.Position = user.GetPosition();
                    point.Orientation = user.GetOrientation();
                    KCPlayer.SendMessage(user,"", "Точка [" + pointName + "] обновлена"); 
                    Log("Точка [" + pointName + "] обновлена", user);               
                }
                else
                {
                    KCPlayer.SendMessage(user,"", "Точка [" + pointName + "] уже существует!"); 
                    return false;
                }
            }
            else
            {
                point = new KCPoint();
                point.Position = user.GetPosition();
                point.Orientation = user.GetOrientation();
                points.Insert(pointName, point);
                KCPlayer.SendMessage(user,"", "Точка [" + pointName + "] добавлена");   
                Log("Точка [" + pointName + "] добавлена", user);
            }
            JsonFileLoader<TPointMap>.JsonSaveFile( FileName, points);
            return true;
        } 
        return false;       
    }

    static TPointMap GetPoints(string FileName)
    {
        TPointMap points;
        JsonFileLoader<TPointMap>.JsonLoadFile(FileName, points);
        if (points)
            return points;
        return new TPointMap();       
    }

    static string GetUserFileName(PlayerBase user)
    {
        return KCUserCmdSP.GetPath() + "\\" + user.GetIdentity().GetPlainId() + ".json";
    }

    static string GetGlobalFileName()
    {
        return KCUserCmdSP.GetPath() + "\\" + GLOBAL_FILE_NAME;
    }
}