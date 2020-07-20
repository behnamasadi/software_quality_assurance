#include "coin_flipper.hpp"

CoinFlipper::CoinFlipper(std::shared_ptr<IRandomNumberGenerator> RandomNumberGenerator)
{
    m_RandomNumberGenerator=RandomNumberGenerator;
}
FlipCoinResult CoinFlipper::flip()
{
    double result=m_RandomNumberGenerator->generate(0.0,1.0);
    return (result>0.5)? FlipCoinResult::HEAD:FlipCoinResult::TAIL;
}
