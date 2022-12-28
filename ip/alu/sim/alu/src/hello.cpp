#include "hello.hpp"

#include <iostream>

namespace Hello {
    
    void greet(int iter)
    {
        for(int i = 0; i < iter; ++i) {
            std::cout << "Hello world\n";
        }
    }

}
