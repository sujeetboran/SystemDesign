#include<iostream>
#include<stdexcept>
#include<memory>
#include<utility>
template<class T>
struct node{
    T val;
    std::shared_ptr<node<T>> next;
    std::weak_ptr<node<T>> prev;
    node(const T& val): val(val){}
    node(T&& val): val(std::move(val)){}
};
template<class T>
class stack{
    private:
        std::shared_ptr<node<T>> head = nullptr, tail = nullptr;
        int length = 0;
        void push_node(std::shared_ptr<node<T>> new_node){
            if(head == nullptr)
                head=tail=std::move(new_node);
            else{
                tail->next = new_node;
                new_node->prev = tail;
                tail = tail->next;
            }
            length++;
        }
    public:
        stack() = default;
        stack(const stack& other){
            std::shared_ptr<node<T>> curr_node = other.head;
            while(curr_node){
                this->push(curr_node->val);
                curr_node = curr_node->next;
            }
        }
        stack& operator=(const stack& other){
            if (this != &other) {
                while (!this->empty()) {
                    this->pop();
                }
                std::shared_ptr<node<T>> curr_node = other.head;
                while(curr_node){
                    this->push(curr_node->val);
                    curr_node = curr_node->next;
                }
            }
            return *this;
        }
        void pop(){
            if(this->empty())
                throw std::underflow_error("pop() called on empty stack");
            if(head==tail){
                head=tail=nullptr;
            }else{
                tail = tail->prev.lock();
                tail->next = nullptr;
            }
            length--;
        }
        void push(const T& val){
            push_node(std::make_shared<node<T>>(val));
        }
        void push(T&& val){
            push_node(std::make_shared<node<T>>(std::move(val)));
        }
        std::size_t size() const noexcept{
            return length;
        }
        bool empty() const noexcept {
            return !length;
        }
        T& top(){
            if(this->empty())
                throw std::underflow_error("top() called on empty stack");
            return tail->val;
        }
        const T& top() const {
            if(this->empty())
                throw std::underflow_error("top() called on empty stack");
            return tail->val;
        }
        void print() const {
            std::shared_ptr<node<T>> temp = tail;
            while(temp){
                std::cout<<temp->val<<" ";
                temp = temp->prev.lock();
            }
            std::cout<<"\n";
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