# longest job first scheduling algorithm
#include <stdio.h>
# define INT_MAX 9999
void main(){
	int n, i, j;
	printf("\nEnter the number of jobs:\n");
	scanf("%d", &n);
	int at[n], bt[n], isVis[n], visited = 0;
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
		for(i = 0; i < n; i++){
			if(isVis[i] == 0){
				if(bt[i] > max && at[i] <= t){
					k = i;
					max = bt[i];
				}
			}
		}
		if(max == -1){
			flag = 1;
			max = bt[0];
			tmin = INT_MAX;
			for(i = 0; i < n; i++){
				if(isVis[i] == 0){
					if(at[i] < tmin || at[i] == tmin && bt[i] > max){
						tmin = at[i];
						max = bt[i];
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
