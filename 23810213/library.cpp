#include <stdio.h>
#include "library.h"
#include "books/books.h"
#include "menu/menu.h"
#include "readers/readers.h"
#include "statistics/statistics.h"
#include "ticket/ticket.h"
#include <uchar.h>
#include <string.h>

#include <stdint.h>



/// @brief show main menu
void show_main_menu()
{
    int functionChoice = library_menu_show();
    /// @brief manage readers
    if (functionChoice == 0)
{
        bool isback = !readers_show_menu_functions();
        /// @brief exit readers menu, show main menu again
        if (isback)
        {
            show_main_menu();
        }
    }
    else
        /// @brief manage books
        if (functionChoice == 1)
        {
            bool isback = !books_show_menu_function();
            /// @brief exit readers menu, show main menu again
            if (isback)
            {
                show_main_menu();
            }
        }
        else if (functionChoice == 2)
        {
            bool isback = !ticket_show_menu();
            if (isback)
            {
                show_main_menu();
            }
        }
        else if (functionChoice == 3)
        {
            bool isback = !ticket_return_show_menu();
            if (isback)
            {
                show_main_menu();
            }
        }
        else if (functionChoice == 4)
        {
            statistics_show();
            show_main_menu();
        }
        else
            /// @brief exit program
            if (functionChoice == 5)
            {
                return;
            }
}

// Shift Option F: format code
int main()
{
    create_template_reader();
    create_template_book();
    create_template_ticket();
    show_main_menu();
    return 0;
}
