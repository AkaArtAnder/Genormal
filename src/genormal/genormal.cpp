//------------------------------------------------------------------
//Discription of class Genormal methods
//------------------------------------------------------------------

#include "genormal.h"

namespace genormal
{
    Genormal::Genormal() {}

    Genormal::Genormal(double& _mx_value, double& _dx_value, int& _size, std::string& _path_folder)    
    {
        assert(_size >= 2); 

        mean = _mx_value;
        variance = _dx_value;
        size_generation = _size;
        path_folder_table_values = _path_folder;

        init_result_vec();
        init_tabular_values_vec();
        calc_threads();
        init_vector_threads();
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

            file_x.close();
            file_y.close();
        }
        else std::cout << "Files is not open!" << '\n';
    }

    void Genormal::init_result_vec()
    {
        result_values.resize(size_generation); 
    }

    void Genormal::calc_threads()
    {
        if (size_generation >= 100)
        {
            unsigned int _hard_threads = std::thread::hardware_concurrency();
            unsigned int _min_num_threads = 2;

            if (_hard_threads < _min_num_threads)
            {
                num_threads = _min_num_threads;
            }
            else num_threads = _hard_threads;
        }
        else num_threads = 1;

        std::cout << "Num threads:  " << num_threads << '\n';
    }

    void Genormal::init_vector_threads()
    {
        threads.resize(num_threads);
    }

    void Genormal::normal_algorithm(unsigned int size_part)
    {
        int _count;
        double _uniform_value_first, _uniform_value_second, _uniform_hybrid;
        std::vector<double> part_array_normal_distribution(size_part);

        //Using uniform distribution generators for the algorithm
        std::random_device sd{};
        std::default_random_engine generator{ sd() };
        std::uniform_real_distribution<> u1(-1,1);
        std::uniform_real_distribution<> u2(-1,1);

        for (int count = 0; count < size_part; ++count)
        {
            while (true)
            {
                _uniform_value_first = u1(generator);
                _uniform_value_second = u2(generator);
                _uniform_hybrid = _uniform_value_first * _uniform_value_first  + 
                                    _uniform_value_second * _uniform_value_second;

                if ((_uniform_hybrid > 0) && (_uniform_hybrid <= 1)) break;
            }


            if ((_uniform_hybrid >= 0.00001) && (_uniform_hybrid < 0.99999))
            {
                _count = (_uniform_hybrid / 0.00001) - 1;
                part_array_normal_distribution[count] =  (value_x[_count] + ((_uniform_hybrid - value_y[_count]) / 
                                                            (value_y[_count + 1] - value_y[_count]))*
                                                                (value_x[_count + 1] - value_x[_count])) * variance + mean;
            }		
            else 
            {
                part_array_normal_distribution[count] = (sqrt(-2 * log(_uniform_hybrid) / _uniform_hybrid) *
                                                            _uniform_value_first) *  variance + mean;
                if (count != (size_generation/4) - 1)
                {
                    count++;
                    part_array_normal_distribution[count] =  (sqrt(-2 * log(_uniform_hybrid) / _uniform_hybrid) * 
                                                                _uniform_value_second) *  variance + mean;

                }
            }        
        }

        gen_mutex.lock();
        static int index_value = 0;
        for(int count = 0; count < size_part; ++count)
           {
               result_values[index_value] = part_array_normal_distribution[count];
               ++index_value;
           } 
        gen_mutex.unlock();           
    }

    std::vector<double> Genormal::run()
    {
        unsigned int _size_part = size_generation/num_threads;
        
        for (size_t count = 0; count < num_threads; ++count)
        {
            if (count == num_threads - 1)
            {
                unsigned int _size_end_part = _size_part + size_generation % num_threads;
                threads[count] = std::thread(&genormal::Genormal::normal_algorithm, this, _size_end_part);
            }
            else threads[count] = std::thread(&genormal::Genormal::normal_algorithm, this, _size_part);
        }

        for (size_t count = 0; count < num_threads; ++count)
        {
            threads[count].join();
        }

        return result_values;
    }
} // namespace genormal
