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

// Hash function
unsigned int hash(const char* name) {
    unsigned int hashValue = 0;
    while (*name) {
        hashValue += *name++;
    }
    return hashValue % TABLE_SIZE; // Ensure the index is within table size
}

// Initialize the hash table
HashTable* createHashTable() {
    HashTable* ht = malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL; // Initialize all entries to NULL
    }
    return ht;
}

// Insert a person into the hash table
int insert(HashTable* ht, const char* name, int age) {
    unsigned int index = hash(name);
    Person* newPerson = malloc(sizeof(Person));
    strcpy(newPerson->name, name);
    newPerson->age = age;
    newPerson->next = NULL;

    // Insert at the beginning of the linked list
    if (ht->table[index] == NULL) {
        ht->table[index] = newPerson;
    } else {
        newPerson->next = ht->table[index];
        ht->table[index] = newPerson;
    }
    return 1; // Success
}

// Lookup a person by name
Person* lookup(HashTable* ht, const char* name) {
    unsigned int index = hash(name);
    Person* current = ht->table[index];

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current; // Found the person
        }
        current = current->next; // Move to the next in the chain
    }
    return NULL; // Not found
}

// Delete a person from the hash table
int delete(HashTable* ht, const char* name) {
    unsigned int index = hash(name);
    Person* current = ht->table[index];
    Person* previous = NULL;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (previous == NULL) {
                ht->table[index] = current->next; // Remove from head
            } else {
                previous->next = current->next; // Bypass the current node
            }
            free(current); // Free the memory
            return 1; // Success
        }
        previous = current;
        current = current->next; // Move to the next in the chain
    }
    return 0; // Not found
}

// Print the hash table
void printHashTable(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        Person* current = ht->table[i];
        while (current != NULL) {
            printf("-> %s (%d) ", current->name, current->age);
            current = current->next;
        }
        printf("\n");
    }
}

// Free the hash table
void freeHashTable(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Person* current = ht->table[i];
        while (current != NULL) {
            Person* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht);
}

int main() {
    HashTable* ht = createHashTable();

    insert(ht, "Alice", 30);
    insert(ht, "Bob", 25);
    insert(ht, "Charlie", 35);
    insert(ht, "David", 40);
    insert(ht, "Eve", 28);
    insert(ht, "Frank", 33);
    insert(ht, "Grace", 22);
    insert(ht, "Heidi", 29);
    insert(ht, "Ivan", 31);
    insert(ht, "Judy", 27);

    printHashTable(ht);

    // Lookup
    Person* found = lookup(ht, "Charlie");
    if (found) {
        printf("Found: %s, Age: %d\n", found->name, found->age);
    } else {
        printf("Not found\n");
    }

    // Delete
    delete(ht, "Alice");
    printf("After deleting Alice:\n");
    printHashTable(ht);

    return 0;
}