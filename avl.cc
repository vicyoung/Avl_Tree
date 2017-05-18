#include <assert.h>
#include <cstdlib>
#include <iostream>
#include "avl.h"

using namespace std;

/***************************
 * EEE2020-03 ASSIGNMENT 3 *
 ***************************/
// Return the tree height.
int avl_t::height() const {
    return height(root);
}

// Find the maximum element in the tree.
avl_element_t avl_t::find_max() const {
    if(!root) {return -1;}              // Fail if a empty tree.
    avl_node_t* current_node = root;
    while(current_node->right)
        current_node = current_node->right;
    return current_node->element;
}

// Add a new element to the tree.
void avl_t::insert(const avl_element_t m_element) {
    root = insert(m_element, root);
    
}

// Remove the element if found in the tree.
void avl_t::remove(const avl_element_t m_element) {
    root = remove(m_element, root);
}
/***********************
 * END OF ASSIGNMENT 3 *
 ***********************/

// Left-left rotation.
avl_node_t* avl_t::ll_rotate(avl_node_t *m_node) {
    avl_node_t* ll = m_node->left;
    m_node->left = ll->right;
    ll->right = m_node;
    return ll;      // Return the 'root' of the subtree.
}

// Right-right rotation.
avl_node_t* avl_t::rr_rotate(avl_node_t *m_node) {
    avl_node_t* rr = m_node->right;
    m_node->right = rr->left;
    rr->left = m_node;
    return rr;
}

// Left-right rotation.
avl_node_t* avl_t::lr_rotate(avl_node_t *m_node) {
    m_node->left = rr_rotate(m_node->left);
    m_node = ll_rotate(m_node);
    return m_node;
}

// Right-left rotation.
avl_node_t* avl_t::rl_rotate(avl_node_t *m_node) {
    m_node->right = ll_rotate(m_node->right);
    m_node = rr_rotate(m_node);
    return m_node;
}

// Recursively find the height of a node.
int avl_t::height(avl_node_t *m_node) const {
    if(!m_node){return -1;}     // Set the height of a null node to -1
    return max(height(m_node->left),height(m_node->right)) + 1;
}

// Recursively insert an element under a node.
avl_node_t* avl_t::insert(const avl_element_t m_element, avl_node_t *m_node) {
    if(m_node == NULL){
        // Find the place to insert or no root, add a new element.
        m_node = new avl_node_t(m_element);
        count++;
    }
    else if(m_element < m_node->element) {
        // Go to left if the inserting element is smaller than current element.
        m_node->left = insert(m_element, m_node->left);
        if(height(m_node->left) - height(m_node->right) == 2) {
            // Balancing conditions. Inserting an element to the left only causes ll or lr.
            if(m_element < m_node->left->element)
                m_node = ll_rotate(m_node);
            else
                m_node = lr_rotate(m_node);
        }
    }
    else if(m_node->element < m_element) {
        // Go to right if the inserting element is larger than current element.
        m_node->right = insert(m_element, m_node->right);
        if(height(m_node->left) - height(m_node->right) == -2) {
            // Balancing conditions.
            if(m_node->right->element <m_element)
                m_node = rr_rotate(m_node);
            else
                m_node = rl_rotate(m_node);
        }
    }
    return m_node;
}

// Recursively removing an element under a node.
avl_node_t* avl_t::remove(const avl_element_t m_element, avl_node_t *m_node) {
    if(m_node == NULL){
        // Not find the element or no root, do nothing.
        return m_node;
    }
    if(m_element < m_node->element){
        // Go to left if the removing element is smaller than current element.
        m_node->left = remove(m_element, m_node->left);
        if(height(m_node->left) - height(m_node->right) == -2) {
            // Balancing conditions. Removing an element from the left only causes rr or rl.
            if(height(m_node->right->left) <= height(m_node->right->right))
                m_node = rr_rotate(m_node);
            else
                m_node = rl_rotate(m_node);
        }
    }
    else if(m_node->element < m_element){
        // Go to right if the removing element is larger than current element.
        m_node->right = remove(m_element, m_node->right);
        if(height(m_node->left) - height(m_node->right) == 2) {
            // Balancing conditions.
            if(height(m_node->left->right) <= height(m_node->left->left))
                m_node = ll_rotate(m_node);
            else
                m_node = lr_rotate(m_node);
        }
    }
    // Find the element.
    else if(m_node->left && m_node->right){
        // If the element have two children.
        m_node->element = find_min(m_node->right);
        m_node->right = remove(m_node->element, m_node->right);
        if(height(m_node->left) - height(m_node->right) == 2) {
            // Balancing conditions happens when deleting root.
            if(height(m_node->left->right) <= height(m_node->left->left))
                m_node = ll_rotate(m_node);
            else
                m_node = lr_rotate(m_node);
        }
    }
    else{
        // If the element have one children or less.
        avl_node_t* old_node = m_node;
        m_node = m_node->left ? m_node->left : m_node->right;
        delete old_node;
        old_node = NULL;
        count--;
    }
        
    return m_node;
}
/*******************************************************/
// AVL node constructor
avl_node_t::avl_node_t(const avl_element_t m_element) :
    element(m_element),
    left(NULL),
    right(NULL) {
}

// AVL node destructor
avl_node_t::~avl_node_t() {
}


// AVL tree constructor
avl_t::avl_t() : 
    count(0),
    root(NULL) {
}

// AVL tree destructor
avl_t::~avl_t() {
    clear();
}


/* PUBLIC FUNCTIONS */
// Get the number of elements (or nodes) in the tree.
size_t avl_t::size() const { return count; }
// Return "true" if the tree is empty.
bool avl_t::empty() const { return count == 0; }
// Print the values of all elements in preorder.
void avl_t::print() const { if(root) { print(0, root); } }
// Find the minimum element in the tree.
avl_element_t avl_t::find_min() const { if(root) { return find_min(root); } return -1; }
// Return "true" if the element exists in the tree.
bool avl_t::contain(const avl_element_t m_element) const { return contain(m_element, root); }
// Remove all nodes in the tree.
void avl_t::clear() { if(root) { clear(root); root = NULL; } }


/* PRIVATE FUNCTIONS */
// Recursively print element values.
void avl_t::print(int m_depth, const avl_node_t *m_node) const {
    for(int d = 0; d < m_depth; d++) { cout << "...."; }
    cout << m_node->element << endl;

    if(m_node->left)  { print(m_depth+1, m_node->left);  }
    if(m_node->right) { print(m_depth+1, m_node->right); }
}

// Recursively find the minimum element in the tree.
avl_element_t avl_t::find_min(const avl_node_t *m_node) const {
    if(m_node->left) { return find_min(m_node->left); }
    return m_node->element;
}

// Recursively check if the tree contains the element.
bool avl_t::contain(const avl_element_t m_element, const avl_node_t *m_node) const {
    if(m_node) {
        if(m_element < m_node->element) { return contain(m_element, m_node->left); }
        if(m_node->element < m_element) { return contain(m_element, m_node->right); }
        return true;
    }
    return false;
}

// Recursively delete nodes.
void avl_t::clear(avl_node_t *m_node) {
    if(m_node->left)  { clear(m_node->left);  }
    if(m_node->right) { clear(m_node->right); }
    delete m_node;
    count--;
}

