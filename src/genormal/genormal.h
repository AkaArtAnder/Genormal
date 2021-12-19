// Header file descriptor class generator normal destribution

#pragma once

//Standart stream
#include <iostream>
#include <fstream>

//Containers
#include <vector>
#include <cstring>

namespace genormal
{
    /*
        The class is a random number generator to the normal distribution, 
        with variable parameters mean and variance. 
        Modified tabular method generation random values.
    */
    class Genormal
    {
        private:
            std::vector <double> result_values;//result values to the normal distribution
            //tabular values
            std::vector <double> value_x;
            std::vector <double> value_y;
            double mean, variance;//mean and variance to the normal distribution
            size_t size_generation;//size result values        
            std::string path_folder_table_values;//path to files mass_X and mass_Y with tabular values to the normal distribution

            void init_result_vec();
            void init_tabular_values_vec();
            
        public:
            Genormal ();
            Genormal(double&, double&, int&, std::string&);
    };
} // namespace genormal