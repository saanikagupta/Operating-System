// highest response ratio next scheduling algorithm
#include <stdio.h>
# define INT_MAX 9999
void main(){
	int n, i, j;
	printf("\nEnter the number of jobs:\n");
	scanf("%d", &n);
	int at[n], bt[n];
	int isVis[n], visited = 0;
	printf("\nEnter the arrival times:\n");
	for(i = 0; i < n; i++){
		scanf("%d", &at[i]);
	}
	printf("\nEnter the burst times:\n");
	for(j = 0; j < n; j++){
		scanf("%d", &bt[j]);
		isVis[j] = 0;
	}
	int t;
	int k = 0;
	int flag;
	int ct[n], wt[n], tat[n], tmin, rr;
	float hrrn[n];
	while(visited < n){
		k = 0;
		flag = 0;
		rr = -1;
		tmin = INT_MAX;
		for(i = 0; i < n; i++){
			if(isVis[i] == 0 && at[i] <= t){ // Calculating RR values
				hrrn[i] = (t - at[i] + bt[i]) / bt[i];
			}
			else
				hrrn[i] = 0;
		}
		/*	
		for(i = 0; i < n; i++)
			printf("%f ", hrrn[i]);
		printf("\n");
		for(i = 0; i < n; i++)
			printf("%d ", isVis[i]);
		printf("\n");
		*/
		for(j = 0; j < n; j++){
			if(isVis[j] == 0){
				if(hrrn[j] >= rr && at[j] <= t){
					if(hrrn[j] == rr){  // For equal RR values, considering arrival time
						if(at[j] < tmin){
							k = j;
							rr = hrrn[j];
							tmin = at[j];
						}		
					}
					else{
						k = j;
						rr = hrrn[j];
						tmin = at[j];
					}
				}
			}
		}
		if(rr == -1){
			flag = 1;
			tmin = INT_MAX;
			for(j = 0; j < n; j++){
				if(isVis[j] == 0){
					if(at[j] < tmin){
						tmin = at[j];
						k = j;
					}
				}
			}
		}
		if(flag == 0){
			t += bt[k];
		}
		else
			t = at[k] + bt[k];
		ct[k] = t;
		isVis[k] = 1;
		visited++;
		tat[k] = ct[k] - at[k];
		wt[k] = tat[k] - bt[k];
	}
	printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
	for(i = 0; i < n; i++){
		printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
	}
	float avg_tat, avg_wt;
	for(i = 0; i < n; i++){
		avg_tat += tat[i];
		avg_wt += wt[i];
	}
	printf("\nAverage turnaround time = %f\n", avg_tat/n);
	printf("\nAverage waiting time = %f\n", avg_wt/n);
}
