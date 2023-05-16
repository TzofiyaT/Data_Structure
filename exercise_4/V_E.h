#pragma once
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <queue>
using namespace std;

enum Color { black, gray, white };

class Vertex; 

class Edge//this class represent a edge includes:two vertexes
{
	Vertex* destination;
public:
	Edge(Vertex* destination);
	bool operator==(Edge & v)const ;
	friend class Vertex;
	friend class Graph;
};


//this class represents a vertex includes:key ,list of his edges

class Vertex
{
	string Key;
	Vertex *pi;
	list<Edge *>EdgeList;
	int d;
	int f;
	Color color;
public:
	Vertex(string key);
	bool adde(Edge *);
	int numOfNeighbours();
	bool destinationExists(Vertex* v)//return if a edge is in the list of the edges
	{
		for (list<Edge *>::iterator it = EdgeList.begin(); it != EdgeList.end(); it++)
			if ((*it)->destination == v)
				return true;
		return false;
	}
	void print()//print the key of a vertex and all its neighbours
	{
		std::cout << Key << ": ";
		for (list<Edge *>::iterator it = EdgeList.begin(); it != EdgeList.end(); it++)
			std::cout << (*it)->destination->Key << " ";
	}
	void removeEdges()
	{
		for (list<Edge *>::iterator it = EdgeList.begin(); it != EdgeList.end(); it++)
			delete (*it);
	}
	void initialize()
	{
		color = white;
		pi = NULL;
	}
	friend class Graph;
};


// a class represents a graph of a vertexes & the edges
class Graph
{
private:
	std::map<string, Vertex*> graph;
	list<Vertex*> order;
	int timer;
public:
	Graph();
	~Graph();
	bool addv(string& key);
	bool adde(string& key1, string& key2);
	void printAll();
	list<Vertex*> DFS();
	void DFS_Visit(Vertex *v);
	// void printPath(Vertex *v1, Vertex *v2);
	void topologicalSort();
};