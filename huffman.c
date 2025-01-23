#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char symbol;
    int freq;
    struct Node *leftChild, *rightChild;
} Node;

typedef struct PriorityQueue
{
    int currentSize;
    int maxSize;
    Node **elements;
} PriorityQueue;

Node* initializeNode(char symbol, int freq);
PriorityQueue* initializePriorityQueue(int maxSize);
void addNode(PriorityQueue *pq, Node *newNode);
Node* removeNode(PriorityQueue *pq);
void heapify(PriorityQueue *pq);
void displayCodes(Node *root, int code[], int depth);
void generateHuffmanCodes(char *inputText);
void countFrequencies(char *inputText, int *freqArray);

int main()
{
    char inputText[1000];

    printf("Input text for compression: ");
    fgets(inputText, sizeof(inputText), stdin);
    inputText[strcspn(inputText, "\n")] = '\0';

    generateHuffmanCodes(inputText);

    return 0;
}

Node* initializeNode(char symbol, int freq)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->symbol = symbol;
    newNode->freq = freq;
    newNode->leftChild = newNode->rightChild = NULL;
    return newNode;
}

PriorityQueue* initializePriorityQueue(int maxSize)
{
    PriorityQueue *pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->currentSize = 0;
    pq->maxSize = maxSize;
    pq->elements = (Node**)malloc(maxSize * sizeof(Node*));
    return pq;
}

void addNode(PriorityQueue *pq, Node *newNode)
{
    pq->elements[pq->currentSize] = newNode;
    int i = pq->currentSize;
    while (i > 0 && pq->elements[(i - 1) / 2]->freq > pq->elements[i]->freq) {
        Node *temp = pq->elements[i];
        pq->elements[i] = pq->elements[(i - 1) / 2];
        pq->elements[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
    pq->currentSize++;
}

Node* removeNode(PriorityQueue *pq)
{
    Node *minNode = pq->elements[0];
    pq->elements[0] = pq->elements[pq->currentSize - 1];
    pq->currentSize--;
    heapify(pq);
    return minNode;
}

void heapify(PriorityQueue *pq)
{
    int n = pq->currentSize - 1;
    for (int i = (n - 1) / 2; i >= 0; i--) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < pq->currentSize && pq->elements[left]->freq < pq->elements[smallest]->freq)
            smallest = left;
        if (right < pq->currentSize && pq->elements[right]->freq < pq->elements[smallest]->freq)
            smallest = right;

        if (smallest != i) {
            Node *temp = pq->elements[i];
            pq->elements[i] = pq->elements[smallest];
            pq->elements[smallest] = temp;
            i = smallest;
        }
    }
}

void countFrequencies(char *inputText, int *freqArray)
{
    for (int i = 0; inputText[i] != '\0'; i++) {
        freqArray[(unsigned char)inputText[i]]++;
    }
}

void displayCodes(Node *root, int code[], int depth)
{
    if (root->leftChild) {
        code[depth] = 0;
        displayCodes(root->leftChild, code, depth + 1);
    }
    if (root->rightChild) {
        code[depth] = 1;
        displayCodes(root->rightChild, code, depth + 1);
    }
    if (!root->leftChild && !root->rightChild) {
        printf("%c: ", root->symbol);
        for (int i = 0; i < depth; i++) {
            printf("%d", code[i]);
        }
        printf("\n");
    }
}

void generateHuffmanCodes(char *inputText)
{
    int freqArray[256] = {0};
    countFrequencies(inputText, freqArray);

    PriorityQueue *pq = initializePriorityQueue(strlen(inputText));
    for (int i = 0; i < 256; i++) {
        if (freqArray[i] > 0) {
            addNode(pq, initializeNode(i, freqArray[i]));
        }
    }

    while (pq->currentSize > 1) {
        Node *leftChild = removeNode(pq);
        Node *rightChild = removeNode(pq);
        Node *parent = initializeNode('$', leftChild->freq + rightChild->freq);
        parent->leftChild = leftChild;
        parent->rightChild = rightChild;
        addNode(pq, parent);
    }

    int code[100], depth = 0;
    printf("\nGenerated Huffman Codes:\n");
    displayCodes(pq->elements[0], code, depth);
}
