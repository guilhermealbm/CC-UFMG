#include <iostream>
#include <fstream>

#include "teamGraph.h"

void read_input_file(std::string file_name){
    std::ifstream readFile;
    readFile.open(file_name);
    if(readFile.is_open()){
        int members, relations, instructions;
        readFile >> members >> relations >> instructions;

        TeamGraph team = TeamGraph(members);

        for (int i = 0; i < members; i++){
            int age;
            readFile >> age;
            team.setAge(i, age);
        }

        for (int i = 0; i < relations; i++){
            int origin, destiny;
            readFile >> origin >> destiny;
            team.insertEdge(origin-1, destiny-1); //Members count starts @ 1
        }

        for (int i = 0; i < instructions; i++){
            std::string instruction;
            readFile >> instruction;
            if(instruction == "M"){
                std::stack<int> topologicalOrder = team.meeting();
                int stackSize = topologicalOrder.size();
                std::cout << "M ";
                for (int j = 0; j < stackSize; j++){
                    std::cout << topologicalOrder.top() << " ";
                    topologicalOrder.pop();
                }
                
                std::cout << std::endl;
                
            }else if(instruction == "C"){
                TeamGraph* invertedTeam = team.invertEdges();
                int member;
                readFile >> member;
                int minAge = invertedTeam->commander(member);
                if(minAge == -1){std::cout << "C *" << std::endl;}
                else
                    std::cout << "C " << minAge << std::endl;
                delete invertedTeam;
            }else{
                int member1, member2;
                readFile >> member1 >> member2;
                std::cout << "S " << (team.swap(member1-1, member2-1) ? "T" : "N") << std::endl;
            }
        }

    }
    readFile.close();
}

int main(int argc, char *argv[]){
    
    read_input_file(std::string(argv[1]));

    return 0;
}