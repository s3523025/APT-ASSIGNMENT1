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
    // std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    // testNode();
    // testNodeList();
    // std::cout << "DONE TESTING" << std::endl << std::endl;
    
    // Check if environment file is provided
    if(argc < 2) {
        std::cerr << "Include an environment file as part of a command line argument.\n";
        std::cerr << "Example: ./pathfinder test1.env\n";
        return 1;
    }

    // Redirect input to the env
    std::string envFilePath = argv[1];
    FILE* file = freopen(envFilePath.c_str(), "r", stdin);

    // make sure the file opened and provide response
    if (file == nullptr) {
        std::cerr << "Couldn't open file: " << envFilePath << std::endl;
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

    //std::cout << std::endl;
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
}

bool isSafeCharacter(char c){
    //Make sure the character is one of the valid types
    if (c == SYMBOL_EMPTY || c==SYMBOL_START || c==SYMBOL_GOAL || c==SYMBOL_WALL){
        return true;
    }
    return false;
}

void printEnvStdout(Env env, NodeList* solution) {
    // print out the environment for display test purposes
    // std::cout << "\nOriginal Environment" << std::endl;
    // for (int i = 0; i < ENV_DIM; ++i) {
    //     for (int j = 0; j < ENV_DIM; ++j) {
    //         std::cout << env[i][j];
    //     }
    //     std::cout << "\n";
    // }
  
    // Using the nodes in the solution, change the environment to show the path
    //std::cout << "Solution path: " << std::endl;
    //Starts at 1 and -1 because first is start node and last is goal node
    for(int i = 1; i < solution->getLength() - 1; i++) {
        int rowDiff = solution->getNode(i + 1)->getRow() - solution->getNode(i)->getRow();
        int colDiff = solution->getNode(i + 1)->getCol() - solution->getNode(i)->getCol();

        // If the next node is below the current node, set the current node to a 'v'
        if(rowDiff > 0) {
            env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] = 'v';
        }
        // If the next node is above the current node, set the current node to a '^'
        else if(rowDiff < 0) {
            env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] = '^';
        }
        // If the next node is to the right of the current node, set the current node to a '>'
        else if(colDiff > 0) {
            env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] = '>';
        }
        // If the next node is to the left of the current node, set the current node to a '<'
        else if(colDiff < 0) {
            env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] = '<';
        }
    }

    // print out the environment with the path
    int i;
    for (i = 0; i < ENV_DIM; ++i) {
        for (int j = 0; j < ENV_DIM; ++j) {
            std::cout << env[i][j];
        }
        // Add a newline character after each row
        if (i < ENV_DIM - 1) {
            std::cout << "\n";
        }
    }
    // Check if it's the last line before adding a newline
    if (i < ENV_DIM - 1) {
        std::cout << "\n";
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