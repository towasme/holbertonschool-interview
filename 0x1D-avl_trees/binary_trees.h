#ifndef BINARY_TREES_H
#define BINARY_TREES_H


/**
 * struct binary_tree_s - Binary tree node
 *
 * @n: Integer stored in the node
 * @parent: Pointer to the parent node
 * @left: Pointer to the left child node
 * @right: Pointer to the right child node
 */
struct binary_tree_s
{
	int n;
	struct binary_tree_s *parent;
	struct binary_tree_s *left;
	struct binary_tree_s *right;
};

typedef struct binary_tree_s binary_tree_t;
typedef struct binary_tree_s avl_t;

/**
 * struct avl_data_s - combined height and AVL balance status of a node in a
 *   binary tree, combined into a struct to be returned recursively
 *
 * @height: height of a subtree
 * @is_AVL: 0 if balance factor of subtree is < -1 or > 1; 1 otherwise
 */
typedef struct avl_data_s
{
	int height;
	int is_AVL;
} avl_data_t;


/* binary_tree_print.c */
void binary_tree_print(const binary_tree_t *);

/* 0-binary_tree_is_avl.c */
avl_data_t BST_is_AVL_balanced(const binary_tree_t *tree);
int tree_is_BST(const binary_tree_t *tree, int *prev);
int binary_tree_is_avl(const binary_tree_t *tree);


#endif /* BINARY_TREES_H */
