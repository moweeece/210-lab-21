// COMSC-210 | Mauricio Espinosa | Lab 21
// IDE Used: Visual Studios Code & Github

#include <iostream>
#include <ctime> // for seeding time
#include <cstdlib> // for randoms
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;
const int ARR_SIZE = 15;
const int MIN_AGE = 1, MAX_AGE = 20;

class Goat {
    private:
    int age;
    string name;
    string color;
    string names[ARR_SIZE] {"Steve", "Mo", "Dani", "Michael", "Grant", "Vida", "Patty", "Mochi", "Brian", "Kelly", "Fluffy", "Dawn", "Bill", "Brent", "Tron"};
    string colors[ARR_SIZE] {"Red", "Blue", "White", "Grey", "Black", "Orange", "Purple", "Yellow", "Teal", "Mauve", "Silver", "Gold", "Brown", "Pink", "Green"};

    public:
    // constructor
    Goat() {
        age = rand() % (MAX_AGE - MIN_AGE + 1) + MIN_AGE;   // random age between 1 and 20
        name = names[rand() % ARR_SIZE];                        // random name from the array
        color = colors[rand() % ARR_SIZE];                      // random color from the array
    }

    // parameter constructor
    Goat(int a, string n, string c)  { age = a; name = n; color = c; }
    
};

class DoublyLinkedList {
private:
    struct Node {
        Goat data;
        Node* prev;
        Node* next;
        Node(const Goat& goat, Node* p = nullptr, Node* n = nullptr) {
            data = goat; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(const Goat& goat) {
        Node* newNode = new Node(goat);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(const Goat& goat) {
        Node* newNode = new Node(goat);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void delete_node(int value) {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }

    void print() {
        if (!head) {
            cout << "List is empty!" << endl;
        }
        Node* current = head;
        if (!current) return;
        while (current) {
            current->data.print();
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        if (!tail) {
            cout << "List is empty!" << endl;
        }
        Node* current = tail;
        if (!current) return;
        while (current) {
            current->data.print();
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
    srand(time(0)); // seed time for random

    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    // append a random number of goat objects (quantity 5-20)
    for (int i = 0; i < size; ++i)
    {
        Goat g;
        list.push_back(g);
    }
        
        
    cout << "List forward: ";
    list.print();

    cout << "List backward: ";
    list.print_reverse();

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();

    return 0;
}
