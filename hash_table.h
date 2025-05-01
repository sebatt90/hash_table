#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include<stdbool.h>

#define HASH_TABLE_SIZE 16

struct KeyValuePair {
  char *key;
  void *value;
};

struct HashTable {
  struct KeyValuePair **hash_map;
  size_t table_size;
  size_t n;
};

struct HashTable *init_hashtable();
bool insert(struct HashTable *ht, char* key, void* value, size_t buf_size);
struct KeyValuePair *get(struct HashTable *ht, char *key);
void free_hashtable(struct HashTable *ht);

#endif
