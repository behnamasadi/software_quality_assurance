#ifndef RANDOMNUMBERGENERATOT_H
#define RANDOMNUMBERGENERATOT_H
class IRandomNumberGenerator
{
    public:
    virtual ~IRandomNumberGenerator(){}
        virtual double generate(double min,double  max)=0;
};

#endif
