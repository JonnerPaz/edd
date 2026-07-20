#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "BSTree.hpp"
#include "AVLTree.hpp"
#include "exercises/maxDepth.hpp"
#include "exercises/invertTree.hpp"
#include "exercises/sameTree.hpp"
#include "exercises/isBalanced.hpp"
#include "exercises/isValidBST.hpp"
#include "exercises/lca.hpp"
#include "exercises/diameter.hpp"
#include "exercises/pathSum.hpp"
#include "exercises/kthSmallest.hpp"
#include "exercises/levelOrder.hpp"
#include "exercises/zigzag.hpp"
#include "exercises/rootToLeafPaths.hpp"
#include "exercises/sortedArrayToBST.hpp"
#include "exercises/buildTreeFromInorderPreorder.hpp"

static int testsPassed = 0;
static int testsFailed = 0;

void check(bool condition, const std::string& name)
{
    if (condition) {
        std::cout << "  \033[32mPASS\033[0m  " << name << "\n";
        testsPassed++;
    } else {
        std::cout << "  \033[31mFAIL\033[0m  " << name << "\n";
        testsFailed++;
    }
}

template <typename F>
std::string captureTraversal(F func)
{
    std::stringstream buffer;
    auto old = std::cout.rdbuf(buffer.rdbuf());
    func();
    std::cout.rdbuf(old);
    return buffer.str();
}

void testEmptyBST()
{
    std::cout << "\n--- Empty BST ---\n";
    BSTree<int> t;
    check(t.countNodes() == 0, "countNodes == 0");
    check(t.countLeaves() == 0, "countLeaves == 0");
    check(t.height() == 0, "height == 0");

    auto out = captureTraversal([&]() { t.inorder(); });
    check(out == "\n", "inorder prints just newline");

    check(!t.search(5), "search 5 returns false");

    bool threw = false;
    try { t.findMin(); } catch (const std::runtime_error&) { threw = true; }
    check(threw, "findMin throws on empty");

    threw = false;
    try { t.findMax(); } catch (const std::runtime_error&) { threw = true; }
    check(threw, "findMax throws on empty");
}

void testBSTInsertAndSearch()
{
    std::cout << "\n--- BST Insert & Search ---\n";
    BSTree<int> t;
    t.insert(5);
    t.insert(3);
    t.insert(7);
    t.insert(2);
    t.insert(4);
    t.insert(6);
    t.insert(8);

    check(t.search(5), "search root 5");
    check(t.search(2), "search leaf 2");
    check(t.search(8), "search leaf 8");
    check(!t.search(1), "search 1 (not found)");
    check(!t.search(9), "search 9 (not found)");

    t.insert(5);
    check(t.countNodes() == 7, "duplicate insert does not add node");
}

void testBSTMinMax()
{
    std::cout << "\n--- BST Min / Max ---\n";
    BSTree<int> t;
    t.insert(10);
    t.insert(3);
    t.insert(15);
    t.insert(1);
    t.insert(20);

    check(t.findMin() == 1, "findMin == 1");
    check(t.findMax() == 20, "findMax == 20");
}

void testBSTHeightCount()
{
    std::cout << "\n--- BST Height / Count / Leaves ---\n";

    BSTree<int> t;
    t.insert(5);
    t.insert(3);
    t.insert(7);
    t.insert(2);
    t.insert(4);
    t.insert(6);
    t.insert(8);

    check(t.countNodes() == 7, "countNodes == 7");
    check(t.countLeaves() == 4, "countLeaves == 4 (2,4,6,8)");
    check(t.height() == 3, "height == 3");
}

void testBSTTraversals()
{
    std::cout << "\n--- BST Traversals ---\n";

    BSTree<int> t;
    t.insert(5);
    t.insert(3);
    t.insert(7);
    t.insert(2);
    t.insert(4);
    t.insert(6);
    t.insert(8);

    auto in = captureTraversal([&]() { t.inorder(); });
    check(in == "2 3 4 5 6 7 8 \n", "inorder: " + in);

    auto pre = captureTraversal([&]() { t.preorder(); });
    check(pre == "5 3 2 4 7 6 8 \n", "preorder: " + pre);

    auto post = captureTraversal([&]() { t.postorder(); });
    check(post == "2 4 3 6 8 7 5 \n", "postorder: " + post);
}

void testBSTRremove()
{
    std::cout << "\n--- BST Remove ---\n";

    BSTree<int> t;
    t.insert(5);
    t.insert(3);
    t.insert(7);
    t.insert(2);
    t.insert(4);
    t.insert(6);
    t.insert(8);

    t.remove(2);
    check(!t.search(2), "remove leaf 2");
    check(t.countNodes() == 6, "countNodes after removing 2");

    t.remove(7);
    check(!t.search(7), "remove node with two children (7)");
    check(t.countNodes() == 5, "countNodes after removing 7");

    BSTree<int> t2;
    t2.insert(10);
    t2.insert(5);
    t2.insert(15);
    t2.remove(5);
    check(!t2.search(5), "remove node with one child (5)");
    check(t2.countNodes() == 2, "countNodes after removing 5");

    BSTree<int> t3;
    t3.insert(1);
    t3.remove(1);
    check(t3.countNodes() == 0, "remove root (only node)");
}

void testBSTSuccessorPredecessor()
{
    std::cout << "\n--- BST Successor / Predecessor ---\n";

    BSTree<int> t;
    t.insert(5);
    t.insert(3);
    t.insert(7);
    t.insert(2);
    t.insert(4);
    t.insert(6);
    t.insert(8);

    check(t.successor(2) == 3, "successor(2) == 3");
    check(t.successor(5) == 6, "successor(5) == 6");

    {
        bool threw = false;
        try { t.successor(8); } catch (const std::runtime_error&) { threw = true; }
        check(threw, "successor(8) throws (no successor)");
    }

    check(t.predecessor(8) == 7, "predecessor(8) == 7");
    check(t.predecessor(5) == 4, "predecessor(5) == 4");

    {
        bool threw = false;
        try { t.predecessor(2); } catch (const std::runtime_error&) { threw = true; }
        check(threw, "predecessor(2) throws (no predecessor)");
    }
}

void testBSTIsValid()
{
    std::cout << "\n--- BST isValidBST ---\n";

    BSTree<int> t;
    t.insert(5);
    t.insert(3);
    t.insert(7);
    check(t.isValidBST(), "valid tree");

    BSTree<int> t2;
    t2.insert(5);
    t2.insert(3);
    t2.insert(7);
    check(t2.isValidBST(), "valid tree #2");
}

void testBSTCopy()
{
    std::cout << "\n--- BST Copy ---\n";

    BSTree<int> t1;
    t1.insert(5);
    t1.insert(3);
    t1.insert(7);

    BSTree<int> t2(t1);
    check(t2.countNodes() == 3, "copy constructor: countNodes");
    check(t2.search(5), "copy constructor: search 5");
    check(t2.search(3), "copy constructor: search 3");
    check(t2.search(7), "copy constructor: search 7");

    BSTree<int> t3;
    t3 = t1;
    check(t3.countNodes() == 3, "assignment: countNodes");
    check(t3.search(5), "assignment: search 5");

    t1.insert(99);
    check(!t2.search(99), "deep copy: modifying original does not affect copy");
}

void testAVLInsertNoRotation()
{
    std::cout << "\n--- AVL Insert (no rotation) ---\n";

    AVLTree<int> t;
    t.insert(5);
    t.insert(3);
    t.insert(7);

    check(t.isBalanced(), "balanced after inserts");
    check(t.countNodes() == 3, "countNodes == 3");

    auto in = captureTraversal([&]() { t.inorder(); });
    check(in == "3 5 7 \n", "inorder: " + in);
}

void testAVLInsertLeftLeft()
{
    std::cout << "\n--- AVL Insert Left-Left (3,2,1) ---\n";

    AVLTree<int> t;
    t.insert(3);
    t.insert(2);
    t.insert(1);

    check(t.isBalanced(), "tree is balanced");

    auto pre = captureTraversal([&]() { t.preorder(); });
    check(pre == "2 1 3 \n", "preorder after LL rotation: " + pre);

    check(t.height() == 2, "height == 2");
}

void testAVLInsertRightRight()
{
    std::cout << "\n--- AVL Insert Right-Right (1,2,3) ---\n";

    AVLTree<int> t;
    t.insert(1);
    t.insert(2);
    t.insert(3);

    check(t.isBalanced(), "tree is balanced");

    auto pre = captureTraversal([&]() { t.preorder(); });
    check(pre == "2 1 3 \n", "preorder after RR rotation: " + pre);

    check(t.height() == 2, "height == 2");
}

void testAVLInsertLeftRight()
{
    std::cout << "\n--- AVL Insert Left-Right (5,2,6,1,3,4) ---\n";

    AVLTree<int> t;
    t.insert(5);
    t.insert(2);
    t.insert(6);
    t.insert(1);
    t.insert(3);
    t.insert(4);

    check(t.isBalanced(), "tree is balanced after LR insertions");

    auto pre = captureTraversal([&]() { t.preorder(); });
    check(pre == "3 2 1 5 4 6 \n",
          "preorder after LR rotation: " + pre);

    auto in = captureTraversal([&]() { t.inorder(); });
    check(in == "1 2 3 4 5 6 \n",
          "inorder after LR rotation: " + in);
}

void testAVLInsertRightLeft()
{
    std::cout << "\n--- AVL Insert Right-Left (1,3,2) ---\n";

    AVLTree<int> t;
    t.insert(1);
    t.insert(3);
    t.insert(2);

    check(t.isBalanced(), "tree is balanced after RL insertions");

    auto pre = captureTraversal([&]() { t.preorder(); });
    check(pre == "2 1 3 \n", "preorder after RL rotation: " + pre);
}

void testAVLRemove()
{
    std::cout << "\n--- AVL Remove ---\n";

    AVLTree<int> t;
    t.insert(5);
    t.insert(3);
    t.insert(7);
    t.insert(2);
    t.insert(4);
    t.insert(6);
    t.insert(8);

    t.remove(2);
    check(t.isBalanced(), "balanced after removing leaf 2");
    check(!t.search(2), "2 removed");
    check(t.countNodes() == 6, "countNodes == 6");

    t.remove(5);
    check(t.isBalanced(), "balanced after removing root 5");
    check(!t.search(5), "5 removed");
    check(t.countNodes() == 5, "countNodes == 5");
}

void testAVLCopy()
{
    std::cout << "\n--- AVL Copy ---\n";

    AVLTree<int> t1;
    t1.insert(3);
    t1.insert(2);
    t1.insert(1);

    AVLTree<int> t2(t1);
    check(t2.isBalanced(), "copy is balanced");
    check(t2.countNodes() == 3, "copy countNodes");
    check(t2.search(2), "copy search 2");

    AVLTree<int> t3;
    t3 = t1;
    check(t3.isBalanced(), "assignment is balanced");
    check(t3.countNodes() == 3, "assignment countNodes");
}

void testExercises()
{
    std::cout << "\n========================================\n";
    std::cout << "         EXERCISE TESTS\n";
    std::cout << "========================================\n";

    BSTree<int> t;
    t.insert(5); t.insert(3); t.insert(7);
    t.insert(2); t.insert(4); t.insert(6); t.insert(8);

    NodeTree<int>* root = t.getRoot();

    check(maxDepth(root) == 3, "maxDepth");
    check(isBalanced(root), "isBalanced");

    check(lcaBST(root, 2, 4)->getData() == 3, "lca 2,4");
    check(lcaBST(root, 2, 8)->getData() == 5, "lca 2,8");
    check(diameter(root) == 4, "diameter");
    check(kthSmallest(root, 1) == 2, "kth 1st");
    check(kthSmallest(root, 3) == 4, "kth 3rd");
    check(kthSmallest(root, 7) == 8, "kth 7th");
    check(hasPathSum(root, 10), "pathSum 10");
    check(hasPathSum(root, 12), "pathSum 12");
    check(!hasPathSum(root, 1), "pathSum 1 false");

    check(isValidBST(root), "isValidBST");
    check(sameTree(root, root), "sameTree identical");

    auto lo = captureTraversal([&]() { levelOrder(root); });
    check(lo == "Nivel 0: 5 \nNivel 1: 3 7 \nNivel 2: 2 4 6 8 \n",
          "levelOrder output");

    auto zz = captureTraversal([&]() { zigzagLevelOrder(root); });
    check(zz == "Nivel 0: 5 \nNivel 1: 7 3 \nNivel 2: 2 4 6 8 \n",
          "zigzag output");

    auto paths = captureTraversal([&]() { rootToLeafPaths(root); });
    check(paths == "5 → 3 → 2\n5 → 3 → 4\n5 → 7 → 6\n5 → 7 → 8\n",
          "paths output");

    int preArr[] = {5,3,2,4,7,6,8};
    int inArr[] = {2,3,4,5,6,7,8};
    NodeTree<int>* built = buildTreeFromInorderPreorder(preArr, inArr, 7);
    check(maxDepth(built) == 3, "buildTree height");

    int sarr[] = {1,2,3,4,5};
    NodeTree<int>* sa = sortedArrayToBST(sarr, 5);
    check(maxDepth(sa) == 3, "sortedArrayToBST height");

    check(!sameTree(root, sa), "sameTree different");

    NodeTree<int>* inv = invertTree(root);
    check(inv->getData() == 5, "invert root");
    check(inv->getLeftNode()->getData() == 7, "invert left");
    check(inv->getRightNode()->getData() == 3, "invert right");
}

void runBSTTests()
{
    std::cout << "\n========================================\n";
    std::cout << "         BINARY SEARCH TREE TESTS\n";
    std::cout << "========================================\n";
    testEmptyBST();
    testBSTInsertAndSearch();
    testBSTMinMax();
    testBSTHeightCount();
    testBSTTraversals();
    testBSTRremove();
    testBSTSuccessorPredecessor();
    testBSTIsValid();
    testBSTCopy();
}

void runAVLTests()
{
    std::cout << "\n========================================\n";
    std::cout << "         AVL TREE TESTS\n";
    std::cout << "========================================\n";
    testAVLInsertNoRotation();
    testAVLInsertLeftLeft();
    testAVLInsertRightRight();
    testAVLInsertLeftRight();
    testAVLInsertRightLeft();
    testAVLRemove();
    testAVLCopy();
}

int main()
{
    runBSTTests();
    runAVLTests();
    testExercises();

    std::cout << "\n========================================\n";
    std::cout << "  Results: " << (testsPassed + testsFailed) << " total, "
              << testsPassed << " \033[32mpassed\033[0m, "
              << testsFailed << " \033[31mfailed\033[0m\n";
    std::cout << "========================================\n";

    return testsFailed > 0 ? 1 : 0;
}
