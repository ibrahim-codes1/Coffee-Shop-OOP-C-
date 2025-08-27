#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
#include <map>
#include <limits>

using namespace std;

// Base class: MenuItem
class MenuItem {
protected:
    string name;
    double price;

public:
    MenuItem(string n, double p) : name(n), price(p) {}
    virtual void display() {
        cout << setw(15) << name << " | $" << fixed << setprecision(2) << price << endl;
    }
    double getPrice() { return price; }
    string getName() { return name; }
};

// Derived class: Drink
class Drink : public MenuItem {
private:
    string size;

public:
    Drink(string n, double p, string s) : MenuItem(n, p), size(s) {}
    void display() {
        cout << setw(15) << name << " (" << size << ")" << " | $" << fixed << setprecision(2) << price << endl;
    }
    string getSize() { return size; }
};

// Order class
class Order {
private:
    map<string, pair<double, int> > orderItems;
    static int orderCounter;
    int orderID;

public:
    Order() {
        orderID = ++orderCounter;
    }

    static int getOrderCounter() { return orderCounter; }

    void addItem(MenuItem* item) {
        string itemName = item->getName();
        double itemPrice = item->getPrice();

        if (orderItems.find(itemName) != orderItems.end()) {
            orderItems[itemName].second++;
        } else {
            orderItems[itemName] = make_pair(itemPrice, 1);
        }
    }

    void displayOrder() {
        if (orderItems.empty()) {
            cout << "\n--- Your Order is Empty ---\n";
            return;
        }

        cout << left << setw(20) << "Item" << setw(15) << "Unit Price"
             << setw(15) << "Quantity" << "Subtotal\n";
        double total = 0.0;

        map<string, pair<double, int> >::iterator it;
        for (it = orderItems.begin(); it != orderItems.end(); ++it) {
            string name = it->first;
            double price = it->second.first;
            int quantity = it->second.second;
            double subtotal = price * quantity;

            cout << left << setw(20) << name
                 << "$" << setw(14) << price
                 << setw(15) << quantity
                 << "$" << subtotal << endl;

            total += subtotal;
        }
        cout << "\nTotal Amount: $" << fixed << setprecision(2) << total << endl;
    }

    double calculateTotal() {
        double total = 0.0;
        map<string, pair<double, int> >::iterator it;
        for (it = orderItems.begin(); it != orderItems.end(); ++it) {
            total += it->second.first * it->second.second;
        }
        return total;
    }

    void saveOrderToFile() {
        ofstream file("order_history.txt", ios::app);
        if (file.is_open()) {
            file << "Order ID: " << orderID << "\n";
            file << left << setw(20) << "Item" << setw(15) << "Unit Price"
                 << setw(15) << "Quantity" << "Subtotal\n";
            map<string, pair<double, int> >::iterator it;
            for (it = orderItems.begin(); it != orderItems.end(); ++it) {
                file << left << setw(20) << it->first
                     << "$" << setw(14) << it->second.first
                     << setw(15) << it->second.second
                     << "$" << it->second.first * it->second.second << "\n";
            }
            file << "Total Amount: $" << fixed << setprecision(2) << calculateTotal() << "\n";
            file << "--------------------------\n";
            file.close();
        }
    }

    void clearOrder() { orderItems.clear(); }
};

int Order::orderCounter = 0;

// CoffeeShop class
class CoffeeShop {
private:
    vector<MenuItem*> menu;
    Order currentOrder;

public:
    CoffeeShop() {
        menu.push_back(new Drink("Espresso", 2.50, "Small"));
        menu.push_back(new Drink("Cappuccino", 3.50, "Medium"));
        menu.push_back(new Drink("Latte", 4.00, "Large"));
        menu.push_back(new Drink("Americano", 2.00, "Small"));
        menu.push_back(new Drink("Mocha", 3.75, "Medium"));
    }

    ~CoffeeShop() {
        for (size_t i = 0; i < menu.size(); ++i) {
            delete menu[i];
        }
    }

    void displayMenu() {
        cout << "\n--- Coffee Shop Menu ---\n";
        for (size_t i = 0; i < menu.size(); ++i) {
            cout << i + 1 << ". ";
            menu[i]->display();
        }
    }

    void takeOrder() {
        int choice = -1, quantity = 0;

        while (true) {
            displayMenu();
            cout << "\nEnter the item number to order (0 to finish): ";

            while (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number: ";
            }

            if (choice == 0) break;

            if (choice < 1 || choice > (int)menu.size()) {
                cout << "Invalid choice. Try again.\n";
            } else {
                cout << "Enter quantity: ";
                while (!(cin >> quantity) || quantity <= 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid quantity. Please enter a positive number: ";
                }

                for (int i = 0; i < quantity; ++i) {
                    currentOrder.addItem(menu[choice - 1]);
                }
                cout << "Item(s) added to order.\n";
            }
        }
    }

    void showOrder() {
        currentOrder.displayOrder();
    }

    void checkout() {
        currentOrder.displayOrder();
        double total = currentOrder.calculateTotal();
        if (total == 0.0) {
            cout << "\nNo items to checkout!\n";
            return;
        }
        currentOrder.saveOrderToFile();
        currentOrder.clearOrder();
        cout << "Order placed successfully!\n";
    }
};

// Main function
int main() {
    CoffeeShop shop;
    int choice;

    do {
        cout << "\n--- Welcome to the Coffee Shop ---\n";
        cout << "1. View Menu\n";
        cout << "2. Place Order\n";
        cout << "3. Show Current Order\n";
        cout << "4. Checkout\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number: ";
        }

        switch (choice) {
        case 1:
            shop.displayMenu();
            break;
        case 2:
            shop.takeOrder();
            break;
        case 3:
            shop.showOrder();
            break;
        case 4:
            shop.checkout();
            break;
        case 5:
            cout << "Thank you for visiting the Coffee Shop!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}

