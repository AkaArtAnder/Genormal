//------------------------------------------------------------------
//Discription of class Genormal methods
//------------------------------------------------------------------

#include "genormal.h"

namespace genormal
{
    Genormal::Genormal() {}

    Genormal::Genormal(double& _mx_value, double& _dx_value, int& _size, std::string& _path_folder)    
    {
        mean = _mx_value;
        variance = _dx_value;
        size_generation = _size;
        path_folder_table_values = _path_folder;

        init_result_vec();
        init_tabular_values_vec();
    }

    void Genormal::init_tabular_values_vec()
    {
        std::string path_file_x = path_folder_table_values + "/mass_X.txt";
        std::string path_file_y = path_folder_table_values + "/mass_Y.txt";

        std::ifstream file_x(path_file_x);
        std::ifstream file_y(path_file_y);

        if(file_x.is_open() && file_y.is_open())
        {
            size_t _size = 99999;
            value_x.resize(_size);
            value_y.resize(_size);

            for (size_t i = 0; i < _size; ++i)
            {
                file_x >> value_x[i];
                file_y >> value_y[i]; 
            }
        }
        else std::cout << "Files is not open!" << '\n';
    }

    void Genormal::init_result_vec()
    {
        result_values.resize(size_generation); 
    }
} // namespace genormal
