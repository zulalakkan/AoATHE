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
    for(int v = 0; v < nodeCount - 1; v++) // do not check sink
    {
        if (excess[v] > 0) return v;
    }
    return -1;
}

void Graph::initializePreflow(int source){
    height.assign(nodeCount, 0);
    excess.assign(nodeCount, 0);
    
    flow.assign(nodeCount, vector<int>(nodeCount, 0));

    height[source] = nodeCount;
    for(int v= 0; v < nodeCount; v++)
    {
        flow[source][v] = capacity[source][v];
        flow[v][source] = - capacity[source][v];
        excess[v] = capacity[source][v];
        excess[source] -= capacity[source][v];
    }
}

void Graph::push(int u, int v){
    int residualCapacity = capacity[u][v] - flow[u][v];
    int delta = excess[u] < residualCapacity ? excess[u] : residualCapacity;
    flow[u][v] += delta;
    flow[v][u] -= delta;
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
    int u = overflowingVertex();
    while(u != -1)
    {
        bool isPush = false;
        for (int v = 0; v < nodeCount; v++)
        {
            if (capacity[u][v] - flow[u][v] > 0 && height[u] == height[v] + 1)
            {
                push(u,v);
                isPush = true;
                break;
            }
        }
        if(!isPush) relabel(u);
        u = overflowingVertex();
    }
    int res = 0;
    for(int v = 0; v < nodeCount-1; v++)
    {
        res += flow[v][nodeCount-1];
    }
    return res;
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