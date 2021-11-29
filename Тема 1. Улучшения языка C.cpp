#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

int main() {
	srand(time(0));

	int n;
	cin >> n;

	int a, b;
	cin >> a >> b;

	int *arr = new int[n];

	for (int i = 0; i < n; i++) {
		arr[i] = rand() % (b - a + 1) + a;

		cout << arr[i] << " ";
	}
	cout << endl;

	for(int i = 0; i < n - 1; i++) {
		if(arr[i] >= arr[i + 1]) {
			cout << i << " ";
		}
		
		while(i < n - 1 && arr[i] >= arr[i + 1]) {
			i++;
		}
	}

	delete[] arr;
	return 0;
}
