#include "./rope.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "utils.h"

#define EMPTY ""



RopeNode* makeRopeNode(const char* str) {
    RopeNode *new_node = malloc(sizeof(*new_node));
    DIE(!new_node, "New node malloc failed");

    new_node->left = NULL;
    new_node->right = NULL;
    new_node->str = str;
    new_node->weight = 0;

    return new_node;
}

RopeTree* makeRopeTree(RopeNode* root) {
    if(!root)
        return 0;

    RopeTree *new_tree = malloc(sizeof(*new_tree));
    DIE(!new_tree, "New tree malloc failed");

    new_tree->root = root;
    return new_tree;
}


void printRopeNode(RopeNode* rn) {

    if (!rn)
        return;

    if (!(rn->left) && !(rn->right)) {
        printf("%s", rn->str);
        return;
    }

    printRopeNode(rn->left);
    printRopeNode(rn->right);
}

void printRopeTree(RopeTree* rt) {

    if (rt && rt->root) {
        printRopeNode(rt->root);
        printf("\n");
    }
}

void debugRopeNode(RopeNode* rn, int indent) {
    if (!rn)
        return;

    for (int i = 0; i < indent; ++i)
        printf("%s", " ");

    if (!strcmp(rn->str, EMPTY))
        printf("# %d\n", rn->weight);
    else
        printf("%s %d\n", rn->str, rn->weight);

    debugRopeNode(rn->left, indent+2);
    debugRopeNode(rn->right, indent+2);
}


int getNodeWeight(RopeNode *rt) {
    if(!rt)
        return 0;

    if(!rt->left && !rt->right)
        return rt->weight;

    return (getNodeWeight(rt->left) + getNodeWeight(rt->right));
}


RopeTree* concat(RopeTree* rt1, RopeTree* rt2) {

    RopeNode *new_root = makeRopeNode(0); 
    new_root->left = rt1->root;
    new_root->right = rt2->root;

    new_root->weight = getNodeWeight(rt1->root);
    
    RopeTree *new_tree = makeRopeTree(new_root);
    return new_tree;
}



char indexRope(RopeTree* rt, int idx) {
    RopeNode *current= rt->root;
    if(current->weight < idx && current->right != NULL){
        rt->root = current->right;
        return indexRope(rt, idx - current->weight);
    }
    if(current->left != NULL){
        rt->root = current->left;
        return indexRope(rt, idx);
    }
    return current->str[idx];
}

char* search(RopeTree* rt, int start, int end) {
    char *c = malloc(sizeof(char) * (end - start));
    for(int i = start; i < end; i++)
        c[i - start] = indexRope(rt, i);
    return c;
}

// SplitPair split(RopeTree* rt, int idx) {
//     RopeNode *left = makeRopeNode(strdup(EMPTY));
//     RopeNode *right = makeRopeNode(strdup(EMPTY));
//     right = left ->right;
//     left->right = NULL;

//     left->weight = getNodeWeight(left);

//     RopeTree *tree1 = makeRopeTree(left),
//              *tree2 = makeRopeTree(right);
    
//     tree1->root = left;
//     tree1->root->weight = left->weight;
    


// }

// RopeTree* insert(RopeTree* rt, int idx, const char* str) {
//     // TODO 5. Insert - 5p
//     debugRopeNode(rt->root, rt->root->weight);
//     
    
//     // RopeNode *new_node = ;
// }

// RopeTree* delete(RopeTree* rt, int start, int len) {
//     // TODO 6. Delete - 5p
     
// }

// // FINAL 10p -> complex test involving all operations
