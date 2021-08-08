#include <iostream>
#include <vector>
#include <initializer_list>

using namespace std;
class TestInit
{
    private:
        int m_a;
        int m_b;

    public:
        TestInit(int a, int b)
            : m_a(a),
            m_b(b) {}

        TestInit(initializer_list<int> list)
            : m_a(*list.begin()),
            m_b(*(list.begin() + 1)) {}

        friend ostream& operator <<(ostream& os, const TestInit& val) {
            os << "(" << val.m_a << "," << val.m_b << ")" << std::endl;
            return os;
        }
};

constexpr int sum(const int v)
{
    if (0 == v) return 0;

    return sum(v - 1) + v;
}

std::tuple<int, double, string> get_tuple()
{
    return std::make_tuple(1, 2.3, "456");
}

// template<class A, class B>
// auto func(A a, B b)
// {
//     return a + b;
// }

// template<class T>
// auto test(const T& t)
// {
//     if constexpr (std::is_integral<T>::value)
//     {
//         return 1;
//     } else
//     {
//         return 0;
//     }
// }

// int func2(int v)
// {
//     if (auto n = 10; n > v) {
//         return -1;
//     } else {
//         return 0;
//     }
// }

constexpr int func3(int v)
{
    return v % 100;
}

class Object {
    private:
        int m_v;

    public:
        // Object() {
        //     std::cout << "empty object..." << std::endl;
        // }
        Object(int v) {
            m_v = v;
            std::cout << "new object..." << v << std::endl;
        }

        Object(const Object& obj) {
            std::cout << "copy object..." << std::endl; 
        }

        Object(Object && obj) {
            std::cout << "move object..." << std::endl;
        }

        ~Object() {
            std::cout << "delete object ..." << std::endl;
        }

        void hello() {
            std::cout << "hello" << std::endl;
        }
};

class Derived : public Object
{
    public:
        using Object::Object;
};

auto func_auto(int v) {
    Object obj(v);
    {
        std::vector<Object> objs;
        Object obj2(1);
        objs.push_back(std::move(obj2));
    }
    std::cout << "function..." << std::endl;
    Object& obj2 = obj;
    return obj2;
}

decltype(auto) func_auto2(int v) {
    return func_auto(v);
}

template<typename ... Args> 
int sum_args(Args ... args) {
    return 0 == sizeof...(args) ? 0 : sum_args(args...);
}

template<typename T, typename ... Args>
int sum_args(T v, Args ... args) {
    return v + (0 == sizeof...(args) ? 0 : sum_args(args...));
}

// template<typename ... Args> 
// int sum_args(Args ... args) {
//     return 0 == sizeof...(args) ? 0 : sum_args(args...);
// }

int main()
{
    TestInit t = {1, 2};
    std::cout << t;

    auto tuple = get_tuple();
    std::cout << std::get<0>(tuple) << "," << std::get<1>(tuple) << "," << std::get<2>(tuple) << std::endl;
    int vv = sum(100);
    std::cout << vv << std::endl;

    auto [a, b, c] = get_tuple();
    std::cout << a << "," << b << "," << c << std::endl;

    // std::cout << func(1, 2.34) << std::endl;

    // std::cout << test(1) << std::endl;
    // std::cout << test(1.1) << std::endl;

    // std::cout << func2(3) << std::endl;
    // std::cout << func2(30) << std::endl;

    std::cout << func3(std::get<0>(get_tuple())) << std::endl;

    if (int t = 10; t > a) {
        std::cout << "bigger" << std::endl;
    }

    auto obj = func_auto2(10);
    obj.hello();

    std::cout << std::is_same<decltype(obj), Object&>() << std::endl;

    std::cout << sum_args(1, 2, 3, 4, 5, 6) << std::endl;

    Derived d(10);
    d.hello();
    return 0;
}