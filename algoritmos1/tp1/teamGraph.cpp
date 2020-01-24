#include "teamGraph.h"
#include <iostream>

TeamGraph::TeamGraph(int n){
    this->studentAges = new int[n];
    this->adjacencyLists = new std::vector<int>[n];
    this->size = n;
}

TeamGraph::~TeamGraph(){
    delete[] this->studentAges;
    delete[] this->adjacencyLists;
}

int TeamGraph::getAge(int n){
    return this->studentAges[n];
}

void TeamGraph::setAge (int n, int age){
    this->studentAges[n] = age;
}

void TeamGraph::insertEdge(int a, int b){
    this->adjacencyLists[a].push_back(b);

}

TeamGraph* TeamGraph::invertEdges(){
    TeamGraph* invertedGraph = new TeamGraph(this->size);

    for(int i = 0; i < this->size; i++)
        invertedGraph->setAge(i, this->getAge(i));


    for (int i = 0; i < this->size; i++){
        for (unsigned int j = 0; j < this->adjacencyLists[i].size(); j++)
            invertedGraph->insertEdge(this->adjacencyLists[i].at(j), i);
    }

    return invertedGraph;

}

int TeamGraph::commander(int member){
    int minAge = 8000;
    std::stack<int> membersStack;
    membersStack.push(member-1);

    bool visited[this->size] = {0};

    while (!membersStack.empty()){
        int currentNodeIndex = membersStack.top();
        membersStack.pop();
        if(!visited[currentNodeIndex]){ //Not explored yet
            visited[currentNodeIndex] = true;
            std::vector<int> currentNodeAdjacencyList = this->adjacencyLists[currentNodeIndex];

            for (unsigned int i = 0; i < currentNodeAdjacencyList.size(); i++)
                membersStack.push(currentNodeAdjacencyList.at(i));
                
            if(this->getAge(currentNodeIndex) < minAge)
                minAge = this->getAge(currentNodeIndex);
        }

        if(member == currentNodeIndex+1 && membersStack.size() == 0) //Member not commanded by anyone. -1 means * @ cout
            minAge = -1;
        
    }

    return minAge;   
}

std::stack<int> TeamGraph::meeting(){
    std::stack<int> topologicalOrder;    

    bool* visited = new bool[this->size] {0};    

    for (int i = 0; i < this->size; i++){
        if(!visited[i])
            this->meetingDFS(i, visited, topologicalOrder);
    }
    
    return topologicalOrder;
}

void TeamGraph::meetingDFS(int currentNodeIndex, bool* visited, std::stack<int>& topologicalOrder){
    visited[currentNodeIndex] = true;

    std::vector<int> currentNodeAdjacencyList = this->adjacencyLists[currentNodeIndex];

    for(unsigned int i = 0; i < currentNodeAdjacencyList.size(); i++){
        int neighbor = currentNodeAdjacencyList.at(i);
        if(!visited[neighbor])
            this->meetingDFS(neighbor, visited, topologicalOrder);
    }

    topologicalOrder.push(currentNodeIndex+1);

}

bool TeamGraph::swap(int a, int b){
    bool hasEdge = this->verifyAndSwapEdge(a, b);
    if(hasEdge){
        if(this->detectCycle()){
            this->verifyAndSwapEdge(b, a);
            return false;
        }
        return true;
    }

    return false;
}

bool TeamGraph::verifyAndSwapEdge(int a, int b){
    std::vector<int>& aNodeAdjacencyList = this->adjacencyLists[a];
    std::vector<int>& bNodeAdjacencyList = this->adjacencyLists[b];
    for (unsigned int i = 0; i < aNodeAdjacencyList.size(); i++){
        if (aNodeAdjacencyList.at(i) == b){
            aNodeAdjacencyList.erase(aNodeAdjacencyList.begin()+i);
            bNodeAdjacencyList.push_back(a);
            return true;
        }
    }

    return false; //There is no edge between nodes.
    
}

bool TeamGraph::detectCycle(){
    int visited[this->size] = {0};

    for (int i = 0; i < this->size; i++){
        if(!visited[i] && this->swapDFS(i, visited))
            return true;
    }

    return false;
}

bool TeamGraph::swapDFS(int currentNodeIndex, int* visited){

    visited[currentNodeIndex] = GRAY;

    std::vector<int> currentNodeAdjacencyList = this->adjacencyLists[currentNodeIndex];

    for(unsigned int i = 0; i < currentNodeAdjacencyList.size(); i++){
        int neighbor = currentNodeAdjacencyList.at(i);
        if(!visited[neighbor] && this->swapDFS(neighbor, visited))
            return true;
        else if(visited[neighbor] == GRAY)
            return true;
    }

    visited[currentNodeIndex] = BLACK;

    return false;
}