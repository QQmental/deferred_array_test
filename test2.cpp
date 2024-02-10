#include <initializer_list>
#include <iostream>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <chrono>
#include <vector>
#include "deferred_array.hpp"

struct ST
{
    bool operator == (const ST &src) {return this->x == src.x && this->y == src.y;}
    int x, y;
};

int main()
{
    std::vector<std::vector<std::vector<ST>>> vec;
    std::size_t a = 300, b = 500, c = 600;
    std::cin >> a >> b >> c;
    vec = std::vector<std::vector<std::vector<ST>>>(a);
    
    std::size_t cnt = 0 ;
    for(auto &vec2 : vec)
    {
        vec2 = std::vector<std::vector<ST>>(b);
        for(auto &vec1 : vec2)
        {
            vec1 = std::vector<ST>(c);
            for(auto &st : vec1)
            {
                st.x = cnt + 10;
                st.y = cnt + 3;
                cnt++;
            }
        }
    }

    auto vec_cpoy = vec;

    auto start = std::chrono::steady_clock::now();

    for(std::size_t i = 0 ; i < a ; i++)
    {
        for(std::size_t j = 0 ; j < b ; j++)
        {
            for(std::size_t k = 0 ; k < c ; k++)
            {
                auto item1 = vec[i][j][k];
                auto item2 = vec_cpoy[i][j][k];
                assert(item1 == item2); 
                //cnt += item1.x + item1.y ;
            }
        }
    }

    auto elapsed = std::chrono::steady_clock::now() - start;
                                                        
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << "miliseconds\n";
}