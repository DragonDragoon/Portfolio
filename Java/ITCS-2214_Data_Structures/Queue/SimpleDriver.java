package Queue;

import java.io.IOException;
import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.Random;
import java.util.Set;

import edu.uncc.cs.bridges.*;


public class SimpleDriver {
	public static final int maxElements = 10; //number of Followers from Twitter
	
		
	public static void main(String[] args) throws IOException{
		outputLog aLog = new outputLog();
		Queue<Follower> queue = new Queue<Follower>();
		Bridge.init(1, "1355347875827", queue, "wwoodar1");
		
		//Adding elements to the queue
		QueueElement<Follower> root = queue.enQueue(new Follower("Joey"));
		queue.enQueue(new Follower("Achusimjennifer"));
		
		//the queue is emptied
		//queue.clear();
				
	
		//This is how you can access the existing elements of the queue, just remove the comments from the 
		//statement below
		System.out.println("The queue elements: "+queue.vertices);
		
		
		queue.deQueue();
		queue.enQueue(new Follower("John"));
		
		
		//One element's properties can be changed
		//to test this remove the comment sign from the statement below
		queue.getfront().setColor("purple");
		
		
		//One can find the size of the queue at any given moment
		//to test this remove the quotes
		System.out.println(queue.length());
		
		System.out.print("\nJSON: ");
		Bridge.complete();
		aLog.returnStream();

	}

}