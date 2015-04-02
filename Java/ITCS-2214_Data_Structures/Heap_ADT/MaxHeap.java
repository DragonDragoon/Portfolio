/**
 * @author William Woodard
 * @date   11/2/2014
 * @HW     Project 4 MaxHeap
 * @name   MaxHeap.java
 */
package Heap_ADT;

/** Source code example for "A Practical Introduction to Data
 *  Structures and Algorithm Analysis, 3rd Edition (Java)" 
 *  by Clifford A. Shaffer
 *  Copyright 2008-2011 by Clifford A. Shaffer
 *  
 *  Edited by William Woodard
 */

import java.lang.Comparable;

/** Max-heap implementation */
public class MaxHeap<E extends Comparable<? super E>> {
	private E[] Heap;   // Pointer to the heap array
	private int size;   // Maximum size of the heap
	private int n;      // Number of things in heap
	private int removes = 0;      // Number of remove operations
	private int swapRemoves = 0;  // Number of swap operations in each remove operation
	private int inserts = 0;      // Number of insert operations
	private int swapInserts = 0;  // Number of swap operations in each insert operation
	
	/** Constructor supporting preloading of heap contents */
	public MaxHeap(E[] h, int num, int max) {
		Heap = h; 
		n = num; 
		size = max; 
		buildheap();
	}
	
	/** @return Current size of the heap */
	public int heapsize() {
		return n;
	}
	
	/** @return True if pos a leaf position, false otherwise */
	public boolean isLeaf(int pos) {
		return (pos >= n/2) && (pos < n); 
	}
	
	/** @return Position for left child of pos */
	public int leftchild(int pos) {
		assert pos < n/2 : "Position has no left child";
		return 2*pos + 1;
	}
	
	/** @return Position for right child of pos */
	public int rightchild(int pos) {
		assert pos < (n-1)/2 : "Position has no right child";
		return 2*pos + 2;
	}
	
	/** @return Position for parent */
	public int parent(int pos) {
		assert pos > 0 : "Position has no parent";
		return (pos-1)/2;
	}
	
	/** Insert val into heap */
	public void insert(E val) {
		assert n < size : "Heap is full";
		int curr = n++;               // Add to size and assign pointer
		Heap[curr] = val;             // Start at end of heap
		// Now sift up until curr's parent's key > curr's key
		while ((curr != 0)  && (Heap[curr].compareTo(Heap[parent(curr)]) > 0)) {
			this.swap(Heap, curr, parent(curr), "Insert");  // Swap current node and parent node for insert operation
			curr = parent(curr);  // Set current node to swapped parent
		}
		inserts++;  // Increment inserts
	}
	
	/** Heapify contents of Heap */
	public void buildheap() {
		for (int i=n/2-1; i>=0; i--)
			siftdown(i);
	}
	
	/** Put element in its correct place */
	private void siftdown(int pos) {
		assert (pos >= 0) && (pos < n) : "Illegal heap position";
		while (!isLeaf(pos)) {
			int j = leftchild(pos);
			if ((j<(n-1)) && (Heap[j].compareTo(Heap[j+1]) < 0)) 
			  j++; // j is now index of child with greater value
			if (Heap[pos].compareTo(Heap[j]) >= 0)
				return;
			this.swap(Heap, pos, j);
			pos = j;  // Move down
		}
	}
	
	/** Remove and return maximum value */
	public E removemax() {
		assert n > 0 : "Removing from empty heap";
		this.swap(Heap, 0, --n, "Remove"); // Swap maximum with last value
		if (n != 0)      // Not on last element
			siftdown(0);   // Put new heap root val in correct place
		removes++;
		return Heap[n];  // Return node removed
	}
	
	/** Remove and return element at specified position */
	public E remove(int pos) {
		assert (pos >= 0) && (pos < n) : "Illegal heap position";
		if (pos == (n-1)) {
			n--; // Last element, no work to be done
		} else {
			this.swap(Heap, pos, --n, "Remove"); // Swap with last value
			// If we just swapped in a big value, push it up
			while ((pos > 0) && (Heap[pos].compareTo(Heap[parent(pos)]) > 0)) {
			  this.swap(Heap, pos, parent(pos), "Remove");  // Swap current node and parent node for remove operation
			  pos = parent(pos);  // New position at parent node
			}
			if (n != 0) {
				siftdown(pos); // If it is little, push down
			}
		}
		removes++;  // Increment removes
		return Heap[n];  // Return node removed
	}
	
	/** Swap elements and record for insertion or deletion */
	public void swap(E[] A, int p1, int p2, String type) {
		E temp = A[p1];  // Assign temporary node
		A[p1] = A[p2];   // Copy p1 to p2 "swap"
		A[p2] = temp;    // Assign p2 p1's (temporary) node
		
		if (type.equals("Insert")) { // If insert type
			swapInserts++;  // Increment insert swaps
		} else if (type.equals("Remove")) { // Else if remove type
			swapRemoves++;  // Increment remove swaps
		}
	}
	
	/** Swap array implementation elements in heap */
	public void swap(E[] A, int p1, int p2) {
		E temp = A[p1];  // Assign temporary node
		A[p1] = A[p2];   // Copy p1 to p2 "swap"
		A[p2] = temp;    // Assign p2 p1's (temporary) node
		// Method for no insert or removal type given
	}
	
	/** Calculate the average swaps made during insert operations */
	public double calcAvgSwapsInsert() {
		if (inserts == 0) {  // If there were no insert operations
			return 0;          // Then there were no swaps
		}
		return swapInserts / ((double) inserts); // Average swaps
	}
	
	/** Calculate the average swaps made during remove operations */
	public double calcAvgSwapsRemove() {
		if (removes == 0) {  // If there were no remove operations
			return 0;          // Then there were no swaps
		}
		return swapRemoves / ((double) removes); // Average swaps
	}
}