#include "readers.h"
#include "../function/function.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>

int width_line = 0;
int column_with[8];

char *reader_file = "files/readers.txt";

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
    
    struct Reader *reader_list;
    int reader_size = read_readers_from_file(reader_file, &reader_list);

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
    free_readers(reader_list, reader_size);
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

void print_reader(struct Reader reader)
{
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
    struct Reader *reader_list;
    int reader_size = read_readers_from_file(reader_file, &reader_list);
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
        print_reader(reader_list[i]);
        }
    }
    else
    {
        print_reader(reader_list[index]);
    }
    free_readers(reader_list, reader_size);
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

    struct Reader *reader_list;
    int reader_size = read_readers_from_file(reader_file, &reader_list);

    // realloc data list
    int newId = 1;
    if (reader_size > 0)
    {
        newId = reader_list[reader_size - 1].id + 1;
    }
    struct Reader reader = createReader(newId, full_name, _cmnd, _birthdate, _gender, _address, current_date, expired_date);
    write_reader_to_file(reader_file, reader);
    free_reader(&reader);
    free_readers(reader_list, reader_size);

    view_readers(0, true);
}

void edit_reader()
{
    struct Reader *reader_list;
    int reader_size = read_readers_from_file(reader_file, &reader_list);
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
    show_edit_reader_menu(index, reader_list, reader_size);
}

void show_edit_reader_menu(int index, Reader *reader_list, int reader_size)
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

    update_reader_in_file(reader_file, editReader.id, editReader);
    free_readers(reader_list, reader_size);

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

    int index = delete_reader_in_file(reader_file, id);
    if (index == -1)
    {
        printLine(54);
        begin_line();
        print_cell("** Không tìm thấy thông tin độc giả **", 50, true);
        end_line();
        printLine(54);
        return;
    }
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
    struct Reader *reader_list;
    int reader_size = read_readers_from_file(reader_file, &reader_list);

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
        int index = indexs[i];
        print_reader(reader_list[index]);
    }
    printLine(width_line);
    free(indexs);
    free_readers(reader_list, reader_size);
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
    struct Reader *reader_list;
    int reader_size = read_readers_from_file(reader_file, &reader_list);
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
        free_readers(reader_list, reader_size);
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
        int index = indexs[i];
        print_reader(reader_list[index]);
    }
    printLine(width_line);
    free(indexs);
    free_readers(reader_list, reader_size);
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
    struct Reader *readers;
    int count = read_readers_from_file(reader_file, &readers);
    free_readers(readers, count);
    return count;
}

int *get_ids_reader()
{
    struct Reader *readers;
    int reader_size = read_readers_from_file(reader_file, &readers);

    int *indexs = (int *)malloc(reader_size * sizeof(int));
    for (int i = 0; i < reader_size; i++)
    {
        indexs[i] = readers[i].id;
    }
    free_readers(readers, reader_size);
    return indexs;
}


void show_statistics_gender()
{
    struct Reader *readers;
    int reader_size = read_readers_from_file(reader_file, &readers);

    int totalMale = 0;
    int totalFemale = 0;
    for (int i = 0; i < reader_size; i++)
    {
        if (strcmp(readers[i].gender, "nam") == 0)
        {
            totalMale++;
        }
        else
        {
            totalFemale++;
        }
    }
    free_readers(readers, reader_size);
    printf(" - Nam: %d\n", totalMale);
    printf(" - Nữ: %d\n", totalFemale);
}

char *get_reader_name(int id)
{
    struct Reader *reader_list;
    int reader_size = read_readers_from_file(reader_file, &reader_list);

    int index = findPersonByid(reader_list, reader_size, id);
    if (index == -1)
    {
        char *result = (char *)malloc(1);
        return result;
    }
    char *name = reader_list[index].reader_name;
    free_readers(reader_list, reader_size);
    return name;
}

struct Reader createReader(int id, char *name, char *cmnd, char *birthdate, char *gender, char *address, char *date_create_card, char *date_expire_card)
{
    struct Reader reader;
    reader.id = id;

    // Cấp phát bộ nhớ cho tên và sao chép tên
    reader.reader_name = (char *)malloc(strlen(name) + 1);
    if (reader.reader_name != NULL)
    {
        strcpy(reader.reader_name, name);
    }
    reader.cmnd = (char *)malloc(strlen(cmnd) + 1);
    if (reader.cmnd != NULL)
    {
        strcpy(reader.cmnd, cmnd);
    }
    reader.birthdate = (char *)malloc(strlen(birthdate) + 1);
    if (reader.birthdate != NULL)
    {
        strcpy(reader.birthdate, birthdate);
    }
    reader.gender = (char *)malloc(strlen(gender) + 1);
    if (reader.gender != NULL)
    {
        strcpy(reader.gender, gender);
    }
    reader.address = (char *)malloc(strlen(address) + 1);
    if (reader.address != NULL)
    {
        strcpy(reader.address, address);
    }
    reader.date_create_card = (char *)malloc(strlen(date_create_card) + 1);
    if (reader.date_create_card != NULL)
    {
        strcpy(reader.date_create_card, date_create_card);
    }
    reader.date_expire_card = (char *)malloc(strlen(date_expire_card) + 1);
    if (reader.date_expire_card != NULL)
    {
        strcpy(reader.date_expire_card, date_expire_card);
    }
    return reader;
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

void write_readers_to_file(const char *filename, struct Reader *readers, int count)
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

    // Write the number of readers
    fprintf(file, "%d\n", count);

    // Write each reader's information
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%d\n", readers[i].id);
        fprintf(file, "%s\n", readers[i].reader_name);
        fprintf(file, "%s\n", readers[i].cmnd);
        fprintf(file, "%s\n", readers[i].birthdate);
        fprintf(file, "%s\n", readers[i].gender);
        fprintf(file, "%s\n", readers[i].address);
        fprintf(file, "%s\n", readers[i].date_create_card);
        fprintf(file, "%s\n", readers[i].date_expire_card);
        fprintf(file, "%s\n", "----------------------------------");
    }

    fclose(file);
}

void write_reader_to_file(const char *filename, struct Reader reader)
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
    if (file == NULL) {
        perror("Error opening file");
        return ;
    }
    // Read the count of readers
    int count;
    if (fscanf(file, "%d\n", &count) != 1) {
        perror("Error reading count of readers");
        fclose(file);
        return ;
    }
    // Update the count of readers
    count++;
    // Move the file pointer to the beginning to overwrite the count
    rewind(file);
    fprintf(file, "%d\n", count);

    // Move the file pointer to the end of the file
    if (fseek(file, 0, SEEK_END) != 0) {
        perror("Error moving file pointer to the end of file");
        fclose(file);
        return ;
    }

    fprintf(file, "%d\n", reader.id);
    fprintf(file, "%s\n", reader.reader_name);
    fprintf(file, "%s\n", reader.cmnd);
    fprintf(file, "%s\n", reader.birthdate);
    fprintf(file, "%s\n", reader.gender);
    fprintf(file, "%s\n", reader.address);
    fprintf(file, "%s\n", reader.date_create_card);
    fprintf(file, "%s\n", reader.date_expire_card);
    fprintf(file, "%s\n", "----------------------------------");

    fclose(file);
}

int read_readers_from_file(const char *filename, struct Reader **readers) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return -1;
    }

    int count;
    if (fscanf(file, "%d\n", &count) != 1) {
        perror("Failed to read the number of readers");
        fclose(file);
        return -1;
    }

    *readers = (struct Reader *)malloc(count * sizeof(struct Reader));
    if (*readers == NULL) {
        perror("Failed to allocate memory for readers");
        fclose(file);
        return -1;
    }

    for (int i = 0; i < count; i++) {
        struct Reader *reader = &(*readers)[i];

        reader->reader_name = (char *)malloc(256);
        reader->cmnd = (char *)malloc(256);
        reader->birthdate = (char *)malloc(256);
        reader->gender = (char *)malloc(256);
        reader->address = (char *)malloc(256);
        reader->date_create_card = (char *)malloc(256);
        reader->date_expire_card = (char *)malloc(256);

        if (fscanf(file, "%d\n", &reader->id) != 1) {
            perror("Failed to read reader id");
            fclose(file);
            return count;
        } 

        if (fscanf(file, "%255[^\n]\n", reader->reader_name) != 1) {
            perror("Failed to read reader name");
            fclose(file);
            return count;
        }

        if (fscanf(file, "%255[^\n]\n", reader->cmnd) != 1) {
            perror("Failed to read reader cmnd");
            fclose(file);
            return count;
        }

        if (fscanf(file, "%255[^\n]\n", reader->birthdate) != 1) {
            perror("Failed to read reader birthdate");
            fclose(file);
            return count;
        }

        if (fscanf(file, "%255[^\n]\n", reader->gender) != 1){
            perror("Failed to read reader gender");
            fclose(file);
            return count;
        }
        if (fscanf(file, "%255[^\n]\n", reader->address) != 1) {
            perror("Failed to read reader address");
            fclose(file);
            return count;
        }
        if (fscanf(file, "%255[^\n]\n", reader->date_create_card) != 1) {
            perror("Failed to read reader date create card");
            fclose(file);
            return count;
        }
        if (fscanf(file, "%255[^\n]\n", reader->date_expire_card) != 1) {
            perror("Failed to read reader date expire card");
            fclose(file);
            return count;
        }

        char line[256];
        if (fscanf(file, "%255[^\n]\n", line) != 1) {
            perror("Failed to read reader data");
            fclose(file);
            return count;
        }

    }

    fclose(file);
    return count;
}

void update_reader_in_file(const char *filename, int id_to_update, struct Reader new_data) {
    struct Reader *readers;
    int count = read_readers_from_file(filename, &readers);

    if (count == -1) {
        printf("Failed to read readers from file.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        if (readers[i].id == id_to_update) {
            free_reader(&readers[i]);
            readers[i] = new_data;
            break;
        }
    }

    write_readers_to_file(filename, readers, count);
    free_readers(readers, count);
}

int delete_reader_in_file(const char *filename, int id_to_update) {
    struct Reader *readers;
    int count = read_readers_from_file(filename, &readers);

    if (count == -1) {
        printf("Failed to read readers from file.\n");
        return -1;
    }

    int index_delete = -1;
    for (int i = 0; i < count; i++) {
        if (readers[i].id == id_to_update) {
            index_delete = i;
        }
        if (index_delete != -1 && i < count - 1) {
            readers[i] = readers[i + 1];
        }
    }

    write_readers_to_file(filename, readers, count-1);
    free_readers(readers, count);
    return 1;
}

void free_reader(struct Reader *reader) {
    free(reader->reader_name);
    free(reader->cmnd);
    free(reader->birthdate);
    free(reader->gender);
    free(reader->address);
    free(reader->date_create_card);
    free(reader->date_expire_card);
}

void free_readers(struct Reader *readers, int count) {
    for (int i = 0; i < count; i++) {
        free_reader(&readers[i]);
    }
    free(readers);
}