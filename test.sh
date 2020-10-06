#!/bin/bash
#-------> uncomment this line to take gui input
# python2 inputGUI.py|tail -n +3 > input.in
#-------> uncomment this line to take random input
# python2 gen.py > input.in
#-------> uncomment the follwing lines to recompute the input
# g++ data.h data.cpp bst.h bst.cpp driverBST.cpp -o BST
# g++ data.h data.cpp kdTree.h kdTree.cpp driverKDTree.cpp -o KDTREE
# g++ data.h data.cpp bst.h bst.cpp rangeTree.h rangeTree.cpp driverRangeTree.cpp -o RANGETREE
# g++ data.h data.cpp bst.h bst.cpp layeredRangeTree.h layeredRangeTree.cpp driverLayeredRangeTree.cpp -o LRANGETREE
#-------> uncomment the follwing line to run the range tree 
time ./RANGETREE<input.in>out2.in
#-------> uncomment the follwing line to run the layered range tree 
# time ./LRANGETREE<input.in>out2.in
#-------> uncomment the follwing line to run the KD tree 
# time ./KDTREE<input.in>out2.in
#-------> uncomment the follwing line to run the 1D BST 
# time ./BST<input.in>out2.in
#-------> uncomment the follwing line to visualize the output 
python2 outputGUI.py < out2.in
# echo 'Done'
