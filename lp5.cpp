#include<iostream>
#include<stdlib.h>
#include<omp.h>
#include <bits/stdc++.h> 
using namespace std;

void bubble(int *, int);
void swap(int &, int &);


void bubble(int *a, int n)
{
    for(  int i = 0;  i < n;  i++ )
     {  	 
   	 int first = i % 2; 	 

   	 #pragma omp parallel for shared(a,first)
   	 for(  int j = first;  j < n-1;  j += 2  )
   	   {  	 
   		 if(  a[ j ]  >  a[ j+1 ]  )
   		  {  	 
     			 swap(  a[ j ],  a[ j+1 ]  );
   		  }  	 
   		   }  	 
     }
}


void simplebubble(int *a, int n)
{
    for(  int i = 0;  i < n;  i++ )
     {  	 
   	 int first = i % 2; 	 
   	 for(  int j = first;  j < n-1;  j += 2  )
   	   {  	 
   		 if(  a[ j ]  >  a[ j+1 ]  )
   		  {  	 
     			 swap(  a[ j ],  a[ j+1 ]  );
   		  }  	 
   		   }  	 
     }
}

void swap(int &a, int &b)
{

    int test;
    test=a;
    a=b;
    b=test;

}


void mergesort(int a[],int i,int j);
void merge(int a[],int i1,int j1,int i2,int j2);

void mergesort(int a[],int i,int j)
{
	int mid;
	if(i<j)
	{
    	mid=(i+j)/2;
   	 
    	#pragma omp parallel sections
    	{

        	#pragma omp section
        	{
            	mergesort(a,i,mid);   	 
        	}

        	#pragma omp section
        	{
            	mergesort(a,mid+1,j);    
        	}
    	}

    	merge(a,i,mid,mid+1,j);    
	}

}
 
void merge(int a[],int i1,int j1,int i2,int j2)
{
	int temp[1000];    
	int i,j,k;
	i=i1;    
	j=i2;    
	k=0;
    
	while(i<=j1 && j<=j2)    
	{
    	if(a[i]<a[j])
    	{
        	temp[k++]=a[i++];
    	}
    	else
    	{
        	temp[k++]=a[j++];
    }    
	}
    
	while(i<=j1)    
	{
    	temp[k++]=a[i++];
	}
   	 
	while(j<=j2)    
	{
    	temp[k++]=a[j++];
	}
   	 
	for(i=i1,j=0;i<=j2;i++,j++)
	{
    	a[i]=temp[j];
	}    
}


int main()
{

    int *a,*a2,*m,n;
    cout<<"\n enter total no of elements=>";
    cin>>n;
    a=new int[n];  
    a2=new int[n];   
    m=new int[n];
    //cout<<"\n enter elements=>";
     for(int i=0;i<n;i++){
		  a[i]=rand()%100;  
		  m[i]=rand()%100;    
		  a2[i]=rand()%100;  
     }
     //for(int i=0;i<n;i++){
     // cout<<"::"<<a[i];
     //}
     //-------------------BUBBLE SORT-------------
     clock_t start1, end1;
    start1 = clock();

    simplebubble(a,n);
    
    end1 = clock();
    //-------------------------------------
    clock_t start, end;
    start = clock();

    bubble(a2,n);
    
    end = clock();
    //-------------------MERGE SORT-------------
     clock_t start3, end3;
    start3 = clock();

    	mergesort(m, 0, n-1);
    
    end3 = clock();
    //-------------------------------------
    //cout<<"\n sorted array is=>";
   // for(int i=0;i<n;i++)
    //{
   	// cout<<a[i]<<endl;
    //}
    cout<<"---------------------"<<endl;
    double time_taken1 = double(end1 - start1) / double(CLOCKS_PER_SEC);
    cout << "Time taken by simple bubble sort is : " << fixed 
         << time_taken1;
    cout << " sec " << endl;
    cout<<"---------------------"<<endl;
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by Bubble sort in parrallel is : " << fixed 
         << time_taken;
    cout << " sec " << endl;
    cout<<"---------------------"<<endl;
    double time_taken3 	= double(end3 - start3) / double(CLOCKS_PER_SEC);
    cout << "Time taken by Merge sort in ll is : " << fixed 
         << time_taken3;
    cout << " sec " << endl;


return 0;
}

