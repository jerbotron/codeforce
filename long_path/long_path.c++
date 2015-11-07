#include <iostream> 	// cin, cout, getline
#include <sstream> 		// istringstream
#include <string> 		// string
#include <vector> 		// vector
#include <algorithm> 	// sort

using namespace std;

int main(){
	string s;
	unsigned int n;
	istringstream iss;

	getline(cin, s);
	iss.str(s);
	iss >> n;
	vector<unsigned int> rooms(n);
	vector<unsigned int> crosses(n, 0);
	vector<unsigned long long> next_room(n, 0);
	iss.clear();

	getline(cin, s);
	iss.str(s);
	for (unsigned int i = 0; i < n; ++i) {
		iss >> rooms[i];
	}

	unsigned int cur_room = 1;
	unsigned long long num_of_moves = 0;
	unsigned long long temp = 0;

	while (cur_room != n+1) {
		if (crosses[cur_room-1] == 0) {
			// Go through portal 2 to rooms[cur_room-1]
			if (next_room[cur_room-1] != 0) {
				num_of_moves = (num_of_moves + next_room[cur_room-1]) % 1000000007;
				temp = (temp + next_room[cur_room-1]) % 1000000007;
				++cur_room;
			}
			else {
				crosses[cur_room-1] = 1;
				cur_room = rooms[cur_room-1];
				temp = (temp + 1) % 1000000007;
				num_of_moves = (num_of_moves + 1) % 1000000007;
			}
		}
		else {
			// Go through portal 1 to cur_room+1
			crosses[cur_room-1] = 0;
			if (next_room[cur_room-1] == 0) {
				temp = (temp + 1) % 1000000007;
				next_room[cur_room-1] = temp;
				temp = 0;
			}
			++cur_room;
			num_of_moves = (num_of_moves + 1) % 1000000007;
		}
	}

	cout << num_of_moves << endl;
	return 0;
}