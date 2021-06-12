
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_INT 32767
#define MIN_INT -32768

typedef struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct Tree {
    TreeNode* root;
} Tree;


typedef struct Heap {
    int* array;
    int capacity;
    int size;
} Heap;


// Inserts value into the tree.
void Insert(Tree* tree, int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    if (tree->root == NULL) {
        tree->root = newNode;
        return;
    }

    TreeNode* curr = tree->root;
    while (curr != NULL) {
        if (value < curr->value) {
            if (curr->left == NULL) {
                curr->left = newNode;
                return;
            }
            curr = curr->left;
        }
        else {
            if (curr->right == NULL) {
                curr->right = newNode;
                return;
            }
            curr = curr->right;
        }
    }
    printf("Exited loop without inserting into the tree!!\n");
}

// Performs an inorder Print on a Tree given a root.
void InOrderPrint(TreeNode* node) {
    if (node == NULL) {
        return;
    }
    InOrderPrint(node->left);
    printf("%d\n", node->value);
    InOrderPrint(node->right);
}


int IsomorphicNode(TreeNode* node1, TreeNode* node2) {
    if (node1 == NULL && node2 == NULL) {
        return 1;
    }
    else if (node1 == NULL || node2 == NULL) {
        return 0;
    }
    else {
        return IsomorphicNode(node1->left, node2->left) &&
            IsomorphicNode(node1->right, node2->right);
    }
}

// Return 1 if they are isomorphic.
// Return 0 if they are not isomorphic.
int Isomorphic(Tree* tree1, Tree* tree2) {
    if (tree1 == NULL && tree2 == NULL) {
        return 1;
    }
    else if (tree1 == NULL || tree2 == NULL) {
        return 0;
    }
    else {
        return IsomorphicNode(tree1->root, tree2->root);
    }
}




int IsBSTNode(TreeNode* node, long min, long max) {
    if (node == NULL) {
        return 1;
    }
    else if (node->value < min || node->value > max) {
        return 0;
    }
    else {
        return IsBSTNode(node->left, min, node->value - 1) &&
            IsBSTNode(node->right, node->value + 1, max);
    }
}

// Return 1 if the tree is a binary search tree.
// Return 0 otherwise
int IsBinarySearchTee(Tree* tree) {
    if (tree == NULL) {
        return 1;
    }
    return IsBSTNode(tree->root, MIN_INT, MAX_INT);
}

// Remove the minimum value in the heap.
void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}


void PrintHeap(Heap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d,", heap->array[i]);
    }
    printf("\n");
}

// Runs in O(Log(N)) as the index is multipled by 2
// at each iteration and we stop about half way into the
// array.
void RemoveMin(Heap* heap) {
    // Replace the minimum element with the last element.
    heap->array[0] = heap->array[--heap->size];
    int i = 0;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // heap->size/2 + 1 is the first leaf in a tree.
    while ((i < (heap->size / 2 + 1)) &&
        // Check if either the left or right child is smaller
        // but only check them when their indices are valid.
        ((left < heap->size && heap->array[i] > heap->array[left])
            || (right < heap->size && heap->array[i] > heap->array[right]))) {

        if (right < heap->size &&
            heap->array[left] > heap->array[right]) {
            swap(&heap->array[i], &heap->array[right]);
            i = right;
        }
        else {
            swap(&heap->array[i], &heap->array[left]);
            i = left;
        }
        left = 2 * i + 1;
        right = 2 * i + 2;
    }
}

// Inserts a value into minHeap
// Uses 0 based index.
// For a node at index i:
// Left child = 2*i + 1
// Right child = 2*i + 2
// Parent = (i-1) / 2
void HeapInsert(Heap* heap, int value) {
    heap->array[heap->size++] = value;
    int index = heap->size - 1;
    while ((index > 0) &&
        (heap->array[(index - 1) / 2] > heap->array[index])) {
        int temp = heap->array[index];
        heap->array[index] = heap->array[(index - 1) / 2];
        heap->array[(index - 1) / 2] = temp;
        index = (index - 1) / 2;
    }

}



int ValidateHeap(Heap* h) {
    for (int i = 0; i < h->size; i++) {
        int left = 2 * i + 1;
        if (left < h->size) {
            if (h->array[left] < h->array[i]) {
                return 0;
            }
        }
        int right = 2 * i + 2;
        if (right < h->size) {
            if (h->array[right] < h->array[i]) {
                return 0;
            }
        }
    }
    return 1;
}

int main(void) {

    Tree tree1 = { NULL };
    Insert(&tree1, 5);
    Insert(&tree1, 2);
    Insert(&tree1, 10);
    Insert(&tree1, 7);
    Insert(&tree1, 4);
    printf("Printing Tree1:\n");
    InOrderPrint(tree1.root);


    Tree tree2 = { NULL };
    Insert(&tree2, 6);
    Insert(&tree2, 3);
    Insert(&tree2, 11);
    Insert(&tree2, 8);
    Insert(&tree2, 5);
    printf("Printing Tree2:\n");
    InOrderPrint(tree2.root);

    // Should be true (1).
    printf("Is Tree1 isomorphic to Tree2?: %d\n", Isomorphic(&tree1, &tree2));

    // Should be true (1)
    printf("Is tree1 a BST? %d\n", IsBinarySearchTee(&tree1));

    // Should be true (1)
    printf("Is tree2 a BST? %d\n", IsBinarySearchTee(&tree2));

    printf("Changing root to 100.\n");
    tree2.root->value = 100;
    // Should be false (0)
    printf("Is tree2 a BST? %d\n", IsBinarySearchTee(&tree2));

    int N = 10;
    int* array = malloc(N * sizeof(N));
    Heap h = { array, N, 0 };
    for (int i = N - 1; i >= 0; i--) {
        HeapInsert(&h, i);
    }

    printf("Is it a heap?  %d\n", ValidateHeap(&h));
    printf("Heap: ");
    PrintHeap(&h);

    while (h.size > 0) {
        printf("Removing minimum value.  ");
        RemoveMin(&h);
        printf("Is it a heap> %d\n", ValidateHeap(&h));
        printf("Heap: ");
        PrintHeap(&h);
    }
}