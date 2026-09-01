
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>

using namespace std;

// ============================================================
// FILE NAMES
// ============================================================

const string ACCOUNTS_FILE = "accounts.dat";
const string TRANSACTIONS_FILE = "transactions.dat";

// ============================================================
// STRUCTURES
// ============================================================

struct Account
{
    int accountNumber;
    string customerName;
    double balance;
    string accountType;
    string createdDate;
};

struct Transaction
{
    string date;
    int accountNumber;
    string type;
    double amount;
    double balanceAfter;
};

// ============================================================
// GLOBAL VARIABLES
// ============================================================

vector<Account> accounts;
vector<Transaction> transactions;

int nextAccountNumber = 1001;

// ============================================================
// GET CURRENT DATE
// ============================================================

string getCurrentDate()
{
    time_t now = time(nullptr);
    tm* timeInfo = localtime(&now);

    char buffer[20];

    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeInfo);

    return string(buffer);
}

// ============================================================
// CLEAR INPUT
// ============================================================

void clearInput()
{
    cin.clear();
    cin.ignore(10000, '\n');
}

// ============================================================
// FIND ACCOUNT USING POINTER
// ============================================================

Account* findAccount(int accountNumber)
{
    for (size_t i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].accountNumber == accountNumber)
        {
            return &accounts[i];
        }
    }

    return nullptr;
}

// ============================================================
// CREATE ACCOUNT
// ============================================================

void createAccount()
{
    Account newAccount;

    cout << "\n========================================\n";
    cout << "           CREATE ACCOUNT\n";
    cout << "========================================\n";

    cout << "Customer Name: ";
    getline(cin >> ws, newAccount.customerName);

    cout << "Account Type (Savings/Checking): ";
    getline(cin, newAccount.accountType);

    if (newAccount.accountType != "Savings" &&
        newAccount.accountType != "savings" &&
        newAccount.accountType != "Checking" &&
        newAccount.accountType != "checking")
    {
        cout << "\nInvalid account type.\n";
        cout << "Please enter Savings or Checking.\n";
        return;
    }

    cout << "Opening Balance (Rs): ";
    cin >> newAccount.balance;

    if (cin.fail())
    {
        clearInput();
        cout << "Invalid balance.\n";
        return;
    }

    if (newAccount.balance < 0)
    {
        cout << "Balance cannot be negative.\n";
        return;
    }

    newAccount.accountNumber = nextAccountNumber++;
    newAccount.createdDate = getCurrentDate();

    accounts.push_back(newAccount);

    cout << "\n========================================\n";
    cout << "      ACCOUNT CREATED SUCCESSFULLY\n";
    cout << "========================================\n";

    cout << "Account Number: "
         << newAccount.accountNumber << endl;

    cout << "Customer Name: "
         << newAccount.customerName << endl;

    cout << "Account Type: "
         << newAccount.accountType << endl;

    cout << "Opening Balance: Rs "
         << fixed << setprecision(2)
         << newAccount.balance << endl;
}

// ============================================================
// DEPOSIT
// ============================================================

void deposit()
{
    if (accounts.empty())
    {
        cout << "\nNo accounts available.\n";
        cout << "Please create an account first.\n";
        return;
    }

    cout << "\n========================================\n";
    cout << "             DEPOSIT MONEY\n";
    cout << "========================================\n";

    int accountNumber;

    cout << "Enter Account Number: ";
    cin >> accountNumber;

    if (cin.fail())
    {
        clearInput();
        cout << "Invalid account number.\n";
        return;
    }

    Account* account = findAccount(accountNumber);

    if (account == nullptr)
    {
        cout << "\nAccount not found.\n";

        cout << "\nAvailable Account Numbers:\n";

        for (const Account& acc : accounts)
        {
            cout << "  " << acc.accountNumber
                 << " - " << acc.customerName << endl;
        }

        return;
    }

    double amount;

    cout << "Amount to deposit (Rs): ";
    cin >> amount;

    if (cin.fail())
    {
        clearInput();
        cout << "Invalid amount.\n";
        return;
    }

    if (amount <= 0)
    {
        cout << "Amount must be greater than zero.\n";
        return;
    }

    account->balance += amount;

    Transaction transaction;

    transaction.date = getCurrentDate();
    transaction.accountNumber = account->accountNumber;
    transaction.type = "Deposit";
    transaction.amount = amount;
    transaction.balanceAfter = account->balance;

    transactions.push_back(transaction);

    cout << "\n========================================\n";
    cout << "          DEPOSIT SUCCESSFUL\n";
    cout << "========================================\n";

    cout << "Account Number: "
         << account->accountNumber << endl;

    cout << "Deposited: Rs "
         << fixed << setprecision(2)
         << amount << endl;

    cout << "New Balance: Rs "
         << account->balance << endl;
}

// ============================================================
// WITHDRAW
// ============================================================

void withdraw()
{
    if (accounts.empty())
    {
        cout << "\nNo accounts available.\n";
        return;
    }

    cout << "\n========================================\n";
    cout << "            WITHDRAW MONEY\n";
    cout << "========================================\n";

    int accountNumber;

    cout << "Enter Account Number: ";
    cin >> accountNumber;

    if (cin.fail())
    {
        clearInput();
        cout << "Invalid account number.\n";
        return;
    }

    Account* account = findAccount(accountNumber);

    if (account == nullptr)
    {
        cout << "\nAccount not found.\n";

        cout << "\nAvailable Account Numbers:\n";

        for (const Account& acc : accounts)
        {
            cout << "  " << acc.accountNumber
                 << " - " << acc.customerName << endl;
        }

        return;
    }

    double amount;

    cout << "Amount to withdraw (Rs): ";
    cin >> amount;

    if (cin.fail())
    {
        clearInput();
        cout << "Invalid amount.\n";
        return;
    }

    if (amount <= 0)
    {
        cout << "Amount must be greater than zero.\n";
        return;
    }

    if (amount > account->balance)
    {
        cout << "\nInsufficient funds.\n";

        cout << "Current Balance: Rs "
             << fixed << setprecision(2)
             << account->balance << endl;

        return;
    }

    account->balance -= amount;

    Transaction transaction;

    transaction.date = getCurrentDate();
    transaction.accountNumber = account->accountNumber;
    transaction.type = "Withdraw";
    transaction.amount = amount;
    transaction.balanceAfter = account->balance;

    transactions.push_back(transaction);

    cout << "\n========================================\n";
    cout << "        WITHDRAWAL SUCCESSFUL\n";
    cout << "========================================\n";

    cout << "Withdrawn: Rs "
         << fixed << setprecision(2)
         << amount << endl;

    cout << "New Balance: Rs "
         << account->balance << endl;
}

// ============================================================
// CHECK BALANCE
// ============================================================

void checkBalance()
{
    if (accounts.empty())
    {
        cout << "\nNo accounts available.\n";
        return;
    }

    int accountNumber;

    cout << "\nEnter Account Number: ";
    cin >> accountNumber;

    if (cin.fail())
    {
        clearInput();
        cout << "Invalid account number.\n";
        return;
    }

    Account* account = findAccount(accountNumber);

    if (account == nullptr)
    {
        cout << "Account not found.\n";
        return;
    }

    cout << "\n========================================\n";
    cout << "           ACCOUNT DETAILS\n";
    cout << "========================================\n";

    cout << "Account Number: "
         << account->accountNumber << endl;

    cout << "Customer Name: "
         << account->customerName << endl;

    cout << "Account Type: "
         << account->accountType << endl;

    cout << "Created Date: "
         << account->createdDate << endl;

    cout << "Balance: Rs "
         << fixed << setprecision(2)
         << account->balance << endl;
}

// ============================================================
// DISPLAY ALL ACCOUNTS
// ============================================================

void displayAllAccounts()
{
    if (accounts.empty())
    {
        cout << "\nNo accounts available.\n";
        return;
    }

    cout << "\n=================================================================\n";
    cout << "                      ALL ACCOUNTS\n";
    cout << "=================================================================\n";

    cout << left
         << setw(12) << "Account"
         << setw(22) << "Customer"
         << setw(15) << "Type"
         << setw(15) << "Balance"
         << endl;

    cout << string(64, '-') << endl;

    for (const Account& account : accounts)
    {
        cout << left
             << setw(12) << account.accountNumber
             << setw(22) << account.customerName
             << setw(15) << account.accountType
             << setw(15)
             << fixed << setprecision(2)
             << account.balance
             << endl;
    }
}

// ============================================================
// TRANSACTION HISTORY
// ============================================================

void transactionHistory()
{
    if (accounts.empty())
    {
        cout << "\nNo accounts available.\n";
        return;
    }

    int accountNumber;

    cout << "\nEnter Account Number: ";
    cin >> accountNumber;

    if (cin.fail())
    {
        clearInput();
        cout << "Invalid account number.\n";
        return;
    }

    Account* account = findAccount(accountNumber);

    if (account == nullptr)
    {
        cout << "Account not found.\n";
        return;
    }

    cout << "\n========================================\n";
    cout << "          TRANSACTION HISTORY\n";
    cout << "========================================\n";

    bool found = false;

    for (const Transaction& transaction : transactions)
    {
        if (transaction.accountNumber == accountNumber)
        {
            cout << "\nDate: "
                 << transaction.date << endl;

            cout << "Type: "
                 << transaction.type << endl;

            cout << "Amount: Rs "
                 << fixed << setprecision(2)
                 << transaction.amount << endl;

            cout << "Balance After: Rs "
                 << transaction.balanceAfter << endl;

            cout << "----------------------------------------\n";

            found = true;
        }
    }

    if (!found)
    {
        cout << "No transactions found.\n";
    }
}

// ============================================================
// SAVE ACCOUNTS
// ============================================================

bool saveAccounts()
{
    ofstream file(ACCOUNTS_FILE);

    if (!file)
    {
        cout << "ERROR: Could not save accounts.dat\n";
        return false;
    }

    file << accounts.size() << '\n';

    for (const Account& account : accounts)
    {
        file << account.accountNumber << "|"
             << account.customerName << "|"
             << fixed << setprecision(2)
             << account.balance << "|"
             << account.accountType << "|"
             << account.createdDate << '\n';
    }

    file.close();

    return true;
}

// ============================================================
// SAVE TRANSACTIONS
// ============================================================

bool saveTransactions()
{
    ofstream file(TRANSACTIONS_FILE);

    if (!file)
    {
        cout << "ERROR: Could not save transactions.dat\n";
        return false;
    }

    file << transactions.size() << '\n';

    for (const Transaction& transaction : transactions)
    {
        file << transaction.date << "|"
             << transaction.accountNumber << "|"
             << transaction.type << "|"
             << fixed << setprecision(2)
             << transaction.amount << "|"
             << transaction.balanceAfter << '\n';
    }

    file.close();

    return true;
}

// ============================================================
// SAVE ALL DATA
// ============================================================

void saveData()
{
    bool accountsSaved = saveAccounts();
    bool transactionsSaved = saveTransactions();

    cout << "\n========================================\n";
    cout << "              SAVE STATUS\n";
    cout << "========================================\n";

    if (accountsSaved && transactionsSaved)
    {
        cout << "All data saved successfully!\n\n";

        cout << "Files created:\n";
        cout << "1. accounts.dat\n";
        cout << "2. transactions.dat\n\n";

        cout << "These files are saved in the program's\n";
        cout << "current working directory.\n\n";

        cout << "If you are using VS Code, check the folder\n";
        cout << "where banking.exe is being run.\n";
    }
    else
    {
        cout << "Some files could not be saved.\n";
    }
}

// ============================================================
// LOAD ACCOUNTS
// ============================================================

void loadAccounts()
{
    ifstream file(ACCOUNTS_FILE);

    if (!file)
    {
        return;
    }

    int count;

    if (!(file >> count))
    {
        file.close();
        return;
    }

    file.ignore(10000, '\n');

    accounts.clear();

    for (int i = 0; i < count; i++)
    {
        string line;

        if (!getline(file, line))
        {
            break;
        }

        if (line.empty())
        {
            i--;
            continue;
        }

        stringstream ss(line);

        Account account;
        string temp;

        try
        {
            if (!getline(ss, temp, '|'))
                continue;

            account.accountNumber = stoi(temp);

            if (!getline(ss, account.customerName, '|'))
                continue;

            if (!getline(ss, temp, '|'))
                continue;

            account.balance = stod(temp);

            if (!getline(ss, account.accountType, '|'))
                continue;

            if (!getline(ss, account.createdDate))
                continue;

            accounts.push_back(account);

            if (account.accountNumber >= nextAccountNumber)
            {
                nextAccountNumber = account.accountNumber + 1;
            }
        }
        catch (...)
        {
            cout << "Invalid account data skipped.\n";
        }
    }

    file.close();
}

// ============================================================
// LOAD TRANSACTIONS
// ============================================================

void loadTransactions()
{
    ifstream file(TRANSACTIONS_FILE);

    if (!file)
    {
        return;
    }

    int count;

    if (!(file >> count))
    {
        file.close();
        return;
    }

    file.ignore(10000, '\n');

    transactions.clear();

    for (int i = 0; i < count; i++)
    {
        string line;

        if (!getline(file, line))
        {
            break;
        }

        if (line.empty())
        {
            i--;
            continue;
        }

        stringstream ss(line);

        Transaction transaction;
        string temp;

        try
        {
            if (!getline(ss, transaction.date, '|'))
                continue;

            if (!getline(ss, temp, '|'))
                continue;

            transaction.accountNumber = stoi(temp);

            if (!getline(ss, transaction.type, '|'))
                continue;

            if (!getline(ss, temp, '|'))
                continue;

            transaction.amount = stod(temp);

            if (!getline(ss, temp))
                continue;

            transaction.balanceAfter = stod(temp);

            transactions.push_back(transaction);
        }
        catch (...)
        {
            cout << "Invalid transaction data skipped.\n";
        }
    }

    file.close();
}

// ============================================================
// MENU
// ============================================================

void menu()
{
    cout << "\n\n";
    cout << "========================================\n";
    cout << "         SIMPLE BANKING SYSTEM\n";
    cout << "========================================\n";
    cout << "1. Create Account\n";
    cout << "2. Deposit Money\n";
    cout << "3. Withdraw Money\n";
    cout << "4. Check Balance\n";
    cout << "5. Display All Accounts\n";
    cout << "6. Transaction History\n";
    cout << "7. Save Data\n";
    cout << "0. Save & Exit\n";
    cout << "========================================\n";
}

// ============================================================
// MAIN
// ============================================================

int main()
{
    loadAccounts();
    loadTransactions();

    int choice;

    do
    {
        menu();

        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail())
        {
            clearInput();
            cout << "\nInvalid choice. Please enter a number.\n";
            continue;
        }

        switch (choice)
        {
            case 1:
                createAccount();
                break;

            case 2:
                deposit();
                break;

            case 3:
                withdraw();
                break;

            case 4:
                checkBalance();
                break;

            case 5:
                displayAllAccounts();
                break;

            case 6:
                transactionHistory();
                break;

            case 7:
                saveData();
                break;

            case 0:
                saveData();
                cout << "\nThank you for using the Banking System!\n";
                break;

            default:
                cout << "\nInvalid choice. Please select 0-7.\n";
        }

    } while (choice != 0);

    return 0;
}

