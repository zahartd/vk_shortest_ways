#pragma once

#include <string>

#include <Graph.hpp>

Graph readGraphFromFile(const std::string &filename, int &startVertex);
