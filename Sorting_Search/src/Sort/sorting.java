package Sort;
import java.util.Scanner;

public class sorting {

	
	/*****************************************************
	첫 인덱스와 가장 작은 숫자를 swap
	그다음인덱스 .. 반복 하는 sorting 알고리즘	
	입력 자료 순서와 무관하게 n-i 번씩 0~n-1까지 수행 함 
	평균 , 최악 시간 복잡도 O(n^2)
	제자리 정렬, i j MinIndex 모두 상수크기 메모리,
	불안정한정렬
	*****************************************************/
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
	
	/*****************************************************
	맨앞에 더미값이 있고
	2 인덱스부터 비교 필요시 교환한다.
	v에 값을 넣고 그 이전 인덱스들과 비교를 해서 계속해서 밀어내고 v의 위치를 찾고 그곳에 넣음
	 제자리정렬 , i j v 상수 크기 메모리
	 안정된 정렬 , 인접한 레코드끼리만 비교
	 최악 시간복잡도 O(n^2) 역순으로 이미 정렬된 레코드,
	 i번째 키 삽입시 i번의 비교를 수행함
	 2+3+...n = n(n+1)/2-1
	 
	 최선 O(n)
	 이미 정렬된 레코드
	 n-1번 비교함
	 
	 평균 O(n^2)
	 
	 A[1:i-1] A[i]를 삽입 할때 
	 평균 비교 횟수 1/i * (1+2+...i) = (i+1)/2
	 평균 시간 복잡도 = 저거으 ㅣ합 , (n^2+3n-4)/4	 
	*****************************************************/	
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
	
	
	/*****************************************************
	맨첫 인덱스와 바로 인접한 인덱스 의 값을 비교하고 위치를 바꾸고
	그다음 인덱스와 바로 인접한 인덱스의 값을 비교하여 위치를 계속해서 바꾸는 방식으로 sorting을 하는 알고리즘
	제자리 정렬, i Sorted등 상수크기 메모리
	안정된 정렬 ( 인접한 레코드 끼리만 자리를 바꿈)
	평균 , 최악 O(n^2) 
	최악, 역순을 이미 정렬된 코드 - > (n-1) + (n-2 ) ... +1 = n(n-1)/2
	*****************************************************/	
	static void BubbleSort(int A[],int n)
	{
		int i;
		boolean Sorted=false;
		int a=0;
		while(!Sorted)
		{
			
			Sorted=true;
			for(i = 1 ; i < n; i ++)
			{	if(A[i-1]>A[i]) 
				{
						swap(A,i,i-1);
						Sorted=false;
				}
			a++;
			}
			n--;
		}
		
		System.out.println(a);
	}
	
	
	static void shellSort(int A[],int n)
	{
		int h = 1;
		while(h<n)
		{
			h = 3*h+1;
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
		BubbleSort(arr.getArr(),n);
		arr.printArr();
		
		
		arr.rand();
		arr.printArr();
		BubbleSort(arr.getArr(),n);
		arr.printArr();
		
		
		sc.close();
		
		
		
		
	}

}
