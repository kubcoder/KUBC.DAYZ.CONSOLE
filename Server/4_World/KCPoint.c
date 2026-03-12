/// @brief Класс сохраненной точки 
class KCPoint
{
    /// @brief Координата
    vector Position;
    /// @brief Ориентация
    vector Orientation;

    void Set(PlayerBase player)
    {
        Position = player.GetPosition();
        Orientation = player.GetOrientation();
    }
}
typedef map<string, ref KCPoint>	TPointMap;