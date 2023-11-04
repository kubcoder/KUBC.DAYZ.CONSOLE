/** @brief Класс сохраненной точки */
class KCPoint
{
    /** @brief Координата */
    vector Position;
    /** @brief Ориентация*/
    vector Orientation;
}
typedef map<string, ref KCPoint>	TPointMap;