#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <memory>

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::DefaultValue;
using ::testing::_;



namespace Fake
{
class Foo
{
public:
    virtual ~Foo() {}
    virtual char DoThis(int n) = 0;
    virtual void DoThat(const char* s, int* p) = 0;
};

class FakeFoo : public Foo
{
public:
    char DoThis(int n) override
    {
        std::cout<<"DoThis from FakeFoo " <<std::endl;
        return (n > 0) ? '+' : (n < 0) ? '-' : '0';
    }

    void DoThat(const char* s, int* p) override
    {
        std::cout<<"DoThat from FakeFoo " <<std::endl;
        *p = strlen(s);
    }
};

class MockFoo : public Foo {
public:
// Normal mock method definitions using gMock.
/*
(Old) MOCK_METHOD1(Bar, double(std::string s));
(New) MOCK_METHOD(double, Bar, (std::string s), (override));
*/

    //MOCK_METHOD1(DoThis,char(int));
    MOCK_METHOD(char, DoThis, (int), (override));
    MOCK_METHOD(void, DoThat, (const char* s, int* p), (override));

// Delegates the default actions of the methods to a FakeFoo object.
// This must be called *before* the custom ON_CALL() statements.
void DelegateToFake()
{
    ON_CALL(*this, DoThis).WillByDefault([this](int n) {  return fake_.DoThis(n); });
    ON_CALL(*this, DoThat).WillByDefault([this](const char* s, int* p) {fake_.DoThat(s, p); });
}

private:
    FakeFoo fake_;  // Keeps an instance of the fake in the mock.
};

}

TEST(TestFoo, DelegatingToFake)
{
    Fake::MockFoo foo;

    foo.DelegateToFake();  // Enables the fake for delegation.

    // Put your ON_CALL(foo, ...)s here, if any.

    // No action specified, meaning to use the default action.
    EXPECT_CALL(foo, DoThis(5));
    EXPECT_CALL(foo, DoThat(_, _));

    int n = 0;
    EXPECT_EQ('+', foo.DoThis(5));  // FakeFoo::DoThis() is invoked.
    foo.DoThat("Hi", &n);  // FakeFoo::DoThat() is invoked.
    EXPECT_EQ(2, n);
}


namespace Real
{
class Foo
{
public:
    virtual ~Foo() {}
    char DoThis(int n)
    {
        std::cout<<"DoThis from RealFoo " <<std::endl;
        return (n > 0) ? '+' : (n < 0) ? '-' : '0';
    }
    void DoThat(const char* s, int* p)
    {
        std::cout<<"DoThat from RealFoo " <<std::endl;
        *p = strlen(s);
    }
};

class MockFoo : public Foo
{
public:
    MockFoo()
    {
        // By default, all calls are delegated to the real object.
        ON_CALL(*this, DoThis).WillByDefault([this](int n) {return real_.DoThis(n); });
        ON_CALL(*this, DoThat).WillByDefault([this](const char* s, int* p) {real_.DoThat(s, p);});
    }
    MOCK_METHOD(char, DoThis, (int) );
    MOCK_METHOD(void, DoThat, (const char* s, int* p));


private:
    Foo real_;
};

}

TEST(TestFoo, DelegatingToReal)
{
    int n = 0;
    Real::MockFoo mock;
    EXPECT_CALL(mock, DoThis(5)).Times(1);
    EXPECT_CALL(mock, DoThat("Hi",&n)).Times(AtLeast(1));

    EXPECT_EQ('+', mock.DoThis(5));  // ::DoThis() is invoked.
    mock.DoThat("Hi", &n);  // ::DoThat() is invoked.
    EXPECT_EQ(2, n);
}

/*
namespace Parent
{
class Foo
{
public:
    virtual ~Foo();
    virtual void Pure(int n) = 0;
    virtual int Concrete(const char* str) {std::cout<<"Concrete from Foo" <<std::endl; }
};
using ::testing::Invoke;

class MockFoo: public Foo
{

public:

    MOCK_METHOD1(Pure, void(int n));
    MOCK_METHOD1(Concrete, int(const char* str));
    MockFoo()
    {
        ON_CALL(*this, Concrete).WillByDefault(Invoke([this](const char* str) {return Foo::Concrete(str);}));
    }
    ~MockFoo() = default;
};
}

TEST(TestFoo, DelegatingToParent)
{
    //Parent::MockFoo foo;
    //        ON_CALL(foo, Concrete).WillByDefault([&foo](const char* str) { return foo.FooConcrete(str); });

    //EXPECT_CALL(foo, Concrete).WillOnce([&foo](const char* str) {return foo.FooConcrete(str); });
    Parent::MockFoo mock;
    //EXPECT_CALL(mock, bar()).WillOnce([&mock](){ return mock.Foo::bar(); });
    //EXPECT_EQ(mock.bar(), 42);
}
*/
namespace Parent
{
class Foo
{
public:
    virtual int DoThat()
    {
        std::cout<<"DoThat from Parent " <<std::endl;
        return 2;
    }
};

class MockFoo : public Foo
{
public:
    MOCK_METHOD0(DoThat, int());
};

TEST(TestFoo, DelegatingToParent)
{
    Parent::MockFoo mock;
    EXPECT_CALL(mock, DoThat()).WillOnce([&mock](){
        return mock.Foo::DoThat(); // trick is here
    });

    EXPECT_EQ(mock.DoThat(), 2);
}
}

int main(int argc , char ** argv)
{
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
}
