# string-expression-calculator
Калькулятор, вычисляющий значение выражения, записанного с клавиатуры в строку.

Функционал:

Операции +, -, *, ^ - возведение в степень, % - остаток от деления, / - вещественное деление, | - целочисленное деление, ! - факториал, скобки ();

Функции log(основание, аргумент), sin, cos(угол в радианах);

Константы Pi и е

При написании чисел можно использовать "." для дробной части и "e" для порядка, пример: 136.798e21

Переменные (правила создания имен аналогичны с++) для удобства написания выражения, после введения выражения программа попросит вас ввести значение всех использованных переменных;

Для операций с целыми числами используется длинная арифметика, после использования вещественной операции (/, sin, cos, log, возведении в нецелую или отрицательную степень) выражение будет считаться в double.

При введении некорректного выражения программа укажет на место и суть ошибки.

В строку "RPN" программа выведет обратную польскую запись вашего выражения.

В нижнюю строку программа выведет численный результат.

Проблемы:

Унарный минус перед скобками или функциями работает некорректно;

Практически весь код содержится в mainwindow.cpp

Для запуска проекта надо скачать содержимое папки exe (сам .exe и необходимые dll)
