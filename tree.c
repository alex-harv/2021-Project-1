// CSCI 2021 Project 1
// Alex Harvey
// Matthew Erickson-Cancino
// February 2023

#include "heap.h"

// The root to the Huffman tree
huffman_tree_node *huffman_tree = NULL;

/**********************************************************************************************
 *
 * Declare and define any local function here to support your implementation of the heap
 *
 **********************************************************************************************/

/*
 * Create a single tree node initialized with the given parameters
 */
huffman_tree_node *create_node(char c, huffman_tree_node *l, huffman_tree_node *r)
{
	huffman_tree_node *node = malloc(sizeof(huffman_tree_node));

	node->c = c;
	node->left = l;
	node->right = r;

	return node;
}

/*
 * Builds Huffman Tree
 * 1. Step through the heap and initialize t_node with a new huffman tree node
 * 2. Repeat while there are more than 1 elements in the heap:
 *    2a. Remove two elements from the heap
 *    2b. Create a new huffman tree node
 *    2c. Reinsert a new heap element that is the parent of thw two deleted elements
 * 3. The last element in the heap contains the root of the huffman tree
 */

void build_huffman_tree()
{
	/********* INSERT YOUR CODE HERE *************/

	int i = 1;
	while (i <= heapSize)
	{
		heap[i].t_node = create_node(heap[i].c, NULL, NULL);
		i++;
	}

	while (1)
	{
		HeapNode OldNode1 = DeleteMin();
		HeapNode OldNode2 = DeleteMin();
		huffman_tree_node *tempnode = create_node(NULL, OldNode1.t_node, OldNode2.t_node);
		HeapInsert(NULL, tempnode, OldNode1.freq + OldNode2.freq);
		if (heapSize == 1)
		{
			huffman_tree = tempnode;
			return;
		}
	}
}

void print_huffman_tree(huffman_tree_node *root, int level)
{
	int i;

	if (level == 0)
		printf("\n----------------\n  TREE BEGIN\n-----------------\n");

	if (root == NULL)
		return;

	for (i = 0; i < level; i++)
		printf("   ");

	if (root->left != NULL || root->right != NULL)
		printf("Node (I)\n");
	else if (isprint(root->c))
		printf("Node %d(%c)\n", root->c, root->c);
	else
		printf("Node %d(--)\n", root->c);

	print_huffman_tree(root->left, level + 1);
	print_huffman_tree(root->right, level + 1);

	if (level == 0)
		printf("\n-----------\n  TREE END\n------------\n");
}

#ifdef TEST

int main()
{
	heapInit();

	HeapInsert('a', NULL, 44);
	HeapInsert('b', NULL, 32);
	HeapInsert('d', NULL, 99);
	HeapInsert('f', NULL, 43);
	HeapInsert('u', NULL, 51);
	HeapInsert('y', NULL, 1);
	build_huffman_tree();
	print_huffman_tree(huffman_tree, 0);
	return 0;
}

#endif // TEST