# libhash
Static library to work with hashtables, written in C.

## Introduction

> In computing, a hash table is a data structure that implements an associative array abstract data type, a structure that can map keys to values. A hash table uses a hash function to compute an index, also called a hash code, into an array of buckets or slots, from which the desired value can be found.

This library give us a simple hash table implementation in C language, comprising the following functions to store, retrieve and clear data.

```C
t_hashtable		*ht_create(unsigned int size);
int				ht_set(t_hashtable *ht, const char *key, void *value);
void			*ht_get(t_hashtable *ht, const void *key);
void			ht_free(t_hashtable *ht, void (del)(void *));
void			ht_remove(t_hashtable *h, const char *k, void (*d)(void*));
```
