#include <format>
#include <iostream>

using namespace std;

template <typename T, typename U>
class MyClass
{
   private:
    T data1;
    U data2;

   public:
    MyClass(T data1, U data2) : data1(data1), data2(data2) { this->data1 = data1; }

    auto getMyProps()
    {
        cout << "Instancia placeholder presenta los siguientes datos:" << endl;
        cout << std::format("Data 1: {}\nData 2: {}", data1, data2);
    }
};

template <typename T>
T sum(T a, T b)

{
    return a + b;
}

int main()
{
    auto placeholder = MyClass<int, double>{42, 3.14};

    int param1 = 2;
    int param2 = 2;

    int res = sum(param1, param2);
    cout << std::format("El resultado de {} y {} es: {}", param1, param2, res) << endl;
    cout << "/// PROPS ///" << endl;
    placeholder.getMyProps();
    return 0;
}
