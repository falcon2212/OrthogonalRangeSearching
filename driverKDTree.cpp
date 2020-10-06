// #include "rangeTree.h"
#include "kdTree.h"
using namespace project;
using namespace std;
#include <bits/stdc++.h>
int main()
{
	int n, m;
	cin >> n;
	vector<data> p;
	for(int i = 0; i < n; i++){
		double x, y;
		cin >> x >> y;
		p.push_back(data(x, y, i));
	}
	kdTree tree(p, 1);
	// printf("here\n");
	cin >> m;
	int m1 = m;
	map<pair<double, double>, bool> vis;
	vector<vector<double>> queries;
	while(m--){
		double u1, u2, v1, v2;
		cin >> u1 >> v1 >> u2 >> v2;
		queries.push_back({u1,v1,u2,v2});
		// std::vector<data> v = tree.query(tree.root,{u1,u2},{v2, v1});
		// for (int i = 0; i < v.size(); ++i)
		// {
		// 	vis[{v[i].x, v[i].y}] = 1; 
		// 	// printf("%f %f \n",v[i].x, v[i].y );
		// }
		int ans= tree.queryCnt(tree.root,{u1,u2},{v2, v1});
		printf("%d\n",ans );
	}
	// cout<<n<<endl;
	// for(int i = 0; i < n; i++){
	// 	cout<<p[i].x<<" "<<p[i].y<<" "<<vis[{p[i].x, p[i].y}]<<endl;
	// }
	// cout<<m1<<endl;
	// for(int i = 0; i < m1; i++){
	// 	cout<<queries[i][0]<<" "<<queries[i][1]<<" "<<queries[i][2]<<" "<<queries[i][3]<<endl;
	// }
	return 0;
}	