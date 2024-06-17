#include <stdlib.h>
#include <ctype.h> // for isdigit() function

// Structure to represent a stack node
struct StackNode {
    int data;
    struct StackNode* next;
};

// Function to create a new stack node
struct StackNode* newNode(int data) {
    struct StackNode* stackNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}

// Function to check if the stack is empty
int isEmpty(struct StackNode* root) {
    return !root;
}

// Function to push an item to the stack
void push(struct StackNode** root, int data) {
    struct StackNode* stackNode = newNode(data);
    stackNode->next = *root;
    *root = stackNode;
}

// Function to pop an item from the stack
int pop(struct StackNode** root) {
    if (isEmpty(*root))
        return INT_MIN;
    struct StackNode* temp = *root;
    *root = (*root)->next;
    int popped = temp->data;
    free(temp);
    return popped;
}

// Function to return the top element of the stack without popping it
int peek(struct StackNode* root) {
    if (isEmpty(root))
        return INT_MIN;
    return root->data;
}

// Function to evaluate arithmetic expression
int evaluateExpression(char* exp) {
    struct StackNode* stack = NULL;

    for (int i = 0; exp[i]; ++i) {
        // If the scanned character is an operand (number), push it to the stack
        if (isdigit(exp[i]))
            push(&stack, exp[i] - '0');

        // If the scanned character is an operator, pop two elements from the stack, apply the operator, and push the result back
        else {
            int val1 = pop(&stack);
            int val2 = pop(&stack);
            switch (exp[i]) {
            case '+':
                push(&stack, val2 + val1);
                break;
            case '-':
                push(&stack, val2 - val1);
                break;
            case '*':
                push(&stack, val2 * val1);
                break;
            case '/':
                push(&stack, val2 / val1);
                break;
            }
        }
    }
    // The final result will be at the top of the stack
    return pop(&stack);
}

int main() {
    char exp[] = "231*+9-"; // Postfix expression: 2 + (3 * 1) - 9
    printf("Value of expression %s is %d\n", exp, evaluateExpression(exp));
    return 0;
}
