#pragma once

#include <filesystem>

#include "Graph.hpp"

namespace graphs {

ShortestPathGraph readGraphFromPath(const std::filesystem::path& path,
                                    uint32_t& start_vertex);

}  // namespace graphs
