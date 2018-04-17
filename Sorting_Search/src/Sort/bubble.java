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
						int tmp = A[i-1];
						A[i-1]=A[i];
						A[i]=tmp;
						Sorted=false;
				}
		}
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
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
