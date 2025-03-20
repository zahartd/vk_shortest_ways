#pragma once

#include <filesystem>

#include "Graph.hpp"

namespace graphs {

ShortestPathGraph readGraphFromPath(const std::filesystem::path& path,
                                    uint32_t& startVertex);

}  // namespace graphs
