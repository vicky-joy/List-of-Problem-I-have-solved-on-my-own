#include <stdio.h>
#include "data.h"
#include <string.h>
#include <stdlib.h>
#include "operations.h"

int main(int argc, char * argv[])
{
    char roomsFilePath[100] = "";
    char itemsFilePath[100] = "";
    if(argc == 2){
        strcat(roomsFilePath, argv[1]);
        strcat(itemsFilePath, argv[1]);
        strcat(roomsFilePath, "/rooms.json");
        strcat(itemsFilePath, "/items.json");
    } else{
        strcat(roomsFilePath, "./rooms.json");
        strcat(itemsFilePath, "./items.json");
    }
    

    int roomMaxId = find_max(roomsFilePath);
    int itemMaxId = find_max(itemsFilePath);

    printf("roomMaxId=%d\n", roomMaxId);
    printf("itemMaxId=%d\n", itemMaxId);


    Item *items_list;

    items_list = load_json_items(itemsFilePath, itemMaxId);
    
    if (items_list == NULL) {
        printf("Failed to load items. Exiting game.\n");
        return 1;
    }
    printf("%d %s\n", items_list[0].id, items_list[0].name);
    printf("%s\n", items_list[0].description);
    printf("%d %s\n", items_list[378].id, items_list[378].name);
    printf("%s\n", items_list[378].description);
    printf("%d %s \n", items_list[1697].id, items_list[1697].name);
    printf("%s\n", items_list[1697].description); 

    Room *rooms_list;
    rooms_list = load_json_rooms(roomsFilePath, roomMaxId);
    if (rooms_list == NULL) {
        printf("Failed to load rooms. Exiting game.\n");
        return 1;
    }

    printf("%d %s \n %s \n", rooms_list[5].id, rooms_list[5].name, rooms_list[5].description);
    printf("%d %s \n %s\n", rooms_list[359].id, rooms_list[359].name, rooms_list[359].description);
    
    int startingRoomId = 1;
    game_loop(rooms_list, items_list, startingRoomId);
    
    for(int i = 0; i <= itemMaxId; i++){
        free(items_list[i].name);
        free(items_list[i].description);
    }
    free(items_list);

     for(int i = 0; i <= roomMaxId; i++){
        free(rooms_list[i].name);
        free(rooms_list[i].description);
    }
    free(rooms_list);

    return 0;
}

//pc eof 285 main
