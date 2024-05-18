#include "books.h"
#include "../function/function.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int bwidth_line = 0;
int bcolumn_with[8];
char *book_file = "files/books.txt";

void bcalculator_column_with(int *arr)
{
    int id_width = 15;
    int name_width = 28;
    int authorW = 20;
    int publisherW = 20;
    int yearW = 8;
    int priceW = 10;
    int quantityW = 10;
    int type_width = 20;

    struct Book *book_list;
    int book_size = read_books_from_file(book_file, &book_list);

    for (int i = 0; i < book_size; ++i)
    {
        struct Book book = book_list[i];
        // name
        if (name_width < utf8_strlen(book.title))
        {
            name_width = utf8_strlen(book.title);
        }
        // authorW
        if (authorW < utf8_strlen(book.author) + 4)
        {
            authorW = utf8_strlen(book.author) + 4;
        }
        // publisher*
        if (publisherW < utf8_strlen(book.publisher))
        {
            publisherW = utf8_strlen(book.publisher);
        }
        // type_width
        if (type_width < utf8_strlen(book.category) + 4)
        {
            type_width = utf8_strlen(book.category) + 4;
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
    free_books(book_list, book_size);
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
    print_cell("NĂM SX", bcolumn_with[4], true);
    begin_line();
    print_cell("THỂ LOẠI", bcolumn_with[5], true);
    begin_line();
    print_cell("GÍA SÁCH", bcolumn_with[6], true);
    begin_line();
    print_cell("SỐ LƯỢNG", bcolumn_with[7], true);
    end_line();
    printLine(bwidth_line);
}

void print_book(struct Book book)
{
    char result[10];
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

void view_books(struct Book book, bool showAll)
{
    struct Book *book_list;
    int book_size = read_books_from_file(book_file, &book_list);
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
            print_book(book_list[i]);
        }
    }
    else
    {
        print_book(book);
    }
    free_books(book_list, book_size);
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
    write_book_to_file(book_file, new_book);
    free_book(&new_book);
     struct Book book;
    view_books(book, true);
}

void show_edit_book_menu(struct Book book)
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
    update_book_in_file(book_file, book.isbn, book);
    view_books(book, false);
}

void edit_book()
{
    struct Book *book_list;
    int book_size = read_books_from_file(book_file, &book_list);
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
    view_books(book_list[index], false);
    show_edit_book_menu(book_list[index]);
    free_books(book_list, book_size);
}

void delete_book()
{
    struct Book *book_list;
    int book_size = read_books_from_file(book_file, &book_list);
    printLine(54);
    begin_line();
    print_cell("** XÓA THÔNG TIN SÁCH **", 50, true);
    end_line();
    printLine(54);

    char _isbn[28];
    printf("Nhập ISBN  cần xóa: ");
    scanf(" %s", _isbn);

    int index = delete_book_in_file(book_file, _isbn);;
    if (index == -1)
    {
        printLine(54);
        begin_line();
        print_cell("** Không tìm thấy thông tin **", 50, true);
        end_line();
        printLine(54);
        return;
    }

    printLine(54);
    begin_line();
    print_cell("** Xóa thành công **", 50, true);
    end_line();
    printLine(54);
    free_books(book_list, book_size);
}

void search_book_by_isbn()
{
    struct Book *book_list;
    int book_size = read_books_from_file(book_file, &book_list);
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
        print_book(book_list[indexs[i]]);
    }
    printLine(bwidth_line);
    free(indexs);
    free_books(book_list, book_size);
}

void search_book_by_name()
{
    struct  Book *book_list;
    int book_size = read_books_from_file(book_file, &book_list);
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
        print_book(book_list[indexs[i]]);
    }
    printLine(bwidth_line);
    free(indexs);
    free_books(book_list, book_size);
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
        struct Book book;
        view_books(book, true);
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
    struct Book *book_list;
    int book_size = read_books_from_file(book_file, &book_list);
    free_books(book_list, book_size);
    return book_size;
}

int get_price_book(char *code)
{
    struct Book *book_list;
    int book_size = read_books_from_file(book_file, &book_list);
    int index = findBookByid(book_list, book_size, code);
    if (index == -1)
    {
        return 0;
    }
    int price = book_list[index].price;
    free_books(book_list, book_size);
    return book_list[index].price;
}

char **get_isbns_book()
{
    struct Book *book_list;
    int book_size = read_books_from_file(book_file, &book_list);
    char **isbns = (char **)malloc(book_size * sizeof(char *));
    for (int i = 0; i < book_size; i++)
    {
        isbns[i] = book_list[i].isbn;
    }
    free_books(book_list, book_size);
    return isbns;
}

int get_total_book()
{
    struct Book *book_list;
    int book_size = read_books_from_file(book_file, &book_list);
    int total = 0;
    for (int i = 0; i < book_size; i++)
    {
        total += book_list[i].quantity;
    }
    free_books(book_list, book_size);
    return total;
}

int get_total_book_by_category(char *category)
{
    struct Book *book_list;
    int book_size = read_books_from_file(book_file, &book_list);
    int total = 0;
    for (int i = 0; i < book_size; i++)
    {
        struct Book book = book_list[i];
        if (strcmp(book.category, category) == 0)
        {
            total += book.quantity;
        }
    }
    free_books(book_list, book_size);
    return total;
}

void show_statistics_category()
{
    struct Book *book_list;
    int book_size = read_books_from_file(book_file, &book_list);
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
    free_books(book_list, book_size);
}

struct Book createBook(char *isbn,
                       char *title,
                       char *author,
                       char *publisher,
                       char *category,
                       int year,
                       int price,
                       int quantity)
{
    struct Book book;

    book.isbn = (char *)malloc(strlen(isbn) + 1);
    if (book.isbn != NULL)
    {
        strcpy(book.isbn, isbn);
    }
    book.title = (char *)malloc(strlen(title) + 1);
    if (book.title != NULL)
    {
        strcpy(book.title, title);
    }
    book.author = (char *)malloc(strlen(author) + 1);
    if (book.author != NULL)
    {
        strcpy(book.author, author);
    }
    book.publisher = (char *)malloc(strlen(publisher) + 1);
    if (book.publisher != NULL)
    {
        strcpy(book.publisher, publisher);
    }
    book.category = (char *)malloc(strlen(category) + 1);
    if (book.category != NULL)
    {
        strcpy(book.category, category);
    }
    book.year = year;
    book.price = price;
    book.quantity = quantity;
    return book;
};

void addBookToList(struct Book **books, int *num, struct Book new_book)
{
    *num += 1;
    *books = (struct Book *)realloc(*books, *num * sizeof(struct Book));
    if (*books == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    (*books)[*num - 1] = new_book;
};

int *findBookByTitle(struct Book *book, int num, int *return_arr_length, const char *title)
{
    int *indexs = (int *)malloc(num * sizeof(int));
    int count = 0;
    for (int i = 0; i < num; i++)
    {
        if (strstr(book[i].title, title) != NULL)
        {
            indexs[count] = i;
            count++;
        }
    }
    *return_arr_length = count;
    return indexs;
};

int *findBooksByISBN(struct Book *book, int num, int *return_arr_length, const char *isbn)
{
    int *indexs = (int *)malloc(num * sizeof(int));
    int count = 0;
    for (int i = 0; i < num; i++)
    {
        if (strstr(book[i].isbn, isbn) != NULL)
        {
            indexs[count] = i;
            count++;
        }
    }
    *return_arr_length = count;
    return indexs;
};

int findBookByid(struct Book *book, int num, const char *isbn)
{
    for (int i = 0; i < num; i++)
    {
        if (strcmp(book[i].isbn, isbn) == 0)
        {
            return i;
        }
    }
    return -1;
};
void deleteBookbyID(struct Book **book, int *num, const char *isbn)
{
    int index = findBookByid(*book, *num, isbn);
    if (index == -1)
    {
        return;
    }
    for (int i = index; i < *num - 1; i++)
    {
        (*book)[i] = (*book)[i + 1];
    }
    *num -= 1;
    *book = (struct Book *)realloc(*book, *num * sizeof(struct Book));
    if (*book == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
};

void write_books_to_file(const char *filename, struct Book *books, int count)
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

    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("Failed to open file");
        return;
    }
    // Write the number of books
    fprintf(file, "%d\n", count);

    // Write each book's information
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%s\n", books[i].isbn);
        fprintf(file, "%s\n", books[i].title);
        fprintf(file, "%s\n", books[i].author);
        fprintf(file, "%s\n", books[i].publisher);
        fprintf(file, "%s\n", books[i].category);
        fprintf(file, "%d\n", books[i].year);
        fprintf(file, "%d\n", books[i].price);
        fprintf(file, "%d\n", books[i].quantity);
        fprintf(file, "%s\n", "----------------------------------");
    }

    fclose(file);
}
void write_book_to_file(const char *filename, struct Book book)
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
    // Write the number of books
    fprintf(file, "%s\n", book.isbn);
    fprintf(file, "%s\n", book.title);
    fprintf(file, "%s\n", book.author);
    fprintf(file, "%s\n", book.publisher);
    fprintf(file, "%s\n", book.category);
    fprintf(file, "%d\n", book.year);
    fprintf(file, "%d\n", book.price);
    fprintf(file, "%d\n", book.quantity);
    fprintf(file, "%s\n", "----------------------------------");
    fclose(file);
}
int read_books_from_file(const char *filename, struct Book **books)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Failed to open file");
        return -1;
    }

    int count;
    if (fscanf(file, "%d\n", &count) != 1)
    {
        perror("Failed to read the number of readers");
        fclose(file);
        return -1;
    }


    // Allocate memory for the array of books
    *books = (struct Book *)malloc(count * sizeof(struct Book));
    if (books == NULL)
    {
        perror("Failed to allocate memory for books");
        fclose(file);
        return -1;
    }

    // Read each book's information
    for (int i = 0; i < count; i++)
    {
        char buffer[256];
        struct Book *book = &(*books)[i];

        // Read and allocate memory for isbn
        if (fgets(buffer, sizeof(buffer), file) == NULL)
            goto read_error;
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
        book->isbn = strdup(buffer);

        // Read and allocate memory for title
        if (fgets(buffer, sizeof(buffer), file) == NULL)
            goto read_error;
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
        book->title = strdup(buffer);

        // Read and allocate memory for author
        if (fgets(buffer, sizeof(buffer), file) == NULL)
            goto read_error;
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
        book->author = strdup(buffer);

        // Read and allocate memory for publisher
        if (fgets(buffer, sizeof(buffer), file) == NULL)
            goto read_error;
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
        book->publisher = strdup(buffer);

        // Read and allocate memory for category
        if (fgets(buffer, sizeof(buffer), file) == NULL)
            goto read_error;
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
        book->category = strdup(buffer);

        // Read year
        if (fscanf(file, "%d\n", &book->year) != 1)
            goto read_error;
        // Read price
        if (fscanf(file, "%d\n", &book->price) != 1)
            goto read_error;
        // Read quantity
        if (fscanf(file, "%d\n", &book->quantity) != 1)
            goto read_error;
        // Read line separator
        char line[256];
        if (fscanf(file, "%255[^\n]\n", line) != 1)
            goto read_error;

    }

    fclose(file);
    return count;

read_error:
    perror("Failed to read book information");
    fclose(file);
    return count;
}

void free_book(struct Book *book)
{
    free(book->isbn);
    free(book->title);
    free(book->author);
    free(book->publisher);
    free(book->category);
}
void free_books(struct Book *books, int count)
{
    for (int i = 0; i < count; i++)
    {
        free_book(&books[i]);
    }
    free(books); // Free the array itself if it was dynamically allocated
}
void update_book_in_file(const char *filename, const char *isbn, struct Book new_data){
    struct Book *book_list;
    int book_size = read_books_from_file(filename, &book_list);
    int index = findBookByid(book_list, book_size, isbn);
    if (index == -1)
    {
        return;
    }
    book_list[index] = new_data;
    write_books_to_file(filename, book_list, book_size);
}

int delete_book_in_file(const char *filename, const char *isbn)
{
    struct Book *book_list;
    int book_size = read_books_from_file(filename, &book_list);
    int index = findBookByid(book_list, book_size, isbn);
    if (index == -1)
    {
        return -1;
    }
    deleteBookbyID(&book_list, &book_size, isbn);
    write_books_to_file(filename, book_list, book_size);
    return 0;
}