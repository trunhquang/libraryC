#include "books.h"
#include "../function/function.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int book_size = 0;
int bwidth_line = 0;
int bcolumn_with[8];
struct Book *book_list = NULL;

void bcalculator_column_with(int *arr)
{
    int id_width = 20;
    int name_width = 28;
    int authorW = 28;
    int publisherW = 20;
    int yearW = 20;
    int priceW = 20;
    int quantityW = 20;
    int type_width = 20;
    for (int i = 0; i < book_size; ++i)
    {
        struct Book book = book_list[i];
        // name
        if (name_width < utf8_strlen(book.title))
        {
            name_width = utf8_strlen(book.title);
        }
        // authorW
        if (authorW < utf8_strlen(book.author))
        {
            authorW = utf8_strlen(book.author);
        }
        // publisher*
        if (publisherW < utf8_strlen(book.publisher))
        {
            publisherW = utf8_strlen(book.publisher);
        }
    }
    arr[0] = id_width;
    arr[1] = name_width;
    arr[2] = authorW;
    arr[3] = publisherW;
    arr[4] = yearW;
    arr[5] = type_width;
    arr[6] = priceW;
    arr[7] = quantityW;
}

void bprint_title()
{
    bwidth_line = 0;
    bcalculator_column_with(bcolumn_with);
    int size = sizeof(bcolumn_with) / sizeof(bcolumn_with[0]);
    for (int i = 0; i < 8; ++i)
    {
        bwidth_line += bcolumn_with[i] + 3; // 2 là 2 ký tự space 2 đầu + 1 ký tự |
    }
    bwidth_line += 1; // 1 là 1 ký tự | endline

    printLine(bwidth_line);
    begin_line();

    // 2 là 2 ký tự space 2 đầu, 2 là 2 ký tự | 2 đầu
    print_cell("DANH SÁCH SÁCH", bwidth_line - 4, true);
    end_line();
    printLine(bwidth_line);

    begin_line();
    print_cell("ISBN", bcolumn_with[0], true);
    begin_line();
    print_cell("TÊN SÁCH", bcolumn_with[1], true);
    begin_line();
    print_cell("TÁC GIẢ", bcolumn_with[2], true);
    begin_line();
    print_cell("NXB", bcolumn_with[3], true);
    begin_line();
    print_cell("NĂM SẢN XUẤT", bcolumn_with[4], true);
    begin_line();
    print_cell("THỂ LOẠI", bcolumn_with[5], true);
    begin_line();
    print_cell("GÍA SÁCH", bcolumn_with[6], true);
    begin_line();
    print_cell("SỐ LƯỢNG", bcolumn_with[7], true);
    end_line();
    printLine(bwidth_line);
}

void print_book(int index)
{
    char result[10];
    struct Book book = book_list[index];

    begin_line();
    print_cell(book.isbn, bcolumn_with[0], false);
    begin_line();
    print_cell(book.title, bcolumn_with[1], false);
    begin_line();
    print_cell(book.author, bcolumn_with[2], false);
    begin_line();
    print_cell(book.publisher, bcolumn_with[3], false);
    begin_line();
    snprintf(result, sizeof(result), "%d", book.year);
    print_cell(result, bcolumn_with[4], true);
    begin_line();
    print_cell(book.category, bcolumn_with[5], false);
    begin_line();
    snprintf(result, sizeof(result), "%d", book.price);
    print_cell(result, bcolumn_with[6], false);
    begin_line();
    snprintf(result, sizeof(result), "%d", book.quantity);
    print_cell(result, bcolumn_with[7], false);
    end_line();
}

void view_books(int index, bool showAll)
{
    bprint_title();
    if (book_size == 0)
    {
        begin_line();
        print_cell("**** Thư viện chưa nhập thông tin sách ****", bwidth_line - 4, true);
        end_line();
        printLine(bwidth_line);
        return;
    }
    if (showAll)
    {
        // In dữ liệu từng dòng
        for (int i = book_size - 1; i >= 0; --i)
        {
            print_book(i);
        }
    }
    else
    {
        print_book(index);
    }

    // Kết thúc bảng
    printLine(bwidth_line);
}

void add_book()
{
    printLine(54);
    begin_line();
    print_cell("** THÊM SÁCH **", 50, true);
    end_line();
    printLine(54);

    char _ibns[28];
    char _name[100];
    char _author[28];
    char _publisher[100];
    char _type[100];
    int _year;
    int _price;
    int _quantity;

    /// @brief date expire card for readers, this is date create card + 2 year
    // char date_expire_card[][11] = {"01/01/2022", "02/02/2022", "03/03/2022", "04/04/2022"};

    // Nhập họ tên từ bàn phím
    printf("Nhập IBNS: ");
    scanf(" %27[^\n]", _ibns); // Sử dụng %[^\n] để cho phép nhập cả dấu cách

    // Nhập ten từ bàn phím
    printf("Nhập tên sách: ");
    scanf(" %99[^\n]", _name);

    printf("Nhập tên tác giả: ");
    scanf(" %27[^\n]", _author);

    printf("Nhập tên NXB: ");
    scanf(" %99[^\n]", _publisher);

    printf("Nhập loại sách: ");
    scanf(" %99[^\n]", _type);

    printf("Nhập năm xuất bản(số): ");
    scanf("%d", &_year);

    printf("Nhập giá sách: ");
    scanf("%d", &_price);

    printf("Nhập số lượng: ");
    scanf("%d", &_quantity);
    struct Book new_book = createBook(_ibns, _name, _author, _publisher, _type, _year, _price, _quantity);
    addBookToList(&book_list, &book_size, new_book);
    view_books(0, true);
}

void show_edit_book_menu(int index)
{
    printf("---------------------DANH MỤC CẦN SỬA-------------------\n");

    char edit_menu[8][100] = {"Sửa tên",
                              "Sửa Tác giả",
                              "Sửa NXB",
                              "Sửa năm xuất bản",
                              "Sửa giá sách",
                              "Sửa số lượng",
                              "Sửa loại sách",
                              "Quay lại"};

    for (int i = 0; i < 8; i++)
    {
        printf("%d.%s\n", i, edit_menu[i]);
    }
    printf("-------------------------------------------------------\n");

    struct Book book = book_list[index];

    int choice = choice_action(8);
    switch (choice)
    {
    case 0:
        char _name[100];
        printf("Nhập tên sách: ");
        scanf(" %99[^\n]", _name);
        strcpy(book.title, _name);
        break;
    case 1:
        char _author[100];
        printf("Nhập tên tác giả: ");
        scanf(" %99[^\n]", _author);
        strcpy(book.author, _author);
        break;
    case 2:
        char _publisher[100];
        printf("Nhập tên NXB");
        scanf(" %99[^\n]", _publisher);
        strcpy(book.publisher, _publisher);
        break;
    case 3:
        int _year;
        printf("Nhập năm xuất bản(4 số): ");
        scanf(" %d", &_year);
        book.year = _year;
        break;
    case 4:
        int _price;
        printf("Nhập giá: ");
        scanf(" %d", &_price);
        book.price = _price;
        break;
    case 5:
        int _quantity;
        printf("Nhập số lượng: ");
        scanf(" %d", &_quantity);
        book.quantity = _quantity;
        break;
    case 6:
        char _type[100];
        printf("Nhập loại sách: ");
        scanf(" %99[^\n]", _type);
        strcpy(book.category, _type);
        break;
    default:
        break;
    }
    printLine(54);
    begin_line();
    print_cell("** THÔNG TIN ĐÃ SỬA **", 50, true);
    end_line();
    printLine(54);
    view_books(index, false);
}

void edit_book()
{
    if (book_size == 0)
    {
        printLine(54);
        begin_line();
        print_cell("** Không có sách trong thư viện **", 54, true);
        end_line();
        printLine(54);
        return;
    }
    printLine(54);
    begin_line();
    print_cell("** SỬA THÔNG TIN SÁCH **", 50, true);
    end_line();
    printLine(54);

    char _ibns[28];
    printf("Nhập ISBN sách cần sửa: ");
    scanf(" %s", _ibns);

    int index = findBookByid(book_list, book_size, _ibns);
    if (index == -1)
    {
        printLine(54);
        begin_line();
        print_cell("** Không tìm thấy thông tin ISBD vừa nhập **", 54, true);
        end_line();
        printLine(54);
        return;
    }
    view_books(index, false);
    show_edit_book_menu(index);
}

void delete_book()
{
    printLine(54);
    begin_line();
    print_cell("** XÓA THÔNG TIN SÁCH **", 50, true);
    end_line();
    printLine(54);

    char _isbn[28];
    printf("Nhập ISBN  cần xóa: ");
    scanf(" %s", _isbn);

    int index = findBookByid(book_list, book_size, _isbn);
    if (index == -1)
    {
        printLine(54);
        begin_line();
        print_cell("** Không tìm thấy thông tin **", 50, true);
        end_line();
        printLine(54);
        return;
    }

    deleteBookbyID(&book_list, &book_size, _isbn);

    book_size--;
    printLine(54);
    begin_line();
    print_cell("** Xóa thành công **", 50, true);
    end_line();
    printLine(54);
}

void search_book_by_isbn()
{
    printLine(54);
    begin_line();
    print_cell("** TÌM KIẾM THEO ISBN **", 50, true);
    end_line();
    printLine(54);

    char _isbn[28];
    printf("Nhập ISBN: ");
    scanf(" %27[^\n]", _isbn);

    int length = 0;
    int *indexs = findBooksByISBN(book_list, book_size, &length, _isbn);
    if (length == 0)
    {
        printLine(54);
        begin_line();
        char message[100] = " ** Không tìm thấy sách có ISBN:";
        strcat(message, _isbn);
        strcat(message, " **");
        print_cell(message, 50, true);
        end_line();
        printLine(54);
        return;
    }

    bprint_title();
    for (int i = 0; i < (length); i++)
    {
        print_book(indexs[i]);
    }
    printLine(bwidth_line);
    free(indexs);
}

void search_book_by_name()
{
    printLine(54);
    begin_line();
    print_cell("** TÌM THEO TÊN SÁCH **", 50, true);
    end_line();
    printLine(54);

    char _name[100];
    printf("Nhập tên sách: ");
    scanf(" %99[^\n]", _name);

    int length = 0;
    int *indexs = findBookByTitle(book_list, book_size, &length, _name);
    if (length == 0)
    {
        printLine(54);
        begin_line();
        char message[100] = " ** Không tìm thấy sách có tên:";
        strcat(message, _name);
        strcat(message, " **");
        print_cell(message, 50, true);
        end_line();
        printLine(54);
        return;
    }

    bprint_title();
    for (int i = 0; i < (length); i++)
    {
        print_book(indexs[i]);
    }
    printLine(bwidth_line);
    free(indexs);
}

bool books_show_menu_function()
{
    printf("-----------------------QUẢN LÝ SÁCH-----------------------\n");

    char menu[8][100] = {"Xem danh sách các sách trong thư viện",
                         "Thêm sách",
                         "Chỉnh sửa thông tin một quyển sách",
                         "Xóa thông tin sách",
                         "Tìm kiếm sách theo ISBN",
                         "Tìm kiếm sách theo tên sách",
                         "Quay lại",
                         "Thoát chương trình"};
    int length = sizeof(menu) / sizeof(menu[0]);
    for (int i = 0; i < length; i++)
    {
        printf("%d.%s\n", i, menu[i]);
    }
    printf("-------------------------------------------------------\n");

    int choice = choice_action(length);

    bool isContinue = choice != 6;
    if (choice == 7)
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
        return handle_books_menu(choice);
    }
}

bool handle_books_menu(int choice)
{
    switch (choice)
    {
    case 0:
        view_books(0, true);
        break;
    case 1:
        add_book();
        break;
    case 2:
        edit_book();
        break;
    case 3:
        delete_book();
        break;
    case 4:
        search_book_by_isbn();
        break;
    case 5:
        search_book_by_name();
        break;
    default:
        break;
    }
    return books_show_menu_function();
}

int get_book_size()
{
    return book_size;
}

int get_price_book(char *code)
{
    int index = findBookByid(book_list, book_size, code);
    if (index == -1)
    {
        return 0;
    }
    return book_list[index].price;
}

char **get_isbns_book()
{
    char **isbns = (char **)malloc(book_size * sizeof(char *));
    for (int i = 0; i < book_size; i++)
    {
        isbns[i] = book_list[i].isbn;
    }
    return isbns;
}

int get_total_book()
{
    int total = 0;
    for (int i = 0; i < book_size; i++)
    {
        total += book_list[i].quantity;
    }
    return total;
}

int get_total_book_by_category(char *category)
{
    int total = 0;
    for (int i = 0; i < book_size; i++)
    {
        struct Book book = book_list[i];
        if (strcmp(book.category, category) == 0)
        {
            total += book.quantity;
        }
    }
    return total;
}

void show_statistics_category()
{
    int size = 0;
    char **categories = (char **)malloc(size * sizeof(char *));
    for (int i = 0; i < book_size; i++)
    {
        if (findExactlyIndex(categories, size, book_list[i].category) == -1)
        {
            categories = addStringToArray(categories, &size, book_list[i].category);
        }
    }

    for (int i = 0; i < size; i++)
    {
        printf(" - %s: %d\n", categories[i], get_total_book_by_category(categories[i]));
    }
    free(categories);
}

void create_template_book()
{
    struct Book book1 = createBook("1234920112", "NHA GIA KIM", "Robust", "KIM DONG", "TRUYEN VIEN TUONG", 2000, 200000, 50);
    struct Book book2 = createBook("0930910", "lam viec dung", "thienn long", "Tre", "TAM LY", 2020, 350000, 100);
    struct Book book3 = createBook("9383993", "Harry Potter", "J.k", "KIM DONG", "Truyen", 2023, 455000, 1);
    addBookToList(&book_list, &book_size, book1);
    addBookToList(&book_list, &book_size, book2);
    addBookToList(&book_list, &book_size, book3);
}

struct Book createBook(char *isbn,
                       char *title,
                       char *author,
                       char *publisher,
                       char *category,
                       int year,
                       int price,
                       int quantity) {
    struct Book book;

    book.isbn = (char *)malloc(strlen(isbn) + 1);
    if (book.isbn != NULL) {
        strcpy(book.isbn, isbn);
    }
    book.title = (char *)malloc(strlen(title) + 1);
    if (book.title != NULL) {
        strcpy(book.title, title);
    }
    book.author = (char *)malloc(strlen(author) + 1);
    if (book.author != NULL) {
        strcpy(book.author, author);
    }
    book.publisher = (char *)malloc(strlen(publisher) + 1);
    if (book.publisher != NULL) {
        strcpy(book.publisher, publisher);
    }
    book.category = (char *)malloc(strlen(category) + 1);
    if (book.category != NULL) {
        strcpy(book.category, category);
    }
    book.year = year;
    book.price = price;
    book.quantity = quantity;
    return book;
};

void addBookToList(struct Book **books, int *num, struct Book new_book) {
    *num += 1;
    *books = (struct Book *)realloc(*books, *num * sizeof(struct Book));
    if (*books == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    (*books)[*num - 1] = new_book;
};

int *findBookByTitle(struct Book *book, int num, int *return_arr_length, const char *title) {
    int *indexs = (int *)malloc(num * sizeof(int));
    int count = 0;
    for (int i = 0; i < num; i++) {
        if (strstr(book[i].title, title) != NULL) {
            indexs[count] = i;
            count++;
        }
    }
    *return_arr_length = count;
    return indexs;
};

int *findBooksByISBN(struct Book *book, int num, int *return_arr_length, const char *isbn) {
    int *indexs = (int *)malloc(num * sizeof(int));
    int count = 0;
    for (int i = 0; i < num; i++) {
        if (strstr(book[i].isbn, isbn) != NULL) {
            indexs[count] = i;
            count++;
        }
    }
    *return_arr_length = count;
    return indexs;
};

int findBookByid(struct Book *book, int num, const char *isbn) {
    for (int i = 0; i < num; i++) {
        if (strcmp(book[i].isbn, isbn) == 0) {
            return i;
        }
    }
    return -1;
};
void deleteBookbyID(struct Book **book, int *num, const char *isbn) {
    int index = findBookByid(*book, *num, isbn);
    if (index == -1) {
        return;
    }
    for (int i = index; i < *num - 1; i++) {
        (*book)[i] = (*book)[i + 1];
    }
    *num -= 1;
    *book = (struct Book *)realloc(*book, *num * sizeof(struct Book));
    if (*book == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
};