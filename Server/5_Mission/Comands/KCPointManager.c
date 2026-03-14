/// @brief Менеджер точек сохраняемых игроками 
class KCPointManager
{
    /// @brief Директория точек пользователей
    ref KCPointDirectory PointsDirectory;

    void KCPointManager()
    {
        PointsDirectory = new KCPointDirectory();
        PointsDirectory.CreatePaths();    
    }
    /// @brief Получить словарь точек
    /// @param fileName имя файла для загрузки
    /// @return словарь точек
    TPointMap GetPoints(string fileName)
    {
        TPointMap points;
        JsonFileLoader<TPointMap>.JsonLoadFile(fileName, points);
        if (points)
            return points;
        return new TPointMap();       
    }

    /// @brief Сохарнить словарь точек на диск
    /// @param fileName имя файла
    /// @param points обновленный словарь точек
    void Save(string fileName, TPointMap points)
    {
        JsonFileLoader<TPointMap>.JsonSaveFile( fileName, points);
    }

    /// @brief Найти в словарях точку для телепортации
    /// @param player игрок который хочет прыгнуть
    /// @param pointName имя точки для прыжка
    /// @return точка, если найдена
    KCPoint GetPoint(PlayerBase player, string pointName)
    {
        TPointMap sPoints = GetPoints(PointsDirectory.GetFileName(player));
        KCPoint point = sPoints.Get(pointName);
        if (point)
        {
            return point;
        }
        sPoints = GetPoints(PointsDirectory.GetFileName());
        point = sPoints.Get(pointName);
        return point;

    }

    /// @brief Телепортировать игрока в указанную точку
    /// @param player игрок для телепортации
    /// @param pointName имя точки куда нужно телепортировать
    /// @return истина если удалось телепортировать игрока
    bool Teleport(PlayerBase player, string pointName)
    {
        KCPoint point = GetPoint(player, pointName);
        if (point)
        {
            player.SetPosition(point.Position);
            player.SetOrientation(point.Orientation);
            return true;
        }
        return false;
    }

}