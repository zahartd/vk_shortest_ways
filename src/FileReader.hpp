#pragma once

#include <filesystem>

#include "Graph.hpp"

namespace graphs {

ShortestPathGraph readGraphFromPath(std::filesystem::path path,
                                    uint32_t &startVertex);

}
