namespace KUBC.DAYZ.CONSOLE.TEST
{
    [TestClass]
    public class BaseTest
    {
        private static DirectoryInfo GetTestProfiles()
        {
            return new DirectoryInfo("..\\..\\..\\..\\..\\Sample\\Profiles"); 
        }
        
        [TestMethod]
        public void LoadSaveCMDSettings()
        {
            var profiles = GetTestProfiles();
            Console.WriteLine(profiles.FullName);
            var cmds = KUBC.DAYZ.CONSOLE.CMD.UserCMDAccess.Find(profiles);
            cmds["god"].Save();
        }
        [TestMethod]
        public void LoadPoints()
        {
            var profiles = GetTestProfiles();
            var sp = Points.PointDictionary.LoadShared(profiles);
        }

    }
}