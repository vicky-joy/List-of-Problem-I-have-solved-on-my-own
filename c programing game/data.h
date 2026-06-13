
#ifndef DATA_H
#define DATA_H 

#include<stdbool.h>

typedef struct Room {
    int id;
    char *name;
    char *description;
    int north;
    int south;
    int east;
    int west;
    int item;
    bool starting;
} Room;

typedef struct Item {
    int id;
    char *name;
    char *description;
} Item;


int find_max(char *filename);
/** DO NOT ADD CODE INSIDE THIS FILE ADD to data.c **/

Room * load_json_rooms(char * filename, int roomMaxId);
/** DO NOT ADD CODE INSIDE THIS FILE ADD to data.c **/

Item * load_json_items(char * filename, int itemMaxId);
/** DO NOT ADD CODE INSIDE THIS FILE ADD to data.c **/

#endif 
