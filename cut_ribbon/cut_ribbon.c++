#include <iostream> 	// cin, cout
#include <sstream> 		// istringstream, sin
#include <string> 		// string
#include <vector> 		// vector
#include <algorithm> 	// sort

using namespace std;

bool my_compare(int i, int j) { return i > j; }

int main(){
	string s;
	int l, a, b, c;
	getline(cin, s);
	istringstream sin(s);
	sin >> l >> a >> b >> c;

	vector<int> v = {a, b, c};

	if (a == b || a == c) {
		v.erase(v.begin());
	}
	if (b == c) {
		v.pop_back();
	}	

	sort(v.begin(), v.end(), my_compare);

	int pieces = 0;

	while (l != 0) {
		int r = accumulate(v.begin()+1, v.end(), 0);
		int m = l - r;
		int q = m / v[0];
		pieces += q;
		l -= q * v[0];
		v.erase(v.begin());
	}

	cout << pieces << endl;
}