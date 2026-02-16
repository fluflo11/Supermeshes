CXX = g++
FLAGS = -o

# Inputs
FILES = src/structs.cpp src/utils.cpp src/VTK_Tools.cpp
MAIN = src/main.cpp
TEST_WINDING = src/auto_test_winding.cpp
TEST_INTERSECTION = src/auto_test_intersection.cpp

# Outputs
EXEC = supermesh
WINDING = auto_test_winding
INTERSECTION = auto_test_intersection

# Files paths

INPUT_NODES_A = resources/meshes_for_FR/unitsqmeshes/unitsqmesh_hexreg_000094_midedge/input_nodes.dat 
INPUT_NODES_B = resources/meshes_for_FR/unitsqmeshes/unitsqmesh_hexreg_000449_flipped_nobd/input_nodes.dat
INPUT_TOPO_A = resources/meshes_for_FR/unitsqmeshes/unitsqmesh_hexreg_000094_midedge/input_topo.dat
INPUT_TOPO_B = resources/meshes_for_FR/unitsqmeshes/unitsqmesh_hexreg_000449_flipped_nobd/input_topo.dat

all: build

.Phony : build run clean

build:
	$(CXX) $(FLAGS) $(EXEC) $(MAIN) $(FILES)

build_tests:
	$(CXX) $(FLAGS) $(WINDING) $(TEST_WINDING) $(FILES)
	$(CXX) $(FLAGS) $(INTERSECTION) $(TEST_INTERSECTION) $(FILES)

run:
	@echo Running supermesh
	./$(EXEC) $(INPUT_NODES_A) $(INPUT_TOPO_A) $(INPUT_NODES_B) $(INPUT_TOPO_B) -d

run_tests:
	@echo test_winding
	./$(WINDING)
	@echo test_intersection
	./$(INTERSECTION)

#Maybe can check which file exists here before deleting
clean:
	rm $(EXEC)
	rm $(WINDING)
	rm $(INTERSECTION)