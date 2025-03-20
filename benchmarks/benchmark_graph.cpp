#include <benchmark/benchmark.h>

#include "Graph.hpp"

namespace graphs::benchmarks {

static void BM_ShortestDistsBFS(benchmark::State& state) {
  const size_t n = state.range(0);
  graphs::ShortestPathGraph graph{n};
  for (int i = 0; i < n - 1; ++i) {
    graph.addEdge(i, i + 1);
  }
  for (auto _ : state) {
    auto distances = graph.shortestDistsBFS(0);
    benchmark::DoNotOptimize(distances);
  }
  state.SetComplexityN(n);
}

static void BM_ShortestDistsDijkstraForComplete(benchmark::State& state) {
  const size_t n = state.range(0);
  graphs::ShortestPathGraph graph{n};
  for (int i = 0; i < n - 1; ++i) {
    graph.addEdge(i, i + 1);
  }
  for (auto _ : state) {
    auto distances = graph.shortestDistsDijkstraForComplete(0);
    benchmark::DoNotOptimize(distances);
  }
  state.SetComplexityN(n);
}

static void BM_ShortestDistsDijkstraForSparse(benchmark::State& state) {
  const size_t n = state.range(0);
  graphs::ShortestPathGraph graph{n};
  for (int i = 0; i < n - 1; ++i) {
    graph.addEdge(i, i + 1);
  }
  for (auto _ : state) {
    auto distances = graph.shortestDistsDijkstraForSparse(0);
    benchmark::DoNotOptimize(distances);
  }
  state.SetComplexityN(n);
}

static void BM_ShortestDistsFloyd(benchmark::State& state) {
  const size_t n = state.range(0);
  graphs::ShortestPathGraph graph{n};
  for (int i = 0; i < n - 1; ++i) {
    graph.addEdge(i, i + 1);
  }
  for (auto _ : state) {
    auto distances = graph.shortestDistsFloyd(0);
    benchmark::DoNotOptimize(distances);
  }
  state.SetComplexityN(n);
}

static void BM_ShortestDistsFloydParallel(benchmark::State& state) {
  const size_t n = state.range(0);
  graphs::ShortestPathGraph graph{n};
  for (int i = 0; i < n - 1; ++i) {
    graph.addEdge(i, i + 1);
  }
  for (auto _ : state) {
    auto distances = graph.shortestDistsFloydParallel(0);
    benchmark::DoNotOptimize(distances);
  }
  state.SetComplexityN(n);
}

BENCHMARK(BM_ShortestDistsBFS)
    ->RangeMultiplier(2)
    ->Range(1000, 10000)
    ->Complexity();

BENCHMARK(BM_ShortestDistsDijkstraForComplete)
    ->RangeMultiplier(2)
    ->Range(1000, 10000)
    ->Complexity();

BENCHMARK(BM_ShortestDistsDijkstraForSparse)
    ->RangeMultiplier(2)
    ->Range(1000, 10000)
    ->Complexity();

BENCHMARK(BM_ShortestDistsFloyd)
    ->RangeMultiplier(2)
    ->Range(10, 100)
    ->Complexity();

BENCHMARK(BM_ShortestDistsFloydParallel)
    ->RangeMultiplier(2)
    ->Range(10, 100)
    ->Complexity();

}  // namespace graphs::benchmarks

BENCHMARK_MAIN();
