CXX = g++

ifeq ($(OS),Windows_NT)
    EXT = .exe
	SHARED_EXT = .dll
    RM = rm -f
	RUN_PREFIX = .
else
    EXT = 
	SHARED_EXT = .so
    RM = rm -f
    RUN_PREFIX = ./
endif

EXEC_NAME = supermesh
WINDING_NAME = auto_test_winding
INTERSECTION_NAME = auto_test_intersection

EXEC = $(EXEC_NAME)$(EXT)
SHARED_LIB = $(EXEC_NAME)$(SHARED_EXT)
WINDING = $(WINDING_NAME)$(EXT)
INTERSECTION = $(INTERSECTION_NAME)$(EXT)

FLAGS = -o
SHARED_FLAGS = -shared -fPIC -o

# Inputs
FILES = src/structs.cpp src/utils.cpp src/VTK_Tools.cpp
MAIN = src/main.cpp
TEST_WINDING = src/auto_test_winding.cpp
TEST_INTERSECTION = src/auto_test_intersection.cpp

# Outputs / Paths
OUTPUT_DIR = resources/VTK/
OUTPUT_FILE = result.vtk

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

build_shared :
	$(CXX) $(SHARED_FLAGS) $(SHARED_LIB) $(FILES)

run:
	$(RUN_PREFIX)/$(EXEC) $(INPUT_NODES_A) $(INPUT_TOPO_A) $(INPUT_NODES_B) $(INPUT_TOPO_B)

run_debug:
	$(RUN_PREFIX)/$(EXEC) $(INPUT_NODES_A) $(INPUT_TOPO_A) $(INPUT_NODES_B) $(INPUT_TOPO_B) -d

run_custom_path:
	$(RUN_PREFIX)/$(EXEC) $(INPUT_NODES_A) $(INPUT_TOPO_A) $(INPUT_NODES_B) $(INPUT_TOPO_B) $(OUTPUT_DIR)$(OUTPUT_FILE)

run_all:
	$(RUN_PREFIX)/$(EXEC) $(INPUT_NODES_A) $(INPUT_TOPO_A) $(INPUT_NODES_B) $(INPUT_TOPO_B) $(OUTPUT_DIR)$(OUTPUT_FILE) -d

run_tests:
	@echo test_winding
	$(RUN_PREFIX)/$(WINDING)
	@echo test_intersection
	$(RUN_PREFIX)/$(INTERSECTION)

clean:
	$(RM) $(EXEC) $(WINDING) $(INTERSECTION) $(SHARED_LIB)