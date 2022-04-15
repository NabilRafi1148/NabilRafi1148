#include<stdio.h>
#include<stdlib.h>

const int hash_table_size = 11;

struct Node{
	int value;
} *head[hash_table_size];

int hash_function(int value){
	return value % hash_table_size;
}

void view(){
	puts("Hash Table :");
	for(int i=0; i<hash_table_size; i++){
		printf("Index %d : ", i);
		if(head[i] != NULL){
			printf("%d\n", head[i]->value);
		} else{
			puts("NULL");
		}
	}
	
}

int main(){
	
	int value_insert[11] = {51, 22, 33, 45, 81, 60, 63, 69, 60, 55, 21};
	
	for(int i=0; i<hash_table_size; i++){
		int index = hash_function(value_insert[i]);
		while(1 == 1){
		if(head[index] == NULL){
			Node *newNode = (struct Node *) malloc(sizeof(Node));
			newNode->value = value_insert[i];
			head[index] = newNode;
			break;
		} else{
			index++;
			if(index == hash_table_size){
				index = 0;
			}
		}
		}
	}
	
	view();
	
	return 0;
}
