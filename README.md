# vk_shortest_ways

## Сборка и запуск

**Создание каталога сборки:**
```bash
mkdir build_debug
cd build_debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . -j$(nproc)
```

**Запуск программа:**
```bash
./graph_app path/to/graph.txt
```

**Запуск тестов:**
```bash
ctest --output-on-failure
```

**Запуск бенчмарков:**
```bash
./benchmarks/benchmark_app
```
