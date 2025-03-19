#include "Graph.hpp"

#include <cstddef>
#include <cstdint>
#include <format>
#include <queue>
#include <stdexcept>

namespace graphs {

UndirectedGraph::UndirectedGraph(std::size_t graph_size) noexcept
    : adj_list_{graph_size} {}

UndirectedGraph::~UndirectedGraph() = default;

void UndirectedGraph::addEdge(std::uint32_t from, std::uint32_t to) {
  if (from >= adj_list_.size() || to >= adj_list_.size()) {
    throw std::out_of_range(
        std::format("Incorrect vertex, should be a non-negative number < {}",
                    adj_list_.size()));
  }
  adj_list_[from].push_back(to);
  adj_list_[to].push_back(from);
}

ShortestPathGraph::ShortestPathGraph(std::size_t grap_size) noexcept
    : UndirectedGraph(grap_size) {}

std::vector<std::int64_t>
ShortestPathGraph::shortestDists(std::uint32_t start) const {
  std::vector<std::int64_t> distances(adj_list_.size(), -1);
  std::queue<std::uint32_t> queue;
  distances[start] = 0; // Set 0 dist to yourself
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

} // namespace graphs
