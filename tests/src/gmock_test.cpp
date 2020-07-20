#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <memory>

#include "../../src/coin_flipper.hpp"
#include "../../src/random_number_generator.hpp"



using ::testing::Return;
using ::testing::AtLeast;
using ::testing::DefaultValue;


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

TEST(CoinFlipper, multipleFlipping)
{
    // 1) Create mock objects (collaborators)
    std::shared_ptr<MockRandomNumberGenerator>rng_ptr(new MockRandomNumberGenerator);

    // 2) Specify your expectations of them
    EXPECT_CALL(*rng_ptr, generate(0.0,1.0))
        .Times(5)
        .WillOnce(Return(0.15))
        .WillOnce(Return(0.35))
        .WillRepeatedly(Return(0.75));

    // 3) Construct object(s) under test, passing mocks
    CoinFlipper coinFlipper(rng_ptr);

    // 4) Run code under test
    FlipCoinResult result0,result1,result2,result3,result4;
    result0= coinFlipper.flip();// this will return 0.15
    result1= coinFlipper.flip();// this will return 0.35
    result2= coinFlipper.flip();// this will return 0.75
    result3= coinFlipper.flip();// this will return 0.75
    result4= coinFlipper.flip();// this will return 0.75

    // 5) Check output (using Google Test or some other framework)
    EXPECT_EQ(FlipCoinResult::TAIL, result0);
    EXPECT_EQ(FlipCoinResult::TAIL, result1);
    EXPECT_EQ(FlipCoinResult::HEAD, result2);
    EXPECT_EQ(FlipCoinResult::HEAD, result3);
    EXPECT_EQ(FlipCoinResult::HEAD, result4);
}



/////////////////////// Mocking Non-virtual Methods //////////////////////////
class RealClass
{
public:
    int generate()
    {
        return 10;
    }
};

class MockRealClass
{
public:
    MOCK_METHOD(int , generate,());
};

template<class T>
class Consumer
{
    std::shared_ptr<T> m_numberGenerator;
public:
    Consumer(std::shared_ptr<T> numberGenerator)
    {
      m_numberGenerator=numberGenerator;
    }
    int multiplier(int n)
    {
        return n* m_numberGenerator->generate();
    }
};


TEST(Consumer, multiplier)
{
    // 1) Create mock objects (collaborators)
    std::shared_ptr<MockRealClass> MockRealClassObject_ptr(new MockRealClass);

    // 2) Specify your expectations of them
    EXPECT_CALL(*MockRealClassObject_ptr, generate())
    .Times(AtLeast(1))
    .WillOnce(Return(5));

    // 3) Construct object(s) under test, passing mocks
    Consumer<MockRealClass> ConsumerObject(MockRealClassObject_ptr);

    // 4) Run code under test
    int n=3;
    int result= ConsumerObject.multiplier(n);

    // 5) Check output (using Google Test or some other framework)
    EXPECT_EQ(15, result);
}

///////////////////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////////////////

class Foo
{
public:
    virtual int somePublicMethod()=0;
protected:
    virtual int someProtectedMethod();
private:
    virtual int somePrivateMethod();
};

class MockFoo: public Foo
{
public:
    MOCK_METHOD(int, somePublicMethod, ( ), (override));
    MOCK_METHOD(int, someProtectedMethod, (), (override));
    MOCK_METHOD(int, somePrivateMethod, (), (override));
};

///////////////////////////////////////////////////////////////////////////////////
template <typename T>
class templatedInterface
{
public:
    virtual T someFunction(T t)=0;
};

template <typename T>
class MockedtemplatedInterface: public templatedInterface<T>
{
public:
    MOCK_METHOD(T, someFunction, (T t), (override));
};

///////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
