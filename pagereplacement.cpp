#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
int n, capacity, page_faults = 0;
std::vector<int> page_string;
void page_lru() {
	set<int> frame;
	int page_index[1000];
	page_faults=0;
	for (int i = 1; i <= n; i++) {
		std::set<int>::iterator it;
		if (frame.size() < capacity) {
			if (frame.find(page_string[i]) == frame.end()) {
				page_faults++;
				frame.insert(page_string[i]);
			}
			page_index[page_string[i]] = i;
		}
		else {
			if (frame.find(page_string[i]) == frame.end()) {
				int val = 9999,min_lru=999;
				for (it=frame.begin(); it != frame.end(); it++) {
					if (page_index[*it] < min_lru){
						min_lru=page_index[*it];
						val = *it;
					}
				}
				frame.erase(val);
				frame.insert(page_string[i]);
				page_faults++;
			}
			page_index[page_string[i]] = i;
		}
		for (it=frame.begin(); it != frame.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "Page faults: " << page_faults << endl;
}
void page_fifo() {
	set<int> frame;
	queue<int> q;
	page_faults = 0;
	for (int i = 1; i <= n; i++) {
		if (frame.size() < capacity) {
			if (frame.find(page_string[i]) == frame.end()) {
				frame.insert(page_string[i]);
				q.push(page_string[i]);
				page_faults++;
			}
		}
		else { //perform FIFO
			if (frame.find(page_string[i]) == frame.end()) {
				page_faults++;
				int val = q.front();
				q.pop();
				frame.erase(val);
				q.push(page_string[i]);
				frame.insert(page_string[i]);
			}
		}
		queue<int> a = q;
		for (int j = 1; j <= capacity; j++) {
			cout << a.front() << " ";
			a.pop();
		}
		cout << endl;
	}
	cout << "Page faults: " << page_faults << endl;
}
int main() {
	cout << "Enter the number of pages\n";
	cin >> n;
	cout << "Enter the page reference string\n";
	page_string.assign(n + 1, 0);
	for (int i = 1; i <= n; i++)cin >> page_string[i];
	cout << "Enter the capacity of frame\n";
	cin >> capacity;
	page_lru();
	return 0;
}
/*
1 2 3 4 2 1 5 6 2 1 2 3 7 6 3 2 1 2 3 6

*/