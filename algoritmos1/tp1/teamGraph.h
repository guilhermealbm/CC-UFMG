#ifndef TEAMGRAPH_H
#define TEAMGRAPH_H

#include <vector>
#include <stack>

enum Colors{WHITE, GRAY, BLACK};

class TeamGraph {
    private:
        int* studentAges;
        std::vector<int>* adjacencyLists;
        int size;
    public:
        TeamGraph(int n);
        ~TeamGraph();

        int getAge(int n);
        void setAge(int n, int age);

        void insertEdge(int a, int b);
        TeamGraph* invertEdges();

        //Different implementations of dfs algorithm
        int commander(int member);

        std::stack<int> meeting();
        void meetingDFS(int currentNodeIndex, bool* visited, std::stack<int>& topologicalOrder);

        bool swap(int a, int b);
        bool verifyAndSwapEdge(int a, int b);
        bool detectCycle();
        bool swapDFS(int currentNodeIndex, int* visited);

};

#endif