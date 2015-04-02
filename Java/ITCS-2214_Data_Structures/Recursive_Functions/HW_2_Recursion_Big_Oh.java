/*
 * @name William Woodard
 * @date 9-15-2014
 * @class ITCS-2214-001
 * @HW HW_2_Recursion_Big_Oh
 */

public class HW_2_Recursion_Big_Oh
{

	public static void main(String[] args)
	{
		int N = 3;
		int A[] = {1,2,3,4,5};
		//System.out.println(Sum_Of_Squares_i(N));
		//System.out.println(Sum_Of_Squares_r(N));
		System.out.println(Array_Print_i(A, A.length));
		System.out.println(Array_Print_r(A, A.length));
		System.out.println(Array_Print_Reverse_r(A, A.length));
	}

	private static int Sum_Of_Squares_i(int N)
	{
		int f = 0;
		for (int i = N; i > 0; i--)
			f += i * i;
		return f;	
	}
	
	private static int Sum_Of_Squares_r(int N)
	{
		if (N == 0)
			return 0;
		else
			return N * N + Sum_Of_Squares_r(N - 1);
	}
	
	private static int Array_Print_i(int A[], int length)
	{
		for (int i = 0; i < length; i++)
			print(A[i]);
		return 0;
	}
	
	private static int Array_Print_r(int A[], int length)
	{
		if (length == 0)
			return 0;
		else
		{
			print(A[A.length - length]);
			return Array_Print_r(A, length - 1);
		}
	}
	
	private static int Array_Print_Reverse_r(int A[], int length)
	{
		if (length == 0)
			return 0;
		else
		{
			print(A[length - 1]);
			return Array_Print_Reverse_r(A, length - 1);
		}
	}
	
	private static int print(int I)
	{
		System.out.print(I + ",");
		return I;
	}
}
