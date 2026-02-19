#include <stdio.h>
#include <stdlib.h>

// Define structure for BST node
struct Node {
    int data;               // value of node
    struct Node *left, *right; // pointers to left and right child
};

// Create new node
struct Node* create(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); // allocate memory
    newNode->data = value;   // store value
    newNode->left = newNode->right = NULL; // initially no children
    return newNode;          // return new node
}

// Insert element into BST
struct Node* insert(struct Node* root, int value) {
    if (root == NULL)        // if tree empty
        return create(value); // create new node

    if (value < root->data)  // if value smaller
        root->left = insert(root->left, value);  // go left
    else if (value > root->data) // if value greater
        root->right = insert(root->right, value); // go right

    return root;             // return updated root
}

// Find minimum node (used in delete)
struct Node* findMin(struct Node* root) {
    while (root->left)       // go to leftmost node
        root = root->left;
    return root;             // smallest value
}

// Delete element from BST
struct Node* deleteNode(struct Node* root, int value) {
    if (root == NULL)        // if tree empty
        return NULL;

    if (value < root->data)  // search in left subtree
        root->left = deleteNode(root->left, value);
    else if (value > root->data) // search in right subtree
        root->right = deleteNode(root->right, value);
    else {                   // element found

        if (!root->left) {   // case: only right child or no child
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (!root->right) { // case: only left child
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // case: two children
        struct Node* temp = findMin(root->right); // find inorder successor
        root->data = temp->data;  // replace value
        root->right = deleteNode(root->right, temp->data); // delete successor
    }
    return root;
}

// Search element in BST
void search(struct Node* root, int key) {
    if (root == NULL) {          // if not found
        printf("Element not found\n");
        return;
    }

    if (key == root->data)       // if found
        printf("Element found\n");
    else if (key < root->data)   // search left
        search(root->left, key);
    else                         // search right
        search(root->right, key);
}

// Inorder traversal (prints sorted order)
void inorder(struct Node* root) {
    if (root) {
        inorder(root->left);     // visit left
        printf("%d ", root->data); // print root
        inorder(root->right);    // visit right
    }
}

// Main function
int main() {
    struct Node* root = NULL;   // initially tree empty
    int choice, value;

    while (1) {
        printf("\n1.Insert  2.Delete  3.Search  4.Display  5.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter value: ");
            scanf("%d", &value);
            root = insert(root, value);   // call insert
        }
        else if (choice == 2) {
            printf("Enter value: ");
            scanf("%d", &value);
            root = deleteNode(root, value); // call delete
        }
        else if (choice == 3) {
            printf("Enter value: ");
            scanf("%d", &value);
            search(root, value);          // call search
        }
        else if (choice == 4) {
            printf("BST (Inorder): ");
            inorder(root);                // display sorted values
            printf("\n");
        }
        else if (choice == 5)
            break;                        // exit program
        else
            printf("Invalid choice\n");
    }
    return 0;
}
