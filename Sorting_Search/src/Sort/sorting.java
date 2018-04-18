package Sort;
import java.util.Scanner;

public class sorting {

	static void selection(int A[],int n)
	{
		for(int i = 0 ; i < n-1 ; i ++)
		{
			int minIndex = i;
			
			for(int j = i+1 ; j< n ; j++)
			{
				if(A[minIndex]>A[j])
					minIndex=j;
			}
			swap(A,i,minIndex);
		}
	}
	
	
	static void insertion(int A[] , int n)
	{
		int i , j ,v;
		for(i = 2; i <= n ; i++)
		{
			v= A[i];
			j=i;
			while(v<A[j-1])
			{
				A[j]=A[j-1];
				j--;
			}
			A[j]=v;
		}
	}
	
	static void BubbleSort(int A[],int n)
	{
		int i;
		boolean Sorted=false;
		while(!Sorted)
		{
			Sorted=true;
			for(i = 1 ; i < n ; i ++)
				if(A[i-1]>A[i]) 
				{
						swap(A,i,i-1);
						Sorted=false;
				}
		}
	}
	
	static void swap(int A[],int i,int j)
	{
		int tmp = A[j];
		A[j]=A[i];
		A[i]=tmp;
	}
	public static void main(String[] args) {
		
		Scanner sc = new Scanner(System.in);
		
		int n = sc.nextInt();
		
		makeArr arr = new makeArr(n);
		
		arr.des();
		arr.printArr();		
		arr.rand();
		arr.printArr();
		
		selection(arr.getArr(),n);
		arr.printArr();
		sc.close();
		
		
	}

}
