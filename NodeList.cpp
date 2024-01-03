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

NodeList::NodeList(NodeList& other){
    // TODO
}

Node* NodeList::pop() {
    if (length > 0) {
        Node* poppedNode = nodes[length - 1];
        length--;
        return poppedNode;
    } else {
        return nullptr;  
    }
}

int NodeList::getLength(){
    return length;
}

void NodeList::addElement(Node* newPos){
    if (length < NODE_LIST_ARRAY_MAX_SIZE) {
        nodes[length] = newPos;
        length++;
    }
    else{
        std::cout << "Error: NodeList is full. Cannot add more elements." << std::endl;
    }
}

Node* NodeList::getNode(int i){
    return nodes[i];
}

Node* NodeList::getSmallestEstDistance(Node* goalNode, NodeList* closedList) {


    // loop through all nodes and find the one with the smallest estimated distance
    Node* smallestNode = nullptr;

    for(int i = 0; i < this->length; i++){
        // Skip if the node is in the closed list
        if(closedList->contains(this->nodes[i])){
            continue;
        }

        // calculate the estimated distance of the current node
        int currentEstDistance = this->nodes[i]->getDistanceTraveled() + this->nodes[i]->getEstimatedDist2Goal(goalNode);
        // If this is the first node or it has a smaller estimated distance, set it as the smallest node
        if(smallestNode == nullptr || currentEstDistance < smallestNode->getDistanceTraveled() + smallestNode->getEstimatedDist2Goal(goalNode)){
            smallestNode = this->nodes[i];
        }
    }


    return smallestNode;
}



