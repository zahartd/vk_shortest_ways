#include "FileReader.hpp"

#include <filesystem>
#include <format>
#include <fstream>
#include <stdexcept>

#include "Graph.hpp"

namespace graphs {

ShortestPathGraph readGraphFromPath(const std::filesystem::path& path,
                                    uint32_t& start_vertex) {
  if (!std::filesystem::exists(path)) {
    throw std::runtime_error{
        std::format("File {} doesn't exist", path.string())};
  }

  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::runtime_error{
        std::format("Failed to open file: {}", path.string())};
  }

  std::size_t vertices_count, edges_count;
  if (!(file >> vertices_count >> edges_count)) {
    throw std::runtime_error{
        "Invalid file format: cannot read vertices or edges count"};
  }

  ShortestPathGraph graph(vertices_count);

  for (std::size_t i = 0; i < edges_count; ++i) {
    std::uint32_t from, to;
    if (!(file >> from >> to)) {
      throw std::runtime_error{
          std::format("Invalid file format: error reading edge {}", i)};
    }
    graph.addEdge(from, to);
  }

  if (!(file >> start_vertex)) {
    throw std::runtime_error{"Invalid file format: cannot read start vertex"};
  }

  return graph;
}

}  // namespace graphs
