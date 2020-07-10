#include <gtest/gtest.h>

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

class FooTest : public ::testing::Test {
protected:
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

    void SetUp() override
    {
        std::cout<<"===================Starting Next Test====================" <<std::endl;

    }

    void TearDown() override
    {
        std::cout<<"===================Test Finished====================" <<std::endl;
    }

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

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
