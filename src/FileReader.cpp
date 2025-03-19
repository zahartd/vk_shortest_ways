#include "FileReader.hpp"

#include <filesystem>
#include <format>
#include <fstream>
#include <stdexcept>

#include "Graph.hpp"

namespace graphs {

ShortestPathGraph readGraphFromPath(std::filesystem::path path,
                                    uint32_t &start_vertex) {
  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::runtime_error(
        std::format("Failed to open file: {}", path.string()));
  }

  std::size_t vertices_count, edges_count;
  file >> vertices_count >> edges_count;

  ShortestPathGraph graph(vertices_count);

  for (std::size_t i = 0; i < edges_count; ++i) {
    std::uint32_t from, to;
    file >> from >> to;
    graph.addEdge(from, to);
  }

  file >> start_vertex;

  return graph;
}

} // namespace graphs
