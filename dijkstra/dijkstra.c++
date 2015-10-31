#include <iostream> //cin, cout
#include <string> // getline, string
#include <sstream>
#include <vector>
#include <map>
#include <utility>
#include <limits.h>
#include <queue>

#define INF 9223372036854775807
using namespace std;
typedef map<long,long>::iterator node_iter;

class node {
public:
	long prev;
	map<long,long> neighbors;
};

vector<long long int> costs(100000);
vector<node> nodes;
priority_queue<pair<long,long>,vector<pair<long,long>>,greater<pair<long,long>>> min_cost;

// void print_costs(vector<long long int>& costs, vector<node>& nodes, priority_queue<pair<long,long>,vector<pair<long,long>>,greater<pair<long,long>>> min_cost) {
// 	// cout << "costs: " << endl;
// 	// for (u_int i = 0; i<costs.size(); ++i) {
// 	// 	cout << i+1 << ", ";
// 	// 	cout << costs.at(i) << ", prev = ";
// 	// 	cout << nodes[i].prev << endl;
// 	// }
// 	cout << "min_costs: " << endl;
// 	while(!min_cost.empty()) {
//         cout << min_cost.top().second << ", ";
// 		cout << min_cost.top().first << endl;
//         min_cost.pop();
//     }
// 	cout << "---" << endl;
// }

void print_path(){
	vector<long> v;
	long n = nodes.size();
	v.push_back(n);
	while (n != 1){
		n = nodes[n-1].prev;
		v.push_back(n);
	}
	for (long i=long(v.size()-1); i>=0; --i)
		cout << v[i] << " ";
	cout << endl;
}

void update_costs() {
	pair<long,long> p = min_cost.top();
	if (!min_cost.empty())
		min_cost.pop();
	if (p.first <= costs.at(p.second-1)) {
		for (node_iter iter = nodes[p.second-1].neighbors.begin(); iter != nodes[p.second-1].neighbors.end(); iter++) {
			if (costs.at(p.second-1) + iter->second < costs.at(iter->first-1)) {
				nodes[iter->first-1].prev = p.second;
				costs.at(iter->first-1) = costs.at(p.second-1) + iter->second;
				min_cost.push({costs.at(p.second-1) + iter->second, iter->first});
			}
		}
	}
}

int main(){
	string s;
	long num_of_nodes, num_of_edges;
	getline(cin, s);
	istringstream sin(s);
	sin >> num_of_nodes >> num_of_edges;

	for (long i=1; i<=num_of_nodes; ++i) {
		node n;
		nodes.push_back(n);
		if (i == 1) {
			nodes[i-1].prev = i;
			costs.at(i-1) = 0;
			min_cost.push({0,i});
		}
		else { costs.at(i-1) = INF; }
	}

	for (long i=0; i<num_of_edges; ++i) {
		getline(cin, s);
		istringstream sin(s);
		long b, e, w;
		sin >> b >> e >> w;
		nodes[b-1].neighbors[e] = w;
		nodes[e-1].neighbors[b] = w;
	}

	while (!min_cost.empty()) {
		update_costs();
		if (min_cost.top().second == num_of_nodes) {
			print_path();
			return 0;
		}
	}
	cout << -1 << endl;
	return 0;	
}