namespace KUBC.DAYZ.CONSOLE
{
    /// <summary>
    /// Тип доступа к чату
    /// </summary>
    public enum AccessType
    {
        /// <summary>
        /// доступ разрешен всем
        /// </summary>
        All = 0,
        /// <summary>
        /// доступ разрешен только указанным пользователям
        /// </summary>
        WhiteList,
        /// <summary>
        /// доступ разрешен всем, кроме указанных пользователей
        /// </summary>
        BlackList
    }
}
