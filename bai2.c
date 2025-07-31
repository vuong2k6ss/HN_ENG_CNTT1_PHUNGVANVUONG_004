#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node {
    char title[100];
    char artist[100];
    float duration;
    struct Node* next;
}Node;


int main() {
    int choice;
    do {
        printf("MENU\n");
        printf("1. Them bai hat moi\n");
        printf("2. Hien thi danh sach bai hat theo ten\n");
        printf("3. Tim bai het theo ten\n");
        printf("4. Xoa bai hat\n");
        printf("5. Tinh tong thoi luong tat ca bai hat\n");
        printf("6. Thoat\n");
        printf("lua chon cua ban: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                printf("Thoat\n");
                return ;
            default:
                printf("lua chon khong hop le");
                return ;
        }
    }while (choice != 6);

    return 0;
}