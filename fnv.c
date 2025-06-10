/* 32 bit FNV_prime = 2^24 + 2^8 + 0x93 */
#include<stdint.h>
#define FNV32prime 0x01000193
#define FNV32basis 0x811C9DC5

static uint32_t hash(struct HashTable *ht, char *key){
  uint32_t hash = FNV32basis;

  char ch;
  while( (ch = *key++))
    hash = FNV32prime * (hash ^ ch);

  return hash & (ht->table_size-1);
}
