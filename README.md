# *Supermeshes*

## Getting Started



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


