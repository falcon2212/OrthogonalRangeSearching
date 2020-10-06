#ifndef LAYERED_RANGE_TREE
#define LAYERED_RANGE_TREE
#include "bst.h"

namespace project{
	class layeredRangeTreeNode{
	public:
		// variables
		data value;
		layeredRangeTreeNode *left, *right;
		std::vector<data> sortedSC;
		std::vector<int> ptrToChild_L, ptrToChild_R;
		int size;
		bool isLeaf;
		// constructors
		layeredRangeTreeNode();
		~layeredRangeTreeNode();
		layeredRangeTreeNode(const data& value);
	};
	class layeredRangeTree
	{
	public:
		// variables
		std::vector<data> a;
		std::vector<data> sortedPC,sortedSC;
		layeredRangeTreeNode *root;
		std::vector<bool> vis;
		int primaryCoordinate, secondaryCoordinate;
		// constructors
		layeredRangeTree();
		layeredRangeTree(std::vector<data> p, int pc, int sc);
		~layeredRangeTree();
		// functions
		void build(std::vector<data>& a, std::vector<data>& b, layeredRangeTreeNode* &root);
		layeredRangeTreeNode* findSplitNode(int x, int x1);
		std::vector<data> query(std::pair<double, double> xRange,std::pair<double, double> yRange);
	};
}
#endif

