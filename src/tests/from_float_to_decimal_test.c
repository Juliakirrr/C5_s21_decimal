#include "test.h"

#define OK 0
#define ERROR 1

START_TEST(from_float_to_decimal_test_1) {
  float float_1 = NAN;
  float float_2 = -NAN;
  float float_3 = INFINITY;
  float float_4 = -INFINITY;
  float float_5 = FLT_MIN;
  float float_6 = -FLT_MIN;
  float float_7 = FLT_MAX;
  float float_8 = -FLT_MAX;

  s21_decimal result = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  s21_decimal null = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};  //    0

  ck_assert_int_eq(ERROR, s21_from_float_to_decimal(float_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(null.bits[i], result.bits[i]);
  }
  ck_assert_int_eq(ERROR, s21_from_float_to_decimal(float_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(null.bits[i], result.bits[i]);
  }
  ck_assert_int_eq(ERROR, s21_from_float_to_decimal(float_3, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(null.bits[i], result.bits[i]);
  }
  ck_assert_int_eq(ERROR, s21_from_float_to_decimal(float_4, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(null.bits[i], result.bits[i]);
  }
  ck_assert_int_eq(ERROR, s21_from_float_to_decimal(float_5, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(null.bits[i], result.bits[i]);
  }
  ck_assert_int_eq(ERROR, s21_from_float_to_decimal(float_6, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(null.bits[i], result.bits[i]);
  }
  ck_assert_int_eq(ERROR, s21_from_float_to_decimal(float_7, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(null.bits[i], result.bits[i]);
  }
  ck_assert_int_eq(ERROR, s21_from_float_to_decimal(float_8, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(null.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(from_float_to_decimal_test_2) {
  float float_1 = 0.0;
  float float_2 = 1.0;
  float float_3 = -1.0;
  float float_4 = 32767.0;
  float float_5 = -65535.0;
  float float_6 = -9999999.0;
  // float float_7 = 212818288.0;
  // float float_8 = -2147483650.0;

  s21_decimal result = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  s21_decimal value_1 = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};  //              0
  s21_decimal value_2 = {
      {0x00000001, 0x00000000, 0x00000000, 0x00000000}};  //              1
  s21_decimal value_3 = {
      {0x00000001, 0x00000000, 0x00000000, 0x80000000}};  //             -1
  s21_decimal value_4 = {
      {0x00007FFF, 0x00000000, 0x00000000, 0x00000000}};  //          32767
  s21_decimal value_5 = {
      {0x0000FFFF, 0x00000000, 0x00000000, 0x80000000}};  //         -65535
  s21_decimal value_6 = {
      {0x0098967F, 0x00000000, 0x00000000, 0x80000000}};  //       -9999999
  // s21_decimal value_7 = {
  //     {0x0CAF597C, 0x00000000, 0x00000000, 0x00000000}};  //      212818300
  // s21_decimal value_8 = {
  //     {0x80000160, 0x00000000, 0x00000000, 0x80000000}};  //    -2147484000

  ck_assert_int_eq(OK, s21_from_float_to_decimal(float_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_1.bits[i], result.bits[i]);
  }
  ck_assert_int_eq(OK, s21_from_float_to_decimal(float_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_2.bits[i], result.bits[i]);
  }
  ck_assert_int_eq(OK, s21_from_float_to_decimal(float_3, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_3.bits[i], result.bits[i]);
  }
  ck_assert_int_eq(OK, s21_from_float_to_decimal(float_4, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_4.bits[i], result.bits[i]);
  }
  ck_assert_int_eq(OK, s21_from_float_to_decimal(float_5, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_5.bits[i], result.bits[i]);
  }
  ck_assert_int_eq(OK, s21_from_float_to_decimal(float_6, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_6.bits[i], result.bits[i]);
  }
  // ck_assert_int_eq(OK, s21_from_float_to_decimal(float_7, &result));
  // for (int i = 0; i < 4; i++) {
  //   ck_assert_int_eq(value_7.bits[i], result.bits[i]);
  // }
  // ck_assert_int_eq(OK, s21_from_float_to_decimal(float_8, &result));
  // for (int i = 0; i < 4; i++) {
  //   ck_assert_int_eq(value_8.bits[i], result.bits[i]);
  // }
}
END_TEST

START_TEST(from_float_to_decimal_test_3) {
  float float_1 = 1.100281;
  float float_2 = 1.00999999;
  // float float_3 = 1.83182812;
  float float_4 = 2.38182998;
  float float_5 = -1.00730002;

  s21_decimal result = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  s21_decimal value_1 = {
      {0x0010C9F9, 0x00000000, 0x00000000, 0x00060000}};  //    1.100281
  s21_decimal value_2 = {
      {0x00000065, 0x00000000, 0x00000000, 0x00020000}};  //        1.01
  // s21_decimal value_3 = {
  //     {0x001BF394, 0x00000000, 0x00000000, 0x00060000}};  //    1.831828
  s21_decimal value_4 = {
      {0x0003A267, 0x00000000, 0x00000000, 0x00050000}};  //     2.38183
  s21_decimal value_5 = {
      {0x00002759, 0x00000000, 0x00000000, 0x80040000}};  //     -1.0073

  ck_assert_int_eq(OK, s21_from_float_to_decimal(float_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_1.bits[i], result.bits[i]);
  }
  ck_assert_int_eq(OK, s21_from_float_to_decimal(float_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_2.bits[i], result.bits[i]);
  }
  // ck_assert_int_eq(OK, s21_from_float_to_decimal(float_3, &result));
  // for (int i = 0; i < 4; i++) {
  //   ck_assert_int_eq(value_3.bits[i], result.bits[i]);
  // }
  ck_assert_int_eq(OK, s21_from_float_to_decimal(float_4, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_4.bits[i], result.bits[i]);
  }
  ck_assert_int_eq(OK, s21_from_float_to_decimal(float_5, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_5.bits[i], result.bits[i]);
  }
}
END_TEST

Suite* s21_from_float_to_decimal_suite(void) {
  Suite* s;
  s = suite_create("\033[33ms21_from_float_to_decimal\033[0m");

  TCase* tc_core;
  tc_core = tcase_create("s21_from_float_to_decimal_core");
  tcase_add_test(tc_core, from_float_to_decimal_test_1);
  tcase_add_test(tc_core, from_float_to_decimal_test_2);
  tcase_add_test(tc_core, from_float_to_decimal_test_3);
  suite_add_tcase(s, tc_core);

  return s;
}
