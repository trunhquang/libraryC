#pragma one

struct Ticket
{
    int ticket_id;
    int reader_id;
    char *book_id;
    char *reason_pay;
    // ticket return or not
    int return_status;
    int money_pay_for_error;
    int day_borrow, mounth_borrow, year_borrow;
    /// date return expect
    int day_return_ex, mounth_return_ex, year_return_ex;
    int day_return, mounth_return, year_return;

    void (*updateReturnDate)(struct Ticket *self, int day_return, int mounth_return, int year_return);
    void (*updateMOney)(struct Ticket *self, int money_pay_for_error);
    void (*updateStatus)(struct Ticket *self, int return_status);
};

bool ticket_show_menu();
bool handle_ticket_menu(int choice);
bool ticket_return_show_menu();

void view_tickets(int index, bool showAll);

void add_ticket();
void print_ticket(int index);
void create_template_ticket();

int get_total_borrowed_books();

void show_reader_late_ticket();

/// do an 2
struct Ticket createTicket(int ticket_id,
                           int reader_id,
                           char *book_id,
                           char *reason_pay,
                           int return_status,
                           int money_pay_for_error,
                           int day_borrow, int mounth_borrow, int year_borrow,
                           int day_return, int mounth_return, int year_return);
void addTicketToList(struct Ticket **tickets, int *num, struct Ticket new_ticket);
int findTicketByid(struct Ticket *ticket, int num, int id);
void deleteTicketbyID(struct Ticket **book, int *num, const char *isbn);