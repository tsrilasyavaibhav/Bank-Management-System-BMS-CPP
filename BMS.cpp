#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class BankAccount
{
private:
    int accountNumber;
    char name[50];
    float balance;

public:
    void createAccount()
    {
        cout << "Enter Account Number: ";
        cin >> accountNumber;

        cin.ignore();
        cout << "Enter Customer Name: ";
        cin.getline(name, 50);

        cout << "Enter Initial Deposit Amount: ";
        cin >> balance;
    }

    void displayAccount() const
    {
        cout << "\n---------------------------";
        cout << "\nAccount Number : " << accountNumber;
        cout << "\nCustomer Name  : " << name;
        cout << "\nBalance        : Rs." << balance;
        cout << "\n---------------------------\n";
    }

    int getAccountNumber() const
    {
        return accountNumber;
    }

    void deposit(float amount)
    {
        balance += amount;
    }

    bool withdraw(float amount)
    {
        if (amount > balance)
        {
            return false;
        }

        balance -= amount;
        return true;
    }

    float getBalance() const
    {
        return balance;
    }
};

void createNewAccount()
{
    BankAccount acc;

    ofstream file("bank.dat", ios::binary | ios::app);

    acc.createAccount();
    file.write((char *)&acc, sizeof(acc));

    file.close();

    cout << "\nAccount Created Successfully!\n";
}

void displayAccount(int accNo)
{
    BankAccount acc;
    bool found = false;

    ifstream file("bank.dat", ios::binary);

    while (file.read((char *)&acc, sizeof(acc)))
    {
        if (acc.getAccountNumber() == accNo)
        {
            acc.displayAccount();
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nAccount Not Found!\n";
    }
}

void depositMoney(int accNo)
{
    BankAccount acc;
    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    bool found = false;
    float amount;

    while (file.read((char *)&acc, sizeof(acc)))
    {
        if (acc.getAccountNumber() == accNo)
        {
            cout << "Enter Amount to Deposit: ";
            cin >> amount;

            acc.deposit(amount);

            int pos = file.tellg();
            file.seekp(pos - sizeof(acc));

            file.write((char *)&acc, sizeof(acc));

            cout << "\nDeposit Successful!\n";
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nAccount Not Found!\n";
    }
}

void withdrawMoney(int accNo)
{
    BankAccount acc;
    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    bool found = false;
    float amount;

    while (file.read((char *)&acc, sizeof(acc)))
    {
        if (acc.getAccountNumber() == accNo)
        {
            cout << "Enter Amount to Withdraw: ";
            cin >> amount;

            if (!acc.withdraw(amount))
            {
                cout << "\nInsufficient Balance!\n";
            }
            else
            {
                int pos = file.tellg();
                file.seekp(pos - sizeof(acc));

                file.write((char *)&acc, sizeof(acc));

                cout << "\nWithdrawal Successful!\n";
            }

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nAccount Not Found!\n";
    }
}

void checkBalance(int accNo)
{
    BankAccount acc;
    bool found = false;

    ifstream file("bank.dat", ios::binary);

    while (file.read((char *)&acc, sizeof(acc)))
    {
        if (acc.getAccountNumber() == accNo)
        {
            cout << "\nCurrent Balance: Rs." << acc.getBalance() << endl;
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nAccount Not Found!\n";
    }
}

int main()
{
    int choice, accNo;

    do
    {
        cout << "\n========== BANK MANAGEMENT SYSTEM ==========\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Balance\n";
        cout << "5. Display Account Details\n";
        cout << "6. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            createNewAccount();
            break;

        case 2:
            cout << "Enter Account Number: ";
            cin >> accNo;
            depositMoney(accNo);
            break;

        case 3:
            cout << "Enter Account Number: ";
            cin >> accNo;
            withdrawMoney(accNo);
            break;

        case 4:
            cout << "Enter Account Number: ";
            cin >> accNo;
            checkBalance(accNo);
            break;

        case 5:
            cout << "Enter Account Number: ";
            cin >> accNo;
            displayAccount(accNo);
            break;

        case 6:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}