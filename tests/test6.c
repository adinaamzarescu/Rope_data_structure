#include "../rope.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    RopeNode *rn1, *rn2, *rn3, *rn4, *rn5, *rn6, *rn7;
    RopeTree *rt;

    rn1 = makeRopeNode("abc");
    rn2 = makeRopeNode("de");
    rn3 = makeRopeNode("fghi");
    rn4 = makeRopeNode("jklmn");
    rn5 = makeRopeNode(EMPTY);
    rn6 = makeRopeNode(EMPTY);
    rn7 = makeRopeNode(EMPTY);

    rn5->left = rn1;
    rn5->right = rn2;
    rn5->weight = 3;

    rn6->left = rn3;
    rn6->right = rn4;
    rn6->weight = 4;

    rn7->left = rn5;
    rn7->right = rn6;
    rn7->weight = 5;

    rt = makeRopeTree(rn7);

    for (int i = 1; i < 14; ++i) {
        for (int j = 0; j < 14; ++j) {
            printRopeTree(delete(rt, j, i));
        }
        printf("%s", "\n");
    }

    return 0;
}
