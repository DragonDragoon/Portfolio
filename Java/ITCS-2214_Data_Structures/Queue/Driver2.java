package Queue;

import java.io.IOException;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

import edu.uncc.cs.bridges.*;


public class Driver2 {
	public static final int maxElements = 10; //number of tweets
	
	/**
	 * The populate method enQueues a specified number of Tweeter followers
	 * @param queue the current queue
	 * @param aList is the list of tweets
	 * @return nothing
	 * @throws BridgesException 
	 */
	public static void populate(List<EarthquakeTweet> aList, Queue<EarthquakeTweet> queue){
		//queue.clear();
	
		for(int i=0; i<aList.size();i++){
			queue.enQueue(aList.get(i));
					
					// The last part of the assignment will require to set the size of 
					// the node based on the magnitude of the earthquake

					// object size range is 0-50; the actual value is adjusted for a better visualization
					// Generates a random number between 0 and 50
			double size = Math.random()*50;
					
			queue.getfront().setSize(size);		
		}
		return ;
	}
	
	public static void main(String[] args) throws IOException {
		//create a log for all outputs with or without errors in user's home directory
		outputLog aLog = new outputLog();
		
		//create a queue of Earthquake tweets
		Queue<EarthquakeTweet> aQueue = new Queue<>();
		
		// Assignment, API key, visualizer, username
		Bridge.init(2, "1355347875827", aQueue, "wwoodar1");

		// Any actual user on Twitter; in this case we use the earthquake account
		TwitterAccount name = new TwitterAccount("earthquake"); 
		
		//retrieve a list of maxElements tweets 
		List<Tweet> TweetList = Bridge.getAssociations(name, maxElements);
		
		//and convert them to EarthquakeTweets 
		//EarthquakeTweet is a special tweet containing also the magnitude field
		List<EarthquakeTweet> EarthquakeTweetList = Bridge.convertTweet (TweetList);
		
		//add one tweet (the latest tweet) to the queue
		//if there is an identical element in the queue the element will not be added
		aQueue.enQueue(EarthquakeTweetList.get(0));
		
		//populate the queue with maxElements tweets from @earthquake
		populate(EarthquakeTweetList, aQueue);
		
		//dequeue one element
		aQueue.deQueue();
		
		//get a snapshot of the queue, creates a visualization
		Bridge.update();
		
		//get another batch of 3 tweets to the queue
		List<Tweet> aSecondTweetList = new ArrayList<>();
		Bridge.next(aSecondTweetList, 3);
		
		List<EarthquakeTweet> EarthquakeSecondTweetList = Bridge.convertTweet (aSecondTweetList);
		
		//add the new batch to the queue
		populate(EarthquakeSecondTweetList, aQueue);
		
		// finish, calls update to create the final visualization
		Bridge.complete();
		
		aLog.returnStream();
	}

}