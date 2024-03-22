#include <stdio.h>
#include <stdlib.h>

// Node structure for binary search tree
struct Node {
    int data;
    struct Node *left, *right;
};

// Function to create a new node
struct Node* newNode(int key) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = key;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to insert a node into the BST
struct Node* insert(struct Node* root, int key) {
    if (root == NULL)
        return newNode(key);
    if (key < root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);
    return root;
}

// Function to delete a node from the BST
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL)
        return root;
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        struct Node* temp = root->right;
        while (temp->left != NULL)
            temp = temp->left;
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to find the height of the BST
int height(struct Node* root) {
    if (root == NULL)
        return -1;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Function to print the level and height of a node
void printLevelAndHeight(struct Node* root, int key, int level) {
    if (root == NULL)
        return;
    if (root->data == key) {
        printf("Level of node %d: %d\n", key, level);
        printf("Height of node %d: %d\n", key, height(root));
        return;
    }
    printLevelAndHeight(root->left, key, level + 1);
    printLevelAndHeight(root->right, key, level + 1);
}

// Function to print the tree (inorder traversal)
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    int arr[] = {30, 20, 40, 10, 25, 35, 45, 5, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    struct Node* root = NULL;
    for (int i = 0; i < n; i++)
        root = insert(root, arr[i]);

    printf("Inorder traversal of the BST: ");
    inorder(root);
    printf("\n");

    int nodeToDelete = 20;
    root = deleteNode(root, nodeToDelete);
    printf("Inorder traversal after deleting %d: ", nodeToDelete);
    inorder(root);
    printf("\n");

    printf("Height of the BST: %d\n", height(root));

    int nodeToFind = 30;
    printLevelAndHeight(root, nodeToFind, 0);

    return 0;
}
