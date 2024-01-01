using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.Encodings.Web;
using System.Text.Json;
using System.Text.Unicode;
using System.Threading.Tasks;

namespace KUBC.DAYZ.CONSOLE.CMD
{
    /// <summary>
    /// Настройки доступа к команде в игре
    /// </summary>
    public class UserCMDAccess
    {
        /// <summary>
        /// Тип доступа к команде
        /// </summary>
        public AccessType AccessType { get; set; } = AccessType.All;
        /// <summary>
        /// Список игроков
        /// </summary>
        public List<string> PlayerList { get; set; } = [];

        /// <summary>
        /// Получить имя команды
        /// </summary>
        /// <returns>Вовзращается название команды, если была загрузка из файла</returns>
        public string? GetCMDName()
        {
            if (LoadedFile!=null)
            {
                return Path.GetFileNameWithoutExtension(LoadedFile.Name);
            }
            return null;
        }

        /// <summary>
        /// Файл из которого была загрузка
        /// </summary>
        private FileInfo? LoadedFile;
        /// <summary>
        /// Создать экземпляр настроек с загрузкой данных из файла
        /// </summary>
        /// <param name="file">Файл из которого нужно загрузится</param>
        public static UserCMDAccess Load(FileInfo file)
        {
            using (var reader = file.OpenText())
            {
                var res = JsonSerializer.Deserialize<UserCMDAccess>(reader.BaseStream);
                reader.Close();
                if (res != null)
                {
                    res.LoadedFile = file;
                    return res;
                }
                else
                {
                    throw new Exception(Resources.CHAT.ChatSettings.NullFile);
                }
            }
        }

        /// <summary>
        /// Сохранить настройки в файл
        /// </summary>
        /// <param name="file">В какой файл сохранять</param>
        /// <returns>null если сохранение прошло успешно, иначе исключение которое возникло при сохранения</returns>
        public Exception? Save(FileInfo file)
        {
            try
            {
                var o = new JsonSerializerOptions()
                {
                    WriteIndented = true,
                    Encoder = JavaScriptEncoder.Create(UnicodeRanges.BasicLatin, UnicodeRanges.Cyrillic)
                };
                using (var stream = file.CreateText())
                {
                    JsonSerializer.Serialize<UserCMDAccess>(stream.BaseStream, this, o);
                    stream.Close();
                }
                return null;
            }
            catch (Exception ex) { return ex; }
        }

        /// <summary>
        /// Если файл был загружен, то данный метод сохраняет в файл
        /// из которого была загрузка
        /// </summary>
        /// <returns>null если сохранение прошло успешно, иначе исключение которое возникло при сохранения</returns>
        public Exception? Save()
        {
            if (LoadedFile != null)
                return Save(LoadedFile);
            return new Exception(Resources.CHAT.ChatSettings.NoFile);
        }

        /// <summary>
        /// Загрузить все настройки команд для сервера
        /// </summary>
        /// <param name="profiles">Папка профилей сервера</param>
        /// <returns>Словарь команд</returns>
        public static Dictionary<string, UserCMDAccess> Find(DirectoryInfo profiles)
        {
            var r = new Dictionary<string, UserCMDAccess>();
            var path = Paths.GetCMDPath(profiles);
            if (path!=null)
            {
                var files = path.GetFiles();
                if (files!=null)
                {
                    foreach(var file in files) 
                    {
                        var cmd = UserCMDAccess.Load(file);
                        if (cmd!=null)
                        {
                            var name = cmd.GetCMDName();
                            if (!string.IsNullOrEmpty(name))
                            {
                                r.Add(name, cmd);
                            }
                        }
                    }
                }
            }
            return r;
        }
    }
}
