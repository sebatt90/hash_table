// hash table def
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include "hash_table.h"


void free_hasharray(struct KeyValuePair **kvp_arr, size_t size);
void free_hasharray_rehash(struct KeyValuePair **kvp_arr, size_t size);

struct HashTable *init_hashtable(){
  struct HashTable *ht = (struct HashTable *) malloc(sizeof(struct HashTable));
  ht->table_size = HASH_TABLE_SIZE;
  ht->hash_map = calloc(ht->table_size, sizeof(struct KeyValuePair));
  ht->n = 0;
  return ht;
}

static size_t hash(struct HashTable *ht, char *key){
  size_t t=0;
  for(size_t i=0;i<strlen(key);i++){
    t += key[i];
  }
  return t % ht->table_size;
}

static void rehash(struct HashTable *ht){
  size_t old_table_size = ht->table_size;
  ht->table_size *= 2;
  //ht->hash_map = realloc(ht->hash_map, ht->table_size);
  struct KeyValuePair **new_hash = calloc(ht->table_size, sizeof(struct KeyValuePair));

  for(size_t i=0;i<old_table_size;i++){
    if(ht->hash_map[i]==NULL) continue;
    // rehash thing...
    struct KeyValuePair *kvp = (struct KeyValuePair*)malloc(sizeof(struct KeyValuePair));
    memcpy(kvp, ht->hash_map[i], sizeof(struct KeyValuePair));
    new_hash[hash(ht, ht->hash_map[i]->key)] = kvp;
  }

  // free old hash map
  free_hasharray_rehash(ht->hash_map, old_table_size);
  ht->hash_map = new_hash;
}


bool insert(struct HashTable *ht, char* key, void* value, size_t buf_size){
  float load_factor = (float)ht->n/(float)ht->table_size;
  if(load_factor >= 0.6f){
    rehash(ht);
    printf("Rehash! New table size is: %d\n", ht->table_size);
  }
  // create keyvaluepair struct
  struct KeyValuePair *kvp = malloc(sizeof(struct KeyValuePair));
  // Clone key string
  kvp->key = malloc(strlen(key)+1); // assuming char size is 1
  strncpy(kvp->key, key, strlen(key)+1);
  // clone value buffer
  kvp->value = malloc(buf_size);
  memcpy(kvp->value, value, buf_size);

  // handle insertion
  size_t h = hash(ht, key);

  bool ins = false;
  for(size_t i=h; i<ht->table_size;i++){
    if(ht->hash_map[i]==NULL){
      ins = true;
      ht->n++;
      ht->hash_map[i] = kvp;
      break;
    } else if(strcmp(ht->hash_map[i]->key, key)==0){
      free(ht->hash_map[i]);
      ins = true;
      ht->n++;
      ht->hash_map[i] = kvp;
      break;
    }
  }

  return ins;
}

struct KeyValuePair *get(struct HashTable *ht, char *key) {
  size_t h = hash(ht,key);
  for(size_t i=h; i<ht->table_size;i++){
    if(ht->hash_map[i]==NULL) continue;

    if(strcmp(ht->hash_map[i]->key, key)==0){
      return ht->hash_map[i];
    }
  }
  return NULL;
}

void free_hasharray(struct KeyValuePair **kvp_arr, size_t size){
  for(size_t i=0;i<size;i++){
    if(kvp_arr[i]==NULL) continue;
    free(kvp_arr[i]->key);
    free(kvp_arr[i]->value);
    free(kvp_arr[i]);
  }
    
  free(kvp_arr);
}

void free_hasharray_rehash(struct KeyValuePair **kvp_arr, size_t size){
  for(size_t i=0;i<size;i++){
    if(kvp_arr[i]==NULL) continue;
    free(kvp_arr[i]);
  }
    
  free(kvp_arr);
}

void free_hashtable(struct HashTable *ht){
  free_hasharray(ht->hash_map, ht->table_size);
  free(ht);
}
