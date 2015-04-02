package p5Driver;

import edu.uncc.cs.bridges.*;

public class p5ExampleDriver {
	/**
	 * the driver
	 * @param args
	 */
	public static void main(String[] args) {
		GraphVisualizer<?> gv = new GraphVisualizer();
		Bridge.init(10, "1355347875827", gv, "wwoodar1");
		
		Vertex<String> anActor, aMovie, aMovie2, aMovie3;
		
		anActor = new Vertex<String> ("Kevin_Bacon_(I)", gv);
							// set attributes
			anActor.setColor("red");
			anActor.setOpacity(0.3);

		aMovie = new Vertex<String> ("A Few Good Men", gv);
		//Setting properties of the node
			aMovie.setColor("green");
			aMovie.setOpacity(0.9);
		aMovie2 = new Vertex<String> ("Mystic River", gv);
			aMovie2.setColor("green");
			aMovie2.setOpacity(0.9);
		aMovie3 = new Vertex<String> ("Apollo_13", gv);
			aMovie3.setColor("green");
			aMovie3.setOpacity(0.9);
		
								// create edges
		AbstractEdge edge;
		edge = anActor.createEdge(aMovie);
		//setting properties of the edge
			edge.setColor("red");
			edge.setOpacity(0.5);
		edge = aMovie.createEdge(anActor);
			edge.setColor("green");
			edge.setOpacity(0.5);
		
		edge = anActor.createEdge(aMovie2);
			edge.setColor("blue");
			edge.setOpacity(0.5);
		edge = aMovie2.createEdge(anActor);
			edge.setColor("green");
			edge.setOpacity(0.5);
			
		edge = anActor.createEdge(aMovie3);
			edge.setColor("red");
			edge.setOpacity(0.5);
		edge = aMovie3.createEdge(anActor);
			edge.setColor("green");
			edge.setOpacity(0.5);

				
		//getting neighbors by calling next() multiple times
		System.out.println("Kevin's first child: " + anActor.next().getIdentifier());
		System.out.println("Kevin's second child: " + anActor.next().getIdentifier());
		System.out.println("Kevin's third child: " + anActor.next().getIdentifier());

		
		
		//getting neighbor edges by calling nextEdge() multiple times			
		System.out.println("Kevin's second movie(edge color): " + anActor.nextEdge().getColor());
		System.out.println("Kevin's second movie(edge color): " + anActor.nextEdge().getColor());
		
		//getting a specific edge between to nodes
		System.out.println("Kevin's second movie(color): " + anActor.getEdge(aMovie).getColor());
		System.out.println("Kevin's second movie(color): " + aMovie.getEdge(anActor).getColor());
		
			
		anActor = new Vertex<String> ("Nicole Kidman", gv);
			anActor.setColor("red");
			anActor.setOpacity(0.3);
		aMovie = new Vertex<String> ("Eyes Wide Shut", gv);
			aMovie.setColor("green");
			aMovie.setOpacity(0.3);
		edge = anActor.createEdge(aMovie);
			edge.setColor("red");
			edge.setOpacity(0.3);
		edge = aMovie.createEdge(anActor);
			edge.setColor("green");
			edge.setOpacity(0.3);


		
		Bridge.complete();
	}

}