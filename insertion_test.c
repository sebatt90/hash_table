#include<stdio.h>
#include<stdlib.h>
#include "hash_table.h"

int main(void){
  struct HashTable *hasht = init_hashtable();
  // Insertion
  for(int i=0;i<10000;i++){
    char str[25];
    snprintf(str, 25, "t%d", i);
    bool t = insert(hasht, str, &i, sizeof(int));
    if(!t) break;
  }

  free_hashtable(hasht);
  return 0;
}
