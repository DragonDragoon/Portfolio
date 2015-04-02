/*package HelloWorld;

import java.io.IOException;
import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.Random;
import java.util.Set;

import edu.uncc.cs.bridges.*;

public class SimpleQueueDriver {
	public static final int maxElements = 10; //number of Followers from Twitter
	
	/**
	 * The populate method enQueues a specified number of Tweeter followers
	 * @param root is the first element of the queue
	 * @param queue the current queue
	 * @param max is the number of followers enqueued by this method
	 * @return
	 *//*
	public static LQueue<Follower> populate(Link<Follower> root, LQueue<Follower> queue, int max){
		if (max!=0){
			List<Follower>	temp= Bridge.getAssociations((Follower)root.element(), max);
			for(int i=0; i<temp.size();i++){
					queue.enQueue(temp.get(i));
			}
		}
		return queue;
	}
	
	
	public static void main(String[] args) throws IOException{
		outputLog aLog = new outputLog();
		LQueue<Follower> queue = new LQueue<Follower>();
		Bridge.init(0, "1355347875827", queue, "wwoodar1");
		
		//Adding elements to the queue
		Link<Follower> root = queue.enQueue(new Follower("Joey"));
		queue.enQueue(new Follower("Achusimjennifer"));
		
		//the queue is emptied
		//queue.clear();
				
		//queue.enQueue(new Follower("Bob"));//the first element of the queue
		//populate(queue.enQueue(new Follower("Achusimjennifer")), queue, maxElements);
		
		//This is how you can access the existing elements of the queue, just remove the comments from the 
		//statement below
		//System.out.println("The queue elements: "+queue.vertices);
		
		//queue.deQueue();
		//queue.deQueue();
		//queue.deQueue();
		//queue.enQueue(new Follower("John"));
		//One can iterate through the elements of the queue using next();
		//this method is inherited from graph
		//to test this remove the comment sign from the statement below
		//System.out.println(((QueueElement<Follower>)queue.getfront()).next().next().getIdentifier());
		
		//One element's properties can be changed
		//to test this remove the comment sign from the statement below
		//queue.getfront().setColor("purple");
		
		//This is another deQueue statement
		//queue.deQueue();
		//queue.deQueue();
		
		//One can find the size of the queue at any given moment
		//to test this remove the quotes
		//System.out.println(queue.length());
		
		System.out.print("\nJSON: ");
		Bridge.complete();
		aLog.returnStream();

	}

}*/