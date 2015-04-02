/** Linked list implementation */
class LList<E> implements List<E> {
	private Link<E> head; // Pointer to list header
	private Link<E> tail; // Pointer to last element
	protected Link<E> curr; // Access to current element
	private int cnt; // Size of list
	
	/** Constructors */
	LList(int size) { this(); } // Constructor -- Ignore size
	LList() {
		curr = tail = head = new Link<E>(null); // Create header
		cnt = 0;
	}
	
	/** Remove all elements */
	public void clear() {
		head.setNext(null); // Drop access to links
		curr = tail = head = new Link<E>(null); // Create header
		cnt = 0;
	}
	
	/** Insert "it" at current position */
	public void insert(E it) {
		curr.setNext(Link.get(it, curr.next())); // Get link
		if (tail == curr) tail = curr.next(); // New tail
		cnt++;
		curr = curr.next(); // Make current new node
	}
	
	/** Append "it" to list */
	public void append(E it) {
		tail = tail.setNext(Link.get(it, null));
		cnt++;
	}
	
	/** Remove and return current element */
	public E remove() {
		if (curr == tail) { // If current is tail
			E it = curr.element(); // Remember value
			curr.release(); // Release current link
			cnt--; // Decrement count
			return it; // Return removed
		} else { // Else current is not tail
			E it = curr.next().element(); // Remember value
			if (tail == curr.next()) tail = curr; // Removed last
			Link<E> tempptr = curr.next(); // Remember link
			curr.setNext(curr.next().next()); // Remove from list
			tempptr.release(); // Release link
			cnt--; // Decrement count
			return it; // Return removed
		}
	}
	
	/** Set curr at list start */
	public void moveToStart()
	{ curr = head; }
	
	/** Set curr at list end */
	public void moveToEnd()
	{ curr = tail; this.prev(); }
	
	/** Move curr one step left; no change if now at front */
	public void prev() {
		if (curr == head) return; // No previous element
		Link<E> temp = head;
		// March down list until we find the previous element
		while (temp.next() != curr) temp = temp.next();
		curr = temp;
	}
	
	/** Move curr one step right; no change if now at end */
	public void next()
	{ if (curr != tail) curr = curr.next(); }
	
	/** @return List length */
	public int length() { return cnt; }
	
	/** @return The position of the current element */
	public int currPos() {
		Link<E> temp = head;
		int i;
		for (i=0; curr != temp; i++)
			temp = temp.next();
		return i;
	}
	
	/** Move down list to "pos" position */
	public void moveToPos(int pos) {
		assert (pos>=0) && (pos<=cnt) : "Position out of range";
		curr = head;
		for(int i=0; i<pos; i++) curr = curr.next();
	}
	
	/** @return Current element value */
	public E getValue() {
		if(curr.next() == null) return null;
		return curr.next().element();
	}
	
	
	/** ADDITIONS */
	/** Prints all elements */
	public void print()
	{
		this.moveToStart();
		System.out.print("{ ");
		while (this.currPos() < this.length())
		{
			this.next();
			System.out.print("["+this.currPos()+"] => \""+curr.element()+"\", ");
		}
		System.out.print(" }\n");
	}
}