#include "Header.h"
#include <iostream>
#include <queue>
#include <list>
#include <string>

using namespace std;

//encode

int HuffmanTree::findIndextav(string tav)//change tav->binary code
{
	for (int i = 0; i < size; i++)
		if (table[i].ltr == tav)
			return i;
}

bool findequal(HNode * a, string equal)
{
	if (a->left == NULL &&  a->right == NULL)
	{
		if (a->ltr == equal)
			return true;
		return false;
	}
	return findequal(a->left, equal) ||	findequal(a->right, equal);
}

void codeOfTav(HNode * a, string tav, string & code)
{
	if (a->left == NULL && a->right == NULL)
		return;
	if (findequal(a->left, tav))
	{
		code += "0";
		codeOfTav(a->left, tav, code);
	}
	else
	{
		code += "1";
		codeOfTav(a->right, tav, code);
	}
}


void HuffmanTree::buildTree(letter * table)
{
	priority_queue<HNode*, vector<HNode*>, CompareNode> priority_feque;
	for (int i = 0; i < size; i++)
	{
		HNode * a = new HNode(table[i].ltr, table[i].frq);
		priority_feque.push(a);
	}
	while (priority_feque.size() > 1)
	{
		HNode * small1 = priority_feque.top();
		priority_feque.pop();
		HNode * small2 = priority_feque.top();
		priority_feque.pop();
		HNode * newNode = new HNode(small1->ltr + small2->ltr , small1->frq + small2->frq);
		newNode->left = small1;
		newNode->right = small2;
		priority_feque.push(newNode);
		this->root = newNode;
	}
	
}

letter * HuffmanTree::bulidTableChange()
{
	for(int i = 0; i< size; i++)
		codeOfTav(this->root, table[i].ltr, table[i].binCode);

	return table;
}

void HuffmanTree::codeTree(HNode* c, string & code)
{
	if (c->left == NULL && c->right == NULL)
		code += "1";
	else
	{
		code += "0";
		codeTree(c->left, code);
		codeTree(c->right, code);
	}
	
	
}

void HuffmanTree::encode(string text)
{
	cout << "The encoded string is: " << endl;
	letter * a = this->buildTableOfFreq(text);
	this->buildTree(a);
	this->bulidTableChange();
	string code = string();
	this->codeTree(this->root, code);
	cout << this->size << endl;
	cout << this->root->ltr << endl;
	cout << code << endl;
	for (int i = 0; text[i] !='\0'; i++)
	{
		string c = string() + text[i];
		int index = findIndextav(c);
		cout << table[index].binCode;
	}
	cout << endl;
}

letter * HuffmanTree::buildTableOfFreq(string word)
{
	int i, j;
	bool first_time;
	size = 0; //num of diffrent tav
	letter * freqTable = new letter[256];// table of all tav
	for ( i = 0; word[i] != '\0'; i++)
	{
		first_time = true;
		for (j = 0; j < size && word[i] != freqTable[j].ltr[0]; j++);
		if (word[i] == freqTable[j].ltr[0])
		{
			first_time = false;
			freqTable[j].frq++;
		}
		if (first_time)
		{
			freqTable[size].ltr = word[i];
			freqTable[size].frq++;
			size++;
		}
	}
	this->table = freqTable;
	return freqTable;
}

//decode


void HuffmanTree::buildTreeFromCode(HNode* & a, string & ltrTav, string & codeBinTree)
{
	if (codeBinTree[0] == '1')
	{
		a = new HNode;
		a->ltr = ltrTav[0];
		ltrTav.erase(0, 1);
		codeBinTree.erase(0, 1);
	}
	else if (codeBinTree[0] == '0')
	{
		a = new HNode;
		codeBinTree.erase(0, 1);
		buildTreeFromCode(a->left, ltrTav, codeBinTree);
		buildTreeFromCode(a->right, ltrTav, codeBinTree);
	}

}

void HuffmanTree::readText(HNode * a, string & text)
{
	if (a->left == NULL && a->right == NULL)
	{
		cout << a->ltr;
		return;
	}
	else if (text[0] == '0')
	{
		text.erase(0, 1);
		readText(a->left, text);
	}
	else
	{
		text.erase(0, 1);
		readText(a->right, text);
	}
}


void HuffmanTree::decode(int size, string ltrTav, string codeBinTree, string & text)
{
	this->size = size;
	this->table = NULL;
	buildTreeFromCode(this->root , ltrTav, codeBinTree);
	while (text[0] != '\0')
		readText(this->root, text);
	cout << endl;
}
