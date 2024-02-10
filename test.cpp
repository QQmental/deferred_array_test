#include <initializer_list>
#include <iostream>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <chrono>
#include "deferred_array.hpp"


struct ST
{
    bool operator == (const ST &src) {return this->x == src.x && this->y == src.y;}
    int x, y;
};

int main()
{
    std::size_t a = 300, b = 500, c = 600;
    std::cin >> a >> b >> c;
    
    // size of the two dimension is set at run time
    Deferred_array<ST, 3> arr({a, b, c});
    

    for(std::size_t i = 0 ; i < arr.data_len() ; i++)
    {
        arr.data()[i].x = i + 10;
        arr.data()[i].y = i + 3;
    }

    
    Deferred_array<ST, 3> arr2;

    arr2 = arr; // copy all element
    
    #define indexies [2][2][5]
    
    auto &x = arr indexies;
    auto &y = arr2 indexies;
    auto p = reinterpret_cast<ST(*)[500][600]>(arr2.data());
   
    std::cout << x.x  << " " << x.y << "\n";
    std::cout << y.x  << " " << y.y << "\n";
    std::cout << p indexies.x  << " " << p indexies.y << "\n";
    std::cout << "dimension length of array is " << arr.dimension_length << "\n";

    auto start = std::chrono::steady_clock::now();

    for(std::size_t i = 0 ; i < a ; i++)
    {
        for(std::size_t j = 0 ; j < b ; j++)
        {
            for(std::size_t k = 0 ; k < c ; k++)
            {
                auto item1 = arr[i][j][k];
                auto item2 = arr2[i][j][k];
                assert(item1 == item2); 
            }
        }
    }
    auto elapsed = std::chrono::steady_clock::now() - start;
                                                        
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << "miliseconds\n";
}