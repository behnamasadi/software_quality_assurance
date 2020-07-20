#include "../src/coin_flipper.hpp"
#include "../src/uniform_random_number_generator.hpp"
#include <map>
#include <iostream>

int main(int argc, char **argv)
{
    std::map<int,std::string> result_mapping;
    std::pair< int,std::string > single_item;
    single_item.first =0;
    single_item.second="tail";

    result_mapping.insert(single_item);

    single_item.first=1;
    single_item.second="head";
    result_mapping.insert(single_item);

    std::shared_ptr<UniFormRandomNumberGenerator> rnd(new UniFormRandomNumberGenerator);
    CoinFlipper coin(rnd);
    FlipCoinResult result;
    for(int i=0;i<10;i++)
    {
        result= coin.flip();
        std::cout<<result_mapping[(int) result]<<std::endl;
    }

}
