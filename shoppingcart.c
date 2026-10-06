#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max 50

struct node
{
    char name[max];
    int quantity;
    int cost;
    struct node *next;
};

//price function
int getPrice(char item[])
{
    if(strcmp(item, "Moisturiser") == 0)
        return 200;
    else if(strcmp(item, "Facecream") == 0)
        return 150;
    else if(strcmp(item, "Facewash") == 0)
        return 100;
    else if(strcmp(item, "Sunscreen") == 0)
        return 250;
    else
        return 0;
}

//display
void display(struct node *head)
{
    struct node *temp = head;
    int total = 0;

    printf("\n---------------------------------------------\n");
    printf("Name\t\tQty\tCost\tTotal\n");
    printf("---------------------------------------------\n");

    while(temp != NULL)
    {
        int item_total = temp->quantity * temp->cost;
        printf("%s\t\t%d\t%d\t%d\n",
               temp->name, temp->quantity, temp->cost, item_total);
        total += item_total;
        temp = temp->next;
    }

    printf("---------------------------------------------\n");
    printf("TOTAL COST = %d\n", total);
}

//helper to select item
int selectItem(struct node *nn)
{
    int choice;

    printf("\n1. Moisturiser (200)\n2. Facecream (150)\n3. Facewash (100)\n4. Sunscreen (250)\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    while(getchar() != '\n');

    switch(choice)
    {
        case 1: strcpy(nn->name, "Moisturiser"); break;
        case 2: strcpy(nn->name, "Facecream"); break;
        case 3: strcpy(nn->name, "Facewash"); break;
        case 4: strcpy(nn->name, "Sunscreen"); break;
        default:
            printf("Invalid choice\n");
            return 0;
    }

    nn->cost = getPrice(nn->name);
    return 1;
}

//DUPLICATE CHECK FUNCTION
int checkDuplicate(struct node *head, struct node *nn)
{
    struct node *temp = head;

    while(temp != NULL)
    {
        if(strcmp(temp->name, nn->name) == 0)
        {
            temp->quantity += nn->quantity;
            printf("Item already exists! Quantity updated.\n");
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

//delete item
struct node* deleteitem(struct node *head)
{
    char itm[max];
    struct node *cur = head, *prev = NULL;

    printf("Enter item name to delete: ");
    fgets(itm, sizeof(itm), stdin);
    itm[strcspn(itm, "\n")] = 0;

    while(cur != NULL && strcmp(cur->name, itm) != 0)
    {
        prev = cur;
        cur = cur->next;
    }

    if(cur == NULL)
    {
        printf("ITEM NOT FOUND\n");
        return head;
    }

    if(prev == NULL)
        head = cur->next;
    else
        prev->next = cur->next;

    free(cur);
    printf("Item deleted successfully\n");

    return head;
}

//change quantity
void changequantity(struct node *head)
{
    char data[max];
    struct node *temp = head;

    printf("Enter item name: ");
    fgets(data, sizeof(data), stdin);
    data[strcspn(data, "\n")] = 0;

    while(temp != NULL && strcmp(temp->name, data) != 0)
        temp = temp->next;

    if(temp == NULL)
    {
        printf("ITEM NOT FOUND\n");
        return;
    }

    printf("Enter new quantity: ");
    scanf("%d", &temp->quantity);
    while(getchar() != '\n');

    printf("Quantity updated\n");
}

//add items
struct node* additems(struct node *head)
{
    struct node *nn, *cur = head;

    nn = (struct node *)malloc(sizeof(struct node));
    nn->next = NULL;

    if(!selectItem(nn))
    {
        free(nn);
        return head;
    }

    printf("Enter quantity: ");
    scanf("%d", &nn->quantity);
    while(getchar() != '\n');

    if(head == NULL)
        return nn;

    //DUPLICATE CHECK HERE
    if(checkDuplicate(head, nn))
    {
        free(nn);
        return head;
    }

    while(cur->next != NULL)
        cur = cur->next;

    cur->next = nn;
    return head;
}

//checkout
void checkout(struct node *head)
{
    if(head == NULL)
    {
        printf("Cart is empty\n");
        return;
    }

    display(head);
    printf("\nOrder placed successfully!\n");
}

int main()
{
    struct node *head = NULL;
    int choice;

    do
    {
        printf("\n===== SHOPPING CART MENU =====\n");
        printf("1. Add Item\n");
        printf("2. Display Cart\n");
        printf("3. Delete Item\n");
        printf("4. Change Quantity\n");
        printf("5. Checkout\n");
        printf("Enter choice: ");

        scanf("%d", &choice);
        while(getchar() != '\n');

        switch(choice)
        {
            case 1:
                 head = additems(head);
                break;
            case 2:
                display(head);
                break;
            case 3:
                head = deleteitem(head);
                break;
            case 4:
                changequantity(head);
                break;
          }

    } while(choice != 5);
    checkout(head);
    return 0;
}
