Реализуйте приложение для организации макрозамен в тексте. 
На вход приложению через аргументы командной строки подаётся путь к текстовому файлу, содержащему в
начале набор директив #define, а далее обычный текст. Синтаксис директивы
соответствует стандарту языка C:
                    #define <def_name> <value>
Аргументов у директивы нет, директива не может быть встроена в другую директиву.

Ваше приложение должно обработать содержимое текстового файла, выполнив замены
последовательностей символов <def_name> на <value>. Количество директив
произвольно, некорректных директив нет, объём текста во входном файле произволен.

В имени <def_name> допускается использование символов латинского алфавита
(прописные и строчные буквы не отождествляются) и символов арабских цифр;

значение <value> произвольно и завершается символом переноса строки или символом
конца файла. 

Для хранения имен макросов и макроподстановок используйте
хеш-таблицу размера HASHSIZE (начальное значение равно 128). Для вычисления
хеш-функции интерпретируйте <def_name> как число, записанное в системе счисления
с основанием 62 (алфавит этой системы счисления состоит из символов {0, …,9, A, …,
Z, a, …, z}). 

Хеш-значение для <def_name> в рамках хеш-таблицы вычисляйте как
остаток от деления эквивалентного для <def_name> числа в системе счисления с
основанием 10 на значение HASHSIZE. Для разрешения коллизий используйте метод
цепочек. В ситуациях, когда после модификации таблицы длины самой короткой и
самой длинной цепочек в хеш-таблице различаются в 2 раза и более, пересобирайте
хеш-таблицу с использованием другого значения HASHSIZE (логику модификации
значения HASHSIZE продумайте самостоятельно) до достижения примерно
равномерного распределения объектов структур по таблице. 

Оптимизируйте расчёт хэш-значений при пересборке таблицы при помощи кэширования.