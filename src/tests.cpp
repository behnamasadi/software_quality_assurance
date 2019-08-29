#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring> //for memcopy

/*
Ref: 
https://github.com/google/googletest/blob/master/googletest/docs/primer.md
https://chromium.googlesource.com/external/github.com/google/googletest/+/HEAD/googlemock/docs/cook_book.md#MockingNonVirtualMethods
https://chromium.googlesource.com/external/github.com/google/googletest/+/HEAD/googlemock/docs/for_dummies.md
Assertion:
1)Succuss
2)Non Fatal Failure ==> EXPECT
3)Fatal Failure ==> ASSERT
*/

//TEST(TestSuiteName, TestName) {  ... test body ...}

TEST(testCaseName1, teseName1)
{
    ASSERT_TRUE(1==1);
}

TEST(testCaseName1, teseName2)
{
    ASSERT_FALSE(1==2);
}

TEST(testCaseName2, teseName1)
{
    EXPECT_EQ(1,1);//Non Fatal Failure
    ASSERT_EQ(1,1);//Fatal Failure
    
    
    std::string str="a";
    EXPECT_STREQ("a",str.c_str());
    

    int arr1[3];
    int arr2[3];
    
    arr1[0]=3;
    arr1[1]=4;
    arr1[2]=1;
    
    arr2[0]=3;
    arr2[1]=4;
    arr2[2]=1;
    
    EXPECT_TRUE( 0 == std::memcmp( arr1, arr2, sizeof( arr1 ) ) );
    EXPECT_NEAR(12.900001, 3*4.3, 1e-5);
}

/////////////////////////////////////////////////Arrange, Act, Assert ///////////////////////////////////////

TEST(testCaseName2, teseName2)
{


//Arrange
    int value=10;
    int increment=1;

//Act
    value=value+increment;


//Assert
    ASSERT_EQ(value,11);

}

////////////////////////////////////////////////////  Test Fixtures  //////////////////////////////////////////////////// 
/*
Test Fixtures: Using the Same Data Configuration for Multiple Tests. Suppose you have the following
class and you need to configre it and test its method
*/
class Foo 
{
public:
    std::string concatStrings(std::string s1, std::string s2)
    { 
        return s1+s2;
    }

    bool hasString(std::string s1, std::string s2)
    {
        if(s1.find(s2) != std::string::npos)
            return true;
        else
            return false;
    }
};

// The fixture for testing class Foo.
class FooTest : public ::testing::Test {
protected:
  // You can remove any or all of the following functions if its body
  // is empty.
    Foo * myfoo_ptr;
    FooTest() 
    {
    // You can do set-up work for each test here.
        myfoo_ptr=new Foo;
    }

    ~FooTest() override 
    {
    // You can do clean-up work that doesn't throw exceptions here.
        delete myfoo_ptr;
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override 
    {
    // Code here will be called immediately after the constructor (right
    // before each test).
        //std::cout<<"===================Starting Next Test====================" <<std::endl;

    }

    void TearDown() override 
    {
    // Code here will be called immediately after each test (right
    // before the destructor).
        //std::cout<<"===================Test Finished====================" <<std::endl;
    }

    // Objects declared here can be used by all tests in the test case for Foo.
};

TEST_F(FooTest,concatStrings)
{
    const std::string input_filepath = "this/package/testdata";
    const std::string output_filepath = "this/package/testdata";

    EXPECT_EQ(myfoo_ptr->concatStrings(input_filepath, output_filepath), input_filepath+output_filepath);
}

TEST_F(FooTest,hasString)
{
    EXPECT_TRUE(myfoo_ptr->hasString("bamboo","boo"));
}


////////////////////////////////////////////////////  Google Mock  ////////////////////////////////////////////////////
/*
ref:https://github.com/google/googletest/blob/master/googlemock/docs/for_dummies.md

Google Mock is not a testing framework itself. Instead, it needs a testing framework for writing tests.
Google Mock works seamlessly with Google Test. It comes with a copy of Google Test bundled. you can also
 use it with any C++ testing framework of your choice.

A mock should inherit from an abstract class, generally, that defines a virtual destructor explicitly
and defines a pure virtual function for any method that will be needed by the mock objects.
This is not a strict requirement, but it avoids some complications.

The destructor of interface class must be virtual, as is the case for all classes you intend to inherit from
 - otherwise the destructor of the derived class will not be called when you delete an object through a
base pointer, and you'll get corrupted program states like memory leaks.

Let's say we have the following interface:
*/

class Turtle
{
public:
    virtual ~Turtle() {}
    virtual void PenUp() = 0;
    virtual void PenDown() = 0;
    virtual void Forward(int distance) = 0;
    virtual void Turn(int degrees) = 0;
    virtual void GoTo(int x, int y) = 0;
    virtual int GetX() const = 0;
    virtual int GetY() const = 0;
};

class Painter
{
        Turtle * turtle;
public:
        Painter( Turtle * turtle): turtle(turtle){}
        bool DrawCircle(int, int, int)
        {
                turtle->PenDown();
                return true;
        }
};


/*
Using a interface, here is what you shoudl do:
Derive a class Mock<ClassName> from interface, Take a virtual function of the interface, and create the following:

MOCK_METHOD(<return type>, <function name>, ( <type parameter1> , <type parameter2>), (override));
*/

using ::testing::AtLeast;                         // #1


class MockTurtle : public Turtle {
 public:
    MOCK_METHOD(void, PenUp, (), (override));
    MOCK_METHOD(void, PenDown, (), (override));
    MOCK_METHOD(void, Forward, (int distance), (override));
    MOCK_METHOD(void, Turn, (int degrees), (override));
    MOCK_METHOD(void, GoTo, (int x, int y), (override));
    MOCK_METHOD(int, GetX, (), (const, override));
    MOCK_METHOD(int, GetY, (), (const, override));
};



TEST(PainterTest, CanDrawSomething) {
  MockTurtle turtle;
  EXPECT_CALL(turtle, PenDown()).Times(AtLeast(1));


  // If the painter object didn't call this method, your test will fail with a message
  Painter painter(&turtle);
  EXPECT_TRUE(painter.DrawCircle(0, 0, 10));



  /* How to send argument for functions */
  //EXPECT_CALL(turtle, Forward(100));//Expects the turtle to move forward by 100 units.
}


int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
