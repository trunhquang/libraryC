#include <stdio.h>
#include "function.h"
#include "string.h"
#include <stdlib.h>
#include <stdbool.h>

/// @brief validate action in
/// @param choice
/// @param length
/// @return
bool validate_action(int choice, int length)
{
    if (choice < 0 || choice > length - 1)
    {
        printf("Chức năng không tồn tại, vui lòng chọn lại \n");
        return false;
    }
    return true;
}

/// @brief choice action
/// @param length max of choice
int choice_action(int length)
{
    printf("Chọn chức năng:");
    int choice;
    if (scanf("%d", &choice) != 1)
    {
        // Clear the input buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        printf("\n*************************ERROR:************************\n");
        printf("****** Chức năng không tồn tại, vui lòng chọn lại. ****\n");
        printf("***** Chức năng là số đầu tiên của menu từ 0 -> %d *****\n", length - 1);
        printf("*******************************************************\n\n");

        return choice_action(length);
    }
    else
    {
        if (validate_action(choice, length))
        {
            return choice;
        }
        else
        {
            printf("\n*************************ERROR:************************\n");
            printf("****** Chức năng không tồn tại, vui lòng chọn lại. ****\n");
            printf("***** Chức năng là số đầu tiên của menu từ 0 -> %d *****\n", length - 1);
            printf("*******************************************************\n\n");
            return choice_action(length);
        }
    }
}

int other_action()
{
    printf("----------------chọn thao tác tiêp theo----------------\n");
    char other_menu[2][100] = {"Quay lại",
                               "Thoát chương trình"};
    int other_menu_length = sizeof(other_menu) / sizeof(other_menu[0]);
    for (int i = 0; i < other_menu_length; i++)
    {
        printf("%d.%s\n", i, other_menu[i]);
    }
    printf("-------------------------------------------------------\n");
    printf("Chọn chức năng:");
    int choice;
    scanf("%d", &choice);
    printf("-------------------------------------------------------\n");
    return choice;
}

void printLine(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("-");
    }
    break_line();
}

void print_cell(const char *text, int width, bool is_center)
{
    char format[100];
    int text_length = utf8_strlen(text);

    int padding_left = 0;
    int padding_right = 0;
    if (is_center)
    {
        padding_left = (width - text_length) / 2;
        padding_right = (width - text_length) - padding_left;
        printf(" %*s%s%*s ", padding_left, "", text, padding_right, "");
    }
    else
    {
        padding_left = 1;
        padding_right = (width - text_length) - padding_left;
        printf(" %*s%s%*s ", padding_left, "", text, padding_right, "");
    }
}

void break_line()
{
    printf("\n");
}

void end_line()
{
    printf("|\n");
}

void begin_line()
{
    printf("|");
}

// Function to add a number to an array
int *addNumberToArray(int *array, int *size, int number)
{
    // Increment the size of the array
    (*size)++;

    // Reallocate memory for the array
    array = (int *)realloc(array, (*size) * sizeof(int));
    if (array == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1); // Exit the program if memory allocation fails
    }

    // Add the number to the end of the array
    array[(*size) - 1] = number;

    return array;
}

// Function to add a string to an array of strings
char **addStringToArray(char **array, int *size, const char *string)
{
    // Increment the size of the array
    (*size)++;

    // Reallocate memory for the array
    array = (char **)realloc(array, (*size) * sizeof(char *));
    if (array == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1); // Exit the program if memory allocation fails
    }

    // Allocate memory for the new string and copy it
    array[(*size) - 1] = (char *)malloc((utf8_strlen(string) + 1) * sizeof(char));
    if (array[(*size) - 1] == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1); // Exit the program if memory allocation fails
    }
    strcpy(array[(*size) - 1], string);
    return array;
}

int findIndex(int arr[], int size, int target)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == target)
        {
            return i; // Return the index if the target is found
        }
    }
    // If the target is not found, return -1
    return -1;
}

int *findStringIndex(char **array, int size, int *arrayLength, const char *target)
{
    (*arrayLength) = 0;

    int *indexs = (int *)malloc(1 * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        if (strstr(array[i], target) != NULL)
        {
            (*arrayLength)++;

            indexs = (int *)realloc(indexs, (*arrayLength) * sizeof(int));
            indexs[(*arrayLength) - 1] = i;
        }
    }

    return indexs;
}

int findExactlyIndex(char **array, int size, const char *target)
{
    for (int i = 0; i < size; i++)
    {
        if (strcmp(array[i], target) == 0)
        {
            return i; // Return the index if the target is found
        }
    }
    // If the target is not found, return -1
    return -1;
}

void deleteElement(char **array, int size, int index)
{
    if (index < 0 || index >= size)
    {
        printf("Invalid index\n");
        return;
    }

    // Free memory for the deleted string
    free(array[index]);

    // Shift elements after the deleted one to the left
    for (int i = index; i < size - 1; i++)
    {
        array[i] = array[i + 1];
    }

    // Adjust the size of the array
    array[size - 1] = NULL;
}

void deleteElementInt(int *array, int size, int index)
{
    if (index < 0 || index >= size)
    {
        printf("Invalid index\n");
        return;
    }

    // Shift elements after the deleted one to the left
    for (int i = index; i < size - 1; i++)
    {
        array[i] = array[i + 1];
    }

    // Adjust the size of the array
    array[size - 1] = NULL;
}

// Hàm kiểm tra năm nhuận
int isLeapYear(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    {
        return 1; // Năm nhuận
    }
    else
    {
        return 0; // Năm không nhuận
    }
}

// Hàm tính số ngày trong một tháng
int daysInMonth(int month, int year)
{
    int days[] = {31, 28 + isLeapYear(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return days[month - 1];
}

// Hàm tính số ngày trễ hạn
int daysLate(int day1, int month1, int year1, int day2, int month2, int year2)
{
    int days = 0;

    // Tính số ngày còn lại trong năm của ngày tháng 1
    for (int m = month1 + 1; m <= 12; ++m)
    {
        days += daysInMonth(m, year1);
    }
    days += daysInMonth(month1, year1) - day1;

    // Tính số ngày trong các năm trung gian
    for (int y = year1 + 1; y < year2; ++y)
    {
        days += 365 + isLeapYear(y);
    }

    if (year2 > year1)
    {
        // Tính số ngày đã qua trong năm của ngày tháng 2
        for (int m = 1; m < month2; ++m)
        {
            days += daysInMonth(m, year2);
        }
        days += day2;
    }
    else if (year2 == year1)
    {
        int date_left = 0;
        // Tính số ngày còn lại trong năm của ngày tháng 2
        for (int m = month2 + 1; m <= 12; ++m)
        {
            date_left += daysInMonth(m, year2);
        }
        date_left += daysInMonth(month2, year2) - day2;
        return days - date_left;
    }
    else
    {
        return -1;
    }
    return days;
}

// Hàm kiểm tra xem một byte có phải là một byte đầu của một UTF-8 character hay không
int is_start_byte(uint8_t byte) {
    return (byte & 0xC0) != 0x80;
}

// Hàm tính độ dài của chuỗi có dấu
int utf8_strlen(const char *str) {
    int length = 0;
    while (*str) {
        // Kiểm tra xem byte hiện tại có phải là một byte đầu của một UTF-8 character hay không
        if (is_start_byte(*str)) {
            length++;
        }
        str++;
    }
    return length;
}