#include <iostream>
#include <vector>

int& func()
{
    int a = 10;
    return a;
}

int fun2(int& a) {
    return a;
}

std::string test(const std::string& s1, const std::string &s2)
{
    return s1 + s2;
}

class Holder
{
    private:
        int *data_;
        int size_;
    public:
        Holder(int size) {
            data_ = new int[size];
            size_ = size;
            std::cout << "construct..." << std::endl;
        }

        ~Holder() {
            std::cout << "deconstruct..." << data_ << "," << this << std::endl;
            delete[] data_;
        }

        int size() {
            return size_;
        }

        Holder(const Holder &other) {
            std::cout << "copy construct ..." << std::endl;
            size_ = other.size_;
            data_ = new int[size_];
            memcpy(data_, other.data_, sizeof(int) * size_);
        }

        Holder& operator=(const Holder& other) {
            if (this == &other) return *this;
            std::cout << "copy assign ..." << std::endl;
            delete[] data_;
            size_ = other.size_;
            data_ = new int[size_];
            memcpy(data_, other.data_, sizeof(int) * size_);

            return *this;
        }

        Holder(Holder &&other) {
            std::cout << "move construct ..." << std::endl;
            data_ = other.data_;
            size_ = other.size_;

            other.data_ = nullptr;
            other.size_ = 0;
        }
};

// Holder& holder()
// {
//     Holder h(10);
//     return h;
// }

Holder holder()
{
    Holder h(10);
    std::cout << "h = " << &h << std::endl;
    return h;
}

int main()
{
    // int a = 10;
    // func() = a;
    // int& b = 10;
    
    // func2(10);

    std::string   s1     = "Hello ";
    std::string   s2     = "world";
    std::string&& s_rref = s1 + s2;    // the result of s1 + s2 is an rvalue
    s_rref += ", my friend";           // I can change the temporary string!
    std::cout << s_rref << '\n';       // prints "Hello world, my friend"

    std::string&& s3 = test(s1, s2);
    s3 += " 123";
    std::cout << s3 << std::endl;

    int&& v = 10;
    v ++;
    std::cout << "===" << v << std::endl;

    int v2 = v;

    Holder h1 = 100;
    Holder h2 = h1;
    h1 = h2;

    std::cout << "=========" << std::endl;
    auto h = holder();
    std::cout << "h = " << &h << std::endl;
    std::cout << "=========" << std::endl;
    std::cout << h.size() << std::endl;

    std::vector<Holder> vec;
    vec.push_back(h);
    return 0;
}
