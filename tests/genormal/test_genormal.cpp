#include <iostream>

#include <exception>

#include "../../src/genormal/genormal.cpp"

class TestGenormal
{
    private:
        genormal::Genormal test_obj;

    public:
        TestGenormal()
        {
            double _mx = 0;
            double _dx = 1;
            int _size = 10;
            std::string folder = "../../src/genormal/source";

            test_obj = std::move(genormal::Genormal(_mx, _dx, _size, folder));
            std::cout << "Object was been created!";
        }
};

int main()
{
    TestGenormal test;
    return 0;
}