#include <gtest/gtest.h>
#include <cstring> //for memcopy
#include <math.h>

double squareRoot(const double a) {
    double b = sqrt(a);
    if(b != b) { // nan check
        return -1.0;
    }else{
        return sqrt(a);
    }
}

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

////////////////////////////Arrange, Act, Assert ////////////////////////

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




TEST(SquareRootTest, PositiveNos) {
  ASSERT_EQ(6, squareRoot(36.0));
  ASSERT_EQ(18.0, squareRoot(324.0));
  ASSERT_EQ(25.4, squareRoot(645.16));
  ASSERT_EQ(0, squareRoot(0.0));

}

TEST(SquareRootTest, NegativeNos) {
  ASSERT_EQ(-1.0, squareRoot(-15.0));
  ASSERT_EQ(-1.0, squareRoot(-0.2));
}

TEST(SquareRootTest, NegativeNos1) {
  ASSERT_EQ(-1.0, squareRoot(-15.0));
  ASSERT_EQ(-1.0, squareRoot(-0.2));
  // EXPECT_EQ
  // EXPECT_NEAR
  //    int arr1[10];
  //    int arr2[10];

  //    // initialize arr1 and arr2

  //    EXPECT_TRUE( 0 == std::memcmp( arr1, arr2, sizeof( arr1 ) ) );

  // ASSERT_STREQ(intended, printer.CStr());

  // ASSERT_EQ() compares pointers. (which are only equal if they point to the
  // same memory location).
  int x;
}


struct Mystruct
{
    int x,y;
};

TEST(testcase10,testname10)
{
    Mystruct myobj1,myobj2;
    myobj1.x=1;
    myobj1.y=2;

    myobj2.x=2;
    myobj2.y=1;
    //ASSERT_EQ(myobj1,myobj2);
    //ASSERT_TRUE(myobj1,myobj2);
}

int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
