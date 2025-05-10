#include <stdio.h>
#include "hash_table.h"

int main(void){
  struct HashTable *hasht = hashtable_init();

  // Insertion
  for(int i=0;i<10000;i++){
    char str[25];
    snprintf(str, 25, "t%d", i);
    bool t = hashtable_insert(hasht, str, &i, sizeof(int));
    if(!t) break;
  }

  hashtable_free(hasht);
  return 0;
}
