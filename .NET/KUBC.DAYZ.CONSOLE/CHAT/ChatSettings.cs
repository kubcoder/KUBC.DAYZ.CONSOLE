using System;
using System.Collections.Generic;
using System.Linq;
using System.Resources;
using System.Text;
using System.Text.Encodings.Web;
using System.Text.Json;
using System.Text.Unicode;
using System.Threading.Tasks;

namespace KUBC.DAYZ.CONSOLE.CHAT
{
    /// <summary>
    /// Настройки глобального чата
    /// </summary>
    public class ChatSettings
    {
        /// <summary>
        /// Включение глобального чата
        /// </summary>
        public int Enable { get; set; } = 1;
        /// <summary>
        /// Настройка доступа к глобальному чату
        /// </summary>
        public AccessType Access { get; set; } = AccessType.All;
        /// <summary>
        /// Список игроков
        /// </summary>
        public List<string> Players { get; set; } = [];
        /// <summary>
        /// Символы в начале строки которые исключают отправку в глобальный чат
        /// </summary>
        public List<string> ExecuteSymbols { get; set; } = [];
        /// <summary>
        /// Имя файла настроек
        /// </summary>
        public const string FILENAME = "GlobalChat.json";

        /// <summary>
        /// Из какого файла были загружены настройки
        /// </summary>
        private FileInfo? LoadedFile;
        
        /// <summary>
        /// Создать экземпляр настроек с загрузкой данных из файла
        /// </summary>
        /// <param name="fileInfo">Файл из которого нужно загрузится</param>
        public static ChatSettings Load(FileInfo fileInfo)
        {
            using (var reader = fileInfo.OpenText())
            {
                var res = JsonSerializer.Deserialize<ChatSettings>(reader.BaseStream);
                reader.Close();
                if (res != null)
                {
                    res.LoadedFile = fileInfo;
                    return res;
                }
                else
                {
                    throw new Exception(Resources.CHAT.ChatSettings.NullFile);
                }
            }
        }
        /// <summary>
        /// Получить полное имя файла настроек глобального чата
        /// </summary>
        /// <param name="profiles">Папка профилей сервера</param>
        /// <returns>Информация о файле настроек глобального чата</returns>
        public static FileInfo GetFile(DirectoryInfo profiles)
        {
            return new FileInfo($"{Paths.GetGlobalChatPath(profiles).FullName}\\{FILENAME}");
        }
        /// <summary>
        /// Создать экземпляр настроек с загрузкой данных из файла
        /// </summary>
        /// <param name="profiles">Папка профилей сервера</param>
        /// <returns></returns>
        public static ChatSettings Load(DirectoryInfo profiles)
        {
            return Load(GetFile(profiles));
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
                    JsonSerializer.Serialize<ChatSettings>(stream.BaseStream, this, o);
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

    }
}
