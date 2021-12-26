#include <iostream>

using namespace std;

template <typename T>
class Queue {
		T *data;
		int start;
		int n;
		int size;
	public:
		Queue(int s): data(new T[s]),start(0), n(0), size(s) {}
		~Queue() {
			delete[] data;
		}
		Queue(const Queue<T>&);

		Queue<T> &operator=(const Queue<T> &);
		Queue<T> &operator<<(const T &);
		Queue<T> &operator>>(const T & );

		void print();
};

struct queueError {
	virtual ~queueError() {}
	virtual const char *what() const=0;
};

struct queueEmpty: queueError {
	const char *what() const {
		return "Queue is empty";
	}
};

struct queueFull: queueError {
	const char *what() const {
		return "Queue is full";
	}
};

template <typename T>
Queue<T>:: Queue(const Queue <T> &c):data(new T[c.size]), start(c.start), n(c.n), size(c.size) {
	for(int i = 0; i < c.n; i++) {
		data[(c.start + i) % size] = c.data[(c.start + i) % size];
	}
}

template <typename T>
Queue<T> &Queue<T>::operator << (const T &x) {
	if(n == size) throw queueFull();

	data[(start+n)%size]=x;
	n++;

	return *this;
}

template <typename T>
Queue<T> &Queue<T>::operator >> (const T &x) {
	if(n == 0) throw queueEmpty();

	start++;
	if(start==size) start=0;
	n--;

	return *this;
}

template <typename T>
Queue<T> &Queue<T>::operator = (const Queue<T> &c) {
	if(c.n > size) throw queueFull();
	n = c.n;
	start = c.start;

	for(int i = 0; i < n; i++) {
		data[(start + i) % size] = c.data[(start + i) % size];
	}

	return *this;
}

template<class T>
void Queue<T>::print() {

	for(int i=0; i<n; ++i) {
		cout << data[(start + i) % size]<< " ";
	}

	cout<< endl;
}

int main() {
	Queue<int> q(5);
	for(int i = 0; i < 5; i++) {
		int temp;
		cin >> temp;

		try {
			q << temp;
		} catch(queueError &e) {
			cout << e.what() << endl;
		}

	}
	try {
		while(1) {
			int temp;
			q >> temp;

			q.print();
		}
	} catch(queueError &e) {
		cout << endl;
		cout << e.what() << endl;
	}

	Queue<int> q1(10);
	for(int i = 0; i < 10; i++) {
		try {
			q1 << i;
		} catch(queueError &e) {
			cout << e.what() << endl;
		}
	}
	try {
		q = q1;
	} catch(queueError &e) {
		cout << e.what() << endl;
	}

}

