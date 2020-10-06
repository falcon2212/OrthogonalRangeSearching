#include "layeredRangeTree.h"
using namespace project;
using namespace std;
#include <iostream>
#include <string.h>
#include <map>
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

const int INF = 1e9;
bool compSC(data a, data b){
	if(a.sc < b.sc) return true;
	if(a.sc == b.sc && a.pc < b.pc) return true;
	return false;
}
layeredRangeTreeNode::layeredRangeTreeNode(){
	value = data(0,0);
	isLeaf = false;
}
layeredRangeTreeNode::~layeredRangeTreeNode(){
	value = data(0,0);
	isLeaf = false;
}
layeredRangeTreeNode::layeredRangeTreeNode(const data& v){
	value = v;
	isLeaf = false;
}
layeredRangeTreeNode* layeredRangeTree::findSplitNode(int l, int r){
	layeredRangeTreeNode *v = root;
	data pcv = (v->value);
	data L(l, -1*INF), R(r, INF);
	while(!(v->isLeaf) && (R <= pcv || L > pcv)){
		if(R <= pcv)
			v = v->left;
		else
			v = v->right;
		pcv = (v->value);
	}
	return v;  
}
layeredRangeTree::layeredRangeTree(std::vector<data> p, int pc, int sc){
	a = p;
	int n = a.size();
	for(int i = 0; i < (int)a.size(); i++){
		a[i].setPrimaryCoordinate(pc);
	} 
	vis = *(new vector<bool>(n, false));
	sortedPC = a;
	sortedSC = a;
	sort(sortedPC.begin(), sortedPC.end());
	sort(sortedSC.begin(), sortedSC.end(), compSC);
	build(sortedPC, sortedSC, root);
}
layeredRangeTree::~layeredRangeTree(){
	a.clear();
	sortedPC.clear();
	sortedSC.clear();
	vis.clear();
}
void layeredRangeTree::build(std::vector<data>& a, std::vector<data>& b, layeredRangeTreeNode* &root){
	int l = 0;
	int r = a.size()-1;
	if(l > r)
		root = NULL;
	else if( l == r ){
		root = (new layeredRangeTreeNode(data(a[l])));
		root->isLeaf = true;
		(root->sortedSC) = *(new vector<data>(b));
		root->size = 1;
	}
	else{
		int m = (l+r)/2;
		// building the current node
		root = (new layeredRangeTreeNode(data(a[m])));
		(root->sortedSC) = *(new vector<data>(b));
		root->size = a.size();

		// partitioning the point set based on primary coordinate
		std::vector<data> leftPC, rightPC;
		std::vector<data> leftSC, rightSC;
		for(int i = 0; i <= r; i++){
			if(i <= m){
				vis[a[i].id] = true;
				leftPC.push_back(a[i]);
			} 
			else
				rightPC.push_back(a[i]);
		}
		for(int i = 0; i <= r; i++){
			if(vis[b[i].id] == true){
				leftSC.push_back(b[i]);
				vis[b[i].id] = false;
			} 
			else rightSC.push_back(b[i]);
		}
		int ptr1 = 0;
		int ptr2 = 0;
		int ptr3 = 0;
		root->ptrToChild_L = {};
		root->ptrToChild_R = {};
		// computing the pointers used in fractional cascading
		while(ptr1 < b.size()){
			while(ptr2<leftSC.size() && compSC(leftSC[ptr2],b[ptr1])) ptr2++;
			if(ptr2 == leftSC.size()) ptr2 = 1e9;
			root->ptrToChild_L.push_back(ptr2);			
			ptr1++;
		}
		ptr1 = 0;
		while(ptr1 < b.size()){
			while(ptr3<rightSC.size() && compSC(rightSC[ptr3],b[ptr1])) ptr3++;
			if(ptr3 == rightSC.size()) ptr3 = 1e9;
			root->ptrToChild_R.push_back(ptr3);			
			ptr1++;
		}
		build(leftPC, leftSC, root->left);
		build(rightPC, rightSC, root->right);
	}
}
std::vector<data> layeredRangeTree::query(std::pair<double, double> pcRange,std::pair<double, double> scRange){
	int l = pcRange.first, r = pcRange.second;
	data L(l, -1*INF), R(r, INF);
	data LL(-1*INF, scRange.first), RR(INF, scRange.second);
	layeredRangeTreeNode *splitNode = findSplitNode(l, r);
	int lo = -1, hi = splitNode->sortedSC.size();
	while(lo+1 < hi){
		int mid = (lo+hi)/2;
		if(splitNode->sortedSC[mid].sc < scRange.first)
			lo = mid;
		else
			hi = mid;
	}
	int it1 = (splitNode->ptrToChild_L)[hi];
	vector<data> ans = {};
	if(splitNode->isLeaf){
		if( l <= (splitNode->value).pc && (splitNode->value).pc <= r)
			if(scRange.first <= (splitNode->value).sc && (splitNode->value).sc <= scRange.second)
				ans.push_back(splitNode->value);
	}
	else{
		layeredRangeTreeNode *v = splitNode->left;
		int it = (splitNode->ptrToChild_L)[hi];

		while(!(v->isLeaf)){
		if(it == 1e9) break;
			if(L <= v->value){
				int t = ((v->ptrToChild_R)[it]);
				while(t<v->right->sortedSC.size()){
					if(!compSC(v->right->sortedSC[t], RR)) break;
					ans.push_back(v->right->sortedSC[t]);
					t++;
				}
				it = (v->ptrToChild_L)[it];
				v = v->left;
			}
			else{
				it = (v->ptrToChild_R)[it];
				v = v->right;
			}
		}
		if(v->isLeaf){
			if(l <= (v->value).pc && (v->value).pc <= r)
				if(scRange.first <= (v->value).sc && (v->value).sc <= scRange.second)
					ans.push_back(v->value);
		}
		v = splitNode->right;
		it = (splitNode->ptrToChild_R)[hi];
		while(!(v->isLeaf)){
		if(it == 1e9) break;
			if(v->value < R){
				int t = ((v->ptrToChild_L)[it]);
				while(t<v->left->sortedSC.size()){
					if(!compSC( v->left->sortedSC[t], RR)) break;
					ans.push_back(v->left->sortedSC[t]);
					t++;
				}
				it = (v->ptrToChild_R)[it];
				v = v->right;
			}
			else{
				it = (v->ptrToChild_L)[it];
				v = v->left;
			}
		}
		if(v->isLeaf){
			if(l <= (v->value).pc && (v->value).pc <= r)
				if(scRange.first <= (v->value).sc && (v->value).sc <= scRange.second)
					ans.push_back(v->value);
		}
	}
	return ans;
}
