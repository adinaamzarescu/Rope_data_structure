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

    RopeNode *new_root = makeRopeNode(my_strdup(EMPTY)); 
    new_root->left = rt1->root;
    new_root->right = rt2->root;

    new_root->weight = getNodeWeight(rt1->root);
    
    RopeTree *new_tree = makeRopeTree(new_root);
    return new_tree;
}

RopeNode* concat_n(RopeNode* rn1, RopeNode* rn2) {
    RopeNode *new_root = makeRopeNode(my_strdup(EMPTY));

    new_root->weight = rn1->weight;
    new_root->left = rn1;
    new_root->right = rn2;

    return new_root;
}

static char __indexRope(RopeNode *rn, int idx) {
    if(rn->weight <= idx && rn->right){
        return __indexRope(rn->right, idx - rn->weight);
    }

    if(rn->left){
        return __indexRope(rn->left, idx);
    }
    
    return rn->str[idx];
}

char indexRope(RopeTree* rt, int idx) {
    if (rt->root != NULL) {
        return __indexRope(rt->root, idx);
    }
    return 0;
}

char* search(RopeTree* rt, int start, int end) {
    char *c = calloc(end - start + 1, sizeof(char));
    for(int i = start; i < end; i++)
        c[i - start] = indexRope(rt, i);
    return c;
}

RopeNode *copy_tree(RopeNode *rn) {
	if(!rn)
    	return;
    
    RopeNode* copy_node = makeRopeNode(my_strdup(rn->str));
    copy_node->weight = rn->weight;
    
    copy_node->left = copy_tree(rn->left);
    copy_node->right = copy_tree(rn->right);
    
    return copy_node;
}

static void split_one(RopeNode* rn, int *idx) {

    unsigned int i;

	if (rn->left == NULL && rn->right == NULL) {
		if (*idx != NULL) {
			char *str1 = malloc(*idx + 1);
			char *str2 = malloc(rn->weight - *idx + 1);
			
			for (i = 0; i < *idx; ++i)
   				str1[i] = (rn->str)[i];
   			str1[i] = '\0';

   			for (i = *idx; i < rn->weight; ++i)
   				str2[i - *idx] = (rn->str)[i];
   			str2[i - *idx] = '\0';

			free((void *)(rn->str));
			rn->str = my_strdup(EMPTY);

			RopeNode *rn1 = makeRopeNode(str1);
			RopeNode *rn2 = makeRopeNode(str2);

			rn->left = rn1;
			rn->right = rn2;
			rn->weight = getNodeWeight(rn->left);
		}

		return;
	}

	int weight = getNodeWeight(rn->left);

	if (*idx < weight) {
		split_one(rn->left, idx);
	} else {
		*idx -= weight;
		split_one(rn->right, idx);
	}
}

static RopeNode* split_two(RopeNode* rn, int *idx, char c) {

    int weight;

    if ((rn->right->str)[0] == c && (rn->left->str)[0] != c) {
        RopeNode* right_copy = rn->right;

		rn->right = NULL;

		return right_copy;
    } else if ((rn->left->str)[0] == c) {
        RopeNode* right_copy = rn->right;
		RopeNode* left_copy = rn->left;

		rn->right = NULL;
		rn->left = NULL;

		return concat_n(left_copy, right_copy);
    }

	weight = getNodeWeight(rn->left);

    if (*idx >= weight) {
        *idx -= weight;
		return split_two(rn->right, idx, c);
    } else if (*idx < weight) {
        RopeNode *right_two = rn->right;

		rn->right = NULL;

		return concat_n(split_two(rn->left, idx, c), right_two);
    }
}

SplitPair split(RopeTree* rt, int idx) {
    SplitPair pair;
    int idx_copy;
    char index;

    RopeNode* new_root = tree_copy(rt->root);

    if (idx >= getNodeWeight(new_root)) {
        pair.right = NULL;
    	pair.left = new_root;
    	return pair;
    }

    idx_copy = idx;
    index = indexRope(rt, idx_copy);

	idx_copy = idx;
	first_split(new_root, &idx_copy);

	idx_copy = idx;
    pair.right = second_split(new_root, &idx_copy, index);
    pair.left = new_root;
    
    return pair;
}

RopeTree* insert(RopeTree* rt, int idx, const char* str) {
    // TODO 5. Insert - 5p
}

RopeTree* delete(RopeTree* rt, int start, int len) {
    // TODO 6. Delete - 5p 
}

char* my_strdup(char* str)
{
	int len;
	char* dup;

	len = strlen(str) + 1;
	dup = malloc(len);
	if(!dup)
		return NULL;
	dup = strcpy(dup, str);
	dup[len - 1] = '\0';
	return (dup);
}

// FINAL 10p -> complex test involving all operations
