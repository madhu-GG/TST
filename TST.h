#ifndef TST_H
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t type;
typedef struct Node Node;
typedef struct TST TST;

TST* TST_alloc(void);
void TST_free(TST* tst_ptr);
bool TST_insert(TST* tst_ptr, type* key, size_t key_len, void* value);
void* TST_get(TST* tst_ptr, type* key);
void* TST_remove(TST* tst_ptr, type* key);
type* TST_longestPrefix(TST* tst_ptr, size_t* ret_len, type* key, size_t key_len);
size_t TST_count(TST *tst_ptr);
#endif /* TST_H */