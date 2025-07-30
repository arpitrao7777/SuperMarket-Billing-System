#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#ifdef _WIN32
#include <cstdlib>
#endif

using namespace std;

class shopping {
private:
    int pcode;
    float price;
    float dis;
    string pname;

public:
    void menu();
    void administrator();
    void buyer();
    void add();
    void edit()
    void rem();
    void list();
    void receipt();
};

void shopping::menu()
{
    while (true)
    {
        int choice;
        string email;
        string password;

        cout << "\n\t\t\t\t_______________________________\n";
        cout << "\t\t\t\t       Supermarket Main Menu       \n";
        cout << "\t\t\t\t_______________________________\n";
        cout << "\t\t\t\t|         1) Administrator           |\n";
        cout << "\t\t\t\t|         2) Buyer                   |\n";
        cout << "\t\t\t\t|         3) Exit                    |\n";
        cout << "\t\t\t\t_______________________________\n";
        cout << "\n\t\t\t Please select: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "\n\t\t\t Please Login \n";
            cout << "\t\t\t Enter Email: ";
            cin >> email;
            cout << "\t\t\t Enter Password: ";
            cin >> password;
            if (email == "abc@gmail.com" && password == "123")
            {
                administrator();
            }
            else
            {
                cout << "Invalid email/password\n";
            }
            break;

        case 2:
            buyer();
            break;

        case 3:
            exit(0);

        default:
            cout << "Please select from the given options\n";
        }
    }
}

void shopping::administrator()
{
    while (true)
    {
        int choice;
        cout << "\n\n\n\t\t\t Administrator Menu";
        cout << "\n\t\t\t| 1) Add the product         |";
        cout << "\n\t\t\t| 2) Modify the product      |";
        cout << "\n\t\t\t| 3) Delete the product      |";
        cout << "\n\t\t\t| 4) Back to main menu       |";
        cout << "\n\n\t Please enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            add();
            break;
        case 2:
            edit();
            break;
        case 3:
            rem();
            break;
        case 4:
            return;
        default:
            cout << "Invalid choice!\n";
        }
    }
}

void shopping::buyer()
{
    while (true)
    {
        int choice;
        cout << "\n\t\t\t Buyer \n";
        cout << "\t\t\t_________________\n";
        cout << "\t\t\t 1) Buy product\n";
        cout << "\t\t\t 2) Go back\n";
        cout << "\t\t\t Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            receipt();
            break;
        case 2:
            return;
        default:
            cout << "Invalid choice\n";
        }
    }
}

void shopping::add()
{
    fstream data;
    int token = 0;
    int tempCode;
    string tempName;
    float tempPrice, tempDis;

    cout << "\n\n\t\t\t Add new product\n";
    cout << "\n\t Product code of the product: ";
    cin >> tempCode;
    cout << "\n\t Name of the product: ";
    cin >> tempName;
    cout << "\n\t Price of the product: ";
    cin >> tempPrice;
    cout << "\n\t Discount on product: ";
    cin >> tempDis;

    data.open("database.txt", ios::in);
    if (!data)
    {
        data.open("database.txt", ios::app | ios::out);
    }
    else
    {
        int c;
        string n;
        float p, d;
        while (data >> c >> n >> p >> d)
        {
            if (c == tempCode)
            {
                token = 1;
                break;
            }
        }
        data.close();
    }

    if (token == 1)
    {
        cout << "\nProduct code already exists. Try again.\n";
        return;
    }

    data.open("database.txt", ios::app | ios::out);
    data << tempCode << " " << tempName << " " << tempPrice << " " << tempDis << "\n";
    data.close();
    cout << "\n\n\t\t Record inserted!\n";
}

void shopping::edit()
{
    fstream data, data1;
    int pkey;
    int token = 0;
    int c;
    float p, d;
    string n;

    cout << "\n\t\t\t Modify the record";
    cout << "\n\t\t\t Product code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "\nFile doesn't exist!\n";
        return;
    }

    data1.open("database1.txt", ios::app | ios::out);
    while (data >> pcode >> pname >> price >> dis)
    {
        if (pkey == pcode)
        {
            cout << "\n\t\t Product new code: ";
            cin >> c;
            cout << "\n\t\t Name of the product: ";
            cin >> n;
            cout << "\n\t\t Price: ";
            cin >> p;
            cout << "\n\t\t Discount: ";
            cin >> d;
            data1 << c << " " << n << " " << p << " " << d << "\n";
            cout << "\n\n\t\t Record edited ";
            token++;
        }
        else
        {
            data1 << pcode << " " << pname << " " << price << " " << dis << "\n";
        }
    }
    data.close();
    data1.close();
    remove("database.txt");
    rename("database1.txt", "database.txt");

    if (token == 0)
    {
        cout << "\n\n Record not found sorry!\n";
    }
}

void shopping::rem()
{
    fstream data, data1;
    int pkey;
    int token = 0;

    cout << "\n\n\t Delete product";
    cout << "\n\n\t Product code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "File doesn't exist\n";
        return;
    }

    data1.open("database1.txt", ios::app | ios::out);
    while (data >> pcode >> pname >> price >> dis)
    {
        if (pcode == pkey)
        {
            cout << "\n\n\t Product deleted successfully\n";
            token++;
        }
        else
        {
            data1 << pcode << " " << pname << " " << price << " " << dis << "\n";
        }
    }
    data.close();
    data1.close();
    remove("database.txt");
    rename("database1.txt", "database.txt");

    if (token == 0)
    {
        cout << "\n\n Record not found\n";
    }
}

void shopping::list()
{
    fstream data;
    data.open("database.txt", ios::in);
    cout << "\n\nProduct Number\tName\t\tPrice\tDiscount\n\n";
    while (data >> pcode >> pname >> price >> dis)
    {
        cout << pcode << "\t\t" << pname << "\t\t" << price << "\t" << dis << "%\n";
    }
    data.close();
}

void shopping::receipt()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    fstream data;
    vector<int> arrc, arrq;
    char choice;
    float amount = 0, discountAmount = 0, total = 0;

    cout << "\n\n\t\t\t Receipt ";
    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "\n\n Empty database. Please try again!";
        return;
    }
    data.close();

    list();

    cout << "\n\n_____________________________\n";
    cout << "\n|                           |";
    cout << "\n|    Please place the order  |";
    cout << "\n|___________________________|\n";

    do
    {
        int code, quantity;
        cout << "\n\n Product Code: ";
        cin >> code;
        cout << " Product Quantity: ";
        cin >> quantity;

        bool duplicate = false;
        for (int i = 0; i < arrc.size(); i++)
        {
            if (arrc[i] == code)
            {
                cout << "\n\n Duplicate Product Code. Please try again.\n";
                duplicate = true;
                break;
            }
        }
        if (!duplicate)
        {
            arrc.push_back(code);
            arrq.push_back(quantity);
        }

        cout << "\n\n Want to buy another product? Press y for yes, n for no: ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    cout << "\n\n\t\t\t_RECEIPT_\n";
    cout << "\nProduct Num.\tProduct Name\tQuantity\tPrice\tAmount\tAmount with discount\n";

    for (int i = 0; i < arrc.size(); i++)
    {
        data.open("database.txt", ios::in);
        while (data >> pcode >> pname >> price >> dis)
        {
            if (pcode == arrc[i])
            {
                amount = price * arrq[i];
                discountAmount = amount - (amount * dis / 100);
                total += discountAmount;
                cout << pcode << "\t\t" << pname << "\t\t" << arrq[i] << "\t\t" << price << "\t" << amount << "\t" << discountAmount << "\n";
                break;
            }
        }
        data.close();
    }
    cout << "\n------------------------------------------";
    cout << "\n Total Amount: " << total << "\n";
}

int main()
{
    shopping s;
    s.menu();
    return 0;
}
