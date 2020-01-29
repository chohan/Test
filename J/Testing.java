package test;




public class Testing {
	
	//constructor
	public Testing()
	{
		func1(2);
		func2(4);
		sort();
		
	}

	//main function
	public static void main(String[] args)
	{
		new Testing();
	}
	
	/**
	 * first function
	 * @param a
	 */
	void func1(int a)
	{
		System.out.println("This is func1 = " + a);		
	}
	
	/**
	 * second function
	 * @param a
	 */
	void func2(int a)
	{
		System.out.println("This is func2 = " + a);		
	}

    public void sort()
    {
        int n = 4;
        int size = 10;
        int[] ar = {1, 4 , 5, 2, 8, 6, 3, 0, 9, 12};
          

        int i, j;
//      sort first n elements of array
        for(i=0; i<(n-1); i++)
        {
          for(j=i+1; j<n; j++)
          {
            if(ar[i]<ar[j])
              swap(ar, i, j);
          }
        }  
        System.out.println("I="+ar[0] + " II="+ar[1] + " III="+ar[2] + " IV="+ar[3]);


        //comparison
        for(i=n; i<size; i++)
        {
          if(ar[i]<=ar[n-1])
            continue;
          
          //comparing with n elements
          for(j=0; j<(n-1); j++)
          {
            if(ar[i]>ar[j])
            {
              int k=n-1;
              while(k>j)
              {
            	  ar[k] = ar[k-1];
            	  --k;
              }
              ar[j] = ar[i];
              System.out.println("I="+ar[0] + " II="+ar[1] + " III="+ar[2] + " IV="+ar[3]);
              break;
            }
          }  
        }
        
        System.out.println("I="+ar[0] + " II="+ar[1] + " III="+ar[2] + " IV="+ar[3]);
        System.out.println(n + "th element in the array is " + ar[n-1]);
    }
    
    void swap(int[] ar, int a, int b)
    {
      int tmp = ar[a];
      ar[a] = ar[b];
      ar[b] = tmp;
    }    

}
