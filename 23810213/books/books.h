#pragma once
// a. Xem danh sách các sách trong thư viện
// b. Thêm sách
// c. Chỉnh sửa thông tin một quyển sách
// d. Xóa thông tin sách
// e. Tìm kiếm sách theo ISBN
// f. Tìm kiếm sách theo tên sách

struct Book
{
    char *isbn;
    char *title;
    char *author;
    char *publisher;
    char *category;
        // publishing year books
    int year;
    int price;
    int quantity;
};

/// @brief show all books
void view_books(int index, bool showAll);

/// @brief show all functions of books
bool books_show_menu_function();

/// @brief handle books menu
bool handle_books_menu(int choice);

int get_book_size();

void create_template_book();

char **get_isbns_book();

int get_price_book(char *code);

int get_total_book();

void show_statistics_category();

/// do an 2
struct Book createBook(char *isbn,
                       char *title,
                       char *author,
                       char *publisher,
                       char *category,
                       int year,
                       int price,
                       int quantity);
void addBookToList(struct Book **books, int *num, struct Book new_book);

int *findBookByTitle(struct Book *book, int num, int *return_arr_length, const char *title);

int *findBooksByISBN(struct Book *book, int num, int *return_arr_length, const char *isbn);

int findBookByid(struct Book *book, int num, const char *isbn);
void deleteBookbyID(struct Book **book, int *num, const char *isbn);