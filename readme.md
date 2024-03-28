sudo apt install libjson-c-dev
gcc test.c -ljson-c -o test
./test

Инфа отсюда:
https://www.youtube.com/watch?v=dQyXuFWylm4

https://github.com/rbtylee/tutorial-jsonc/blob/master/tutorial/new.md

-------------------------------------------------------------------

gcc array_to_json_to_file.c -ljson-c -o save
./save

Команда - собрать динамическую библиотеку (уже для импорта в python):
gcc npconverter.c -shared -ljson-c -o npconverter.so -I/usr/include/python3.10 -I/home/dima/.local/lib/python3.10/site-packages/numpy/core/include -fPIC

Ключи:
-c - отсутствует, так как не только компилируем, но и компануем
-shared - создать динамическую библиотеку
-ljson-c - использовать при компоновке  библиотеку json-c. После выполнения команды "sudo apt install libjson-c-dev" файл json-c/json.h будет находиться в /usr/include. Этот адрес компановщик должен распознать автоматически.
-o - имя выходного файла
-I - добавить каталоги для поиска заголовочных файлов в процессе сборки (для python и numpy)
-fPIC - испольтзование относительных адресов