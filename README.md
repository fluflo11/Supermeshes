# *Supermeshes*
## Parsing 
### Nodes

Node parser is directly implemented as a static function of the Point2D class.
### Topology
Topology is also implemented as a static function of the Topology class, but it returns a vector and not a Topology. 
Example : 
```cpp
std::vector<Cell> my_cells = Topology::getInputTopology(input_file);
Topology my_topology(my_cells);
my_topology.printTopology();
```
## Author
[Florentin Royer](https://github.com/fluflo11)

![](thinking-cat.gif)
