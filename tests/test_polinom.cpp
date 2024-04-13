#include "polinom.h"
#include <gtest.h>

TEST(Monom, can_create) {

	ASSERT_NO_THROW(Monom());
}

TEST(Monom, can_initialize_k) {
	Monom A(2.4, 104);

	EXPECT_EQ(A.k, 2.4);
}

TEST(Monom, can_initialize_deg) {
	Monom A(2.4, 104);

	EXPECT_EQ(A.deg, 104);
}

TEST(Monom, throw_when_deg_out_of_range_more) {

	ASSERT_ANY_THROW(Monom(2.4, 1111));
}

TEST(Monom, throw_when_deg_out_of_range_less) {

	ASSERT_ANY_THROW(Monom(2.4, -111));
}

TEST(Monom, can_eq) {
	Monom A(2.4, 104);
	Monom B(5, 206);
	A = B;

	EXPECT_EQ(A.k, 5);
}

TEST(Monom, can_compare_more) {
	Monom A(2.4, 104);
	Monom B(5, 206);

	EXPECT_EQ(B > A, true);
}

TEST(Monom, can_compare_less) {
	Monom A(2.4, 104);
	Monom B(5, 206);

	EXPECT_EQ(A < B, true);
}



TEST(Polinom, can_create) {

	ASSERT_NO_THROW(Polinom());
}

TEST(Polinom, can_copy) {
	Polinom A;
	Monom MA(2, 101);
	Monom MB(3, 101);
	Monom MC(10, 102);
	A.Push(MA);
	A.Push(MB);
	A.Push(MC);
	Polinom B(A);

	EXPECT_EQ(B.PoliOut().HeadOut()->next->next->data.deg, 101);
}

TEST(Polinom, can_push_right_k) {
	Polinom A;
	Monom MA(2, 101);
	A.Push(MA);
	EXPECT_EQ(A.PoliOut().HeadOut()->next->data.k, 2);
}

TEST(Polinom, can_push_right_deg) {
	Polinom A;
	Monom MA(2, 101);
	A.Push(MA);
	EXPECT_EQ(A.PoliOut().HeadOut()->next->data.deg, 101);
}

TEST(Polinom, can_delete_zero_Monoms) {
	Polinom A;
	Monom MA(2, 101);
	Monom MB(0, 102);
	Monom MC(10, 103);
	A.Push(MA);
	A.Push(MB);
	A.Push(MC);
	EXPECT_EQ(A.PoliOut().HeadOut()->next->next->data.deg, 101);
}

TEST(Polinom, can_search_similar_one_pair_two_elem) {
	Polinom A;
	Monom MA(2, 101);
	Monom MB(3, 101);
	A.Push(MA);
	A.Push(MB);
	EXPECT_EQ(A.PoliOut().HeadOut()->next->data.k, 5);
}

TEST(Polinom, can_search_similar_one_pair_three_elem) {
	Polinom A;
	Monom MA(2, 101);
	Monom MB(3, 101);
	Monom MC(10, 102);
	A.Push(MA);
	A.Push(MB);
	A.Push(MC);
	EXPECT_EQ(A.PoliOut().HeadOut()->next->next->data.k, 5);
}

TEST(Polinom, can_search_similar_two_pair_5_elem) {
	Polinom A;
	Monom MA(2, 101);
	Monom MB(3, 101);
	Monom MC(10, 102);
	Monom MD(4, 103);
	Monom ME(11, 102);
	A.Push(MA);
	A.Push(MB);
	A.Push(MC);
	A.Push(MD);
	A.Push(ME);
	EXPECT_EQ(A.PoliOut().HeadOut()->next->next->data.k, 21);
}

TEST(Polinom, can_search_similar_one_trio_5_elem) {
	Polinom A;
	Monom MA(2, 101);
	Monom MB(3, 101);
	Monom MC(10, 102);
	Monom MD(4, 101);
	Monom ME(11, 102);
	A.Push(MA);
	A.Push(MB);
	A.Push(MC);
	A.Push(MD);
	A.Push(ME);
	EXPECT_EQ(A.PoliOut().HeadOut()->next->next->data.k, 9);
}

TEST(Polinom, can_sort_two_elem) {
	Polinom A;
	Monom MA(2, 101);
	Monom MB(3, 201);
	A.Push(MA);
	A.Push(MB);
	A.PoliOut().Sort();
	EXPECT_EQ(A.PoliOut().HeadOut()->next->next->data.deg, 101);
}

TEST(Polinom, can_sort_three_elem) {
	Polinom A;
	Monom MA(2, 101);
	Monom MB(3, 201);
	Monom MC(4, 301);
	A.Push(MA);
	A.Push(MB);
	A.Push(MC);
	A.PoliOut().Sort();
	EXPECT_EQ(A.PoliOut().HeadOut()->next->data.deg, 301);
}

TEST(Polinom, can_sort_four_elem) {
	Polinom A;
	Monom MA(2, 101);
	Monom MB(3, 301);
	Monom MC(4, 201);
	Monom MD(5, 601);
	A.Push(MA);
	A.Push(MB);
	A.Push(MC);
	A.Push(MD);
	A.PoliOut().Sort();
	EXPECT_EQ(A.PoliOut().HeadOut()->next->data.deg, 601);
}

TEST(Polinom, can_sum_eq_poli) {
	Polinom A, B;
	Monom MA(2, 101);
	Monom MB(3, 301);
	Monom MC(4, 201);
	Monom MD(5, 102);
	A.Push(MA);
	A.Push(MB);
	B.Push(MC);
	B.Push(MD);
	A += B;
	EXPECT_EQ(A.PoliOut().HeadOut()->next->next->next->data.k, 5);
}

TEST(Polinom, can_eq_poli) {
	Polinom A, B;
	Monom MA(2, 101);
	Monom MB(3, 301);
	Monom MC(4, 201);
	Monom MD(5, 102);
	A.Push(MA);
	A.Push(MB);
	B.Push(MC);
	B.Push(MD);
	A = B;
	EXPECT_EQ(A.PoliOut().HeadOut()->next->data.k, 4);
}

TEST(Polinom, can_sum_poli) {
	Polinom A, B, C;
	Monom MA(2, 101);
	Monom MB(3, 301);
	Monom MC(4, 201);
	Monom MD(5, 101);
	A.Push(MA);
	A.Push(MB);
	B.Push(MC);
	B.Push(MD);
	C = A + B;
	EXPECT_EQ(C.PoliOut().HeadOut()->next->next->next->data.k, 7);
}

TEST(Polinom, can_mul_k) {
	Polinom A;
	Monom MA(2, 101);
	Monom MB(3, 301);
	Monom MC(4, 201);
	Monom MD(5, 101);
	A.Push(MA);
	A.Push(MB);
	A.Push(MC);
	A.Push(MD);
	A = A * 2.5;
	EXPECT_EQ(A.PoliOut().HeadOut()->next->next->next->data.k, 17.5);
}

TEST(Polinom, can_mul_0) {
	Polinom A;
	Monom MA(2, 101);
	Monom MB(3, 301);
	Monom MC(4, 201);
	Monom MD(5, 101);
	A.Push(MA);
	A.Push(MB);
	A.Push(MC);
	A.Push(MD);
	A = A * 0.0;
	EXPECT_EQ(A.PoliOut().HeadOut()->next, nullptr);
}

TEST(Polinom, can_sub_poli) {
	Polinom A, B, C;
	Monom MA(2, 101);
	Monom MB(3, 301);
	Monom MC(4, 201);
	Monom MD(5, 101);
	A.Push(MA);
	A.Push(MB);
	B.Push(MC);
	B.Push(MD);
	C = A - B;
	EXPECT_EQ(C.PoliOut().HeadOut()->next->next->next->data.k, -3);
}

TEST(Polinom, can_mul_check_k) {
	Polinom A, B, C;
	Monom MA(2, 101);
	Monom MB(3, 301);
	Monom MC(4, 201);
	Monom MD(5, 101);
	A.Push(MA);
	A.Push(MB);
	B.Push(MC);
	B.Push(MD);
	C = A * B;
	EXPECT_EQ(C.PoliOut().HeadOut()->next->next->next->data.k, 8);
}

TEST(Polinom, can_mul_check_deg) {
	Polinom A, B, C;
	Monom MA(2, 101);
	Monom MB(3, 301);
	Monom MC(4, 201);
	Monom MD(5, 101);
	A.Push(MA);
	A.Push(MB);
	B.Push(MC);
	B.Push(MD);
	C = A * B;
	EXPECT_EQ(C.PoliOut().HeadOut()->next->next->next->data.deg, 302);
}