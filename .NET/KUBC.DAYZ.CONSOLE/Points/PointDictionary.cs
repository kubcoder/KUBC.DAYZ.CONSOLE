using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Encodings.Web;
using System.Text.Json;
using System.Text.Unicode;
using System.Threading.Tasks;

namespace KUBC.DAYZ.CONSOLE.Points
{
    /// <summary>
    /// Словарь точек
    /// </summary>
    public class PointDictionary: Dictionary<string, Point>
    {
        /// <summary>
        /// Файл из которого была загрузка
        /// </summary>
        private FileInfo? LoadedFile;
        /// <summary>
        /// Создать экземпляр настроек с загрузкой данных из файла
        /// </summary>
        /// <param name="file">Файл из которого нужно загрузится</param>
        public static PointDictionary Load(FileInfo file)
        {
            using (var reader = file.OpenText())
            {
                var res = JsonSerializer.Deserialize<PointDictionary>(reader.BaseStream);
                reader.Close();
                if (res != null)
                {
                    res.LoadedFile = file;
                    return res;
                }
                else
                {
                    throw new Exception(Resources.Points.PointDictionary.NullFile);
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
                    JsonSerializer.Serialize<PointDictionary>(stream.BaseStream, this, o);
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
            return new Exception(Resources.Points.PointDictionary.NoFile);
        }
        /// <summary>
        /// Имя файла с общими точками сервера
        /// </summary>
        public static string SharedFileName = "SharedPoints.json";

        /// <summary>
        /// Получить полное имя файла общих точек сервера
        /// </summary>
        /// <param name="profiles">Папка профилей сервера</param>
        /// <returns></returns>
        public static FileInfo GetSharedFile(DirectoryInfo profiles)
        {
            return new FileInfo($"{Paths.GetPointsPath(profiles).FullName}\\{SharedFileName}");
        }
        /// <summary>
        /// Загрзуить общие точки сервера
        /// </summary>
        /// <param name="profiles">Папка профилей сервера</param>
        /// <returns></returns>
        public static PointDictionary LoadShared(DirectoryInfo profiles)
        {
            return Load(GetSharedFile(profiles));
        }
    }
}
