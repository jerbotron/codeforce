#include <iostream> 	// cin, cout, getline
#include <sstream> 		// istringstream
#include <string> 		// string
#include <vector> 		// vector
#include <algorithm> 	// sort

using namespace std;
typedef map<int,int>::iterator iter;
bool my_compare(int i, int j) { return i > j; }

int find_team(int x, vector<vector<int>>& teams) {
	for (unsigned int i=0; i<teams.size(); ++i) {
		if (teams[i].size() > 0) {
			for (unsigned int j=0; j<teams[i].size(); ++j) {
				if (teams[i][j] == x && teams[i].size() < 3)
					return i;
			}
		}
	}
	return -1;
}

bool assigned_to_team(int&& x, vector<vector<int>>& teams) {
	for (unsigned int i=0; i<teams.size(); ++i) {
		if (teams[i].size() < 3) {
			teams[i].push_back(x);
			return true;
		}
	}
	return false;
}

void print_teams(vector<vector<int>>& teams) {
	for (unsigned int i=0; i<teams.size(); ++i) {
		sort(teams[i].begin(), teams[i].end(), my_compare);
		cout << teams[i][0] << " " << teams[i][1] << " " << teams[i][2] << endl;
	}
}

int main(){
	string s;
	unsigned int n, m;
	istringstream iss;

	getline(cin, s);
	iss.str(s);
	iss >> n >> m;
	iss.clear();
	map<int,int> friends;
	vector<int> assigned(n, 0);
	vector<vector<int>> teams(n/3);
	bool failed = false;

	for (unsigned int i=0; i<m; ++i) {
		getline(cin, s);
		unsigned int x, y;
		iss.str(s);
		iss >> x >> y;
		iter temp = friends.find(x);
		if (temp != friends.end()) { friends[y] = x; }
		else { friends[x] = y; }
		iss.clear();
	}

	for (iter pair = friends.begin(); pair != friends.end(); ++pair) {
		bool team_found = false;
		if (assigned[pair->first-1] == 0 && assigned[pair->second-1] == 0) {
			assigned[pair->first-1] = 1;
			assigned[pair->second-1] = 1;
			for (unsigned int x=0; x<teams.size(); ++x) {
				if (teams[x].size() == 0) {
					teams[x].push_back(pair->first);
					teams[x].push_back(pair->second);
					team_found = true;
					break;
				}
			}
			if (!team_found) { 
				failed = true; 
				break; 
			}
		}
		else {
			int single_student = -1;
			int friend_student = -1;
			if (assigned[pair->first-1] == 0 && assigned[pair->second-1] == 1) { 
				single_student = pair->first; 
				friend_student = pair->second;
			}
			else if (assigned[pair->first-1] == 1 && assigned[pair->second-1] == 0) { 
				single_student = pair->second; 
				friend_student = pair->first;
			}

			if (single_student != -1) {
				int friend_team = find_team(friend_student, teams);
				if (friend_team != -1) { 
					teams[friend_team].push_back(single_student);
					assigned[single_student-1] = 1;
				}
				else {
					failed = true;
					break;
				}
			}
			else {
				if (find_team(pair->first, teams) != find_team(pair->second, teams)) {
					failed = true;
					break;
				}
			}
		}
	}

	for (unsigned int i=0; i<n; ++i) {
		if (assigned[i] == 0) { 
			if (!assigned_to_team(i+1, teams)) { 
				failed = true; 
				break; 
			} 
		}
	}

	if (failed) { cout << -1 << endl; }
	else { print_teams(teams); }

	return 0;
}