#include "../rope.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* strdup(const char*);

RopeNode* rnallocated[1000];
RopeTree* rtallocated[1000];
int numrn = 0;
int numrt = 0;

RopeNode * checkerMakeRopeNode(const char *str) {
   rnallocated[numrn] = makeRopeNode(str);
   return rnallocated[numrn++];
}

RopeTree * checkerMakeRopeTree(RopeNode * rn) {
   rtallocated[numrt] = makeRopeTree(rn);
   return rtallocated[numrt++];
}   

RopeNode* copyRopeNode(RopeNode* rn) {
    if (!rn)
        return NULL;

    RopeNode* new_rn = checkerMakeRopeNode(strdup(rn->str));
    new_rn->left = copyRopeNode(rn->left);
    new_rn->right = copyRopeNode(rn->right);
    return new_rn;
}

RopeTree* copyRopeTree(RopeTree* rt) {
    if (!rt)
        return NULL;

    RopeTree* new_rt = checkerMakeRopeTree(copyRopeNode(rt->root));
    return new_rt;
}

void freeRopeNode(RopeNode* rn) {
    if (rn == NULL)
        return;
    for (int i = 0; i < numrn; ++i)
        if (rn == rnallocated[i])
            return;

    free((void*)rn->str);
    freeRopeNode(rn->left);
    freeRopeNode(rn->right);
    free(rn);
}

//void freeRopeTree(RopeTree* rt) {
//    if (!rt)
//        return;
//
//    freeRopeNode(rt->root);
//}




int main() {

    RopeNode *rn1, *rn2, *rn3, *rn4, *rn5, *rn6, *rn7;
    RopeTree *rt, *rt1, *rt2;

    rn1 = checkerMakeRopeNode(strdup("abc"));
    rn2 = checkerMakeRopeNode(strdup("de"));
    rn3 = checkerMakeRopeNode(strdup("fghi"));
    rn4 = checkerMakeRopeNode(strdup("jklmn"));
    rn5 = checkerMakeRopeNode(strdup(EMPTY));
    rn6 = checkerMakeRopeNode(strdup(EMPTY));
    rn7 = checkerMakeRopeNode(strdup(EMPTY));

    rn5->left = rn1;
    rn5->right = rn2;
    rn5->weight = 3;

    rn6->left = rn3;
    rn6->right = rn4;
    rn6->weight = 4;

    rn7->left = rn5;
    rn7->right = rn6;
    rn7->weight = 5;

    rt = checkerMakeRopeTree(rn7);

    for (int i = 0; i < 15; ++i) {
        SplitPair sp = split(rt, i); 
        rt1 = makeRopeTree(sp.left);
        printRopeTree(rt1);
        rt2 = makeRopeTree(sp.right);
        printRopeTree(rt2);
        printf("\n");
        freeRopeNode(sp.left);
        free(rt1);
        freeRopeNode(sp.right);
        free(rt2);
    }

    for (int i = 0; i < numrn; i++) {
        free((void*)rnallocated[i]->str);
        free(rnallocated[i]);
    }

    for (int i = 0; i < numrt; i++) {
        free(rtallocated[i]);
    }

    return 0;
}
