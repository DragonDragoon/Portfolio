/**
 * @author William Woodard
 * @date   11/2/2014
 * @HW     Project 4 MaxHeap
 * @name   Twitter.java
 */
package Heap_ADT;

import java.lang.Comparable;

/** Custom Generic data type for HeapDrive.java implementation */
public class Twitter implements Comparable<Twitter> {
	private String name;   // Name of twitter
	private int followers; // Number of followers
	private int follows;   // Number of people the twitter follows
	private int tweets;    // Number of tweets made by twitter
	
	/** Constructor for Twitter object */
	public Twitter(String n, int fs, int f, int t) {
		// Initialize values
		name = n;
		followers = fs;
		follows = f;
		tweets = t;
	}
	
	/** Compare two twitters, using number of followers for identity */
	public int compareTo(Twitter T) {
		if (this.followers > T.followers) // If there are more followers in this twitter than being compared to
			return 1;
		else if (this.followers == T.followers) // If there are equal followers in this twitter and other
			return 0;
		else                              // Else there are less followers in this twitter compared to other
			return -1;
	}
	
	/** Return formatted string of object values */
	public String toString() {
		return String.format("%-18s %-10s %-10s %-10s", name, followers, follows, tweets);
	}
	
	/** Getter: Name value */
	public String getName() {
		return name;
	}
	
	/** Getter: Followers value */
	public int getFollowers() {
		return followers;
	}
	
	/** Getter: Follows value */
	public int getFollows() {
		return follows;
	}
	
	/** Getter: Tweets value */
	public int getTweets() {
		return tweets;
	}
	
	/** Setter: Name value */
	public void setName(String n) {
		name = n;
	}
	
	/** Setter: Followers value */
	public void setFollowers(int fs) {
		followers = fs;
	}
	
	/** Setter: Follows value */
	public void setFollows(int f) {
		follows = f;
	}
	
	/** Setter: Tweets value */
	public void setTweets(int t) {
		tweets = t;
	}
}
