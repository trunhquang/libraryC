#pragma once

/// @brief handle menu
int choice_action(int);

/// @brief validate action
bool validate_action(int, int);

/// @brief handle other actions
int other_action();

/// @brief print line with n char "-"
/// @param n 
void printLine(int n);

///@
void print_cell(const char *text, int width, bool is_center);

void break_line();

void end_line();

void begin_line();

int* addNumberToArray(int *array, int *size, int number);

char **addStringToArray(char **array, int *size, const char *string);

int findIndex(int arr[], int size, int target);
int *findStringIndex( char **array, int size, int *arrayLength, const char *target);
int findExactlyIndex(char **array, int size, const char *target);
void deleteElement(char **array, int size, int index);

void deleteElementInt(int *array, int size, int index);

int daysLate(int day1, int month1, int year1, int day2, int month2, int year2);
int utf8_strlen(const char *str);
int ensure_directory_exists(const char *path);