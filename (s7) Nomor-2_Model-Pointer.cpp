#include<stdio.h>
#include<stdlib.h>

const int size = 6;

struct Node{
    int value;
} *head[size];

int hash_function(int value){
    return value % size;
}

int menu(){
    while(1 == 1){
        int choice;
        puts("1. Insert");
        puts("2. Delete");
        puts("3. Exit");
        printf(">> "); scanf("%d", &choice); getchar();

        if(choice >= 1 && choice <= 3){
            return choice;
        }
    }
}

void print(){
    for(int i=0; i<size; i++){
        printf("Index %d: ", i);
        if(head[i] != NULL){
            printf("%d\n", head[i]->value);
        }
        else{
            printf("NULL\n");
        }
    }
}

int main(){
    while(-1 == -1){
        print();
        int pilihan_user = menu();
        switch (pilihan_user){
            case 1:{ //insert
                int input;
                printf("Value untuk diinsert: "); scanf("%d", &input); getchar();
                int index = hash_function(input);
                for(int i=0; i<size; i++){
                    if(head[index] == NULL){
                        struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
                        new_node->value = input;
                        head[index] = new_node;
                        break;
                    }
                    else{
                        index++;
                        if(index == size){
                            index = 0;
                        }
                    }
                }
                break;
            }
            case 2:{ //delete
                int target_delete;
                printf("Value untuk didelete: "); scanf("%d", &target_delete); getchar();
                int index = hash_function(target_delete); //4
                int flag_deleted = 0;
                for(int i=0; i<size; i++){
                    if(head[index] != NULL){ //4
                        if(head[index]->value == target_delete){
                            free(head[index]);
                            head[index] = NULL;
                            flag_deleted = 1;
                            break;
                        }
                        else{
                            index++;
                            if(index == size){
                                index = 0;
                            }
                        }
                    }
                    else{
                        index++;
                        if(index == size){
                            index = 0;
                        }
                    }
                }
                if(flag_deleted == 0){
                    puts("Yang mau dihapus ga ada!");
                }
                else{
                    puts("Sukses dihapus!");
                }
                break;
            }
            case 3:{ //exit
                puts("Program Ended!");
                return 0;
            }
        }
    }
}

// [0] -> 
// [1] -> 
// [2] -> x
// [3] -> x
// [4] -> 
// [5] -> 
