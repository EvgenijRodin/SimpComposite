#include "Simp.h"


int main()
{
    const int dim = 7;
    const std::initializer_list<int> li = { 1,2,3 };
    auto S1 = Simplex();
    auto S2 = Simplex(dim, li);
    
    if (S1.isEmpty())
    {
        std::cout << "Ups\n";
    }
    
    std::cout << S1;
    std::cout << S2;
    
}
