
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
    time_t now = time(0);
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
    Account newAcc;

    cout << "\n----------------------------------------\n";
    cout << "          CREATE NEW ACCOUNT\n";
    cout << "----------------------------------------\n";

    cout << "Customer Name: ";
    getline(cin >> ws, newAcc.customerName);

    cout << "Account Type (Savings/Checking): ";
    getline(cin, newAcc.accountType);

    if (newAcc.accountType != "Savings" &&
        newAcc.accountType != "savings" &&
        newAcc.accountType != "Checking" &&
        newAcc.accountType != "checking")
    {
        cout << "Invalid account type!\n";
        cout << "Please enter Savings or Checking.\n";
        return;
    }

    cout << "Opening Balance (Rs): ";
    cin >> newAcc.balance;

    if (cin.fail())
    {
        clearInput();
        cout << "Invalid balance!\n";
        return;
    }

    if (newAcc.balance < 0)
    {
        cout << "Balance cannot be negative!\n";
        return;
    }

    // Assign account number only after successful input
    newAcc.accountNumber = nextAccountNumber++;

    // Get creation date
    newAcc.createdDate = getCurrentDate();

    // Add account to vector
    accounts.push_back(newAcc);

    cout << "\nAccount created successfully!\n";
    cout << "Account Number: "
         << newAcc.accountNumber << endl;
}

// ============================================================
// DEPOSIT
// ============================================================

void deposit()
{
    if (accounts.empty())
    {
        cout << "\nNo accounts yet!\n";
        cout << "Please create an account first.\n";
        return;
    }

    int accNum;

    cout << "\n----------------------------------------\n";
    cout << "              DEPOSIT\n";
    cout << "----------------------------------------\n";

    cout << "Account Number: ";
    cin >> accNum;

    if (cin.fail())
    {
        clearInput();
        cout << "Invalid account number!\n";
        return;
    }

    // Find account using pointer
    Account* foundAcc = findAccount(accNum);

    if (foundAcc == nullptr)
    {
        cout << "Account not found!\n";
        return;
    }

    double amount;

    cout << "Amount to deposit (Rs): ";
    cin >> amount;

    if (cin.fail())
    {
        clearInput();
        cout << "Invalid amount!\n";
        return;
    }

    if (amount <= 0)
    {
        cout << "Amount must be positive!\n";
        return;
    }

    // Modify account through pointer
    foundAcc->balance += amount;

    // Create transaction
    Transaction transaction;

    transaction.date = getCurrentDate();
    transaction.accountNumber = accNum;
    transaction.type = "Deposit";
    transaction.amount = amount;
    transaction.balanceAfter = foundAcc->balance;

    transactions.push_back(transaction);

    cout << "\nDeposit successful!\n";
    cout << "Deposited: Rs "
         << fixed << setprecision(2)
         << amount << endl;

    cout << "New Balance: Rs "
         << foundAcc->balance << endl;
}

// ============================================================
// WITHDRAW
// ============================================================

void withdraw()
{
    if (accounts.empty())
    {
        cout << "\nNo accounts yet!\n";
        cout << "Please create an account first.\n";
        return;
    }

    int accNum;

    cout << "\n----------------------------------------\n";
    cout << "             WITHDRAW\n";
    cout << "----------------------------------------\n";

    cout << "Account Number: ";
    cin >> accNum;

    if (cin.fail())
    {
        clearInput();
        cout << "Invalid account number!\n";
        return;
    }

    // Find account using pointer
    Account* foundAcc = findAccount(accNum);

    if (foundAcc == nullptr)
    {
        cout << "Account not found!\n";
        return;
    }

    double amount;

    cout << "Amount to withdraw (Rs): ";
    cin >> amount;

    if (cin.fail())
    {
        clearInput();
        cout << "Invalid amount!\n";
        return;
    }

    if (amount <= 0)
    {
        cout << "Amount must be positive!\n";
        return;
    }

    // Check sufficient balance
    if (amount > foundAcc->balance)
    {
        cout << "Insufficient funds!\n";
        cout << "Current Balance: Rs "
             << fixed << setprecision(2)
             << foundAcc->balance << endl;
        return;
    }

    // Modify balance using pointer
    foundAcc->balance -= amount;

    // Create transaction
    Transaction transaction;

    transaction.date = getCurrentDate();
    transaction.accountNumber = accNum;
    transaction.type = "Withdraw";
    transaction.amount = amount;
    transaction.balanceAfter = foundAcc->balance;

    transactions.push_back(transaction);

    cout << "\nWithdrawal successful!\n";
    cout << "Withdrawn: Rs "
         << fixed << setprecision(2)
         << amount << endl;

    cout << "New Balance: Rs "
         << foundAcc->balance << endl;
}

// ============================================================
// DISPLAY ALL ACCOUNTS
// ============================================================

void displayAllAccounts()
{
    if (accounts.empty())
    {
        cout << "\nNo accounts!\n";
        return;
    }

    cout << "\n------------------------------------------------------------\n";
    cout << "                    ALL ACCOUNTS\n";
    cout << "------------------------------------------------------------\n";

    cout << left
         << setw(12) << "Account No"
         << setw(20) << "Name"
         << setw(12) << "Type"
         << setw(15) << "Balance (Rs)"
         << endl;

    cout << string(59, '-') << endl;

    for (const auto& acc : accounts)
    {
        cout << left
             << setw(12) << acc.accountNumber
             << setw(20) << acc.customerName
             << setw(12) << acc.accountType
             << setw(15)
             << fixed << setprecision(2)
             << acc.balance
             << endl;
    }
}

// ============================================================
// CHECK BALANCE
// ============================================================

void checkBalance()
{
    if (accounts.empty())
    {
        cout << "\nNo accounts!\n";
        return;
    }

    int accNum;

    cout << "\nAccount Number: ";
    cin >> accNum;

    if (cin.fail())
    {
        clearInput();
        cout << "Invalid account number!\n";
        return;
    }

    Account* foundAcc = findAccount(accNum);

    if (foundAcc == nullptr)
    {
        cout << "Account not found!\n";
        return;
    }

    cout << "\n----------------------------------------\n";
    cout << "           ACCOUNT DETAILS\n";
    cout << "----------------------------------------\n";

    cout << "Account Number: "
         << foundAcc->accountNumber << endl;

    cout << "Customer Name: "
         << foundAcc->customerName << endl;

    cout << "Account Type: "
         << foundAcc->accountType << endl;

    cout << "Created Date: "
         << foundAcc->createdDate << endl;

    cout << "Balance: Rs "
         << fixed << setprecision(2)
         << foundAcc->balance << endl;
}

// ============================================================
// TRANSACTION HISTORY
// ============================================================

void transactionHistory()
{
    if (accounts.empty())
    {
        cout << "\nNo accounts!\n";
        return;
    }

    int accNum;

    cout << "\nAccount Number: ";
    cin >> accNum;

    if (cin.fail())
    {
        clearInput();
        cout << "Invalid account number!\n";
        return;
    }

    Account* foundAcc = findAccount(accNum);

    if (foundAcc == nullptr)
    {
        cout << "Account not found!\n";
        return;
    }

    cout << "\n----------------------------------------\n";
    cout << "          TRANSACTION HISTORY\n";
    cout << "----------------------------------------\n";

    bool found = false;

    for (const auto& transaction : transactions)
    {
        if (transaction.accountNumber == accNum)
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
        cout << "No transactions found for this account.\n";
    }
}

// ============================================================
// SAVE ACCOUNTS
// ============================================================

void saveAccounts()
{
    ofstream file(ACCOUNTS_FILE);

    if (!file)
    {
        cout << "Error saving accounts!\n";
        return;
    }

    file << accounts.size() << endl;

    for (const auto& acc : accounts)
    {
        file << acc.accountNumber << "|"
             << acc.customerName << "|"
             << acc.balance << "|"
             << acc.accountType << "|"
             << acc.createdDate << endl;
    }

    file.close();
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
        Account acc;
        string line;

        if (!getline(file, line))
        {
            break;
        }

        stringstream ss(line);
        string temp;

        try
        {
            // Account number
            getline(ss, temp, '|');
            acc.accountNumber = stoi(temp);

            // Customer name
            getline(ss, acc.customerName, '|');

            // Balance
            getline(ss, temp, '|');
            acc.balance = stod(temp);

            // Account type
            getline(ss, acc.accountType, '|');

            // Created date
            getline(ss, acc.createdDate);

            accounts.push_back(acc);

            // Update next account number
            if (acc.accountNumber >= nextAccountNumber)
            {
                nextAccountNumber = acc.accountNumber + 1;
            }
        }
        catch (...)
        {
            cout << "Invalid account record skipped.\n";
        }
    }

    file.close();
}

// ============================================================
// SAVE TRANSACTIONS
// ============================================================

void saveTransactions()
{
    ofstream file(TRANSACTIONS_FILE);

    if (!file)
    {
        cout << "Error saving transactions!\n";
        return;
    }

    file << transactions.size() << endl;

    for (const auto& transaction : transactions)
    {
        file << transaction.date << "|"
             << transaction.accountNumber << "|"
             << transaction.type << "|"
             << transaction.amount << "|"
             << transaction.balanceAfter << endl;
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
        Transaction transaction;
        string line;

        if (!getline(file, line))
        {
            break;
        }

        stringstream ss(line);
        string temp;

        try
        {
            // Date
            getline(ss, transaction.date, '|');

            // Account number
            getline(ss, temp, '|');
            transaction.accountNumber = stoi(temp);

            // Transaction type
            getline(ss, transaction.type, '|');

            // Amount
            getline(ss, temp, '|');
            transaction.amount = stod(temp);

            // Balance after transaction
            getline(ss, temp);
            transaction.balanceAfter = stod(temp);

            transactions.push_back(transaction);
        }
        catch (...)
        {
            cout << "Invalid transaction record skipped.\n";
        }
    }

    file.close();
}

// ============================================================
// SAVE ALL DATA
// ============================================================

void saveData()
{
    saveAccounts();
    saveTransactions();

    cout << "\nData saved successfully!\n";
    cout << "accounts.dat and transactions.dat have been updated.\n";
}

// ============================================================
// MAIN MENU
// ============================================================

void showMenu()
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
// MAIN FUNCTION
// ============================================================

int main()
{
    // Load previously saved data
    loadAccounts();
    loadTransactions();

    int choice;

    do
    {
        showMenu();

        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail())
        {
            clearInput();

            cout << "\nInvalid input!\n";
            cout << "Please enter a number from 0 to 7.\n";

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
                cout << "\nInvalid choice!\n";
                cout << "Please select a number from 0 to 7.\n";
        }

    } while (choice != 0);

    return 0;
}

