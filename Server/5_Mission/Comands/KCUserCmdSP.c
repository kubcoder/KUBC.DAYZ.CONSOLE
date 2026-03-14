/// @brief Команда сохранения точек положения игрока на диске сервера 
class KCUserCmdSP : KCUserCMD
{
    /// @brief Название команды 
    const string CMD_NAME = "sp";

    /// @brief атрибут указывающий что нужно работать с глобальным списоком точек
    const string ATT_GLOBAL = "g";
    /// @brief атрибут указывающий что нужно перезаписать точку
    const string ATT_OWERWRITE = "r";

    ref KCPointManager pointManager;

    void KCUserCmdSP(KCPointManager manager)
    {
        pointManager = manager;
    }

    override string GetName()
    {
        return KCUserCmdSP.CMD_NAME;
    }

    override bool Execute(KCTextCmd data)
    {
        if ((data.Arg.Count()>0)&&(data.Arg[0]!=""))
        {
            string fileName = "";
            if (data.ContainsArg(ATT_GLOBAL))
            {
                fileName = pointManager.PointsDirectory.GetFileName();
            }
            else
            {
                fileName = pointManager.PointsDirectory.GetFileName(data.Owner);
            }
            TPointMap points = pointManager.GetPoints(fileName);
            string pointName = data.Arg[0];
            pointName.ToLower();
            KCPoint point = points.Get(pointName);
            if (point)
            {
                if (data.ContainsArg(ATT_OWERWRITE))
                {
                    point.Set(data.Owner);
                    KCPlayer.SendMessage(data.Owner,"", "Точка [" + pointName + "] обновлена"); 
                    Log("Точка [" + pointName + "] обновлена", data.Owner);               
                }
                else
                {
                    KCPlayer.SendMessage(data.Owner,"", "Точка [" + pointName + "] уже существует!"); 
                    return false;
                }
            }
            else
            {
                point = new KCPoint();
                point.Set(data.Owner);
                points.Insert(pointName, point);
                KCPlayer.SendMessage(data.Owner,"", "Точка [" + pointName + "] добавлена");   
                Log("Точка [" + pointName + "] добавлена", data.Owner);
            }
            pointManager.Save(fileName, points);
            return true;
        } 
        return false;       
    }

}