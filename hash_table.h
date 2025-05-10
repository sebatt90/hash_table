#ifndef HASH_TABLE_H

#define HASH_TABLE_H
#include <stdbool.h>
#include <stddef.h>

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

struct HashTable *hashtable_init();
bool hashtable_insert(struct HashTable *ht, char* key, void* value, size_t buf_size);
struct KeyValuePair *hashtable_get(struct HashTable *ht, char *key);
void hashtable_free(struct HashTable *ht);
bool hashtable_delete(struct HashTable *ht, char *key);

#endif
