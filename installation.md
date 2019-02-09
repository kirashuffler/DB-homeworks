# Установка

## Шаг 1: Установка Jupyter Notebook

### _Рекомендованный способ_

  [Видео по установке](https://www.youtube.com/watch?v=E8hUFNYt8VU)

  1. Загрузите и установите Anaconda for Python 3.6 (Установка [здесь](https://www.anaconda.com/download/) )

  2. Запустите из командной строки jupyter notebook, чтобы убедиться, что установка завершена

### Установка через pip

  1. Можно установить через Пакетный менеджер python pip: pip install --user --upgrade jupyter

## Шаг 2: Установка других зависимостей

[Видео по установке](https://www.youtube.com/watch?v=ezGSKnWfEq0)

### Git

Git - это система контроля версий, которая будет использована для хранения различных материалов курса. Установить можно [здесь](https://git-scm.com/downloads)

### IPython-SQL

ipython-sql позволит нам использовать SQL запросы внутри jupyter notebook. Для установки зайдите в командную строку через права администратора и напишите следующий код:

```
pip install --user --upgrade ipython-sql
```

## Шаг 3: Начало работы

### Получение последних материалов курса:

[Видео по работе с git](https://www.youtube.com/watch?v=Zr9tsqmdLKM)

Для получения последней версии материалов курса выберите папку, в которой вы планируете хранить материалы курса и запустите через git bash:

```
git clone https://github.com/bakanchevn/DBMIREA-KMBO-15.git
```

Теперь вы можете всегда получить новые материлы курса, выполнив команду

```
git pull
```

находясь в папке с git репозиторием.


## Возможные проблемы

![Anaconda error](https://api.monosnap.com/rpc/file/download?id=YsAx6g8YS46kZJ6TMcbQjhaTit7TrC)

Решение - запустить установщик от имени администратора.
