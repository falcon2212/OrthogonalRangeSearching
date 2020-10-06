This folder contains two data structures for range searching
 1) bst for 1d range searching
 2) 2-dimensional range trees for orthogonal range searching
 2) 2-dimensional range trees for orthogonal range searching with fractional cascading
 3) 2-dimensional KD tree for orthogonal range searching
The '.h' files contain the design of the implementation as in function definitions and their signature, '.cpp' files contain the actual implementation of the code.

Code for representing data is in - "data.h" and "data.cpp"
Code for one dimensional bst is in - "bst.h" and "bst.cpp"
Code for two dimensional range tree is in - "rangeTree.h" and "rangeTree.cpp"
Code for two dimensional layered range tree is in - "layeredRangeTree.h" and "layeredRangeTree.cpp"
Code for two dimensional KDtree is in - "kdTree.h" and "kdTree.cpp"
Code for GUI in inputGUI.py and outputGUI.py

The driver program for testing the data structures are as follows:
	Testing program for BST - driverBst.cpp
	Testing program for Range Tree - driverRangeTree.cpp
	Testing program for Layuered Range Tree - driverLayeredRangeTree.cpp
	Testing program for KDTree - driverKDTree.cpp

The input format for one dimensional BST is as follows:	
	First line contains n - the number of points
	Then the next line contains n space seperated numbers describing the 1d coordinates of the n points.
	The next line describes the query range
	There are two space seperated numbers l,r denoting the range [l,r].
	for example:
	4
	3 5 7 10
	4 6
The input format for two dimensional query is as follows:	
	First line contains n - the number of points
	Then the next n lines are as follows:
		Each ith line contains two space seperated integers x, y denoting the 2-d coordinates of the ith point.
	The next two lines describes the query Rectangle.	
	Then the next line gives the 2d-coordinates of the lower left point of the rectangle.	
	Then the next line gives the 2d-coordinates of the upper right point of the rectangle.	
	for example:
	4
	1 2
	2 4
	3 5
	10 1
	1 2 3 5
	// the range in the eg 2 is the rectange from [1,2] to [3,5] as it's left lower and right upper points respectively.

Inorder to compile the code follow the below steps

For range trees:
$ g++ data.h data.cpp kdTree.h kdTree.cpp driverKDTree.cpp -o KDTREE
$ ./KDTREE < input.in

For range trees:
$ g++ data.h data.cpp bst.h bst.cpp rangeTree.h rangeTree.cpp driverRangeTree.cpp -o RANGE_TREE
$ ./RANGE_TREE < input.in

For BST:
$ g++ data.h data.cpp bst.h bst.cpp driverForBst.cpp -o BST
$ ./BST < input1d.in

For testing with GUI:
	$ bash ./test.sh
Experimental Ananlysis: Please find the details in report.pdf
How to test?, In oreder to run this code you need to have following software installed
-> pygame python library
-> bash shell
$ bash ./test.sh
running the above command will execute the software, the file "test.sh" is properly commented for you to modify and play around with various data structures.