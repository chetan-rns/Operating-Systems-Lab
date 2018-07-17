#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
struct process {
	int pid, bt, art;
};
int n;
void getProcess(int flag, process pro[]) {
	for (int i = 0; i < n; i++) {
		cout << "Enter the details of process " << i + 1 << endl;
		pro[i].pid = i + 1;
		cin >> pro[i].bt;
		if (flag == 1)cin >> pro[i].art;
		else pro[i].art = 0;
	}
}
void printProcess(process pro[], int wt[]) {
	cout << "Processes "
	     << " Burst time "
	     << " Waiting time "
	     << " Turn around time\n";
	int total_wt = 0, total_tat = 0;
	for (int i = 0; i < n; i++) {
		total_wt = total_wt + wt[i];
		total_tat = total_tat + pro[i].bt + wt[i];
		cout << " " << pro[i].pid << "\t\t"
		     << pro[i].bt << "\t\t " << wt[i]
		     << "\t\t " << pro[i].bt + wt[i] << endl;
	}
	cout << "\nAverage waiting time = "
	     << (float)total_wt / (float)n;
	cout << "\nAverage turn around time = "
	     << (float)total_tat / (float)n;
}
void SJF(process pro[]) {
	int wt[100], rt[100], shortest, t = 0, complete = 0, minm = 99999;
	bool done = false;
	for(int i=0;i<n;i++)rt[i]=pro[i].bt;
	while (complete != n) {
		for (int i = 0; i < n; i++)
			if (rt[i] > 0 && rt[i] < minm && pro[i].art <= t) {
				shortest = i;
				minm = rt[i];
				done = true;
			}
		if (!done) {
			t++;
			continue;
		}
		rt[shortest]--;
		minm = rt[shortest];
		if (minm <= 0)minm = 99999;
		if (rt[shortest] == 0) {
			int finish_time = t + 1;
			complete++;
			wt[shortest] = finish_time - pro[shortest].bt - pro[shortest].art;
			if (wt[shortest] < 0)wt[shortest] = 0;
		}
		t++;
	}
	printProcess(pro, wt);
}
void SJF_preemptive(process pro[]) {
	int wt[100], rt[100], shortest, t = 0, complete = 0, minm = 99999;
	bool done = false;
	for(int i=0;i<n;i++)rt[i]=pro[i].bt;
	while (complete != n) {
		done = false;
		for (int i = 0; i < n; i++)
			if (rt[i] > 0 && rt[i] < minm && pro[i].art <= t) {
				shortest = i;
				minm = rt[i];
				done = true;
			}
		if (!done) {
			t++;
			continue;
		}
		t += rt[shortest];
		rt[shortest] = 0;
		minm = 99999;
		if (rt[shortest] == 0) {
			int finish_time = t;
			complete++;
			wt[shortest] = finish_time - pro[shortest].bt - pro[shortest].art;
			if (wt[shortest] < 0)wt[shortest] = 0;
		}
	}
	printProcess(pro, wt);
}
/*void RR(process pro[]) {
	int wt[100], rt[100], quantum = 0, complete = false,t=0;
	bool done = false;
	for(int i=0;i<n;i++)rt[i]=pro[i].bt;
	cout << "ENter time quantum\n";
	cin >> quantum;
	while (1) {
		done = false;
		for (int i = 0; i < n; i++) {
			if (rt[i] > 0) {
				done = true;
				if (rt[i] > quantum) {
					t += quantum;
					rt[i] -= quantum;
				}
				else {
					t += rt[i];
					rt[i] = 0;
					wt[i] = t - pro[i].bt;
				}
			}
		}
		if (!done)break;
	}
	printProcess(pro, wt);
}*/
void round_robin(process pro[]) {
	int wt[1000], rt[1000], t = 0;
	for (int i = 0; i < n; i++)rt[i] = pro[i].bt;
	cout << "Enter time quantum\n";
	int quantum;
	cin >> quantum;
	bool done = true;
	while (1) {
		done = true;
		for (int i = 0; i < n; i++) {
			if (rt[i] > 0) {
				done = false;
				if (rt[i] > quantum) {
					t += quantum;
					rt[i] -= quantum;
				}
				else {
					t += rt[i];
					rt[i] = 0;
					wt[i] = t - pro[i].bt;
				}
			}
		}
		if (done)break;
	}
	printProcess(pro, wt);
}
int main() {
	cout << "Enter the number of process\n";
	cin >> n;
	process pro[n];
	cout << "Enter your choice:\n";
	cout << "1.SJF\n2.RR\n";
	int ch;
	cin >> ch;
	if (ch == 1) {
		getProcess(1,pro);
		SJF_preemptive(pro);
	}
	else {
		getProcess(0,pro);
		round_robin(pro);
	}


	return 0;
}