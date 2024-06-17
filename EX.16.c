#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10 


struct Node {
    int key;
    int value;
    struct Node* next; 
};


struct HashTable {
    struct Node** array; 
    int capacity;
};


struct Node* newNode(int key, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}


struct HashTable* createHashTable(int capacity) {
    struct HashTable* hashTable = (struct HashTable*)malloc(sizeof(struct HashTable));
    hashTable->capacity = capacity;
    hashTable->array = (struct Node**)malloc(capacity * sizeof(struct Node*));
    for (int i = 0; i < capacity; i++)
        hashTable->array[i] = NULL;
    return hashTable;
}


int hashFunction(int key, int capacity) {
    return key % capacity;
}


void insertOpenAddressing(struct HashTable* hashTable, int key, int value) {
    int index = hashFunction(key, hashTable->capacity);
    while (hashTable->array[index] != NULL && hashTable->array[index]->key != key) {
        index = (index + 1) % hashTable->capacity;
    }
    if (hashTable->array[index] != NULL && hashTable->array[index]->key == key) {
        printf("Key already exists, updating value.\n");
        hashTable->array[index]->value = value; 
    } else {
        hashTable->array[index] = newNode(key, value);
    }
}


struct Node* searchOpenAddressing(struct HashTable* hashTable, int key) {
    int index = hashFunction(key, hashTable->capacity);
    while (hashTable->array[index] != NULL) {
        if (hashTable->array[index]->key == key)
            return hashTable->array[index];
        index = (index + 1) % hashTable->capacity;
    }
    return NULL; 
}


void insertClosedAddressing(struct HashTable* hashTable, int key, int value) {
    int index = hashFunction(key, hashTable->capacity);
    if (hashTable->array[index] == NULL) {
        hashTable->array[index] = newNode(key, value);
    } else {
        struct Node* newNode = hashTable->array[index];
        while (newNode->next != NULL && newNode->key != key)
            newNode = newNode->next;
        if (newNode->key == key) {
            printf("Key already exists, updating value.\n");
            newNode->value = value; 
        } else {
            newNode->next = newNode(key, value);
        }
    }
}


struct Node* searchClosedAddressing(struct HashTable* hashTable, int key) {
    int index = hashFunction(key, hashTable->capacity);
    struct Node* node = hashTable->array[index];
    while (node != NULL) {
        if (node->key == key)
            return node;
        node = node->next;
    }
    return NULL;
}


void rehash(struct HashTable* oldHashTable, struct HashTable* newHashTable) {
    for (int i = 0; i < oldHashTable->capacity; i++) {
        struct Node* node = oldHashTable->array[i];
        while (node != NULL) {
            insertOpenAddressing(newHashTable, node->key, node->value);
            node = node->next;
        }
    }
}


void displayHashTable(struct HashTable* hashTable) {
    for (int i = 0; i < hashTable->capacity; i++) {
        printf("Bucket %d: ", i);
        struct Node* node = hashTable->array[i];
        while (node != NULL) {
            printf("(%d, %d) ", node->key, node->value);
            node = node->next;
        }
        printf("\n");
    }
}

int main() {
    struct HashTable* hashTableOpenAddressing = createHashTable(SIZE);
    struct HashTable* hashTableClosedAddressing = createHashTable(SIZE);
    struct HashTable* hashTableRehashing = createHashTable(SIZE * 2); 

    
    insertOpenAddressing(hashTableOpenAddressing, 1, 10);
    insertOpenAddressing(hashTableOpenAddressing, 11, 20);
    insertOpenAddressing(hashTableOpenAddressing, 21, 30);

    insertClosedAddressing(hashTableClosedAddressing, 2, 40);
    insertClosedAddressing(hashTableClosedAddressing, 12, 50);
    insertClosedAddressing(hashTableClosedAddressing, 22, 60);

    
    printf("Hash Table using Open Addressing:\n");
    displayHashTable(hashTableOpenAddressing);
    printf("\nHash Table using Closed Addressing:\n");
    displayHashTable(hashTableClosedAddressing);

    
    rehash(hashTableClosedAddressing, hashTableRehashing);

    
    printf("\nHash Table after Rehashing:\n");
    displayHashTable(hashTableRehashing);

    return 0;
}
