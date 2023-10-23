#include "TST.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    type keyBit;
    void* value_ptr;
    size_t count;
    Node *next[3];
};

typedef struct LinkNode {
    type key;
    struct LinkNode *next;
} LinkNode;

struct TST {
    Node* root;
    size_t count;
};


static void print_key(uint8_t* key, int key_len)
{
    for (int i = 0; i < key_len; i++)
    {
        printf(" %d", key[i]);
    }
    printf("\n");
}

static void visit(Node *ptr, uint8_t *key_buf, int depth)
{
    if (ptr == NULL) return;

    visit(ptr->next[0], key_buf, depth);
    key_buf[depth] = ptr->keyBit;
    if (ptr->value_ptr != NULL)
    {
        key_buf[depth + 1] = 0;
        print_key(key_buf, depth + 1);
    }
    visit(ptr->next[1], key_buf, depth + 1);
    visit(ptr->next[2], key_buf, depth);
}

TST* tst_alloc(void)
{
    TST* tst_ptr = malloc(sizeof(TST));
    if (tst_ptr != NULL)
    {
        tst_ptr->count = 0;
        tst_ptr->root = NULL;
    }
}

void tst_free(TST* tst_ptr);

Node * insert(Node *parent, type* key, size_t key_len, void* value, int i)
{
    /* for the case when left or right node is empty and we add a key there */
    if (parent == NULL)
    {
        Node *ptr, *prev;
        for (int j = i; j < key_len; j++)
        {
            ptr = calloc(1, sizeof(Node));
            ptr->count = 1;
            ptr->keyBit = key[j];
            ptr->value_ptr = NULL;
            ptr->next[0] = ptr->next[1] = ptr->next[2] = NULL;

            if (j == i)
            {
                parent = ptr;
                prev = ptr;
            } else
            {
                prev->next[1] = ptr;
                prev = ptr;
            }
        }
        
        ptr->value_ptr = value;
        return parent;

        // parent = calloc(1, sizeof(Node));
        // parent->keyBit = key[i];
        // parent->value_ptr = NULL;
        // parent->next[0] = parent->next[1] = parent->next[2] = NULL;
        // parent->count = 1;

        // Node *ptr, *prev;
        // prev = parent;

        // while(i < key_len)
        // {
        //     i++;
        //     ptr = calloc(1, sizeof(Node));
        //     ptr->count = 1;
        //     ptr->keyBit = key[i];
        //     ptr->value_ptr = NULL;
        //     ptr->next[0] = ptr->next[1] = ptr->next[2] = NULL;

        //     prev->next[1] = ptr;
        //     prev = ptr;            
        // }

        // if (i == key_len)
        // {
        //     ptr->value_ptr = value;
        // }

        // return parent;
    }
    else
    {
        /* key exists, overwrite */
        if (i == key_len)
        {
            parent->value_ptr = value;
            return parent;
        }

        int nextIndex, depth = i;
        if (key[i] == parent->keyBit)
        {
            nextIndex = 1;
            depth++;
        }
        else if (key[i] < parent->keyBit)
        {
            nextIndex = 0;
        }
        else
        {
            nextIndex = 2;
        }

        parent->next[nextIndex] = insert(parent->next[nextIndex], key, key_len, value, depth);
        parent->count++;
        return parent;
    }
}

bool tst_insert(TST* tst_ptr, type* key, size_t key_len, void* value)
{
    Node *ptr;
    if (tst_ptr == NULL || key == NULL || key_len == 0)
    {
        return false;
    }

    tst_ptr->root = insert(tst_ptr->root, key, key_len, value, 0);

    tst_ptr->count = tst_ptr->root->count;
    return true;
}


void* tst_get(TST* tst_ptr, type* key);
void* tst_remove(TST* tst_ptr, type* key);

/*
 * perform DFS:
 * 1. check if left has any value
 * 2. check if right has any value
 * 3. check if current has value
 * 4. return largest key_len
 */
size_t findPrefix(Node* ptr, type* res_buf, size_t *res_len, type* key, size_t key_len, size_t depth)
{
    if (ptr == NULL)
    {
        return 0;
    }

    if (depth == key_len)
    {
        if (ptr->value_ptr != NULL)
        {
            res_buf[depth] = 0;
            return depth;
        } else
        {
            return 0;
        }
    }

    // if (depth == key_len - 1)
    // {
    //     if (key[depth] == ptr->keyBit && ptr->value_ptr != NULL)
    //     {
    //         res_buf[depth] = ptr->keyBit;
    //         *res_len = depth + 1;
    //         return depth + 1;
    //     }
    //     else
    //     {
    //         return 0;
    //     }
    // }

    if (key[depth] == ptr->keyBit)
    {
        size_t middle_len = 0;
        res_buf[depth] = ptr->keyBit;
        *res_len = depth + 1;
        middle_len = findPrefix(ptr->next[1], res_buf, res_len, key, key_len, depth + 1);
        if (middle_len == 0 && ptr->value_ptr != NULL)
        {
            return *res_len;
        }
        else
        {
            return middle_len;
        }
    }
    else if (key[depth] < ptr->keyBit)
    {
        size_t left_len = 0;

        left_len = findPrefix(ptr->next[0], res_buf, res_len, key, key_len, depth);
        return left_len;
    }
    else
    {
        size_t right_len = 0;

        right_len = findPrefix(ptr->next[2], res_buf, res_len, key, key_len, depth);
        return right_len;
    }
}

type* tst_longestPrefix(TST* tst_ptr, size_t * ret_len, type* key, size_t key_len)
{
    type *key_buf, *result_buf;

    if (tst_ptr == NULL)
    {
        *ret_len = 0;
        return NULL;
    }

    Node *ptr = tst_ptr->root;
    result_buf = calloc(key_len, sizeof(type));
    
    *ret_len = findPrefix(ptr, result_buf, ret_len, key, key_len, 0);
    
    return result_buf;
}

size_t tst_count(TST *tst_ptr)
{
    if (tst_ptr == NULL)
    {
        return 0;
    } else {
        return tst_ptr->count;
    }
}

void tst_iter_print(TST *tst)
{
    uint8_t *key_buf;
    if (tst == NULL)
    {
        return;
    }

    key_buf = calloc(100, sizeof(uint8_t));

    visit(tst->root, key_buf, 0);

    printf("TST count = %ld\n", tst->count);
}

typedef struct test {
    uint8_t key[4];
    size_t key_len;
    char value;
} Test;

int main(int argc, char** argv)
{
    int rc = 0;
    // uint8_t key1[] = {192, 168}; // A
    // uint8_t key2[] = {192, 168, 5}; // B
    // uint8_t key3[] = {192, 169, 10}; // C
    // uint8_t key4[] = {192, 169, 10, 1}; // D
    uint8_t src1[] = {192, 169, 11, 3};

    Test T[] = {
        {{192, 168}, 2, 'A'},
        {{192, 168, 5}, 3, 'B'},
        {{192, 169, 10}, 3, 'C'},
        {{192, 169, 11}, 3, 'D'},
        {{192, 169, 10, 1}, 4, 'E'},
        {{192, 169, 11, 1}, 4, 'M'},
        {{192, 169, 11, 2}, 4, 'N'},
        {{192}, 1, 'F'},
        {{172, 168, 10}, 3, 'G'},
        {{172, 169, 5}, 3, 'H'},
        {{172, 0, 1}, 3, 'I'},
        {{172, 0, 0, 0}, 4, 'J'},
        {{172, 168, 10, 2}, 4, 'K'},
        {{172}, 1, 'L'},
        {{}, 0, '\0'}
    };

    size_t res_len = 0;
    char v1 = 'A', v2='B', v3 = 'C', v4='D';

    TST * tst = tst_alloc();

    // tst_insert(tst, key1, 2, (void*)&v1);
    // tst_insert(tst, key2, 3, (void*)&v2);
    // tst_insert(tst, key3, 3, (void*)&v3);
    // tst_insert(tst, key4, 4, (void*)&v4);

    for (int i = 0; T[i].key_len != 0; i++) {
        tst_insert(tst, T[i].key, T[i].key_len, (void*) &T[i].value);
    }

    tst_iter_print(tst);
    printf("Longest prefix search for: \n");
    print_key(src1, 4);
    printf("Result = \n");
    uint8_t* res_buf = tst_longestPrefix(tst, &res_len, src1, 4);
    if (res_len == 0)
    {
        printf ("No longest prefix found!\n");
    } else
    {
        print_key(res_buf, res_len);
    }

    return 0;
}
