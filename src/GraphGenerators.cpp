#include "GraphGenerators.hpp"

namespace graphs {

std::mt19937 rng(SEED);

ShortestPathGraph generateGraph(std::size_t num_vertices, double edge_prob) {
  ShortestPathGraph graph(num_vertices);
  std::uniform_real_distribution<double> dist(0.0, 1.0);

  for (std::uint32_t u = 0; u < num_vertices; ++u) {
    for (std::uint32_t v = u + 1; v < num_vertices; ++v) {
      if (dist(rng) < edge_prob) {
        graph.addEdge(u, v);
      }
    }
  }

  return graph;
}

}  // namespace graphs
