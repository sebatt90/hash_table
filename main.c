#include<stdio.h>
#include<stdlib.h>
#include "hash_table.h"

int main(void){
  printf("Hello Hash Table\n");
  struct HashTable *hasht = init_hashtable();

  // Insertion
  for(int i=0;i<240;i++){
    char str[25];
    snprintf(str, 25, "t%d\0", i);
    int a = 69;

    printf("iteration %d\n",i);
    bool t = insert(hasht, str, &a, sizeof(a));
    if(!t) break;
  }

  // Retrieval
  struct KeyValuePair *kvp;
  for(int i=0;i<240;i++){
    char str[25];
    snprintf(str, 25, "t%d\0", i);
    kvp = get(hasht,str);
    // dump info
    printf("key: %s; value: %d\n",kvp->key, *((int*)(kvp->value)));
  }

  free_hashtable(hasht);
  return 0;
}
