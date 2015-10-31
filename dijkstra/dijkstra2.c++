#include <iostream> //cin, cout
#include <string> // getline, string
#include <sstream>
#include <vector>
#include <map>
#include <utility>
#include <limits.h>

#define INF 9223372036854775807
using namespace std;
typedef map<long,long long int>::iterator node_iter;

class node {
public:
	long long int cost = INF;
	long prev;
	map<long,long> neighbors;
	node (const long& n) : prev(n) {}
};

void print_costs(map<long, long long int>& costs, vector<node>& nodes) {
	for (node_iter iter = costs.begin(); iter != costs.end(); iter++) {
		cout << iter->first << ", ";
		cout << iter->second << ", prev = ";
		cout << nodes[iter->first-1].prev << endl;
	}
	cout << "---" << endl;
}

void print_path(vector<node>& nodes){
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

void update_costs(map<long,long long int>& costs, vector<node>& nodes, long& current_pos) {
	for (map<long,long>::iterator iter = nodes[current_pos-1].neighbors.begin(); iter != nodes[current_pos-1].neighbors.end(); iter++) {
		long neighbor = iter->first;
		long weight = iter->second;
		if ((costs.find(neighbor) == costs.end() && costs[current_pos] + weight < nodes[neighbor-1].cost) ||
			(costs[current_pos] + weight < costs[neighbor])) {
			nodes[neighbor-1].cost = costs[current_pos] + weight;
			nodes[neighbor-1].prev = current_pos;
			costs[neighbor] = nodes[neighbor-1].cost;
		}
		if (costs[neighbor] == 0) { costs.erase(neighbor);}
	}
	costs.erase(current_pos);
}

long get_min_cost(map<long,long long int>& costs) {
	long min_key = costs.begin()->first;
	for (node_iter iter = costs.begin(); iter != costs.end(); iter++) {
		if (iter->second <= costs[min_key]) {
			min_key = iter->first;
		}
	}
	return min_key;
}

int main(){
	string s;
	long num_of_nodes, num_of_edges;
	getline(cin, s);
	istringstream sin(s);
	sin >> num_of_nodes >> num_of_edges;

	map<long,long long int> costs;
	vector<node> nodes;

	for (long i=1; i<=num_of_nodes; ++i) {
		node n(i);
		nodes.push_back(n);
		if (i == 1) {
			nodes[i-1].prev = i;
			nodes[i-1].cost = 0;
			costs[i] = 0;
		}
	}

	for (long i=0; i<num_of_edges; ++i) {
		getline(cin, s);
		istringstream sin(s);
		long b, e, w;
		sin >> b >> e >> w;
		nodes[b-1].neighbors[e] = w;
		nodes[e-1].neighbors[b] = w;
	}

	long current_pos;
	while (!costs.empty()) {
		current_pos = get_min_cost(costs);
		// cout << "current_pos = " << current_pos << endl;
		update_costs(costs, nodes, current_pos);
		// print_costs(costs, nodes);
		if (current_pos == num_of_nodes) {
			print_path(nodes);
			return 0;
		}
	}

	cout << -1 << endl;
	return 0;	
}