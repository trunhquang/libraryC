#include "menu.h"
#include <stdio.h>
#include <string.h>
#include <wchar.h>

#include "../function/function.h"


/// @brief show main menu
/// @return choice
int library_menu_show()
{
    printf("\n\n********************THƯ VIỆN ĐHKHTN********************\n");
    printf("--------------------------MENU-------------------------\n");
    char menu[6][100] = {"Quản lí độc giả",
                         "Quản lí sách",
                         "Lập phiếu mượn sách",
                         "Lập phiếu trả sách",
                         "Thống kê cơ bản",
                         "Thoát chương trình"};
    for (int i = 0; i < 6; i++)
    {
        printf("%d.%s\n", i, menu[i]);
    }
    printf("-------------------------------------------------------\n");
    return choice_action(6);
}

