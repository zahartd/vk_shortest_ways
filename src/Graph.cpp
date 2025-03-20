#include "Graph.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <format>
#include <future>
#include <limits>
#include <queue>
#include <stdexcept>
#include <thread>
#include <vector>

namespace graphs {

namespace {

constexpr std::int64_t kINF = std::numeric_limits<std::int64_t>::max() / 2;

}

UndirectedGraph::UndirectedGraph() = default;

UndirectedGraph::UndirectedGraph(std::size_t graph_size) noexcept
    : adj_list_{graph_size} {}

UndirectedGraph::~UndirectedGraph() = default;

void UndirectedGraph::addEdge(std::uint32_t from, std::uint32_t to) {
  if (from >= adj_list_.size() || to >= adj_list_.size()) {
    throw std::out_of_range{
        std::format("Incorrect vertex, should be a non-negative number < {}",
                    adj_list_.size())};
  }
  adj_list_[from].push_back(to);
  adj_list_[to].push_back(from);
  edges_count_ += 2;
}

size_t UndirectedGraph::getEdgesCount() const noexcept { return edges_count_; }

ShortestPathGraph::ShortestPathGraph() = default;

ShortestPathGraph::ShortestPathGraph(std::size_t grap_size) noexcept
    : UndirectedGraph(grap_size) {}

std::vector<std::int64_t> ShortestPathGraph::shortestDistsBFS(
    std::uint32_t start) const noexcept {
  std::vector<std::int64_t> distances(adj_list_.size(), -1);
  distances[start] = 0;
  std::queue<std::uint32_t> queue;
  queue.push(start);

  while (!queue.empty()) {
    std::uint32_t curr = queue.front();
    queue.pop();
    for (auto neighbour : adj_list_[curr]) {
      if (distances[neighbour] == -1) {
        queue.push(neighbour);
        distances[neighbour] = distances[curr] + 1;
      }
    }
  }

  return distances;
}

std::vector<std::int64_t> ShortestPathGraph::shortestDistsDijkstraForComplete(
    std::uint32_t start) const noexcept {
  std::vector<std::int64_t> distances(adj_list_.size(), kINF);
  distances[start] = 0;
  std::vector<bool> visited(adj_list_.size(), false);

  for (std::size_t i = 0; i < adj_list_.size(); ++i) {
    std::int64_t v = -1;
    for (std::int64_t u = 0; u < adj_list_.size(); ++u) {
      if (!visited[u] && (v == -1 || distances[u] < distances[v])) {
        v = u;
      }
    }
    visited[v] = true;
    for (auto u : adj_list_[v]) {
      distances[u] = std::min(distances[u], distances[v] + 1);
    }
  }

  for (auto& dist : distances) {
    if (dist == kINF) {
      dist = -1;
    }
  }

  return distances;
}

std::vector<std::int64_t> ShortestPathGraph::shortestDistsDijkstraForSparse(
    std::uint32_t start) const noexcept {
  std::vector<std::int64_t> distances(adj_list_.size(), kINF);
  distances[start] = 0;
  std::priority_queue<std::pair<std::uint32_t, std::int64_t>> pq;
  pq.push({start, 0});

  while (!pq.empty()) {
    auto [v, curr_dist] = pq.top();
    pq.pop();
    if (curr_dist > distances[v]) {
      continue;
    }
    for (auto u : adj_list_[v]) {
      if (distances[u] > curr_dist + 1) {
        distances[u] = curr_dist + 1;
        pq.push({u, distances[u]});
      }
    }
  }

  for (auto& dist : distances) {
    if (dist == kINF) {
      dist = -1;
    }
  }

  return distances;
}

std::vector<std::int64_t> ShortestPathGraph::shortestDistsFloyd(
    std::uint32_t start) const {
  const std::uint32_t n = adj_list_.size();
  std::vector<std::vector<std::int64_t>> distances_matrix(
      n, std::vector<std::int64_t>(n, kINF));

  for (std::uint32_t i = 0; i < n; ++i) {
    distances_matrix[i][i] = 0;
  }
  for (std::uint32_t from = 0; from < n; ++from) {
    for (std::uint32_t to : adj_list_[from]) {
      distances_matrix[from][to] = 1;
    }
  }

  for (std::uint32_t k = 0; k < n; ++k) {
    for (std::uint32_t i = 0; i < n; ++i) {
      for (std::uint32_t j = 0; j < n; ++j) {
        distances_matrix[i][j] =
            std::min(distances_matrix[i][j],
                     distances_matrix[i][k] + distances_matrix[k][j]);
      }
    }
  }

  for (auto& dist : distances_matrix[start]) {
    if (dist == kINF) {
      dist = -1;
    }
  }

  return distances_matrix[start];
}

std::vector<std::int64_t> ShortestPathGraph::shortestDistsFloydParallel(
    std::uint32_t start) const noexcept {
  const std::uint32_t n = adj_list_.size();
  std::vector<std::vector<std::int64_t>> distances_matrix(
      n, std::vector<std::int64_t>(n, kINF));

  for (std::uint32_t i = 0; i < n; ++i) {
    distances_matrix[i][i] = 0;
  }
  for (std::uint32_t u = 0; u < n; ++u) {
    for (std::uint32_t v : adj_list_[u]) {
      distances_matrix[u][v] = 1;
    }
  }

  const std::uint32_t threads_num = std::thread::hardware_concurrency();
  const std::uint32_t chunk_size =
      (n + threads_num - 1) / threads_num;  // ceil of n / threads_num

  std::vector<std::future<void>> futures;

  for (std::uint32_t k = 0; k < n; ++k) {
    for (std::uint32_t t = 0; t < threads_num; ++t) {
      std::uint32_t from = t * chunk_size;
      std::uint32_t to = std::min(n, from + chunk_size);
      futures.push_back(std::async(std::launch::async, [&, from, to, k]() {
        for (std::uint32_t i = from; i < to; ++i) {
          for (std::uint32_t j = 0; j < n; ++j) {
            distances_matrix[i][j] =
                std::min(distances_matrix[i][j],
                         distances_matrix[i][k] + distances_matrix[k][j]);
          }
        }
      }));
    }
  }

  for (auto& f : futures) {
    f.get();
  }

  for (auto& dist : distances_matrix[start]) {
    if (dist == kINF) {
      dist = -1;
    }
  }

  return distances_matrix[start];
}

}  // namespace graphs
