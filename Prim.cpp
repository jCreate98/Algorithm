#include <iostream>
#include <vector>

using namespace std;

class PQ
{
	pair<int, int> arr[1000];
	int cnt;
public:

	PQ() {
		cnt = 0;
	}

	int get_number(void) {
		return cnt;
	}

	void insert(pair<int, int> input) {
		if (cnt < 0)
		{
			cnt = 0;
		}
		int i = cnt + 1;
		arr[i] = input;
		pair<int, int> temp;
		while (i != 1)
		{
			if (arr[i / 2].second <= arr[i].second)
			{
				break;
			}
			else {
				temp = arr[i / 2];
				arr[i / 2] = arr[i];
				arr[i] = temp;
				i = i / 2;
			}
		}
		cnt++;
		return;
	}

	pair<int, int> del() {
		int i = 1;
		pair<int, int> answer = arr[1];
		pair<int, int> temp;
		arr[1] = arr[cnt--];
		if (cnt < 0)
		{
			temp.first = 0;
			temp.second = 0;
			return temp;
		}
		while (i * 2 <= cnt)
		{
			if (i * 2 + 1 < cnt) {
				if (arr[i].second >= arr[2 * i].second || arr[i].second >= arr[2 * i + 1].second)
				{
					if (arr[2 * i].second >= arr[2 * i + 1].second) {
						temp = arr[2 * i + 1];
						arr[2 * i + 1] = arr[i];
						arr[i] = temp;
						i = 2 * i + 1;
					}
					else {
						temp = arr[2 * i];
						arr[2 * i] = arr[i];
						arr[i] = temp;
						i = 2 * i;
					}
				}
				else 
				{
					i = 2 * i;
				}
			}
			else if (cnt % 2 == 1)
			{
				if (arr[i].second >= arr[2 * i].second || arr[i].second >= arr[2 * i + 1].second)
				{
					if (arr[2 * i].second > arr[2 * i + 1].second) {
						temp = arr[2 * i + 1];
						arr[2 * i + 1] = arr[i];
						arr[i] = temp;
						break;
					}
					else {
						temp = arr[2 * i];
						arr[2 * i] = arr[i];
						arr[i] = temp;
						break;
					}
				}
				break;
			}
			else {
				if (arr[i].second >= arr[2 * i].second)
				{
					temp = arr[2 * i];
					arr[2 * i] = arr[i];
					arr[i] = temp;
					break;
				}
				else
					break;
			}
		}
		return answer;
	}
};

void Prim()
{
	PQ priority;
	int n_nodes;
	int n_edges;
	int mark[1000] = { 0 };
	int resent = 1;
	int first, second, weight;
	pair<int, int> temp;
	vector<pair<int, int>> input[1000];
	int total = 0;

	cout << "The number of Nodes = ";
	cin >> n_nodes;
	cout << "The number of Edges = ";
	cin >> n_edges;

	for (int i = 0; i < n_edges; i++)
	{
		cin >> first >> second >> weight;
		input[second].push_back(make_pair(first, weight));
		input[first].push_back(make_pair(second, weight));
	}

	mark[1] = 1;

	for (int fin = 1; fin < n_nodes; fin++)
	{
		for (unsigned int i = 1; i <= (unsigned int)input[resent].size(); i++)
		{
				priority.insert(make_pair(input[resent].at(i-1).first, input[resent].at(i-1).second));
				// 새로 연결된 엣지 들을 집어 넣는다. // 기존의 엣지는 priority queue 에 있기 때문에 다시 넣을 필요 없다.
		} // add edges to priority queue

		while (true)
		{
			temp = priority.del();
			if (mark[temp.first] == 1)
			{
				continue;
			}
			else {
				cout << "노드 : " << temp.first << " 거리 : " << temp.second << " " << endl;
				total += temp.second;
				mark[temp.first] = 1;
				resent = temp.first;
				break;
			}
		}// priority queue out
	}
	cout << "Minimum Spanning Tree 비용 : " << total << endl;
	return;
}

int main() {
	Prim();
	return 0;
}
/*
5 8
1 2 5
1 3 4 
1 5 6
2 3 2
2 4 1
2 5 10
3 4 7
4 5 2
*/