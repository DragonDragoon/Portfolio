/*
 * @name	William Woodard
 * @date	Due 10-19-2014
 * @class	ITCS-2214-001
 * @HW		Project_3_Filter_Quake_Data
 */

package Queue;

import java.io.IOException;
import java.util.List;

import edu.uncc.cs.bridges.Bridge;
import edu.uncc.cs.bridges.EarthquakeTweet;
import edu.uncc.cs.bridges.Queue;
import edu.uncc.cs.bridges.Tweet;
import edu.uncc.cs.bridges.TwitterAccount;
import edu.uncc.cs.bridges.outputLog;

public class FilterQuake {
	public static final int maxElements = 50; //number of intial tweets and maxmimum queue size
	
	/**
	 * The populate method enQueues a specified number of Tweeter followers
	 * @param root is the first element of the queue
	 * @param queue the current queue
	 * @param max is the number of followers enqueued by this method
	 * @return
	 */
	public static Queue<EarthquakeTweet> populate(List<EarthquakeTweet> aList, Queue<EarthquakeTweet> queue, double minScale, double maxScale) {
		double mag;
		if (aList.size()!=0){
			for(int i=0; i<aList.size();i++){
				mag = aList.get(i).getMagnitude();
				if (mag >= minScale && mag <= maxScale) {
					// deQueue if the added element will make the queue surpass the max elements
					//if (queue.length() >= maxElements) queue.deQueue();
					queue.enQueue(aList.get(i));
					//Set size of magnitude (mapped to an expansion for ease of view)
					queue.getfront().setSize((aList.get(i).getMagnitude() - minScale) / (maxScale - minScale) * 40 + 10);
				}
			}
		}
		return queue;
	}
	
	public static Queue<EarthquakeTweet> fill(Queue<EarthquakeTweet> eQueue, double minScale, double maxScale) {
		TwitterAccount name = new TwitterAccount("earthquake"); 
		
		// Initial twenty Twitter elements
		List<Tweet> TweetList = Bridge.getAssociations(name, maxElements); //Get initial twenty tweets
		List<EarthquakeTweet> EarthquakeTweetList = Bridge.convertTweet (TweetList); //Convert them to earthquake tweets
		populate(EarthquakeTweetList, eQueue, minScale, maxScale); //Populate the queue with them
		
		/** (We did not have to fill up the queue, did we?)
		//Fill up rest of queue
		while (eQueue.length() < maxElements) {
			TweetList = Bridge.next(TweetList, maxElements - eQueue.length()); //Get unfilled slots
			EarthquakeTweetList = Bridge.convertTweet (TweetList); //Convert them to earthquake tweets
			populate(EarthquakeTweetList, eQueue, minScale, maxScale); //Populate the queue with them
		}
		*/
		
		return eQueue;
	}
	
	public static void main(String[] args) throws IOException {
		outputLog aLog = new outputLog();
		Queue<EarthquakeTweet> eQueue = new Queue<>();
		
		Bridge.init(9, "1355347875827", eQueue, "wwoodar1");
		
		eQueue = fill(eQueue, 5.0, 6.0);
		System.out.println("The length of queue (5-6): "+eQueue.length()); //Output length
		Bridge.update(); //Update API
		eQueue.clear(); //Clear queue
		eQueue = fill(eQueue, 6.0, 7.0);
		System.out.println("The length of queue (6-7): "+eQueue.length()); //Output length
		Bridge.update(); //Update API
		eQueue.clear(); //Clear queue
		eQueue = fill(eQueue, 7.0, 8.0);
		System.out.println("The length of queue (7-8): "+eQueue.length()); //Output length
		Bridge.update(); //Update API
		
		aLog.returnStream();
	}
}