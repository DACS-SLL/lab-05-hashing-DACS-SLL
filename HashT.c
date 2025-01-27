#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estructura de un nodo de la linked list
struct Node {
    int key;
    int value;
    struct Node* next;
};

// Estructura de la tabla hash
struct HashTable {
    int size;
    struct Node** buckets;
    int (*hashFunction)(int); // Nueva adición: función de hash utilizada
};

// Prototipos de funciones
struct HashTable* createHashTable(int size);
void insert(struct HashTable* hashTable, int key, int value);
int find(struct HashTable* hashTable, int key);

int main() {
    // Crear una tabla con N = 10 
    struct HashTable* hashTable = createHashTable(10);

    // Insertar algunos elementos
    insert(hashTable, 123, 456);
    insert(hashTable, 789, 101);
    insert(hashTable, 567, 432);

    return 0;
}

// Definición de la función para crear una nueva tabla hash
struct HashTable* createHashTable(int size) {
    struct HashTable* hashTable = (struct HashTable*)malloc(sizeof(struct HashTable));
    hashTable->size = size;
    hashTable->buckets = (struct Node**)malloc(sizeof(struct Node*) * size);
    hashTable->hashFunction = hashFunction; // Nueva adición: almacenar la función de hash

    // Inicializar los buckets con Vacío - NULL
    for (int i = 0; i < size; i++) {
        hashTable->buckets[i] = NULL;
    }

    return hashTable;
}

// Definición de la función para insertar un par (clave, valor)
void insert(struct HashTable* hashTable, int key, int value) {
    int index = hashTable->hashFunction(key);

    // Crear un nuevo nodo
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;

    // Si el bucket está vacío, simplemente inserta el nuevo nodo
    if (hashTable->buckets[index] == NULL) {
        hashTable->buckets[index] = newNode;
    } else {
        // Si hay alguien ocupando el espacio... añadiremos al principio de la linked list
        newNode->next = hashTable->buckets[index];
        hashTable->buckets[index] = newNode;
    }

    // Imprimir confirmación
    printf("Elemento (%d, %d) insertado con éxito.\n", key, value);
}

// Definición de la función para buscar un valor dado una clave en la tabla hash
int find(struct HashTable* hashTable, int key) {
    int index = hashTable->hashFunction(key);

    // Buscar en la linked list con la correspondiente key
    struct Node* current = hashTable->buckets[index];
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }

    // Si la clave no se encuentra, retornar -1
    return -1;
}
