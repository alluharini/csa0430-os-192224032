#include<stdio.h>
#include<stdlib.h>
int main(){
	int n,i,total=0,ready[100],a;
	printf("enter number of requests:");
	scanf("%d",&n);
	for(i=0;i<n;i++){
		printf("enter the requests:");
		scanf("%d",&ready[i]);
	}
	printf("enter the intial of head position:");
	scanf("%d",&a);
	for(i=0;i<n;i++){
		total=total+abs(ready[i]-a);
		a=ready[i];
	}
	printf("seek time is:%d",total);
	return 0;	
}
