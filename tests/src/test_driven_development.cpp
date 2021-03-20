/*
http://alexott.net/en/cpp/CppTestingIntro.html
Ref: https://www.youtube.com/watch?v=pkdwtRAUIkE
1)Write enough failing Test Code (include compile time and run time failures)
2)Write Production code to pass the failing tests.
3)Refactor the production code and verify the same with existing test.
4)Go to step 1
*/

#include <gtest/gtest.h>
#include <memory>
/*
class Binarytree
{
public:
    int value;
    Binarytree *left, *right;
    Binarytree(int val):value(val),left(nullptr), right(nullptr){}
};

Binarytree * makeBinarytree(int value)
{
    Binarytree * bst= new Binarytree(value);
    return bst;
}

void insertNode(Binarytree * tree, int value)
{
    while(1)
    {
        if(value>tree->value)
        {
            if(tree->right==nullptr)
            {
                tree->right=makeBinarytree(value);
                break;
            }
            else
            {
                tree=tree->right;
                continue;
            }
        }
        else if(value<tree->value)
        {
            if(tree->left==nullptr)
            {
                tree->left=makeBinarytree(value);
                break;
            }
            else
            {
                tree=tree->left;
                continue;
            }
        }
        else
        {
            std::cout<<"no duplicate" <<std::endl;
        }
    }
}

void printTree(Binarytree *tree)
{
    std::cout<<tree->value <<std::endl;
    if(tree->left!=nullptr)
        printTree(tree->left);
    if(tree->right!=nullptr)
        printTree(tree->right);
}
class testingBinarytree: public ::testing::Test
{
protected:
    testingBinarytree(){}
    ~testingBinarytree(){}
    void SetUp(){}
    void TearDown(){}
};

TEST_F(testingBinarytree,makeBinarytree)
{
    int value=8;
    Binarytree * binary_search_tree=makeBinarytree(value);
    EXPECT_NE(binary_search_tree,nullptr);
}

TEST_F(testingBinarytree,traverseTree)
{
    int value=8;
    Binarytree * binary_search_tree=makeBinarytree(value);

    insertNode(binary_search_tree,1);
    insertNode(binary_search_tree,3);
    insertNode(binary_search_tree,4);
    insertNode(binary_search_tree,6);
    insertNode(binary_search_tree,7);
    insertNode(binary_search_tree,10);
    insertNode(binary_search_tree,13);
    insertNode(binary_search_tree,14);
    printTree(binary_search_tree);
}

int main(int argc, char ** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
*/


class Tree
{
public:
    Tree(double data):data(data){}
    std::array<std::shared_ptr<Tree>,2 > leaves;
    /*
    tree->leaves[0] left node
    tree->leaves[1] right node
    */
    double data;
};

std::shared_ptr<Tree> makeTree(double data)
{
    std::shared_ptr<Tree> tree(new Tree(data));
    return tree;
}

void insertNode(std::shared_ptr<Tree> tree, double data)
{
    while(1)
    {
        if(data>tree->data)
        {
            if(tree->leaves[1] ==nullptr)
            {
                tree->leaves[1]=makeTree(data);
                break;
            }
            else
            {
                tree=tree->leaves[1];
                continue;
            }
        }
        else if(data<tree->data)
        {
            if(tree->leaves[0]==nullptr)
            {
                tree->leaves[0]=makeTree(data);
                break;
            }
            else
            {
                tree=tree->leaves[0];
                continue;
            }
        }
        else
        {
            std::cout<<"no duplicate" <<std::endl;
        }
    }
}

void DFS(std::shared_ptr<Tree> rootNode)
{
    std::cout<<rootNode->data <<std::endl;
    for(auto n:rootNode->leaves)
    {
        if(n!=nullptr)
            DFS(n);
    }
}

class testingTree: public ::testing::Test
{
protected:
    testingTree(){}
    ~testingTree(){}
    void SetUp(){}
    void TearDown(){}
};

TEST_F(testingTree,makeTree)
{
    std::shared_ptr<Tree> tree=makeTree(-1);
    EXPECT_NE(tree.get(),nullptr);
}

TEST_F(testingTree,traverseTree)
{
    int value=5;
    std::shared_ptr<Tree> tree=makeTree(value);


/*
                    5
                  /   \
                3       7
              /  \    /
             4    1  6
*/
    insertNode(tree,3);
    insertNode(tree,7);
    insertNode(tree,4);
    insertNode(tree,1);
    insertNode(tree,6);
    DFS(tree);
}


int main(int argc, char ** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
