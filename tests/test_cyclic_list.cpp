#include <gtest/gtest.h>
#include <iostream>
#include "cyclic_list.hpp"  // твой файл с CyclicList

// Проверка пустого списка
TEST(CyclicListTest, EmptyOnCreate) {
    CyclicList<int> list;
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0u);
}

// Проверка добавления элементов
TEST(CyclicListTest, PushBackIncreasesSize) {
    CyclicList<int> list;
    list.push_back(10);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 1u);
    list.push_back(20);
    EXPECT_EQ(list.size(), 2u);
}

// Проверка правильности итерации по элементам
TEST(CyclicListTest, IterateElements) {
    CyclicList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    int expected = 1;
    for (auto it = list.begin(); it != list.end(); ++it) {
        EXPECT_EQ(*it, expected);
        ++expected;
    }
}

// Проверка копирования
TEST(CyclicListTest, CopyConstructorWorks) {
    CyclicList<int> list1;
    list1.push_back(5);
    list1.push_back(10);

    CyclicList<int> list2 = list1;
    EXPECT_EQ(list1.size(), list2.size());

    auto it1 = list1.begin();
    auto it2 = list2.begin();
    while (it1 != list1.end() && it2 != list2.end()) {
        EXPECT_EQ(*it1, *it2);
        ++it1; ++it2;
    }
}

// Проверка оператора присваивания
TEST(CyclicListTest, AssignmentOperatorWorks) {
    CyclicList<int> list1;
    list1.push_back(7);
    list1.push_back(14);

    CyclicList<int> list2;
    list2 = list1;
    EXPECT_EQ(list1.size(), list2.size());

    auto it1 = list1.begin();
    auto it2 = list2.begin();
    while (it1 != list1.end() && it2 != list2.end()) {
        EXPECT_EQ(*it1, *it2);
        ++it1; ++it2;
    }
}

// Проверка оператора сравнения ==
TEST(CyclicListTest, EqualityOperator) {
    CyclicList<int> list1;
    CyclicList<int> list2;

    EXPECT_TRUE(list1 == list2);

    list1.push_back(1);
    list1.push_back(2);

    list2.push_back(1);
    list2.push_back(2);

    EXPECT_TRUE(list1 == list2);

    list2.push_back(3);
    EXPECT_FALSE(list1 == list2);
}

// Проверка очистки
TEST(CyclicListTest, ClearWorks) {
    CyclicList<int> list;
    list.push_back(1);
    list.push_back(2);

    list.clear();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0u);
}

// Проверка константных итераторов
TEST(CyclicListTest, ConstIterator) {
    CyclicList<int> list;
    list.push_back(10);
    list.push_back(20);

    const CyclicList<int>& const_list = list;
    int expected = 10;
    for (auto it = const_list.begin(); it != const_list.end(); ++it) {
        EXPECT_EQ(*it, expected);
        expected += 10;
    }
}

// Проверка операторов инкремента и декремента итератора
TEST(CyclicListTest, IteratorIncrementDecrement) {
    CyclicList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    auto it = list.begin();
    EXPECT_EQ(*it, 1);

    ++it;
    EXPECT_EQ(*it, 2);

    ++it;
    EXPECT_EQ(*it, 3);

    --it;
    EXPECT_EQ(*it, 2);
}
