#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Person{
    char name[100+1];
    char status[10+1];
    struct Person *previous, *next;
} *head, *tail;

struct Person *createNode(char inputted_name[], char inputted_status[]){
    struct Person *node = (struct Person *) malloc(sizeof(struct Person));
    strcpy(node->name, inputted_name);
    sprintf(node->status, inputted_status); //sama aja kaya strcpy (buat copy)
    // strcpy(node->status, inputted_status); //juga bisa (sama aja)
    node->previous = node->next = NULL;
    return node;
}

int get_priority(char status[]){
    if(strcmpi(status, "VIP") == 0){
        return 1;
    }
    else if(strcmpi(status, "Member") == 0){
        return 2;
    }
    else if(strcmpi(status, "Guest") == 0){
        return 3;
    }
}

void push(struct Person *node){
    if(tail == NULL){
        head = tail = node;
    }
    else{
        struct Person *inspectur = tail;
        int node_priority = get_priority(node->status);

        while(inspectur != NULL){
            if(get_priority(inspectur->status) <= node_priority){
                if(inspectur == tail){
                    tail->next = node;
                    node->previous = tail;
                    tail = node;
                }
                else{
                    node->previous = inspectur;
                    node->next = inspectur->next;
                    inspectur->next->previous = node;
                    inspectur->next = node;
                }
                return;
            }
            inspectur = inspectur->previous;
        }
        node->previous = NULL;
        node->next = head;
        head->previous = node;
        head = node;
    }
}

void pop(){
    if(head == NULL){
        printf("There's no person in waiting room!\n");
        printf("ENTER.."); getchar();
    }
    else{
        printf("%s %s is called from waiting room!\n", head->status, head->name);
        printf("ENTER.."); getchar();
        if(head == tail){
            free(head);
            head = tail = NULL;
        }
        else{
            struct Person *inspectur = head;
            head = head->next;
            inspectur->next = NULL;
            head->previous = NULL;
            free(inspectur);
        }
    }
}

void print(){
    struct Person *inspectur = head;
    int count = 1;
    while(inspectur != NULL){
        printf("%d) [%s] %s\n", count, inspectur->status, inspectur->name);
        count++;
        inspectur = inspectur->next;
    }
}

int main(){
    while(0 == 0){
        system("CLS || clear");
        char command[5+1], name[100+1], status[10+1];
        print();
        printf("ADD || CALL: "); scanf("%s", command);
        if(strcmpi(command, "ADD") == 0){
            scanf(" %s %[^\n]", status, name); getchar();
            struct Person *new_person = createNode(name, status);
            push(new_person);
        }
        else if(strcmpi(command, "CALL") == 0){
            getchar();
            pop();
        }
    }
    return 0;
}

//kurang panjang nama di soal