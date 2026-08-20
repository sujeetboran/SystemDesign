#include<iostream>
#include<memory>
#include <stdexcept>
#include<utility>
template<class T>
struct node {
    T val;
    std::unique_ptr<node<T>> next = nullptr;

    node(const T& val) : val(val) {}
    node(T&& val) : val(std::move(val)) {}
};
template<class T>
class stack{
    private:
        int size = 0;
        std::unique_ptr<node<T>> head = nullptr;
    public:
        stack() = default;
        stack(const stack<T>& other) : size(other.size) {
            if(other.head == nullptr)
                return;
            head = std::make_unique<node<T>>(other.head->val);
            node<T>* temp1 = head.get();
            node<T>* temp2 = other.head->next.get();
            while (temp2) {
                temp1->next = std::make_unique<node<T>>(temp2->val);
                temp1 = temp1->next.get();
                temp2 = temp2->next.get();
            }
        }
        stack& operator=(stack<T> other) {
            head = std::move(other.head);
            size = other.size; 
            return *this;
        }
        void pop(){
            if(this->is_empty())
                throw std::underflow_error("pop() called on empty stack");
            head = std::move(head->next);
            size--;
        }
        void push(const T& val){
            std::unique_ptr<node<T>> new_node = std::make_unique<node<T>>(val);
            new_node->next = std::move(head);
            head = std::move(new_node);
            size++;
        }
        void push(T&& val) {
            auto new_node = std::make_unique<node<T>>(std::move(val));
            new_node->next = std::move(head);
            head = std::move(new_node);
            size++;
        }

        const T& top() const {
            if (is_empty())
                throw std::underflow_error("top() called on empty stack");
            return head->val;
        }

        T& top() {
            if (is_empty())
                throw std::underflow_error("top() called on empty stack");
            return head->val;
        }

        bool is_empty() const noexcept {
            return head == nullptr;
        }

        int length() const noexcept {
            return size;
        }

};
int main() {
    stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);

    stack<int> s_copy = s;
    s_copy.pop();

    std::cout << "Original top: " << s.top() << "\n";
    std::cout << "Copied top:   " << s_copy.top() << "\n";
}