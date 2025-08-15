#include <stdio.h>
#include <stdbool.h>
#include <conio.h>

int main()
{
    // Values
    // grocery list
    // 5 categories, 10 items each
    char grocery[5][11][20] = {
        {"Vegetables", "Corn", "Mushroom", "Broccoli", "Capsicum", "Carrot", "Tomato", "Cabbage", "Lettuce", "Potato", "Cucumber"},
        {"Fruits", "Apple", "Avocado", "Banana", "Grape", "Kiwi", "Mango", "blueberry", "Raspberry", "Strawberry", "Watermelon"},
        {"Beverages", "Beer", "Root Beer", "Tea", "Yogurt", "Milk", "Wine", "Cola", "Soda", "Coffee", "Water"},
        {"Garnishes", "Pepper", "Sugar", "Ketchup", "Cook oil", "Fish sauce", "Salt", "Cinnamon", "Chili sauce", "Honey", "Mint"},
        {"Snacks", "Cookie", "Roll cake", "Cupcake", "Macaron", "Pie", "Jello", "Donut", "Popsicle", "Brownie", "Ice cream"}};

    // price list
    // 5 categories, 10 items each
    float price[5][11] = {
        {1.0f, 1.0f, 8.60f, 1.63f, 1.06f, 5.30f, 1.38f, 7.0f, 1.16f, 1.46f, 3.15f},
        {2.0f, 1.11f, 1.68f, 0.75f, 1.00f, 5.5f, 2.19f, 7.5f, 19.92f, 5.24f, 8.78f},
        {3.0f, 3.84f, 2.50f, 2.39, 4.98, 3.46f, 5.97f, 1.97f, 1.97f, 4.97f, 1.47f},
        {4.0f, 1.97f, 1.97f, 2.97f, 7.97f, 2.98f, 1.17f, 1.97f, 3.67f, 4.97f, 1.67f},
        {5.0f, 3.97f, 3.77f, 3.47f, 7.98f, 6.01f, 2.00f, 3.00f, 4.78f, 2.78f, 3.97f}};

    // Variables
    float pay = 0, change = 0;
    float total = 0.0f, total_with_tax = 0.0f;
    float tax_rate = 0.08f;

    // Shopping list
    // 1000 items, each with 3 attributes: category, item, quantity
    int shopList[1000][3];

    int i, amount, listCurrent = 0;
    int ansType, ansItem;
    char ansDone;

    // Loop select
    printf("\t\t  !Welcome to our shop!\n");
    bool passA = true;
    while (passA)
    {
        bool passM = true;
        while (passM)
        {
            printf("==============================================================\n");
            printf("Please choose which category of grocery would you like to buy:");
            // print grocery list
            for (i = 1; i <= 5; i++)
            {
                printf("\n[%d] %s", i, grocery[i - 1][0]);
            }
            printf("\n==============================================================\n");
            // Select grocery
            bool passB = true;
            while (passB) // check select grocery information
            {
                printf("○ Your select Grocery: ");
                scanf("%d", &ansType);
                if (ansType >= 1 && ansType <= 5)
                {
                    passB = false;
                }
                else
                {
                    printf("\n= Not a valid choice, please re-enter =\n");
                }
            }
            // Select item
            system("cls");
            printf("\n**************************************************************\n");
            printf("Here is a list of items marked as %s:", grocery[ansType - 1][0]);

            // Print item list
            for (i = 1; i <= 10; i++)
            {
                printf("\n[%d] %s ($%.2f)", i, grocery[ansType - 1][i], price[ansType - 1][i]);
            }
            printf("\n[0] back to Grocery");
            printf("\n**************************************************************\n");

            // confirm select
            bool passC = true; // check items select information
            char ansSure;
            while (passC)
            {
                bool passD = true; // check items number or out
                while (passD)
                {
                    printf("○ Your select Item: ");
                    scanf("%d", &ansItem);
                    if (ansItem >= 1 && ansItem <= 10)
                    {
                        passD = false;
                    }
                    else if (ansItem == 0)
                    {
                        passD = false;
                        passC = false;
                        system("cls");
                    }
                    else
                    {
                        printf("\n= Not a valid choice, please re-enter =\n");
                    }
                }
                if (passC)
                {
                    printf("\nAre you sure to select %s?(y/n) :", grocery[ansType - 1][ansItem]); /*check items select information*/
                    scanf(" %c", &ansSure);
                    if (ansSure == 'y' || ansSure == 'Y')
                    {
                        passC = false;
                        passM = false;
                    }
                    else if (ansSure != 'n' && ansSure != 'N')
                    {
                        printf("\n= Not a valid choice, please re-enter =\n");
                    }
                }
            }
        }

        // how many?
        printf("\nHow much you would like to buy?");
        bool passN = true;
        while (passN)
        {
            printf("\n○ How many pieces: ");
            scanf("%d", &amount);
            if (amount <= 0)
            {
                printf("\n= Not a valid choice, please re-enter =\n");
            }
            else
            {
                passN = false;
            }
        }

        system("cls");

        // Calculate total price
        total += price[ansType - 1][ansItem] * (float)amount;
        total_with_tax = total * (1.0f + tax_rate);

        // Add to shopping list
        shopList[listCurrent][0] = ansType - 1;
        shopList[listCurrent][1] = ansItem;
        shopList[listCurrent][2] = amount;
        listCurrent++;

        printf("\n++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("Added %s to the shopping list. \nYour total is now $%.2f (+$%.2f Tax)",
               grocery[ansType - 1][ansItem],
               total_with_tax,
               total * tax_rate);
        printf("\n++++++++++++++++++++++++++++++++++++++++++++++++\n");

        // printf shoplist
        printf("\nYour purchases: \n");
        for (i = 1; i <= listCurrent; i++)
        {
            printf("[%d] %s ($%.2f)  x%d\n", i, grocery[shopList[i - 1][0]][shopList[i - 1][1]], price[shopList[i - 1][0]][shopList[i - 1][1]] * (float)amount * (1.0f + tax_rate), amount);
        }

        // Buy more?
        bool passE = true;
        while (passE)
        {
            printf("Would you like to purchase another item? (y/n)");
            printf("\nYour Answer: ");
            scanf(" %c", &ansDone);
            if (ansDone == 'n' || ansDone == 'N') /*Check answer done*/
            {
                passE = false;
                passA = false;
                system("cls");
            }
            else if (ansDone == 'y' || ansDone == 'Y')
            {
                passE = false;
                system("cls");
            }
            else
            {
                printf("\n= Not a valid choice, please re-enter =\n");
            }
        }
    }

    // end
    printf("How much will you pay?");
    bool passp = true;
    while (passp)
    {
        printf("\nYour total is $%.2f (+$%.2f Tax).", 
            total * (1.0f + tax_rate), 
            total * tax_rate);
        printf("\nYour money : ");
        scanf("%f", &pay);
        if (pay < total)
        {
            printf("\n\nNot enough money, please enter again");
        }
        else if (pay > total)
        {
            change = pay - total;
            passp = false;
            system("cls");
        }
    }

    printf("\n\n################################################################\n");
    printf("\nYour purchases: \n");
    // printf shoplist
    for (i = 1; i <= listCurrent; i++)
    {
        printf("[%d] %s ($%.2f)  x%d\n", i, grocery[shopList[i - 1][0]][shopList[i - 1][1]], price[shopList[i - 1][0]][shopList[i - 1][1]] * (float)amount, amount);
    }
    printf("\nThank you for our purchase! \nYour total is $%.2f (+$%.2f Tax). \nYour Change is $%.2f .", total * (1.0f + tax_rate), total * (1.0f + tax_rate), change);

    return 0;
}
