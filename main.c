#include <stdio.h>
#include "hash_table.h"

void get_elements(struct HashTable *hasht){
  printf("Retrieving items\n");
  struct KeyValuePair *kvp;
  for(int i=0;i<10000;i++){
    char str[25];
    snprintf(str, 25, "t%d", i);
    kvp = hashtable_get(hasht,str);
    if(kvp == NULL){
      continue;
    }
    // dump info
    printf("key: %s; value: %d\n",kvp->key, *((int*)(kvp->value)));
  }
}

int main(void){
  printf("Hello Hash Table\n");
  struct HashTable *hasht = hashtable_init();

  // Insertion
  for(int i=0;i<10000;i++){
    char str[25];
    snprintf(str, 25, "t%d", i);

    printf("iteration %d\n",i);
    bool t = hashtable_insert(hasht, str, &i, sizeof(int));
    if(!t) break;
  }

  // Retrieval
  get_elements(hasht);
  // Deletion
  for(int i=0;i<10000;i++){
    char str[25];
    snprintf(str, 25, "t%d", i);

    if(i%2==0){
	bool deleted = hashtable_delete(hasht,str);
	if(deleted == false){
	    printf("Element not found\n");
	    continue;
	}
    }
  }
  printf("Trying to retrieve elements again \n");
  get_elements(hasht);

  hashtable_free(hasht);
  return 0;
}
