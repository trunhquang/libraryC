#include <stdio.h>
#include "statistics.h"
#include <stdlib.h>
#include "../books/books.h"
#include "../readers/readers.h"
#include "../ticket/ticket.h"

void statistics_show()
{
    printf("------------------------THỐNG KÊ------------------------\n");
    int total_book = get_total_book();
    printf("a. Số lượng sách trong thư viện: %d\n", total_book);
    printf("b. Số lượng sách theo thể loại:\n");
    show_statistics_category();
    printf("c. Số lượng độc giả: %d\n", get_total_reader());
    printf("d. Số lượng độc giả theo giới tính:\n");
    show_statistics_gender();
    printf("e. Số sách đang được mượn: %d\n", get_total_borrowed_books());
    printf("f. Danh sách độc giả bị trễ hạn:\n");
    show_reader_late_ticket();
}