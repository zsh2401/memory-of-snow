#ifndef __MAP_H
#define __MAP_H
typedef char *key_t;
typedef void *value_t;
typedef struct _Map
{
    /* data */
} *Map;

void Map_Init(Map *target);
void Map_Get(Map map, key_t key, value_t *value);
void Map_Set(Map map, key_t key, value_t value);
void Map_Remove(Map map, key_t key);
void Map_Exist(Map map, key_t key);
void Map_Free(Map map);
#endif