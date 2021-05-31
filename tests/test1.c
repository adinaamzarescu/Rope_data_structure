#include "../rope.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strdup(const char *s);

const char* strs[] = {"Ana", "are", "mere", "legume", "o", "mandarine"};

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

    for (unsigned int i = 0; i < sizeof(strs) / sizeof(const char*); ++i) {
        rt1 = concat(checkerMakeRopeTree(checkerMakeRopeNode(strdup(strs[i]))), rt);
        printRopeTree(rt1);
        rt2 = concat(rt, checkerMakeRopeTree(checkerMakeRopeNode(strdup(strs[i]))));
        printRopeTree(rt2);
        printf("\n");

        free((void*)rt1->root->str);
        free(rt1->root);
        free(rt1);

        free((void*)rt2->root->str);
        free(rt2->root);
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
