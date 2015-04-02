/*
 * @name William Woodard
 * @date 9-8-2014
 */
public class Recursion
{
	public static void main(String[] args)
	{
		int[] a = {3, 5, 6, 5, 23, 12, 2};
		boolean[] b = {true, false, true};
		int n = 0;
		System.out.println(Fib(n));
		System.out.println(Sum(n));
		System.out.println(Product(n));
		System.out.println(ArraySum(a, a.length));
		
		//1) Find the minimum element in an array of integers
		System.out.println(MinEl(a, a.length));
		
		//2) Given an array of boolean values, return the Nth 
		//operation on all the elements.
		System.out.println(LastAND(b, b.length));
	}
	
	private static int MinEl(int a[], int n)
	{
		if (n == 1)
			return a[0];
		else
		{
			int temp = MinEl(a, n - 1);
			if (temp < a[n - 1])
				return temp;
			else
				return a[n - 1];
		}
	}
	
	private static boolean LastAND(boolean a[], int n)
	{
		if (n == 1)
			return a[0];
		else
			return a[n - 1] && LastAND(a, n - 1);
	}
	
	
	
	private static int Fib(int n)
	{
		if (n==0)
			return 0;
		else if (n == 1 || n == 2)
			return 1;
		else
			return Fib(n - 1) + Fib(n - 2);
	}
	
	private static int Sum(int n)
	{
		if (n == 0) 
			return 0;
		else 
			return n + Sum(n - 1);
	}
	
	private static int Product(int n)
	{
		if (n == 1 || n == 0) 
			return 1;
		else 
			return n * Product(n - 1);
	}
	
	private static int ArraySum(int a[], int n)
	{
		if (n == 1)
			return a[0];
		else
			return a[n - 1] + ArraySum(a, n - 1);
	}
}
