#ifndef KUBC_USER_CMD_ACCESS
/** @brief класс настройки доступа к команде*/
class KCUserCMDAccess
{
    /** @brief тип доступа (всем, только избранным, всем кроме указанных)*/
    KCAccessType AccessType = KCAccessType.WhiteList;
    /** @brief список игроков, тут именно SteamID игроков должны быть*/
    ref TStringArray PlayerList = new TStringArray();

    /** @brief Проверить имеет ли игрок доступ к текстовой команде
    *   @param player игрок который пытается выполнить команду
    *   @return true если игроку разрешено выполнить команду, false если игроку 
    *           команда недоступна
    */
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

    /** @brief Получить имя файла настроек команды 
    *   @param cmdName - имя текстовой команды
    *   @return полный путь к файлу настроек команды
    */
    static string GetFileName(string cmdName)
    {
        return KCCmd.GetSettingsPath() + "\\" + cmdName + ".json";
    }
    /** @brief Получить настройки команды
    *   @param cmdName - имя текстовой команды
    *   @return настройки текстовой команды, если их почему то нет на диске
                будет возвращен экземпляр с настройками по умолчанию.
    */
    static KCUserCMDAccess GetAccess(string cmdName)
    {
        KCUserCMDAccess access;
        JsonFileLoader<KCUserCMDAccess>.JsonLoadFile( GetFileName(cmdName), access);
        if (access)
            return access;
        return new KCUserCMDAccess();
    }
}
#define KUBC_USER_CMD_ACCESS
#endif;