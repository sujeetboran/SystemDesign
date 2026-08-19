#include<iostream>
#include<vector>
#include<initializer_list>
#include<utility>
#include<stdexcept>
template<class T>
class stack{
    private:
        std::vector<T> data;
    public:
        stack(std::initializer_list<T> elements) : data(elements){}
        stack() = default;
        void pop(){
            if(this->empty())
                throw std::underflow_error("pop() called on empty stack");
            data.pop_back();
        }
        void push(const T& val){
            data.push_back(val);
        }
        void push(T&& val){
            data.push_back(std::move(val));
        }
        T& top(){
            if(this->empty())
                throw std::underflow_error("top() called on empty stack");
            return data.back();
        }
        const T& top() const {
            if(this->empty())
                throw std::underflow_error("top() called on empty stack");
            return data.back();
        }
        bool empty() const noexcept{
            return !data.size();
        }
        std::size_t size() const noexcept{
            return data.size();
        }
        void print()const{
            for (auto it = data.rbegin(); it != data.rend(); ++it) {
                std::cout << *it << " ";
            }
        }
};
int main(){
}