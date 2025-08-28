#include <bits/stdc++.h>
using namespace std;

struct Item
{
    int id{};
    string name;
    int qty{};
    double price{};
};

static const string DB_FILE = "inventory.csv";

vector<Item> loadDB()
{
    vector<Item> v;
    ifstream f(DB_FILE);
    string line;
    while (getline(f, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        string sid, name, sqty, sprice;
        getline(ss, sid, ',');
        getline(ss, name, ',');
        getline(ss, sqty, ',');
        getline(ss, sprice, ',');
        v.push_back({stoi(sid), name, stoi(sqty), stod(sprice)});
    }
    return v;
}
void saveDB(const vector<Item> &v)
{
    ofstream f(DB_FILE);
    for (auto &it : v)
        f << it.id << "," << it.name << "," << it.qty << "," << it.price << "\n";
}
int findById(const vector<Item> &v, int id)
{
    for (size_t i = 0; i < v.size(); ++i)
        if (v[i].id == id)
            return (int)i;
    return -1;
}
void addItem(vector<Item> &v)
{
    Item it;
    cout << "ID: ";
    cin >> it.id;
    if (findById(v, it.id) != -1)
    {
        cout << "ID exists.\n";
        return;
    }
    cout << "Name: ";
    cin >> ws;
    getline(cin, it.name);
    cout << "Qty: ";
    cin >> it.qty;
    cout << "Price: ";
    cin >> it.price;
    v.push_back(it);
    cout << "✔ Added.\n";
}
void updateQty(vector<Item> &v)
{
    int id, delta;
    cout << "Item ID: ";
    cin >> id;
    int i = findById(v, id);
    if (i == -1)
    {
        cout << "Not found.\n";
        return;
    }
    cout << "Change (+/-): ";
    cin >> delta;
    v[i].qty += delta;
    cout << "New qty: " << v[i].qty << "\n";
}
void sellItem(vector<Item> &v)
{
    int id, q;
    cout << "Item ID: ";
    cin >> id;
    int i = findById(v, id);
    if (i == -1)
    {
        cout << "Not found.\n";
        return;
    }
    cout << "Sell quantity: ";
    cin >> q;
    if (q > v[i].qty)
    {
        cout << "Insufficient stock.\n";
        return;
    }
    v[i].qty -= q;
    cout << "Sold. Revenue: " << q * v[i].price << "\n";
}
void searchName(const vector<Item> &v)
{
    cout << "Keyword: ";
    string k;
    cin >> ws;
    getline(cin, k);
    cout << "Results:\n";
    for (auto &it : v)
        if (it.name.find(k) != string::npos)
            cout << it.id << " " << it.name << " qty=" << it.qty << " price=" << it.price << "\n";
}
void report(const vector<Item> &v)
{
    cout << "\nID   NAME                 QTY    PRICE   VALUE\n";
    double total = 0;
    for (auto &it : v)
    {
        double val = it.qty * it.price;
        total += val;
        cout << setw(4) << it.id << " " << left << setw(20) << it.name << right
             << setw(6) << it.qty << " " << setw(7) << fixed << setprecision(2) << it.price
             << " " << setw(8) << val << "\n";
    }
    cout << "Total inventory value: " << total << "\n";
}
int main()
{
    vector<Item> items = loadDB();
    while (true)
    {
        cout << "\n=== Inventory ===\n"
             << "1) Add Item\n2) Adjust Qty\n3) Sell Item\n4) Search by Name\n5) Report\n6) Save & Exit\nChoice: ";
        int c;
        if (!(cin >> c))
            break;
        if (c == 1)
            addItem(items);
        else if (c == 2)
            updateQty(items);
        else if (c == 3)
            sellItem(items);
        else if (c == 4)
            searchName(items);
        else if (c == 5)
            report(items);
        else if (c == 6)
        {
            saveDB(items);
            cout << "Saved. Bye!\n";
            break;
        }
        else
            cout << "Invalid.\n";
    }
    return 0;
}
