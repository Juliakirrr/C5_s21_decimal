#include "test.h"

#define TRUE 1
#define FALSE 0

START_TEST(is_greater_test_1) {
  s21_decimal value_1 = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};  //        0
  s21_decimal value_2 = {
      {0x00000000, 0x00000000, 0x00000000, 0x80000000}};  //       -0
  s21_decimal value_3 = {
      {0x00000000, 0x00000000, 0x00000000, 0x00050000}};  //  0.00000

  ck_assert_int_eq(FALSE, s21_is_greater(value_1, value_1));
  ck_assert_int_eq(FALSE, s21_is_greater(value_2, value_2));
  ck_assert_int_eq(FALSE, s21_is_greater(value_3, value_3));

  ck_assert_int_eq(FALSE, s21_is_greater(value_1, value_2));
  ck_assert_int_eq(FALSE, s21_is_greater(value_2, value_1));
  ck_assert_int_eq(FALSE, s21_is_greater(value_1, value_3));
  ck_assert_int_eq(FALSE, s21_is_greater(value_2, value_3));
}
END_TEST

START_TEST(is_greater_test_2) {
  s21_decimal value_1 = {
      {0x00000001, 0x00000000, 0x00000000, 0x00000000}};  //  1
  s21_decimal value_2 = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};  //  0
  s21_decimal value_3 = {
      {0x00000001, 0x00000000, 0x00000000, 0x80000000}};  // -1

  ck_assert_int_eq(TRUE, s21_is_greater(value_1, value_2));
  ck_assert_int_eq(TRUE, s21_is_greater(value_1, value_3));
  ck_assert_int_eq(TRUE, s21_is_greater(value_2, value_3));

  ck_assert_int_eq(FALSE, s21_is_greater(value_1, value_1));
  ck_assert_int_eq(FALSE, s21_is_greater(value_2, value_2));
  ck_assert_int_eq(FALSE, s21_is_greater(value_3, value_3));

  ck_assert_int_eq(FALSE, s21_is_greater(value_2, value_1));
  ck_assert_int_eq(FALSE, s21_is_greater(value_3, value_1));
  ck_assert_int_eq(FALSE, s21_is_greater(value_3, value_2));
}
END_TEST

START_TEST(is_greater_test_3) {
  s21_decimal value_1 = {{0x00000000, 0x00000000, 0x00000100,
                          0x00000000}};  //   4.7223664828696e+21
  s21_decimal value_2 = {{0x00000000, 0x00000100, 0x00000000,
                          0x00000000}};  //         1099511627776
  s21_decimal value_3 = {{0x00000100, 0x00000000, 0x00000000,
                          0x00000000}};  //                   256
  s21_decimal value_4 = {{0x00000000, 0x00000000, 0x00000000,
                          0x00000000}};  //                     0
  s21_decimal value_5 = {{0x00000100, 0x00000000, 0x00000000,
                          0x80000000}};  //                  -256
  s21_decimal value_6 = {{0x00000000, 0x00000100, 0x00000000,
                          0x80000000}};  //        -1099511627776
  s21_decimal value_7 = {{0x00000000, 0x00000000, 0x00000100,
                          0x80000000}};  //  -4.7223664828696e+21

  ck_assert_int_eq(TRUE, s21_is_greater(value_1, value_2));
  ck_assert_int_eq(TRUE, s21_is_greater(value_1, value_3));
  ck_assert_int_eq(TRUE, s21_is_greater(value_1, value_4));
  ck_assert_int_eq(TRUE, s21_is_greater(value_1, value_5));
  ck_assert_int_eq(TRUE, s21_is_greater(value_1, value_6));
  ck_assert_int_eq(TRUE, s21_is_greater(value_1, value_7));

  ck_assert_int_eq(TRUE, s21_is_greater(value_2, value_3));
  ck_assert_int_eq(TRUE, s21_is_greater(value_2, value_4));
  ck_assert_int_eq(TRUE, s21_is_greater(value_2, value_5));
  ck_assert_int_eq(TRUE, s21_is_greater(value_2, value_6));
  ck_assert_int_eq(TRUE, s21_is_greater(value_2, value_7));

  ck_assert_int_eq(TRUE, s21_is_greater(value_3, value_4));
  ck_assert_int_eq(TRUE, s21_is_greater(value_3, value_5));
  ck_assert_int_eq(TRUE, s21_is_greater(value_3, value_6));
  ck_assert_int_eq(TRUE, s21_is_greater(value_3, value_7));

  ck_assert_int_eq(TRUE, s21_is_greater(value_4, value_5));
  ck_assert_int_eq(TRUE, s21_is_greater(value_4, value_6));
  ck_assert_int_eq(TRUE, s21_is_greater(value_4, value_7));

  ck_assert_int_eq(TRUE, s21_is_greater(value_5, value_6));
  ck_assert_int_eq(TRUE, s21_is_greater(value_5, value_7));

  ck_assert_int_eq(TRUE, s21_is_greater(value_6, value_7));
}
END_TEST

START_TEST(is_greater_test_4) {
  s21_decimal value_1 = {{0x00000000, 0x00000000, 0x00000100,
                          0x00000000}};  //   4.7223664828696e+21
  s21_decimal value_2 = {{0x00000000, 0x00000100, 0x00000000,
                          0x00000000}};  //         1099511627776
  s21_decimal value_3 = {{0x00000100, 0x00000000, 0x00000000,
                          0x00000000}};  //                   256
  s21_decimal value_4 = {{0x00000000, 0x00000000, 0x00000000,
                          0x00000000}};  //                     0
  s21_decimal value_5 = {{0x00000100, 0x00000000, 0x00000000,
                          0x80000000}};  //                  -256
  s21_decimal value_6 = {{0x00000000, 0x00000100, 0x00000000,
                          0x80000000}};  //        -1099511627776
  s21_decimal value_7 = {{0x00000000, 0x00000000, 0x00000100,
                          0x80000000}};  //  -4.7223664828696e+21

  ck_assert_int_eq(FALSE, s21_is_greater(value_7, value_1));
  ck_assert_int_eq(FALSE, s21_is_greater(value_7, value_2));
  ck_assert_int_eq(FALSE, s21_is_greater(value_7, value_3));
  ck_assert_int_eq(FALSE, s21_is_greater(value_7, value_4));
  ck_assert_int_eq(FALSE, s21_is_greater(value_7, value_5));
  ck_assert_int_eq(FALSE, s21_is_greater(value_7, value_6));
  ck_assert_int_eq(FALSE, s21_is_greater(value_7, value_7));

  ck_assert_int_eq(FALSE, s21_is_greater(value_6, value_1));
  ck_assert_int_eq(FALSE, s21_is_greater(value_6, value_2));
  ck_assert_int_eq(FALSE, s21_is_greater(value_6, value_3));
  ck_assert_int_eq(FALSE, s21_is_greater(value_6, value_4));
  ck_assert_int_eq(FALSE, s21_is_greater(value_6, value_5));
  ck_assert_int_eq(FALSE, s21_is_greater(value_6, value_6));

  ck_assert_int_eq(FALSE, s21_is_greater(value_5, value_1));
  ck_assert_int_eq(FALSE, s21_is_greater(value_5, value_2));
  ck_assert_int_eq(FALSE, s21_is_greater(value_5, value_3));
  ck_assert_int_eq(FALSE, s21_is_greater(value_5, value_4));
  ck_assert_int_eq(FALSE, s21_is_greater(value_5, value_5));

  ck_assert_int_eq(FALSE, s21_is_greater(value_4, value_1));
  ck_assert_int_eq(FALSE, s21_is_greater(value_4, value_2));
  ck_assert_int_eq(FALSE, s21_is_greater(value_4, value_3));
  ck_assert_int_eq(FALSE, s21_is_greater(value_4, value_4));

  ck_assert_int_eq(FALSE, s21_is_greater(value_3, value_1));
  ck_assert_int_eq(FALSE, s21_is_greater(value_3, value_2));
  ck_assert_int_eq(FALSE, s21_is_greater(value_3, value_3));

  ck_assert_int_eq(FALSE, s21_is_greater(value_2, value_1));
  ck_assert_int_eq(FALSE, s21_is_greater(value_2, value_2));

  ck_assert_int_eq(FALSE, s21_is_greater(value_1, value_1));
}
END_TEST

START_TEST(is_greater_test_5) {
  s21_decimal value_1 = {{0x910AF4CA, 0xC045D5F2, 0x27E41B00,
                          0x00150000}};  //    12345677.987654345678987654346
  s21_decimal value_2 = {{0x11CDD185, 0xF5BC6FC0, 0x02D50F3F,
                          0x00100000}};  // 87654323456.9876545678987653

  ck_assert_int_eq(FALSE, s21_is_greater(value_1, value_2));
  ck_assert_int_eq(TRUE, s21_is_greater(value_2, value_1));

  s21_decimal value_3 = {{0x910AF4CA, 0xC045D5F2, 0x27E41B00,
                          0x80150000}};  //    -12345677.987654345678987654346
  s21_decimal value_4 = {{0x11CDD185, 0xF5BC6FC0, 0x02D50F3F,
                          0x80100000}};  // -87654323456.9876545678987653

  ck_assert_int_eq(FALSE, s21_is_greater(value_4, value_3));
  ck_assert_int_eq(TRUE, s21_is_greater(value_3, value_4));

  ck_assert_int_eq(TRUE, s21_is_greater(value_1, value_3));
  ck_assert_int_eq(TRUE, s21_is_greater(value_1, value_4));
  ck_assert_int_eq(TRUE, s21_is_greater(value_2, value_3));
  ck_assert_int_eq(TRUE, s21_is_greater(value_2, value_4));

  ck_assert_int_eq(FALSE, s21_is_greater(value_3, value_1));
  ck_assert_int_eq(FALSE, s21_is_greater(value_3, value_2));
  ck_assert_int_eq(FALSE, s21_is_greater(value_4, value_1));
  ck_assert_int_eq(FALSE, s21_is_greater(value_4, value_2));
}
END_TEST

START_TEST(is_greater_test_6) {
  s21_decimal value_1 = {{0xE40E02A1, 0x2CDB84DA, 0x00000000,
                          0x00150000}};  //   0.003232323233232323233
  s21_decimal value_2 = {{0xAFB3304F, 0xEFE479B9, 0x001C9336,
                          0x001C0000}};  //   0.0034545124232446543232446543
  s21_decimal value_3 = {{0xE40E02A1, 0x2CDB84DA, 0x00000000,
                          0x80150000}};  //  -0.003232323233232323233
  s21_decimal value_4 = {{0xAFB3304F, 0xEFE479B9, 0x001C9336,
                          0x801C0000}};  //  -0.0034545124232446543232446543

  ck_assert_int_eq(TRUE, s21_is_greater(value_2, value_1));
  ck_assert_int_eq(TRUE, s21_is_greater(value_2, value_3));
  ck_assert_int_eq(TRUE, s21_is_greater(value_2, value_4));

  ck_assert_int_eq(TRUE, s21_is_greater(value_1, value_3));
  ck_assert_int_eq(TRUE, s21_is_greater(value_1, value_4));

  ck_assert_int_eq(TRUE, s21_is_greater(value_3, value_4));
}
END_TEST

START_TEST(is_greater_test_7) {
  s21_decimal value_1 = {{0xE40E02A1, 0x2CDB84DA, 0x00000000,
                          0x00150000}};  //   0.003232323233232323233
  s21_decimal value_2 = {{0xAFB3304F, 0xEFE479B9, 0x001C9336,
                          0x001C0000}};  //   0.0034545124232446543232446543
  s21_decimal value_3 = {{0xE40E02A1, 0x2CDB84DA, 0x00000000,
                          0x80150000}};  //  -0.003232323233232323233
  s21_decimal value_4 = {{0xAFB3304F, 0xEFE479B9, 0x001C9336,
                          0x801C0000}};  //  -0.0034545124232446543232446543

  ck_assert_int_eq(FALSE, s21_is_greater(value_4, value_3));
  ck_assert_int_eq(FALSE, s21_is_greater(value_4, value_2));
  ck_assert_int_eq(FALSE, s21_is_greater(value_4, value_1));

  ck_assert_int_eq(FALSE, s21_is_greater(value_3, value_2));
  ck_assert_int_eq(FALSE, s21_is_greater(value_3, value_1));

  ck_assert_int_eq(FALSE, s21_is_greater(value_1, value_2));
}
END_TEST

Suite* s21_is_greater_suite(void) {
  Suite* s;
  s = suite_create("\033[33ms21_is_greater\033[0m");

  TCase* tc_core;
  tc_core = tcase_create("s21_is_greater_core");
  tcase_add_test(tc_core, is_greater_test_1);
  tcase_add_test(tc_core, is_greater_test_2);
  tcase_add_test(tc_core, is_greater_test_3);
  tcase_add_test(tc_core, is_greater_test_4);
  tcase_add_test(tc_core, is_greater_test_5);
  tcase_add_test(tc_core, is_greater_test_6);
  tcase_add_test(tc_core, is_greater_test_7);

  suite_add_tcase(s, tc_core);

  return s;
}
