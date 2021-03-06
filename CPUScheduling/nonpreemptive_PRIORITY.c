// non-preemptive priority scheduling algorithm
#include <stdio.h>
# define INT_MAX 9999
void main(){
	int n, i, j;
	printf("\nEnter the number of jobs:\n");
	scanf("%d", &n);
	int at[n], bt[n], isVis[n], visited = 0, priority[n];
	printf("\nEnter the priority:\n");
	for(j = 0; j < n; j++){
		scanf("%d", &priority[j]);
	}

	printf("\nEnter the arrival times:\n");
	for(i = 0; i < n; i++){
		scanf("%d", &at[i]);
	}
	printf("\nEnter the burst times:\n");
	for(j = 0; j < n; j++){
		scanf("%d", &bt[j]);
		isVis[j] = 0;
	}
	int t = 0, k = 0;
	int tat[n], ct[n], wt[n], flag, tmin, max, min;
	while(visited < n){
		k = 0;
		flag = 0;
		max = -1;
		tmin= INT_MAX;
		for(i = 0; i < n; i++){
			if(isVis[i] == 0){
				if(priority[i] > max && at[i] <= t){
					if(max == priority[i]){  // To consider arrival time in case of equal priority
						if(at[i] < tmin){
							k = i;
							max = priority[i];
							tmin = at[i];
						}
					}
					else{
						k = i;
						max = priority[i];
						tmin = at[i];
					}
				}
			}
		}
		if(max == -1){
			flag = 1;
			max = priority[0];
			tmin = INT_MAX;
			for(i = 0; i < n; i++){
				if(isVis[i] == 0){
					if(at[i] < tmin || at[i] == tmin && priority[i] > max){
						tmin = at[i];
						max = priority[i];
						k = i;
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
	printf("\nProcess\tPriority\tAT\tBT\tCT\tTAT\tWT\n");
	for(i = 0; i < n; i++){
		printf("P%d\t%d\t\t%d\t%d\t%d\t%d\t%d\n", i+1, priority[i], at[i], bt[i], ct[i], tat[i], wt[i]);
	}
	float avg_tat = 0, avg_wt = 0;
	for(i = 0; i < n; i++){
		avg_tat += tat[i];
		avg_wt += wt[i];
	}
	printf("\nAverage turnaround time = %f\n", avg_tat/n);
	printf("\nAverage waiting time = %f\n", avg_wt/n);
}
