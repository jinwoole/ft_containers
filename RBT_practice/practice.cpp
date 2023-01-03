#include <iostream>
#include <stdlib.h>

enum Color { RED, BLACK };
struct RBTNode
{
    struct RBTNode* parent; //회전을 구현하는데 필요하다.
    struct RBTNode* left;
    struct RBTNode* right;
    int data;
    enum Color color;
};

static RBTNode* NIL;

void rbt_set()
{
    NIL = (RBTNode*)malloc(sizeof(RBTNode));
    NIL->color = BLACK;
}

void rbt_rotate_right(RBTNode** root, RBTNode* parent)
{
    // Store the left child of the parent node
    RBTNode* left_child = parent->left;

    // Set the parent node's left child as the right child of the left child
    // This is done according to the rules of a right rotation
    parent->left = left_child->right;

    // If the left child's right child is not NIL (sentinel node), set its parent as the parent node
    if (left_child->right != NIL)
        left_child->right->parent = parent;

    // Set the parent of the left child as the parent of the parent node
    left_child->parent = parent->parent;

    // If the parent node is the root of the tree, set the left child as the new root
    if (parent->parent == NULL)
        (*root) = left_child;
        // Otherwise, set the left child as either the left or right child of the parent node's parent
        // depending on which child the parent node was
    else
    {
        if (parent == parent->parent->left)
            parent->parent->left = left_child;
        else
            parent->parent->right = left_child;
    }

    // Set the parent node as the right child of the left child
    left_child->right = parent;

    // Set the left child as the parent of the parent node
    parent->parent = left_child;
}

int main(void)
{

}