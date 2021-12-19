#include <iostream>

#include <exception>

#include "../../src/genormal/genormal.cpp"

class TestGenormal
{
    private:
        genormal::Genormal* test_obj;
    public:
        TestGenormal()
        {
            double _mx = 0;
            double _dx = 1;
            int _size = 101;
            std::string path_folder = "../../src/genormal/source";

            test_obj = new genormal::Genormal(_mx, _dx, _size, path_folder);
            std::cout << "Object was create!" << '\n';

            std::vector<double> res = test_obj -> run();
            for (size_t i = 0; i < res.size(); ++i)
            {
                std::cout << i << " :  " << res[i] << '\n';
            }
        }

        ~TestGenormal()
        {
            delete test_obj;
        }
};

int main()
{
    TestGenormal test;
    return 0;
}