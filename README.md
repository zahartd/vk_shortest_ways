# vk_shortest_ways

Программа на C++, которая считает кратчайшее расстояние от переданной вершины (номер) до всех остальных вершин в ненаправленном графе. Расстояние до каждой вершины от переданной необходимо вывести на экран.

Структура графа должна считываться из файла. Пример файла graph.txt:

```txt
5
4
0 1
0 4
1 2
1 3
4
```

Файл имеет фиксированную структуру.

Первая строка — количество вершин графа.
Вторая строка — количество ребер в графе.
Далее идут ребра графа («0 1» означает, что существует путь от вершины с номером 0 до вершины с номером 1).
Длина каждого ребра равна 1.
Последняя строка — номер вершины, от которой необходимо посчитать расстояние до всех остальных.
Нумерация вершин всегда начинается с нуля.
Допускаем, что точно существует путь до каждой вершины от каждой.
Вывод для тестовых данных выше:

```
1
2
3
3
0
```

## Сборка и запуск

**Сборка проекта**
```bash
make build
```
Сборка проверена на GCC >= 14 и Clang >= 17

**Запуск программы:**
```bash
make run
make run INPUT_FILE=../examples/simple_graph.txt
```

**Запуск тестов:**
```bash
make test
```
Требуется google/googletest (загузиться по сети при первой сборке)

**Запуск стресс-тестов:**
```bash
make stress-test
```
Требуется Python и networkx

**Запуск бенчмарков:**
```bash
make bench
```
Требуется google/benchmarks (загузиться по сети при первой сборке)

## Описание архитектуры

Для сборки и организации проекта используется CMake, также настроены таргеты в make.

Основной код лежиь в src/. Запускаемый и главный файл - main.cpp, в нем определена функция main в которой вызываем другие вспомогательные функции.

Для удобства логика парсинга входа и генерации по нему графа вынесена в отдельную функцию в FileReader.hpp.

Код графа и алгоритмы лежат в Graph.hpp.

В GraphGenerators.hpp лежат функции для генерации графов, это используется в тестах и бенчмарках. Например, функция generateGraph по умолчанию генерирует полные графы заданного размера, но можно указать дополнительно вероятность появления каждого из ребра и получить разреженный граф.

В папке tests лежат юнит тесты написанные с помощью фреймворка googletest. Протестированы функции чтения графа, основные методы графов и написаны базовые тесты на алгоритмы: один мальнький из условия и два генерируемых с разными размерами от 10 до 250 один на полные графы, другой на разреженный с вероятностью появления ребра 0.05. Во всех тестах зафиксирвоан сид для воспроизводимости.

В папке benchmarks представлены бенчмарки - тесты производительности. Рассматривается два типа графа аналогично юнит-тестам. Используется фреймворк для написания бенчмарков - google/benchmarks. Используется метод Complexity для примерного подсчета асимптотики результата и константы.

В папке stress-tests можно найти стресс тесты программы, написан скрипт на Python и стороннего модуля networkx с помощью которого генерируем разные графы: полные, разные степени разряженности, деревья, звезды, колеса, разного размера от 10 до 2500. Записываем графы в файл и запускаем на них нашу программу, для проверки результата используется SSSP solver из networkx. Такие тесты позволяют проверить алгоритм на разных вариациях графов.



## Описание алгоритмов

Проект vk_shortest_ways реализует несколько алгоритмов поиска кратчайших путей для ненаправленного графа с единичными весами ребер:

### **BFS** (поиск в ширину) - самый оптимальный (выбран по умолчанию)
Оптимальный алгоритм для графов с единичными весами ребер. Работает за O(N + M), где N - количество вершин в графе, M - количество ребер в нем. Таким образом, если граф близок к полному и M ≈ N^2, то алгоритм работает за квадрат, если же работает с разреженным графом, то сложность будет линейная. Это наблюдение подтверждается бенчмарками.

###  **Алгоритм Дейкстры**
Общий алгоритм поиска путей, обычно применяется когда ребра могут иметь разные положительные веса, но попробуем применить его к нашей задаче также.
Реализовано два варианта алгоритма: для плотных графов с асимптотикой O(N^2) и разрежённых графов с использование priority_queue (двоичная куча) с асиптотикой O(MlogN). Преймущество второго на разряженном графе подтвердилось бенчмарками.

### **Алгоритм Флойда–Уоршелла**
Алгоритм нахождения длин кратчайших путей между всеми парами вершин во взвешенном ориентированном графе. Работает корректно, если в графе нет циклов отрицательной величины. Но можем попробовать применить к нашей задачи, тем более что это самый простой и комактный алгоритм, по сути все происходит в 4 строчках, три из которых это вложенные циклы. Алгоритм работает за O(N^3) по времени и использует уже значительно больше памяти - (что отличает его от предыдущих) O(N^2). На практики показа очевидно себя хуже всех в рассматриваемоей задачи. Но стоит отметить что используя тривиальную логику параллелизма через std::async получилось ускорить его до условно линейного, но с очень большой константой, согласно бенчмаркам. Также известно что можно параллелить BFS и Дейкстру, так что возможно и их результаты можно ускорить.

## Итог

Самым быстрым алгоритмом для данной задачи согласно тестам оказался ожижаемо BFS. Он показал лучшее время как на полных графах (получаем квадратичный алгоритм с хорошей константой), так и на разряженных (получаем линейный алгоритм). Также стоит отметить что на моих бенчмарках Дейкстра с кучей побеждает обычную как на полном так и на разряженном графе. Флойд-Уоршелл ожидаемо работает за O(N^3), его же параллельная версия хоть и быстрее обычной, но до осталвьных не дотягивает.

Мои замеры:

```
Run on (10 X 2450 MHz CPU s)
CPU Caches:
  L1 Data 64 KiB (x10)
  L1 Instruction 64 KiB (x10)
  L2 Unified 512 KiB (x10)
  L3 Unified 16384 KiB (x10)
Load Average: 0.62, 0.29, 0.17
-------------------------------------------------------------------------------------------------
Benchmark                                                       Time             CPU   Iterations
-------------------------------------------------------------------------------------------------
BM_ShortestDistsBFS_CompleteGraph/10                         2862 ns         2862 ns       244192
BM_ShortestDistsBFS_CompleteGraph/64                        67089 ns        67084 ns        10434
BM_ShortestDistsBFS_CompleteGraph/512                     3871355 ns      3871157 ns          181
BM_ShortestDistsBFS_CompleteGraph/1000                   14664872 ns     14663718 ns           48
BM_ShortestDistsBFS_CompleteGraph_BigO                      14.67 N^2       14.67 N^2
BM_ShortestDistsBFS_CompleteGraph_RMS                           0 %             0 %
BM_ShortestDistsDijkstraForComplete_CompleteGraph/10         9477 ns         9477 ns        73814
BM_ShortestDistsDijkstraForComplete_CompleteGraph/64       342401 ns       342385 ns         2044
BM_ShortestDistsDijkstraForComplete_CompleteGraph/512    21407854 ns     21406631 ns           33
BM_ShortestDistsDijkstraForComplete_CompleteGraph/1000   81609702 ns     81605551 ns            9
BM_ShortestDistsDijkstraForComplete_CompleteGraph_BigO      81.61 N^2       81.61 N^2
BM_ShortestDistsDijkstraForComplete_CompleteGraph_RMS           0 %             0 %
BM_ShortestDistsDijkstraForSparse_CompleteGraph/10           8338 ns         8337 ns        83834
BM_ShortestDistsDijkstraForSparse_CompleteGraph/64         125719 ns       125715 ns         5566
BM_ShortestDistsDijkstraForSparse_CompleteGraph/512       4694323 ns      4694047 ns          149
BM_ShortestDistsDijkstraForSparse_CompleteGraph/1000     16815600 ns     16814586 ns           42
BM_ShortestDistsDijkstraForSparse_CompleteGraph_BigO        16.89 N^2       16.89 N^2
BM_ShortestDistsDijkstraForSparse_CompleteGraph_RMS             3 %             3 %
BM_ShortestDistsFloyd_CompleteGraph/10                      29460 ns        29458 ns        23749
BM_ShortestDistsFloyd_CompleteGraph/64                    6596449 ns      6596050 ns          106
BM_ShortestDistsFloyd_CompleteGraph/512                3310123168 ns   3309920978 ns            1
BM_ShortestDistsFloyd_CompleteGraph/1000               2.4647e+10 ns   2.4646e+10 ns            1
BM_ShortestDistsFloyd_CompleteGraph_BigO                    24.65 N^3       24.65 N^3
BM_ShortestDistsFloyd_CompleteGraph_RMS                         0 %             0 %
BM_ShortestDistsFloydParallel_CompleteGraph/10            6317365 ns      5923971 ns          120
BM_ShortestDistsFloydParallel_CompleteGraph/64           43579847 ns     40433560 ns           17
BM_ShortestDistsFloydParallel_CompleteGraph/512         642541483 ns    300220813 ns            2
BM_ShortestDistsFloydParallel_CompleteGraph/1000       3280457956 ns    556324416 ns            1
BM_ShortestDistsFloydParallel_CompleteGraph_BigO       2852544.72 N     562790.77 N
BM_ShortestDistsFloydParallel_CompleteGraph_RMS                47 %             3 %
BM_ShortestDistsBFS_SparseGraph/10                            591 ns          591 ns       964753
BM_ShortestDistsBFS_SparseGraph/64                          10529 ns        10520 ns        66290
BM_ShortestDistsBFS_SparseGraph/512                        257198 ns       257150 ns         2765
BM_ShortestDistsBFS_SparseGraph/1000                       885719 ns       885689 ns          792
BM_ShortestDistsBFS_SparseGraph_BigO                         0.89 N^2        0.89 N^2
BM_ShortestDistsBFS_SparseGraph_RMS                             4 %             4 %
BM_ShortestDistsDijkstraForComplete_SparseGraph/10           7800 ns         7800 ns        90228
BM_ShortestDistsDijkstraForComplete_SparseGraph/64         266687 ns       266635 ns         2598
BM_ShortestDistsDijkstraForComplete_SparseGraph/512      16489816 ns     16488919 ns           42
BM_ShortestDistsDijkstraForComplete_SparseGraph/1000     62243896 ns     62240195 ns           11
BM_ShortestDistsDijkstraForComplete_SparseGraph_BigO        62.29 N^2       62.28 N^2
BM_ShortestDistsDijkstraForComplete_SparseGraph_RMS             0 %             0 %
BM_ShortestDistsDijkstraForSparse_SparseGraph/10              842 ns          842 ns       832588
BM_ShortestDistsDijkstraForSparse_SparseGraph/64           129302 ns       129294 ns         8940
BM_ShortestDistsDijkstraForSparse_SparseGraph/512         2021291 ns      2021178 ns          385
BM_ShortestDistsDijkstraForSparse_SparseGraph/1000        4778188 ns      4777885 ns          145
BM_ShortestDistsDijkstraForSparse_SparseGraph_BigO         472.10 NlgN     472.07 NlgN
BM_ShortestDistsDijkstraForSparse_SparseGraph_RMS               5 %             5 %
BM_ShortestDistsFloyd_SparseGraph/10                        27952 ns        27950 ns        24963
BM_ShortestDistsFloyd_SparseGraph/64                      6574809 ns      6574360 ns          107
BM_ShortestDistsFloyd_SparseGraph/512                  3316361523 ns   3316177723 ns            1
BM_ShortestDistsFloyd_SparseGraph/1000                 2.4623e+10 ns   2.4622e+10 ns            1
BM_ShortestDistsFloyd_SparseGraph_BigO                      24.62 N^3       24.62 N^3
BM_ShortestDistsFloyd_SparseGraph_RMS                           0 %             0 %
BM_ShortestDistsFloydParallel_SparseGraph/10              5752580 ns      5373098 ns          128
BM_ShortestDistsFloydParallel_SparseGraph/64             36397391 ns     33799868 ns           20
BM_ShortestDistsFloydParallel_SparseGraph/512           641720553 ns    301551112 ns            2
BM_ShortestDistsFloydParallel_SparseGraph/1000         3233418031 ns    542371873 ns            1
BM_ShortestDistsFloydParallel_SparseGraph_BigO         2814698.99 N     551971.01 N
BM_ShortestDistsFloydParallel_SparseGraph_RMS                  47 %             5 %
```


