#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "nodes.h"
// Chase Stuk
// Last Modified : 2/4/2022
// Date Created : 3/31/2022


//puzzle functions
void printStatus(int var[]);
int verifyStatus(int var[], int Status[]);
int *movePuzzle(int var[], move action);
int zeroSearch(int var[]);
int *exchange(int n1, int n2, int estado[]);

//data structure funcs
tree createNode(tree father, move action, int var[]);
void pushBorder(End* queue, tree node);
void Push(End* queue, tree node);
tree Pop(End* queue);
int emptyQueue(End c);


//heuristic functions
int manhattanDistance(int var[]);
int outOfPlace(int estado[]);

//search functions
int starSearch(int var[]);
int findNode(End set,int var[]);
int exploredNodes = 0;
int createdNodes = 0;
int borderNodes = 0;
int goalState[boxes] = {1,2,3,8,0,4,7,6,5};

int main(void){
   int var[boxes] = {2,8,3,6,7,4,1,5,0};
    printf("\nSolution Found!\n");
    system("PAUSE");
    starSearch(var);
    return 0;
}

int emptyQueue(End c) {
    return (c == NULL);
}


int verifyStatus(int var[], int otherState[]) {

    int i;
    // compares each array element and returns false if fail
    for (i = 0; i < boxes; i++) {
        if (var[i] != otherState[i])
            return False;
    }
    return True;
}


void printStatus(int var[]){
    int i;
    for(i = 0; i < boxes;i++){
        if(i % 3 == 0)
            printf("\n\n");
        printf("%d\t",var[i]);
    }
    printf("\n\n");
}


void pushBorder(End *queue, tree node) {
    pNode newNode, anterior;

    newNode = (End)malloc(sizeof(nodeType));
    newNode->nTree = node;

    // add element to empty queue
    if(emptyQueue(*queue) || (*queue)->nTree->h > node->h) {
        newNode->following = *queue;
        *queue = newNode;
    } else {
        // find lowest heuristic
        anterior = *queue;
        // go until last element or next element has a value greater than heuristic of node we want
        while(anterior->following && anterior->following->nTree->h <= node->h)
            anterior = anterior->following;
        newNode->following = anterior->following;
        anterior->following = newNode;
    }
}



void Push(End *queue, tree node){

    End new_;
    //assign data to node
    new_ = (End)malloc(sizeof(nodeType));
    //point to start of queue
    new_->nTree = node;
    new_->following = *queue;
    *queue = new_;
}


tree Pop(End *queue){
    // 2 nodes created
    End node,aux = NULL;
    aux=*queue;
    node = *queue;
    if(!node) return 0;
    *queue = node->following;
    return aux->nTree;
}


//////////////////////////////////////////////////////////////////////////

int *movePuzzle(int state[], move action){
    int location = zeroSearch(state);
    int *newState = NULL;
   if(location == 0){
        if(action == above)
            return state;
        if(action == below){
            newState = exchange(0, 3, state);
            return newState;
        }
        if(action == left)
            return state;
        if(action == right){
            newState = exchange(0, 1, state);
            return newState;
        }
   }
   if(location == 1){
        if(action == above)
            return state; // no option
        if(action == below){
            newState = exchange(1, 4, state);
            return newState;
        }
        if(action == left){
            newState = exchange(1, 0, state);
            return newState;
        }
        if(action == right){
            newState = exchange(1, 2, state);
            return newState;
        }
   }
   if(location == 2){
        if(action == above)
            return state;
        if(action == below){
            newState = exchange(2, 5, state);
            return newState;
        }
        if(action == left){
            newState = exchange(1, 2, state);
            return newState;
        }
        if(action == right)
            return state;
   }


   if(location == 3){
        if(action == above){
            newState = exchange(0, 3, state);
            return newState;
        }
        if(action == below){
            newState = exchange(3, 6, state);
            return newState;
        }
        if(action == left)
            return state;
        if(action == right){
            newState = exchange(3, 4, state);
            return newState;
        }
   }
   if(location == 4){
        if(action == above){
            newState = exchange(1, 4, state);
            return newState;
        }
        if(action == below){
            newState = exchange(4, 7, state);
            return newState;
        }
        if(action == left){
            newState = exchange(4, 3, state);
            return newState;
        }
        if(action == right){
            newState = exchange(4, 5, state);
            return newState;
        }
   }
   if(location == 5){
        if(action == above){
            newState = exchange(2, 5, state);
            return newState;
        }
        if(action == below){
            newState = exchange(5, 8, state);
            return newState;
        }
        if(action == left){
            newState = exchange(4, 5, state);
            return newState;
        }
        if(action == right)
            return state;
   }


   if(location == 6){
        if(action == above){
            newState = exchange(3, 6, state);
            return newState;
        }
        if(action == below)
            return state;
        if(action == left)
            return state;
        if(action == right){
            newState = exchange(6, 7, state);
            return newState;
        }
   }
   if(location == 7){
        if(action == above){
            newState = exchange(4, 7, state);
            return newState;
        }
        if(action == below)
            return state;
        if(action == left){
            newState = exchange(6, 7, state);
            return newState;
        }
        if(action == right){
            newState = exchange(7, 8, state);
            return newState;
        }
   }
   if(location == 8){
        if(action == above){
            newState = exchange(5, 8, state);
            return newState;
        }
        if(action == below)
            return state;
        if(action == left){
            newState = exchange(7, 8, state);
            return newState;
        }
        if(action == right)
            return state;
   }
}

// loops until 0
int zeroSearch(int estado[]){
    int i;
    for(i = 0; i < boxes; i++){
        if(estado[i] == 0)
            return i;
    }
}

//swaps two state elements
int *exchange(int n1, int n2, int state[]){
    int aux = state[n1];
    state[n1] = state[n2];
    state[n2] = aux;
    return state;
}


tree createNode(tree father,move action, int state[]){
    tree node = NULL;
    int *temp;
    int temp2[boxes];
    int i;
    node = (tree)malloc(sizeof(treeNodeType));
    if(father == NULL){
        for(i = 0; i < boxes; i++){
            temp2[i] = state[i];
            node->condition[i] = temp2[i];
        }
        node->father = NULL;
        node->action = action;
        node->cost = 0;
        return node;
    }

    for(i = 0; i < boxes; i++)
        temp2[i] = state[i];
    temp = movePuzzle(temp2, action);
    for(i = 0; i < boxes; i++)
        node->condition[i] = temp[i];
    node->father = father;
    node->action = action;
    node->cost = (int)father->cost + 1;
    node->h = outOfPlace(node->condition) + node->cost;
    return node;
}

int starSearch(int estado[]){
    int i;
    tree node = NULL;
    tree son = NULL;
    move m;
    End border = NULL;
    End explored = NULL;
    End action = NULL;
    // create father node
    node = createNode(NULL,left,estado);
    // initial state
    printf("Initial State");
    printStatus(node->condition);
    // check inital node
    if(verifyStatus(node->condition,goalState) == True){
        printf("\nSolution Found\n");
        printf("\nLevel Reached: %d\n", node->cost);
        return True;
    }
    // add node to border
    pushBorder(&border, node);
    borderNodes++;
    do{
        if(border == NULL)
            return False;
        //remove node from border
        node = Pop(&border);
        borderNodes--;
        Push(&explored, node);
        exploredNodes++;
        // create child for each action
        for(i = 0; i < 4; i++){
            if(i==0) m = above;
            if(i==1) m = below;
            if(i==2) m = left;
            if(i==3) m = right;

            son = createNode(node,m,node->condition);
            createdNodes++;
            if(findNode(explored,son->condition) == False && findNode(border,son->condition) == False){
                //verify child node
                if(verifyStatus(son->condition,goalState) == True){
                    printf("\n-----------------------------------------------------------\n");
                    printf("\n Solution Found! \n");
                    printf("\n-----------------------------------------------------------\n");
                    printf("\n Reached Level:  %d\n", son->cost);
                    printf("\n Nodes Created: %d\n", createdNodes);
                    printf("\n-----------------------------------------------------------\n");
                    while(son->father != NULL){
                        Push(&action, son);
                        son = son->father;
                    }
                    // display what was used to reach solution
                    while(action != NULL){
                        son = Pop(&action);
                        printf("\nHeuristic A* Cost: %d\n",son->h);
                        printf("\nAction: ");
                        if(son->action == left){
                            printf("left\n");
                        }
                        if(son->action == right){
                            printf("right\n");
                        }
                        if(son->action == above){
                            printf("above\n");
                        }
                        if(son->action == below){
                            printf("below\n");
                        }
                        printStatus(son->condition);
                    }
                    return True;
                }
                else{
                    pushBorder(&border,son);
                    borderNodes++;
                }
            }
        }
    }while(True);
    return False;
}

int findNode(End set, int state[]){
    End node = set;
    if(node == NULL)
        return False;
    while(node){
        if(verifyStatus(node->nTree->condition,state) == True){
            return True;
        }
        node = node->following;
    }
    return False;
}

// function for calculating manhattan distance
int manhattanDistance(int state[]) {
    int distanceSum = 0;
    int i, var = 0;
    //calculate distance
    for (i = 0; i < boxes; i++) {
        if (state[i] != goalState[i]) {
            if (i != 8 && state[i] == 0) {
                var = abs(9 - goalState[i]);
            }
            else if (i == 8 && state[8] != 0) {
                var = abs(9 - state[i]);
            }
            else {
                var = abs(state[i] - goalState[i]);
            }
            distanceSum += var;
        }
    }
    return distanceSum;
}

//function to compute heuristic
int outOfPlace(int estado[]){
    int sum = 0;
    int i, j;
    for(i = 0; i < boxes; i++){
        if(estado[i] != goalState[i])
            sum++;
    }
    return sum;
}
