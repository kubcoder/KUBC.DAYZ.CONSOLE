#ifndef KC_DATE_TIME
// @brief Класс даты и времени 
class KCDateTime
{
    int Year = 0;
    int Month = 0;
    int Day = 0;

    int Hour = 0;
    int Minute = 0;
    int Second = 0;

    /// @brief Получить текущее время
    static KCDateTime Now()
    {
        KCDateTime r = new KCDateTime();
        GetHourMinuteSecond(r.Hour, r.Minute, r.Second);
        GetYearMonthDay(r.Year, r.Month, r.Day);
        return r;
    }

    // @brief Сравнивает две даты.
    // @return: 
    //   1 — если this > time (this позже)
    //  -1 — если this < time (this раньше)
    //   0 — если даты полностью совпадают
    int Compare(KCDateTime time)
    {

        // Проверка года
        if (Year > time.Year) return 1;
        if (Year < time.Year) return -1;

        // Года равны, проверяем месяц
        if (Month > time.Month) return 1;
        if (Month < time.Month) return -1;

        // Месяцы равны, проверяем день
        if (Day > time.Day) return 1;
        if (Day < time.Day) return -1;

        // Дни равны, проверяем час
        if (Hour > time.Hour) return 1;
        if (Hour < time.Hour) return -1;

        // Часы равны, проверяем минуту
        if (Minute > time.Minute) return 1;
        if (Minute < time.Minute) return -1;

        // Минуты равны, проверяем секунду
        if (Second > time.Second) return 1;
        if (Second < time.Second) return -1;

        // Все поля идентичны
        return 0;
    }

    

    /// @brief Получить дату и время в виде текста
    /// @return Текстовое представление даты и времени в формате DD.MM.YYYY HH:mm
    string GetText()
    {
        return Day.ToStringLen(2) + "." + Month.ToStringLen(2) + "." + Year.ToStringLen(4) + " " + Hour.ToStringLen(2) + ":" + Minute.ToStringLen(2);
    }
}
#define KC_DATE_TIME
#endif