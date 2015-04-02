/**
 * @author William Woodard
 * @date   3/28/2015
 * @HW     Topological Ordering Implementation
 * @name   Edge.java
 * @desc   This file contains the data structure for implementing edges in the graph structure
 */
package TopologicalOrdering;

/**
 * 
 * @author William
 *
 * @param <Vertex>
 * @desc  Simple implementation of an edge for the assignment; should be self-explanatory
 */
@SuppressWarnings("hiding")  //Clean the code slightly...
public class Edge<Vertex> {
	private Vertex parent;
	private Vertex child;
	
	public Edge(Vertex v, Vertex n) {
		parent = v;
		child = n;
	}
	
	public Vertex getParent() {
		return parent;
	}
	
	public Vertex getChild() {
		return child;
	}
	
	@Override
	public String toString() {
		return "Edge: " + parent + "->" + child;
	}
}
