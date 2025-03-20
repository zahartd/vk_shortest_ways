#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace graphs {

class IGraph {
 public:
  virtual ~IGraph() = default;

  virtual void addEdge(std::uint32_t from, std::uint32_t to) = 0;
};

class UndirectedGraph : public IGraph {
 public:
  explicit UndirectedGraph();
  explicit UndirectedGraph(std::size_t graph_size) noexcept;

  ~UndirectedGraph() override;

  void addEdge(std::uint32_t from, std::uint32_t to) final;

  size_t getEdgesCount() const noexcept;

 protected:
  using AdjacencyList = std::vector<std::vector<std::uint32_t>>;

  AdjacencyList adj_list_;
  size_t edges_count_{};
};

class ShortestPathGraph final : public UndirectedGraph {
 public:
  explicit ShortestPathGraph();
  explicit ShortestPathGraph(std::size_t graph_size) noexcept;

  std::vector<std::int64_t> shortestDistsBFS(
      std::uint32_t start) const noexcept;
  std::vector<std::int64_t> shortestDistsDijkstraForComplete(
      std::uint32_t start) const noexcept;
  std::vector<std::int64_t> shortestDistsDijkstraForSparse(
      std::uint32_t start) const noexcept;
  std::vector<std::int64_t> shortestDistsFloyd(std::uint32_t start) const;
  std::vector<std::int64_t> shortestDistsFloydParallel(
      std::uint32_t start) const noexcept;
};

}  // namespace graphs
