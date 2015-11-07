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

	sort(v.begin(), v.end(), my_compare);

	int i = 0;
	while (i < int(v.size())) {
		int t = v[i];
		for (unsigned int j = i+1; j < v.size(); ++j) {
			if (t % v[j] == 0 || t > l) {
				v.erase(v.begin()+i);
				i = -1;
				break;
			}
		}
		++i;
	}

	int origina_length = l;
	int pieces = 0, strategy = 0, temp_p = 0, temp_l = 0, counter = 0;
	// 0 = 0b00, 1 = 0b01, 2 = 0b10, 3 = 0b10

	while (l % v.back() != 0) {
		if (v.size() == 2) {
			l -= v[0];
			pieces += 1;
		}
		else {
			switch (strategy) {
				case 0:
					l-=v[1];
					pieces+=1;
					if (l % v.back() == 0 && pieces >= 2 && l >= 0) {
						temp_p = pieces;
						temp_l = l;
						strategy = 1;
						l = -1;
					}
					break;
				case 1:
					if (counter == 0) {
						l -= v[1];
						pieces += 1;
						counter = 2;
					}
					else if (counter == 2) {
						l += v[1];
						l -= v[0];
						counter = 3;
					}
					else if (counter == 3) {
						l -= v[1];
						pieces += 1;
						counter = 0;
					}
					break;
				case 2:
					l-=v[0];
					pieces+=1;
					if (l < 0 || (l >= 0 && l % v.back() == 0 && temp_p != 0 && temp_l >= l)) {
						pieces = temp_p;
						l = temp_l;
					}
					break;
			}
			if (l < 0 && strategy < 2) {
				l = origina_length;
				pieces = 0;
				++strategy;
			}
		}
	}

	if (l/v.back() + pieces >= temp_p + temp_l/v.back())
		pieces += l/v.back();
	else
		pieces = temp_p + temp_l/v.back();

	cout << pieces << endl;
	return 0;
}