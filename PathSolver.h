#ifndef COSC_ASSIGN_ONE_PATHSOLVER
#define COSC_ASSIGN_ONE_PATHSOLVER 

#include "Node.h"
#include "NodeList.h"
#include "Types.h"

class PathSolver{
public:
    /*                                           */
    /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
    /*                                           */

    // Constructor/Destructor
    PathSolver();
    ~PathSolver();




    // Execute forward search algorithm
    // To be implemented for Milestone 2
    void forwardSearch(Env env);



    // Get a DEEP COPY of the explored NodeList in forward search
    // To be implemented for Milestone 2
    NodeList* getNodesExplored();

    // Execute backtracking and Get a DEEP COPY of the path the 
    // robot should travel
    // To be implemented for Milestone 3
    NodeList* getPath(Env env);

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */

    bool hasReachedGoal(Node* current, Node* goal);
    bool canMoveTo(Node* node, Env env);

private:
    /*                                           */
    /* DO NOT MOFIFY THESE VARIABLES             */
    /*                                           */

    // Nodes explored in forward search algorithm
    NodeList* nodesExplored;

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */
    NodeList* getNeighbours(Node* node, bool cond);
    bool CheckEmptySpace(Env env, int get_row, int get_col);
    bool CheckEmptySpaceByNode(Node* node, Env env);
    void exploreNeighbors(Node* current, Node* goal, const Env& env, NodeList* openList, NodeList* closedList);
    void reconstructPath(Node* start, Node* goal);
    bool CheckGoalNodeByNode(Node* node, Env env);
    Node* findAdjacentNode(Node* current, Env env);


};




#endif //COSC_ASSIGN_ONE_PATHSOLVER