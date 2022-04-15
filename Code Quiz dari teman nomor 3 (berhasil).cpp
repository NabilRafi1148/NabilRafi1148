#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Node{
	char name[100];
	char condition[10];
	Node *next, *prev;
} *head, *tail;

Node *create_node(char input_name[], char input_condition[]){
	Node* newNode = (struct Node *) malloc(sizeof(Node));
	strcpy(newNode->name, input_name);
	strcpy(newNode->condition, input_condition);
	newNode->next = newNode->prev = NULL;
	return newNode;
}

int get_priority(char condition[]){
	if(strcmpi(condition, "Critical") == 0){
		return 1;
	} else if(strcmpi(condition, "Serious") == 0){
		return 2;
	} else if(strcmpi(condition, "Fair") == 0 || strcmpi(condition, "Good") == 0 ){
		return 3;
	}
}

void push(struct Node *newNode){
	if(tail == NULL){
		head = newNode;
		tail = newNode;
	} else{
		Node *curr = tail;
		int node_priority = get_priority(newNode->condition);
		
		while(curr != NULL){
			if(get_priority(curr->condition) <= node_priority){
				if(curr == tail){
					tail->next = newNode;
					newNode->prev = tail;
					tail = newNode;
				} else{
					newNode->prev = curr;
					newNode->next = curr->next;
					curr->next->prev = newNode;
					curr->next =newNode;
				}
				return;
			}
			curr = curr->prev;
		}
		newNode->prev = NULL;
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
}

void pop(){
	if(strcmpi(head->condition, "Critical") == 0){
		printf("%s is in Emergency Room\n", head->name);
		if(head == tail){
			free(head);
			head = tail = NULL;
		} else{
			Node *curr = head;
			head = head->next;
			head->prev = NULL;
			curr->next =NULL;
			free(curr);
		}
	} else if(strcmpi(head->condition, "Serious") == 0){
		printf("%s is in Examination Room\n", head->name);
		if(head == tail){
			free(head);
			head = tail = NULL;
		} else{
			Node *curr = head;
			head = head->next;
			head->prev = NULL;
			curr->next =NULL;
			free(curr);
		}
	} else if(strcmpi(head->condition, "Fair") == 0 || strcmpi(head->condition, "Good") == 0){
		printf("%s is in Consultation Room\n", head->name);
		if(head == tail){
			free(head);
			head = tail = NULL;
		} else{
			Node *curr = head;
			head = head->next;
			head->prev = NULL;
			curr->next =NULL;
			free(curr);
		}
	}
}


void print(){
	Node *curr = head;
	printf("Waiting Room: ");
	if(curr == NULL){
		printf("None\n");
	} else{
	while(curr != NULL){
		if(curr->next == NULL){ //jika org terakhir di waiting list
			printf("%s\n", curr->name);
			return;
		}
		printf("%s, ", curr->name); // jika masih ada pasien lain
		curr = curr->next;
	}
	}
}

int main(){
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; i++){	
	
		char command[5], input_name[100], input_condition[10];
		scanf("%s", command); 
		if(strcmpi(command, "ADD") == 0){
			scanf("%s %[^\n]", input_name, input_condition); getchar();
			Node *newNode = create_node(input_name, input_condition);
			push(newNode);
		} else if(strcmpi(command, "CALL") == 0){
		//	getchar();
			pop();
		}
	
	
 }
   print();
	return 0;
}
