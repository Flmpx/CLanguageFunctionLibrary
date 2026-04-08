#ifndef _MAP_INT_INT_H
#define _MAP_INT_INT_H

#define DEL -2
#define NONE -1
#define NOT_FOUND -1
typedef struct entry {
    int key;
    int val;
} Entry;

typedef struct map {
    Entry* arr;
    int size;
    int len;
    int mod;
} Map;

#endif