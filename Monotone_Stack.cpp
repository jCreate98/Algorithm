#include <iostream>
#include <stack>

using namespace std;

long long highest(long long a, long long b) {
	if (a > b) {
		return a;
	}
	else return b;
}

int main(void) {
	stack<pair<long long, long long>> size;
	long long test;
	long long input;
	long long high = 0;

	while (true) {
		cin >> test;
		high = 0;

		if (test == 0) {
			break;
		}
		else {
			size.push(make_pair(-1, 0));

			for (long long i = 1; i <= test + 1; i++) {
				if (i == test + 1) {
					input = 0;
				}
				else {
					cin >> input;
				}

				if (input <= size.top().first) {
					while (size.top().first >= input) {
						high = highest(high, (size.top().first) * (i - size.top().second));
						size.pop();
					}
					high = highest(high, size.top().first * (i - size.top().second));
					size.push(make_pair(input, size.top().second + 1));
					size.push(make_pair(input, i));
				}
				else size.push(make_pair(input, i));
			}
		}
		cout << high << '\n';
		while (!size.empty()) {
			size.pop();
		}
	}
}
