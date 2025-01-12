#include <iostream>
#include <vector>

using namespace std;

int main() {
	int N;
	cin >> N;
	vector<long long> A(N);

	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}

	long long count = 0;
	for (int j = 0; const auto & a : A) {
		while (j < N && A[j] * 2 <= a) j++;
		count += j;
	}
	cout << count << endl;
}
