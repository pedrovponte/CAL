/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <stack>
#include "MutablePriorityQueue.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
	T info;						// content of the vertex
	vector<Edge<T> > adj;		// outgoing edges
	
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool visited = false;		// auxiliary field
	bool processing = false;	// auxiliary field

	void addEdge(Vertex<T> *dest, double w);

public:
	Vertex(T in);
	T getInfo() const;
	double getDist() const;
	Vertex *getPath() const;

	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set

public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;

	// Fp05 - single source
	void unweightedShortestPath(const T &s);    //TODO...
	void dijkstraShortestPath(const T &s);      //TODO...
	void bellmanFordShortestPath(const T &s);   //TODO...
	vector<T> getPathTo(const T &dest) const;   //TODO...

	// Fp05 - all pairs
	void floydWarshallShortestPath();   //TODO...
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...

};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
	for(auto& v : this->vertexSet){
	    v->dist = INF;
	    v->path = NULL;
	}

	auto v = findVertex(orig);
	v->dist = 0;

	queue<Vertex<T>*> q;
	q.push(v);

	while(!q.empty()){
	    v = q.front();
	    q.pop();
	    for(auto& w : v->adj){
	        if(w.dest->dist == INF){
	            w.dest->dist = v->dist + 1;
	            w.dest->path = v;
                q.push(w.dest);
	        }
	    }
	}
}


template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
    for(auto& v : vertexSet){
        v->dist = INF;
        v->path = NULL;
        v->visited = false;
    }

    auto v = findVertex(origin);
    v->dist = 0;
    v->visited = true;

    MutablePriorityQueue<Vertex<T>> q;
    q.insert(v);

    while(!q.empty()){
        v = q.extractMin();
        for(auto& w : v->adj){
            if(w.dest->dist > v->dist + w.weight){
                w.dest->dist = v->dist + w.weight;
                w.dest->path = v;
                if(!w.dest->visited){
                    q.insert(w.dest);
                    w.dest->visited = true;
                }
                else{
                    q.decreaseKey(w.dest);
                }
            }
        }
    }


}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
	for(auto& v : vertexSet){
	    v->path = NULL;
	    v->dist = INF;
	}

	auto v = findVertex(orig);
	v->dist = 0;

	for(int i = 1; i < vertexSet.size();i++){
	    for(auto v1 : vertexSet){
	        for(auto w : v1->adj){
                if(w.dest->dist > v1->dist + w.weight) {
                    w.dest->dist = v1->dist + w.weight;
                    w.dest->path = v1;
                }
	        }
	    }
	}
}


template<class T>
vector<T> Graph<T>::getPathTo(const T &dest) const{
	vector<T> res;
	Vertex<T>* v = findVertex(dest);
	stack<T> s;
	s.push(v->info);
	while(v->getPath() != NULL){
	    s.push(v->getPath()->getInfo());
	    v = v->getPath();
	}
	while(!s.empty()){
	    res.push_back(s.top());
	    s.pop();
	}

	return res;
}



/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
	// TODO
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
	vector<T> res;
	// TODO
	return res;
}


#endif /* GRAPH_H_ */
