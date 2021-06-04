# Rope data structure
_______________________________________________________________________________________________________________________
This is the third university project for the Data Structures course.

Copyright 2021 Amzarescu Adina-Maria & Popescu Maria-Mateea
_______________________________________________________________________________________________________________________
__-> data structure composed of smaller strings that is used to efficiently store and manipulate a very long string.__
_______________________________________________________________________________________________________________________

A rope is a binary tree where each leaf (end node) holds a string and a length (also known as a "weight"), and each
node further up the tree holds the sum of the lengths of all the leaves in its left subtree. A node with two children
thus divides the whole string into two parts: the left subtree stores the first part of the string, the right subtree
stores the second part of the string, and a node's weight is the length of the first part.

__Operations__

  __1. Concatenation__
  
   Join 2 ropes(s1 and s2) by adding another knot that
will become the root and its weight becomes the sum of weights of leaf
nodes in S1.

__2. Index__

  Find the character at ith position.
  
__3. Search__

  Find the characters between 2 positions.

__4. Split__

  Divide the rope into 2 on position i and there are 2 cases:
  
      * Split point being the last character of a leaf node
      * Split point being a middle character of a leaf node.

__5. Insertion__

  Add a string at position i by splitting the rope at this
position followed by 2 concatenations.

__6. Deletion__

  Delete a string from an interval by 2 splits of the rope
followed by a concatenation.
