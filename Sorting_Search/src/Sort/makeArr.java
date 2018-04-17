package Sort;

public class makeArr {
	
	private int[] arr;
	private int N;
	makeArr(int n){
		arr = new int[n];
		N=n;
	}
	int[] getArr() {return arr;}
	
	void des(){for(int i = 0 ; i < N ; i ++) arr[i]=N-i;}
	void rand() {
		this.des();
		for(int i = 0 ; i < N ; i++)
			swap((int)(Math.random()*(N-1))+1,i);
	}
	
	void swap(int i ,int j)
	{
		int temp = arr[i];
		arr[i]= arr[j];
		arr[j]=temp;
	}
	
	void printArr()
	{
		for(int i = 0 ; i < 20 && i < N ; i++)
			System.out.print(arr[i]+" ");
		System.out.println();
	}
}
