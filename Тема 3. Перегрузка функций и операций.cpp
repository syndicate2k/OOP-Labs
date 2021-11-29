#include <iostream>

using namespace std;

class Time {
		int sec;
	public:
		Time(int h = 0, int m = 0, int s = 0): sec(h * 3600 + m * 60 + s) {}

		int getHour() const;
		int getMin() const;
		int getSec() const;

		friend istream& operator >> (istream &in, Time&);
		friend ostream& operator << (ostream &out, Time);

		friend bool operator == (Time a, Time b);
		friend bool operator ! (Time a);
		friend bool operator > (Time a, Time b);
		friend bool operator >= (Time a, Time b);
		friend bool operator < (Time a, Time b);
		friend bool operator <= (Time a, Time b);

		Time& operator += (Time t);
		Time& operator -= (Time t);
		Time& operator *= (int z);
		Time& operator /= (int z);
		Time& operator =(Time t);
};

int Time::getHour() const {
	return sec / 3600;
}

int Time::getMin() const {
	return sec / 60 % 60;
}

int Time::getSec() const {
	return sec % 60;
}

istream& operator >> (istream &in, Time &t) {
	int h, s, m;
	char symb;

	in >> h >> symb >> s >> symb >> m;

	t = Time(h, s, m);

	return in;
}

ostream& operator << (ostream &out, Time t) {
	string r = to_string(t.getHour()) + ":";

	if(t.getMin() < 10) r += "0";
	
	r += to_string(t.getMin());
	r += ":";

	if(t.getSec() < 10) r += "0";
	r += to_string(t.getSec());

	return out << r;
}


inline bool operator == (Time a, Time b) {
	return a.sec == b.sec;
}

inline bool operator ! (Time a) {
	return a.sec == 0;
}

inline bool operator > (Time a, Time b) {
	return a.sec > b.sec;
}

inline bool operator >= (Time a, Time b) {
	return a.sec >= b.sec;
}

inline bool operator < (Time a, Time b) {
	return a.sec < b.sec;
}

inline bool operator <= (Time a, Time b) {
	return a.sec <= b.sec;
}


Time &Time::operator = (Time t) {
	sec = t.sec;
	return *this;
}

Time &Time::operator += (Time t) {
	sec += t.sec;
	return *this;
}

Time &Time::operator *= (int z) {
	sec *= z;
	return *this;
}

Time &Time::operator -= (Time t) {
	sec -= t.sec;
	return *this;
}

Time &Time::operator /= (int z) {
	sec /= z;
	return *this;
}

inline Time operator + (Time a, Time b) {
	return a += b;
}

inline Time operator - (Time a, Time b) {
	return a -= b;
}

inline Time operator * (Time a, int z) {
	return a *= z;
}

inline Time operator / (Time a, int z) {
	return a /= z;
}

inline bool operator != (Time a, Time b) {
	return !(a == b);
}

int main() {
	return 0;
}
