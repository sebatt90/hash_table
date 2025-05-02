#include<stdio.h>
#include<stdlib.h>
#include "hash_table.h"

void get_elements(struct HashTable *hasht){
  struct KeyValuePair *kvp;
  for(int i=0;i<10000;i++){
    char str[25];
    snprintf(str, 25, "t%d", i);
    kvp = get(hasht,str);
    if(kvp == NULL){
      printf("NULL DETECTED\n");
      continue;
    }
    // dump info
    printf("key: %s; value: %d\n",kvp->key, *((int*)(kvp->value)));
  }
}

int main(void){
  printf("Hello Hash Table\n");
  struct HashTable *hasht = init_hashtable();

  // Insertion
  for(int i=0;i<10000;i++){
    char str[25];
    snprintf(str, 25, "t%d", i);

    printf("iteration %d\n",i);
    bool t = insert(hasht, str, &i, sizeof(int));
    if(!t) break;
  }

  // Retrieval
  get_elements(hasht);
  /*
  // Deletion
  for(int i=0;i<10000;i++){
    char str[25];
    snprintf(str, 25, "t%d", i);
    bool deleted = get(hasht,str);
    if(deleted == false){
      printf("Element not found\n");
      continue;
    }
    // dump info
    printf("Deleted!\n");
  }
  printf("Trying to retrieve elements again \n");
  get_elements(hasht);
  */
  free_hashtable(hasht);
  return 0;
}
