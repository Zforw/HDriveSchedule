#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

int request[] = {30,50,100,180,20,90,150,70,80,10,160,120,40,110};
const int n = 14;
int start = 90;//当前读写头在90号


void FCFS() {
	int num = 0;
	int last = start;
	for (int i = 0; i < n; i++) {
		cout << char('A' + i) << " ";
		num += abs(last - request[i]);
		last = request[i];
	}
	cout << endl << "先来先服务平均移动道数:" << (double)num / n << endl;
}
bool cmp(const pair<int, int> a, const pair<int, int> b) {
	if(a.first == b.first) {
		return a.second < b.second;
	} else {
		return a . first < b . first;
	}
}
void SSTF() {
	int num = 0;
	vector<pair<int,int>> t;
	for (int i = 0; i < n; i++) {
		t. emplace_back(request[i], i);
	}
	//sort(t.begin(), t.end(), cmp);//排序
	int loc = start;
	int pre = start;
	while(!t.empty()) {
		int min_dis = 2333;
		auto ind = t.begin();
		for (auto i = t . begin (); i != t . end (); i++) {
			if(abs((*i).first - loc) < min_dis) {
				min_dis = abs((*i).first - loc);
				ind = i;
			}
		}
		loc = (*ind).first;
		cout << char('A' + (*ind).second) << " ";
		num += abs(loc - pre);
		pre = loc;
		t.erase(ind);
	}
	cout << endl << "最短寻道优先平均移动道数:" << (double)num / n << endl;
}
void LIFT() {
	int num = 0;
	vector<pair<int,int>> t;
	for (int i = 0; i < n; i++) {
		t. push_back(make_pair(request[i], i));
	}
	sort(t.begin(), t.end(), cmp);
	int loc = lower_bound(t.begin(), t.end(), make_pair(start,0)) - t.begin();
	for (int i = loc; i < n; i++) {
		cout << char('A' + t[i].second) << " ";
		if(i == loc) {
			num += abs (t[i] . first - start);
		} else {
			num += abs (t[i] . first - t[i - 1] . first);
		}
	}
	for (int i = loc-1; i >= 0; i--) {
		cout << char('A' + t[i].second) << " ";
		if(i == loc - 1) {
			num += abs(t[n-1].first - t[loc - 1].first);//转头回来
		} else {
			num += abs (t[i] . first - t[i + 1] . first);
		}
	}
	cout << "\n电梯调度平均移动道数:" << (double)num / n;
}
int main() {
	FCFS();
	SSTF();
	LIFT();
	return 0;
}
