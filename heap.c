// CSCI 2021 Project 1
// Alex Harvey
// Matthew Erickson-Cancino
// February 2023

#include "heap.h"

HeapNode heap[256];
int heapSize;

/**********************************************************************************************
 *
 * Declare and define any local function here to support your implementation of the heap
 *
 **********************************************************************************************/
/******** INSERT YOUR CODE HERE IF NEEDED ********/

HeapNode *parent(int n)
{
    // moves binary representation of int one to the right,
    // halfing the number with floor / accessing parent node of binary tree
    return &heap[n >> 1];
}
HeapNode *lChild(int n)
{
    return &heap[n * 2];
}
HeapNode *rChild(int n)
{
    return &heap[n * 2 + 1];
}

void bubbleUp(int pos)
{
    // int pos = child pos

    HeapNode temp = *parent(pos);

    // to bubbleup there must be a child element smaller than the parent
    if ((*parent(pos)).freq > heap[pos].freq)
    {
        // swapping the child with the parent will bubble it up
        *parent(pos) = heap[pos];
        heap[pos] = temp;
        bubbleUp(pos >> 1);
    }
}
void bubbleDown(int pos)
{
    // int pos = parent pos
    HeapNode temp = *parent(pos);

    if ((pos * 2) > heapSize)
    {
        return; // TODO potential bug??
    }

    if (heap[pos].freq < (*lChild(pos)).freq && heap[pos].freq < (*rChild(pos)).freq)
        return;

    if ((*lChild(pos)).freq < (*rChild(pos)).freq)
    {
        temp = *lChild(pos);
        *lChild(pos) = heap[pos];
        heap[pos] = temp;
        bubbleDown(pos * 2);
    }
    else
    {
        temp = *rChild(pos);
        *rChild(pos) = heap[pos];
        heap[pos] = temp;
        bubbleDown(pos * 2 + 1);
    }
}

/*Initialize Heap*/
void heapInit()
{
    heapSize = 0;
    heap[0].c = 0;
    heap[0].t_node = NULL;
    heap[0].freq = 0;
}

/*
 * To insert a new node into the heap
 * 1. The size of the heap is increased by 1
 * 2. The new element is inserted as the last element of the heap
 * 3. Sift up the new element (swim/bubble up operation) until the heap property has been reestablished.
 */
void HeapInsert(char c, huffman_tree_node *t, int freq)
{
    /******** INSERT YOUR CODE HERE ********/
    heapSize++;
    heap[heapSize].c = c;
    heap[heapSize].t_node = t;
    heap[heapSize].freq = freq;
    bubbleUp(heapSize);
}

/*
 * heap[1] is the root of the heap and contains the minimum node. To remove root,
 * 1. the content of heap[1] is copies to an return struct.
 * 2. the last element of the heap heap[heapSize] is copied to the root.
 * 3. the size of the heap is decreased by 1.
 * 4. sift down the new root (sink/tri operation) to reestablish the heap property.
 * 5. return the old heap[1] stored in the return struct/
 * Note that, heap[0] is NOT used in this heap implementation
 */
HeapNode DeleteMin()
{
    /******** INSERT YOUR CODE HERE ********/
    HeapNode returnHead = heap[1];
    heap[1] = heap[heapSize];
    heapSize--; // this leaves the alst heap ndoe stilll there but we wont access it
    bubbleDown(1);
    return returnHead;
}

void heapPrint()
{
    int i;
    printf("\n----------------\n  HEAP BEGIN\n-----------------\n");
    for (i = 1; i <= heapSize; i++)
    {
        printf("%d ", heap[i].c);
        if (isprint(heap[i].c))
            printf("(%c)", heap[i].c);
        else
            printf("(--)");
        printf("%d\n", heap[i].freq);
    }
    printf("\n----------------\n  HEAP END\n-----------------\n");
}

/****************************************************************
 *
 * Debuggine Code for the heap data structure
 * Compile this code with
 *
 ****************************************************************/

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

    heapPrint();

    DeleteMin();
    heapPrint();

    DeleteMin();
    heapPrint();
    return 0;
}

#endif // TEST
