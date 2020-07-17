#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

class Graph{
    vector <vector<int>> capacity;
    vector <vector<int>> flow;
    int nodeCount;
    vector <int> excess;
    vector <int> height; 
    public:
    void addCapacity(int, int, int);
    void push(int, int);
    void relabel(int);
    void initializePreflow(int);
    int overflowingVertex();
    int findMaxFlow();
    Graph(int);
    ~Graph();
};

Graph::Graph(int n){
    nodeCount = n;
    capacity.assign(nodeCount, vector<int>(nodeCount, 0));
}

void Graph::addCapacity(int from, int to, int cap){
    capacity[from][to] = cap;
}

int Graph::overflowingVertex(){
    // IMPLEMENT HERE
}

void Graph::initializePreflow(int source){
    for(int v = 0; v < nodeCount; v++)
    {
        height[v] = 0;
        excess[v] = 0;
    }
    flow.assign(nodeCount, vector<int>(nodeCount, 0));

    height[source] = nodeCount;
    for(int v= 0; v < nodeCount && v != source; v++)
    {
        flow[s][v] = capacity[s][v];
        excess[v] = capacity[s][v];
        excess[s] -= capacity[s][v];
    }
}

void Graph::push(int u, int v){
    int residualCapacity = capacity[u][v] - flow[u][v];
    int delta = excess[u] < residualCapacity ? excess[u] : residualCapacity;
    flow[u][v] += delta;
    flow[v][u] += delta;
    excess[u] -= delta;
    excess[v] += delta;
}

void Graph::relabel(int u){
    int min = height[u];
    for (int v = 0; v < nodeCount; v++)
    {
        if(capacity[u][v] - flow[u][v] > 0)
        {
            if(height[v] < min) min = height[v];
        }
    }
    height[u] = min + 1;
}

int Graph::findMaxFlow(){
    // IMPLEMENT HERE
}

Graph::~Graph(){

}

int main(int argumentNumber, char *arguments[]){
    int nodeCount;
    string filename = arguments[1];
    string tempString;
    int temp, from, to, flow;
    
    ifstream file;
    file.open(filename);
    file >> nodeCount;
    Graph graph(nodeCount);
    file >> tempString >> tempString >> tempString;
    while(file.good()){
        file >> from >> to >> flow;
        graph.addCapacity(from, to, flow);
    }
    graph.initializePreflow(0); // 0th node is source
    cout << "Maximum flow: " << graph.findMaxFlow() << endl; 
    return 0;
}