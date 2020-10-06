#include "bst.h"
#include <iostream>
using namespace project;
using namespace std;
int main()
{
	int n, m;
	cin >> n;
	vector<data> p;
	for(int i = 0; i < n; i++){
		int x, y;
		cin >> x;
		p.push_back(data(x, y, i));
	}
	sort(p.begin(),p.end());
	bst tree(p, true);
	cin >> m;
	while(m--){
		double u, v;
		cin >> u >> v;
		int ans = tree.queryCnt({u,v});
		/*
		Uncomment to print the answer to the query
		// std::vector<data> v1 = tree.query({u,v});

		// for (int i = 0; i < v1.size(); ++i)
		// {
		// 	printf("%f ",v1[i].x );
		// }
		*/
		printf("%d\n", ans);
	}
	return 0;
}	
