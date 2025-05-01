#include<stdio.h>
#include<stdlib.h>
#include "hash_table.h"

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
  struct KeyValuePair *kvp;
  for(int i=0;i<10000;i++){
    char str[25];
    snprintf(str, 25, "t%d", i);
    kvp = get(hasht,str);
    if(kvp == NULL) continue;
    // dump info
    printf("key: %s; value: %d\n",kvp->key, *((int*)(kvp->value)));
  }
  free_hashtable(hasht);
  return 0;
}
