# Google Test, Google Mocking and Test Driven Development Sample
This repository contains snippet code of how to use Google Test and Google Mocking (Gtest, GMock) and Test Driven Development

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

### Test-Driven Development (TDD) 





## Google Mock
Let say you have a component which use an interface and you interested to test the component and not the interface. For example your interface would be a class called `databaseConnect` which can connect you to sql server, mysql server, sqlite, etc and your data access layer class would called 
`databaseLayer`

 This class should be an abstract calss (which cannot be instantiated) and depending on the database type the real job should be implemented in classes such as `sqlServerConnector`, `mysqlServerConnector` which inherite from `databaseConnect` class.

You data access layer class, `databaseLayer` use `databaseConnect` type to establish connection to different databases type, in fact a pointer to the interface type should be passed into the constructor of `databaseLayer`. It is best practice to use a smart pointer in these cases, to avoid memory management issues.


Since we interested to only test `databaseLayer`, and instances of `databaseConnect` might have non-deterministic behaviour which can't be reliably controlled, we create a mock object that inherite from `databaseConnect` and we pass that to `databaseLayer`.

In fact any code that is non-deterministic for example:

- External data sources (e.g. files, databases)
- Network connections (e.g. services)
- External code dependencies (libraries)
- Internal code dependencies
would be mocked via a mock class and In the production code, the constructor will be called with a pointer to an instance of the implementation class, and in the tests, the constructor will be called with a pointer to an instance of the mock class. 

<!--- correspondig PlantUML model 
@startuml
databaseLayer..> databaseConnect
databaseConnect <|-- MockDB
databaseLayer..> MockDB
@enduml
-->

![PlantUML model](http://www.plantuml.com/plantuml/svg/SoWkIImgAStDuKf9B4bCIYnEzKciJ2tIqxDJW0auv-VbfIQNSA7n5MngT7KLVFEJirsSC3J3n1rIyrA0XWC0)


A mock should inherit from an abstract class, generally, that defines a virtual destructor explicitly and defines a pure virtual function for any method that will be needed by the mock objects.

The destructor of interface class must be virtual, as is the case for all classes you intend to inherit from - otherwise the destructor of the derived class will not be called when you delete an object through a base pointer, and you'll get corrupted program states like memory leaks.)



## Google Test XML report

```
<test executable> --gtest_output=xml:<filename>
```

## Testing Multi-Threaded Code


# Test Driven Development



[![Build Status](https://travis-ci.org/behnamasadi/gtest_gmock.svg?branch=master)](https://travis-ci.org/behnamasadi/gtest_gmock)
![alt text](https://img.shields.io/badge/license-BSD-blue.svg)

Ref:    [1](https://github.com/google/googletest/blob/master/googletest/docs/primer.md),
	[2](https://chromium.googlesource.com/external/github.com/google/googletest/+/HEAD/googlemock/docs/cook_book.md#MockingNonVirtualMethods),
	[3](https://chromium.googlesource.com/external/github.com/google/googletest/+/HEAD/googlemock/docs/for_dummies.md),
	[4](https://github.com/google/googletest/blob/master/googlemock/docs/for_dummies.md),
	[5](https://stackoverflow.com/questions/47354280/what-is-the-best-way-of-testing-private-methods-with-googletest/47358700)





