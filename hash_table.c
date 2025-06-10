// hash table def
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash_table.h"

#define HASH_TABLE_SIZE 16

static struct KeyValuePair *deleted;

static void _insert(struct KeyValuePair **kvp_arr, size_t table_size, struct KeyValuePair *kvp, size_t h);
static void free_hasharray(struct KeyValuePair **kvp_arr, size_t size);

struct HashTable *hashtable_init(){
  struct HashTable *ht = (struct HashTable *) malloc(sizeof(struct HashTable));
  ht->table_size = HASH_TABLE_SIZE;
  ht->hash_map = calloc(ht->table_size, sizeof(struct KeyValuePair));
  ht->n = 0;
  return ht;
}

#ifdef FNV_HASH
#include "fnv.c"
#else
static size_t hash(struct HashTable *ht, char *key){
  size_t t=0;
  for(size_t i=0;i<strlen(key);i++){
    t += key[i];
  }
  return t & (ht->table_size-1);
}
#endif

static void rehash(struct HashTable *ht){
  size_t old_table_size = ht->table_size;
  ht->table_size *= 2;
  struct KeyValuePair **new_hash = calloc(ht->table_size, sizeof(struct KeyValuePair));

  for(size_t i=0;i<old_table_size;i++){
    if(ht->hash_map[i]==deleted) continue;
    if(ht->hash_map[i]==NULL) continue;
    // rehash thing...
    size_t h = hash(ht, ht->hash_map[i]->key);
    _insert(new_hash, ht->table_size, ht->hash_map[i], h);
  }

  free(ht->hash_map);
  ht->hash_map = new_hash;
}

static void _insert(struct KeyValuePair **kvp_arr, size_t table_size, struct KeyValuePair *kvp, size_t h){
  // handle insertion
  bool ins = false;
  for(size_t i=h; i<table_size+h;i++){
    if(kvp_arr[i%table_size]==NULL || kvp_arr[i%table_size]==deleted){
      ins = true;
      kvp_arr[i%table_size] = kvp;
      break;
    } else if(strcmp(kvp_arr[i%table_size]->key, kvp->key)==0){
      free(kvp_arr[i%table_size]);
      ins = true;
      kvp_arr[i%table_size] = kvp;
      break;
    }
  }

  if(!ins) free(kvp);
}

void hashtable_insert(struct HashTable *ht, char* key, void* value, size_t buf_size){
  float load_factor = (float)ht->n/(float)ht->table_size;
  if(load_factor >= 0.6f){
    rehash(ht);
  }
  // create keyvaluepair struct
  struct KeyValuePair *kvp = malloc(sizeof(struct KeyValuePair));
  // Clone key string
  kvp->key = malloc(strlen(key)+1); // assuming char size is 1
  strncpy(kvp->key, key, strlen(key)+1);
  // clone value buffer
  kvp->value = malloc(buf_size);
  memcpy(kvp->value, value, buf_size);
  _insert(ht->hash_map, ht->table_size, kvp, hash(ht,key));
  ht->n++;
}

struct KeyValuePair *hashtable_get(struct HashTable *ht, char *key) {
  size_t h = hash(ht,key);
  for(size_t i=h; i<ht->table_size+h;i++){
    if(ht->hash_map[i%ht->table_size]==NULL) return NULL;
    if(ht->hash_map[i%ht->table_size]==deleted) continue;

    if(strcmp(ht->hash_map[i%ht->table_size]->key, key)==0){
      return ht->hash_map[i%ht->table_size];
    }
  }
  return NULL;
}

bool hashtable_delete(struct HashTable *ht, char *key) {
  size_t h = hash(ht,key);
  for(size_t i=h; i<ht->table_size+h;i++){
    size_t j = i%ht->table_size;
    if(ht->hash_map[j]==NULL) return false;
    if(ht->hash_map[j]==deleted) continue;
    if(strcmp(ht->hash_map[j]->key, key)) continue;

    free(ht->hash_map[j]->key);
    free(ht->hash_map[j]->value);
    free(ht->hash_map[j]);
    ht->hash_map[j] = deleted;
    ht->n--;
    break;
  }
  return true;
}

static void free_hasharray(struct KeyValuePair **kvp_arr, size_t size){
  for(size_t i=0;i<size;i++){
    if(kvp_arr[i]==deleted) continue;
    if(kvp_arr[i]==NULL) continue;
    free(kvp_arr[i]->key);
    free(kvp_arr[i]->value);
    free(kvp_arr[i]);
  }

  free(kvp_arr);
}

void hashtable_free(struct HashTable *ht){
  free_hasharray(ht->hash_map, ht->table_size);
  free(ht);
}
