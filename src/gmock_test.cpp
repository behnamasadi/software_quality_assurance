#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <memory>

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
        //if(databaseConnectObject->login())
    }
};


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


// Tests that the Foo::Bar() method does Abc.

TEST(MyTestSuite, MyTest) {
  std::vector<int> test1;
  std::vector<int> test2;

  EXPECT_THAT(test1, ::testing::ContainerEq(test2));

  int x;
  //    EXPECT_THAT(test1, ContainerEq(test2));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
