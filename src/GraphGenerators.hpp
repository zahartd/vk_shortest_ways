#pragma once

#include <random>

#include "Graph.hpp"

namespace graphs {

constexpr int SEED = 42;
extern std::mt19937 rng;

ShortestPathGraph generateGraph(std::size_t num_vertices,
                                double edge_prob = 1.0);

}  // namespace graphs
