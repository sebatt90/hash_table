#include<stdio.h>
#include<stdlib.h>
#include "hash_table.h"

int main(void){
  printf("Hello Hash Table\n");
  struct HashTable hasht = init_hashtable();
  int arr[10] = {0};
  arr[3] = 69;
  insert(&hasht, "Test", arr, 10*sizeof(int));
  
  struct KeyValuePair *test = get(&hasht, "Test");

  printf("key: %s, values:\n", test->key);
  for(int i=0;i<10;i++){
    printf("%i ", ((int *)test->value)[i]);
  }
  printf("\n");
  
  int a = 420;
  insert(&hasht, "Test", &a, sizeof(int));
  test = get(&hasht, "Test");
  printf("key: %s, value: %d\n", test->key, *((int*)(test->value)));
  return 0;
}
