#include "list.h"
#include "polinom.h"
#include <gtest.h>

TEST(Node, can_create) {

	ASSERT_NO_THROW(Node<int>());
}

TEST(Node, can_initialize_data) {
	Node<char> A('b', nullptr);
	EXPECT_EQ(A.data, 'b');
}

TEST(Node, can_initialize_next) {
	Node<char>* A = new Node<char>();
	Node<char> B('b', A);

	EXPECT_EQ(B.next, A);

}


TEST(List, can_create) {

	ASSERT_NO_THROW(List<int>());
}

TEST(List, can_idenify_empty) {
	List<int> A;
	EXPECT_TRUE(A.IsEmpty());
}

TEST(List, can_icopy) {
	List<int> A;
	A.Push(1);
	A.Push(2);
	List<int> B(A);

	EXPECT_EQ(B.HeadOut()->next->next->data, 2);
}

TEST(List, can_idenify_non_empty) {
	List<int> A;
	A.Push(1);
	EXPECT_FALSE(A.IsEmpty());
}

TEST(List, can_push) {
	List<int> A;
	A.Push(1);
	A.Push(2);
	A.Push(3);

	EXPECT_EQ(A.HeadOut()->next->next->data, 2);

}

TEST(List, can_delete) {
	List<int> A;
	A.Push(1);
	A.Push(2);
	A.Push(3);
	A.Delete(A.HeadOut()->next->next);
	EXPECT_EQ(A.HeadOut()->next->next->data, 3);
}

TEST(List, can_delete_one_elem) {
	List<int> A;
	A.Push(1);
	A.Delete(A.HeadOut()->next);
	EXPECT_EQ(A.HeadOut()->next, nullptr);
}

TEST(List, cannot_delete_non_existent_elem) {
	List<int> A;
	A.Push(1);
	A.Push(2);
	A.Push(3);
	Node<int>* NA = new Node<int>;
	ASSERT_ANY_THROW(A.Delete(NA));
}

TEST(List, can_sort_int) {
	List<int> A;
	A.Push(1);
	A.Push(2);
	A.Push(3);
	A.Sort();
	EXPECT_EQ(A.HeadOut()->next->next->next->data, 1);
}

TEST(List, can_sort_Monom) {
	List<Monom> A;
	Monom MA(2, 101);
	Monom MB(3, 301);
	Monom MC(4, 201);
	A.Push(MA);
	A.Push(MB);
	A.Push(MC);
	A.Sort();
	EXPECT_EQ(A.HeadOut()->next->next->next->data.deg, 101);
}

