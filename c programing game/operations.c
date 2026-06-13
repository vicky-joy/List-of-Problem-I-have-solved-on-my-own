#include "operations.h"
#include <string.h>
#include <stdio.h>



/** Put functions here **/
int inventory[100];
int invIdx = -1;

void game_loop(Room rooms[], Item items[], int startingRoomId){
    int currentRoomId = startingRoomId;
    for( ;;) {  
        printf("#%d : %s\n", rooms[currentRoomId].id, rooms[currentRoomId].name);
        printf("%s\n", rooms[currentRoomId].description);
        if(rooms[currentRoomId].item != -1){
            printf("You see a %s\n", items[rooms[currentRoomId].item].name);
        } 
        char inquir[100] = "";
        char opt[20] = "";
        strcat(inquir, "[");
        if(rooms[currentRoomId].north != -1){
            strcat(inquir, " [n]orth,");
            strcat(opt, "n");
        }
        if(rooms[currentRoomId].south != -1){
            strcat(inquir, " [s]outh,");
            strcat(opt, "s");
        }
        if(rooms[currentRoomId].east != -1){
            strcat(inquir, " [e]ast,");
            strcat(opt, "e");
        }
        if(rooms[currentRoomId].west != -1){
            strcat(inquir, " [w]est,");
            strcat(opt, "w");
        }
        strcat(inquir, "  [l]ook, [g]et, [i]nventory, [d]rop, [q]uit ]");
        strcat(opt, "qlgid");
        printf("%s\n>", inquir);

        char fw[20];
 
        scanf("%s", fw);
        char fc = fw[0];
        
        char nc = getchar();
        if (nc != '\n' && nc != '\0'){
            printf("You should enter single charecter or word based on the options\n\n");
            int dump;
            while ((dump = getchar()) != '\n' && dump != EOF);
        }
        if(strlen(fw) > 1 || strchr(opt, fc) != NULL){
            if(strlen(fw) > 1){
                fc = '\0';
            }
            if(strcmp(fw, "quit") == 0 || fc == 'q'){
                printf("Exiting game loop. Goodbye!\n");
                break;
            }else if(strcmp(fw, "north") == 0 || fc == 'n'){
                currentRoomId = rooms[currentRoomId].north;
            }else if(strcmp(fw, "south") == 0 || fc == 's'){
                currentRoomId = rooms[currentRoomId].south;
            }else if(strcmp(fw, "west") == 0 || fc == 'w'){
                currentRoomId = rooms[currentRoomId].west;
            }else if(strcmp(fw, "east") == 0 || fc == 'e'){
                currentRoomId = rooms[currentRoomId].east;
            }else if(strcmp(fw, "get") == 0 || fc == 'g'){
                invIdx++;
                inventory[invIdx] = rooms[currentRoomId].item;
                rooms[currentRoomId].item = -1;
                printf("You picked up a %s\n", items[inventory[invIdx]].name);
            }else if(strcmp(fw, "inventory") == 0 || fc == 'i'){
                if(invIdx == -1){
                    printf("You currently have nothing in your backpack\n");
                }else{
                    printf("Your backpack of infinite holding contains:\n");
                    for(int i = 0; i <= invIdx; i++){
                        printf("+ [%d] %s\n", inventory[i], items[inventory[i]].name);
                    }
                }
            }else if(strcmp(fw, "look") == 0 || fc == 'l'){
                if(rooms[currentRoomId].item != -1){
                printf("%s\n", items[rooms[currentRoomId].item].description);
                }else{
                    printf("No item in this room\n");
                }
            }else if(strcmp(fw, "drop") == 0 || fc == 'd'){
                printf("Your backpack of infinite holding contains:\n");
                    for(int i = 0; i <= invIdx; i++){
                        printf("+ [%d] %s\n", inventory[i], items[inventory[i]].name);
                    }
                    int val;
                    printf("Enter the item id of the thing to drop:");
                    scanf("%d", &val);
                    int dump1;
                    while ((dump1 = getchar()) != '\n' && dump1 != EOF);
                    int found = -1;
                    for(int i = 0; i <= invIdx; i++){
                        if(inventory[i] == val){
                            found = i;
                            rooms[currentRoomId].item = inventory[i];
                            inventory[i] = inventory[invIdx];
                            invIdx--;
                        }
                    }
                    if(found == -1){
                        printf("Item does not exist in backpack\n");
                    }else{
                        printf("new inventory size = %d\n", invIdx + 1);
                    }
            }
        }else{
            printf("invalid direction\n");
        }

    }
}