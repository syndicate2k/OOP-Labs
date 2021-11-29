#include <iostream>

using namespace std;

class Deque {
		int *data; 
		int n; 
		int size; 
		int head; 
		int tail; 

	public:
		Deque(int maxsize = 100); 
		~Deque(); 

		void addleft(int); 
		void addright(int); 

		int getleft(); 
		int getright();

		void delleft(); 
		void delright();

		bool isEmpty(); 
		bool isFull(); 
		void print(); 
};

Deque::Deque(int s): data(new int[s]), size(s), n(0), head(0), tail(0) {}

Deque::~Deque() {
	delete[] data;
}

void Deque::addright(int x) {
	if(isFull()) {
		cout<< "Deque is full" << endl;

		exit(1);
	}

	data[tail] = x;
	tail = (tail + 1) % size;

	n++;
}

void Deque::addleft(int x) {
	if(isFull()) {
		cout<< "Deque is full" << endl;

		exit(1);
	}


	head = (head - 1 + size) % size;
	data[head] = x;

	n++;
}

int Deque::getleft() {
	if(isEmpty()) {
		cout<< "Deque is empty" << endl;

		exit(1);
	}

	return data[head];
}

int Deque::getright() {
	if(isEmpty()) {
		cout<< "Deque is empty" << endl;

		exit(1);
	}

	return data[(tail + size - 1) % size];
}

void Deque::delleft() {
	if(isEmpty()) {
		cout<< "Deque is empty" << endl;

		return;
	}

	head = (head + 1) % size;
	n--;
}

void Deque::delright() {
	if(isEmpty()) {
		cout<< "Deque is empty" << endl;

		return;
	}

	tail = (tail + size - 1) % size;
	n--;
}

bool Deque::isEmpty() {
	return n == 0;
}

bool Deque::isFull() {
	return n == size;
}

void Deque::print() {
	for(int i = 0; i < n; i++) {
		cout << data[(head + i) % size] << " ";
	}
	cout << endl;

	return;
}

int main() {
	return 0;
}
