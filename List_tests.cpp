#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

TEST(test_list_default_ctor) {
    List<int> empty_list;
    ASSERT_TRUE(empty_list.empty());
}

// TODO add tests for asserts()


TEST(test_add_front_empty) {
    List<int> list;
    list.push_front(4);
    ASSERT_FALSE(list.empty());
    ASSERT_TRUE(list.size() == 1);

}

TEST(test_add_front_twice) {
    List<int> list;
    list.push_front(4);
    list.push_front(5);
    ASSERT_TRUE(list.size() == 2);
    ASSERT_TRUE(list.front() == 5);
    ASSERT_TRUE(list.back() == 4);
}

TEST(test_push_back) {
    List<int> list;
    list.push_back(4);
    list.push_back(5);
    ASSERT_TRUE(list.size() == 2);
    ASSERT_TRUE(list.front() == 4);
    ASSERT_TRUE(list.back() == 5);
}

TEST(pop_front_one_item) {
    List<int> list;
    list.push_front(4);
    list.pop_front();
    ASSERT_TRUE(list.size() == 0);
    ASSERT_TRUE(list.empty());
}

TEST(pop_front_two_items) {
    List<int> list;
    list.push_front(4);
    list.push_back(5);
    ASSERT_TRUE(list.size() == 2);
    list.pop_front();
    ASSERT_TRUE(list.size() == 1);
    ASSERT_TRUE(list.front() == 5);
    ASSERT_TRUE(list.back() == 5);
    list.pop_front();
    ASSERT_TRUE(list.size() == 0);
}

TEST(pop_back_one_item) {
    List<int> list;
    list.push_front(4);
    list.pop_back();
    ASSERT_TRUE(list.size() == 0);
    ASSERT_TRUE(list.empty());
}

TEST(pop_back_two_items) {
    List<int> list;
    list.push_front(4);
    list.push_back(5);
    ASSERT_TRUE(list.size() == 2);
    list.pop_back();
    ASSERT_TRUE(list.size() == 1);
    ASSERT_TRUE(list.front() == 4);
    ASSERT_TRUE(list.back() == 4);
    list.pop_back();
    ASSERT_TRUE(list.size() == 0);
}

TEST(clear) {
    List<int> list;
    list.push_front(3);
    list.push_front(4);
    list.push_back(5);
    list.pop_front();
    list.clear();
    ASSERT_TRUE(list.size() == 0);
    list.push_front(7);
    ASSERT_TRUE(list.size() == 1);
    ASSERT_TRUE(list.front() == 7);
    ASSERT_TRUE(list.back() == 7);
}

TEST(copy_ctor) {
    List<int> list1;
    
    list1.push_front(1);
    list1.push_back(2);
    list1.push_back(3);

    List<int> list2(list1);

    ASSERT_TRUE(list1.size() == 3);
    ASSERT_TRUE(list2.size() == 3);
    ASSERT_TRUE(list1.front() == 1);
    ASSERT_TRUE(list2.front() == 1);
    list1.pop_front();
    ASSERT_TRUE(list1.front() == 2);
    ASSERT_TRUE(list2.front() == 1);
}

TEST(iterator_plusplus_star_begin_end_eq_noteq) {
    List<int> list;
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    list.push_back(6);
    List<int>::Iterator itr = list.begin();
    int expected[] = {3, 4, 5, 6};
    int i = 0;

    for(; itr != list.end(); ++itr) {
        ASSERT_TRUE(*itr == expected[i]);
        i++;
    }
}

TEST(iterator_minusminus) {
    List<int> list;
    list.push_back(7);
    list.push_back(8);
    list.push_back(9);
    List<int>::Iterator itr = list.begin();
    ++itr;
    ASSERT_TRUE(*itr == 8);
    --itr;
    ASSERT_TRUE(*itr == 7);
}

TEST(iterator_erase_front) {
    List<int> list;
    list.push_back(7);
    list.push_back(8);
    list.push_back(9);
    List<int>::Iterator itr = list.begin();
    ASSERT_TRUE(list.front() == 7);
    ASSERT_TRUE(list.size() == 3);
    list.erase(itr);
    ASSERT_TRUE(list.front() == 8);
    ASSERT_TRUE(list.size() == 2);
}

TEST(iterator_erase_middle) {
    List<int> list;
    list.push_back(7);
    list.push_back(8);
    list.push_back(9);
    List<int>::Iterator itr = list.begin();
    ++itr;
    ASSERT_TRUE(list.front() == 7);
    ASSERT_TRUE(list.size() == 3);
    list.erase(itr);
    ASSERT_TRUE(list.front() == 7);
    ASSERT_TRUE(list.size() == 2);
    list.pop_front();
    ASSERT_TRUE(list.front() == 9);
    ASSERT_TRUE(list.size() == 1);
}

TEST(iterator_erase_end) {
    List<int> list;
    list.push_back(7);
    list.push_back(8);
    list.push_back(9);
    List<int>::Iterator itr = list.begin();
    ++itr;
    ++itr;
    ASSERT_TRUE(list.front() == 7);
    ASSERT_TRUE(list.size() == 3);
    list.erase(itr);
    ASSERT_TRUE(list.front() == 7);
    ASSERT_TRUE(list.size() == 2);
    list.pop_back();
    ASSERT_TRUE(list.front() == 7);
    ASSERT_TRUE(list.size() == 1);
}

TEST(iterator_insert_front) {
    List<int> list;
    list.push_back(7);
    list.push_back(8);
    list.push_back(9);
    List<int>::Iterator itr = list.begin();
    ASSERT_TRUE(list.front() == 7);
    ASSERT_TRUE(list.size() == 3);
    list.insert(itr, 6);
    ASSERT_TRUE(list.front() == 6);
    ASSERT_TRUE(list.size() == 4);
}

TEST(iterator_insert_not_front) {
    List<int> list;
    list.push_back(7);
    list.push_back(9);
    list.push_back(10);
    List<int>::Iterator itr = list.begin();
    ++itr;
    ASSERT_TRUE(list.front() == 7);
    ASSERT_TRUE(list.size() == 3);
    list.insert(itr, 8);
    ASSERT_TRUE(list.front() == 7);
    ASSERT_TRUE(list.size() == 4);
    list.pop_front();
    ASSERT_TRUE(list.front() == 8);
    ASSERT_TRUE(list.size() == 3);
}

TEST_MAIN()
