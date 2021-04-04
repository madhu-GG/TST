#ifndef TST_H
#define TST_H
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// typedef uint8_t type;
// typedef struct Node Node;
// typedef struct TST TST;

// TST* TST_alloc(void);
// void TST_free(TST* tst_ptr);
// bool TST_insert(TST* tst_ptr, type* key, size_t key_len, void* value);
// void* TST_get(TST* tst_ptr, type* key);
// void* TST_remove(TST* tst_ptr, type* key);
// type* TST_longestPrefix(TST* tst_ptr, size_t* ret_len, type* key, size_t key_len);
// size_t TST_count(TST *tst_ptr);

typedef struct tst tst;

/**
 * tst* tst_alloc(uint32_t radix);
 *
 * function to allocate memory for an empty ternary search trie.
 *
 * input:
 *  uint32_t radix: number of symbols in the language.
 *
 * output:
 *  None.
 *
 * returns:
 * tst* : pointer to an empty ternary search trie.
 */
tst* tst_alloc(uint32_t radix);

/**
 * void tst_free(tst* tst_ptr);
 *
 * function to free memory of a ternary search trie. This function
 * attempts to remove all the keys and values stored in the trie.
 *
 * input:
 *  tst* tst_ptr : pointer to a ternary search trie.
 *
 * output:
 *  None.
 *
 * returns:
 *  void
 */
void tst_free(tst* tst_ptr);

/**
 * size_t tst_count(tst* tst_ptr);
 *
 * function to return the number of (key, value) pairs that were
 * inserted into the trie using tst_put()
 *
 * input:
 *  tst* tst_ptr: pointer to a ternary search trie.
 *
 * output:
 *  None.
 *
 * returns:
 *  size_t : number of (key, value) pairs in the trie.
 */
size_t tst_count(tst* tst_ptr);

/**
 * void* tst_get(tst* tst_ptr, void* key);
 *
 * function to return the value for the given key, NULL if key is
 * not found in the trie or key is NULL or the tst pointer is NULL.
 *
 * input:
 *  tst* tst_ptr: pointer to a ternary search trie.
 *  void* key: generic pointer to the key.
 *
 * output:
 *  None.
 *
 * returns:
 *  void* : generic pointer to value object, NULL if it is not found;
 *          or the key is NULL or the tst pointer is NULL.
 */
void* tst_get(tst* tst_ptr, void* key);

/**
 * void* tst_remove(tst* tst_ptr, void* key);
 *
 * function to remove the value for the given key, NULL if key is
 * not found in the trie or key is NULL or the tst pointer is NULL.
 *
 * input:
 *  tst* tst_ptr: pointer to a ternary search trie.
 *  void* key: generic pointer to the key.
 *
 * output:
 *  None.
 *
 * returns:
 *  void* : generic pointer to value object that was removed.
 *          NULL if it is not found, or
 *          the key is NULL or the tst pointer is NULL.
 */
void* tst_remove(tst* tst_ptr, void* key);

/**
 * int tst_put(tst* tst_ptr, void* key, void* value);
 *
 * function to put the (key, value) pair into the trie. Fails
 * if the tst pointer is NULL, or key is NULL.
 *
 * This function overwrites the value pointer if the key already exists
 * in the trie.
 *
 * Returns 0 on successful return without value overwrite, 1 on overwrite,
 * and -1 on failure.
 *
 * input:
 *  tst* tst_ptr: pointer to a ternary search trie.
 *  void* key: generic pointer to the key.
 *  void* value: generic pointer to the value to insert.
 *
 * output:
 *  None.
 *
 * returns:
 *  0 : on successful addition without value overwrite.
 *  1 : on overwrite of value if key already exists.
 *  -1 : if either tst pointer or key are NULL.
 */
int tst_put(tst* tst_ptr, void* key, void* value);

/**
 * void* tst_longest_prefix(tst* tst_ptr, void* search_term);
 *
 * function to return the value of the longest prefix of the given search_term
 * in the trie.
 *
 * returns NULL if the search_term does not have a prefix with a value.
 *
 * input:
 *  tst* tst_ptr: pointer to a ternary search trie.
 *  void* search_term: generic pointer to the search_term.
 *
 * output:
 *  None.
 *
 * returns:
 *  void* : generic pointer to value object, corresponding to the longest
 *          prefix key in the trie.
 *          NULL if there is no prefix of the given search_term
 *          that has a stored value in the trie.
 *          NULL if the search_term is NULL or the tst pointer is NULL.
 */
void* tst_longest_prefix(tst* tst_ptr, void* search_term);
#endif /* TST_H */