#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* sortedListToBST(struct ListNode* head) {
    if (head == NULL) return NULL;
    if (head->next == NULL) {
        struct TreeNode* n = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        n->val = head->val;
        n->left = n->right = NULL;
        return n;
    }

    struct ListNode *slow = head, *fast = head, *prev = NULL;
    while (fast && fast->next) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    if (prev) prev->next = NULL;

    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = slow->val;
    root->left = sortedListToBST(head);
    root->right = sortedListToBST(slow->next);
    return root;
}

void printLeetCodeFormat(struct TreeNode* root) {
    if (!root) {
        printf("[]\n");
        return;
    }

    struct TreeNode* queue[2048] = {NULL}; 
    int head = 0, tail = 0;
    queue[tail++] = root;

    printf("[");
    bool first = true;

    while (head < tail) {
        struct TreeNode* current = queue[head++];

        if (!first) printf(",");
        first = false;

        if (current) {
            printf("%d", current->val);
            queue[tail++] = current->left;
            queue[tail++] = current->right;
        } else {
            printf("null");
        }

        bool hasMore = false;
        for (int i = head; i < tail; i++) {
            if (queue[i] != NULL) {
                hasMore = true;
                break;
            }
        }
        if (!hasMore) break;
    }
    printf("]\n");
}

void liberarArvore(struct TreeNode* root) {
    if (root == NULL) return;
    liberarArvore(root->left);
    liberarArvore(root->right);
    free(root);
}

struct ListNode* criarNoLista(int val) {
    struct ListNode* novo = (struct ListNode*)malloc(sizeof(struct ListNode));
    novo->val = val;
    novo->next = NULL;
    return novo;
}

int main() {
    struct ListNode* n1 = criarNoLista(-10);
    struct ListNode* n2 = criarNoLista(-3);
    struct ListNode* n3 = criarNoLista(0);
    struct ListNode* n4 = criarNoLista(5);
    struct ListNode* n5 = criarNoLista(9);
    
    n1->next = n2; n2->next = n3; n3->next = n4; n4->next = n5;

    struct TreeNode* root = sortedListToBST(n1);

    printLeetCodeFormat(root);

    liberarArvore(root);
    
    free(n1); free(n2); free(n3); free(n4); free(n5);

    return 0;
}