#ifndef __AVL_H__
#define __AVL_H__

#include <stdint.h>


// AVL element is 32-bit unsigned integer type.
typedef uint32_t avl_element_t;


// AVL node
class avl_node_t {
public:
    avl_node_t(const avl_element_t m_element);  // AVL node constructor
    ~avl_node_t();                              // AVL node destructor

    avl_element_t element;                      // Node element (data)
    avl_node_t *left, *right;                   // Left, right child pointers
};


// AVL tree
class avl_t {
public:
    avl_t();                                    // AVL tree constructor
    ~avl_t();                                   // AVL tree destructor

    /* AVL OPERATIONS */
    // Get the number of elements (or nodes) in the tree.
    size_t size() const;
    // Return "true" if the tree is empty.
    bool empty() const;
    // Print the values of all elements in preorder.
    void print() const;
    // Return the tree height.
    int height() const;
    // Find the minimum element in the tree.
    avl_element_t find_min() const;
    // Find the maximum element in the tree.
    avl_element_t find_max() const;
    // Return "true" if the element exists in the tree.
    bool contain(const avl_element_t m_element) const;
    // Add a new element to the tree.
    void insert(const avl_element_t m_element);
    // Remove the element if found in the tree.
    void remove(const avl_element_t m_element);
    // Remove all nodes in the tree.
    void clear();

private:
    /* INTERNALLY USED RECURSIVE FUNCTIONS */
    // Recursively print element values.
    void print(int m_depth, const avl_node_t *m_node) const;
    // Recursively find the minimum element in the tree.
    avl_element_t find_min(const avl_node_t *m_node) const;
    // Recursively check if the tree contains the element.
    bool contain(const avl_element_t m_element, const avl_node_t *m_node) const;
    // Recursively delete nodes.
    void clear(avl_node_t *m_node);
    
    unsigned count;                             // Number of nodes in the tree
    avl_node_t *root;                           // Pointer to the root node
    
    
    /***************************************************************************/
    // Recursively return the height of the tree.
    int height(avl_node_t *m_node) const;
    // Recursively insert the element in the subtrees of a node.
    avl_node_t* insert(const avl_element_t m_element, avl_node_t *m_node);
    // Recursively remove the element in the subtrees of a node.
    avl_node_t* remove(const avl_element_t m_element, avl_node_t *m_node);
    // Rotation while left-left happens.
    avl_node_t* ll_rotate(avl_node_t *m_node);
    // Rotation while right-right happens.
    avl_node_t* rr_rotate(avl_node_t *m_node);
    // Rotation while left-right happens.
    avl_node_t* lr_rotate(avl_node_t *m_node);
    // Rotation while right-left happens.
    avl_node_t* rl_rotate(avl_node_t *m_node);
    
};

#endif

