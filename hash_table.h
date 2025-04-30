#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include<stdbool.h>

#define HASH_TABLE_SIZE 255

struct KeyValuePair {
  char *key;
  void *value;
};

struct HashTable {
  struct KeyValuePair **hash_map;
};

struct HashTable init_hashtable();
bool insert(struct HashTable *ht, char* key, void* value, size_t buf_size);
struct KeyValuePair *get(struct HashTable *ht, char *key);

#endif
