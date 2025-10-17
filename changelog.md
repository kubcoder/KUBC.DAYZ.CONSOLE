# Журнал версий
## [3.0](https://github.com/kubcoder/KUBC.DAYZ.CONSOLE/releases/tag/3.0)
### Изменено
- Метод `KCPlayer.PlayerBase Find(string name)` гарантировано возвращает `null` если ник у игрока не установлен (#7)
### Добавлено
- Параметр `KCGlChatSettings.MessageFormat` позволяющий настраивать отображение сообщений в глобальном чате (#8). [Описание настройки](https://kubcoder.ru/dayz/console/settings/globalchat)
## 2.2 
Доработан метод `ContainsArg` в классе текстовой команды `KCTextCmd`
## [2.1(01.01.2024)](https://github.com/kubcoder/KUBC.DAYZ.CONSOLE/releases/tag/2.1)
Исправляем некоторые косяки мода, пока видим только мелкие. Но и за одно переходим на запуск тестового экземпляра без сборки т.е. напрямую.
Дополнительно прукручиваем пакет .NET для работы с файлами мода в стороннем ПО.

## [2.0 (04.11.2023)](https://github.com/kubcoder/KUBC.DAYZ.CONSOLE/releases/tag/2.0)
- Работает глобальный чат
- Добавлен базовый класс команд
- Добавлены команды god, heal, time, weather, sp, jump.