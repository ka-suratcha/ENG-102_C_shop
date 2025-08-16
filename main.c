#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* Helper: clear the rest of the current input line */
static void clear_line(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    { /* discard */
    }
}

int main(void)
{
    /* ====== Data ====== */
    // 5 categories, 10 items each
    const char grocery[5][11][20] = {
        {"Vegetables", "Corn", "Mushroom", "Broccoli", "Capsicum", "Carrot", "Tomato", "Cabbage", "Lettuce", "Potato", "Cucumber"},
        {"Fruits", "Apple", "Avocado", "Banana", "Grape", "Kiwi", "Mango", "Blueberry", "Raspberry", "Strawberry", "Watermelon"},
        {"Beverages", "Beer", "Root Beer", "Tea", "Yogurt", "Milk", "Wine", "Cola", "Soda", "Coffee", "Water"},
        {"Garnishes", "Pepper", "Sugar", "Ketchup", "Cook oil", "Fish sauce", "Salt", "Cinnamon", "Chili sauce", "Honey", "Mint"},
        {"Snacks", "Cookie", "Roll cake", "Cupcake", "Macaron", "Pie", "Jello", "Donut", "Popsicle", "Brownie", "Ice cream"}};

    const float price[5][11] = {
        {0.0f, 8.60f, 1.63f, 1.06f, 5.30f, 1.38f, 7.00f, 1.16f, 1.46f, 3.15f, 2.50f},  // Vegetables
        {0.0f, 1.11f, 1.68f, 0.75f, 1.00f, 5.50f, 2.19f, 7.50f, 19.92f, 5.24f, 8.78f}, // Fruits
        {0.0f, 3.84f, 2.50f, 2.39f, 4.98f, 3.46f, 5.97f, 1.97f, 1.97f, 4.97f, 1.47f},  // Beverages
        {0.0f, 1.97f, 1.97f, 2.97f, 7.97f, 2.98f, 1.17f, 1.97f, 3.67f, 4.97f, 1.67f},  // Garnishes
        {0.0f, 3.97f, 3.77f, 3.47f, 7.98f, 6.01f, 2.00f, 3.00f, 4.78f, 2.78f, 3.97f}   // Snacks
    };

    const float TAX_RATE = 0.08f;

    /* Shopping list: up to 1000 lines: category, item, qty */
    int shopList[1000][3];
    int listCount = 0;

    /* Totals */
    float subtotal = 0.0f;

    printf("\t\t! Welcome to our shop !\n");

    bool continueShopping = true;
    while (continueShopping)
    {

        /* === Choose Category 1..5 === */
        int ansType = 0;
        while (1)
        {
            printf("\n==============================================================\n");
            printf("Please choose which category of grocery you would like to buy:");
            for (int i = 1; i <= 5; i++)
            {
                printf("\n[%d] %s", i, grocery[i - 1][0]);
            }
            printf("\n==============================================================\n");
            printf("> Your selected Grocery (1-5): ");

            if (scanf("%d", &ansType) != 1)
            {
                clear_line();
                system("cls");
                printf("\nX Not a valid choice, please re-enter");
                continue;
            }
            clear_line();
            if (ansType >= 1 && ansType <= 5)
                break;
            system("cls");
            printf("\nX Not a valid choice, please re-enter");
        }
        system("cls");

        /* === Choose Item 1..10 or 0 back === */
        int ansItem = -1;
        while (1)
        {
            printf("\n**************************************************************\n");
            printf("Items in %s:", grocery[ansType - 1][0]);
            for (int i = 1; i <= 10; i++)
            {
                printf("\n[%d] %s ($%.2f)", i, grocery[ansType - 1][i], price[ansType - 1][i]);
            }
            printf("\n[0] Back to grocery categories");
            printf("\n**************************************************************\n");
            printf("> Your selected Item (0-10): ");

            if (scanf("%d", &ansItem) != 1)
            {
                clear_line();
                system("cls");
                printf("\nX Not a valid choice, please re-enter");
                continue;
            }
            clear_line();

            if (ansItem == 0)
            { /* go back to categories */
                system("cls");
                goto continue_outer_loop; /* restart outer while */
            }
            if (ansItem >= 1 && ansItem <= 10)
            {
                /* Confirm item */
                char ansSure = 0;
                printf("Are you sure to select %s? (y/n): ", grocery[ansType - 1][ansItem]);
                if (scanf(" %c", &ansSure) != 1)
                {
                    clear_line();
                    system("cls");
                    printf("\nX Not a valid choice, please re-enter");
                    continue;
                }
                clear_line();
                if (ansSure == 'y' || ansSure == 'Y')
                    break;
                if (ansSure == 'n' || ansSure == 'N')
                {
                    system("cls");
                    continue;
                }
                system("cls");
                printf("\nX Not a valid choice, please re-enter");
                continue;
            }
            system("cls");
            printf("\nX Not a valid choice, please re-enter");
        }

        system("cls");

        /* === Amount > 0 (integer) === */
        int amount = 0;
        while (1)
        {
            printf("\nHow many would you like to buy?\n");
            printf("> Quantity (integer > 0): ");
            if (scanf("%d", &amount) != 1)
            {
                clear_line();
                system("cls");
                printf("\nX Not a valid choice, please re-enter");
                continue;
            }
            clear_line();
            if (amount > 0)
                break;
            system("cls");
            printf("\nX Not a valid choice, please re-enter");
        }

        system("cls");

        /* Add line and update totals */
        if (listCount < 1000)
        {
            shopList[listCount][0] = ansType - 1;
            shopList[listCount][1] = ansItem;
            shopList[listCount][2] = amount;
            listCount++;
        }
        subtotal += price[ansType - 1][ansItem] * amount;
        float total_with_tax = subtotal * (1.0f + TAX_RATE);

        /* Print confirmation + current purchases */
        printf("\n++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("Added %s x%d\n", grocery[ansType - 1][ansItem], amount);
        printf("Subtotal: $%.2f, Tax: $%.2f, Total: $%.2f\n",
               subtotal, subtotal * TAX_RATE, total_with_tax);
        printf("++++++++++++++++++++++++++++++++++++++++++++++++\n");

        printf("\nYour purchases:\n");
        for (int i = 0; i < listCount; i++)
        {
            int c = shopList[i][0], it = shopList[i][1], qty = shopList[i][2];
            float line_sub = price[c][it] * qty;
            printf("[%d] %s ($%.2f) x%d  = $%.2f\n",
                   i + 1, grocery[c][it], price[c][it], qty, line_sub);
        }

        /* === Continue? (y/n) === */
        while (1)
        {
            char ansDone = 0;
            printf("Would you like to purchase another item? (y/n): ");
            if (scanf(" %c", &ansDone) != 1)
            {
                clear_line();
                printf("\n\nX Not a valid choice, please re-enter\n");
                continue;
            }
            clear_line();
            if (ansDone == 'y' || ansDone == 'Y')
            {
                system("cls");
                break;
            }
            if (ansDone == 'n' || ansDone == 'N')
            {
                continueShopping = false;
                system("cls");
                break;
            }
            printf("\n\nX Not a valid choice, please re-enter\n");
        }

    continue_outer_loop:
        /* loop label to re-show categories when user chose 0 */
        continue;
    }

    /* === Payment === */
    float total_with_tax = subtotal * (1.0f + TAX_RATE);
    float pay = 0.0f;
    while (1)
    {
        printf("How much will you pay?\n");
        printf("Your total is $%.2f (incl. $%.2f tax).\n",
               total_with_tax, subtotal * TAX_RATE);
        printf("Your money: ");
        if (scanf("%f", &pay) != 1)
        {
            clear_line();
            printf("\n\nX Not a valid choice, please re-enter\n");
            continue;
        }
        clear_line();
        if (pay + 1e-4f >= total_with_tax)
            break; /* allow tiny float error */
        printf("\n\nX Not a valid choice, please re-enter\n");
    }
    float change = pay - total_with_tax;

    /* === Summary === */
    printf("\n################################################################\n");
    printf("Your purchases:\n");
    for (int i = 0; i < listCount; i++)
    {
        int c = shopList[i][0], it = shopList[i][1], qty = shopList[i][2];
        float line_sub = price[c][it] * (float)qty;
        printf("[%d] %s ($%.2f) x%d  = $%.2f\n",
               i + 1, grocery[c][it], price[c][it], qty, line_sub);
    }
    printf("\nSubtotal: $%.2f\nTax (8%%): $%.2f\nTotal: $%.2f\nPaid: $%.2f\nChange: $%.2f\n",
           subtotal, subtotal * TAX_RATE, total_with_tax, pay, change);
    printf("Thank you for your purchase!\n");

    return 0;
}
