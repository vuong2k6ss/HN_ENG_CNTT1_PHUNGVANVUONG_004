#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_COMMAND_LENGTH 100

typedef struct CommandNode {
    char command[MAX_COMMAND_LENGTH];
    struct CommandNode* next;
} CommandNode;

typedef struct {
    CommandNode* top;
} CommandStack;

void initStack(CommandStack* stack);
bool isEmpty(CommandStack* stack);
void push(CommandStack* stack, const char* command);
char* pop(CommandStack* stack);
void addCommand(CommandStack* executedStack, CommandStack* redoStack);
void undoCommand(CommandStack* executedStack, CommandStack* redoStack);
void redoCommand(CommandStack* executedStack, CommandStack* redoStack);
void viewCurrentCommand(CommandStack* executedStack);
void listExecutedCommands(CommandStack* executedStack);
void freeStack(CommandStack* stack);
void toUpperCase(char* str);
void displayMenu();

int main() {
    CommandStack executedStack, redoStack;
    initStack(&executedStack);
    initStack(&redoStack);
    int choice;
    char input[10];
    do {
        displayMenu();
        fgets(input, sizeof(input), stdin);
        choice = atoi(input);
        switch(choice) {
            case 1:
                addCommand(&executedStack, &redoStack);
                break;
            case 2:
                undoCommand(&executedStack, &redoStack);
                break;
            case 3:
                redoCommand(&executedStack, &redoStack);
                break;
            case 4:
                viewCurrentCommand(&executedStack);
                break;
            case 5:
                listExecutedCommands(&executedStack);
                break;
            case 6:
                clearHistory(&executedStack, &redoStack);
                break;
            case 7:
                printf("thoat chuong trinh...\n");
                break;
            default:
                printf("Lua chon khong hop le, chon lai.\n");
        }
    } while(choice != 7);
    freeStack(&executedStack);
    freeStack(&redoStack);
    return 0;
}

void displayMenu() {
    printf("\nMENU\n");
    printf("1. Them lenh moi\n");
    printf("2. Hoan tac lenh\n");
    printf("3. Phuc hoi lenh\n");
    printf("4. Xem lenh hien tai\n");
    printf("5. Danh sach lenh da thuc hien\n");
    printf("6. Lam moi lich su\n");
    printf("7. Thoat\n");
}


void initStack(CommandStack* stack) {
    stack->top = NULL;
}


bool isEmpty(CommandStack* stack) {
    return stack->top == NULL;
}


void push(CommandStack* stack, const char* command) {
    CommandNode* newNode = (CommandNode*)malloc(sizeof(CommandNode));
    if (newNode == NULL) {
        printf("Loi cap phat bo nho.\n");
        exit(EXIT_FAILURE);
    }

    strncpy(newNode->command, command, MAX_COMMAND_LENGTH - 1);
    newNode->command[MAX_COMMAND_LENGTH - 1] = '\0';
    newNode->next = stack->top;
    stack->top = newNode;
}

char* pop(CommandStack* stack) {
    if (isEmpty(stack)) {
        return NULL;
    }
    CommandNode* temp = stack->top;
    char* command = (char*)malloc(MAX_COMMAND_LENGTH * sizeof(char));
    if (command == NULL) {
        printf("Loi cap phat bo nho.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(command, temp->command);
    stack->top = temp->next;
    free(temp);

    return command;
}


void addCommand(CommandStack* executedStack, CommandStack* redoStack) {
    char command[MAX_COMMAND_LENGTH];
    printf("Nhap lenh: ");
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = '\0';
    if (strlen(command) == 0) {
        printf("Lenh khong duoc trong.\n");
        return;
    }
    toUpperCase(command);
    push(executedStack, command);
    freeStack(redoStack);
    initStack(redoStack);
    printf("them lenh thanh cong: %s\n", command);
}

void undoCommand(CommandStack* executedStack, CommandStack* redoStack) {
    if (isEmpty(executedStack)) {
        printf("Khong co lenh nao de hoan tac.\n");
        return;
    }
    char* command = pop(executedStack);
    push(redoStack, command);
    free(command);
    printf("Hoan tac lenh.\n");
    if (!isEmpty(executedStack)) {
        printf("Lenh hien tai: %s\n", executedStack->top->command);
    } else {
        printf("Khong con lenh nao trong lich su\n");
    }
}

void redoCommand(CommandStack* executedStack, CommandStack* redoStack) {
    if (isEmpty(redoStack)) {
        printf("Khong co lenh nao phuc hoi.\n");
        return;
    }
    char* command = pop(redoStack);
    push(executedStack, command);
    free(command);
    printf("Đa phuc hoi lenh: %s\n", executedStack->top->command);
}

void viewCurrentCommand(CommandStack* executedStack) {
    if (isEmpty(executedStack)) {
        printf("Khong co lenh nao duoc lam.\n");
        return;
    }
    printf("Lenh hien tai %s\n", executedStack->top->command);
}


void listExecutedCommands(CommandStack* executedStack) {
    if (isEmpty(executedStack)) {
        printf("Khong co lenh nao thuc thi\n");
        return;
    }
    printf("Danh sach lenh da thuc hien:\n");
    CommandNode* current = executedStack->top;
    int count = 1;
    while (current != NULL) {
        printf("%d. %s\n", count++, current->command);
        current = current->next;
    }
}


void freeStack(CommandStack* stack) {
    while (!isEmpty(stack)) {
        CommandNode* temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }
}

void toUpperCase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}