PROJECT_NAME = vk_shortest_ways
NPROCS ?= $(shell nproc)
BUILD_DIR = build_debug
CMAKE_OPTS = -DCMAKE_BUILD_TYPE=Debug ..
INPUT_FILE ?= $(CURDIR)/examples/simple_graph.txt

.PHONY: build run test stress-test bench clean

build:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake $(CMAKE_OPTS)
	cd $(BUILD_DIR) && cmake --build . -j $(NPROCS)

run: build
	cd $(BUILD_DIR) && ./$(PROJECT_NAME) $(INPUT_FILE)

test: build
	cd $(BUILD_DIR) && ctest --output-on-failure

stress-test: build
	python3 stress_tests/run_tests.py $(BUILD_DIR)/$(PROJECT_NAME)

bench: build
	cd $(BUILD_DIR) && ./benchmarks/$(PROJECT_NAME)_benchmarks

clean:
	rm -rf $(BUILD_DIR)
