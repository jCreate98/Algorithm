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

	int get_number(void)
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

void Dijkstra() {
	PQ priority;
	int n_nodes;
	int n_edges;
	int mark[1000] = { 0 };
	int nodes_weights[1000] = { 0 };
	int resent = 1;
	int first, second, weight;
	pair<int, int> temp;
	vector<pair<int, int>> input[1000];

	cout << "The number of Nodes = ";
	cin >> n_nodes;
	cout << "The number of Edges = ";
	cin >> n_edges;

	for (int i = 0; i < n_edges; i++)
	{
		cin >> first >> second >> weight;
		input[second].push_back(make_pair(first, weight));
		input[first].push_back(make_pair(second, weight));
	} // 노드 입력 받기

	mark[1] = 1; // 처음을 1로 설정 // 입력 받을시 시작 위치 조정 가능

	for (int fin = 1; fin < n_nodes; fin++)
	{
		for (unsigned int i = 1; i <= (unsigned int)input[resent].size(); i++)
		{
			if (nodes_weights[input[resent].at(i - 1).first] == 0) {
				nodes_weights[input[resent].at(i - 1).first] = nodes_weights[resent] + input[resent].at(i - 1).second;
			} // 거리가 입력돼있지 않은 경우 덮어쓰기
			else if (nodes_weights[input[resent].at(i - 1).first] >= nodes_weights[resent] + input[resent].at(i - 1).second) {
				nodes_weights[input[resent].at(i - 1).first] = nodes_weights[resent] + input[resent].at(i - 1).second;
			} // 거리 비교해서 더 낮은 거리로 덮어쓰기
			priority.insert(make_pair(input[resent].at(i - 1).first, nodes_weights[input[resent].at(i - 1).first]));
			// 목표 노드와 거리를 priority queue 에 집어넣기.
		} // add nodes to priority queue

		while (true)
		{
			temp = priority.del();
			if (mark[temp.first] == 1)
			{
				continue;
			}
			else {
				cout << "노드: " << temp.first << " 거리 : " << temp.second << " " << endl;
				mark[temp.first] = 1;
				resent = temp.first;
				break;
			}
		} // priority queue out
	}
	return;
}

int main() {
	Dijkstra();
	return 0;
}