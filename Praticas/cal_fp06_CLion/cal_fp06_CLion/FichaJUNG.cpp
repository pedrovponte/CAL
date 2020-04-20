#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

void exercicio1();
void exercicio2();
void exercicio3();


void exercicio1()
{
    GraphViewer *gv = new GraphViewer(600, 600, true);
    gv->setBackground("background.jpg");
    gv->createWindow(600, 600);
    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");

    gv->addNode(0);
    gv->addNode(1);
    gv->rearrange();

    gv->addEdge(0, 0, 1, EdgeType::UNDIRECTED);
    gv->addEdge(1, 0, 1, EdgeType::DIRECTED);

    gv->removeNode(1);
    gv->rearrange();

    gv->addNode(2);
    gv->addEdge(2, 0, 2, EdgeType::UNDIRECTED);
    gv->rearrange();

    gv->setVertexLabel(2, "Isto e um no");
    gv->setEdgeLabel(2, "Isto e uma aresta");
    gv->rearrange();

    gv->setVertexColor(2, "green");
    gv->setEdgeColor(2, "yellow");
    gv->rearrange();


}

void exercicio2()
{
    GraphViewer *gv = new GraphViewer(600, 600, false);
    gv->createWindow(600, 600);

    gv->addNode(0, 300, 50);
    gv->addNode(1, 318, 58);
    gv->addNode(2, 325, 75);
    gv->addNode(3, 318, 93);
    gv->addNode(4, 300, 100);
    gv->addNode(5, 282, 93);
    gv->addNode(6, 275, 75);
    gv->addNode(7, 282, 93);
    gv->addNode(8, 150, 200);
    gv->addNode(9, 300, 200);
    gv->addNode(10, 450, 200);
    gv->addNode(11, 300, 400);
    gv->addNode(12, 200, 550);
    gv->addNode(13, 400, 550);

    gv->rearrange();

    gv->addEdge(0, 0, 1, EdgeType::DIRECTED);
    gv->addEdge(1, 1, 2, EdgeType::DIRECTED);
    gv->addEdge(2, 2, 3, EdgeType::DIRECTED);
    gv->addEdge(3, 3, 4, EdgeType::DIRECTED);
    gv->addEdge(4, 4, 5, EdgeType::DIRECTED);
    gv->addEdge(5, 5, 6, EdgeType::DIRECTED);
    gv->addEdge(6, 6, 7, EdgeType::DIRECTED);
    gv->addEdge(7, 7, 0, EdgeType::DIRECTED);
    gv->addEdge(8, 4, 9, EdgeType::DIRECTED);
    gv->addEdge(9, 9, 8, EdgeType::DIRECTED);
    gv->addEdge(10, 9, 10, EdgeType::DIRECTED);
    gv->addEdge(11, 9, 11, EdgeType::DIRECTED);
    gv->addEdge(12, 11, 12, EdgeType::DIRECTED);
    gv->addEdge(13, 11, 13, EdgeType::DIRECTED);

    gv->rearrange();

    int i = 14;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true) {  // animation cycle
        gv->removeNode(i - 2);
        gv->removeNode(i - 1);
        gv->addNode(i, 250, 550);
        gv->addNode(i + 1, 350, 550);
        gv->addEdge(i, 11, i, EdgeType::DIRECTED);
        gv->addEdge(i + 1, 11, i + 1, EdgeType::DIRECTED);
        Sleep(1000);
        gv->rearrange();

        gv->removeNode(i);
        gv->removeNode(i + 1);
        gv->addNode(i + 2, 200, 550);
        gv->addNode(i + 3, 400, 550);
        gv->addEdge(i + 4, 11, i + 2, EdgeType::DIRECTED);
        gv->addEdge(i + 5, 11, i + 3, EdgeType::DIRECTED);
        Sleep(1000);
        gv->rearrange();

        i += 4;
    }
#pragma clang diagnostic pop

}

void exercicio3()
{
    ifstream nodes("../resources/mapa1/nos.txt");
    ifstream edges("../resources/mapa1/arestas.txt");

    GraphViewer* gv = new GraphViewer(600, 600, false);
    gv->createWindow(600, 600);

    if(nodes.is_open()){
        string line;
        while(getline(nodes, line)){
            stringstream ss(line);
            vector<int> info;
            string token;
            while(getline(ss, token, ';')){
                info.push_back(stoi(token));
            }
            gv->addNode(info[0], info[1], info[2]);
        }
    }

    if(edges.is_open()){
        string line;
        while(getline(edges, line)){
            stringstream ss(line);
            vector<int> info;
            string token;
            while(getline(ss, token, ';')){
                info.push_back(stoi(token));
            }

            gv->addEdge(info[0], info[1], info[2], EdgeType::UNDIRECTED);
        }
    }

    gv->defineEdgeCurved(false);
    gv->rearrange();
}

int main() {
    /*
     * Uncomment the line below to run Exercise 1
     */
    //exercicio1();

    /*
      * Uncomment the line below to run Exercise 2
      */
    //exercicio2();

    /*
      * Uncomment the line below to run Exercise 3
      */
	//
	exercicio3();

	getchar();
	return 0;
}
