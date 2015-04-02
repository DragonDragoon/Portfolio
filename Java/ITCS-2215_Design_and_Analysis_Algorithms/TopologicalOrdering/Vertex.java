/**
 * @author William Woodard
 * @date   3/28/2015
 * @HW     Topological Ordering Implementation
 * @name   Vertex.java
 * @desc   This file contains the data structure for implementing vertexes in the graph structure
 */
package TopologicalOrdering;

/**
 * 
 * @author William
 *
 * @param <V> : V is some general object
 * @desc  Simple implementation of a vertex for the assignment; self-explanatory
 */
public class Vertex<V> {
	private V value;
	
	public Vertex(V v) {
		value = v;
	}
	
	public void setValue(V v) {
		value = v;
	}
	
	public V getValue() {
		return value;
	}
	
	@Override
	public String toString() {
		return value.toString();
	}
}
