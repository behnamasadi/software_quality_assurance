- [Google Test](#google-test)
  * [Assertions](#assertions)
    + [Binary Comparison](#binary-comparison)
    + [User Defined Type](#user-defined-type)
    + [String Comparison](#string-comparison)
  * [Simple Tests](#simple-tests)
  * [Test Fixtures](#test-fixtures)
      - [SetUp()](#setup--)
      - [TearDown()](#teardown--)
  * [Google Test XML report](#google-test-xml-report)
  * [Parameterised Test (Template class parameters)](#parameterised-test--template-class-parameters-)
- [Google Mock](#google-mock)
  * [Writing the Mock Class](#writing-the-mock-class)
  * [Writting the Test](#writting-the-test)
  * [Mocking Non-virtual Methods](#mocking-non-virtual-methods)
  * [ON_CALL vs EXPECT_CALL](#on-call-vs-expect-call)
  * [Matchers](#matchers)
  * [Common Matchers](#common-matchers)
    + [Defining Matchers](#defining-matchers)
  * [Actions](#actions)
  * [Common Actions](#common-actions)
    + [Defining Actions](#defining-actions)
  * [Where to Place Mocked Interfaces Code](#where-to-place-mocked-interfaces-code)
- [Testing Multi-Threaded Code](#testing-multi-threaded-code)
- [Test-Driven Development (TDD)](#test-driven-development--tdd-)


This repository contains snippet code of how to use Google Test and Google Mocking (Gtest, GMock) and Test Driven Development

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
│        └── lib.hpp  
├──src  
│    ├──CMakeLists.txt  
│    ├──lib.cpp  
│    └──include  
│        └──private_header.hpp  
├──apps  
│    ├──CMakeLists.txt  
│    └──app.cpp  
├──tests  
│    ├──CMakeLists.txt  
│    ├──project_test.cmake
│    └──src  
├──docs  
│    └── CMakeLists.txt  
├──extern  
|    └──googletest  
└──scripts  
     └──helper.py  
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

```
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
```
Mystruct myobj1,myobj2;
ASSERT_EQ(myobj1,myobj2); // you need to define the corresponding comparison operator (e.g., == or <)
```
Since this is discouraged by the Google C++ Style Guide, you may need to use `ASSERT_TRUE()` or `EXPECT_TRUE()` to assert the equality of two objects of a user-defined type.
```
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

```c++
TEST(TestSuiteName, TestName1) {
  
}

TEST(TestSuiteName, TestName2) {
  
}
```

and your main function:

```
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



```
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
```
TEST_F(FooTest,hasString)
{
    EXPECT_TRUE(myfoo_ptr->hasString("bamboo","boo"));
}
```

## Google Test XML report

```
<test executable> --gtest_output=xml:<filename>
```

## Parameterised Test (Template class parameters)
```
TYPED_TEST_CASE
TYPED_TEST
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

```
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

```
MOCK_METHOD[n](methodName, returnType(arg1Type, ..., argNType));
MOCK_CONST_METHOD[n](methodName, returnType(arg1Type, ..., argNType));
```
So you should have something like this in your code:
```
class MockRandomNumberGenerator: public IRandomNumberGenerator
{
public:
    MOCK_METHOD2(generate,double(double,double));
};
```

## Writting the Test 

You test should have the follwoing format:
```
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
```
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
```
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
```
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
```
class MockRealClass
{
public:
    MOCK_METHOD(int , generate,());
};
```
Here we templatize the consumer class:
```
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
```
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


## ON_CALL vs EXPECT_CALL

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

# Testing Multi-Threaded Code

# Test-Driven Development (TDD) 


[![Build Status](https://travis-ci.com/behnamasadi/gtest_gmock.svg?branch=master)](https://travis-ci.com/behnamasadi/gtest_gmock)
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
	[14](https://ctest-ext.readthedocs.io/en/v0.7.1/ci/travis/)

