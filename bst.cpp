#include "bst.h"
#include <iostream>
#include <string.h>
using namespace project;
using namespace std;

#define ss second
#define ff first


const long long OO = 1e18;

bstNode::bstNode(){
	value=data();
	isLeaf = false;
	left = NULL;
	right = NULL;
}
bstNode::~bstNode(){
	value=data();
	isLeaf = false;
	left = NULL;
	right = NULL;

}
bstNode::bstNode(const data& v){
	value = data(v);
	isLeaf = false;
	left = NULL;
	right = NULL;
}
vector<data> reportSubtree(bstNode* root){
	if (root == NULL)
		return {};
	else if(root->isLeaf){
		vector<data> ret;
		ret.push_back(root->value);
		return ret;
	}
	else{
		vector<data> left, right;
		left = reportSubtree(root->left);
		right = reportSubtree(root->right);
		for(int i = 0; i < (int)right.size(); i++)
			left.push_back(right[i]);
		return left;

	}
}
bst::bst(std::vector<data> v, int pc){
	a = v;
	for(int i = 0; i < (int)a.size(); i++){
		a[i].setPrimaryCoordinate(pc);
	}
	sortedPC = a;
	buildFast(0, (int)a.size()-1, root);
}
bst::bst(){
	a = {};
	sortedPC = {};
	root = NULL;
	primaryCoordinate = 1;
}
bst::~bst(){
	a.clear();
	sortedPC.clear();
	root = NULL;
	primaryCoordinate = 1;
}
void bst::build(std::vector<data>& a, bstNode* &root){
	int l = 0;
	int r = a.size()-1;
	if(l > r)
		root = NULL;
	else if( l == r ){
		root = (new bstNode(data(a[l])));
		root->isLeaf = true;
		root->size = 1;
	}
	else{
		int m = (l+r)/2;
		root = (new bstNode(data(a[m])));
		root->size = a.size();
		std::vector<data> left, right;
		for(int i = 0; i <= r; i++){
			if(i <= m) left.push_back(a[i]);
			else right.push_back(a[i]);
		}
		build(left, root->left);
		build(right, root->right);
	}
}
void bst::buildFast(int l, int r, bstNode* &root){
	if(l > r)
		root = NULL;
	else if( l == r ){
		root = (new bstNode(data(sortedPC[l])));
		root->isLeaf = true;
		root->size = 1;
	}
	else{
		int m = (l+r)/2;
		root = (new bstNode(data(sortedPC[m])));
		root->size = r-l+1;
		buildFast(l, m, root->left);
		buildFast(m+1, r, root->right);
	}
}
bstNode* bst::findSplitNode(int l, int r){
	bstNode *v = root;
	int pcv = (v->value).pc;
	while(!(v->isLeaf) && (r <= pcv || l > pcv)){
		if(r <= pcv)
			v = v->left;
		else
			v = v->right;
		pcv = (v->value).pc;
	}
	return v; 
}

vector<data> bst::query(pair<double, double> range){
	int l = range.first, r = range.second;
	bstNode *splitNode = findSplitNode(l, r);
	vector<data> ans = {};
	if(splitNode->isLeaf){
		int pcv = (splitNode->value).pc;
		if( l <= pcv && pcv <= r)
			ans.push_back(splitNode->value);
	}
	else{
		bstNode *v = splitNode->left;
		int pcv = (v->value).pc;
		while(!(v->isLeaf)){
			if(l <= pcv){
				vector<data> t = reportSubtree(v->right);
				for(int i = 0; i < t.size(); i++){
					ans.push_back(t[i]);
				}
				v = v->left;
			}
			else
				v = v->right;
			pcv = (v->value).pc;
		}
		if(v->isLeaf){
			pcv = (v->value).pc;
			if( l <= pcv && pcv <= r)
				ans.push_back(v->value);
		}
		v = splitNode->right;
		pcv = (v->value).pc;
		while(!(v->isLeaf)){
			if(pcv < r){
				vector<data> t = reportSubtree(v->left);
				for(int i = 0; i < t.size(); i++)
					ans.push_back(t[i]);
				v = v->right;
			}
			else
				v = v->left;
			pcv = (v->value).pc;
		}
		if(v->isLeaf){
			pcv = (v->value).pc;
			if(l <= pcv && pcv <= r)
				ans.push_back(v->value);
		}
	}
	return ans;
}
int bst::queryCnt(pair<double, double> range){
	int l = range.first, r = range.second;
	bstNode *splitNode = findSplitNode(l, r);
	int ans = 0;
	if(splitNode->isLeaf){
		int pcv = (splitNode->value).pc;
		if( l <= pcv && pcv <= r)
			ans++;
	}
	else{
		bstNode *v = splitNode->left;
		int pcv = (v->value).pc;
		while(!(v->isLeaf)){
			if(l <= pcv){
				ans+=(v->right)->size;
				v = v->left;
			}
			else
				v = v->right;
			pcv = (v->value).pc;
		}
		if(v->isLeaf){
			pcv = (v->value).pc;
			if( l <= pcv && pcv <= r)
				ans++;
		}
		v = splitNode->right;
		pcv = (v->value).pc;
		while(!(v->isLeaf)){
			if(pcv < r){
				ans+=(v->left)->size;
				v = v->right;
			}
			else
				v = v->left;
			pcv = (v->value).pc;
		}
		if(v->isLeaf){
			pcv = (v->value).pc;
			if(l <= pcv && pcv <= r)
				ans++;	
		}
	}
	return ans;
}
