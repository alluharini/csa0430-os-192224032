#include<stdio.h>
#include<limits.h>
void bestsize(int blocksize[],int m, int processsize[],int n){
	int allocation[n];
	for (int i=0;i<n;i++ ){
		allocation[i]=-1;
	}
	for(int i=0;i<n;i++){
		int bestidx=-1;
		for (int j=0;j<m;j++){
			if(blocksize[j]>=processsize[i]){
				if(bestidx==-1||blocksize[bestidx]>blocksize[j]){
				bestidx=j;
			}
		}
	}
	if(bestidx!=-1){
		allocation[i]=bestidx;
		blocksize[bestidx]=-processsize[i];
   }
}
   printf("process no\t process size \t allocation\t");
   for(int i=0;i<n;i++){
   	printf("\n%d\t %d\t ",i+1,processsize[i]);
   	if(allocation[i]!=-1){
   		printf("%d\n",allocation[i]+1);
	   }else{
	   	printf("not allocated\n");
	   }
   }
}
int main() {
   	int blocksize[]={100,200,300,400};
   	int processsize[]={198,340,90,290};
   	int m = sizeof(blocksize)/sizeof(blocksize[0]);
   	int n = sizeof(processsize)/sizeof(processsize[0]);
   	bestsize(blocksize,m,processsize,n);
   	
   	return 0;
}
