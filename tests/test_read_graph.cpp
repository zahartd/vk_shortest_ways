#include "gtest/gtest.h"

#include <filesystem>
#include <fstream>
#include <stdexcept>

#include "FileReader.hpp"
#include "Graph.hpp"

namespace fs = std::filesystem;

namespace graphs::tests {

class FileReaderTest : public ::testing::Test {
 protected:
  fs::path tempFile;

  void SetUp() override {
    tempFile = fs::temp_directory_path() / "test_graph.txt";
  }

  void TearDown() override {
    if (fs::exists(tempFile)) fs::remove(tempFile);
  }

  void WriteContent(const std::string& content) {
    std::ofstream ofs(tempFile);
    ofs << content;
  }
};

TEST_F(FileReaderTest, ValidGraph) {
  std::string content = R"(
  5
  4
  0 1
  0 4
  1 2
  1 3
  4
  )";
  WriteContent(content);

  uint32_t startVertex = 0;
  ShortestPathGraph graph;

  EXPECT_NO_THROW(graph = readGraphFromPath(tempFile, startVertex));
  EXPECT_EQ(startVertex, 4);
}

TEST_F(FileReaderTest, FileDoesNotExist) {
  fs::path nonExistent = fs::temp_directory_path() / "non_existent.txt";
  uint32_t startVertex = 0;
  EXPECT_THROW(
      { readGraphFromPath(nonExistent, startVertex); }, std::runtime_error);
}

TEST_F(FileReaderTest, InvalidVerticesEdgesFormat) {
  std::string content = "invalid\n";
  WriteContent(content);

  uint32_t startVertex = 0;
  EXPECT_THROW(
      { readGraphFromPath(tempFile, startVertex); }, std::runtime_error);
}

TEST_F(FileReaderTest, InvalidEdgeFormat) {
  std::string content = R"(
  5
  4
  0 1
  0
  1 3
  4
  )";
  WriteContent(content);

  uint32_t startVertex = 0;
  EXPECT_THROW(
      { readGraphFromPath(tempFile, startVertex); }, std::runtime_error);
}

TEST_F(FileReaderTest, InvalidStartVertexFormat) {
  std::string content = R"(
  5
  4
  0 1
  0 4
  1 2
  1 3
  )";
  WriteContent(content);

  uint32_t startVertex = 0;
  EXPECT_THROW(
      { readGraphFromPath(tempFile, startVertex); }, std::runtime_error);
}

}  // namespace graphs::tests
