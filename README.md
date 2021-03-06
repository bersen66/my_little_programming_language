# MY_LITTLE_PROGRAMMING_LANGUAGE (название в разработке)

Данный проект является решением лабораторных работ по дисциплине "Разработка предметно-ориентированных языков программирования"

# Установка

## Сначала необходимо установить сторонние библиотеки и системы сборки (если все уже есть, то смело пропускаем этот пункт)

### Ubuntu: 

В проекте используется библиотека boost, поэтому, если она не установлена заранее, ее необходимо скачать.

Для этого в терминале нужно набрать:

```
    sudo apt-get install libboost-all-dev
```

Сборка проекта осуществляется с помощью CMake и утилиты Make, поэтому, если они не установлены их нужно скачать.

Для этого в терминале нужно набрать:

##### Для CMake
```
   sudo apt install cmake 
```

##### Для Make
```
   sudo apt install make 
```

## Сборка из исходников

Для того чтобы собрать проект, нужно запустить скрипт installer.sh

### Как это сделать? 

В папке, где лежит этот README открываем терминал и пишем:

```
   chmod 755 installer.sh
   bash installer.sh
```

Скрипт все сделает сам, в результате получится 2 исполняемых файла COMPILER и INTERPRETER

### COMPILER - нужен для того, чтобы компилировать исходный код

### INTERPRETER - исполняет скомпилированный промежуточный код

# Компиляция программы

Для того чтоб скомпилировать программу необходимо воспользоваться компилятором, притом указав ему соответсвующие флаги:
```
./COMPILER --fp=файл.rtr --o=ПУТЬ_ДО_ФАЙЛА_КУДА_БУДЕТ_ВЫВОДИТЬСЯ_КОД_ДЛЯ_СТЕК_МАШИНЫ
```

* Флаг --help - выведет информацию о всех флагах компилятора, которые могут быть выставлены

* Флаг --o  - опционален и явно указывает где должен располагаться результирующий файл

* Флаг --fp - определяет файл, который будет скомпилирован

* Флаг --l - опционален, выводит на консоль результат лексического анализа

* Флаг --p - опционален, выводит на консоль результат синтаксического анализа

# Запуск программы

Для запуска программы необходимо воспользоваться интерпретатором. Работа с ним аналогична работе с компилятором

Запуск программы: 

```
./INTERPRETER --fp=файл.rpn
```

* Флаг --help - выведет информацию о всех флагах компилятора, которые могут быть выставлены

* Флаг --fp - определяет файл, который будет исполнен

# Синтаксис языка

В языке определены следующие типы данных: 

* Int - целое число
* Bool - логическое значение
* LinkedList - связный список
* Iterator -  определяет положение объекта в связном списке
