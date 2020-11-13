#include "kdTree.h"
#include <algorithm>
using namespace project;
using namespace std;
#include <iostream>
#include <string.h>
#include <map>

// Uncomment this section to enable debugging functions
#define ss second
#define ff first
#define tr(...) cerr<<__FUNCTION__<<' '<<__LINE__<<" = ";trace(#__VA_ARGS__, __VA_ARGS__)
template<typename S, typename T> 
ostream& operator<<(ostream& out,pair<S,T> const& p){out<<'('<<p.ff<<", "<<p.ss<<')';return out;}
template<typename T>
ostream& operator<<(ostream& out,vector<T> const& v){
int l=v.size();for(int i=0;i<l-1;i++)out<<v[i]<<' ';if(l>0)out<<v[l-1];return out;}
template<typename T>
void trace(const char* name, T&& arg1){cout<<name<<" : "<<arg1<<endl;}
template<typename T, typename... Args>
void trace(const char* names, T&& arg1, Args&&... args){
const char* comma = strchr(names + 1, ',');cout.write(names, comma-names)<<" : "<<arg1<<" | ";trace(comma+1,args...);}


const double MIN = -1.0*1e9;
const double MAX = 1.0*1e9;

bool compSC(data a, data b){
	if(a.sc < b.sc) return true;
	if(a.sc == b.sc && a.pc < b.pc) return true;
	return false;
}
kdTreeNode::kdTreeNode(){
	l = MIN;
	r = MAX;
	u = MAX;
	d = MIN;
	isLeaf = false;
	left=NULL;
	right = NULL;
}
kdTreeNode::~kdTreeNode(){
	l = MIN;
	r = MAX;
	u = MAX;
	d = MIN;
	isLeaf = false;
	left=NULL;
	right = NULL;
}
kdTreeNode::kdTreeNode(double l1, double r1, double u1, double d1, const data& v1){
	l = l1;
	r = r1;
	u = u1;
	d = d1;
	isLeaf = false;
	left = NULL;
	right = NULL;
	value = v1;
}
kdTreeNode::kdTreeNode(const kdTreeNode& n){
	l = n.l;
	r = n.r;
	u = n.u;
	d = n.d;
	isLeaf = n.isLeaf;
	left = n.left;
	right = n.right;
	value = n.value;
}
vector<double> kdTreeNode::getRegion(){
	return {l, r, u, d};
}
kdTree::kdTree(){
	p = {};
	root = NULL;
}
kdTree::kdTree(std::vector<data> a, int pc){
	p = a;
	int n = a.size();
	for(int i = 0; i < (int)p.size(); i++) p[i].setPrimaryCoordinate(pc);
	vis = *(new vector<bool>(n, false));	
	sortedPC = p;
	sortedSC = p;
	primaryCoordinate = pc;
	sort(sortedPC.begin(), sortedPC.end());
	p = sortedPC;
	sort(sortedSC.begin(), sortedSC.end(), compSC);
	
	build(sortedPC, sortedSC, 0, root, {MIN, MAX, MAX, MIN});
}
kdTree::~kdTree(){
	p.clear();
	sortedPC.clear();
	sortedSC.clear();
	vis.clear();
	root = NULL;
}
void kdTree::build(vector<data>& a, vector<data>& b, int depth, kdTreeNode* &root, vector<double> boundaries){
	int l = 0, r = (int)a.size()-1;
	// tr(l, r);
	if(l > r) root = NULL;
	else if(l == r){
		double ln,rn,un,dn;
		ln = boundaries[0];
		rn = boundaries[1];
		un = boundaries[2];
		dn = boundaries[3];
		root = new kdTreeNode(ln, rn, un, dn, data(a[0]));
		root->isLeaf = true;
		root->size = 1;
	}
	else{
		double ln,rn,un,dn;
		ln = boundaries[0];
		rn = boundaries[1];
		un = boundaries[2];
		dn = boundaries[3];
		vector<double> leftBoundary, rightBoundary;
		int m = (l+r)/2;
		vector<data> left, right;
		vector<data> lefty, righty;
		data dt;
		data median;
		if(depth&1){
			median = b[m];
			for(int i = 0; i <= r; i++){
				if(compSC(b[i], median)){
					lefty.push_back(b[i]);
					vis[b[i].id] = 1;
				}
				else
					righty.push_back(b[i]);
			}
			for(int i = 0;  i <= r; i++){
				if(vis[a[i].id]){
					vis[a[i].id] = 0;
					left.push_back(a[i]);
				}
				else 
					right.push_back(a[i]);
			}
			leftBoundary = {ln, rn, median.sc, dn};
			rightBoundary = {ln, rn, un, median.sc};
		} 
		else{
			median  = a[m];
			for(int i = 0; i <= r; i++){
				if(a[i] <= median){
					left.push_back(a[i]);
					vis[a[i].id] = 1;
				}
				else
					right.push_back(a[i]);
			}
			for(int i = 0; i <= r; i++){
				if(vis[b[i].id]){
					vis[b[i].id] = 0;
					lefty.push_back(b[i]);
				}
				else
					righty.push_back(b[i]);
			}
			leftBoundary = {ln, median.pc, un, dn};
			rightBoundary = {median.pc, rn, un, dn};
		} 
		root = new kdTreeNode(ln, rn, un, dn, median);
		root->size = a.size();
		build(left, lefty, depth+1, root->left, leftBoundary);
		build(right, righty, depth+1, root->right, rightBoundary);
	}

}
vector<data> reportSubTree(kdTreeNode* root){
	if(root == NULL) return {};
	else if(root->isLeaf){
		return {root->value};
	}
	else{
		vector<data> left = reportSubTree(root->left);
		vector<data> right = reportSubTree(root->right);
		for(int i = 0; i < (int)right.size(); i++)
			left.push_back(right[i]);
		return left;
	}
}
// returns true if a lies completly with in b
bool liesWithIn(vector<double> a, vector<double> b){
	return a[0] >= b[0] && a[1] <= b[1] && a[2] <= b[2] && a[3] >= b[3];
}
bool intersect(vector<double> a, vector<double> b){
	return (max(a[0], b[0]) <= min(a[1], b[1])) && (max(a[3], b[3]) <= min(a[2], b[2]));
}
vector<data> kdTree::query(kdTreeNode* root, pair<double, double> pcRange, pair<double, double> scRange){
	vector<double> qry = {pcRange.first, pcRange.second, scRange.first, scRange.second};
	kdTreeNode *v = root;
	if(v == NULL) return {};
	else if(v->isLeaf){
		if(liesWithIn({v->value.pc, v->value.pc, v->value.sc, v->value.sc}, qry))
			return {v->value};
		else
			return {};
	}
	else{
		vector<double> curr = v->getRegion();
		vector<double> left = {MAX,MAX, MAX, MAX};
		if(v->left != NULL)
			left = v->left->getRegion();
		vector<double> right = {MAX,MAX, MAX, MAX};
		if(v->right != NULL)
			right = v->right->getRegion();
		vector<data> ans;
		if(liesWithIn(left, qry)){
			vector<data> t = reportSubTree(v->left);
			for(int i = 0; i < (int)t.size(); i++)
				ans.push_back(t[i]);
		}
		else if(intersect(left, qry)){
			vector<data> t = query(v->left, pcRange, scRange);
			for(int i = 0; i < (int)t.size(); i++)
				ans.push_back(t[i]);
		}
		if(liesWithIn(right, qry)){
			vector<data> t = reportSubTree(v->right);
			for(int i = 0; i < (int)t.size(); i++)
				ans.push_back(t[i]);
		}
		else if(intersect(right, qry)){
			vector<data> t = query(v->right, pcRange, scRange);
			for(int i = 0; i < (int)t.size(); i++)
				ans.push_back(t[i]);
		}
		return ans;
	}
}
int kdTree::queryCnt(kdTreeNode* root, pair<double, double> pcRange, pair<double, double> scRange){
	vector<double> qry = {pcRange.first, pcRange.second, scRange.first, scRange.second};
	kdTreeNode *v = root;
	if(v == NULL) return 0;
	else if(v->isLeaf){
		if(liesWithIn({v->value.pc, v->value.pc, v->value.sc, v->value.sc}, qry))
			return 1;
		else
			return 0;
	}
	else{
		vector<double> curr = v->getRegion();
		vector<double> left = {MAX,MAX, MAX, MAX};
		if(v->left != NULL)
			left = v->left->getRegion();
		vector<double> right = {MAX,MAX, MAX, MAX};
		if(v->right != NULL)
			right = v->right->getRegion();
		int ans = 0;
		if(liesWithIn(left, qry)){
			ans += v->left->size;
		}
		else if(intersect(left, qry)){
			ans += queryCnt(v->left, pcRange, scRange);
		}
		if(liesWithIn(right, qry)){
			ans += v->right->size;
		}
		else if(intersect(right, qry)){
			ans+= queryCnt(v->right, pcRange, scRange);
		}
		return ans;
	}
}
