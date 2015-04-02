/*
 * @name	William Woodard
 * @date	Due 10-19-2014
 * @class	ITCS-2214-001
 * @HW		Project_3_Earthquake_Data
 */

package Queue;

import java.io.IOException;
import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.Random;
import java.util.Set;

import edu.uncc.cs.bridges.*;


public class EarthquakeSnapshots {
	public static final int maxElements = 20; //number of intial tweets and maxmimum queue size
	public static final int marginElements = 5; //number of tweets to add from Twitter
	public static final int loopTimes = 4; //number of times tweets are added from Twitter
	
	/**
	 * The populate method enQueues a specified number of Tweeter followers
	 * @param root is the first element of the queue
	 * @param queue the current queue
	 * @param max is the number of followers enqueued by this method
	 * @return
	 */
	public static Queue<EarthquakeTweet> populate(List<EarthquakeTweet> aList, Queue<EarthquakeTweet> queue) {
		if (aList.size()!=0){
			for(int i=0; i<aList.size();i++){
				// deQueue if the added element will make the queue surpass the max elements
				if (queue.length() >= maxElements) queue.deQueue();
				queue.enQueue(aList.get(i));					
			}
		}
		return queue;
	}
	
	public static void main(String[] args) throws IOException {
		outputLog aLog = new outputLog();
		Queue<EarthquakeTweet> eQueue = new Queue<>();
		
		Bridge.init(3, "1355347875827", eQueue, "wwoodar1");
		
		TwitterAccount name = new TwitterAccount("earthquake"); 
		
		// Initial twenty Twitter elements
		List<Tweet> TweetList = Bridge.getAssociations(name, maxElements); //Get initial twenty tweets
		List<EarthquakeTweet> EarthquakeTweetList = Bridge.convertTweet (TweetList); //Convert them to earthquake tweets
		populate(EarthquakeTweetList, eQueue); //Populate the queue with them
		System.out.println("The length of the initial queue: "+eQueue.length()); //Output length
		
		//Next five, four times
		for (int i = 0; i < loopTimes; i++) {
			TweetList = Bridge.next(TweetList, marginElements); //Get next five tweets
			EarthquakeTweetList = Bridge.convertTweet (TweetList); //Convert them to earthquake tweets
			populate(EarthquakeTweetList, eQueue); //Populate the queue with them
			System.out.println("The length of queue "+(i+1)+": "+eQueue.length()); //Output length
			Bridge.update(); //Update API
		}
		
		aLog.returnStream();
	}
}