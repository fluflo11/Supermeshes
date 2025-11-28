all: build

.Phony : build run_nodes_topo clean

build:
	g++ -o list_nodesandtopo src/main.cpp src/structs.cpp
	g++ -o auto_test src/auto_test.cpp src/structs.cpp src/utils.cpp

run_nodes_topo: 
	./list_nodesandtopo

run_winding:
	./auto_test


clean: 
	rm list_nodes
	rm auto_test