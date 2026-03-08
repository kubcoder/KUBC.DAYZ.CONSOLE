/// @brief Класс доступа к командам
class KCUserCMDAccess
{
    /// @brief тип доступа (всем, только избранным, всем кроме указанных)
    KCAccessType AccessType = KCAccessType.WhiteList;
    /// @brief список игроков, тут именно SteamID игроков должны быть
    ref TStringArray PlayerList = new TStringArray();

    /// @brief Проверить имеет ли игрок доступ к текстовой команде
    /// @param player игрок который пытается выполнить команду
    /// @return true если игроку разрешено выполнить команду, false если игроку 
    ///         команда недоступна
    bool Garanted(PlayerBase player)
    {
        int index = -1;
        switch(AccessType)
        {
            case KCAccessType.All:
                return true;
            case KCAccessType.WhiteList:
                index = PlayerList.Find(player.GetIdentity().GetPlainId());
                if (index>-1)
                    return true;
                return false;
            case KCAccessType.BlackList:
                index = PlayerList.Find(player.GetIdentity().GetPlainId());
                if (index>-1)
                    return false;
                return true;
        }
        return false;
    }

}