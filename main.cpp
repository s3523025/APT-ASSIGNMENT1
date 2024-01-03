#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env);
bool isSafeCharacter(char c);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList* solution);


int main(int argc, char** argv){
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    testNode();
    testNodeList();
    std::cout << "DONE TESTING" << std::endl << std::endl;
    // Check if environment file is provided
    if(argc < 2) {
        std::cerr << "Please provide an environment file as a command line argument.\n";
        return 1;
    }

    // Redirect standard input to the environment file
    std::string envFilePath = argv[1];
    FILE* file = freopen(envFilePath.c_str(), "r", stdin);

    // make sure the file opened and provide response
    if (file == nullptr) {
        std::cerr << "Failed to open file: " << envFilePath << std::endl;
        return 1;
    }

    // Load Environment 
    Env env;
    readEnvStdin(env);

    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    PathSolver* pathSolver = new PathSolver();
    pathSolver->forwardSearch(env);

    NodeList* exploredPositions = nullptr;
    exploredPositions = pathSolver->getNodesExplored();

    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList* solution = pathSolver->getPath(env);
    printEnvStdout(env, solution);

    delete pathSolver;
    delete exploredPositions;
    delete solution;

}

void readEnvStdin(Env env){
    char c;
    int row = 0, col = 0;
    while (std::cin >> c) {
        if (c == '\n') {
            ++row;
            col = 0;
        } else {
            env[row][col] = c;
            ++col;
        }
    }

    //std::cout << "Environment loaded from stdin" << std::endl;

}
/*void readEnvStdin(Env env){
	//Read in the 20x20 environemnt file .env from the Milestone1Tests folder
    std::ifstream file("../Milestone1Tests/test1.env");
    char c;
    if (file.is_open()){
        for (int i = 0; i < ENV_DIM; i++){
            for (int j = 0; j < ENV_DIM;){
                file.get(c);
                if (isSafeCharacter(c)) {
                    env[i][j] = c;
                    j++;
                }
            }
        }
    }
    else{
        std::cout << "Could not open file";
    }
    file.close();
}*/



bool isSafeCharacter(char c){
    if (c == SYMBOL_EMPTY || c==SYMBOL_START || c==SYMBOL_GOAL || c==SYMBOL_WALL){
        return true;
    }
    return false;
}

void printEnvStdout(Env env, NodeList* solution) {
    // print out the environment
    std::cout << "\nOriginal Environment" << std::endl;
    for (int i = 0; i < ENV_DIM; ++i) {
        for (int j = 0; j < ENV_DIM; ++j) {
            std::cout << env[i][j];
        }
        std::cout << std::endl;
    }
  

    // Using the nodes in the solution, change the environment to show the path
    // this loop starts at 1 and end at length - 1 because the first and last nodes are the start and goal nodes
    std::cout << "\nSolution path: " << std::endl;
    for(int i = 1; i < solution->getLength() - 1; i++){

       //if the previous node was to the left of the current node, set the current node to a >
        if(solution->getNode(i - 1)->getCol() < solution->getNode(i)->getCol()){
            env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] = '>';
        }
        //if the previous node was to the right of the current node, set the current node to a <
        else if(solution->getNode(i - 1)->getCol() > solution->getNode(i)->getCol()){
            env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] = '<';
        }
        //if the previous node was above the current node, set the current node to a v
        else if(solution->getNode(i - 1)->getRow() < solution->getNode(i)->getRow()){
            env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] = 'v';
        }
        //if the previous node was below the current node, set the current node to a ^
        else if(solution->getNode(i - 1)->getRow() > solution->getNode(i)->getRow()){
            env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] = '^';
        }

    }


    // print out the environment with the path
    for (int i = 0; i < ENV_DIM; ++i) {
        for (int j = 0; j < ENV_DIM; ++j) {
            std::cout << env[i][j];
        }
        std::cout << std::endl;
    }

}



void testNode() {
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node* node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;
}

void testNodeList() {
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList* nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node* b1 = new Node(1, 1, 1);
    nodeList->addElement(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node* b2 = new Node(0, 0, 1);
    nodeList->addElement(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node* getB = nodeList->getNode(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceTraveled() << std::endl;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
}