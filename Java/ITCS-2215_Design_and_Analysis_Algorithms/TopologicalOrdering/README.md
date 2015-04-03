Simple imlementation of a custom graph, edges, and vertexes, and then implementing a topological ordering of data included in data.txt.

For example, let data.txt be:<br />
D,A,B<br />
A,B<br />
B,C<br />

This means that:<br />
D is connected to A<br />
D is connected to B<br />
A is connected to B<br />
B is connected to C

The output would be D,A,B,C. If a cycle is found, then the program will output that there is no topologial ordering.
