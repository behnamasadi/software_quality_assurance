#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <memory>

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::DefaultValue;

class IRandomNumberGenerator
{
    public:
    virtual ~IRandomNumberGenerator(){}
        virtual double generate(double min,double  max)=0;
};

enum class FlipCoinResult{HEAD=0, TAIL=1};

class CoinFlipper
{
    std::shared_ptr<IRandomNumberGenerator> m_RandomNumberGenerator;
public:
    CoinFlipper(std::shared_ptr<IRandomNumberGenerator> RandomNumberGenerator)
    {
        m_RandomNumberGenerator=RandomNumberGenerator;
    }
    FlipCoinResult flip()
    {
        double result=m_RandomNumberGenerator->generate(0.0,1.0);
        return (result>0.5)? FlipCoinResult::HEAD:FlipCoinResult::TAIL;
    }
};

class MockRandomNumberGenerator: public IRandomNumberGenerator
{
public:
    MOCK_METHOD2(generate,double(double,double));
};

TEST(CoinFlipper, flip)
{
    // 1) Create mock objects (collaborators)
    std::shared_ptr<MockRandomNumberGenerator>rng_ptr(new MockRandomNumberGenerator);

    // 2) Specify your expectations of them
    EXPECT_CALL(*rng_ptr, generate(0.0,1.0))
    .Times(AtLeast(1))
    .WillOnce(Return(0.25));

    // 3) Construct object(s) under test, passing mocks
    CoinFlipper coinFlipper(rng_ptr);

    // 4) Run code under test
    FlipCoinResult result= coinFlipper.flip();

    // 5) Check output (using Google Test or some other framework)
    EXPECT_EQ(FlipCoinResult::TAIL, result);
}

class databaseConnect
{
public:
    virtual bool login(std::string userName, std::string password){}
    virtual bool logout(std::string userName){}
    virtual void fetchRecords(){}
    virtual ~databaseConnect();
};

class mockDB :public databaseConnect
{

};

class databaseLayer
{
public:
    databaseLayer(std::shared_ptr<databaseConnect> databaseConnectObject)
    {
    }
};

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
