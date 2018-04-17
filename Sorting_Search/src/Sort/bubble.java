package Sort;
import java.util.Scanner;

public class bubble {

	
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
		
		BubbleSort(arr.getArr(),n);
		arr.printArr();
		sc.close();
		
		
	}

}
