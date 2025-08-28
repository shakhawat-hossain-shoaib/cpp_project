#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Transaction
{
    string type;
    string category;
    double amount;
};

class ExpenseTracker
{
private:
    vector<Transaction> transactions;

public:
    void addTransaction(string type, string category, double amount)
    {
        Transaction t = {type, category, amount};
        transactions.push_back(t);
        cout << "Transaction added successfully!\n";
    }

    void showSummary()
    {
        double income = 0, expense = 0;
        for (auto &t : transactions)
        {
            if (t.type == "Income") income += t.amount;
            else expense += t.amount;
        }
        cout << "\n===== Summary =====\n";
        cout << "Total Income: " << income << endl;
        cout << "Total Expense: " << expense << endl;
        cout << "Net Savings: " << (income - expense) << endl;
    }

    void saveToFile()
    {
        ofstream file("transactions.txt");
        for (auto &t : transactions)
        {
            file << t.type << " " << t.category << " " << t.amount << endl;
        }
        file.close();
        cout << "Data saved to transactions.txt\n";
    }
};

int main()
{
    ExpenseTracker tracker;
    int choice;
    string type, category;
    double amount;

    while (true)
    {
        cout << "\n===== Expense Tracker =====\n";
        cout << "1. Add Income\n";
        cout << "2. Add Expense\n";
        cout << "3. Show Summary\n";
        cout << "4. Save & Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "Enter category: ";
            cin >> category;
            cout << "Enter amount: ";
            cin >> amount;
            tracker.addTransaction("Income", category, amount);
        }
        else if (choice == 2)
        {
            cout << "Enter category: ";
            cin >> category;
            cout << "Enter amount: ";
            cin >> amount;
            tracker.addTransaction("Expense", category, amount);
        }
        else if (choice == 3)
        {
            tracker.showSummary();
        }
        else if (choice == 4)
        {
            tracker.saveToFile();
            break;
        }
        else
        {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
