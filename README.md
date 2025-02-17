# KUBC.DAYZ.CONSOLE
Серверный мод для игры [DAYZ SA](https://dayz.com/) который выполняет обработку сообщений в чат от игроков и добавляет функции:
- Глобальный чат
- Текстовые команды

**[Подробное описание на сайте разработчика](https://kubcoder.ru/dayz/console/index)**

## Глобальный чат
Обеспечивает доставку сообщений из чата всем игрокам сервера вне зависимости от дистанции между ними. Т.е. буквально сообщение в чат будут видеть все игроки сервера. 

Администраторы сервера имеют возможность настроить доступ игроков к данной функции, т.е. разрешить только некоторым писать в глобальный чат, или писать всем кроме указанных. [Как это настроить](https://kubcoder.ru/dayz/console/settings/globalchat)

## Текстовые команды
Функция выполнения действий на стороне сервера по текстовым командам из чата. Данная функция может реализовать функционал администрирования игры без использования клиентского мода. В данном моде добавляются базовые классы команд, а также методика управления доступом к той или иной команде. 
- [Как вызывать команду в игре](https://kubcoder.ru/dayz/console/cmd/format)
- [Полный список команд](https://kubcoder.ru/dayz/console/cmd/)
- [Как добавить новую команду](https://kubcoder.ru/dayz/console/cmd/moding)


# Инструменты
Для разработки мода используется редактор [VS Code](https://code.visualstudio.com/), сборка мода выполняется с помощью [Mikero Tools](https://mikero.bytex.digital/Downloads). 
В рабочем пространстве проекта добавлены инструменты для сборки мода, и запуска сервера с подключенным модом:
- **Clear Server Logs** Выполнить очистку логов сервера
- **Start Test Server** Запустить тестовый сервер с очисткой логов, запуск производится без сборки мода, а напрямую с файлами мода. Для корректной работы нужно создать ссылку на исходные файлы мода инструментом **Create Link**
- **Create Link** Создает в папке сервера ссылку на исходники мода
- **Start Debug Server** Запускает сервер DAYZ с подключеными исходниками мода.

Для выполнения данных команд, в VS Code нажимаем `Shift+Ctrl+P`, далее вводим `Tasks: Run Task` и выбираем из списка одну из команд рабочего пространства.

# Журнал версий
## 2.2 
Доработан метод `ContainsArg` в классе текстовой команды `KCTextCmd`
## [2.1(01.01.2024)](https://github.com/kubcoder/KUBC.DAYZ.CONSOLE/releases/tag/2.1)
Исправляем некоторые косяки мода, пока видим только мелкие. Но и за одно переходим на запуск тестового экземпляра без сборки т.е. напрямую.
Дополнительно прукручиваем пакет .NET для работы с файлами мода в стороннем ПО.
## [2.0 (04.11.2023)](https://github.com/kubcoder/KUBC.DAYZ.CONSOLE/releases/tag/2.0)
- Работает глобальный чат
- Добавлен базовый класс команд
- Добавлены команды god, heal, time, weather, sp, jump.
