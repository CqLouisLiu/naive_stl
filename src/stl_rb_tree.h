//
// Created by Shuai on 2017/8/16.
//

#ifndef NAIVE_STL_STL_RB_TREE_H
#define NAIVE_STL_STL_RB_TREE_H

/*
 * RB-Tree(Red-black tree)
 * Different from Binary tree, Red-black tree keep the average
 * height in range [logN,2*long(N+1)] always;
 *
 * 1: Every node is colored either red or black;
 * 2: The root of RB-Tree is black;
 * 3: The parent and children node can't be red meanwhile;
 * 4: Every path from a node to a null pointer must contain the same
 *    number of black nodes.
 * 5: When insert node into RB-Tree, the new node must be red and only if its
 *    parent is black, the insert operation is done. Otherwise, adjust the RB-Tree;
 */
namespace naive{


}


#endif //NAIVE_STL_STL_RB_TREE_H
