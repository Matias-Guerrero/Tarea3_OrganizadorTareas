#ifndef TREEMAP_h
#define TREEMAP_h

typedef struct TreeMap TreeMap;

typedef struct Pair {
     void * key;
     void * value;
} Pair;

TreeMap * createTreeMap(int (*lower_than_int) (void* key1, void* key2));

void insertTreeMap(TreeMap * tree, void* key, void * value); // Funcion actualizada

void eraseTreeMap(TreeMap * tree, void* key);

Pair * searchTreeMap(TreeMap * tree, void* key);

Pair * upperBound(TreeMap * tree, void* key);

Pair * firstTreeMap(TreeMap * tree);

Pair * nextTreeMap(TreeMap * tree);

// Nuevas funciones
void removerNodoActual(TreeMap * tree);

void actualizarNodoActual(TreeMap * tree, void* key, void * value);

#endif /* TREEMAP_h */
