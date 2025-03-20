#include "gtest/gtest.h"

#include "Graph.hpp"
#include "GraphGenerators.hpp"

namespace graphs::tests {

namespace {

constexpr double kSparseCoeff = 0.05;

}  // namespace

TEST(GraphTest, AddEdgeValid) {
  UndirectedGraph graph(5);

  EXPECT_NO_THROW(graph.addEdge(0, 1));
  EXPECT_NO_THROW(graph.addEdge(0, 4));
  EXPECT_NO_THROW(graph.addEdge(1, 2));
  EXPECT_NO_THROW(graph.addEdge(1, 3));
}

TEST(GraphTest, AddEdgeInvalid) {
  UndirectedGraph graph(3);

  EXPECT_THROW(graph.addEdge(0, 3), std::out_of_range);
  EXPECT_THROW(graph.addEdge(3, 1), std::out_of_range);
  EXPECT_THROW(graph.addEdge(5, 5), std::out_of_range);
}

TEST(GraphTest, ShortestDistsSimple) {
  ShortestPathGraph spg(5);
  spg.addEdge(0, 1);
  spg.addEdge(0, 4);
  spg.addEdge(1, 2);
  spg.addEdge(1, 3);

  std::vector<std::vector<std::int64_t>> expected = {{0, 1, 2, 2, 1},
                                                     {1, 0, 1, 1, 2},
                                                     {2, 1, 0, 2, 3},
                                                     {2, 1, 2, 0, 3},
                                                     {1, 2, 3, 3, 0}};
  {
    for (std::uint32_t start = 0; start < expected.size(); ++start) {
      auto distances = spg.shortestDistsBFS(start);
      EXPECT_EQ(distances, expected[start])
          << "BFS failed for start vertex " << start;
    }
  }

  {
    for (std::uint32_t start = 0; start < expected.size(); ++start) {
      auto distances = spg.shortestDistsDijkstraForComplete(start);
      EXPECT_EQ(distances, expected[start])
          << "Dijkstra for complete graphs failed for start vertex " << start;
    }
  }

  {
    for (std::uint32_t start = 0; start < expected.size(); ++start) {
      auto distances = spg.shortestDistsDijkstraForSparse(start);
      EXPECT_EQ(distances, expected[start])
          << "Dijkstra for sparse graphs failed for start vertex " << start;
    }
  }

  {
    for (std::uint32_t start = 0; start < expected.size(); ++start) {
      auto distances = spg.shortestDistsFloyd(start);
      EXPECT_EQ(distances, expected[start])
          << "Floyd-Warshall failed for start vertex " << start;
    }
  }

  {
    for (std::uint32_t start = 0; start < expected.size(); ++start) {
      auto distances = spg.shortestDistsFloydParallel(start);
      EXPECT_EQ(distances, expected[start])
          << "Floyd-Warshall Parallel failed for start vertex " << start;
    }
  }
}

TEST(GraphTest, ShortestDistsComplete) {
  std::vector<std::size_t> test_sizes = {10, 50, 100, 250};

  for (auto size : test_sizes) {
    SCOPED_TRACE(testing::Message() << "Testing graphs of size " << size);

    auto g = generateGraph(size);

    for (std::uint32_t start_vertex = 0; start_vertex < size;
         start_vertex += size / 10) {
      auto distances_BFS = g.shortestDistsBFS(start_vertex);
      auto distances_DijkstraComplete =
          g.shortestDistsDijkstraForComplete(start_vertex);
      auto distances_DijkstraSparse =
          g.shortestDistsDijkstraForSparse(start_vertex);
      auto distances_Floyd = g.shortestDistsFloyd(start_vertex);
      auto distances_FloydParallel = g.shortestDistsFloydParallel(start_vertex);

      EXPECT_EQ(distances_BFS, distances_DijkstraComplete)
          << "Complete: Dijkstra (Complete) failed";
      EXPECT_EQ(distances_BFS, distances_DijkstraSparse)
          << "Complete: Dijkstra (Sparse) failed";
      EXPECT_EQ(distances_BFS, distances_Floyd)
          << "distances_BFS: Floyd-Warshall failed";
      EXPECT_EQ(distances_BFS, distances_FloydParallel)
          << "distances_BFS: Floyd-Warshall Parallel failed";
    }
  }
}

TEST(GraphTest, ShortestDistsSparse) {
  std::vector<std::size_t> test_sizes = {10, 50, 100, 250};

  for (auto size : test_sizes) {
    SCOPED_TRACE(testing::Message() << "Testing graphs of size " << size);

    auto g = generateGraph(size, kSparseCoeff);

    for (std::uint32_t start_vertex = 0; start_vertex < size;
         start_vertex += size / 10) {
      auto distances_BFS = g.shortestDistsBFS(start_vertex);
      auto distances_DijkstraComplete =
          g.shortestDistsDijkstraForComplete(start_vertex);
      auto distances_DijkstraSparse =
          g.shortestDistsDijkstraForSparse(start_vertex);
      auto distances_Floyd = g.shortestDistsFloyd(start_vertex);
      auto distances_FloydParallel = g.shortestDistsFloydParallel(start_vertex);

      EXPECT_EQ(distances_BFS, distances_DijkstraComplete)
          << "Complete: Dijkstra (Complete) failed";
      EXPECT_EQ(distances_BFS, distances_DijkstraSparse)
          << "Complete: Dijkstra (Sparse) failed";
      EXPECT_EQ(distances_BFS, distances_Floyd)
          << "distances_BFS: Floyd-Warshall failed";
      EXPECT_EQ(distances_BFS, distances_FloydParallel)
          << "distances_BFS: Floyd-Warshall Parallel failed";
    }
  }
}

}  // namespace graphs::tests
