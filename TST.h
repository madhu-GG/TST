#ifndef TST_H
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t type;
typedef struct Node Node;
typedef struct TST TST;

TST* tst_alloc(void);
void tst_free(TST* tst_ptr);
bool tst_insert(TST* tst_ptr, type* key, size_t key_len, void* value);
void* tst_get(TST* tst_ptr, type* key);
void* tst_remove(TST* tst_ptr, type* key);
type* tst_longestPrefix(TST* tst_ptr, size_t* ret_len, type* key, size_t key_len);
size_t tst_count(TST *tst_ptr);
#endif /* TST_H */
