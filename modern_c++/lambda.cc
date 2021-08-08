#include <iostream>

class Object
{
    private:
        int m_val = 1;

    public:
        Object()
        {
            std::cout << "new object ..." << std::endl;
        }

        Object(const Object& obj)
        {
            std::cout << "copy object ..." << std::endl;
            m_val = 2;
        }

        Object(Object &&obj)
        {
            std::cout << "move object ..." << std::endl;
            m_val = 3;
        }

        Object& operator= (const Object &obj)
        {
            std::cout << "assign object ..." << std::endl;
            m_val = 4;
            return *this;
        }

        void SetValue(int val) {
            std::cout << "set new value = " << val << std::endl;
            m_val = val;
        }

        void Print() {
            std::cout << "value = " << m_val << std::endl;
        }

        ~Object()
        {
            std::cout << "destory value = " << m_val << std::endl;
        }
};

Object return_obj(const Object& obj)
{
    Object obj2;
    return obj2;
}

Object return_move_obj(const Object& obj)
{
    Object obj2;
    return std::move(obj2);
}

void test_lambda_pass_by_value()
{
    Object obj;
    auto func = [obj]() {       // copy object
        return obj;
    };

    obj.SetValue(10);
    // auto obj2 = func();         // copy return object.
    auto obj3 = std::move(func());
    // obj3 = obj;
    obj3.Print();
    // obj2.Print();
    obj.Print();
}

int main()
{
    test_lambda_pass_by_value();

    Object obj;
    Object obj2 = return_obj(obj);

    Object obj3 = return_move_obj(obj);
}