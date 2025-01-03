#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TABLE_SIZE 10

typedef struct Person {
    char name[256];
    int age;
    struct Person* next; // Pointer to the next person in the chain
} Person;

typedef struct HashTable {
    Person* table[TABLE_SIZE]; // Array of pointers to Person
} HashTable;


//Insert Function :
int insert(HashTable* ht, const char* name, int age) {
    unsigned int index = hash(name); // Find the hash index using the name
    Person* newPerson = malloc(sizeof(Person));
    strcpy(newPerson->name, name);
    newPerson->age = age;
    newPerson->next = NULL;

    // Insert at the beginning of the linked list
    if (ht->table[index] == NULL) {
        ht->table[index] = newPerson; // Empty slot, insert the person
    } else {
        newPerson->next = ht->table[index]; // Insert at the head of the chain
        ht->table[index] = newPerson;
    }
    return 1; // Success
}

//Lookup (search) Function :

Person* lookup(HashTable* ht, const char* name) {
    unsigned int index = hash(name); // Find the hash index using the name
    Person* current = ht->table[index];

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current; // Found the person
        }
        current = current->next; // Move to the next person in the chain
    }
    return NULL; // Not found
}
