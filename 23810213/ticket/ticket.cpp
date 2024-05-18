#include "../function/function.h"
#include "../readers/readers.h"
#include "../books/books.h"
#include "string.h"
#include <stdio.h>
#include "ticket.h"
#include <stdlib.h>
#include "time.h"

int ticket_w_line = 0;
int ticket_column_with[10];
char *ticket_file = "files/ticket.txt";

/// late fee per day
int late_fee_per_day = 5000;
/// lost fee per book 200% price book
int lost_fee_per_book = 2;

bool ticket_show_menu()
{
    printf("-----------------------QUẢN LÝ PHIẾU MƯỢN SÁCH-----------------------\n");

    char menu[4][100] = {"Xem tất cả phiếu mượn/trả",
                         "Lập phiếu mượn sách",
                         "Quay lại",
                         "Thoát chương trình"};
    int length = 4;
    for (int i = 0; i < length; i++)
    {
        printf("%d.%s\n", i, menu[i]);
    }
    printf("---------------------------------------------------------------------\n");

    int choice = choice_action(length);

    bool isContinue = choice != 2;
    if (choice == 3)
    {
        // Exit program
        return true;
    }
    else if (!isContinue)
    {
        // Exit readers menu, show main menu again
        return false;
    }
    else
    {
        // Handle readers menu
        return handle_ticket_menu(choice);
    }
}

void return_ticket()
{
    struct Ticket *ticket_list;
    int ticket_size = read_tickets_from_file(ticket_file, &ticket_list);
    printLine(54);
    begin_line();
    print_cell("** LẬP PHIẾU TRẢ SÁCH **", 50, true);
    end_line();
    printLine(54);

    int _id_ticket;
    // day, mounth ,year
    int _day_return, _mounth_return, _year_return;

    printf("Nhập ID phiếu mượn(số): ");
    scanf("%d", &_id_ticket);
    printf("Độc giả có làm mất sách không? (1.Có  0.Không) ");

    int index = findTicketByid(ticket_list, ticket_size, _id_ticket);

    if (index == -1)
    {
        printLine(54);
        begin_line();
        print_cell("Không tìm thấy phiếu mượn", 50, true);
        end_line();
        printLine(54);
    }

    struct Ticket *ticket = &ticket_list[index];

    if (ticket->return_status == 1)
    {
        printLine(54);
        begin_line();
        print_cell("** Phiếu mượn này đã được trả **", 50, true);
        end_line();
        printLine(54);
        return;
    }

    int value;
    scanf(" %d", &value);
    if (value == 0)
    {
        // Nhập ngày, tháng và năm cách nhau bằng dấu /
        printf("Nhập ngày trả (vd: 28/04/2024): ");
        scanf("%d/%d/%d", &_day_return, &_mounth_return, &_year_return);

        int _dayslate = daysLate(ticket->day_borrow, ticket->mounth_borrow, ticket->year_borrow, _day_return, _mounth_return, _year_return);

        while (_dayslate < 0)
        {
            printf("Ngày tháng không hợp lệ, Nhập lại (vd: 28/04/2024): ");
            scanf("%d/%d/%d", &_day_return, &_mounth_return, &_year_return);
            _dayslate = daysLate(ticket->day_borrow, ticket->mounth_borrow, ticket->year_borrow, _day_return, _mounth_return, _year_return);
        }

        ticket->day_return = _day_return;
        ticket->mounth_return = _mounth_return;
        ticket->year_return = _year_return;

        printf("Ngày trả: %d/%d/%d\n", ticket->day_return, ticket->mounth_return, ticket->year_return);

        ticket->return_status = 1;
        print_ticket(ticket_list[index]);

        if (_dayslate > 7)
        {
            _dayslate -= 7;
            int money_pay_for_error = _dayslate * late_fee_per_day;
            ticket->money_pay_for_error =  money_pay_for_error;
            char message[100];
            snprintf(message, sizeof(message), "Trễ %d ngày", _dayslate);
            strcpy(ticket->reason_pay, message);
        }
    } else {
        int price = get_price_book(ticket->book_id);
        int money_pay_for_error = price * lost_fee_per_book;
        ticket->money_pay_for_error = money_pay_for_error;
        ticket->return_status = 1;
        strcpy(ticket->reason_pay, "Mất sách");
    }
    write_tickets_to_file(ticket_file, ticket_list, ticket_size);
    printLine(54);
    begin_line();
    print_cell("** Đã trả sách thành công **", 50, true);
    end_line();
    printLine(54);

    view_tickets(index, false);
    free_tickets(ticket_list, ticket_size);
}

bool handle_ticket_return__menu(int choice)
{
    switch (choice)
    {
    case 0:
        view_tickets(0, true);
        break;
    case 1:
        return_ticket();
        break;
    default:
        break;
    }
    return ticket_return_show_menu();
}

bool ticket_return_show_menu()
{
    printf("-----------------------QUẢN LÝ PHIẾU-----------------------\n");

    char menu[4][100] = {"Xem tất cả phiếu mượn/trả",
                         "Lập phiếu trả sách",
                         "Quay lại",
                         "Thoát chương trình"};
    int length = 4;
    for (int i = 0; i < length; i++)
    {
        printf("%d.%s\n", i, menu[i]);
    }
    printf("---------------------------------------------------------------------\n");

    int choice = choice_action(length);

    bool isContinue = choice != 2;
    if (choice == 3)
    {
        // Exit program
        return true;
    }
    else if (!isContinue)
    {
        // Exit readers menu, show main menu again
        return false;
    }
    else
    {
        // Handle readers menu
        return handle_ticket_return__menu(choice);
    }
}

bool handle_ticket_menu(int choice)
{
    switch (choice)
    {
    case 0:
        view_tickets(0, true);
        break;
    case 1:
        add_ticket();
        break;
    default:
        break;
    }
    return ticket_show_menu();
}

void calculator_titket_column_w(int *arr)
{
    int id_ticket_w = 9;
    int id_reader_w = 11;
    int reader_name = 20;
    int isbn_w = 15;
    int day_borrow_w = 16;
    int day_return_w_ex = 16;
    int day_return_w = 16;
    int status_w = 8;
    int money_w = 10;
    int reason_w = 20;

    arr[0] = id_ticket_w;
    arr[1] = id_reader_w;
    arr[2] = reader_name;
    arr[3] = isbn_w;
    arr[4] = day_borrow_w;
    arr[5] = day_return_w_ex;
    arr[6] = day_return_w;
    arr[7] = status_w;
    arr[8] = money_w;
    arr[9] = reason_w;
}

void print_ticket_title()
{
    ticket_w_line = 0;
    calculator_titket_column_w(ticket_column_with);
    for (int i = 0; i < 10; ++i)
    {
        ticket_w_line += ticket_column_with[i] + 3; // 2 là 2 ký tự space 2 đầu + 1 ký tự |
    }
    ticket_w_line += 1; // 1 là 1 ký tự | endline

    printLine(ticket_w_line);
    begin_line();

    // 2 là 2 ký tự space 2 đầu, 2 là 2 ký tự | 2 đầu
    print_cell("DANH SÁCH", ticket_w_line - 4, true);
    end_line();
    printLine(ticket_w_line);

    begin_line();
    print_cell("ID", ticket_column_with[0], true);
    begin_line();
    print_cell("ID ĐỘC GIẢ", ticket_column_with[1], true);
    begin_line();
    print_cell("TÊN ĐỘC GIẢ", ticket_column_with[2], true);
    begin_line();
    print_cell("IBNS", ticket_column_with[3], true);
    begin_line();
    print_cell("NGÀY MƯỢN", ticket_column_with[4], true);
    begin_line();
    print_cell("NGÀY TRẢ DỰ KIẾN", ticket_column_with[5], true);
    begin_line();
    print_cell("NGÀY TRẢ", ticket_column_with[6], true);
    begin_line();
    print_cell("DÃ TRẢ", ticket_column_with[7], true);
    begin_line();
    print_cell("TIỀN PHẠT", ticket_column_with[8], true);
    begin_line();
    print_cell("LÝ DO", ticket_column_with[9], true);
    end_line();
    printLine(ticket_w_line);
}

void print_ticket(struct Ticket ticket)
{
    char result[20];
    begin_line();
    snprintf(result, sizeof(result), "%d", ticket.ticket_id);
    print_cell(result, ticket_column_with[0], true);
    begin_line();
    snprintf(result, sizeof(result), "%d", ticket.reader_id);
    print_cell(result, ticket_column_with[1], true);
    begin_line();
    print_cell(get_reader_name(ticket.reader_id), ticket_column_with[2], false);
    begin_line();
    print_cell(ticket.book_id, ticket_column_with[3], false);
    begin_line();
    snprintf(result, 11, "%02d/%02d/%d", ticket.day_borrow, ticket.mounth_borrow, ticket.year_borrow);
    print_cell(result, ticket_column_with[4], true);
    begin_line();
    snprintf(result, 11, "%02d/%02d/%d", ticket.day_return_ex, ticket.mounth_return_ex, ticket.year_return_ex);
    print_cell(result, ticket_column_with[5], true);
    begin_line();

    if (ticket.day_return != 0)
    {
        snprintf(result, 11, "%02d/%02d/%d", ticket.day_return, ticket.mounth_return, ticket.year_return);
        print_cell(result, ticket_column_with[6], true);
    }
    else
    {
        print_cell("", ticket_column_with[6], true);
    }

    begin_line();
    if (ticket.return_status == 1)
    {
        snprintf(result, sizeof(result), "%s", "True");
    }
    else
    {
        snprintf(result, sizeof(result), "%s", "False");
    }
    print_cell(result, ticket_column_with[7], true);
    begin_line();
    snprintf(result, sizeof(result), "%d", ticket.money_pay_for_error);
    print_cell(result, ticket_column_with[8], false);
    begin_line();
    print_cell(ticket.reason_pay, ticket_column_with[9], false);
    end_line();
}

void view_tickets(int index, bool showAll)
{
    struct Ticket *ticket_list;
    int ticket_size = read_tickets_from_file(ticket_file, &ticket_list);
    print_ticket_title();
    if (ticket_size == 0)
    {
        begin_line();
        print_cell("**** Chưa có thông tin phiếu mượn/trả ****", ticket_w_line - 4, true);
        end_line();
        printLine(ticket_w_line);
        return;
    }
    if (showAll)
    {
        // In dữ liệu từng dòng
        for (int i = ticket_size - 1; i >= 0; --i)
        {
            struct Ticket ticket = ticket_list[i];
            print_ticket(ticket);
        }
    }
    else
    {
        struct Ticket ticket = ticket_list[index];
        print_ticket(ticket);
    }

    // Kết thúc bảng
    printLine(ticket_w_line);
    free_tickets(ticket_list, ticket_size);
}

void add_ticket()
{
    if (get_reader_size() == 0)
    {
        printLine(100);
        begin_line();
        print_cell("**** Chưa có thông tin độc giả, vui lòng thêm đọc giả trước ****", 97, true);
        end_line();
        printLine(100);
        return;
    }
    if (get_book_size() == 0)
    {
        printLine(100);
        begin_line();
        print_cell("**** Chưa có sách trong thư viện ****", 97, true);
        end_line();
        printLine(100);
        return;
    }

    printLine(54);
    begin_line();
    print_cell("** LÂPK PHIẾU MƯỢN SÁCH **", 50, true);
    end_line();
    printLine(54);

    // reader id
    int _id_reader;
    // isbn books,
    char _isbn_book[100];
    // day, mounth ,year
    int _day_borrow, _mounth_borrow, _year_borrow;

    printf("Nhập ID độc giả(số): ");
    scanf(" %d", &_id_reader);
    int reader_size = get_reader_size();
    int *ids_reader = get_ids_reader();

    int index = findIndex(ids_reader, reader_size, _id_reader);

    while (index == -1)
    {
        printf("Không tìm thấy, nhập lại ID độc giả(số): ");
        scanf(" %d", &_id_reader);
        index = findIndex(ids_reader, reader_size, _id_reader);
    }

    printf("ISBN sách cần mượn: ");
    scanf(" %99[^\n]", _isbn_book);

    int book_size = get_book_size();
    char **isbns = get_isbns_book();

    index = findExactlyIndex(isbns, book_size, _isbn_book);
    while (index == -1)
    {
        printf("Không tìm thấy, nhập lại ISBN: ");
        scanf(" %99[^\n]", _isbn_book);
        index = findExactlyIndex(isbns, book_size, _isbn_book);
    }

    // Nhập ngày, tháng và năm cách nhau bằng dấu /
    printf("Nhập ngày mượn (vd: 28/04/2024): ");
    scanf("%d/%d/%d", &_day_borrow, &_mounth_borrow, &_year_borrow);

    // realloc data list
    struct Ticket *ticket_list;
    int ticket_size = read_tickets_from_file(ticket_file, &ticket_list);
    int newId = 1;
    if (ticket_size > 0)
    {
        newId = ticket_list[ticket_size - 1].ticket_id + 1;
    }

    char reason[256] = "_";
    struct Ticket ticket = createTicket(newId, _id_reader, _isbn_book, reason, 0, 0, _day_borrow, _mounth_borrow, _year_borrow, 0, 0, 0);
    write_ticket_to_file(ticket_file, ticket);
    view_tickets(ticket_size - 1, false);
    free_tickets(ticket_list, ticket_size);
}

int get_total_borrowed_books()
{
    struct Ticket *ticket_list;
    int ticket_size = read_tickets_from_file(ticket_file, &ticket_list);
    int count = 0;
    for (int i = 0; i < ticket_size; i++)
    {
        if (ticket_list[i].return_status == 0)
        {
            count++;
        }
    }
    free_tickets(ticket_list, ticket_size);
    return count;
}
void show_reader_late_ticket()
{
    struct Ticket *ticket_list;
    int ticket_size = read_tickets_from_file(ticket_file, &ticket_list);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int ngay = tm.tm_mday;
    int thang = tm.tm_mon + 1;   // tm_mon đếm từ 0, nên cần cộng 1
    int nam = tm.tm_year + 1900; // tm_year là số năm kể từ 1900
    print_ticket_title();
    for (int i = 0; i < ticket_size; i++)
    {
        struct Ticket ticket = ticket_list[i];
        if (ticket.return_status == 0)
        {
            int _dayslate = daysLate(ticket.day_borrow, ticket.mounth_borrow, ticket.year_borrow, ngay, thang, nam);
            if (_dayslate > 7)
            {
                ticket.money_pay_for_error = (_dayslate - 7) * late_fee_per_day;
                char message[100];
                snprintf(message, sizeof(message), "Trễ %d ngày", (_dayslate - 7));
                strcpy(ticket.reason_pay, message);
                print_ticket(ticket);
            }
        }
    }
    printLine(ticket_w_line);
    free_tickets(ticket_list, ticket_size);
}

struct Ticket createTicket(int ticket_id,
                           int reader_id,
                           char *book_id,
                           char *reason_pay,
                           int return_status,
                           int money_pay_for_error,
                           int day_borrow, int mounth_borrow, int year_borrow,
                           int day_return, int mounth_return, int year_return)
{
    struct Ticket ticket;
    ticket.ticket_id = ticket_id;
    ticket.reader_id = reader_id;
    ticket.book_id = (char *)malloc(strlen(book_id) + 1);
    if (ticket.book_id != NULL)
    {
        strcpy(ticket.book_id, book_id);
    }
    ticket.reason_pay = (char *)malloc(strlen(reason_pay) + 1);
    if (ticket.reason_pay != NULL)
    {
        strcpy(ticket.reason_pay, reason_pay);
    }
    ticket.return_status = return_status;
    ticket.money_pay_for_error = money_pay_for_error;
    ticket.day_borrow = day_borrow;
    ticket.mounth_borrow = mounth_borrow;
    ticket.year_borrow = year_borrow;

    struct tm return_ex_time = {0};
    return_ex_time.tm_mday = day_borrow;
    return_ex_time.tm_mon = mounth_borrow;
    return_ex_time.tm_year = year_borrow - 1900;

    // Chuyển đổi struct tm thành thời gian số nguyên (số giây kể từ epoch)
    time_t time_seconds = mktime(&return_ex_time);

    struct tm *current_time = localtime(&time_seconds);
    // Thêm 7 ngày vào thời gian số nguyên
    time_seconds += (7 * 24 * 60 * 60);
    // Chuyển đổi thời gian số nguyên mới thành struct tm
    struct tm *future_time = localtime(&time_seconds);

    ticket.day_return_ex = future_time->tm_mday;
    ticket.mounth_return_ex = future_time->tm_mon;
    ticket.year_return_ex = future_time->tm_year + 1900;

    ticket.day_return = day_return;
    ticket.mounth_return = mounth_return;
    ticket.year_return = year_return;
    return ticket;
}

void addTicketToList(struct Ticket **tickets, int *num, struct Ticket new_ticket)
{
    *num += 1;
    *tickets = (struct Ticket *)realloc(*tickets, *num * sizeof(struct Ticket));
    if (*tickets == NULL)
    {
        printf("Không đủ bộ nhớ để cấp phát\n");
        return;
    }
    (*tickets)[*num - 1] = new_ticket;
}

int findTicketByid(struct Ticket *ticket, int num, int id)
{
    for (int i = 0; i < num; i++)
    {
        if (ticket[i].ticket_id == id)
        {
            return i;
        }
    }
    return -1;
};

void write_tickets_to_file(const char *filename, struct Ticket *tickets, int count)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("Failed to open file");
        return;
    }
    // Write the number of ticket
    fprintf(file, "%d\n", count);

    // Write each book's information
    for (int i = 0; i < count; i++)
    {
        struct Ticket ticket = tickets[i];
        // printf( "ticketid:%d\n", ticket.ticket_id);
        // printf( "readerID:%d\n", ticket.reader_id);
        // printf( "book_id:%s\n", ticket.book_id);
        // printf( "reason_pay:%s\n", ticket.reason_pay);
        // printf( "return_status:%d\n", ticket.return_status);
        // printf( "money_pay_for_error:%d\n", ticket.money_pay_for_error);
        // printf( "day_borrow:%d\n", ticket.day_borrow);
        // printf( "mounth_borrow:%d\n", ticket.mounth_borrow);
        // printf( "year_borrow:%d\n", ticket.year_borrow);
        // printf( "day_return_ex:%d\n", ticket.day_return_ex);
        // printf( "mounth_return_ex:%d\n", ticket.mounth_return_ex);
        // printf( "year_return_ex:%d\n", ticket.year_return_ex);
        // printf( "day_return:%d\n", ticket.day_return);
        // printf( "mounth_return:%d\n", ticket.mounth_return);
        // printf( "year_return:%d\n", ticket.year_return);
        // printf( "%s\n", "----------------------------------");

        fprintf(file, "%d\n", ticket.ticket_id);
        fprintf(file, "%d\n", ticket.reader_id);
        fprintf(file, "%s\n", ticket.book_id);
        fprintf(file, "%s\n", ticket.reason_pay);
        fprintf(file, "%d\n", ticket.return_status);
        fprintf(file, "%d\n", ticket.money_pay_for_error);
        fprintf(file, "%d\n", ticket.day_borrow);
        fprintf(file, "%d\n", ticket.mounth_borrow);
        fprintf(file, "%d\n", ticket.year_borrow);
        fprintf(file, "%d\n", ticket.day_return_ex);
        fprintf(file, "%d\n", ticket.mounth_return_ex);
        fprintf(file, "%d\n", ticket.year_return_ex);
        fprintf(file, "%d\n", ticket.day_return);
        fprintf(file, "%d\n", ticket.mounth_return);
        fprintf(file, "%d\n", ticket.year_return);
        fprintf(file, "%s\n", "----------------------------------");
    }

    fclose(file);
}

void write_ticket_to_file(const char *filename, struct Ticket ticket)
{
    // Extract the directory path from the filename
    char dir[256];
    strcpy(dir, filename);
    char *last_slash = strrchr(dir, '/');
    if (last_slash != NULL)
    {
        *last_slash = '\0'; // Terminate the string at the last slash
        if (ensure_directory_exists(dir) != 0)
        {
            return;
        }
    }

    FILE *file = fopen(filename, "r+"); // Open the file in read-write mode
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }
    // Read the count of readers
    int count;
    if (fscanf(file, "%d\n", &count) != 1)
    {
        perror("Error reading count of readers");
        fclose(file);
        return;
    }
    // Update the count of readers
    count++;
    // Move the file pointer to the beginning to overwrite the count
    rewind(file);
    fprintf(file, "%d\n", count);

    // Move the file pointer to the end of the file
    if (fseek(file, 0, SEEK_END) != 0)
    {
        perror("Error moving file pointer to the end of file");
        fclose(file);
        return;
    }
        fprintf(file, "%d\n", ticket.ticket_id);
        fprintf(file, "%d\n", ticket.reader_id);
        fprintf(file, "%s\n", ticket.book_id);
        fprintf(file, "%s\n", ticket.reason_pay);
        fprintf(file, "%d\n", ticket.return_status);
        fprintf(file, "%d\n", ticket.money_pay_for_error);
        fprintf(file, "%d\n", ticket.day_borrow);
        fprintf(file, "%d\n", ticket.mounth_borrow);
        fprintf(file, "%d\n", ticket.year_borrow);
        fprintf(file, "%d\n", ticket.day_return_ex);
        fprintf(file, "%d\n", ticket.mounth_return_ex);
        fprintf(file, "%d\n", ticket.year_return_ex);
        fprintf(file, "%d\n", ticket.day_return);
        fprintf(file, "%d\n", ticket.mounth_return);
        fprintf(file, "%d\n", ticket.year_return);
        fprintf(file, "%s\n", "----------------------------------");
    fclose(file);
}

int read_tickets_from_file(const char *filename, struct Ticket **tickets)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Failed to open file");
        return 0;
    }

    int count;
    fscanf(file, "%d\n", &count);

    *tickets = (struct Ticket *)malloc(count * sizeof(struct Ticket));
    if (*tickets == NULL)
    {
        perror("Failed to allocate memory");
        return 0;
    }

    for (int i = 0; i < count; i++)
    {
        struct Ticket *ticket = &(*tickets)[i];

        ticket->book_id = (char *)malloc(256);
        ticket->reason_pay = (char *)malloc(256);

        fscanf(file, "%d\n", &ticket->ticket_id);
        fscanf(file, "%d\n", &ticket->reader_id);
        fscanf(file, "%255[^\n]\n", ticket->book_id);
        fscanf(file, "%255[^\n]\n", ticket->reason_pay);
        fscanf(file, "%d\n", &ticket->return_status);
        fscanf(file, "%d\n", &ticket->money_pay_for_error);
        fscanf(file, "%d\n", &ticket->day_borrow);
        fscanf(file, "%d\n", &ticket->mounth_borrow);
        fscanf(file, "%d\n", &ticket->year_borrow);
        fscanf(file, "%d\n", &ticket->day_return_ex);
        fscanf(file, "%d\n", &ticket->mounth_return_ex);
        fscanf(file, "%d\n", &ticket->year_return_ex);
        fscanf(file, "%d\n", &ticket->day_return);
        fscanf(file, "%d\n", &ticket->mounth_return);
        fscanf(file, "%d\n", &ticket->year_return);
        char line[256];
        fscanf(file, "%s\n", line);
    }

    fclose(file);
    return count;
}

void free_ticket(struct Ticket *ticket)
{
    free(ticket->book_id);
    free(ticket->reason_pay);
}

void free_tickets(struct Ticket *tickets, int count)
{
    for (int i = 0; i < count; i++)
    {
        free_ticket(&tickets[i]);
    }
    free(tickets);
}
