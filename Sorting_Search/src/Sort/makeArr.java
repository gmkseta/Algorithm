package Sort;

public class makeArr {
	
	private int[] arr;
	private int N;
	private boolean dummy;
	makeArr(int n,boolean dum){
		arr = new int[n+1];
		N=n+1;
		dummy = dum;		
	}
	makeArr(int n){
		arr = new int[n];
		N=n;
		dummy = false;
	}
	int[] getArr() {return arr;}
	
	void des(){
		arr[0]=Integer.MIN_VALUE;
		for(int i = dummy?1:0 ; i < N ; i ++) arr[i]=N-i;
		
	}
	void rand() {
		this.des();
		for(int i = dummy?1:0 ; i < N ; i++)
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
		for(int i = dummy?1:0 ; i < (dummy?21:20) && i < N ; i++)
			System.out.print(arr[i]+" ");
		System.out.println();
	}
}
