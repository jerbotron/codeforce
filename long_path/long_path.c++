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
}