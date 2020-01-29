import java.util.Scanner;

class Test
{

public static void main(String[] args) throws Exception
{
	Test test = new Test(args);
}

public Test(String[] args)
{
	System.out.println("\nBismillah");
	System.out.printf("\nNo of args=%d\n", args.length);
	//System.out.println(String.format("1=%s, 2=%s", args[0], args[1]));
	//ifExists();
	System.out.println("Factorial=" + factorial(20));
	swapNos();
}

public void swapNos()
{
	int a=55, b=77;
	System.out.printf("\na=%d, b=%d", a, b);
	a = a+b;
	b = a-b;
	a = a-b;
	System.out.printf("\na=%d, b=%d", a, b);
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
	System.out.printf("\na=%d, b=%d", a, b);
}

public void ifExists()
{
	//int[] ints = {100,150,151,200};
	//int[] ints = {100};
	//int k = 270;
	System.out.println("Please enter inputs");
	Scanner scanner = new Scanner(System.in);
	int N = scanner.nextInt();
	int ints[] = new int[N];
	for(int i=0; i<N; i++){
		ints[i] = scanner.nextInt();
	}
	System.out.println("Please enter number to find");
	int k = scanner.nextInt();
	boolean res = find(ints, k);
	System.out.println("Result=" + res);
}

public boolean find(int[] ints, int k)
{
	for(int x : ints){System.out.println(x + " ");}
	if(ints.length<2){ 
		System.out.println("not a valid array");
		return false;
	}
	if(k < ints[0] || k > ints[ints.length-1]){
		System.out.printf("%d is not there in given array", k);
		return false;
	}
	int iFound = isPresent(ints, 0, ints.length-1, k);
	System.out.println("\niFound="+iFound);
	String res = "\n" + ((iFound>=0)? k + " is found" : k + " is NOT found");
	System.out.println(res);
	return false;
}

public int isPresent(int[] ints, int iL, int iH, int k)
{
	int iM = (iH + iL)/2;
	System.out.printf("\niL=%d, iH=%d, iM=%d, ints[iM]=%d, k=%d", iL, iH, iM, ints[iM], k);
	//if(ints[iM] == k) return iM; // found
	if(ints[iM] == k){
		System.out.printf("\nints[%d]=%d, k=%d", iM, ints[iM], k);
		return iM; // found
	}
	else if(iL == iM)	{return -100;}
	else if(k < ints[iM]) {isPresent(ints, iL, iM, k);}
	else if(k > ints[iM]) {isPresent(ints, iM, iH, k);}
	return -200;
}

public long factorial(int N)
{
	if(N==2) return N;
	return N*factorial(N-1);
}

}
