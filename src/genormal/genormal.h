//-----------------------------------------------------------
// Header file descriptor class generator normal destribution
//-----------------------------------------------------------

#pragma once

//Standart stream
#include <iostream>
#include <fstream>

//Containers
#include <vector>
#include <cstring>

#include <cmath>//sqrt, log
#include <random>   //uniform_real_distribution, 
                    //default_random_engine,
                    //random_device

//Parallels module
#include <thread>
#include <mutex>

//Exception handler
#include <cassert>//assert

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
            std::vector <std::thread> threads;//Vector for thread objects

            std::mutex gen_mutex;//Mutex for access shared data: result_values
            double mean, variance;//mean and variance to the normal distribution
            size_t size_generation;//size result values        
            std::string path_folder_table_values;//path to files mass_X and mass_Y with tabular values to the normal distribution
            unsigned int num_threads;//Var for number active threads in program

            void init_result_vec();
            void init_tabular_values_vec();
            
            void normal_algorithm(unsigned int);//A function that implements an algorithm for generating normally distributed numbers

            void calc_threads();//Function for calculating the number of threads when using in program
            void init_vector_threads();//Function initialize vector for threads object

        public:
            Genormal ();
            Genormal(double&, double&, int&, std::string&);
            std::vector<double> run();//run algorithm generation number
    };
} // namespace genormal