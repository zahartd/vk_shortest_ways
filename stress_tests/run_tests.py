import os
import random
import subprocess
import networkx as nx
import tempfile
import shutil

EXECUTABLE = os.path.join('..', 'build_debug', 'vk_shortest_ways_app')
FAILED_DIR = 'failed'
RANDOM_SEED = 42

random.seed(RANDOM_SEED)

def write_graph_to_file(G, start_vertex, filename):
    with open(filename, 'w') as f:
        f.write(f"{len(G.nodes())}\n")
        f.write(f"{len(G.edges())}\n")
        for u, v in G.edges():
            f.write(f"{u} {v}\n")
        f.write(f"{start_vertex}\n")

def run_cpp_application(input_file):
    result = subprocess.run([EXECUTABLE, input_file], capture_output=True, text=True)
    return result.stdout.strip()

def parse_cpp_output(output):
    distances = {}
    for vertex, line in enumerate(output.split('\n')):
        line = line.strip()
        dist = int(line)
        if dist >= 0:
            distances[vertex] = dist
    return distances

def process_graph(graph_type, G, start_vertex, temp_dir):
    input_file = os.path.join(temp_dir, f"{graph_type}_graph_{len(G.nodes())}.txt")
    write_graph_to_file(G, start_vertex, input_file)
    cpp_output = run_cpp_application(input_file)
    actual_distances = parse_cpp_output(cpp_output)
    expected_distances = nx.single_source_shortest_path_length(G, start_vertex)
    if expected_distances == actual_distances:
        print(f"TEST {graph_type.capitalize()} graph: PASSED")
    else:
        print(f"TEST {graph_type.capitalize()} graph: FAILED")
        if not os.path.exists(FAILED_DIR):
            os.makedirs(FAILED_DIR)
        shutil.move(input_file, os.path.join(FAILED_DIR, os.path.basename(input_file)))

        actual_file = os.path.join(FAILED_DIR, f"{graph_type}_graph_{len(G.nodes())}_actual.txt")
        with open(actual_file, 'w') as f:
            for vertex in range(len(G.nodes())):
                f.write(f"{actual_distances.get(vertex, -1)}\n")

        expected_file = os.path.join(FAILED_DIR, f"{graph_type}_graph_{len(G.nodes())}_expected.txt")
        with open(expected_file, 'w') as f:
            for vertex in range(len(G.nodes())):
                f.write(f"{expected_distances.get(vertex, -1)}\n")


def main():
    temp_dir = tempfile.mkdtemp()

    try:
        sizes = [10, 100, 500, 1000, 2500]
        start_vertex = 0

        for size in sizes:
            print(f"TEST graphs with {size} vertices:")

            G_full = nx.complete_graph(size)
            process_graph('complete', G_full, start_vertex, temp_dir)

            G_sparse = nx.erdos_renyi_graph(size, 0.8, seed=RANDOM_SEED)
            process_graph('sparse_0.8', G_sparse, start_vertex, temp_dir)

            G_sparse = nx.erdos_renyi_graph(size, 0.5, seed=RANDOM_SEED)
            process_graph('sparse_0.5', G_sparse, start_vertex, temp_dir)

            G_sparse = nx.erdos_renyi_graph(size, 0.25, seed=RANDOM_SEED)
            process_graph('sparse_0.25', G_sparse, start_vertex, temp_dir)

            G_sparse = nx.erdos_renyi_graph(size, 0.1, seed=RANDOM_SEED)
            process_graph('sparse_0.1', G_sparse, start_vertex, temp_dir)

            G_sparse = nx.erdos_renyi_graph(size, 0.01, seed=RANDOM_SEED)
            process_graph('sparse_0.01', G_sparse, start_vertex, temp_dir)

            G_tree = nx.random_tree(size, seed=RANDOM_SEED)
            process_graph('tree', G_tree, start_vertex, temp_dir)

            G_star = nx.star_graph(size - 1)
            process_graph('star', G_star, start_vertex, temp_dir)

            G_wheel = nx.wheel_graph(size)
            process_graph('wheel', G_wheel, start_vertex, temp_dir)

    finally:
        shutil.rmtree(temp_dir)

if __name__ == "__main__":
    main()
