//
//  main.cpp
//  sperasoft_test_task
//
//  Created by Евгений Курятов on 14.10.2021.
//

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>

template <class T>
class PriorityItem {
public:
    T item;
    int priority;
public:
    PriorityItem (int priority, T item)
    : item(item)
    , priority(priority) {}
};

template <class T>
std::ostream& operator << (std::ostream& os, PriorityItem<T> item) {
    os << "Priority: " << item.priority << " Item: " << item.item;
    return os;
}

template <class T>
class PriorityStack {
public:
    PriorityStack();
    void Push(int priority, T value);
    T Pop();
    bool IsEmpty();
    void Clear();
    void PrintStack();
private:
    std::vector<PriorityItem<T>> stack;
private:
    PriorityItem<T>* next_item;
};

template <class T>
PriorityStack<T>::PriorityStack() {
}

template <class T>
void PriorityStack<T>::Push(int priority, T value) {
    stack.push_back(PriorityItem(priority, value));
}

template <class T>
T PriorityStack<T>::Pop() {
    if (stack.size() > 0) {
        PriorityItem<T> item_to_pop = stack.back();
        int iteration = 0;
        int item_offset = iteration;
        for (auto item =  stack.rbegin(); item != stack.rend(); ++item) {
            if (item->priority > item_to_pop.priority) {
                item_to_pop = *item;
                item_offset = iteration;
            }
            iteration++;
        }
        std::cout << item_to_pop << std::endl;
        auto item_to_delete = stack.end()-item_offset-1;
        stack.erase(item_to_delete);
        return item_to_pop.item;
    }
    std::cout << "Stack is empty" << std::endl;
    return T();
}

template <class T>
bool PriorityStack<T>::IsEmpty() {
    if (stack.size() > 0) return false;
    return true;
}

template <class T>
void PriorityStack<T>::Clear() {
    stack.clear();
}

template <class T>
void PriorityStack<T>::PrintStack() {
    for (PriorityItem<T> item : stack) {
        std::cout << item << std::endl;
    }
}

void print_header(std::string header, int length) {
    std::string bracketed_header = std::string("[ ").append(header);
    bracketed_header = bracketed_header.append(" ]");
    std::cout << "\n" << std::setw(length) << std::setfill('-') << bracketed_header << std::endl;
}

int main() {
    std::srand(std::time(0));
    PriorityStack<std::string> test_stack;
    int string_length = 46;
    
    print_header("Fill stack and print it", string_length);
    for (int i=1; i <= 10; i++) {
        int priority = std::rand() % 10;
        test_stack.Push(priority, std::string("Random object with prority ").append(std::to_string(priority)));
    }
    test_stack.PrintStack();
    
    print_header("Pop values", string_length);
    test_stack.Pop();
    test_stack.Pop();
    test_stack.Pop();
    
    print_header("Print stack", string_length);
    test_stack.PrintStack();
    
    print_header("Cleared stack", string_length);
    test_stack.Clear();
    test_stack.PrintStack();
    
    print_header("If stack is empty refill it", string_length);
    if (test_stack.IsEmpty()){
        for (int i=1; i <= 10; i++) {
            int priority = std::rand() % 10;
            test_stack.Push(priority, std::string("Random object with prority ").append(std::to_string(priority)));
        }
    }
    test_stack.PrintStack();
    return 0;
}
