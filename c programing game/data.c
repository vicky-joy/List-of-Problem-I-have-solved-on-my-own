#include "data.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int get_int_value(char * ptr);
char *get_string_value(char *ptr);
/** Add code for .c here **/
int find_max(char *filename){
    FILE *fle = fopen(filename, "r");
    if(fle == NULL){
        printf("Something wrong with opening file");
        return -1;
    }
    char line[50];
    int largest_id = 0;
    while(fgets(line, 50, fle) != NULL){
        char * id_ptr;
        int id;
        if((id_ptr = strstr(line, "\"id\"")) != NULL){
            id_ptr += 5;

            id = (int)strtol(id_ptr, NULL, 10);
            if(id > largest_id){
                largest_id = id;
            }
        }
    }
    fclose(fle);
    return largest_id;
}


int get_int_value(char * ptr){
    while(*ptr == ' '){
        ptr++;
    }
    int value = (int)strtol(ptr, NULL, 10);
    if(*ptr == 'n'){
        return -1;
    }
    return value;
}
char *get_string_value(char *ptr){
    char *st = strchr(ptr, '"');
    st++;
    char *ed = strchr(st, '"');
    *ed = '\0';
    char * value = strdup(st);
    *ed = '"';

    return value;
}
Item * load_json_items(char * filename, int itemMaxId){
    Item *items_list = malloc((itemMaxId + 1) * sizeof(struct Item));
    for(int i = 0; i <= itemMaxId; i++){
        items_list[i].id = -1;
        items_list[i].name = NULL;
        items_list[i].description = NULL;
    }
    FILE *fle = fopen(filename, "r");
    if(fle == NULL){
        printf("Something wrong with opening file");
        return NULL;
    }
    char line[256];
    int current_index = 0;
    while(fgets(line, 256, fle) != NULL){
        char * ptr;
        if((ptr = strstr(line, "\"id\"")) != NULL){
            ptr += 5;
            current_index = get_int_value(ptr);
           items_list[current_index].id = current_index;
        }else if((ptr = strstr(line, "\"name\"")) != NULL){
            ptr += 6;
           items_list[current_index].name = get_string_value(ptr);
        } else if((ptr = strstr(line, "\"description\"")) != NULL){
            ptr += 13;
           items_list[current_index].description = get_string_value(ptr);
        }
    }
    fclose(fle);


    return items_list;
}

Room *load_json_rooms(char * filename, int roomMaxId){
    Room *rooms_list = malloc((roomMaxId + 1) * sizeof(struct Room));
    for(int i = 0; i <= roomMaxId; i++){
        rooms_list[i].id = -1;
        rooms_list[i].name = NULL;
        rooms_list[i].description = NULL;
        rooms_list[i].north = -1;
        rooms_list[i].south = -1;
        rooms_list[i].west = -1;
        rooms_list[i].east = -1;
        rooms_list[i].item = -1;
        rooms_list[i].starting = 0;
    }
    FILE *fle = fopen(filename, "r");
    if(fle == NULL){
        printf("Something wrong with opening file");
        return NULL;
    }
    char line[1024];
    int current_index = 0;
    while(fgets(line, 1024, fle) != NULL){
        char * ptr;
        if((ptr = strstr(line, "\"id\"")) != NULL){
            ptr += 5;
            current_index = get_int_value(ptr);
           rooms_list[current_index].id = current_index;
        }else if((ptr = strstr(line, "\"name\"")) != NULL){
            ptr += 6;
           rooms_list[current_index].name = get_string_value(ptr);
        } else if((ptr = strstr(line, "\"description\"")) != NULL){
            ptr += 13;
           rooms_list[current_index].description = get_string_value(ptr);
        }else if((ptr = strstr(line, "\"south\"")) != NULL){
            ptr += 8;
           rooms_list[current_index].south = get_int_value(ptr);
        }else if((ptr = strstr(line, "\"north\"")) != NULL){
            ptr += 8;
           rooms_list[current_index].north = get_int_value(ptr);
        }else if((ptr = strstr(line, "\"east\"")) != NULL){
            ptr += 7;
           rooms_list[current_index].east = get_int_value(ptr);
        }else if((ptr = strstr(line, "\"west\"")) != NULL){
            ptr += 7;
           rooms_list[current_index].west = get_int_value(ptr);
        }else if((ptr = strstr(line, "\"item\"")) != NULL){
            ptr += 7 ;
           rooms_list[current_index].item = get_int_value(ptr);
        }else if((ptr = strstr(line, "\"starting\"")) != NULL){
            ptr += 11;
            if(strstr(ptr, "true") != NULL){
                rooms_list[current_index].starting = 1;
            }
        }
    }
    fclose(fle);


    return rooms_list;
}
//pc eof 285 data
