#include "test.h"

#define OK 0
#define ERROR 1

START_TEST(from_int_to_decimal_test_1) {
  int int_1 = 0;
  int int_2 = 1;
  int int_3 = -1;
  int int_4 = 2147483647;
  int int_5 = -2147483648;

  s21_decimal result = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  s21_decimal value_1 = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};  //            0
  s21_decimal value_2 = {
      {0x00000001, 0x00000000, 0x00000000, 0x00000000}};  //            1
  s21_decimal value_3 = {
      {0x00000001, 0x00000000, 0x00000000, 0x80000000}};  //           -1
  s21_decimal value_4 = {
      {0x7FFFFFFF, 0x00000000, 0x00000000, 0x00000000}};  //   2147483647
  s21_decimal value_5 = {
      {0x80000000, 0x00000000, 0x00000000, 0x80000000}};  //  -2147483648

  ck_assert_int_eq(OK, s21_from_int_to_decimal(int_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_1.bits[i], result.bits[i]);
  }
  ck_assert_int_eq(OK, s21_from_int_to_decimal(int_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_2.bits[i], result.bits[i]);
  }
  ck_assert_int_eq(OK, s21_from_int_to_decimal(int_3, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_3.bits[i], result.bits[i]);
  }
  ck_assert_int_eq(OK, s21_from_int_to_decimal(int_4, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_4.bits[i], result.bits[i]);
  }
  ck_assert_int_eq(OK, s21_from_int_to_decimal(int_5, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_5.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(from_int_to_decimal_test_2) {
  int int_1 = 423;
  int int_2 = 68900;
  int int_3 = 8936874;
  int int_4 = 2121453612;

  s21_decimal result = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  s21_decimal value_1 = {
      {0x000001A7, 0x00000000, 0x00000000, 0x00000000}};  //         423
  s21_decimal value_2 = {
      {0x00010D24, 0x00000000, 0x00000000, 0x00000000}};  //       68900
  s21_decimal value_3 = {
      {0x00885DAA, 0x00000000, 0x00000000, 0x00000000}};  //     8936874
  s21_decimal value_4 = {
      {0x7E72D02C, 0x00000000, 0x00000000, 0x00000000}};  //  2121453612

  ck_assert_int_eq(OK, s21_from_int_to_decimal(int_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_1.bits[i], result.bits[i]);
  }
  ck_assert_int_eq(OK, s21_from_int_to_decimal(int_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_2.bits[i], result.bits[i]);
  }
  ck_assert_int_eq(OK, s21_from_int_to_decimal(int_3, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_3.bits[i], result.bits[i]);
  }
  ck_assert_int_eq(OK, s21_from_int_to_decimal(int_4, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_4.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(from_int_to_decimal_test_3) {
  int int_1 = -687;
  int int_2 = -74209;
  int int_3 = -8936874;
  int int_4 = -2111436613;

  s21_decimal result = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  s21_decimal value_1 = {
      {0x000002AF, 0x00000000, 0x00000000, 0x80000000}};  //         -687
  s21_decimal value_2 = {
      {0x000121E1, 0x00000000, 0x00000000, 0x80000000}};  //       -74209
  s21_decimal value_3 = {
      {0x00885DAA, 0x00000000, 0x00000000, 0x80000000}};  //     -8936874
  s21_decimal value_4 = {
      {0x7DD9F745, 0x00000000, 0x00000000, 0x80000000}};  //  -2111436613

  ck_assert_int_eq(OK, s21_from_int_to_decimal(int_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_1.bits[i], result.bits[i]);
  }
  ck_assert_int_eq(OK, s21_from_int_to_decimal(int_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_2.bits[i], result.bits[i]);
  }
  ck_assert_int_eq(OK, s21_from_int_to_decimal(int_3, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_3.bits[i], result.bits[i]);
  }
  ck_assert_int_eq(OK, s21_from_int_to_decimal(int_4, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_4.bits[i], result.bits[i]);
  }
}
END_TEST

Suite* s21_from_int_to_decimal_suite(void) {
  Suite* s;
  s = suite_create("\033[33ms21_from_int_to_decimal\033[0m");

  TCase* tc_core;
  tc_core = tcase_create("s21_from_int_to_decimal_core");
  tcase_add_test(tc_core, from_int_to_decimal_test_1);
  tcase_add_test(tc_core, from_int_to_decimal_test_2);
  tcase_add_test(tc_core, from_int_to_decimal_test_3);
  suite_add_tcase(s, tc_core);

  return s;
}
