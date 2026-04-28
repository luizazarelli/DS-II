#include "hashtable.h"

typedef struct ht_entry
{
    char*            chave;
    void*            info;
    struct ht_entry* next;
} ht_entry;

typedef struct ht_table
{
    ht_entry** buckets;
    int        capacity;
    int        size;
} ht_table;

static unsigned int hashFn(const char* chave, int capacity)
{
    unsigned long h = 5381;
    int c;
    while ((c = (unsigned char)*chave++))
        h = h * 33 + c;
    return (unsigned int)(h % (unsigned long)capacity);
}

HashTable createHT(int n)
{
    assert(n > 0);
    ht_table* t = calloc(1, sizeof(ht_table));
    assert(t != NULL);
    t->buckets  = calloc(n, sizeof(ht_entry*));
    assert(t->buckets != NULL);
    t->capacity = n;
    t->size     = 0;
    return t;
}

void killHT(HashTable ht)
{
    if (!ht) return;
    ht_table* t = ht;
    for (int i = 0; i < t->capacity; i++)
    {
        ht_entry* e = t->buckets[i];
        while (e)
        {
            ht_entry* tmp = e->next;
            free(e->chave);
            free(e);
            e = tmp;
        }
    }
    free(t->buckets);
    free(t);
}

void insertHT(HashTable ht, char* chave, void* info)
{
    assert(!existsHT(ht, chave));
    ht_table* t = ht;
    unsigned int idx = hashFn(chave, t->capacity);

    ht_entry* e = calloc(1, sizeof(ht_entry));
    assert(e != NULL);
    e->chave = strdup(chave);
    assert(e->chave != NULL);
    e->info  = info;
    e->next  = t->buckets[idx];
    t->buckets[idx] = e;
    t->size++;
}

int existsHT(HashTable ht, char* chave)
{
    ht_table* t = ht;
    unsigned int idx = hashFn(chave, t->capacity);
    ht_entry* e = t->buckets[idx];
    while (e)
    {
        if (strcmp(e->chave, chave) == 0)
            return 1;
        e = e->next;
    }
    return 0;
}

void* getHT(HashTable ht, char* chave)
{
    assert(existsHT(ht, chave));
    ht_table* t = ht;
    unsigned int idx = hashFn(chave, t->capacity);
    ht_entry* e = t->buckets[idx];
    while (e)
    {
        if (strcmp(e->chave, chave) == 0)
            return e->info;
        e = e->next;
    }
    return NULL;
}

void* removeHT(HashTable ht, char* chave)
{
    assert(existsHT(ht, chave));
    ht_table* t = ht;
    unsigned int idx = hashFn(chave, t->capacity);
    ht_entry* e    = t->buckets[idx];
    ht_entry* prev = NULL;

    while (e)
    {
        if (strcmp(e->chave, chave) == 0)
        {
            if (prev)
                prev->next = e->next;
            else
                t->buckets[idx] = e->next;
            void* info = e->info;
            free(e->chave);
            free(e);
            t->size--;
            return info;
        }
        prev = e;
        e    = e->next;
    }
    return NULL;
}

int sizeHT(HashTable ht)
{
    return ((ht_table*)ht)->size;
}
