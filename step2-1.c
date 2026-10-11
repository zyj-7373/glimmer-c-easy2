#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return NULL;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertHead(Node** head, int n) {
    Node* newNode = createNode(n);
    if (newNode == NULL) return;
    newNode->next = *head;
    *head = newNode;
}

void insertTail(Node** head, int n) {
    Node* newNode = createNode(n);
    if (newNode == NULL) return;
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* p = *head;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = newNode;
}

void printList(Node* head) {
    Node* p = head;
    while (p != NULL) {
        printf("%d -> ", p->data);
        p = p->next;
    }
    printf("NULL\n");
}

int searchNode(Node* head, int n) {
    Node* p = head;
    int index = 1;
    while (p != NULL) {
        if (p->data == n) {
            return index;
        }
        p = p->next;
        index++;
    }
    return 0;
}

bool deleteNode(Node** head, int n) {
    if (*head == NULL || n <= 0) return false;
    if (n == 1) {
        Node* temp = *head;
        *head = (*head)->next;
        free(temp);
        return true;
    }
    Node* prev = *head;
    Node* curr = (*head)->next;
    int index = 2;
    while (curr != NULL && index < n) {
        prev = curr;
        curr = curr->next;
        index++;
    }
    if (curr == NULL) return false;
    prev->next = curr->next;
    free(curr);
    return true;
}

void reverseList(Node** head) {
    Node* prev = NULL;
    Node* curr = *head;
    Node* next = NULL;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *head = prev;
}

int main() {
    Node* head = createNode(0);
    if (head == NULL) return 1;

    printf("初始链表: ");
    printList(head);

    insertHead(&head, 10);
    insertHead(&head, 20);
    printf("头插10,20后: ");
    printList(head);

    insertTail(&head, 30);
    insertTail(&head, 40);
    printf("尾插30,40后: ");
    printList(head);

    int pos = searchNode(head, 30);
    if (pos) printf("找到30, 位置: %d\n", pos);
    else printf("未找到30\n");

    pos = searchNode(head, 99);
    if (pos) printf("找到99, 位置: %d\n", pos);
    else printf("未找到99\n");

    if (deleteNode(&head, 3)) printf("删除第3个节点成功\n");
    else printf("删除第3个节点失败\n");
    printf("删除后: ");
    printList(head);

    if (deleteNode(&head, 10)) printf("删除第10个节点成功\n");
    else printf("删除第10个节点失败\n");

    reverseList(&head);
    printf("反转后: ");
    printList(head);

    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
