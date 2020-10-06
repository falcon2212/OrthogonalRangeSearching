#ifndef KD_TREE
#define KD_TREE
#include "data.h"
#include <vector>
namespace project{
	class kdTreeNode{
	public:
		// variables
		double l, r, u, d;
		bool isLeaf;
		data value;
		int size;
		kdTreeNode *left, *right;
		// constructors
		kdTreeNode();
		kdTreeNode(double l, double r, double u, double d, const data& v);
		~kdTreeNode();
		kdTreeNode(const kdTreeNode& n);
		// functions
		std::vector<double> getRegion();
	};	

	class kdTree
	{
	public:
		// variables
		kdTreeNode *root;
		std::vector<data> p;
		std::vector<data> sortedPC, sortedSC;
		std::vector<bool> vis;
		int dimensions;
		int primaryCoordinate, secondaryCoordinate;
		// constructors
		kdTree();
		kdTree(std::vector<data> a, int pc);
		~kdTree();
		// functions
		void build(std::vector<data>& a, std::vector<data>& b, int depth, kdTreeNode* &root, std::vector<double> bd);
		std::vector<data> query(kdTreeNode* root, std::pair<double, double> pcRange, std::pair<double, double> scRange);
		std::vector<data> reportSubtree(kdTreeNode* root);
		int queryCnt(kdTreeNode* root, std::pair<double, double> pcRange, std::pair<double, double> scRange);
	};
}
#endif