#include <cstdio>
#include <exception>
#include <iostream>
#include <ostream>
#include <print>

#include "FileReader.hpp"
#include "Graph.hpp"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::println(stderr, "Usage: {} <path_to_graph_file>", argv[0]);
    return 1;
  }

  std::filesystem::path path_to_graph = argv[1];
  std::uint32_t start_vertex = 0;
  graphs::ShortestPathGraph g;

  try {
    g = graphs::readGraphFromPath(path_to_graph, start_vertex);
  } catch (std::exception& err) {
    std::println(stderr, "Failde to read data from {}: {}", argv[1],
                 err.what());
    return 1;
  }

  auto distances = g.shortestDistsBFS(start_vertex);
  for (auto d : distances) {
    std::println("{}", d);
  }

  return 0;
}
