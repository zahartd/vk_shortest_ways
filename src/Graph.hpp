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
  explicit UndirectedGraph(std::size_t graph_size) noexcept;

  ~UndirectedGraph() override;

  void addEdge(std::uint32_t from, std::uint32_t to) final;

protected:
  using AdjacencyList = std::vector<std::vector<std::uint32_t>>;

  AdjacencyList adj_list_;
};

class ShortestPathGraph final : public UndirectedGraph {
public:
  explicit ShortestPathGraph(std::size_t graph_size) noexcept;

  std::vector<std::int64_t> shortestDists(std::uint32_t start) const;
};

} // namespace graphs
