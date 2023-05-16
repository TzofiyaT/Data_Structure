#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <queue>
#include <list>
#include <string>
using namespace std;

class letter
{
public:
	string ltr;
	int  frq;
	string binCode;
	letter()
	{
		ltr = "";
		frq = 0;
		binCode = "";

	}

};

//a node of a leave or a node of a subtree.
class HNode
{
public:
	string ltr;
	int frq;
	HNode* left;
	HNode* right;


	HNode(string s = " ", int n = 0) {
		ltr = s;
		frq = n;
		left = NULL;
		right = NULL;
	}
	bool operator=(HNode * a)
	{
		if (this->ltr == a->ltr)
			if (this->frq == a->frq)
				return true;
		return false;
	}
	

};

class CompareNode
{
public:
	CompareNode() {}
	~CompareNode() {}
	bool operator()(HNode* const& n1, HNode* const& n2)
	{
		return(n1->frq > n2->frq);
	}
};

class HuffmanTree
{
	HNode* root;
	letter * table; 
	int size;
public:
	//string text;text-> binarytext
	letter* buildTableOfFreq(string word);
	void buildTree(letter* table);
	int findIndextav(string tav);
	letter * bulidTableChange();
	void codeTree(HNode* c, string & code);// code of sturcte of tree
	void encode(string text);

	//binary text-> regular text
	void buildTreeFromCode(HNode* & a, string & ltrTav, string & codeBinTree);
	void readText(HNode * a, string & text);
	void decode(int size, string ltrTav, string codeBinTree, string & text);


	};