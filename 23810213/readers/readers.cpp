#include "readers.h"
#include "../function/function.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>

int width_line = 0;
int column_with[8];
int reader_size = 0;
struct Reader *reader_list = NULL;

/// @brief readers menu
char menu[8][100] = {"Xem danh sách độc giả trong thư viện",
                     "Thêm độc giả",
                     "Chỉnh sửa thông tin một độc giả",
                     "Xóa thông tin một độc giả",
                     "Tìm kiếm độc giả theo CMND",
                     "Tìm kiếm sách theo họ tên",
                     "Quay lại",
                     "Thoát chương trình"};

char edit_menu[6][100] = {"Sửa tên",
                          "Sửa CMND",
                          "Sửa ngày sinh",
                          "Sửa giới tính",
                          "Sửa địa chỉ",
                          "Quay lại"};


void calculator_column_with(int *arr)
{
    int id_width = 7;
    int name_width = 28;
    int cmnd_width = 13;
    int birthdate_width = 12;
    int gender_width = 10;
    int date_create_width = 12;
    int date_expired_width = 12;
    int address_width = 20;
    for (int i = 0; i < reader_size; ++i)
    {
        struct Reader reader = reader_list[i];
        // reader_name
        if (name_width < utf8_strlen(reader.reader_name))
        {
            name_width = utf8_strlen(reader.reader_name);
        }
        // cmnd
        if (cmnd_width < utf8_strlen(reader.cmnd))
        {
            cmnd_width = utf8_strlen(reader.cmnd);
        }

        // address*
        if (address_width < utf8_strlen(reader.address))
        {
            address_width = utf8_strlen(reader.address);
        }
    }
    arr[0] = id_width;
    arr[1] = name_width;
    arr[2] = cmnd_width;
    arr[3] = birthdate_width;
    arr[4] = gender_width;
    arr[5] = date_create_width;
    arr[6] = date_expired_width;
    arr[7] = address_width + 3;
}

void print_title()
{
    width_line = 0;
    calculator_column_with(column_with);
    int size = sizeof(column_with) / sizeof(column_with[0]);
    for (int i = 0; i < 8; ++i)
    {
        width_line += column_with[i] + 3; // 2 là 2 ký tự space 2 đầu + 1 ký tự |
    }
    width_line += 1; // 1 là 1 ký tự | endline

    printLine(width_line);
    begin_line();

    // 2 là 2 ký tự space 2 đầu, 2 là 2 ký tự | 2 đầu
    print_cell("DANH SÁCH ĐỘC GIẢ", width_line - 4, true);
    end_line();
    printLine(width_line);

    begin_line();
    print_cell("ID", column_with[0], true);
    begin_line();
    print_cell("HỌ TÊN", column_with[1], true);
    begin_line();
    print_cell("CMND", column_with[2], true);
    begin_line();
    print_cell("NGÀY SINH", column_with[3], true);
    begin_line();
    print_cell("GIỚI TÍNH", column_with[4], true);
    begin_line();
    print_cell("NGÀY TẠO THẺ", column_with[5], true);
    begin_line();
    print_cell("NGÀY HẾT HẠN", column_with[6], true);
    begin_line();
    print_cell("ĐỊA CHỈ", column_with[7], true);
    end_line();
    printLine(width_line);
}

void print_reader(int index)
{
    struct Reader reader = reader_list[index];
    char result[10];
    snprintf(result, sizeof(result), "%d", reader.id);

    begin_line();
    print_cell(result, column_with[0], true);
    begin_line();
    print_cell(reader.reader_name, column_with[1], false);
    begin_line();
    print_cell(reader.cmnd, column_with[2], false);
    begin_line();
    print_cell(reader.birthdate, column_with[3], true);
    begin_line();
    print_cell(reader.gender, column_with[4], true);
    begin_line();
    print_cell(reader.date_create_card, column_with[5], true);
    begin_line();
    print_cell(reader.date_expire_card, column_with[6], true);
    begin_line();
    print_cell(reader.address, column_with[7], false);
    end_line();
}

void view_readers(int index, bool showAll)
{
    print_title();
    if (reader_size == 0)
    {
        begin_line();
        print_cell("**** Không có độc giả nào trong thư viện ****", width_line - 4, true);
        end_line();
        printLine(width_line);
        return;
    }
    if (showAll)
    {
        // In dữ liệu từng dòng
        for (int i = reader_size - 1; i >= 0; --i)
        {
            print_reader(i);
        }
    }
    else
    {
        print_reader(index);
    }

    // Kết thúc bảng
    printLine(width_line);
}

void add_reader()
{
    printLine(54);
    begin_line();
    print_cell("** THÊM ĐỘC GIẢ **", 50, true);
    end_line();
    printLine(54);

    char full_name[28];
    char _cmnd[10];
    char _birthdate[11];
    char _gender[10];
    char _address[100];
    char current_date[11];
    char expired_date[11];

    /// @brief date expire card for readers, this is date create card + 2 year
    // char date_expire_card[][11] = {"01/01/2022", "02/02/2022", "03/03/2022", "04/04/2022"};

    // Nhập họ tên từ bàn phím
    printf("Nhập họ tên: ");
    scanf(" %27[^\n]", full_name); // Sử dụng %[^\n] để cho phép nhập cả dấu cách

    // Nhập hCMND từ bàn phím
    printf("CMND (9 số): ");
    scanf(" %s", _cmnd);

    // Nhập ngày tháng năm sinh
    printf("Nhâp ngày sinh (dd/mm/yyyy): ");
    scanf(" %s", _birthdate);

    // Nhập giới tính
    printf("Nhập giới tính (nam/nữ): ");
    scanf(" %9[^\n]", _gender); // Cần có khoảng trắng trước %c để loại bỏ ký tự new line còn trong bộ nhớ đệm

    // Nhập hCMND từ bàn phím
    printf("Địa chỉ: ");
    scanf(" %99[^\n]", _address);


    // Lấy thời gian hiện tại
    time_t current_time;
    time(&current_time);

    // Chuyển đổi thời gian hiện tại thành cấu trúc tm
    struct tm *create_time = localtime(&current_time);
    int day = create_time->tm_mday, month = create_time->tm_mon + 1, year = create_time->tm_year + 1900;
    
    snprintf(current_date, 11, "%02d/%02d/%d", day, month, year);
    snprintf(expired_date, 11, "%02d/%02d/%d", day, month, year + 4);

    // realloc data list
    int newId = 1;
    if (reader_size > 0)
    {
        newId = reader_list[reader_size - 1].id + 1;
    }
    struct Reader reader = createReader(newId, full_name, _cmnd, _birthdate, _gender, _address, current_date, expired_date);
    addReader(&reader_list, &reader_size, reader);

    view_readers(0, true);
    view_readers(reader_size - 1, false);
}

void edit_reader()
{
    if (reader_size == 0)
    {
        printLine(54);
        begin_line();
        print_cell("** Không có độc giả nào trong thư viện **", 54, true);
        end_line();
        printLine(54);
        return;
    }
    view_readers(0, true);
    printLine(54);
    begin_line();
    print_cell("** SỬA THÔNG TIN ĐỘC GIẢ **", 50, true);
    end_line();
    printLine(54);

    int id;
    printf("Nhập ID độc giả cần chỉnh sửa: ");
    scanf(" %d", &id);

    // int index = findIndex(ids, reader_size, id);
    int index = findPersonByid(reader_list, reader_size, id);
    if (index == -1)
    {
        printLine(54);
        begin_line();
        print_cell("** Không tìm thấy độc giả có ID đã nhập **", 54, true);
        end_line();
        printLine(54);
        return;
    }
    view_readers(index, false);
    show_edit_reader_menu(index);
}

void show_edit_reader_menu(int index)
{
    printf("------------------DANH MỤC CẦN SỬA----------------\n");

    int length = sizeof(edit_menu) / sizeof(edit_menu[0]);
    for (int i = 0; i < length; i++)
    {
        printf("%d.%s\n", i, edit_menu[i]);
    }
    printf("-------------------------------------------------------\n");

    int choice = choice_action(length);
    struct Reader editReader = reader_list[index];

    switch (choice)
    {
    case 0:
        char full_name[28];
        printf("Nhập họ tên: ");
        scanf(" %27[^\n]", full_name);
        strcpy(editReader.reader_name, full_name);
        break;
    case 1:
        char _cmnd[10];
        printf("CMND (9 số): ");
        scanf(" %s", _cmnd);
        strcpy(editReader.cmnd, _cmnd);
        break;
    case 2:
        char _birthdate[11];
        printf("Nhâp ngày sinh (dd/mm/yyyy): ");
        scanf(" %s", _birthdate);
        strcpy(editReader.birthdate, _birthdate);
        break;
    case 3:
        char _gender[4];
        printf("Nhập giới tính (nam/nữ): ");
        scanf(" %s", _gender);
        strcpy(editReader.gender, _gender);
        break;
    case 4:
        char _address[100];
        printf("Địa chỉ: ");
        scanf(" %99[^\n]", _address);
        strcpy(editReader.address, _address);
        break;
    }
    printLine(54);
    begin_line();
    print_cell("** THÔNG TIN ĐÃ SỬA **", 50, true);
    end_line();
    printLine(54);
    view_readers(index, false);
}

void delete_reader()
{
    view_readers(0, true);
    printLine(54);
    begin_line();
    print_cell("** XÓA THÔNG TIN ĐỘC GIẢ **", 50, true);
    end_line();
    printLine(54);

    int id;
    printf("Nhập ID độc giả cần xóa: ");
    scanf(" %d", &id);

    int index = findPersonByid(reader_list, reader_size, id);
    if (index == -1)
    {
        printLine(54);
        begin_line();
        print_cell("** Không tìm thấy thông tin độc giả **", 50, true);
        end_line();
        printLine(54);
        return;
    }
    deletePersonbyID(&reader_list, &reader_size, id);
    printLine(54);
    begin_line();
    print_cell("** Đã xóa độc giả thành công **", 50, true);
    end_line();
    printLine(54);
}

void search_reader_by_cmnd()
{
    view_readers(0, true);
    printLine(54);
    begin_line();
    print_cell("** TIM DOC GIA THEO CMND **", 50, true);
    end_line();
    printLine(54);

    char _cmnd[10];
    printf("CMND (9 số): ");
    scanf(" %s", _cmnd);

    int length;
    int *indexs = findPersonByCmnd(reader_list, reader_size, &length, _cmnd);
    if (length == 0)
    {
        printLine(54);
        begin_line();
        char message[100] = " ** Không tìm thấy độc giả có CMND: ";
        strcat(message, _cmnd);
        strcat(message, " **");

        print_cell(message, 50, true);
        end_line();
        printLine(54);
        return;
    }
    printLine(54);
    begin_line();
    print_cell(" ** Thông tin độc giả được tìm thấy **", 50, true);
    end_line();
    printLine(54);

    print_title();
    for (int i = 0; i < (length); i++)
    {
        print_reader(indexs[i]);
    }
    printLine(width_line);
    free(indexs);
}

void search_book_by_reader_name()
{
    view_readers(0, true);
    printLine(54);
    begin_line();
    print_cell("** TÌM KIẾM ĐỘC GIẢ THEO TÊN **", 50, true);
    end_line();
    printLine(54);

    char full_name[28];
    printf("Nhập họ tên: ");
    scanf(" %27[^\n]", full_name);

    int length = 0;
    int *indexs = findPersonByName(reader_list, reader_size, &length, full_name);
    if (length == 0)
    {
        printLine(54);
        begin_line();
        char message[100] = " ** Không tìm thấy độc gỉa có TEN:";
        strcat(message, full_name);
        strcat(message, " **");

        print_cell(message, 50, true);
        end_line();
        printLine(54);
        return;
    }
    printLine(54);
    begin_line();
    print_cell(" ** Thông tin độc giả được tìm thấy **", 50, true);
    end_line();
    printLine(54);

    print_title();
    for (int i = 0; i < (length); i++)
    {
        print_reader(indexs[i]);
    }
    printLine(width_line);
    free(indexs);
}

/// @brief show readers menu
/// @return true if user want to continue, false if user want to exit
/// loop until user want to exit
bool readers_show_menu_functions()
{
    printf("--------------------QUẢN LÝ ĐỘC GIẢ--------------------\n");

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
        return handle_readers_menu(choice);
    }
}

/// @brief handle readers menu
/// @param choice user choice
/// @return true if user want to continue, false if user want to exit
bool handle_readers_menu(int choice)
{
    switch (choice)
    {
    case 0:
        view_readers(0, true);
        break;
    case 1:
        add_reader();
        break;
    case 2:
        edit_reader();
        break;
    case 3:
        delete_reader();
        break;
    case 4:
        search_reader_by_cmnd();
        break;
    case 5:
        search_book_by_reader_name();
        break;
    default:
        break;
    }
    return readers_show_menu_functions();
}
int get_reader_size()
{
    return reader_size;
}

int *get_ids_reader()
{
    int *indexs = (int *)malloc(reader_size * sizeof(int));
    for (int i = 0; i < reader_size; i++){
        indexs[i] = reader_list[i].id;
    }
    return indexs;
}

int get_total_reader()
{
    return reader_size;
}

void show_statistics_gender()
{
    int totalMale = 0;
    int totalFemale = 0;
    for (int i = 0; i < reader_size; i++)
    {
        if (strcmp(reader_list[i].gender, "nam") == 0)
        {
            totalMale++;
        }
        else
        {
            totalFemale++;
        }
    }
    printf(" - Nam: %d\n", totalMale);
    printf(" - Nữ: %d\n", totalFemale);
}

char *get_reader_name(int id)
{
    int index = findPersonByid(reader_list, reader_size, id);
    if (index == -1)
    {
        char *result = (char *)malloc(1);
        return result;
    }
    return reader_list[index].reader_name;
}

struct Reader createReader(int id, char *name, char *cmnd, char *birthdate, char *gender, char *address, char *date_create_card, char *date_expire_card)
{
    struct Reader reader;
    reader.id = id;

    // Cấp phát bộ nhớ cho tên và sao chép tên
    reader.reader_name = (char *)malloc(strlen(name) + 1);
    if (reader.reader_name  != NULL) {
        strcpy(reader.reader_name, name);
    }
    reader.cmnd = (char *)malloc(strlen(cmnd) + 1);
    if (reader.cmnd != NULL) {
        strcpy(reader.cmnd, cmnd);
    }
    reader.birthdate = (char *)malloc(strlen(birthdate) + 1);
    if (reader.birthdate != NULL) {
        strcpy(reader.birthdate, birthdate);
    }
    reader.gender = (char *)malloc(strlen(gender) + 1);
    if (reader.gender != NULL) {
        strcpy(reader.gender, gender);
    }
    reader.address = (char *)malloc(strlen(address) + 1);
    if (reader.address != NULL) {
        strcpy(reader.address, address);
    }
    reader.date_create_card = (char *)malloc(strlen(date_create_card) + 1);
    if (reader.date_create_card != NULL) {
        strcpy(reader.date_create_card, date_create_card);
    }   
    reader.date_expire_card = (char *)malloc(strlen(date_expire_card) + 1);
    if (reader.date_expire_card != NULL) {
        strcpy(reader.date_expire_card, date_expire_card);
    }
    return reader;
}

void create_template_reader()
{
    struct Reader reader = createReader(1, "Nguyễn trung quang", "215151911", "19/11/2002", "nam", "hoai thanh-hoai nhon-binh dinh", "20/04/2023", "20/04/2027");
    struct Reader reader1 = createReader(2, "Nguyen thi ngoc", "27161721", "19/11/1996", "nữ", "My an- my k- phu cat", "20/04/2024", "20/04/2028");
    struct Reader reader2 = createReader(3, "Thai thi my lan", "052091002214", "19/11/1996", "nam", "My an- my k- phu cat", "20/04/2024", "20/04/2028");
    struct Reader reader3 = createReader(4, "Trần văn trà", "27161721", "19/11/1996", "nữ", "My an- my k- phu cat", "20/04/2024", "20/04/2028");
    addReader(&reader_list, &reader_size, reader);
    addReader(&reader_list, &reader_size, reader1);
    addReader(&reader_list, &reader_size, reader2);
    addReader(&reader_list, &reader_size, reader3);
}

void addReader(struct Reader **people, int *num_people, struct Reader new_person)
{
    // Cấp phát lại bộ nhớ cho mảng để tăng kích thước nếu cần
    *people = (struct Reader *)realloc(*people, (*num_people + 1) * sizeof(struct Reader));
    if (*people == NULL)
    {
        printf("Không đủ bộ nhớ!\n");
        return;
    }

    // Thêm người mới vào mảng
    (*people)[*num_people] = new_person;

    // Tăng số lượng người trong mảng lên 1
    (*num_people)++;
}

// Hàm tìm kiếm một người theo tên trong mảng
int *findPersonByName(struct Reader *people, int num_people, int *return_arr_length, const char *name)
{
    (*return_arr_length) = 0;
    int *indexs = (int *)malloc(1 * sizeof(int));
    for (int i = 0; i < num_people; i++)
    {
        if (strstr(people[i].reader_name, name) != NULL)
        {
            (*return_arr_length)++;

            indexs = (int *)realloc(indexs, (*return_arr_length) * sizeof(int));
            indexs[(*return_arr_length) - 1] = i;
        }
    }
    return indexs;
}

int *findPersonByCmnd(struct Reader *people, int num_people, int *return_arr_length, const char *cmnd)
{
    (*return_arr_length) = 0;
    int *indexs = (int *)malloc(1 * sizeof(int));
    for (int i = 0; i < num_people; i++)
    {
        if (strstr(people[i].cmnd, cmnd) != NULL)
        {
            (*return_arr_length)++;

            indexs = (int *)realloc(indexs, (*return_arr_length) * sizeof(int));
            indexs[(*return_arr_length) - 1] = i;
        }
    }
    return indexs;
}

int findPersonByid(struct Reader *people, int num_people, int id)
{
    for (int i = 0; i < num_people; i++)
    {
        if (people[i].id == id)
        {
            return i; // Trả về chỉ số của người tìm thấy
        }
    }
    return -1; // Trả về -1 nếu không tìm thấy
}

// Hàm xóa một đối tượng Person khỏi mảng
void deletePersonbyID(struct Reader **people, int *num_people, int id)
{
    int index = findPersonByid(*people, *num_people, id);
    if (index == -1)
    {
        printf("Không tìm thấy người có id %d.\n", id);
        return;
    }

    // Dịch chuyển các phần tử còn lại để lấp chỗ trống
    for (int i = index; i < *num_people - 1; i++)
    {
        (*people)[i] = (*people)[i + 1];
    }

    // Giảm kích thước của mảng
    *people = (struct Reader *)realloc(*people, (*num_people - 1) * sizeof(struct Reader));
    if (*people == NULL && *num_people - 1 > 0)
    {
        printf("Không đủ bộ nhớ!\n");
        return;
    }

    // Giảm số lượng người trong mảng đi 1
    (*num_people)--;
}