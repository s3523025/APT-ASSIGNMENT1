#include "NodeList.h"
#include <iostream>

NodeList::NodeList(){
    //Constructor
    length = 0;
    for (int i = 0; i< NODE_LIST_ARRAY_MAX_SIZE; i++){
        nodes[i] = new Node(0,0,0);
    }
}

NodeList::~NodeList(){
    for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; i++){
        delete nodes[i];
    }
}

int NodeList::getLength(){
    return length;
}

void NodeList::addElement(Node* newPos) {
    // Check if there is space in the array
    if (this->length < NODE_LIST_ARRAY_MAX_SIZE) {
        // Add the new node to the end of the array
        this->nodes[this->length] = new Node(newPos->getRow(), newPos->getCol(), newPos->getDistanceTraveled());
        this->length++;
    }
}

Node* NodeList::getNode(int i) {
    // Check if i is within the bounds of the array
    if (i < this->length) {
        // Return the node at index i
        return this->nodes[i];
    }
    // Return NULL if i is out of bounds
    return NULL;
}

Node* NodeList::getSmallestEstDistance(Node* goalNode, NodeList* closedList) {
    // loop through nodes and find the one with the smallest estimated distance
    Node* smallestNode = nullptr;

    for(int i = 0; i < this->length; i++){
        // Skip if the node is in the closed list
        if(closedList->contains(this->nodes[i])){
            continue;
        }

        // calculate the estimated distance of the current node
        int currentEstDistance = this->nodes[i]->getDistanceTraveled() + this->nodes[i]->getEstimatedDist2Goal(goalNode);
        // If this is the 1st node or it has a lesser estimated distance, set it as the smallest node
        if(smallestNode == nullptr || currentEstDistance < smallestNode->getDistanceTraveled() + smallestNode->getEstimatedDist2Goal(goalNode)){
            smallestNode = this->nodes[i];
        }
    }

    return smallestNode;
}





