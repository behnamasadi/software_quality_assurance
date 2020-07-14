#include <gtest/gtest.h>

template <typename T>
T add(T x, T y)
{
    return x+y;
}


TEST(testsuitname, testcasename)
{
    EXPECT_EQ(2,1+1);
}

//template <typename T>
class student
{
public:
//    T add(T x, T y)
//    {
//        return x+y;
//    }
    int add(int x, int y)
    {
        return x+y;
    }

};

//template <typename T>
class studentTesting :public ::testing::Test
{
protected:
    //student<T>* std;
    student* std;
    void SetUp() override
    {

    }

    void TearDown() override
    {

    }

    studentTesting(){std =new student;}
    ~studentTesting(){delete std;}
};

//template <typename T>
TEST_F(studentTesting, add)
{
    EXPECT_EQ(2,std->add(1,1));
}


int main(int argc , char ** argv)
{
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
}
