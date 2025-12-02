all: build

.Phony : build run_nodes_topo clean

build:
	g++ -o list_nodesandtopo src/main.cpp src/structs.cpp
	g++ -o auto_test_winding src/auto_test_winding.cpp src/structs.cpp src/utils.cpp
	g++ -o auto_test_intersection src/auto_test_intersection.cpp src/structs.cpp src/utils.cpp

run:
	echo nodesandotopo
	./list_nodesandtopo
	echo test_winding
	./auto_test_winding
	echo test_intersection
	./auto_test_intersection
	


clean: 
	rm list_nodesandtopo
	rm auto_test_winding
	rm auto_test_intersection