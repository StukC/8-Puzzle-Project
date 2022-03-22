#ifndef nodes_h_included
#define nodes_h_included
#define False   0
#define True    1
#define boxes    9
#define MAX     4

enum move { above = 3, below, left, right, state };

//node for tree
typedef struct _node {
    int condition[boxes];
    int cost;
    int h;
    move action;
    struct _node* father;
} treeNodeType;
typedef treeNodeType* tree;


//Node for queue and list
typedef struct node {
    tree nTree;
    struct node* following;
}nodeType;

typedef nodeType* End;

typedef nodeType* pNode;

#endif 
