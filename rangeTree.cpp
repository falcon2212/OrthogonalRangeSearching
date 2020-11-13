#include "rangeTree.h"
using namespace project;
using namespace std;
#include <iostream>
#include <string.h>
#include <map>
#define ss second
#define ff first

const int INF = 1e9;
bool compSC(data a, data b){
	if(a.sc < b.sc) return true;
	if(a.sc == b.sc && a.pc < b.pc) return true;
	return false;
}
rangeTreeNode::rangeTreeNode(){
	value = data(0,0);
	isLeaf = false;
}
rangeTreeNode::~rangeTreeNode(){
	value = data(0,0);
	isLeaf = false;
}
rangeTreeNode::rangeTreeNode(const data& v){
	value = v;
	isLeaf = false;
}
rangeTreeNode* rangeTree::findSplitNode(int l, int r){
	rangeTreeNode *v = root;
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
rangeTree::rangeTree(std::vector<data> p, int pc, int sc){
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
rangeTree::~rangeTree(){
	a.clear();
	sortedPC.clear();
	sortedSC.clear();
	vis.clear();
}
void rangeTree::build(std::vector<data>& a, std::vector<data>& b, rangeTreeNode* &root){
	int l = 0;
	int r = a.size()-1;
	if(l > r)
		root = NULL;
	else if( l == r ){
		root = (new rangeTreeNode(data(a[l])));
		root->isLeaf = true;
		(root->Tassoc) = (new bst(b, 2));
		root->size = 1;
	}
	else{
		int m = (l+r)/2;
		// building the current node
		root = (new rangeTreeNode(data(a[m])));
		(root->Tassoc)=new bst(b, 2);
		root->size = a.size();
		// partitioning the point set based on secondary coordinate
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

		build(leftPC, leftSC, root->left);
		build(rightPC, rightSC, root->right);
	}
}
vector<data> reportSubtree1(bstNode* root){
	if (root == NULL)
		return {};
	else if(root->isLeaf){
		vector<data> ret;
		ret.push_back(root->value);
		return ret;
	}
	else{
		vector<data> left, right;
		left = reportSubtree1(root->left);
		right = reportSubtree1(root->right);
		for(int i = 0; i < (int)right.size(); i++)
			left.push_back(right[i]);
		return left;

	}
}

std::vector<data> rangeTree::query(std::pair<double, double> pcRange,std::pair<double, double> scRange){
	int l = pcRange.first, r = pcRange.second;
	data L(l, -1*INF), R(r, INF);

	rangeTreeNode *splitNode = findSplitNode(l, r);
	vector<data> ans = {};
	if(splitNode->isLeaf){
		if( l <= (splitNode->value).pc && (splitNode->value).pc <= r)
			if(scRange.first <= (splitNode->value).sc && (splitNode->value).sc <= scRange.second)
				ans.push_back(splitNode->value);
	}
	else{
		rangeTreeNode *v = splitNode->left;
		while(!(v->isLeaf)){
			if(L <= v->value){
				vector<data> t = ((v->right)->Tassoc)->query(scRange);
				for(int i = 0; i < t.size(); i++){
					ans.push_back(t[i]);
				}
				v = v->left;
			}
			else{
				v = v->right;
			}
		}
		if(v->isLeaf){
			if(l <= (v->value).pc && (v->value).pc <= r)
				if(scRange.first <= (v->value).sc && (v->value).sc <= scRange.second)
					ans.push_back(v->value);
		}
		v = splitNode->right;
		while(!(v->isLeaf)){
			if(v->value < R){
				vector<data> t = ((v->left)->Tassoc)->query(scRange);
				for(int i = 0; i < t.size(); i++){
					ans.push_back(t[i]);
				}
				v = v->right;
			}
			else{
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
int rangeTree::queryCnt(std::pair<double, double> pcRange,std::pair<double, double> scRange){
	int l = pcRange.first, r = pcRange.second;
	data L(l, -1*INF), R(r, INF);

	rangeTreeNode *splitNode = findSplitNode(l, r);
	int ans = 0;
	if(splitNode->isLeaf){
		if( l <= (splitNode->value).pc && (splitNode->value).pc <= r)
			if(scRange.first <= (splitNode->value).sc && (splitNode->value).sc <= scRange.second)
				ans++;
	}
	else{
		rangeTreeNode *v = splitNode->left;
		while(!(v->isLeaf)){
			if(L <= v->value){
				ans+=((v->right)->Tassoc)->queryCnt(scRange);
				v = v->left;
			}
			else{
				v = v->right;
			}
		}
		if(v->isLeaf){
			if(l <= (v->value).pc && (v->value).pc <= r)
				if(scRange.first <= (v->value).sc && (v->value).sc <= scRange.second)
					ans++;
		}
		v = splitNode->right;
		while(!(v->isLeaf)){
			if(v->value < R){
				ans += ((v->left)->Tassoc)->queryCnt(scRange);
				v = v->right;
			}
			else{
				v = v->left;
			}
		}
		if(v->isLeaf){
			if(l <= (v->value).pc && (v->value).pc <= r)
				if(scRange.first <= (v->value).sc && (v->value).sc <= scRange.second)
					ans++;
		}
	}
	return ans;

}
