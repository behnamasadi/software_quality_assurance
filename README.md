- [Project Structure](#project-structure)
- [Installation](#installation)
- [Google Test](#google-test)
  * [Assertions](#assertions)
    + [Binary Comparison](#binary-comparison)
    + [User Defined Type](#user-defined-type)
    + [String Comparison](#string-comparison)
  * [Simple Tests](#simple-tests)
  * [Test Fixtures](#test-fixtures)
      - [SetUp()](#setup--)
      - [TearDown()](#teardown--)
      - [static  SetUpTestSuite()/ TearDownTestSuite()](#static--setuptestsuite----teardowntestsuite--)
  * [Global Set-Up and Tear-Down](#global-set-up-and-tear-down)
  * [Running Tests and Patterns](#running-tests-and-patterns)
  * [Google Test XML report](#google-test-xml-report)
- [Google Mock](#google-mock)
  * [Writing the Mock Class](#writing-the-mock-class)
  * [Writting the Test](#writting-the-test)
  * [Mocking Non-virtual Methods](#mocking-non-virtual-methods)
  * [Delegating Calls](#delegating-calls)
    + [Delegating Calls to Fake Class](#delegating-calls-to-fake-class)
    + [Delegating Calls to Real Class](#delegating-calls-to-real-class)
    + [Delegating Calls to Parent Class](#delegating-calls-to-parent-class)
  * [Matchers](#matchers)
  * [Common Matchers](#common-matchers)
    + [Defining Matchers](#defining-matchers)
  * [Actions](#actions)
  * [Common Actions](#common-actions)
    + [Defining Actions](#defining-actions)
  * [Where to Place Mocked Interfaces Code](#where-to-place-mocked-interfaces-code)
  * [Mocking Private or Protected Methods](#mocking-private-or-protected-methods)
  * [Mocking Class Templates](#mocking-class-templates)
- [Testing Multi-Threaded Code](#testing-multi-threaded-code)
- [Test-Driven Development (TDD)](#test-driven-development--tdd-)
- [Code Coverage with GCC](#code-coverage-with-gcc)
- [Code Coverage with Clang-tidy](#code-coverage-with-clang-tidy)
- [Cppcheck](#cppcheck)
  * [Integrating Cppcheck into CMake](#integrating-cppcheck-into-cmake)
    + [Suppression](#suppression)
    + [exitcode](#exitcode)
    + [XML output](#xml-output)
    + [Excluding files](#excluding-files)
- [Valgrind call-graph](#valgrind-call-graph)

This repository is about quality assurance of c++ code.It contains testing in diffrent levels `Unit testing`, `Integration testing`, `Regression testing` and `Acceptance tests` and cppcheck and code coverage.
snippet code of how to use Google Test and Google Mocking (Gtest, GMock) and Test Driven Development


Software testing includes many different forms of tests:

1) unit tests
2) integration tests
3) regression tests
4) acceptance tests
5) performance tests

Unit testing - You unit test each individual piece of code. Think each file or class.

Integration testing - When putting several units together that interact you need to conduct Integration testing to make sure that integrating these units together has not introduced any errors.

Regression testing - after integrating (and maybe fixing) you should run your unit tests again. This is regression testing to ensure that further changes have not broken any units that were already tested. The unit testing you already did has produced the unit tests that can be run again and again for regression testing.

Acceptance tests - when a user/customer/business receive the functionality they (or your test department) will conduct Acceptance tests to ensure that the functionality meets their requirements.



# Project Structure

```
project  
├──.gitignore  
├──README.md  
├──LICENCE.md  
├──CMakeLists.txt  
├──cmake  
│    └──Modules
│         └──FindGMock.cmake  
│
├──include  
│    └──poject  
│        └──lib.hpp  
├──src  
│    ├──coin_flipper.cpp  
│    ├──coin_flipper.hpp  
│    ├──random_number_generator.hpp  
│    └──uniform_random_number_generator.hpp
│
├──apps  
│    ├──CMakeLists.txt  
│    └──flip_coin.cpp  
├──tests  
│    ├──CMakeLists.txt  
│    ├──project_test.cmake
│    └──src
│	 ├──assert_expect_tests.cpp
│	 ├──gmock_test.cpp
│	 ├──main.cpp
│	 ├──test_driven_development.cpp
│	 └──test_fixtures.cpp  
├──docs  
│    └── CMakeLists.txt  
├──extern  
|    └──googletest  
└──scripts  
     └──helper.py  
```

# Installation
First install the required and optional packages for this repository (building, GTest, GMock, cppcheck, code coverage):

```
sudo apt  install build-essential cmake cmake-qt-gui cppcheck-gui cppcheck  valgrind kcachegrind gcovr ggcov lcov 
```

Then download and install Google Test:
```
git clone https://github.com/google/googletest

mkdir googletest/build && cd googletest/build/

cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX:PATH=~/usr .. && make -j8 all install
```


# Google Test

When using googletest, you start by writing assertions (assertions are macros that resemble function calls). Tests use assertions to verify the tested code's behavior. 
If a test crashes or has a failed assertion, then it fails; otherwise it succeeds.
An assertion's result can be:

1) Succuss
2) Non Fatal Failure
3) Fatal Failure

If a fatal failure occurs, it aborts the current function; otherwise the program continues normally.

A **test suite** contains one or many tests. You should group your tests into test suites that reflect the structure of the tested code. 
When multiple tests in a test suite need to share common objects and subroutines, you can put them into a **test fixture** class.

A test program can contain multiple test suites.

## Assertions
You test a class or function by making assertions about its behavior. There are two sort of assertions:
1) `ASSERT_*`  generate fatal failures when they fail, and abort the current function. 
2) `EXPECT_*`  generate nonfatal failures, which don't abort the current function. 
Usually `EXPECT_*` are preferred, as they allow more than one failure to be reported in a test. However, you should use `ASSERT_*`
 if it doesn't make sense to continue when the assertion in question fails.

To provide a custom failure message, simply stream it into the macro using the << operator

```cpp
ASSERT_EQ(x, y) << "Your custom message.";
```
### Binary Comparison

These assertions do basic true/false condition testing.

Fatal assertion            | Nonfatal assertion         | Verifies
-------------------------- | -------------------------- | --------------------
`ASSERT_TRUE(condition);`  | `EXPECT_TRUE(condition);`  | `condition` is true
`ASSERT_FALSE(condition);` | `EXPECT_FALSE(condition);` | `condition` is false

Two compare two values:

Fatal assertion          | Nonfatal assertion       | Verifies
------------------------ | ------------------------ | --------------
`ASSERT_EQ(val1, val2);` | `EXPECT_EQ(val1, val2);` | `val1 == val2`
`ASSERT_NE(val1, val2);` | `EXPECT_NE(val1, val2);` | `val1 != val2`
`ASSERT_LT(val1, val2);` | `EXPECT_LT(val1, val2);` | `val1 < val2`
`ASSERT_LE(val1, val2);` | `EXPECT_LE(val1, val2);` | `val1 <= val2`
`ASSERT_GT(val1, val2);` | `EXPECT_GT(val1, val2);` | `val1 > val2`
`ASSERT_GE(val1, val2);` | `EXPECT_GE(val1, val2);` | `val1 >= val2`

### User Defined Type
These assertions can work with a user-defined type, but only if you define the corresponding comparison operator (e.g., == or <).
```cpp
Mystruct myobj1,myobj2;
ASSERT_EQ(myobj1,myobj2); // you need to define the corresponding comparison operator (e.g., == or <)
```
Since this is discouraged by the Google C++ Style Guide, you may need to use `ASSERT_TRUE()` or `EXPECT_TRUE()` to assert the equality of two objects of a user-defined type.
```cpp
Mystruct myobj1,myobj2;
ASSERT_TRUE(myobj1== myobj2); 
```
However, when possible, `ASSERT_EQ(actual, expected)` is preferred to
`ASSERT_TRUE(actual == expected)`, since it tells you `actual` and `expected`'s
values on failure.

### String Comparison
The assertions in this group compare two **C strings**. If you want to compare
two `string` objects, use `EXPECT_EQ`, `EXPECT_NE`, and etc instead.

<!-- mdformat off(github rendering does not support multiline tables) -->

| Fatal assertion                | Nonfatal assertion             | Verifies                                                 |
| --------------------------     | ------------------------------ | -------------------------------------------------------- |
| `ASSERT_STREQ(str1,str2);`     | `EXPECT_STREQ(str1,str2);`     | the two C strings have the same content   		     |
| `ASSERT_STRNE(str1,str2);`     | `EXPECT_STRNE(str1,str2);`     | the two C strings have different contents 		     |
| `ASSERT_STRCASEEQ(str1,str2);` | `EXPECT_STRCASEEQ(str1,str2);` | the two C strings have the same content, ignoring case   |
| `ASSERT_STRCASENE(str1,str2);` | `EXPECT_STRCASENE(str1,str2);` | the two C strings have different contents, ignoring case |

<!-- mdformat on-->

## Simple Tests
googletest groups the test results by test suites, so logically related tests should be in the same test suite; in other words, the first argument to their `TEST()` should be the same. 

```cpp
TEST(TestSuiteName, TestName1) {
  
}

TEST(TestSuiteName, TestName2) {
  
}
```

and your main function:

```cpp
int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```
 

## Test Fixtures
**Test Fixtures** allows you to reuse the same configuration of objects for several different tests. To create a test fixtures just derive a class from `::testing::Test`.

If the constructor and destructor are not enough for setting up and cleaning up each test, you can define the 
following methods: `SetUp()`, `TearDown()`.
#### SetUp()
Code here will be called immediately after the constructor (right before each test).

#### TearDown()
Code here will be called immediately after each test (right before the destructor).



```cpp
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
```

When using a fixture, use TEST_F() instead of TEST() as it allows you to access objects and subroutines in the test fixture:
```cpp
TEST_F(FooTest,hasString)
{
    EXPECT_TRUE(myfoo_ptr->hasString("bamboo","boo"));
}
```

#### static  SetUpTestSuite()/ TearDownTestSuite()
Gtest creates a new test fixture object for each test in order to make tests independent. Constructor/destructor and setup/teardown functions will execute after each test rather than after the entire set of tests in the fixture. To sharing resources between tests in the same test suite, you can use `SetUpTestSuite()` and `TearDownTestSuite()`.



```cpp
class FooTest : public testing::Test {
 protected:
  // Per-test-suite set-up.
  // Called before the first test in this test suite.
  // Can be omitted if not needed.
  static void SetUpTestSuite() {
    shared_resource_ = new ...;
  }

  // Per-test-suite tear-down.
  // Called after the last test in this test suite.
  // Can be omitted if not needed.
  static void TearDownTestSuite() {
    delete shared_resource_;
    shared_resource_ = nullptr;
  }

  // You can define per-test set-up logic as usual.
  void SetUp() override { ... }

  // You can define per-test tear-down logic as usual.
  void TearDown() override { ... }

  // Some expensive resource shared by all tests.
  static T* shared_resource_;
};

T* FooTest::shared_resource_ = nullptr;

TEST_F(FooTest, Test1) {
  ... you can refer to shared_resource_ here ...
}

TEST_F(FooTest, Test2) {
  ... you can refer to shared_resource_ here ...
}
```

Refs: [1](https://github.com/google/googletest/blob/master/docs/advanced.md#sharing-resources-between-tests-in-the-same-test-suite)

## Global Set-Up and Tear-Down
Refs: [1](https://github.com/google/googletest/blob/master/docs/advanced.md#global-set-up-and-tear-down)

## Running Tests and Patterns
You can list all the test:

```cpp
<test executable> --gtest_list_tests
```
You can run specific tests:
```cpp
<test executable> --gtest_filter=<test-fixutre-name>
```
or with pattern
```cpp
<test executable> --gtest_filter=*<test-fixutre-name>*
```

or exclude specific tests:
```cpp
<test executable> --gtest_filter=-*<test-fixutre-name>*
```

## Google Test XML report

```cpp
<test executable> --gtest_output=xml:<filename>
```


# Google Mock
Let say you have a class which use an interface and you interested to test the class and not the interface. For example your interface would be a class called `IRandomNumberGenerator` which can generate random number with various data distribution. 
This class should be an abstract calss (which cannot be instantiated) and depending on the desired distribution, the real job should be implemented in classes such as `UniformRandomNumberGenerator`, `GammaRandomNumberGenerator`, etc which inherite from `IRandomNumberGenerator` class.

The class that you are interested to test is `CoinFlipper` which needs a random generator. We use dependency injection 
and instead of having your application talk to the system API directly, wrap the API in an interface (`IRandomNumberGenerator`) and code to that interface

So in your `CoinFlipper` calss you have memeber that is a pointer from `IRandomNumberGenerator` type.  In fact a pointer to the interface type should be passed into the constructor of `CoinFlipper`. It is best practice to use a smart pointer in these cases, to avoid memory management issues.


Since we interested to only test `CoinFlipper`,  (which needs an instance of `IRandomNumberGenerator`) and that instances might have non-deterministic behaviour which can't be reliably controlled, we create a mock object that inherite from `IRandomNumberGenerator` and we pass that to `CoinFlipper`.

In fact any code that is non-deterministic for example:

- External data sources (e.g. files, databases)
- Network connections (e.g. services)
- External code dependencies (libraries)
- Internal code dependencies
would be mocked via a mock class and In the production code, the constructor will be called with a pointer to an instance of the implementation class, and in the tests, the constructor will be called with a pointer to an instance of the mock class. 

<!--- correspondig PlantUML model 
@startuml
CoinFlipper..> IRandomNumberGenerator
databaseConnect <|-- MockRandomNumberGenerator
CoinFlipper..> MockRandomNumberGenerator
@enduml
-->

![PlantUML model](http://www.plantuml.com/plantuml/svg/SoWkIImgAStDuNBEpynpoyaiA4WjqjEpK_0CIinBoS_rAyrDIYroJyrBBKeioI_YmYwiO5EZgwlWcv-SZLKQpMmy2XrIyrA0ZW40)


A mock should inherit from an abstract class, generally, that defines a virtual destructor explicitly and defines a pure virtual function for any method that will be needed by the mock objects. In other words, you can't mock non-virtual methods.
The destructor of interface class must be virtual, as is the case for all classes you intend to inherit from - otherwise the destructor of the derived class will not be called when you delete an object through a base pointer, and you'll get corrupted program states like memory leaks.)

```cpp
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

```
## Writing the Mock Class

1) Derive a class `MockRandomNumberGenerator` from `IRandomNumberGenerator`

2) For every vitual function use the following macros:

```cpp
MOCK_METHOD[n](methodName, returnType(arg1Type, ..., argNType));
MOCK_CONST_METHOD[n](methodName, returnType(arg1Type, ..., argNType));
```
So you should have something like this in your code:

```cpp
class MockRandomNumberGenerator: public IRandomNumberGenerator
{
public:
    MOCK_METHOD2(generate,double(double,double));
};
```

## Writting the Test 

You test should have the follwoing format:

```cpp
EXPECT_CALL(mockObject, method(arg1Matcher, ..., argNMatcher))
    .With(multiArgumentMatcher)  // 0 or 1
    .Times(cardinality)          // 0 or 1
    .InSequence(sequences)       // 0+
    .After(expectations)         // 0+
    .WillOnce(action)            // 0+
    .WillRepeatedly(action)      // 0 or 1
    .RetiresOnSaturation();      // 0 or 1
```
For example:

```cpp
TEST(CoinFlipper, flip)
{
    // 1) Create mock objects
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

```

An other example:

```cpp
EXPECT_CALL(*rng_ptr, generate(0.0,1.0))
	.Times(5)
	.WillOnce(Return(0.15))
	.WillOnce(Return(0.35))
	.WillRepeatedly(Return(0.75));
```

## Mocking Non-virtual Methods
gMock can mock non-virtual functions to be used in Hi-perf dependency injection. To achieve this, you have to create a mock class that 
has functions with the same signature of your real class. You dont inherite from your real class and 
your mock class will be unrelated to the real class.
Now have to templatize your consumer class (your consumer class has an intance of your real class). In the production you send an instance 
of real class and during testing you send an instance of mock class;


Here your class has no virtual function:

```cpp
class RealClass
{
public:
    int generate()
    {
        return 10;
    }
};
```

We mock the real class with all functions:

```cpp
class MockRealClass
{
public:
    MOCK_METHOD(int , generate,());
};
```

Here we templatize the consumer class:
```cpp
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
```

During the test we send an instance of mock class and during production we send an instance of real class:
```cpp
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
```

## Delegating Calls
Sometimes the behavior of the mock classes might differ from the real objects. This could be intentional i.e for simulating an error such that you can test the error handling code. If your mocks have different behaviors than the real objects by mistake, you could end up with code that passes the tests but fails in production. Imagine you have the following interface:

```cpp
class Foo
{
public:
    virtual ~Foo() {}
    virtual char DoThis(int n) = 0;
    virtual void DoThat(const char* s, int* p) = 0;
};
```

You can use the followings:

### Delegating Calls to Fake Class
Now you want to mock this interface such that you it uses `FakeFoo` for the default behavior.
When you define the mock class using gMock, you can have it delegate its default action to a fake class you already have, using this pattern.
```cpp
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

```


```cpp

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
```



### Delegating Calls to Real Class

You can use the `delegating to real`  to ensure that your mock has the same functionality as the real object while keeping 
the ability to validate calls. This technique is very similar to the above one (`delegating to fake`), the difference is that 
we use a real object instead of a fake.

```cpp
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



```

### Delegating Calls to Parent Class
Ideally, you should code to interfaces, whose methods are all pure virtual. In reality, sometimes you do need to mock a virtual method that is not pure (i.e, it already has an implementation). For example:

```cpp
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
```


Full example available [here](tests/src/delegating_calls.cpp) 

## Matchers
Matchers are functions used to match mock inputs to their expected values:

## Common Matchers
<!-- mdformat off(github rendering does not support multiline tables) -->

| Matcher	                                        | Matches                                | 
| --------------------------                            | ------------------------------         | 
|`_`	                                                |matches anything                        |
|`Eq(value)`	                                        |values using operator==()               |
|`DoubleEq(value)`	                                |values using fuzzy 64-bit float equality|
|`IsNull()`	                                        |null raw/smart pointers                 |
|`StrCaseEq(string)`	                                |string (case-insensitive)               |
|`HasSubstr(string)`	                                |strings with given substring            |
|`Contains(elem)`	                                |containers that contain elem at least once|
|`UnorderedElementsAre(e0, e1, ...)`                    |containers that contain specified elements, ignoring order|
|`Field(&class::field, matcher)` (e.g. obj.d_age)       |objects with value for specified member variable|
|`Property(&class::property, matcher)` (e.g. obj.age()) |objects with value for specified member function |

<!-- mdformat on-->

### Defining Matchers
```
MATCHER(IsEven, "") { return (arg % 2) == 0; }
```
For example:
```
MATCHER_P(IsDivisibleBy, n, "") 
{
    return (arg % n) == 0;
}

// all numbers in vector being written should be even
EXPECT_CALL(writer, writeVec(Each(IsEven))
    .Times(Exactly(1)).WillOnce(Return(0));

// all numbers in vector being written should be divisible by 3
EXPECT_CALL(writer, writeVec(Each(IsDivisibleBy(3))))
    .Times(Exactly(1)).WillOnce(Return(0));

```
## Actions
Actions specify what a mock method does when called

```
EXPECT_CALL(writer, writeVec(_))
    .Times(Exactly(1)).WillOnce(
        Return(1) // action
    );
```

## Common Actions
<!-- mdformat off(github rendering does not support multiline tables) -->
| Action	        |                                                                              | 
| ----------------------| ------------------------------                                               | 
|Return(value)	        |Return specified value                                                        |
|SetArgPointee<N>()	|Set value of Nth argument passed to mocked method (useful for out parameters) |
|Throw(exception)	|Throw specified exception                                                     |
|Invoke(f)	        |Invoke function f with arguments passed to mocked method                      |
|DoAll(a1, a2, ..., aN)	|Perform multiple actions in sequence                                          |
<!-- mdformat on-->

### Defining Actions
```
ACTION(Sum) 
{
    return arg0 + arg1;
}
```
For example
```
// parametrised action
ACTION_P(AppendName, name) {
    arg0.push_back(name);
}

EXPECT_CALL(calculator, add(_, _))
    .Times(Exactly(1)).WillOnce(Sum());

EXPECT_CALL(customerDatabase, retrieveCustomerNames(_))
    .Times(Exactly(1)).WillOnce(DoAll(
        AppendName("Bob"),
        AppendName("Susie"),
        Return(0)             // retrieval was a success
    ));
```

## Where to Place Mocked Interfaces Code
If you need to mock `IFoo` and it's is not your code and belonged to others, you can do the following:

1) Define a sub-package test in IFoo's package, put it in a .h and a cc_library  and  everyone can reference them from their tests. If `IFoo` ever changes, there is only one copy of `MockIFoo` to change, 
and only tests that depend on the changed methods need to be fixed.

2) you can introduce a thin layer `FooAdaptor` on top of `IFoo` and code to this new interface. Since you own `FooAdaptor`, you can absorb changes
 in Foo much more easily. While this is more work initially, carefully choosing the adaptor interface can make your code easier to write and more readable (a net win in the long run), as you can choose `FooAdaptor` to fit your specific domain much better than Foo does.


## Mocking Private or Protected Methods
C++ allows a subclass to change the access level of a virtual function in the base class.

```
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
```

## Mocking Class Templates


```
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
```

# Testing Multi-Threaded Code

# Test-Driven Development (TDD) 


# Code Coverage with GCC
Here I have used `gcov`, `ggcov` and `lcov` for my code coverage. Obtain a copy of `CodeCoverage.cmake` from [here](https://github.com/bilke/cmake-modules/blob/master/CodeCoverage.cmake) and copy it into 
`cmake/Modules/`. Then add the followings to your CMakeLists.txt

```
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
if(CMAKE_COMPILER_IS_GNUCXX)
    include(CodeCoverage) # this will include CodeCoverage.cmake
endif()

append_coverage_compiler_flags()
setup_target_for_coverage_lcov(
        NAME coverage
        EXECUTABLE ctest -j ${n_cores} # Executable in PROJECT_BINARY_DIR
        DEPENDENCIES
        <your-executable_targes1> <your-executable_targes1>)
```
Now run:
```
make coverage && firefox ./coverage/index.html
```
This will generate a report in `./coverage/index.html`.



# Code Coverage with Clang-tidy


# Cppcheck
Cppcheck is an open-source static analysis tool for C/C++. Static analysis is the analysis of code without executing it. To check a single file
you can use the following:
```
cppcheck  <your-source-file>.cpp 
```

If have more than one file with lots of header and libraries, you have to pass these details to Cppcheck as well. The easiest way to do this is 
to use a [compilation database](http://clang.llvm.org/docs/JSONCompilationDatabase.html). cmake can create that for you. All you have to do
 is just to set `CMAKE_EXPORT_COMPILE_COMMANDS`: 

```
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON 
```

or in the CMakeLists.txt

```
set(CMAKE_EXPORT_COMPILE_COMMANDS ON )
```
This will generate the file `compile_commands.json`. Now run Cppcheck like this:
```
cppcheck --project=compile_commands.json
```

To ignore certain folders you can use -i. This will skip analysis of source files in the foo folder.
```
cppcheck --project=compile_commands.json -ifoo
```
## Integrating Cppcheck into CMake
First you need to add the path to `FindCppcheck.cmake` to your CMakeLists.txt:
```
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
```

### Suppression
You can enable/ disable some warnings in Cppcheck using a suppression file. Default value for a suppressions file in `.cppcheck_suppressions`. To specify you custom file use:

```
set(CPPCHECK_SUPPRESSIONS ${PROJECT_ROOT_DIR}/CppCheckSuppressions.txt)
```
### exitcode

When Cppcheck finds errors you can tell it what error code to use when exiting the program. With the above script the default exitcode is 1. To override this you can use the CPPCHECK_ERROR_EXITCODE_ARG. To set it to use the cppcheck default

```
set(CPPCHECK_ERROR_EXITCODE_ARG "")
```

### XML output
You can set the output of the Cppcheck to XML so later on the result can be read by CI systems:
 
```
set(CPPCHECK_XML_OUTPUT "${PROJECT_BINARY_DIR}/analysis/cppcheck/cppcheck_analysis.xml")
```


### Excluding files
To exclude a file or folder you can create a list CPPCHECK_EXCLUDES, this is very usefull for excluding third partiy and libraries

```
set(CPPCHECK_EXCLUDES
    ${CMAKE_SOURCE_DIR}/3rd_party
    ${CMAKE_BINARY_DIR}/
)
```

# Valgrind call-graph 
Callgrind is a profiling tool that records the call history among functions in a program's run as a call-graph. 
By default, the collected data consists of the number of instructions executed, their relationship to source lines, 
the caller/callee relationship between functions. To start a profile run for a program, execute:

`valgrind --tool=callgrind ./<your-binary>`.

It will generate a file called `callgrind.out.x`. You can then use `kcachegrind` tool to read this file. It will give you a graphical analysis of things with results like which lines cost how much.


[![Build Status](https://travis-ci.com/behnamasadi/software_quality_assurance.svg?branch=master)](https://travis-ci.com/behnamasadi/software_quality_assurance)
![alt text](https://img.shields.io/badge/license-BSD-blue.svg)

<small><i>TOC generated with <a href='http://ecotrust-canada.github.io/markdown-toc/'>markdown-toc</a></i></small>


Ref:    [1](https://github.com/google/googletest/blob/master/googletest/docs/primer.md),
	[2](https://github.com/google/googletest/blob/master/googlemock/docs/for_dummies.md),
	[3](https://chromium.googlesource.com/external/github.com/google/googletest/+/HEAD/googletest/docs/advanced.md),
	[4](https://github.com/google/googletest/blob/master/googlemock/docs/cook_book.md),
	[5](https://github.com/google/googletest/blob/master/googlemock/docs/cheat_sheet.md),
	[6](http://donsoft.io/gmock-presentation/),
	[7](https://github.com/davidstutz/googlemock-example),
	[8](https://medium.com/foxguard-development/google-test-and-google-mock-20a7e416f93e),
	[9](https://stackoverflow.com/questions/3152326/google-test-parameterized-tests-which-use-an-existing-test-fixture-class),
	[10](https://stackoverflow.com/questions/47354280/what-is-the-best-way-of-testing-private-methods-with-googletest/47358700),
	[11](https://chromium.googlesource.com/external/github.com/google/googletest/+/HEAD/googletest/samples/sample6_unittest.cc),
	[12](https://ctest-ext.readthedocs.io/en/v0.7.1/usage/project_script/),
	[13](https://gitlab.kitware.com/cmake/community/-/wikis/doc/ctest/Testing-With-CTest),
	[14](https://ctest-ext.readthedocs.io/en/v0.7.1/ci/travis/),
	[15](http://www.stablecoder.ca/2018/01/15/code-coverage.html),
	[16](https://stackoverflow.com/questions/13116488/detailed-guide-on-using-gcov-with-cmake-cdash),
	[17](http://cppcheck.sourceforge.net/manual.html#cmake),
	[18](https://valgrind.org/docs/manual/cl-manual.html),
	[19](https://hopstorawpointers.blogspot.com/2018/11/integrating-cppcheck-and-cmake.html),
	[20](https://github.com/ttroy50/cmake-examples/tree/master/04-static-analysis/cppcheck)
