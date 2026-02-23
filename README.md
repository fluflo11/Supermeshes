# *Supermeshes*

## Getting Started

You can compile it with the makefile : 
```
make
```
Or simply 
```
g++ -o supermesh src/main.cpp src/structs.cpp src/utils.cpp src/VTK_Tools.cpp
```
You can also compile the program as a shared library with
```
make build_shared
```
Its supported on windows & linux and there shouldnt be too much bugs. Ill add the API documentation "soon". 
Then you can run the program with :
```
make run
```
or 
```
./supermesh {path_input_nodes_A} {path_input_topo_A} {path_input_nodes_B} {path_input_topo_B}  [output_path] [-d]
```
if you are on linux, or 
```
.\supermesh {path_input_nodes_A} {path_input_topo_A} {path_input_nodes_B} {path_input_topo_B} [output_path] [-d]
```
On windows.

## Incoming features
- Adding a "union" supermesh option
- Creating a wrapper to use it in Python

## Parsing 
### Nodes
Node parser is directly implemented as a static function of the Point2D class.
### Topology
Topology parser is also implemented as a static function of the Topology class. It directly creates a Topology object. Use : 
```cpp
Topology my_topology = Topology::getInputTopology(input_file);
my_topology.printTopology();
```

### Visualisation 

You can export meshes to vtk format (you can then use Paraview to visualize it).
```cpp
VTK::VTK_Exporter my_exporter(my_topology,my_vector);
std::string output_file = "resources/VTK/mesh.vtk";
```

## Computations
### Utils

*utils.hpp* creates a new namespace called utils, introducing a lot of toolbox functions, and the most important one (for now): *winding(point,polygon)*.
I went through a lot of documentation to find the algorithm I wanted to use, I dont know if im right but the one I used seems robust enough for the task.


## Author
[Florentin Royer](https://github.com/fluflo11)

## Sources 

* https://alienryderflex.com/polygon/
* *Numerical Recipes Third Edition* by Saul Teukolsky
* https://www.cnblogs.com/chriscai/archive/2009/12/10/1620932.html

![](thinking-cat.gif)





