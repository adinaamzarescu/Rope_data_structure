#include "../rope.h"
#include <stdio.h>
#include <stdlib.h>

const char* strs[] = {"123", "1234", "1234567", "0", "!?"};

int main() {

    RopeTree *r1, *r2, *r3, *r4, *r5, *r6;
    r1 = makeRopeTree(makeRopeNode("A"));
    r2 = makeRopeTree(makeRopeNode("BCDE"));
    r3 = makeRopeTree(makeRopeNode("F"));
    r4 = makeRopeTree(makeRopeNode("GH"));
    r5 = makeRopeTree(makeRopeNode("IJKL"));
    r6 = makeRopeTree(makeRopeNode("M"));

    RopeTree* rtc = concat(concat(concat(concat(concat(r1, r2), r3), r4), r5), r6);
    printRopeTree(rtc);

    rtc = insert(rtc, 12, "123");
    printRopeTree(rtc);
    rtc = insert(rtc, 3, "45");
    printRopeTree(rtc);
    rtc = insert(rtc, 3, "67");
    printRopeTree(rtc);

    rtc = delete(rtc, 0, 2);
    printRopeTree(rtc);
    rtc = delete(rtc, 12, 1);
    printRopeTree(rtc);
    rtc = delete(rtc, 5, 3);
    printRopeTree(rtc);

    printf("str[4]:%c\nstr[8]:%c\nstr[10]:%c\n", indexRope(rtc, 4), indexRope(rtc, 8), indexRope(rtc, 10));

    printf("str[0:2]:%s\nstr[4:7]:%s\nstr[9:10]:%s\n", search(rtc, 0, 2), search(rtc, 4, 7), search(rtc, 9, 10));

    return 0;
}
