// round robin scheduling algorithm
#include <stdio.h>
# define INT_MAX 999
void main(){
	int n, i, tq;
	printf("\nEnter the number of jobs and time quanta:\n");
	scanf("%d%d", &n, &tq);
	int at[n], bt[n], bt_copy[n], at_copy[n], isVis[n];
	printf("\nEnter the arrival time:\n");
	for(i = 0; i < n; i++){
		scanf("%d", &at[i]);
		at_copy[i] = at[i];	
	}
	printf("\nEnter the burst time:\n");
	for(i = 0; i < n; i++){
		scanf("%d", &bt[i]);
		bt_copy[i] = bt[i];	
		isVis[i] = 0;
	}
	int rq[100], k = 0, j, rear = -1, front = 0, count = 0;
	int ct[n], wt[n], tat[n], rt[n], t = 0, min, l, f, flag = 0;
	for(j = 0; j < n; j++){
		min = INT_MAX;
		flag = 0;
		k = 0;
		for(i = 0; i < n; i++){
			if(isVis[i] == 0 && at_copy[i] <= t){
				if(at_copy[i] < min){
					flag = 1;
					k = i;
					min = at_copy[i];			
				}
			}
		}
		if(flag == 0)
			break;
		rq[++rear] = k;
		at_copy[k] = INT_MAX;
		isVis[k] = 1;
	}
	if(rear == -1){
		k = 0;
		min = at_copy[0];
		for(i = 0; i < n; i++){
			if(at_copy[i] < min){
				min = at_copy[i];
				k = i;
			}
		}
		rq[++rear] = k;
		at_copy[k] = INT_MAX;
		isVis[k] = 1;
		t = min;
	}
	while(count < n){
		int flag2 = 0;
		l = rq[front++];
		f = bt_copy[l];
		if(bt[l] == bt_copy[l])
			rt[l] = t - at[l];
		if(f < tq){
			t += f;
		}
		else{
			t += tq;
			f = tq;
		}
		bt_copy[l] = bt_copy[l] - f;
		if(bt_copy[l] == 0){
			ct[l] = t;
			tat[l] = ct[l] - at[l];
			wt[l] = tat[l] - bt[l];
			count++;
			flag2 = 1;
		}
		int flag3 = 0;
		for(j = 0; j < n; j++){
			min = INT_MAX;
			k = 0;
			flag = 0;
			for(i = 0; i < n; i++){
				if(isVis[i] == 0 && at_copy[i] <= t){
					if(at_copy[i] < min){
						flag = 1;
						k = i;
						min = at_copy[i];		
					}
				}
			}
			if(flag == 0)
				break;
			rq[++rear] = k;
			at_copy[k] = INT_MAX;
			isVis[k] = 1;
			if(min == t && flag2 == 0){
				flag3 = 1;
				rq[++rear] = l;
			}
		}
		if(flag3 != 1 && flag2 == 0){
			rq[++rear] = l;
		}
		if(front > rear && count < n){
			k = 0;
			min = INT_MAX;
			for(i = 0;i < n; i++){
				if(at_copy[i] < min){
					min = at_copy[i];
					k = i;
				}
			}
			rq[++rear] = k;
			at_copy[k] = INT_MAX;
			isVis[k] = 1;
			t = min;
		}
	}
	printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");
	for(i = 0; i < n; i++){
		printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
	}
	float avg_tat = 0, avg_wt = 0, avg_rt = 0;
	for(i = 0; i < n; i++){
		avg_tat += tat[i];
		avg_wt += wt[i];
		avg_rt += rt[i];
	}
	printf("\nAverage turnaround time = %f\n", avg_tat/n);
	printf("\nAverage waiting time = %f\n", avg_wt/n);
	printf("\nAverage response time = %f\n", avg_rt/n);
}
