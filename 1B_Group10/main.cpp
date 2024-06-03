#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <vector>
#include <fstream>
#include <sstream>
#include "Queue.h"
#include "Stack.h"

class Reservation //Element
{
private:
    std::string a_username; //Attribute
    std::string a_passwd;
    int id_number = 0;
    std::string c_name;
    std::string c_gender;
    std::string c_email;
    std::string c_contactNumber;
    std::string date;
    std::string time;
    std::string seat;

public:
    static void welcome();  //Function
    static void admin_page1();
    static void admin_page2();
    static void customer_page();
    static void AddReserve();
    static void CancelReserve();
    static void SearchReserve();
    static void DisplayReserve(const std::vector<Reservation> display_data);
    static void EditReserve();
    static void SortReserve();
    static void loadData();
    static void saveData();
    static int getNewId();
    static int getLastId();
    std::string get_name() const;
};

std::vector<Reservation> rsvt_data;
const std::string FILENAME = "booking.txt";

std::string Reservation::get_name() const
{
    return c_name;
}

void Reservation::loadData()
{
    rsvt_data.clear(); //Prevent data repetition
    std::ifstream bookingFile(FILENAME);

    if (!bookingFile.is_open())
    {
        std::cout << "File '" << FILENAME << "' does not exist.";
        exit(1);
    }

    std::string line;
    std::string buf;
    Reservation rsvt;
    char delim = ';';

    try
    {
        while (getline(bookingFile, line))
        {
            std::stringstream ss(line);
            getline(ss, buf, delim);
            rsvt.id_number = stoi(buf);
            getline(ss, rsvt.c_name, delim);
            getline(ss, rsvt.c_gender, delim);
            getline(ss, rsvt.date, delim);
            getline(ss, rsvt.time, delim);
            getline(ss, rsvt.c_contactNumber, delim);
            getline(ss, rsvt.c_email, delim);
            getline(ss, rsvt.seat, delim);
            rsvt_data.push_back(rsvt);
        }
    }
    catch (...)
    {
        std::cout << "Error in loading data from " << FILENAME << std::endl;
        system("pause");
    }
    bookingFile.close();
}

void Reservation::saveData()
{
    std::ofstream bookingFile(FILENAME);
    Reservation rsvt;

    if (bookingFile.is_open())
    {
        char delim = ';';
        for (int i = 0; i < rsvt_data.size(); i++)
        {
            bookingFile
                << rsvt_data[i].id_number << delim
                << rsvt_data[i].c_name << delim
                << rsvt_data[i].c_gender << delim
                << rsvt_data[i].date << delim
                << rsvt_data[i].time << delim
                << rsvt_data[i].c_contactNumber << delim
                << rsvt_data[i].c_email << delim
                << rsvt_data[i].seat << delim
                << std::endl;
        }
        bookingFile.close();
    }
}

int Reservation::getNewId() // called upon every rsvt creation
{
    static int id = getLastId();
    return ++id;
}

int Reservation::getLastId() // called upon every system run
{
    if (rsvt_data.empty()) return 0;
    return rsvt_data.back().id_number;
}

void swap_index(int& x, int& y)
{
    int temp = x;
    x = y;
    y = temp;
}

void sort_by_name_partition(const std::vector <Reservation> record, int first, int last, int& pivotIndex, std::vector <int>& result)
{
    pivotIndex = first;

    int last_s1 = first;
    int first_unknown = first + 1;

    while (first_unknown <= last)
    {
        if (record[result[pivotIndex]].get_name() >= record[result[first_unknown]].get_name())
        {
            last_s1++;
            swap_index(result[last_s1], result[first_unknown]);
        }
        first_unknown++;
    }
    swap_index(result[pivotIndex], result[last_s1]);
    pivotIndex = last_s1;
}

void sort_by_name(const std::vector <Reservation> rsvt_data, int first, int last, Queue& result_queue, Stack& result_stack)
{
    if (!result_queue.isEmpty() && !result_stack.isEmpty())
    {
        return;
    }

    int recordSize = last - first + 1;
    int pivotIndex = first;

    static std::vector <int> result_vector;

    if (result_vector.empty())
    {
        for (unsigned int i = 0; i < rsvt_data.size(); i++)
        {
            result_vector.push_back(i);
        }
    }

    bool sorted = true;

    for (unsigned int i = 0; i < rsvt_data.size() - 1; i++)
    {
        if (rsvt_data[result_vector[i]].get_name() > rsvt_data[result_vector[i + 1]].get_name())
        {
            sorted = false;
            break;
        }
    }

    if (sorted)
    {
        for (unsigned int i = 0; i < rsvt_data.size(); i++)
        {
            result_queue.enqueue(result_vector[i]);
            result_stack.push(result_vector[i]);
        }
        result_vector.clear();
        return;
    }

    if (recordSize > 1)
    {
        sort_by_name_partition(rsvt_data, first, last, pivotIndex, result_vector);
        sort_by_name(rsvt_data, first, pivotIndex - 1, result_queue, result_stack);
        sort_by_name(rsvt_data, pivotIndex + 1, last, result_queue, result_stack);
    }
}

void Reservation::welcome()
{
    int opt;
    do
    {
        system("cls");
        std::cout << ":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << std::endl;
        std::cout << "::::                                                                   ::::" << std::endl;
        std::cout << "::::                      ZERO 1 RESTAURANT                            ::::" << std::endl;
        std::cout << "::::                                                                   ::::" << std::endl;
        std::cout << ":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << std::endl;

        std::cout << std::endl;

        std::cout << "Welcome to ZERO 1 Restaurant" << std::endl
            << std::endl;
        std::cout << "1) Admin" << std::endl;
        std::cout << "2) Customer" << std::endl;
        std::cout << "3) Exit" << std::endl;

        std::cout << "Choose your option to proceed[1/2/3]: ";
        std::cin >> opt;

        if (opt == 1)
        {
            admin_page1();
        }
        else if (opt == 2)
        {
            customer_page();
        }
        else if (opt == 3)
        {
            exit(0);
        }
        else
        {
            std::cout << "Please type the correct input" << std::endl;
            system("pause");
        }

    } while (true);
}

void Reservation::admin_page1()
{
    std::cin.ignore();

    do
    {
        system("cls");
        Reservation rsvt;
        const std::string a_username = "admin";
        const std::string a_passwd = "123";
        std::cout << "Welcome to the ADMIN PAGE " << std::endl;

        std::cout << "Please enter your name: ";
        getline(std::cin, rsvt.a_username);
        std::cout << std::endl;

        std::cout << "Please enter your password: ";
        getline(std::cin, rsvt.a_passwd);
        std::cout << std::endl;

        if (rsvt.a_username == a_username && rsvt.a_passwd == a_passwd)
        {
            admin_page2();
        }
        else
        {
            std::cout << "Login failed. Incorrect username or password." << std::endl;
            system("pause");
        }

    } while (true);
}

void Reservation::admin_page2()
{
    do
    {
        system("cls");
        char choice;

        std::cout << "        Main Menu" << std::endl
            << std::endl;
        std::cout << "1) Add Reservation" << std::endl;
        std::cout << "2) Display Reservation" << std::endl;
        std::cout << "3) Search Reservation" << std::endl;
        std::cout << "4) Cancel Reservation" << std::endl;
        std::cout << "5) Edit Reservation" << std::endl;
        std::cout << "6) Sort Reservation" << std::endl;
        std::cout << "7) Exit" << std::endl
            << std::endl;

        std::cout << "Enter your choice to proceed[1/2/3/4/5/6/7]:";
        std::cin >> choice;

        switch (choice)
        {
        case '1':
            AddReserve();
            break;
        case '2':
            DisplayReserve(rsvt_data);
            break;
        case '3':
            SearchReserve();
            break;
        case '4':
            CancelReserve();
            break;
        case '5':
            EditReserve();
            break;
        case '6':
            SortReserve();
            break;
        case '7':
            welcome();
            break;
        default:
            std::cout << "Please enter the correct input" << std::endl;
            system("pause");
        }

    } while (true);
}

void Reservation::customer_page()
{
    do
    {
        system("cls");
        char choice;

        std::cout << "        Main Menu" << std::endl
            << std::endl;
        std::cout << "1) Add Reservation" << std::endl;
        std::cout << "2) Search Reservation" << std::endl;
        std::cout << "3) Cancel Reservation" << std::endl;
        std::cout << "4) Exit" << std::endl
            << std::endl;

        std::cout << "Enter your choice to proceed[1/2/3/4]:";
        std::cin >> choice;

        switch (choice)
        {
        case '1':
            AddReserve();
            break;
        case '2':
            SearchReserve();
            break;
        case '3':
            CancelReserve();
            break;
        case '4':
            welcome();
            break;
        default:
            std::cout << "Please enter the correct input" << std::endl;
            system("pause");
        }

    } while (true);
}

void Reservation::AddReserve()
{
    system("cls");
    Reservation rsvt;
    std::fstream bookingFile;

    std::cin.ignore();
    std::cout << "Name:";
    getline(std::cin, rsvt.c_name);
    std::cout << std::endl;
    std::cout << "Gender[M/F]:";
    getline(std::cin, rsvt.c_gender);
    std::cout << std::endl;
    std::cout << "Date Reserve[Exp: DD/MM/YYYY]:";
    getline(std::cin, rsvt.date);
    std::cout << std::endl;
    std::cout << "Time Reserve[Exp: 7pm]:";
    getline(std::cin, rsvt.time);
    std::cout << std::endl;
    std::cout << "Contact Number:";
    getline(std::cin, rsvt.c_contactNumber);
    std::cout << std::endl;
    std::cout << "Email Address:";
    getline(std::cin, rsvt.c_email);
    std::cout << std::endl;
    std::cout << "==============================================" << std::endl;
    std::cout << "|    VIP ROOM    |   Number of People Limit  |" << std::endl;
    std::cout << "|----------------|---------------------------|" << std::endl;
    std::cout << "|       A1       |            10             |" << std::endl;
    std::cout << "|       A2       |            10             |" << std::endl;
    std::cout << "|       B1       |             8             |" << std::endl;
    std::cout << "|       B2       |             8             |" << std::endl;
    std::cout << "==============================================" << std::endl;
    std::cout << "|   Normal Seat  |   Number of People Limit  |" << std::endl;
    std::cout << "|----------------|---------------------------|" << std::endl;
    std::cout << "|       C1       |             6             |" << std::endl;
    std::cout << "|       C2       |             6             |" << std::endl;
    std::cout << "|       C3       |             6             |" << std::endl;
    std::cout << "|       D1       |             4             |" << std::endl;
    std::cout << "|       D2       |             4             |" << std::endl;
    std::cout << "|       D3       |             2             |" << std::endl;
    std::cout << "==============================================" << std::endl
        << std::endl;
    std::cout << "Seat Reserve:";
    getline(std::cin, rsvt.seat);
    std::cout << std::endl
        << std::endl;
    rsvt.id_number = getNewId();

    std::cout << "Booking ID: " << rsvt.id_number << std::endl;
    std::cout << "Name: " << rsvt.c_name << std::endl;
    std::cout << "Gender :" << rsvt.c_gender << std::endl;
    std::cout << "Date: " << rsvt.date << std::endl;
    std::cout << "Time: " << rsvt.time << std::endl;
    std::cout << "Contact Number: " << rsvt.c_contactNumber << std::endl;
    std::cout << "Email Address: " << rsvt.c_email << std::endl;
    std::cout << "Seat: " << rsvt.seat << std::endl;
    std::cout << std::endl;

    rsvt_data.push_back(rsvt);
    saveData();
    system("pause");
}

void Reservation::DisplayReserve(const std::vector<Reservation> display_data)
{
    system("cls");

    std::cout << "==================================================" << std::endl;
    for (int i = 0; i < display_data.size(); i++)
    {
        std::cout << "Booking ID: " << display_data[i].id_number << std::endl;
        std::cout << "Name: " << display_data[i].c_name << std::endl;
        std::cout << "Gender: " << display_data[i].c_gender << std::endl;
        std::cout << "Date: " << display_data[i].date << std::endl;
        std::cout << "Time: " << display_data[i].time << std::endl;
        std::cout << "Contact Number: " << display_data[i].c_contactNumber << std::endl;
        std::cout << "Email Address: " << display_data[i].c_email << std::endl;
        std::cout << "Seat: " << display_data[i].seat << std::endl;
        std::cout << "==================================================" << std::endl;
    }
    system("pause");
}

void Reservation::CancelReserve()
{
    system("cls");

    int id;

    std::cout << "Please enter your booking ID:";
    std::cin >> id;

    bool found = false;
    for (int i = 0; i < rsvt_data.size(); i++)
    {
        if (rsvt_data[i].id_number == id)
        {
            found = true;
            rsvt_data.erase(rsvt_data.begin() + i);

            saveData();
            std::cout << "Delete Successful!!!" << std::endl;
            break;
        }
    }

    if (!found)
    {
        std::cout << "\nReservation not found!" << std::endl;
    }
    system("pause");
}

void Reservation::SearchReserve()
{
    system("cls");

    int id;

    std::cout << "Please enter your booking ID:";
    std::cin >> id;

    bool found = false;
    for (int i = 0; i < rsvt_data.size(); i++)
    {
        if (rsvt_data[i].id_number == id)
        {
            found = true;
            std::cout << "\nReservation Found!" << std::endl;
            std::cout << "==================================================" << std::endl;
            std::cout << "Booking ID: " << rsvt_data[i].id_number << std::endl;
            std::cout << "Name:" << rsvt_data[i].c_name << std::endl;
            std::cout << "Gender:" << rsvt_data[i].c_gender << std::endl;
            std::cout << "Date:" << rsvt_data[i].date << std::endl;
            std::cout << "Time:" << rsvt_data[i].time << std::endl;
            std::cout << "Contact Number:" << rsvt_data[i].c_contactNumber << std::endl;
            std::cout << "Email Address:" << rsvt_data[i].c_email << std::endl;
            std::cout << "Seat:" << rsvt_data[i].seat << std::endl;
        }
    }

    if (!found)
    {
        std::cout << "\nReservation not found!" << std::endl;
    }

    system("pause");
}

void Reservation::EditReserve()
{
    system("cls");

    int id;

    std::cout << "Please enter your booking ID:";
    std::cin >> id;

    bool found = false;
    for (int i = 0; i < rsvt_data.size(); i++)
    {
        if (rsvt_data[i].id_number == id)
        {
            found = true;
            std::cin.ignore();
            std::cout << "Name: ";
            getline(std::cin, rsvt_data[i].c_name);
            std::cout << std::endl;
            std::cout << "Gender: ";
            getline(std::cin, rsvt_data[i].c_gender);
            std::cout << std::endl;
            std::cout << "Date Reserve: ";
            getline(std::cin, rsvt_data[i].date);
            std::cout << std::endl;
            std::cout << "Time Reserve: ";
            getline(std::cin, rsvt_data[i].time);
            std::cout << std::endl;
            std::cout << "Contact Number: ";
            getline(std::cin, rsvt_data[i].c_contactNumber);
            std::cout << std::endl;
            std::cout << "Email Address: ";
            getline(std::cin, rsvt_data[i].c_email);
            std::cout << std::endl;
            std::cout << "==============================================" << std::endl;
            std::cout << "|    VIP ROOM    |   Number of People Limit  |" << std::endl;
            std::cout << "|----------------|---------------------------|" << std::endl;
            std::cout << "|       A1       |            10             |" << std::endl;
            std::cout << "|       A2       |            10             |" << std::endl;
            std::cout << "|       B1       |             8             |" << std::endl;
            std::cout << "|       B2       |             8             |" << std::endl;
            std::cout << "==============================================" << std::endl;
            std::cout << "|   Normal Seat  |   Number of People Limit  |" << std::endl;
            std::cout << "|----------------|---------------------------|" << std::endl;
            std::cout << "|       C1       |             6             |" << std::endl;
            std::cout << "|       C2       |             6             |" << std::endl;
            std::cout << "|       C3       |             6             |" << std::endl;
            std::cout << "|       D1       |             4             |" << std::endl;
            std::cout << "|       D2       |             4             |" << std::endl;
            std::cout << "|       D3       |             2             |" << std::endl;
            std::cout << "==============================================" << std::endl
                << std::endl;
            std::cout << "Seat Reserve: ";
            getline(std::cin, rsvt_data[i].seat);
            std::cout << std::endl;

            saveData();
            std::cout << "Edit Successful!!!" << std::endl;
            break;
        }
    }

    if (!found)
    {
        std::cout << "\nReservation not found!" << std::endl;
    }
    system("pause");
}

void Reservation::SortReserve()
{
    char choice;

    do
    {
        system("cls");
        std::cin.ignore();
        std::cout<<"[A] Sort by ascending"<<std::endl; //vector->sorting->queue/stack
        std::cout<<"[D] Sort by descending"<<std::endl;
        std::cout<<"[E] Exit"<<std::endl;

        std::cout<<"Sort by[A/D]: ";
        std::cin>>choice;

        Queue result_queue;
        Stack result_stack;
        std::vector<Reservation> sort_result;

        if (choice == 'A' || choice == 'a')
        {
            sort_by_name(rsvt_data, 0, (int)rsvt_data.size() - 1, result_queue, result_stack);

            while (!result_queue.isEmpty())
            {
                sort_result.push_back(rsvt_data[result_queue.getFront()]);
                result_queue.dequeue();
            }

            DisplayReserve(sort_result);
        }
        else if (choice == 'D' || choice == 'd')
        {
            sort_by_name(rsvt_data, 0, (int)rsvt_data.size() - 1, result_queue, result_stack);

            while (!result_stack.isEmpty())
            {
                sort_result.push_back(rsvt_data[result_stack.getTop()]);
                result_stack.pop();
            }

            DisplayReserve(sort_result);
        }
        else if (choice == 'E' || choice == 'e')
        {
            admin_page2();
        }
        else
        {
            std::cout << "Please enter the correct input!";
        }

    }while(true);

    system("pause");
}

int main()
{
    Reservation::loadData();
    Reservation::welcome();

    return 0;
}
