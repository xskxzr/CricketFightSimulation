#include <iostream>
#include "cricket.h"

using namespace cricketNs;
        
int main()
{
    Cricket tanheibaxian{"tanhei", "baxian"}, xiuhuazhen{"xiuhuazhen"};
    std::cout << winRate(tanheibaxian, xiuhuazhen);    
}
