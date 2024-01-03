#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver() {
    nodesExplored = new NodeList();
}

PathSolver::~PathSolver() {
    //delete this->nodesExplored;
}

void PathSolver::forwardSearch(Env env) {

    Node* S = nullptr; // Start Node
    Node* G = nullptr; // Goal Node
    NodeList* O = new NodeList(); // Open List
    NodeList* C = new NodeList(); // Closed List

    // Find the start and goal positions in the environment
    for (int x = 0; x < ENV_DIM; x++) {
        for (int y = 0; y < ENV_DIM; y++) {
            // Find Start Pos
            if (env[x][y] == SYMBOL_START) {
                S = new Node(x, y, 0);
                O->addElement(S);
                std::cout << "Start position is [" << x << "][" << y << "]\n";
                nodesExplored->addElement(S);  // Add the start node to nodesExplored
            }
            // Find End Pos
            if (env[x][y] == SYMBOL_GOAL) {
                G = new Node(x, y, 0);
                std::cout << "Goal position is [" << x << "][" << y << "]\n" << std::endl;;
            }
        }
    }

    if (S == nullptr) {
        std::cout << "No Start Position could be found\n";
        return;
    }
    if (G == nullptr) {
        std::cout << "No Goal Position could be found\n";
        return;
    }

    

    bool searching = false;
    
    while (O->getLength() >0 && ! searching){
        // Select the node p from the open-list P that has the smallest estimated distance (see Section 3.2.2) to goal and, is not in the closed-list C.
        Node* p = O->getSmallestEstDistance(G, C);
        Node* up = nullptr;
        Node* down = nullptr;
        Node* left = nullptr;
        Node* right = nullptr;


        //look at the nodes above, below, left and right of p and set the travel distance
        up = new Node(p->getRow() - 1, p->getCol(), p->getDistanceTraveled() + 1);
        down = new Node(p->getRow() + 1, p->getCol(), p->getDistanceTraveled() + 1);
        left = new Node(p->getRow(), p->getCol() - 1, p->getDistanceTraveled() + 1);
        right = new Node(p->getRow(), p->getCol() + 1, p->getDistanceTraveled() + 1);
        
        //dset bools to determine whether can travel to the nodes above, below, left and right of p
        bool goUp = this->isOpenSpace(up, env);
        bool goDown = this->isOpenSpace(down, env);
        bool goLeft = this->isOpenSpace(left, env);
        bool goRight = this->isOpenSpace(right, env);

        //if nodes can be travelled to, add to the open list if not already stored
        if (goUp) {
            if (!O->contains(up) && !C->contains(up)) {
                O->addElement(up);
                std::cout << "Adding Node[" << up->getRow() << "][" << up->getCol() << "]\n";
                
            }
        }
        if (goDown) {
            if (!O->contains(down) && !C->contains(down)) {
                O->addElement(down);
                std::cout << "Adding Node[" << down->getRow() << "][" << down->getCol() << "]\n";
           
            }
        }
        if (goLeft) {
            if (!O->contains(left) && !C->contains(left)) {
                O->addElement(left);
                std::cout << "Adding Node[" << left->getRow() << "][" << left->getCol() << "]\n";
         
            }
        }
        if (goRight) {
            if (!O->contains(right) && !C->contains(right)) {
                O->addElement(right);
                std::cout << "Adding Node[" << right->getRow() << "][" << right->getCol() << "]\n";

            }
        }

        C->addElement(p); // add a copy of p to the closed list
        nodesExplored->addElement(p); // Add the current node to nodesExplored

        // Check if the current node is the goal
        if (p->getRow() == G->getRow() && p->getCol() == G->getCol()) {
            std::cout << "Goal reached!\n";
            searching = true;
            std::cout << std::endl;
            this->nodesExplored->addElement(p); // Add the goal node to nodesExplored
        }

        //free memory
        delete up;
        delete down;
        delete left;
        delete right;


    }
    
    // Clean up

    delete S;
    delete G;
    delete O;
    delete C;

      
}

bool PathSolver::hasReachedGoal(Node* current, Node* goal) {
    return (*current == *goal);
}

NodeList* PathSolver::getNodesExplored() {
    return this->nodesExplored;
}

NodeList* PathSolver::getPath(Env env){
    NodeList* path = new NodeList();
    //get a deep copy of the nodesExplored list
    //NodeList* nodesExplored = getNodesExplored();

    // get the last node in the nodesExplored list which should be the goal node. This is now the current node
    Node* current = nodesExplored->getNode(nodesExplored->getLength() - 1);

    path->addElement(current);


    // loop through the nodesExplored list backwards until the start node is found
for (int i = nodesExplored->getLength() - 1; i >= 0; i--) {
    Node* node = nodesExplored->getNode(i);

    // check if the node is adjacent to the current node
    if ((node->getRow() == current->getRow() - 1 && node->getCol() == current->getCol()) ||
        (node->getRow() == current->getRow() + 1 && node->getCol() == current->getCol()) ||
        (node->getRow() == current->getRow() && node->getCol() == current->getCol() - 1) ||
        (node->getRow() == current->getRow() && node->getCol() == current->getCol() + 1)) {
        // check if the node is empty
        if (this->isOpenSpace(node, env)) {
            // add the node to the path
            path->addElement(node);
            std::cout << "Adding Node[" << node->getRow() << "][" << node->getCol() << "] to the path\n";
            // set the current node to the node
            current = node;
        }
    }
}

    //reverse the path
    NodeList* reversedPath = new NodeList();
    for(int i = path->getLength() - 1; i >= 0; i--){
        reversedPath->addElement(path->getNode(i));
    }

    return reversedPath;
}

bool PathSolver::isOpenSpace(Node* node, Env env){
    // check if the node is within the bounds of the environment
    if(node->getRow() < 0 || node->getRow() >= ENV_DIM || node->getCol() < 0 || node->getCol() >= ENV_DIM){
        return false;
    }
    // check if the node is a wall
    else if(env[node->getRow()][node->getCol()] == SYMBOL_WALL){
        return false;
    }
    // else the node is empty
    return true;
}


Node* PathSolver::findAdjacentNode(Node* current, Env env) {
    // Find the adjacent node in the nodesExplored list
    for (int i = current->getCol() - 1; i <= current->getCol() + 1; i++) {
        for (int j = current->getRow() - 1; j <= current->getRow() + 1; j++) {
            if (i != current->getCol() || j != current->getRow()) {
                if (i >= 0 && j >= 0 && i < ENV_DIM && j < ENV_DIM) {
                    if (env[j][i] == SYMBOL_EMPTY) {
                        Node* adjacentNode = new Node(j, i, 0);
                        return adjacentNode;
                    }
                }
            }
        }
    }

    // If no adjacent node is found, return nullptr or handle the case accordingly.
    return nullptr;  // You may need to adjust this based on your design.
}




bool PathSolver::CheckEmptySpace(Env env, int row, int col) {
    if (env[row][col] == SYMBOL_EMPTY) {
        return true;
    }
    return false;
}

bool PathSolver::CheckEmptySpaceByNode(Node* node, Env env) {
    int row = node->getRow();
    int col = node->getCol();

    if (env[row][col] == SYMBOL_EMPTY) {
        return true;
    }

    return false;
}

bool PathSolver::CheckGoalNodeByNode(Node* node, Env env) {
    int row = node->getRow();
    int col = node->getCol();

    if (env[row][col] == SYMBOL_GOAL) {
        return true;
    }

    return false;
}

bool NodeList::contains(Node* node) {
    for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; i++) {
        if (nodes[i]->getCol() == node->getCol() && nodes[i]->getRow() == node->getRow()) {
            return true;
        }
    }
    return false;
}

NodeList* PathSolver::getNeighbours(Node* node, bool cond) {
    NodeList* neighbours = new NodeList();
    int row = node->getRow();
    int col = node->getCol();

    // Check if the node is on the edge of the environment
    if (row == 0 || row == ENV_DIM - 1 || col == 0 || col == ENV_DIM - 1) {
        // Check if the node is in the top left corner
        if (row == 0 && col == 0) {
            // Check the right and bottom
            neighbours->addElement(new Node(row, col + 1, 0));
            neighbours->addElement(new Node(row + 1, col, 0));
            neighbours->addElement(new Node(row + 1, col + 1, 0));
        } else if (row == ENV_DIM - 1 && col == 0) {
            // Check the top, right, and bottom
            neighbours->addElement(new Node(row - 1, col, 0));
            neighbours->addElement(new Node(row, col + 1, 0));
            neighbours->addElement(new Node(row - 1, col + 1, 0));
        } else if (row == 0 && col == ENV_DIM - 1) {
            // Check the left, bottom, and bottom left
            neighbours->addElement(new Node(row, col - 1, 0));
            neighbours->addElement(new Node(row + 1, col, 0));
            neighbours->addElement(new Node(row + 1, col - 1, 0));
        } else if (row == ENV_DIM - 1 && col == ENV_DIM - 1) {
            // Check the top, left, and top left
            neighbours->addElement(new Node(row - 1, col, 0));
            neighbours->addElement(new Node(row, col - 1, 0));
            neighbours->addElement(new Node(row - 1, col - 1, 0));
        } else {
            // Check the sides based on the position
            if (row == 0) {
                // Check the left, right, bottom, bottom left, and bottom right
                neighbours->addElement(new Node(row, col - 1, 0));
                neighbours->addElement(new Node(row, col + 1, 0));
                neighbours->addElement(new Node(row + 1, col, 0));
                neighbours->addElement(new Node(row + 1, col - 1, 0));
                neighbours->addElement(new Node(row + 1, col + 1, 0));
            } else if (row == ENV_DIM - 1) {
                // Check the left, right, top, top left, and top right
                neighbours->addElement(new Node(row, col - 1, 0));
                neighbours->addElement(new Node(row, col + 1, 0));
                neighbours->addElement(new Node(row - 1, col, 0));
                neighbours->addElement(new Node(row - 1, col - 1, 0));
                neighbours->addElement(new Node(row - 1, col + 1, 0));
            } else if (col == 0) {
                // Check the top, right, bottom, top right, and bottom right
                neighbours->addElement(new Node(row - 1, col, 0));
                neighbours->addElement(new Node(row + 1, col, 0));
                neighbours->addElement(new Node(row, col + 1, 0));
                neighbours->addElement(new Node(row - 1, col + 1, 0));
                neighbours->addElement(new Node(row + 1, col + 1, 0));
            } else if (col == ENV_DIM - 1) {
                // Check the top, left, bottom, top left, and bottom left
                neighbours->addElement(new Node(row - 1, col, 0));
                neighbours->addElement(new Node(row + 1, col, 0));
                neighbours->addElement(new Node(row, col - 1, 0));
                neighbours->addElement(new Node(row - 1, col - 1, 0));
                neighbours->addElement(new Node(row + 1, col - 1, 0));
            }
        }
    } else {
        // Check the top, left, right and bottom
        neighbours->addElement(new Node(row, col + 1, 0));
        neighbours->addElement(new Node(row + 1, col, 0));
        neighbours->addElement(new Node(row, col - 1, 0));
        neighbours->addElement(new Node(row - 1, col, 0));

        // Additional conditions for adding nodes
        if (cond) {
            // Add nodes based on the condition
            // For example:
            // neighbours->addElement(new Node(row - 1, col - 1, 0));
            // neighbours->addElement(new Node(row - 1, col + 1, 0));
        }
    }

    return neighbours;
}





//-----------------------------