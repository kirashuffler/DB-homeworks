# Работа с Windows 

Существует 2 варианта работа в среде  Windows: использование cygwin или windows компилятора 

## Использование Cygwin 

После установки cygwin необходимо дополнительно поставить gcc и sqlite (или скачать исходный код дополнительно)

## Использования windows компилятора
Для примера будет описана работа с Visual Studio.
* Скачиваем исходный код на [sqlite.org](https://www.sqlite.org/download.html) - выбираем Sourсe код
* Переносим файлы в папку проекта
* Явно добавляем файл sqlite3.c
* В его настройках выбираем - Properties->Configuration Properties->C/C++->Precompiled Headers->Precompiled Header = Not Using Precompiled Headers
