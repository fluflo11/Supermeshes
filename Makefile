CXX = g++
FLAGS = -o

# Inputs
FILES = src/structs.cpp src/utils.cpp
TEST_LIST_NODES_TOPOLOGY = src/main.cpp
TEST_WINDING = src/auto_test_winding.cpp
TEST_INTERSECTION = src/auto_test_intersection.cpp

# Outputs
LIST_NODES_TOPOLOGY = list_nodesandtopo
WINDING = auto_test_winding
INTERSECTION = auto_test_intersection

all: build

.Phony : build run_nodes_topo clean

build:
	$(CXX) $(FLAGS) $(LIST_NODES_TOPOLOGY) $(TEST_LIST_NODES_TOPOLOGY) $(FILES)
	$(CXX) $(FLAGS) $(WINDING) $(TEST_WINDING) $(FILES)
	$(CXX) $(FLAGS) $(INTERSECTION) $(TEST_INTERSECTION) $(FILES)

run:
	@echo nodesandotopo
	./$(LIST_NODES_TOPOLOGY)
	@echo test_winding
	./$(WINDING)
	@echo test_intersection
	./$(INTERSECTION)
	


clean: 
	rm $(LIST_NODES_TOPOLOGY)
	rm $(WINDING)
	rm $(INTERSECTION)