#ifndef RANGE_TREE
#define RANGE_TREE
#include "bst.h"

namespace project{
	class rangeTreeNode{
	public:
		// variables
		data value;
		rangeTreeNode *left, *right;
		bst *Tassoc;
		bstNode *TassocRoot;
		int size;
		bool isLeaf;
		// constructors
		rangeTreeNode();
		~rangeTreeNode();
		rangeTreeNode(const data& value);
	};
	class rangeTree
	{
	public:
		// variables
		std::vector<data> a;
		std::vector<data> sortedPC,sortedSC;
		rangeTreeNode *root;
		std::vector<bool> vis;
		int primaryCoordinate, secondaryCoordinate;
		// constructors
		rangeTree();
		rangeTree(std::vector<data> p, int pc, int sc);
		~rangeTree();
		// functions
		void build(std::vector<data>& a, std::vector<data>& b, rangeTreeNode* &root);
		rangeTreeNode* findSplitNode(int x, int x1);
		std::vector<data> query(std::pair<double, double> xRange,std::pair<double, double> yRange);
		int queryCnt(std::pair<double, double> xRange,std::pair<double, double> yRange);
	};
}
#endif

