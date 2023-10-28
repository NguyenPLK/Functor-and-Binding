#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

class Compare {
public:
    // In this case, the operator () overloading function in this class which has 3 arguments.
    // Perhaps, in the function body of std::sort, we are just allowed to pass 2 arguments to compare each others.
    // So, we must use std::bind to cover the third argument. In order to pass the function object in elegal way to the std::sort function
    bool operator() (int first, int second, bool _ascending) {
        if (_ascending)
            return first < second; // ascending order
        else
            return first > second; // descending order
    }

};

class Display {
public:
    // Operator take 1 argument to print
    void operator()(int something) {
        std::cout << something << " ";
    }
};

int main() {
    std::vector<int> data_list{ 1,5,6,3,2,7,8,9,4 };

    Display visualizer;
    std::cout << "Initial list:" << std::endl;
    // we passed visualizer function object 
    // as argument of function for_each
    std::for_each(data_list.begin(), data_list.end(), visualizer);
    std::cout << std::endl;

    std::cout << "Sorted ascending:" << std::endl;
    bool Ascending{ true };

    ///// --------------------------- Initualize an instant object ---------------------------
    Compare ascen;
    // Passing an object to std::bind
    auto ptr_func_1 = std::bind(ascen, std::placeholders::_1,std::placeholders::_2,Ascending);

    ///// --------------------------- Initualize an function object via lambdas ---------------------------
    // We are also allowed to create a function object via the lamdbas method, which will be handled by a fucntion pointer.
    // Passing that function pointer which is holding the lambdas is the same way to pass the object to the std::bind
    auto lambdas_1 = [](int& first, int& second, bool _ascending) -> bool {
        if (_ascending)
            return first < second; // ascending order
        else
            return first > second; // descending order
    };
    auto ptr_func_2 = std::bind(lambdas_1, std::placeholders::_1, std::placeholders::_2, Ascending);

    ///// --------------------------- Initualize an function object via functor ---------------------------
    // The FUNCTOR is also known as the function object. As we used to clear that it will create an temporary object in runtime 
    // and the function pointer which handles the functor will be called later, especially to the operator () overloading of the Compare class .
    auto lambdas_2 = Compare();
    auto ptr_func_3 = std::bind(lambdas_2, std::placeholders::_1, std::placeholders::_2, Ascending);

    std::sort(data_list.begin(), data_list.end(), ptr_func_3); // we pass ascen function object to sort function
    std::for_each(data_list.begin(), data_list.end(), visualizer); // we passed visualizer function object
    std::cout << std::endl;

    std::cout << "Sorted descending:" << std::endl;
    Ascending = false;
    Compare desc;
    auto ptr_func_4 = std::bind(desc, std::placeholders::_1, std::placeholders::_2, Ascending);
    std::sort(data_list.begin(), data_list.end(), ptr_func_4); // we pass desc function object to sort function
    std::for_each(data_list.begin(), data_list.end(), visualizer); // we passed visualizer function object
    std::cout << std::endl;

    return 0;
}
