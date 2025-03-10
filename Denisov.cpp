
#pragma warning(disable:4996)
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include "testing.h"

int main()
{
    int number, count; //число, которое предположительно является счастливым
    bool isLucky; //признак того, что число является действительно счастливым
    int digit1, digit2, digit3, digit4, digit5, digit6; //разряды исходного числа, digit1- младший разряд

    //Ввести число
    input_printf("Input number:");
    scanf("%d", &number);

    //Выделить разряды числа
         //Выделить разряд 6 и исключить его из числа
    digit6 = number / 100000;
    number = number - digit6 * 100000;

    //Выделить разряд 5 и исключить его из числа
    digit5 = number / 10000;
    number = number - digit5 * 10000;

    //Выделить разряд 4 и исключить его из числа
    digit4 = number / 1000;
    number = number - digit4 * 1000;

    //Выделить разряд 3 и исключить его из числа
    digit3 = number / 100;
    number = number - digit3 * 100;

    //Выделить разряд 2 и исключить его из числа
    digit2 = number / 10;
    number = number - digit2 * 10;

    //Выделить разряд 1
    digit1 = number;

    //Определить, является ли число счастливым
    isLucky = (digit1 == digit4) && ((digit2 == digit5) && (digit3 == digit6));

    //Напечатать, является ли число счастливым
    if (isLucky)
    {
        printf("Number is lucky");
    }
    else
    {
        printf("Number is not lucky");
    }
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"
