#include "V_E.h"
#include <iostream>
#include <map>
#include <list>
#include <string>
#include <queue>


using namespace std;

//constracto initilizes the pointers
Edge::Edge(Vertex* dst)
{
	destination = dst;
}
//comperative operator
bool Edge:: operator==(Edge& v)const
{
	return (v.destination == destination);
}

//==================================================================================
int Vertex::numOfNeighbours()//returns the number of the neighbours of a vertex
{
	return EdgeList.size();
	
}
//constractor
Vertex::Vertex(string key)
{
	Key = key;
}

bool Vertex::adde(Edge* e)//add a edge to the list of the edges
{
	EdgeList.push_back(e);
	return true;
}


// a class represents a graph of a vertexes & the edges
//==================================================================================

Graph::Graph()//constractor
{}


Graph::~Graph()//distractor
{
	std::map<string, Vertex*>::iterator it;
	for (it = graph.begin(); it != graph.end(); it++)
		(*it).second->removeEdges();
	for (it = graph.begin(); it != graph.end(); it++)
		delete (*it).second;
	graph.clear();
}

void Graph::printAll()
{
	std::map<string, Vertex*>::iterator it;
	for (it = graph.begin(); it != graph.end(); it++)
	{
		(*it).second->print();
		cout << endl;
	}
}



//add a vertex to the graph: 
bool Graph::addv(string& key)
{
	std::map<string, Vertex*>::iterator it;
	if (graph.empty() || graph.find(key) == graph.end())
	{
		graph[key] = new Vertex(key);
		return true;
	}
	else
		return false;
}

// add a edge to the graph-recives two vertexes
bool Graph::adde(string& key1, string& key2) //undirected graph
{
	if (graph.find(key1) == graph.end() || graph.find(key2) == graph.end())
	{
		return false;
	}
	Vertex* v1 = graph[key1]; //new Vertex(key1);
	Vertex* v2 = graph[key2]; //new Vertex(key2);
	if (v1->destinationExists(v2))//checks if the edge already exists
		return false;
	Edge *e1 = new Edge(v2);
	v1->adde(e1);//
	return true;
}


void Graph::DFS_Visit(Vertex *u)
{
	u->color = gray;
	timer++;
	for (std::list<Edge*>::iterator i = u->EdgeList.begin(); i != u->EdgeList.end(); i++)
	{
		if ((*i)->destination->color == white)
		{
			(*i)->destination->pi = u;
			DFS_Visit((*i)->destination);
		}
	}
	u->color = black;
	u->f = ++timer;
	order.push_front(u);
}



list<Vertex*> Graph::DFS()
{
	std::map<string, Vertex*>::iterator it;
	for (it = graph.begin();it != graph.end(); it ++)
	{
		(*it).second->color = white;
		(*it).second->pi = NULL;
	}
	for (it = graph.begin(); it != graph.end(); it++)
	{
		if ((*it).second->color == white)
			DFS_Visit((*it).second);
	}
	return order;
}




void Graph::topologicalSort()
{
	order.clear();
	DFS();
	cout << "order: ";
	for (std::list<Vertex*>::iterator i = order.begin(); i != order.end(); i++)
	{
		cout << (*i)->Key << " ";
	}
}


