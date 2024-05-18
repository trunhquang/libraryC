#include <stdbool.h>

#pragma once
// a. Xem danh sách độc giả trong thư viện
// b. Thêm độc giả
// c. Chỉnh sửa thông tin một độc giả
// d. Xóa thông tin một độc giả
// e. Tìm kiếm độc giả theo CMND
// f. Tìm kiếm sách theo họ tên

struct Reader
{
    int id;
    char *reader_name;
    char *cmnd;
    char *birthdate;
    char *gender;
    char *address;
    char *date_create_card;
    char *date_expire_card;
};
void free_reader(struct Reader *reader);
void free_readers(struct Reader *readers, int count);
struct Reader createReader(int id, char *name, char *cmnd, char *birthdate, char *gender, char *address, char *date_create_card, char *date_expire_card);

int get_reader_size();

// This is a declaration of a function that will be defined in readers.cpp
bool readers_show_menu_functions();

/// @brief handle readers menu
/// @param choice
bool handle_readers_menu(int choice);

void show_edit_reader_menu(int index, Reader *reader_list, int reader_size);

int *get_ids_reader();

void show_statistics_gender();

char *get_reader_name(int id);

/// do an 2

struct Reader createReader(int id, char *name, char *cmnd, char *birthdate, char *gender, char *address, char *date_create_card, char *date_expire_card);
void addReader(struct Reader **people, int *num_people, struct Reader new_person);

// Hàm tìm kiếm một người theo tên trong mảng
int *findPersonByName(struct Reader *people, int num_people, int *return_arr_length, const char *name);

// Hàm tìm kiếm một người theo cmnd trong mảng
int *findPersonByCmnd(struct Reader *people, int num_people, int *return_arr_length, const char *cmnd);

int findPersonByid(struct Reader *people, int num_people, int id);
// Hàm xóa một đối tượng Person khỏi mảng
void deletePersonbyID(struct Reader **people, int *num_people, int id);

//files
void write_readers_to_file(const char *filename, struct Reader *readers, int count);
void write_reader_to_file(const char *filename, struct Reader reader);
int read_readers_from_file(const char *filename, struct Reader **readers);
void update_reader_in_file(const char *filename, int id_to_update, struct Reader new_data);
int delete_reader_in_file(const char *filename, int id_to_update);