package Sort;
import java.util.Scanner;

public class sorting {

	
	/*****************************************************
	ù �ε����� ���� ���� ���ڸ� swap
	�״����ε��� .. �ݺ� �ϴ� sorting �˰���	
	�Է� �ڷ� ������ �����ϰ� n-i ���� 0~n-1���� ���� �� 
	��� , �־� �ð� ���⵵ O(n^2)
	���ڸ� ����, i j MinIndex ��� ���ũ�� �޸�,
	�Ҿ���������
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
	�Ǿտ� ���̰��� �ְ�
	2 �ε������� �� �ʿ�� ��ȯ�Ѵ�.
	v�� ���� �ְ� �� ���� �ε������ �񱳸� �ؼ� ����ؼ� �о�� v�� ��ġ�� ã�� �װ��� ����
	 ���ڸ����� , i j v ��� ũ�� �޸�
	 ������ ���� , ������ ���ڵ峢���� ��
	 �־� �ð����⵵ O(n^2) �������� �̹� ���ĵ� ���ڵ�,
	 i��° Ű ���Խ� i���� �񱳸� ������
	 2+3+...n = n(n+1)/2-1
	 
	 �ּ� O(n)
	 �̹� ���ĵ� ���ڵ�
	 n-1�� ����
	 
	 ��� O(n^2)
	 
	 A[1:i-1] A[i]�� ���� �Ҷ� 
	 ��� �� Ƚ�� 1/i * (1+2+...i) = (i+1)/2
	 ��� �ð� ���⵵ = ������ ���� , (n^2+3n-4)/4	 
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
	��ù �ε����� �ٷ� ������ �ε��� �� ���� ���ϰ� ��ġ�� �ٲٰ�
	�״��� �ε����� �ٷ� ������ �ε����� ���� ���Ͽ� ��ġ�� ����ؼ� �ٲٴ� ������� sorting�� �ϴ� �˰���
	���ڸ� ����, i Sorted�� ���ũ�� �޸�
	������ ���� ( ������ ���ڵ� ������ �ڸ��� �ٲ�)
	��� , �־� O(n^2) 
	�־�, ������ �̹� ���ĵ� �ڵ� - > (n-1) + (n-2 ) ... +1 = n(n-1)/2
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
		int h = 1,i,j,value;
		while(h<n)
			h = 3*h+1;
		
		do {
			h = h/3;
			for(i = h ; i < n ;i++)
			{
				value = A[i];
				j = i ;
				while(A[j-h]>value) 
				{
					A[j]=A[j-h];
					j-=h;
					if(j<=h-1)break;
				}
			A[j]=value;	
			}	
		}while(h>1);
		
	}
	static int partition(int A[],int left , int right) 
	{
		int value,tmp;
		tmp = left; value=A[tmp];
		do {
			while(A[++left]<value);
			while(A[--right]>value);
			if(left<right)swap(A,left,right);
			else break;
		}while(true);
		
		A[tmp] = A[right];
		A[right] = value;
		return right;
		
	}
	static void quickSort(int A[],int left , int right)
	{
		int k ;
		if (right>left)
		{
			k = partition(A,left,right);
			quickSort(A,left,k-1);
			quickSort(A,k+1,right);
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
		//shellSort(arr.getArr(),n);
		quickSort(arr.getArr(),0,n);
		arr.printArr();
		
		
		arr.rand();
		arr.printArr();
		shellSort(arr.getArr(),n);
		arr.printArr();
		
		
		sc.close();
		
		
		
		
	}

}
