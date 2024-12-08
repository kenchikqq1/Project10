#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


struct Product {
    string name;
    int quantity;
    double price;
};


void writeToFile(const string& filename, const vector<Product>& products) {
    ofstream file;
    file.open(filename);

    for (const auto& product : products) {
        file << product.name << endl << product.quantity << endl << product.price << endl;
    }

    file.close();
}


vector<Product> readFromFile(const string& filename) {
    ifstream file(filename);
    vector<Product> products;
    Product product;

    while (getline(file, product.name) && file >> product.quantity >> product.price) {
        file.ignore(); // Игнорируем символ новой строки после цены
        products.push_back(product);
    }

    file.close();
    return products;
}


void displayProducts(const vector<Product>& products) {
    cout << "Id | Название    | Кол-во | Цена" << endl;
    cout << "---|-------------|--------|------" << endl;
    for (size_t i = 0; i < products.size(); ++i) {
        cout << i + 1 << ") " << products[i].name << " | "
            << products[i].quantity << " | "
            << products[i].price << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<Product> products;
    string filename;

    cout << "Введите имя файла для записи данных: ";
    cin >> filename;

    
    ifstream file(filename);
    if (file.good()) {
        cout << "Файл уже существует. Хотите (1) дополнить или (2) перезаписать его? (1/2): ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            products = readFromFile(filename);
        }
       
    }

    
    for (int i = 0; i < 3; ++i) {
        Product product;
        cout << "Введите название товара " << (i + 1) << ": ";
        cin >> product.name;
        cout << "Введите количество товара " << (i + 1) << ": ";
        cin >> product.quantity;
        cout << "Введите цену товара " << (i + 1) << ": ";
        cin >> product.price;

        products.push_back(product);
    }

    writeToFile(filename, products);

    
    cout << "\nТаблица товаров:\n";
    displayProducts(products);

    return 0;
}