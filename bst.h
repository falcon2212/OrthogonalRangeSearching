#ifndef BST
#define BST
#include "data.h"
#include <vector>
#include <algorithm>
#include <iostream>
namespace project
{
	class bstNode
	{
		public:
			// variables
			data value;
			bstNode *left, *right;
			bool isLeaf;
			int size;
			// constructors
			bstNode();
			bstNode(const data& v);
			~bstNode();
		
	};
	class bst
	{
	public:
		// variables
		std::vector<data> a;
		std::vector<data> sortedPC;
		bstNode *root;
		int primaryCoordinate;
		// constructors
		bst(std::vector<data> v, int primaryCoordinate);
		~bst();
		bst();
		// functions
		void build(std::vector<data>& a, bstNode* &root);
		void buildFast(int l, int r, bstNode* &root);
		bstNode* findSplitNode(int l, int r);
		std::vector<data> query(std::pair<double, double> range);
		int queryCnt(std::pair<double, double> range);
	};
}
#endif