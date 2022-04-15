#include<stdio.h>
#include<stdlib.h>

struct Node{
    int value;
    struct Node *left, *right;
};

void search(struct Node *root, int target){
    //Code Here
    if(root == NULL){
        printf("%d is not found\n", target);
        return;
    }
    else{
        if(root->value == target){
            printf("%d is found\n", target);
            return;
        }
        else if(root->value > target){
            search(root->left, target);
        }
        else if(root->value < target){
            search(root->right, target);
        }
    }
}

int get_minimum_value(struct Node *root){
    //Code Here
    struct Node *min_node = root;
    while(min_node->left != NULL){
        min_node = min_node->left;
    }
    return min_node->value;
}

int get_maximum_value(struct Node *root){
    //Code Here
    struct Node *max_node = root;
    while(max_node->right != NULL){
        max_node = max_node->right;
    }
    return max_node->value;
}

int get_node_amount(struct Node *root){
    //Code Here
    int sum = 0;
    if(root != NULL){
        int left = get_node_amount(root->left);
        int right = get_node_amount(root->right);
        sum += 1 + left + right;
    }
    return sum;
}

int get_tree_height(struct Node *root){
    //Code Here
    if(root == NULL){
        return 0;
    }
    int level = 1;
    int left_height = get_tree_height(root->left);
    int right_height = get_tree_height(root->right);

    if(left_height > right_height){
        level += left_height;
    }
    else{
        level += right_height;
    }

    return level;
}

struct Node *createNode(struct Node *root, int value){
    //Code Here
    struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
    new_node->value = value;
    new_node->left = new_node->right = NULL;
    return new_node;
}

struct Node *insert_node(struct Node *root, struct Node *new_node){
    //Code Here
    if(root == NULL){
        root = new_node;
    }
    else{
        if(root->value < new_node->value){ //right child
            root->right = insert_node(root->right, new_node);
        }
        else if(new_node->value <= root->value){ //left child (tree left descendants will more often inserted than right descendants)
            root->left = insert_node(root->left, new_node);
        }
    }
    return root;
}

struct Node *find_predecessor(struct Node *root){
    //Code Here
    struct Node *predecessor = (root)->left;
    while(predecessor->right != NULL){
        predecessor = predecessor->right;
    }
    return predecessor;
}

struct Node *find_successor(struct Node *root){
    //Code Here
    struct Node *successor = (root)->right;
    while(successor->left != NULL){
        successor = successor->left;
    }
    return successor;
}

struct Node *delete_node(struct Node *root, int target){
    //Code Here
    if(root != NULL){
        if(root->value < target){
            root->right = delete_node(root->right, target);
        }
        else if(target < root->value){
            root->left = delete_node(root->left, target);
        }
        else if(target == root->value){ //target found
            if(root->left == NULL && root->right == NULL){
                free(root);
                root = NULL;
            }
            else if(root->left != NULL){ //tree left descendants will more often deleted than right descendants
                struct Node *predecessor = find_predecessor(root);
                root->value = predecessor->value;
                root->left = delete_node(root->left, predecessor->value);
            }
            else if(root->right != NULL){
                struct Node *successor = find_successor(root);
                root->value = successor->value;
                root->right = delete_node(root->right, successor->value);
            }
        }
    }
    return root;
}

void preorder_print(struct Node *root){
    //Code Here
    if(root != NULL){
        printf("%d ", root->value);
        preorder_print(root->left);
        preorder_print(root->right);
    }
}

void inorder_print(struct Node *root){
    //Code Here
    if(root != NULL){
        inorder_print(root->left);
        printf("%d ", root->value);
        inorder_print(root->right);
    }
}

void postorder_print(struct Node *root){
    //Code Here
    if(root != NULL){
        postorder_print(root->left);
        postorder_print(root->right);
        printf("%d ", root->value);
    }
}

struct Node *delete_all_node(struct Node *root){
    //Code Here
    if(root != NULL){
        root->left = delete_all_node(root->left);
        root->right = delete_all_node(root->right);
        free(root);
        root = NULL;
    }
    return root;
}

void menu(int *choice){
    system("CLS || clear");
    puts("1. Insert Node");
    puts("2. Delete Node");
    puts("3. Delete All Nodes");
    puts("4. Print Tree");
    puts("5. Search Node");
    puts("6. Get Tree Info");
    do{
        printf(">> "); scanf("%d", choice); getchar();
    }while((*choice) < 1 || (*choice) > 6);
}

void print_tree(struct Node *root){
    printf("Pre-Order: "); preorder_print(root); puts("");
    printf("In-Order: "); inorder_print(root); puts("");
    printf("Post-Order: "); postorder_print(root); puts("");
}

int main(){
    int choice, value;
    struct Node *root = NULL;

    int init_tree[12] = {5, 2, 4, 8, 9, 10, 7, 6, 1, -1, 0, 100};
    for(int i=0; i<12; i++){
        root = insert_node(root, createNode(root, init_tree[i]));
    }

    for(;;){
        menu(&choice);
        if(choice == 1){
            print_tree(root); puts("");
            printf("Insert Value: "); scanf("%d", &value); getchar();
            root = insert_node(root, createNode(root, value));
        }
        else if(choice == 2){
            print_tree(root); puts("");
            printf("Delete Value: "); scanf("%d", &value); getchar();
            root = delete_node(root, value);
        }
        else if(choice == 3){
            root = delete_all_node(root);
        }
        else if(choice == 4){
            print_tree(root);
            printf("Click Enter to Continue.."); getchar();
        }
        else if(choice == 5){
            printf("Search Value: "); scanf("%d", &value); getchar();
            search(root, value);
            printf("Click Enter to Continue.."); getchar();
        }
        else if(choice == 6){
            printf("Minimum Value: %d\n", get_minimum_value(root));
            printf("Maximum Value: %d\n", get_maximum_value(root));
            printf("Node Amount: %d\n", get_node_amount(root));
            printf("Tree Height: %d\n", get_tree_height(root));
            printf("\nClick Enter to Continue.."); getchar();
        }
    }
    return 0;
}