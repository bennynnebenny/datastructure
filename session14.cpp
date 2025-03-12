#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 10

struct node
{
    char data[100];
    struct node *next;
} *hashTable[TABLE_SIZE], *curr;

// Hash Functions
int midSquare(int key)
{
    key = key * key;
    return (key / 100) % TABLE_SIZE;
}

int divisionHash(int key)
{
    return key % TABLE_SIZE;
}

int foldingHash(int key)
{
    int part1 = key / 1000;
    int part2 = key % 1000;
    return (part1 + part2) % TABLE_SIZE;
}

int digitExtraction(int key)
{
    return (key / 10) % TABLE_SIZE;
}

int rotationHash(int key)
{
    int lastDigit = key % 10;
    int remaining = key / 10;
    return ((lastDigit * 1000) + remaining) % TABLE_SIZE;
}

int hashFunction(char data[], int hashFchoice)
{
    int hashKey = tolower(data[0]) - 97;
    switch (hashFchoice)
    {
    case 1:
        return midSquare(hashKey);
    case 2:
        return divisionHash(hashKey);
    case 3:
        return foldingHash(hashKey);
    case 4:
        return digitExtraction(hashKey);
    case 5:
        return rotationHash(hashKey);
    default:
        return hashKey % TABLE_SIZE;
    }
}

void linearProbing(int *hashKey)
{
    while (hashTable[*hashKey] != NULL)
    {
        *hashKey = (*hashKey + 1) % TABLE_SIZE;
    }
}

void chaining(int hashKey, char data[])
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    strcpy(newNode->data, data);
    newNode->next = hashTable[hashKey];
    hashTable[hashKey] = newNode;
}

void pushBack(int hashKey, char data[], int collisionHchoice)
{
    if (collisionHchoice == 1)
    {
        linearProbing(&hashKey);
        struct node *newNode = (struct node *)malloc(sizeof(struct node));
        strcpy(newNode->data, data);
        newNode->next = NULL;
        hashTable[hashKey] = newNode;
    }
    else if (collisionHchoice == 3)
    {
        chaining(hashKey, data);
    }
}

void viewHashTable()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        printf("Hash Table Index [%d] : ", i);
        curr = hashTable[i];
        while (curr != NULL)
        {
            printf("%s -> ", curr->data);
            curr = curr->next;
        }
        printf("NULL\n");
    }
}

int main()
{
    char data[100];
    int hashFchoice = 0, collisionHchoice = 0;

    while (hashFchoice < 1 || hashFchoice > 5)
    {
        printf("Choose Hash Function:\n1. Mid Square\n2. Division\n3. Folding\n4. Digit Extraction\n5. Rotation\n>> ");
        scanf("%d", &hashFchoice);
        getchar();
    }

    while (collisionHchoice < 1 || collisionHchoice > 3)
    {
        printf("Choose Collision Handling:\n1. Linear Probing\n2. Rehashing (Not Implemented)\n3. Chaining\n>> ");
        scanf("%d", &collisionHchoice);
        getchar();
    }

    while (1)
    {
        printf("Input Data (type 'exit' to stop): ");
        scanf("%s", data);
        if (strcmpi(data, "exit") == 0)
            break;
        pushBack(hashFunction(data, hashFchoice), data, collisionHchoice);
    }

    viewHashTable();
    return 0;
}