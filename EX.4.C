int stack[100],i,j,choice=0,n,top=-1;  
void push();  
void pop();  
void show();  
void main ()  
{  
     
    printf("Enter the number of elements in the stack ");  
    scanf("%d",&n);  
    printf("Stack operations using array");  
 
printf("\n----------------------------------------------\n");  
    while(choice != 4)  
    {  
        printf("Chose one from the below options...\n");  
        printf("\n1.Push\n2.Pop\n3.Show\n4.Exit");  
        printf("\n Enter your choice \n");        
        scanf("%d",&choice);  
        switch(choice)  
        {  
            case 1:  
            {  
                push();  
                break;  
            }  
            case 2:  
            {  
                pop();  
                break;  
            }  
            case 3:  
            {  
                show();  
                break;  
            }  
            case 4:  
            {  
                printf("Exiting....");  
                break;  
            }  
            default:  
            {  
                printf("Please Enter valid choice ");  
            }  
        };  
    }  
}  
 
void push ()  
{  
    int val;      
    if (top == n )  
    printf("\n Overflow");  
    else  
    {  
        printf("Enter the value?");  
        scanf("%d",&val);        
        top = top +1;  
        stack[top] = val;  
    }  
}  
 
void pop ()  
{  
    if(top == -1)  
    printf("Underflow");  
    else  
    top = top -1;  
}  
void show()  
{  
    for (i=top;i>=0;i--)  
    {  
        printf("%d\n",stack[i]);  
    }  
    if(top == -1)  
    {  
        printf("Stack is empty");  
    }  
}
USING LINKED LIST 
#include<stdio.h>
#include<stdlib.h>
void pop();
void push(int value);
void display();
void makenull();
struct node
{
int data;
struct node *link;
};
struct node *top=NULL,*temp;
void main()
{
int choice,data;
while(1) //infinite loop is used to insert/delete infinite number of elements in stack
{
printf("\n1.Push\n2.Pop\n3.Display\n4.Makenull\n5.Exit\n");
printf("\nEnter ur choice:");
scanf("%d",&choice);
switch(choice)
{
case 1: //To push a new element into stack
printf("Enter a new element :");
scanf("%d",&data);
push(data);
break;
case 2: // pop the element from stack
pop();
break;
case 3: // Display the stack elements
display();
break;
case 4:
makenull();
break;
case 5: // To exit
exit(0);
}
}
getch();
}
void makenull()
{
while(top!=NULL)
{
pop();
printf("\n");
}
}
void display()
{
temp=top;
if(temp==NULL)
{
printf("\nStack is empty\n");
return;
}
printf("\n The Contents of the Stack are...");
while(temp!=NULL)
{
printf(" %d ->",temp->data);
temp=temp->link;
}
}
void push(int data)
{
temp=(struct node *)malloc(sizeof(struct node)); // creating a space for the new element.
temp->data=data;
temp->link=top;
top=temp;
display();
}
void pop()
{
if(top!=NULL)
{
printf("The poped element is %d",top->data);
top=top->link;
}
else
{
printf("\nStack Underflow");
}
display();
}
