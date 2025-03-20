#include <benchmark/benchmark.h>

#include "Graph.hpp"
#include "GraphGenerators.hpp"

namespace graphs::benchmarks {

namespace {

constexpr double kSparseCoeff = 0.05;

}

static void BM_ShortestDistsBFS_CompleteGraph(benchmark::State& state) {
  const size_t n = state.range(0);
  auto graph = generateGraph(n);
  for (auto _ : state) {
    auto distances = graph.shortestDistsBFS(0);
    benchmark::DoNotOptimize(distances);
  }
  state.SetComplexityN(n);
}

static void BM_ShortestDistsBFS_SparseGraph(benchmark::State& state) {
  const size_t n = state.range(0);
  auto graph = generateGraph(n, kSparseCoeff);
  for (auto _ : state) {
    auto distances = graph.shortestDistsBFS(0);
    benchmark::DoNotOptimize(distances);
  }
  state.SetComplexityN(n);
}

static void BM_ShortestDistsDijkstraForComplete_CompleteGraph(
    benchmark::State& state) {
  const size_t n = state.range(0);
  auto graph = generateGraph(n);
  for (auto _ : state) {
    auto distances = graph.shortestDistsDijkstraForComplete(0);
    benchmark::DoNotOptimize(distances);
  }
  state.SetComplexityN(n);
}

static void BM_ShortestDistsDijkstraForComplete_SparseGraph(
    benchmark::State& state) {
  const size_t n = state.range(0);
  auto graph = generateGraph(n, kSparseCoeff);
  for (auto _ : state) {
    auto distances = graph.shortestDistsDijkstraForComplete(0);
    benchmark::DoNotOptimize(distances);
  }
  state.SetComplexityN(n);
}

static void BM_ShortestDistsDijkstraForSparse_CompleteGraph(
    benchmark::State& state) {
  const size_t n = state.range(0);
  auto graph = generateGraph(n);
  for (auto _ : state) {
    auto distances = graph.shortestDistsDijkstraForSparse(0);
    benchmark::DoNotOptimize(distances);
  }
  state.SetComplexityN(n);
}

static void BM_ShortestDistsDijkstraForSparse_SparseGraph(
    benchmark::State& state) {
  const size_t n = state.range(0);
  auto graph = generateGraph(n, kSparseCoeff);
  for (auto _ : state) {
    auto distances = graph.shortestDistsDijkstraForSparse(0);
    benchmark::DoNotOptimize(distances);
  }
  state.SetComplexityN(n);
}

static void BM_ShortestDistsFloyd_CompleteGraph(benchmark::State& state) {
  const size_t n = state.range(0);
  auto graph = generateGraph(n);
  for (auto _ : state) {
    auto distances = graph.shortestDistsFloyd(0);
    benchmark::DoNotOptimize(distances);
  }
  state.SetComplexityN(n);
}

static void BM_ShortestDistsFloyd_SparseGraph(benchmark::State& state) {
  const size_t n = state.range(0);
  auto graph = generateGraph(n, kSparseCoeff);
  for (auto _ : state) {
    auto distances = graph.shortestDistsFloyd(0);
    benchmark::DoNotOptimize(distances);
  }
  state.SetComplexityN(n);
}

static void BM_ShortestDistsFloydParallel_CompleteGraph(
    benchmark::State& state) {
  const size_t n = state.range(0);
  auto graph = generateGraph(n);
  for (auto _ : state) {
    auto distances = graph.shortestDistsFloydParallel(0);
    benchmark::DoNotOptimize(distances);
  }
  state.SetComplexityN(n);
}

static void BM_ShortestDistsFloydParallel_SparseGraph(benchmark::State& state) {
  const size_t n = state.range(0);
  auto graph = generateGraph(n, kSparseCoeff);
  for (auto _ : state) {
    auto distances = graph.shortestDistsFloydParallel(0);
    benchmark::DoNotOptimize(distances);
  }
  state.SetComplexityN(n);
}

BENCHMARK(BM_ShortestDistsBFS_CompleteGraph)->Range(10, 1000)->Complexity();
BENCHMARK(BM_ShortestDistsDijkstraForComplete_CompleteGraph)
    ->Range(10, 1000)
    ->Complexity();
BENCHMARK(BM_ShortestDistsDijkstraForSparse_CompleteGraph)
    ->Range(10, 1000)
    ->Complexity();
BENCHMARK(BM_ShortestDistsFloyd_CompleteGraph)->Range(10, 1000)->Complexity();
BENCHMARK(BM_ShortestDistsFloydParallel_CompleteGraph)
    ->Range(10, 1000)
    ->Complexity();

BENCHMARK(BM_ShortestDistsBFS_SparseGraph)->Range(10, 1000)->Complexity();
BENCHMARK(BM_ShortestDistsDijkstraForComplete_SparseGraph)
    ->Range(10, 1000)
    ->Complexity();
BENCHMARK(BM_ShortestDistsDijkstraForSparse_SparseGraph)
    ->Range(10, 1000)
    ->Complexity();
BENCHMARK(BM_ShortestDistsFloyd_SparseGraph)->Range(10, 1000)->Complexity();
BENCHMARK(BM_ShortestDistsFloydParallel_SparseGraph)
    ->Range(10, 1000)
    ->Complexity();

}  // namespace graphs::benchmarks

BENCHMARK_MAIN();
