#include <memory>
#include "random_number_generator.hpp" 

#ifndef COINFLIPPER_H
#define COINFLIPPER_H

enum class FlipCoinResult{HEAD=0, TAIL=1};

class CoinFlipper
{
    std::shared_ptr<IRandomNumberGenerator> m_RandomNumberGenerator;
public:
    CoinFlipper(std::shared_ptr<IRandomNumberGenerator> RandomNumberGenerator);
   
    FlipCoinResult flip();
};
#endif
