#include "rope.h"
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
	new_node->weight = strlen(str);

	return new_node;
}

RopeTree* makeRopeTree(RopeNode* root) {
	if (!root)
		return NULL;

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
	if (!rt)
		return 0;

	if (!rt->left && !rt->right)
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

// Recursive function to find the index
char __indexRope(RopeNode *rn, int idx) {
	// If the weight isn't more than the given index
	if (rn->weight <= idx && rn->right) {
		return __indexRope(rn->right, idx - rn->weight);
	}
	// Only if the left node exists
	if (rn->left) {
		return __indexRope(rn->left, idx);
	}

	return rn->str[idx];
}

char indexRope(RopeTree* rt, int idx) {
	if (rt->root) {
		return __indexRope(rt->root, idx);
	}
	return 0;
}

char* search(RopeTree* rt, int start, int end) {
	char *c = calloc(end - start + 1, sizeof(char));
	for (int i = start; i < end; i++)
		// The index has to be i - start
		c[i - start] = indexRope(rt, i);
	return c;
}
// Concatenantion of nodes
RopeNode* concat_n(RopeNode* rn1, RopeNode* rn2) {
	RopeNode *new_root = makeRopeNode(my_strdup(EMPTY));
	if (rn1 && rn2) {
		// Asigning values and adresses to the new node
		new_root->weight = rn1->weight;
		new_root->left = rn1;
		new_root->right = rn2;
	}
	return new_root;
}

// Function to copy the given tree
RopeNode *copy_tree(RopeNode *rn) {
	if (!rn)
		return NULL;

	RopeNode* copy_node = makeRopeNode(my_strdup(rn->str));
	copy_node->weight = rn->weight;

	copy_node->left = copy_tree(rn->left);
	copy_node->right = copy_tree(rn->right);
	return copy_node;
}

void split_one(RopeNode* rn, int *idx) {
	int i;
	// Only if the nodes don't exist
	if (rn->left == NULL && rn->right == NULL) {
		if (*idx != 0) {
			// Allocating memory for the strings
			char *s1 = malloc(*idx + 1);
			char *s2 = malloc(rn->weight - *idx + 1);
			// Building the first string
			for (i = 0; i < *idx; ++i)
				s1[i] = (rn->str)[i];
			s1[i] = '\0';
			// Building the second string
			for (i = *idx; i < rn->weight; ++i)
				s2[i - *idx] = (rn->str)[i];
			s2[i - *idx] = '\0';
			// Emptying the node
			free((void *)(rn->str));
			rn->str = my_strdup(EMPTY);
			// Creating 2 new nodes
			// Those nodes have the strings
			// created above
			RopeNode *rn1 = makeRopeNode(s1),
					 *rn2 = makeRopeNode(s2);
			
			// Linking them to the given
			// node of the rope
			rn->left = rn1;
			rn->right = rn2;
			// The weight is only the left's
			rn->weight = getNodeWeight(rn->left);
		}

		return;
	}

	int weight = getNodeWeight(rn->left);

	if (*idx < weight) {
		// Recursivelly calling the function
		split_one(rn->left, idx);
	} else {
		// Substracting the weight
		*idx = *idx - weight;
		// Recursivelly calling the function
		split_one(rn->right, idx);
	}
}

RopeNode* split_two(RopeNode* rn, int *idx, char c) {
	int weight;
	// Only if the nodes exist
	if (rn->right && rn->left) {
		// If the first character of the right node's string
		// is equal to the given character and the
		// first character of the left node's string
		// is not equal to the given character
		if ((rn->right->str)[0] == c && (rn->left->str)[0] != c) {
			RopeNode* right_copy = rn->right;
			// The right node has to be empty
			rn->right = NULL;
			// Returning the copy
			return right_copy;
		} else if ((rn->left->str)[0] == c) {
		// If the first character of the left node's string
		// is equal to the given character
			// Creating copies
			RopeNode* right_copy = rn->right;
			RopeNode* left_copy = rn->left;
			// The nodes has to be empty
			rn->right = NULL;
			rn->left = NULL;
			// Recursivelly calling the function
			// with the copies created above
			return concat_n(left_copy, right_copy);
		}
		// The weight is only the left node's weight
		weight = getNodeWeight(rn->left);

		if (*idx >= weight) {
			*idx = *idx - weight;
			return split_two(rn->right, idx, c);
		} else if (*idx < weight) {
			RopeNode *right_two = rn->right;

			rn->right = NULL;
			// If the index is lower than thw weight
			// the concat function is called
			// with the split function between
			// the left node, the index and the given character c
			// and the right copy
			return concat_n(split_two(rn->left, idx, c), right_two);
		}
	}

	return NULL;
}

SplitPair split(RopeTree* rt, int idx) {
	SplitPair pair;
	int idx_copy;
	char index;

	idx_copy = idx;
	// Creating a new root
	RopeNode* new_root = copy_tree(rt->root);
	// If the index is higher than the weight of the new root
	if (idx >= getNodeWeight(new_root)) {
		pair.left = new_root;
		pair.right = makeRopeNode(my_strdup(EMPTY));
		return pair;
	}

	index = indexRope(rt, idx_copy);
	// First split
	idx_copy = idx;
	split_one(new_root, &idx_copy);
	// Second split
	idx_copy = idx;
	pair.right = split_two(new_root, &idx_copy, index);
	pair.left = new_root;

	return pair;
}
// Creating a strdup function
char* my_strdup(const char* str)
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

RopeTree* insert(RopeTree* rt, int idx, const char* str) {
	// One split and a concatenation
	if(!rt)
		return NULL;

	SplitPair pair = split(rt, idx);

	RopeNode *new_node = makeRopeNode(str),
			 *new_root = concat_n(pair.left, new_node),
			 *final_node = concat_n(new_root, pair.right);

	RopeTree *new_tree = makeRopeTree(final_node);

	return new_tree;
}

RopeTree* delete(RopeTree* rt, int start, int len) {
	// Two splits and a concatenation
	if(!rt)
		return NULL;

	SplitPair pair_one = split(rt, start),
			  pair_two = split(rt, start + len);

	RopeNode *new_root = concat_n(pair_one.left, pair_two.right);
	RopeTree *new_tree = makeRopeTree(new_root);

	return new_tree;
}
