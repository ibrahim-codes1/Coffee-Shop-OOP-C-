# ☕ Coffee Shop Management System

An advanced C++ console application designed to handle the daily operations of a coffee shop. This project is built using Object-Oriented Programming (OOP) principles to ensure the code remains maintainable and scalable.

---

# ✨ Features

- **Dynamic Menu:** Displays a list of coffee items such as Espresso, Latte, Mocha, etc.
- **Smart Ordering:** Users can select items and choose their desired quantity.
- **Polymorphic Display:** Uses inheritance to handle drinks and regular menu items efficiently.
- **Order History:** All successful orders are automatically saved in `order_history.txt`.
- **Input Validation:** Prevents program crashes by handling invalid user input properly.

---

# 🛠️ Technical Highlights (OOP Concepts)

## Inheritance
The `Drink` class inherits from the `MenuItem` class.

## Polymorphism
Uses `virtual void display()` to call the correct function at runtime.

## STL (Standard Template Library)

- `std::vector` is used to store menu items.
- `std::map` is used to track item quantities and subtotals.

## Encapsulation
Data members are kept private/protected for better security and structure.

---

# 🚀 Installation & Compilation

## Prerequisites

You must have a C++ compiler such as GCC or MinGW installed.

## Compile

```bash
g++ main.cpp -o CoffeeShop
```

## Run

```bash
./CoffeeShop
```

---

# 📂 File Output

When the user checks out, the system creates an `order_history.txt` file that looks like this:

```text
Order ID: 1

Item                Unit Price     Quantity       Subtotal
Cappuccino (Medium) $3.50          2              $7.00
Latte (Large)       $4.00          1              $4.00

Total Amount: $11.00
--------------------------
```

---

# 💡 Developer Feedback

## Memory Management
Objects are dynamically created using `new`, and properly deleted inside the `~CoffeeShop` destructor. This helps prevent memory leaks and demonstrates good memory management practices.

## Smart Mapping Logic
Using `map<string, pair<double, int>>` in the order system is a smart approach. It automatically handles duplicate items and updates quantities efficiently.

## Future Improvement Idea
A **Discount Coupon** feature could be added to apply percentage-based discounts on the total bill.
