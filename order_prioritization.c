#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent an order
struct Order {
    int orderID;
    char dishName[50];
    int cookingTime;
    char status[20];
};

// Structure to represent a node in the priority queue
struct Node {
    struct Order data;
    struct Node* next;
};

// Priority Queue functions
struct Node* front = NULL;

// Function to insert an order into the priority queue based on cooking time
void push(struct Order newOrder) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = newOrder;
    newNode->next = NULL;

    if (front == NULL || newOrder.cookingTime < front->data.cookingTime) {
        newNode->next = front;
        front = newNode;
    } else {
        struct Node* temp = front;
        while (temp->next != NULL && temp->next->data.cookingTime <= newOrder.cookingTime) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

// Function to process and remove the highest priority order
void pop() {
    if (front == NULL) {
        printf("No orders to process.\n");
    } else {
        printf("Processing Order ID: %d, Dish: %s, Cooking Time: %d minutes\n",
               front->data.orderID, front->data.dishName, front->data.cookingTime);
        front = front->next;
    }
}

int main() {
    int orderID = 1;
    int addAnotherOrder = 1;

    while (addAnotherOrder) {
        struct Order newOrder;
        newOrder.orderID = orderID++;
        printf("Enter Dish Name: ");
        scanf("%s", newOrder.dishName);
        printf("Enter Cooking Time (in minutes): ");
        scanf("%d", &newOrder.cookingTime);
        strcpy(newOrder.status, "pending");

        push(newOrder);

        printf("Do you want to add another order? (1 for Yes, 0 for No): ");
        scanf("%d", &addAnotherOrder);
    }

    printf("Processing Orders:\n");
    while (front != NULL) {
        pop();
    }

    return 0;
}
