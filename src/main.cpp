#include <exception>
#include <iostream>
#include <ostream>

#include "FileReader.hpp"
#include "Graph.hpp"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <path_to_graph_file>" << std::endl;
    return 1;
  }

  std::filesystem::path path_to_graph = argv[1];
  std::uint32_t start_vertex = 0;

  try {
    auto g = graphs::readGraphFromPath(path_to_graph, start_vertex);
    auto distances = g.shortestDists(start_vertex);
    for (auto d : distances) {
      std::cout << d << std::endl;
    }
  } catch (std::exception &err) {
    std::cerr << err.what();
    return 1;
  }

  return 0;
}
