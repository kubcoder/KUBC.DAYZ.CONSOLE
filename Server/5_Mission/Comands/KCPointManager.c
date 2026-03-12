/// @brief Менеджер точек сохраняемых игроками 
class KCPointManager
{
    /// @brief Директория точек пользователей
    ref KCPointDirectory PointsDirectory;

    void KCPointFactory()
    {
        PointsDirectory = new KCPointDirectory();
        PointsDirectory.CreatePaths();    
    }

    TPointMap GetPoints(string fileName)
    {
        TPointMap points;
        JsonFileLoader<TPointMap>.JsonLoadFile(fileName, points);
        if (points)
            return points;
        return new TPointMap();       
    }

    void Save(string fileName, TPointMap points)
    {
        JsonFileLoader<TPointMap>.JsonSaveFile( fileName, points);
    }

}