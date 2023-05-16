#pragma once
#pragma once
#include <iostream>
#include<cstring>
#include <iterator>
#include<list>

using namespace std;

class Answer;
class Node
{
public:
	string value;
	list <Answer*> listanswer;
	Node(Node & g)
	{
		value = g.value;
		if (g.listanswer.empty())return;
		list<Answer*>::iterator t;
		t = g.listanswer.begin();
		list<Answer*>::iterator tt;
		tt = listanswer.begin();
		for (int i = 0; i < g.listanswer.size(); i++)
		{
			(*tt) = (*t);
			(t)++;
			(tt)++;
		}
	}

	bool isLeaf()
	{
		if (listanswer.empty())
		{
			return true;
		}
		return false;
	}
	Node(string s = "") { value = s; }
	~Node()
	{
		listanswer.clear();
	}
};

class Answer
{
public:
	string aaa;
	Node * son;
	Answer(string a = "") { aaa = a; }
	Answer(string a, Node * s) { aaa = a; son = s; }
	~Answer() { }
};

class Tree
{
public:
	Node * abc;
	Tree() { abc = NULL; }
	~Tree()
	{
		deleteTree(abc);
	}

	void deleteTree(Node* g)
	{
		if (g != NULL)
		{
			if (g->isLeaf())
			{
				delete g;
				return;
			}
			list<Answer*>::iterator it = g->listanswer.begin();
			for (int i = 0; i < g->listanswer.size(); i++)
			{
				it = g->listanswer.begin();
				if ((*it)->son != NULL)
				{
					deleteTree((*it)->son); 
					g->listanswer.erase(it);
				}
			}
			return;
		}
	}

	void addRoot(string s)
	{
		abc = new Node(s);
	}

	void printAllTree()
	{
		printHelp(abc);
	}

	void printHelp(Node * g)
	{
		cout << g->value << endl; 
		if (g->isLeaf())
		{
			return;
		}
		list<Answer*>::iterator it = g->listanswer.begin();
		for (int i = 0; i < g->listanswer.size(); i++)
		{
			cout << (*it)->aaa << endl;
			printHelp((*it)->son); 
			(it)++;
		}
	}

	void SAP(string a, Node * g, list<string>&s, bool & isFind)
	{
		if (g->value == a)
		{
			s.push_front(g->value);
			isFind = true;
			return;
		}
		if (g->isLeaf())
		{
			return;
		}
		list<Answer*>::iterator it = g->listanswer.begin();
		for (int i = 0; i < g->listanswer.size(); i++)
		{
			SAP(a, (*it)->son, s, isFind); 
			if (isFind == true)
			{
				i = g->listanswer.size();
			}
			(it)++;
		}
		if (isFind == true)
		{
			s.push_back(g->value);
			return;
		}
	}

	void searchAndPrint(string a)
	{
		bool isfind = false;
		list<string>s;
		SAP(a, abc, s, isfind);
		list<string>::iterator it = s.begin();
		for (int i = 0; i < s.size(); i++)
		{
			cout << (*it) << endl;
			(it)++;
		}
	}


	Node* FindHelp(string val, Node * &dad, Node * g, bool &isfind, Node *& p)
	{
		if (g->value == val)
		{
			isfind = true;
			p = g;
			return p;
		}
		if (g->isLeaf())
		{
			p = NULL;
			return g;
		}
		list<Answer*>::iterator it = g->listanswer.begin();
		for (int i = 0; i < g->listanswer.size(); i++)
		{
			FindHelp(val, g, (*it)->son, isfind, p); 
			if (isfind == true)
			{
				i = g->listanswer.size();
			}
			(it)++;
		}
		return g;
	}

	Node* find(string val, Node * &dad)
	{
		if (abc == NULL)
		{
			dad = NULL;
			return NULL;
		}
		if (abc->value == val)
		{
			dad = abc;
			return abc;
		}
		bool isfind = false;
		Node * p = NULL;
		FindHelp(val, dad, abc, isfind, p);
		return p;
	}

	void deleteSubTree(string val)
	{
		Node * g = abc;
		deleteTree(find(val, g));
	}

	bool addSon(string dad, string val, string sol)
	{
		Node * g = abc;
		Node * f = find(dad, g);
		if (f == NULL)
		{
			return false;
		}
		else
		{
			Answer * answer = new Answer(val);
			answer->son = new Node(sol);
			f->listanswer.push_back(answer);
			return true;
		}
	}

	void process_m(Node * g)
	{
		if (g->isLeaf())
		{
			cout << g->value << endl;
			return;
		}
		cout << g->value << endl;
		string anserU;
		cin >> anserU;
		list<Answer*>::iterator it = g->listanswer.begin();
		for (int i = 0; i < g->listanswer.size(); i++)
		{
			if (anserU == (*it)->aaa)
			{
				process_m((*it)->son);
			}
			(it)++;
		}
	}

	void process()
	{
		process_m(abc);
	}
};