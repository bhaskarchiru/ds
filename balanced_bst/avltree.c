#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Types: bstnode, treeT
 * -------------------
 * These types define the structure of the binary search tree.
 * The type bstnode is a record that corresponds to an individual
 * node; the type bstnode_t * is simply a pointer to a node.
 */

typedef struct bstnode {
    struct bstnode	*children[2];
    int			key;
    int			bf;
} bstnode_t;

#define left	children[0]
#define right	children[1]

/* Private function prototypes */

static bstnode_t * find_node(bstnode_t *, int key);
static void insert_node(bstnode_t **, int);
static int insert_avl(bstnode_t **, int);
static void fix_left_imbalance(bstnode_t **);
static void fix_right_imbalance(bstnode_t **);
static void rotate_left(bstnode_t **);
static void rotate_right(bstnode_t **);
static void display_tree(bstnode_t *);
static void display_structure(bstnode_t *);
static void recursive_display_structure(bstnode_t *, int, char *);

/* Main program */

int
main(int argc, char *argv[])
{
	int		ii, key, n = 20;
	bstnode_t	*root = NULL;

	srand(time(NULL));
	for(ii = 0; ii < n; ii++) {
        	insert_node(&root, rand() % 99);
    	}
	display_structure(root);
	return 0;
}

/*
 * Function: find_node
 * Usage: np = find_node(t, key);
 * -----------------------------
 * This function searches the tree t for a node containing key.
 * If it finds it, it returns a pointer to that node, which can
 * also be regarded as the subtree rooted at that point.  If
 * the key does not appear, find_node returns NULL.
 */

static bstnode_t *
find_node(bstnode_t *root, int key)
{
	if(root == NULL) {
 		return NULL;
    	}
	if(key < root->key) {
		return find_node(root->left, key);
	}
	return find_node(root->right, key);
}

/*
 * Function: insert_node
 * Usage: insert_node(&t, key);
 * ---------------------------
 * This function calls insert_avl and discards the result.
 */

static void
insert_node(bstnode_t **rootp, int key)
{

	(void) insert_avl(rootp, key);
	return;
}

bstnode_t *
make_bstnode(int val)
{

	bstnode_t	*node = calloc(1, sizeof(bstnode_t));
	node->key = val;
	return node;
}

/*
 * Function: insert_avl
 * Usage: delta = insert_avl(&t, key);
 * ----------------------------------
 * This function enters the key into the tree whose address is
 * passed as the first argument.  The return value is the change
 * in depth in the tree, which is used to correct the balance
 * factors in ancestor nodes.
 */

static int
insert_avl(bstnode_t **rootp, int key)
{
	int			sign, delta;
  	bstnode_t		*node, *root = *rootp;

	if(root == NULL) {
		node = make_bstnode(key);
		*rootp = node;
		return 1;
	}

	/*
	 * Don't want to have duplicates.
	 */

    	if(root->key == key) {
		return 0;
	}

	if(root->key > key) {
		delta = insert_avl(&root->left, key);
		if(delta == 0) {
			return 0;
		}
		
		/*
		 * We've inserted the new value in left sub-tree.
		 * If this node's balance factor is 1, i.e. right-heavy
		 * by 1, then this insert events it out. Update
		 * balancee factor to 0, and pass delta as 0, upwards
		 * the stack.
		 * If this node's balance factor is 0, then this became
		 * left-heavy due to this insert, update balance factor
		 * to -1, also send delta as 1 up the stack.
		 * If this node's balance factor was -1 (i.e already
		 * left-heavy before the insert), then this new insert
		 * increases balance factor to -2, correct this imbalance
		 * as this node as pivot.
		 */

		switch (root->bf) {
		case 1:
			root->bf = 0;
			return 0;

		case 0:
			root->bf = -1;
			return 1;

	  	case -1:
			fix_left_imbalance(rootp);
			return 0;
		}
	}

	/*
	 * New node is going into right sub-tree.
	 */

        delta = insert_avl(&root->right, key);
	if(delta == 0) {
		return 0;
	}
	switch (root->bf) {
	case -1:
		root->bf = 0;
		return 0;

	case  0:
		root->bf = 1;
		return 1;

	case 1:
		fix_right_imbalance(rootp);
		return 0;
	}
}

/*
 * Function: fix_left_imbalance
 * Usage: fix_left_imbalance(&t);
 * ----------------------------
 * This function is called when a node has been found that
 * is out of balance with the longer subtree on the left.
 * Depending on the balance factor of the left child, the
 * code performs a single or double rotation.
 */

static void
fix_left_imbalance(bstnode_t **rootp)
{
	int		oldBF;
	bstnode_t	*root, *parent, *child, **cptr;

	/*
	 * Noticed imbalance on the node rooted at *rootp.
	 * Figure out whether we've to do a single rotatation
	 * or double rotation. We came here without updating
	 * balance factor of node at *rootp.
	 *
	 *
	 * Case 1 - which would require double rotation, i.e.
	 *   left rotation with 'child' as pivot and then 'right'
	 *   rotation with 'parent' as pivot.
	 *
	 *		parent (bf: -1)
	 *	       /
	 *	      child (bf: 1)
	 *              \
	 *		right-heavy
	 *
	 * Case 2 - whicch would require single rotation
	 *
	 *              parent (bf: -1)
	 *	       /
	 *          child(bf: -1)
	 *          /
	 *        left-heavy
	 */

	parent = *rootp;
	cptr = &parent->left;
	child = *cptr;

	/*
	 * Case 1:
	 */

	if(child->bf != parent->bf) {
		oldBF = child->right->bf;

		/*
		 * Do left rotation with child as pivot.
		 */

		rotate_left(cptr);

		/*
		 * Do right rotation with parent as pivot
		 */

		rotate_right(rootp);

		root = *rootp;
		root->bf = 0;
		switch (oldBF) {
		case -1:
			root->left->bf = 0;
			root->right->bf = 1;
			break;

		case  0:
			root->left->bf = root->right->bf = 0;
			break;

		case 1:
			root->left->bf = -1;
			root->right->bf = 0;
			break;
        	}
	} else {
        	rotate_right(rootp);
		root = *rootp;
		root->right->bf = root->bf = 0;
    	}
	return;
}

/*
 * Function: rotate_left
 * Usage: rotate_left(&t);
 * ----------------------
 * This function performs a single left rotation of the tree
 * whose address is passed as an argument.  The balance factors
 * are unchanged by this function and must be corrected at a
 * higher level of the algorithm.
 */

static void
rotate_left(bstnode_t **rootp)
{
	bstnode_t	*parent, *child;

	parent = *rootp;
	child = parent->right;
	parent->right = child->left;
	child->left = parent;
	(*rootp) = child;
	return;
}

/*
 * Functions: fix_right_imbalance, rotate_right
 * -----------------------------------------
 * These functions are symmetrical to their fix_left_imbalance
 * and rotate_left counterparts.
 */

static void
fix_right_imbalance(bstnode_t **rootp)
{
	int		oldBF;
	bstnode_t	*root, *parent, *child, **cptr;

	parent = *rootp;
	cptr = &parent->right;
	child = *cptr;
	if(child->bf != parent->bf) {
		oldBF = child->right->bf;
		rotate_right(cptr);
		rotate_left(rootp);
		root = *rootp;
		root->bf = 0;
		switch (oldBF) {
		case -1:
			root->left->bf = 0;
			root->right->bf = 1;
			break;

		case  0:
			root->left->bf = root->right->bf = 0;
			break;

		case 1:
			root->left->bf = -1;
			root->right->bf = 0;
			break;
        	}
	} else {
		rotate_left(rootp);
		root = *rootp;
		root->left->bf = root->bf = 0;
    }
}

static void
rotate_right(bstnode_t	**rootp)
{
	bstnode_t	*parent, *child;

	parent = *rootp;
	child = parent->left;
	parent->left = child->right;
	child->right = parent;
	(*rootp) = child;
	return;
}

/*
 * Function: display_tree
 * Usage: display_tree(t);
 * ----------------------
 * This function displays the keys in the specified tree in
 * alphabetical order by performing an inorder traversal.
 */

static void
display_tree(bstnode_t *root)
{
	if(root) {
		display_tree(root->left);
		printf("%d\n", root->key);
		display_tree(root->right);
    	}
	return;
}

/*
 * Function: display_structure
 * Usage: display_structure(t);
 * ---------------------------
 * This function lists the keys in the tree in a form that
 * makes its structure clear by indenting children with respect
 * to their parents and labeling left and right children.  The
 * display_structure function is implemented as a simple wrapper;
 * all the work is done by recursive_display_structure.
 */

static void
display_structure(bstnode_t *root)
{

	recursive_display_structure(root, 0, NULL);
	return;
}

static void
recursive_display_structure(bstnode_t *root, int depth, char *label)
{
	if(root == NULL) {
		return;
    	}
	printf("%*s", 3 * depth, "");
	if(label != NULL) {
		printf("%s: ", label);
	}	
	printf("%d (%s%d)\n", root->key, (root->bf > 0) ? "+" : "", root->bf);
	recursive_display_structure(root->left, depth + 1, "L");
	recursive_display_structure(root->right, depth + 1, "R");
	return;
}
