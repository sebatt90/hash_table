// hash table def
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include "hash_table.h"

struct HashTable init_hashtable(){
  struct HashTable *ht = (struct HashTable *) malloc(sizeof(struct HashTable));
  ht->hash_map = calloc(HASH_TABLE_SIZE, sizeof(struct KeyValuePair));
}

size_t hash(char *key){
  size_t t=0;
  for(size_t i=0;i<strlen(key);i++){
    t += key[i];
  }
  return t % HASH_TABLE_SIZE;
}

bool insert(struct HashTable *ht, char* key, void* value, size_t buf_size){
  // create keyvaluepair struct
  struct KeyValuePair *kvp = malloc(sizeof(struct KeyValuePair));
  // Clone key string
  kvp->key = malloc(strlen(key)+1); // assuming char size is 1
  strncpy(kvp->key, key, strlen(key)+1);
  // clone value buffer
  kvp->value = malloc(buf_size);
  memcpy(kvp->value, value, buf_size);

  // handle insertion
  size_t h = hash(key);

  bool ins = false;
  for(size_t i=h; i<HASH_TABLE_SIZE;i++){
    if(ht->hash_map[i]==NULL){
      ins = true;
      ht->hash_map[i] = kvp;
      break;
    } else if(strcmp(ht->hash_map[i]->key, key)==0){
      // TODO: delete old reference
      ins = true;
      ht->hash_map[i] = kvp;
      break;
    }
  }

  return false;
}

struct KeyValuePair *get(struct HashTable *ht, char *key) {
  // TODO: fix this
  return ht->hash_map[hash(key)];
}
