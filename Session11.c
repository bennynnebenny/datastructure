#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int precedence(char c)
{

    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

void infixToPostfix(char *infix)
{
    int len = strlen(infix);
    char result[len + 1];
    char stack[len];
    int j = 0;
    int top = -1;

    for (int i = 0; i < len; i++)
    {
        char c = infix[i];

        if (isalnum(c))
            result[j++] = c;

        else if (c == '(')
            stack[++top] = '(';

        else if (c == ')')
        {
            while (top != -1 && stack[top] != '(')
            {
                result[j++] = stack[top--];
            }
            top--;
        }

        else
        {
            while (top != -1 && (precedence(c) < precedence(stack[top]) ||
                                 precedence(c) == precedence(stack[top])))
            {
                result[j++] = stack[top--];
            }
            stack[++top] = c;
        }
    }

    while (top != -1)
    {
        result[j++] = stack[top--];
    }

    result[j] = '\0';
    printf("%s\n", result);
}

int isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

void postfixToInfix(char *postfix)
{
    char stack[100][100];
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; i++)
    {
        char c = postfix[i];

        if (isalnum(c))
        {
            char temp[2] = {c, '\0'};
            strcpy(stack[++top], temp);
        }
        else if (isOperator(c))
        {
            if (top < 1)
            {
                printf("Invalid postfix expression\n");
                return;
            }

            char op2[100], op1[100], expr[100];
            strcpy(op2, stack[top--]);
            strcpy(op1, stack[top--]);

            printf(expr, "%s%c%s", op1, c, op2);
            strcpy(stack[++top], expr);
        }
    }

    if (top != 0)
    {
        printf("Invalid postfix expression\n");
        return;
    }

    printf("Infix: %s\n", stack[top]);
}

int main()
{
    int choice;
    printf("Operation Available :\n1. Infix to postfix\n2. Postfix to Infix\n>> ");
    scanf("%d", &choice);
    getchar();

    if (choice == 1)
    {
        char infix[100];
        printf("Input Infix : ");
        scanf("%[^\n]", infix);
        getchar();
        infixToPostfix(infix);
    }
    else if (choice == 2)
    {
        char postfix[100];
        printf("Input Postfix: ");
        scanf("%[^\n]", postfix);
        getchar();
        postfixToInfix(postfix);
    }
    else
    {
        printf("Please input the correct choice!\n\n");
        main();
    }

    return 0;
}
