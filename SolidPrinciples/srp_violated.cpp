#include <iostream>
#include <vector>
#include <string>
using namespace std;

// -----------------------------------------------
// Class 1: ShoppingCart
// Responsibility: ONLY manages cart items
//                and calculates total
// -----------------------------------------------
class ShoppingCart {
private:
    vector<pair<string, double>> items; // {productName, price}

public:
    // Add item to cart
    void addItem(string name, double price) {
        items.push_back({name, price});
        cout << "Item added: " << name << " - $" << price << endl;
    }

    // Calculate total price
    double calculateTotal() const {
        double total = 0;
        for (const auto& item : items) {
            total += item.second;
        }
        return total;
    }

    // Getter so other classes can access items
    vector<pair<string, double>> getItems() const {
        return items;
    }
};


// -----------------------------------------------
// Class 2: CartDBStorage
// Responsibility: ONLY handles saving cart to DB
// -----------------------------------------------
class CartDBStorage {
private:
    // Takes a reference to ShoppingCart
    const ShoppingCart& cart;

public:
    // Constructor takes ShoppingCart reference
    CartDBStorage(const ShoppingCart& cart) : cart(cart) {}

    void saveToDB() {
        cout << "\n--- Saving Cart to Database ---" << endl;
        for (const auto& item : cart.getItems()) {
            // Imagine this is saving to a real DB
            cout << "Saved to DB: "
                 << item.first
                 << " | Price: $"
                 << item.second
                 << endl;
        }
        cout << "Cart successfully saved to DB!" << endl;
    }
};


// -----------------------------------------------
// Class 3: CartInvoicePrinter
// Responsibility: ONLY handles printing invoice
// -----------------------------------------------
class CartInvoicePrinter {
private:
    // Takes a reference to ShoppingCart
    const ShoppingCart& cart;

public:
    // Constructor takes ShoppingCart reference
    CartInvoicePrinter(const ShoppingCart& cart) : cart(cart) {}

    void printInvoice() {
        cout << "\n==============================" << endl;
        cout << "         INVOICE              " << endl;
        cout << "==============================" << endl;

        for (const auto& item : cart.getItems()) {
            cout << "Product : " << item.first << endl;
            cout << "Price   : $" << item.second << endl;
            cout << "------------------------------" << endl;
        }

        cout << "Total   : $" << cart.calculateTotal() << endl;
        cout << "==============================" << endl;
        cout << "   Thank you for shopping!    " << endl;
        cout << "==============================" << endl;
    }
};


// -----------------------------------------------
// Main Function - Putting it all together
// -----------------------------------------------
int main() {

    // Step 1: Create the shopping cart
    ShoppingCart myCart;

    // Step 2: Add items to the cart
    myCart.addItem("Apple iPhone 15", 999.99);
    myCart.addItem("AirPods Pro",     249.99);
    myCart.addItem("iPhone Case",      29.99);

    // Step 3: Show total (ShoppingCart's responsibility)
    cout << "\nCart Total: $" << myCart.calculateTotal() << endl;

    // Step 4: Save to DB (CartDBStorage's responsibility)
    // Pass cart reference to CartDBStorage
    CartDBStorage dbStorage(myCart);
    dbStorage.saveToDB();

    // Step 5: Print Invoice (CartInvoicePrinter's responsibility)
    // Pass cart reference to CartInvoicePrinter
    CartInvoicePrinter invoicePrinter(myCart);
    invoicePrinter.printInvoice();

    return 0;
}