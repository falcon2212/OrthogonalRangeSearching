#include "layeredRangeTree.h"
using namespace project;
using namespace std;
#include <iostream>
#include <map>
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);

	int n, m;
	cin >> n;
	vector<data> p;
	for(int i = 0; i < n; i++){
		double x, y;
		cin >> x >> y;
		p.push_back(data(x, y, i));
	}
	layeredRangeTree tree(p, 1, 2);
	cin >> m;
	int m1 = m;
	map<pair<double, double>, bool> vis;
	vector<vector<double>> queries;
	while(m--){
		double u1, u2, v1, v2;
		cin >> u1 >> v1 >> u2 >> v2;
		queries.push_back({u1,v1,u2,v2});
		std::vector<data> v = tree.query({u1,u2},{v1, v2});
		for (int i = 0; i < v.size(); ++i)
		{
			vis[{v[i].x, v[i].y}] = 1; 
			// printf("%f %f \n",v[i].x, v[i].y );
		}
	}
	cout<<n<<endl;
	for(int i = 0; i < n; i++){
		cout<<p[i].x<<" "<<p[i].y<<" "<<vis[{p[i].x, p[i].y}]<<endl;
	}
	cout<<m1<<endl;
	for(int i = 0; i < m1; i++){
		cout<<queries[i][0]<<" "<<queries[i][1]<<" "<<queries[i][2]<<" "<<queries[i][3]<<endl;
	}
	return 0;
}	