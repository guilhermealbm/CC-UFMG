#include <iostream>
 
using namespace std;

struct node {
    char value;
    node* left = NULL; 
    node* right = NULL;
};

int preIndex = 0;

node* getTree(string pre, string in, int start, int end) {
    if (start > end) {
        return NULL;
    }

    node* curr = new node();
    curr->value = pre[preIndex];preIndex++;

    if (start == end) {
        return curr;
    }

    int inIndex = in.find(curr->value);
    if (inIndex == -1)
        return NULL;

    curr->left = getTree(pre, in, start, inIndex - 1);
    curr->right = getTree(pre, in, inIndex + 1, end);
    return curr;
}

void printPostOrder(node* root) {
    if (root->left != NULL)
        printPostOrder(root->left);
    if (root->right != NULL)
        printPostOrder(root->right);
    
    cout << root->value;
}
 
int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */

    int c;cin>>c;
    while (c--) {
        int n;cin>>n;
        string pre;cin>>pre;
        string in;cin>>in;
        preIndex = 0;
        node* root = getTree(pre, in, 0, n - 1);
        printPostOrder(root);
        cout << endl;
    }
 
    return 0;
}
