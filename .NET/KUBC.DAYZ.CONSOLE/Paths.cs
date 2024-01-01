using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KUBC.DAYZ.CONSOLE
{
    /// <summary>
    /// Папки мода
    /// </summary>
    public class Paths
    {
        /// <summary>
        /// Папка разработчика модов
        /// </summary>
        public const string DEVPATH = "KUBC";

        /// <summary>
        /// Получить папочку мода в папке профилей
        /// </summary>
        /// <param name="profiles">Папка профилей</param>
        /// <returns>Папка мода</returns>
        public static DirectoryInfo GetModPath(DirectoryInfo profiles)
        {
            return new DirectoryInfo($"{profiles.FullName}\\{DEVPATH}");
        }

        /// <summary>
        /// Папка с настройками глобального чата
        /// </summary>
        public const string GCPATH = "CHAT";

        /// <summary>
        /// Получить папочку с настройками глобального чата
        /// </summary>
        /// <param name="profiles">Папка профилей</param>
        /// <returns>Папка с настройками глобального чата</returns>
        public static DirectoryInfo GetGlobalChatPath(DirectoryInfo profiles)
        {
            return new DirectoryInfo($"{GetModPath(profiles).FullName}\\{GCPATH}");
        }

        /// <summary>
        /// Папка с настройками команд
        /// </summary>
        public const string CMDPATH = "CMD";

        /// <summary>
        /// Получить папочку с настройками команд
        /// </summary>
        /// <param name="profiles">Папка профилей</param>
        /// <returns>Папка с настройками команд</returns>
        public static DirectoryInfo GetCMDPath(DirectoryInfo profiles)
        {
            return new DirectoryInfo($"{GetModPath(profiles).FullName}\\{CMDPATH}");
        }

        /// <summary>
        /// Папка с сохранеными координатами
        /// </summary>
        public const string POINTSPATH = "Points";
        
        /// <summary>
        /// Получить папочку с сохранеными координатами
        /// </summary>
        /// <param name="profiles">Папка профилей</param>
        /// <returns>Папка с сохранеными координатами</returns>
        public static DirectoryInfo GetPointsPath(DirectoryInfo profiles)
        {
            return new DirectoryInfo($"{GetModPath(profiles).FullName}\\{POINTSPATH}");
        }

    }
}
