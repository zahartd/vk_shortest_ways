#include "gtest/gtest.h"

#include "Graph.hpp"

namespace graphs::tests {

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
  for (std::uint32_t start = 0; start < expected.size(); ++start) {
    auto distances = spg.shortestDists(start);
    EXPECT_EQ(distances, expected[start])
        << "BFS failed for start vertex " << start;
  }
}

}  // namespace graphs::tests
