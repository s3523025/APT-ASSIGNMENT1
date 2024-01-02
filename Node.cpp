#include "Node.h"
#include <iostream>


Node::Node(int row, int col, int dist_traveled)
{
    Node::row = row;
    Node::col = col;
    Node::dist_traveled = dist_traveled;
}

Node::~Node(){
    // TODO
}

int Node::getRow(){
    return this->row;
}

int Node::getCol(){
    return this->col;
}

int Node::getDistanceTraveled(){
    return this->dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{
    Node::dist_traveled = dist_traveled;
}

int Node::getEstimatedDist2Goal(Node* goal){
    // Using the manhattan distance
    return (getDistanceTraveled() + ((getCol() - goal->getCol()) + (getRow() - goal -> getRow())));
}
    
//--------------------------------                             