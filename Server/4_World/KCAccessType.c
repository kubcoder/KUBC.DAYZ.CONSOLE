#ifndef KUBC_ACCESS
/** @brief Тип доступа к функциям текстовой консоли */
enum KCAccessType
{
    /** @brief доступ разрешен всем*/
    All,
    /** @brief доступ разрешен только указанным пользователям*/
    WhiteList,
    /** @brief доступ разрешен всем, кроме указанных пользователей*/
    BlackList
}
#define KUBC_ACCESS
#endif