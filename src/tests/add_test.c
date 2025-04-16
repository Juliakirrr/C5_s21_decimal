#include "test.h"

#define OK 0
#define BIG 1
#define SMALL 2

START_TEST(add_test_1) {
  s21_decimal plus_one = {
      {0x00000001, 0x00000000, 0x00000000, 0x00000000}};  //       1
  s21_decimal minus_one = {
      {0x00000001, 0x00000000, 0x00000000, 0x80000000}};  //      -1
  s21_decimal plus_null = {
      {0x00000000, 0x00000000, 0x00000000, 0x00000000}};  //       0
  s21_decimal minus_null = {
      {0x00000000, 0x00000000, 0x00000000, 0x80000000}};  //      -0
  s21_decimal result = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  // 0 + 1 = 1
  ck_assert_int_eq(OK, s21_add(plus_null, plus_one, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(plus_one.bits[i], result.bits[i]);
  }
  // 1 + 0 = 1
  ck_assert_int_eq(OK, s21_add(plus_one, plus_null, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(plus_one.bits[i], result.bits[i]);
  }
  // 0 + (-1) = (-1)
  ck_assert_int_eq(OK, s21_add(plus_null, minus_one, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(minus_one.bits[i], result.bits[i]);
  }
  // (-1) + 0 = (-1)
  ck_assert_int_eq(OK, s21_add(minus_one, plus_null, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(minus_one.bits[i], result.bits[i]);
  }
  // 0 + 0 = 0
  ck_assert_int_eq(OK, s21_add(plus_null, plus_null, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(plus_null.bits[i], result.bits[i]);
  }
  // 0 + (-0) = 0
  ck_assert_int_eq(OK, s21_add(plus_null, minus_null, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(plus_null.bits[i], result.bits[i]);
  }
  // (-0) + 0 = 0
  ck_assert_int_eq(OK, s21_add(minus_null, plus_null, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(plus_null.bits[i], result.bits[i]);
  }
  // (-0) + (-0) = 0
  ck_assert_int_eq(OK, s21_add(minus_null, minus_null, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(plus_null.bits[i], result.bits[i]);
  }
  // (-0) + 1 = 1
  ck_assert_int_eq(OK, s21_add(minus_null, plus_one, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(plus_one.bits[i], result.bits[i]);
  }
  // 1 + (-0) = 1
  ck_assert_int_eq(OK, s21_add(plus_one, minus_null, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(plus_one.bits[i], result.bits[i]);
  }
  // (-0) + (-1) = (-1)
  ck_assert_int_eq(OK, s21_add(minus_null, minus_one, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(minus_one.bits[i], result.bits[i]);
  }
  // (-1) + (-0) = (-1)
  ck_assert_int_eq(OK, s21_add(minus_one, minus_null, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(minus_one.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(add_test_2) {
  s21_decimal value_1 = {{0x89E7FFFF, 0x00000000, 0x00000000,
                          0x00000000}};  //                2313682943
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0x00000000,
                          0x00000000}};  //      18446744073709551615
  s21_decimal value_3 = {{0xFFFFFFFF, 0x05D19D1B, 0x00012189,
                          0x00000000}};  // 1367291536776409582141439

  s21_decimal result = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  s21_decimal answer_1 = {{0x13CFFFFE, 0x00000001, 0x00000000,
                           0x00000000}};  //                4627365886
  s21_decimal answer_2 = {{0x89E7FFFE, 0x00000000, 0x00000001,
                           0x00000000}};  //      18446744076023234558
  s21_decimal answer_3 = {{0x89E7FFFE, 0x05D19D1C, 0x00012189,
                           0x00000000}};  // 1367291536776411895824382
  s21_decimal answer_4 = {{0xFFFFFFFE, 0xFFFFFFFF, 0x00000001,
                           0x00000000}};  //      36893488147419103230
  s21_decimal answer_5 = {{0xFFFFFFFE, 0x05D19D1B, 0x0001218A,
                           0x00000000}};  // 1367309983520483291693054
  s21_decimal answer_6 = {{0xFFFFFFFE, 0x0BA33A37, 0x00024312,
                           0x00000000}};  // 2734583073552819164282878

  // 2313682943 + 2313682943 = 4627365886
  ck_assert_int_eq(OK, s21_add(value_1, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_1.bits[i], result.bits[i]);
  }
  // 2313682943 + 18446744073709551615 = 18446744076023234558
  ck_assert_int_eq(OK, s21_add(value_1, value_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_2.bits[i], result.bits[i]);
  }
  // 2313682943 + 1367291536776409582141439 = 1367291536776411895824382
  ck_assert_int_eq(OK, s21_add(value_1, value_3, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_3.bits[i], result.bits[i]);
  }
  // 18446744073709551615 + 2313682943 = 18446744076023234558
  ck_assert_int_eq(OK, s21_add(value_2, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_2.bits[i], result.bits[i]);
  }
  // 18446744073709551615 + 18446744073709551615 = 36893488147419103230
  ck_assert_int_eq(OK, s21_add(value_2, value_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_4.bits[i], result.bits[i]);
  }
  // 18446744073709551615 + 1367291536776409582141439 =
  // 1367309983520483291693054
  ck_assert_int_eq(OK, s21_add(value_2, value_3, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_5.bits[i], result.bits[i]);
  }
  // 1367291536776409582141439 + 2313682943 = 1367291536776411895824382
  ck_assert_int_eq(OK, s21_add(value_3, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_3.bits[i], result.bits[i]);
  }
  // 1367291536776409582141439 + 18446744073709551615 =
  // 1367309983520483291693054
  ck_assert_int_eq(OK, s21_add(value_3, value_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_5.bits[i], result.bits[i]);
  }
  // 1367291536776409582141439 + 1367291536776409582141439 =
  // 2734583073552819164282878
  ck_assert_int_eq(OK, s21_add(value_3, value_3, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_6.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(add_test_3) {
  s21_decimal value_1 = {{0x89E7FFFF, 0x00000000, 0x00000000,
                          0x80000000}};  //                -2313682943
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0x00000000,
                          0x80000000}};  //      -18446744073709551615
  s21_decimal value_3 = {{0xFFFFFFFF, 0x05D19D1B, 0x00012189,
                          0x80000000}};  // -1367291536776409582141439

  s21_decimal result = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  s21_decimal answer_1 = {{0x13CFFFFE, 0x00000001, 0x00000000,
                           0x80000000}};  //                -4627365886
  s21_decimal answer_2 = {{0x89E7FFFE, 0x00000000, 0x00000001,
                           0x80000000}};  //      -18446744076023234558
  s21_decimal answer_3 = {{0x89E7FFFE, 0x05D19D1C, 0x00012189,
                           0x80000000}};  // -1367291536776411895824382
  s21_decimal answer_4 = {{0xFFFFFFFE, 0xFFFFFFFF, 0x00000001,
                           0x80000000}};  //      -36893488147419103230
  s21_decimal answer_5 = {{0xFFFFFFFE, 0x05D19D1B, 0x0001218A,
                           0x80000000}};  // -1367309983520483291693054
  s21_decimal answer_6 = {{0xFFFFFFFE, 0x0BA33A37, 0x00024312,
                           0x80000000}};  // -2734583073552819164282878

  // -2313682943 + -2313682943 = -4627365886
  ck_assert_int_eq(OK, s21_add(value_1, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_1.bits[i], result.bits[i]);
  }
  // -2313682943 + -18446744073709551615 = -18446744076023234558
  ck_assert_int_eq(OK, s21_add(value_1, value_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_2.bits[i], result.bits[i]);
  }
  // -2313682943 + -1367291536776409582141439 = -1367291536776411895824382
  ck_assert_int_eq(OK, s21_add(value_1, value_3, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_3.bits[i], result.bits[i]);
  }
  // -18446744073709551615 + -2313682943 = -18446744076023234558
  ck_assert_int_eq(OK, s21_add(value_2, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_2.bits[i], result.bits[i]);
  }
  // -18446744073709551615 + -18446744073709551615 = -36893488147419103230
  ck_assert_int_eq(OK, s21_add(value_2, value_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_4.bits[i], result.bits[i]);
  }
  // -18446744073709551615 + -1367291536776409582141439 =
  // -1367309983520483291693054
  ck_assert_int_eq(OK, s21_add(value_2, value_3, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_5.bits[i], result.bits[i]);
  }
  // -1367291536776409582141439 + -2313682943 = -1367291536776411895824382
  ck_assert_int_eq(OK, s21_add(value_3, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_3.bits[i], result.bits[i]);
  }
  // -1367291536776409582141439 + -18446744073709551615 =
  // -1367309983520483291693054
  ck_assert_int_eq(OK, s21_add(value_3, value_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_5.bits[i], result.bits[i]);
  }
  // -1367291536776409582141439 + -1367291536776409582141439 =
  // -2734583073552819164282878
  ck_assert_int_eq(OK, s21_add(value_3, value_3, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_6.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(add_test_4) {
  s21_decimal value_1 = {{0x89E7FFFF, 0x00000000, 0x00000000,
                          0x00050000}};  //                23136.82943
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0x00000000,
                          0x00080000}};  //      184467440737.09551615
  s21_decimal value_3 = {{0xFFFFFFFF, 0x05D19D1B, 0x00012189,
                          0x000C0000}};  // 1367291536776.409582141439

  s21_decimal result = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  s21_decimal answer_1 = {{0x13CFFFFE, 0x00000001, 0x00000000,
                           0x00050000}};  //                46273.65886
  s21_decimal answer_2 = {{0xB23FFC17, 0x0000021A, 0x00000001,
                           0x00080000}};  //      184467463873.92494615
  s21_decimal answer_3 = {{0xE367697F, 0x0623CFEE, 0x00012189,
                           0x000C0000}};  // 1367291559913.239012141439
  s21_decimal answer_4 = {{0xFFFFFFFE, 0xFFFFFFFF, 0x00000001,
                           0x00080000}};  //      368934881474.19103230
  s21_decimal answer_5 = {{0xFFFFD8EF, 0x05D19D1B, 0x00014899,
                           0x000C0000}};  // 1551758977513.505098291439
  s21_decimal answer_6 = {{0xFFFFFFFE, 0x0BA33A37, 0x00024312,
                           0x000C0000}};  // 2734583073552.819164282878

  // 23136.82943 + 23136.82943 = 46273.65886
  ck_assert_int_eq(OK, s21_add(value_1, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_1.bits[i], result.bits[i]);
  }
  // 23136.82943 + 184467440737.09551615 = 184467463873.92494615
  ck_assert_int_eq(OK, s21_add(value_1, value_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_2.bits[i], result.bits[i]);
  }
  // 2313682943 + 1367291536776.409582141439 = 1367291559913.239012141439
  ck_assert_int_eq(OK, s21_add(value_1, value_3, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_3.bits[i], result.bits[i]);
  }
  // 184467440737.09551615 + 23136.82943 = 184467463873.92494615
  ck_assert_int_eq(OK, s21_add(value_2, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_2.bits[i], result.bits[i]);
  }
  // 184467440737.09551615 + 184467440737.09551615 = 368934881474.19103230
  ck_assert_int_eq(OK, s21_add(value_2, value_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_4.bits[i], result.bits[i]);
  }
  // 184467440737.09551615 + 1367291536776.409582141439 =
  // 1551758977513.505098291439
  ck_assert_int_eq(OK, s21_add(value_2, value_3, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_5.bits[i], result.bits[i]);
  }
  // 1367291536776.409582141439 + 2313682943 = 1367291559913.239012141439
  ck_assert_int_eq(OK, s21_add(value_3, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_3.bits[i], result.bits[i]);
  }
  // 1367291536776.409582141439 + 184467440737.09551615 =
  // 1551758977513.505098291439
  ck_assert_int_eq(OK, s21_add(value_3, value_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_5.bits[i], result.bits[i]);
  }
  // 1367291536776.409582141439 + 1367291536776.409582141439 =
  // 2734583073552.819164282878
  ck_assert_int_eq(OK, s21_add(value_3, value_3, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_6.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(add_test_5) {
  s21_decimal value_1 = {{0x89E7FFFF, 0x00000000, 0x00000000,
                          0x80050000}};  //                -23136.82943
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0x00000000,
                          0x80080000}};  //      -184467440737.09551615
  s21_decimal value_3 = {{0xFFFFFFFF, 0x05D19D1B, 0x00012189,
                          0x800C0000}};  // -1367291536776.409582141439

  s21_decimal result = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  s21_decimal answer_1 = {{0x13CFFFFE, 0x00000001, 0x00000000,
                           0x80050000}};  //                -46273.65886
  s21_decimal answer_2 = {{0xB23FFC17, 0x0000021A, 0x00000001,
                           0x80080000}};  //      -184467463873.92494615
  s21_decimal answer_3 = {{0xE367697F, 0x0623CFEE, 0x00012189,
                           0x800C0000}};  // -1367291559913.239012141439
  s21_decimal answer_4 = {{0xFFFFFFFE, 0xFFFFFFFF, 0x00000001,
                           0x80080000}};  //      -368934881474.19103230
  s21_decimal answer_5 = {{0xFFFFD8EF, 0x05D19D1B, 0x00014899,
                           0x800C0000}};  // -1551758977513.505098291439
  s21_decimal answer_6 = {{0xFFFFFFFE, 0x0BA33A37, 0x00024312,
                           0x800C0000}};  // -2734583073552.819164282878

  // -23136.82943 + -23136.82943 = -46273.65886
  ck_assert_int_eq(OK, s21_add(value_1, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_1.bits[i], result.bits[i]);
  }
  // -23136.82943 + -84467440737.09551615 = -184467463873.92494615
  ck_assert_int_eq(OK, s21_add(value_1, value_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_2.bits[i], result.bits[i]);
  }
  // -2313682943 + -1367291536776.409582141439 = -1367291559913.239012141439
  ck_assert_int_eq(OK, s21_add(value_1, value_3, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_3.bits[i], result.bits[i]);
  }
  // -184467440737.09551615 + -23136.82943 = -184467463873.92494615
  ck_assert_int_eq(OK, s21_add(value_2, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_2.bits[i], result.bits[i]);
  }
  // -184467440737.09551615 + -184467440737.09551615 = -368934881474.19103230
  ck_assert_int_eq(OK, s21_add(value_2, value_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_4.bits[i], result.bits[i]);
  }
  // -184467440737.09551615 + -1367291536776.409582141439 =
  // -1551758977513.505098291439
  ck_assert_int_eq(OK, s21_add(value_2, value_3, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_5.bits[i], result.bits[i]);
  }
  // -1367291536776.409582141439 + -2313682943 = -1367291559913.239012141439
  ck_assert_int_eq(OK, s21_add(value_3, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_3.bits[i], result.bits[i]);
  }
  // -1367291536776.409582141439 + -184467440737.09551615 =
  // -1551758977513.505098291439
  ck_assert_int_eq(OK, s21_add(value_3, value_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_5.bits[i], result.bits[i]);
  }
  // -1367291536776.409582141439 + -1367291536776.409582141439 =
  // -2734583073552.819164282878
  ck_assert_int_eq(OK, s21_add(value_3, value_3, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_6.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(add_test_6) {
  s21_decimal max = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                      0x00000000}};  //    79228162514264337593543950335
  s21_decimal plus_one = {{0x00000001, 0x00000000, 0x00000000,
                           0x00000000}};  //                                1
  s21_decimal minus_one = {{0x00000001, 0x00000000, 0x00000000,
                            0x80000000}};  //                               -1
  s21_decimal plus_null = {{0x00000000, 0x00000000, 0x00000000,
                            0x00000000}};  //                                0
  s21_decimal minus_null = {{0x00000000, 0x00000000, 0x00000000,
                             0x80000000}};  //                               -0

  s21_decimal result = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  s21_decimal answer_1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
                           0x00000000}};  //    79228162514264337593543950334

  // 79228162514264337593543950335 + 79228162514264337593543950335 = NUMBER IS
  // TOO BIG!
  ck_assert_int_eq(BIG, s21_add(max, max, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(plus_null.bits[i], result.bits[i]);
  }
  // 79228162514264337593543950335 + 0 = 79228162514264337593543950335
  ck_assert_int_eq(OK, s21_add(max, plus_null, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(max.bits[i], result.bits[i]);
  }
  // 0 + 79228162514264337593543950335 = 79228162514264337593543950335
  ck_assert_int_eq(OK, s21_add(plus_null, max, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(max.bits[i], result.bits[i]);
  }
  // 79228162514264337593543950335 + (-0) = 79228162514264337593543950335
  ck_assert_int_eq(OK, s21_add(max, minus_null, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(max.bits[i], result.bits[i]);
  }
  // (-0) + 79228162514264337593543950335 = 79228162514264337593543950335
  ck_assert_int_eq(OK, s21_add(minus_null, max, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(max.bits[i], result.bits[i]);
  }
  // 79228162514264337593543950335 + 1 = NUMBER IS TOO BIG!
  ck_assert_int_eq(BIG, s21_add(max, plus_one, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(plus_null.bits[i], result.bits[i]);
  }
  // 1 + 79228162514264337593543950335 = NUMBER IS TOO BIG!
  ck_assert_int_eq(BIG, s21_add(plus_one, max, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(plus_null.bits[i], result.bits[i]);
  }
  // 79228162514264337593543950335 + (-1) = 79228162514264337593543950334
  ck_assert_int_eq(OK, s21_add(max, minus_one, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_1.bits[i], result.bits[i]);
  }
  // (-1) + 79228162514264337593543950335 = 79228162514264337593543950334
  ck_assert_int_eq(OK, s21_add(minus_one, max, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_1.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(add_test_7) {
  s21_decimal min = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                      0x80000000}};  //   -79228162514264337593543950335
  s21_decimal plus_one = {{0x00000001, 0x00000000, 0x00000000,
                           0x00000000}};  //                                1
  s21_decimal minus_one = {{0x00000001, 0x00000000, 0x00000000,
                            0x80000000}};  //                               -1
  s21_decimal plus_null = {{0x00000000, 0x00000000, 0x00000000,
                            0x00000000}};  //                                0
  s21_decimal minus_null = {{0x00000000, 0x00000000, 0x00000000,
                             0x80000000}};  //                               -0

  s21_decimal result = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  s21_decimal answer_1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
                           0x80000000}};  //    79228162514264337593543950334

  // // -79228162514264337593543950335 + -79228162514264337593543950335 = NUMBER
  // IS
  // // TOO SMALL!
  ck_assert_int_eq(SMALL, s21_add(min, min, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(plus_null.bits[i], result.bits[i]);
  }
  // -79228162514264337593543950335 + 0 = -79228162514264337593543950335
  ck_assert_int_eq(OK, s21_add(min, plus_null, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(min.bits[i], result.bits[i]);
  }
  // 0 + -79228162514264337593543950335 = -79228162514264337593543950335
  ck_assert_int_eq(OK, s21_add(plus_null, min, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(min.bits[i], result.bits[i]);
  }
  // -79228162514264337593543950335 + (-0) = -79228162514264337593543950335
  ck_assert_int_eq(OK, s21_add(min, minus_null, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(min.bits[i], result.bits[i]);
  }
  // (-0) + -79228162514264337593543950335 = -79228162514264337593543950335
  ck_assert_int_eq(OK, s21_add(minus_null, min, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(min.bits[i], result.bits[i]);
  }
  // -79228162514264337593543950335 + 1 = -79228162514264337593543950334
  ck_assert_int_eq(OK, s21_add(min, plus_one, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_1.bits[i], result.bits[i]);
  }
  // 1 + -79228162514264337593543950335 = -79228162514264337593543950334
  ck_assert_int_eq(OK, s21_add(plus_one, min, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_1.bits[i], result.bits[i]);
  }
  // -79228162514264337593543950335 + (-1) = NUMBER IS TOO SMALL!
  ck_assert_int_eq(SMALL, s21_add(min, minus_one, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(plus_null.bits[i], result.bits[i]);
  }
  // (-1) + -79228162514264337593543950335 = NUMBER IS TOO SMALL!
  ck_assert_int_eq(SMALL, s21_add(minus_one, min, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(plus_null.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(add_test_8) {
  s21_decimal max = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                      0x00000000}};  //    79228162514264337593543950335
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF,
                          0x00000000}};  //    39614081257132168796771975167
  s21_decimal value_2 = {{0x00000000, 0x00000000, 0x80000000,
                          0x00000000}};  //    39614081257132168796771975168
  s21_decimal value_3 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
                          0x00000000}};  //    79228162514264337593543950334
  s21_decimal value_4 = {{0x00000003, 0x00000000, 0x00000000,
                          0x00010000}};  //                              0.3
  s21_decimal value_5 = {{0x00000006, 0x00000000, 0x00000000,
                          0x00010000}};  //                              0.6
  s21_decimal plus_null = {{0x00000000, 0x00000000, 0x00000000,
                            0x00000000}};  //                                0

  s21_decimal result = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  // 39614081257132168796771975167 + 39614081257132168796771975167 =
  // 79228162514264337593543950334
  ck_assert_int_eq(OK, s21_add(value_1, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_3.bits[i], result.bits[i]);
  }
  // 39614081257132168796771975167 + 39614081257132168796771975168 =
  // 79228162514264337593543950335
  ck_assert_int_eq(OK, s21_add(value_1, value_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(max.bits[i], result.bits[i]);
  }
  //    39614081257132168796771975168 + 39614081257132168796771975168 = NUMBER
  //    IS TOO BIG!
  ck_assert_int_eq(BIG, s21_add(value_2, value_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(plus_null.bits[i], result.bits[i]);
  }
  //    79228162514264337593543950335 + 39614081257132168796771975167 = NUMBER
  //    IS TOO BIG!
  ck_assert_int_eq(BIG, s21_add(max, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(plus_null.bits[i], result.bits[i]);
  }
  //    39614081257132168796771975167 + 79228162514264337593543950335 = NUMBER
  //    IS TOO BIG!
  ck_assert_int_eq(BIG, s21_add(value_1, max, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(plus_null.bits[i], result.bits[i]);
  }
  // 79228162514264337593543950334 + 0.3 = ~79228162514264337593543950334
  ck_assert_int_eq(OK, s21_add(value_3, value_4, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_3.bits[i], result.bits[i]);
  }
  // 79228162514264337593543950334 + 0.6 = ~79228162514264337593543950335
  ck_assert_int_eq(OK, s21_add(value_3, value_5, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(max.bits[i], result.bits[i]);
  }
  // 79228162514264337593543950335 + 0.3 = ~79228162514264337593543950335
  ck_assert_int_eq(OK, s21_add(max, value_4, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(max.bits[i], result.bits[i]);
  }
  // 79228162514264337593543950335 + 0.6 = NUMBER IS TOO BIG!
  ck_assert_int_eq(BIG, s21_add(max, value_5, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(plus_null.bits[i], result.bits[i]);
  }
}
END_TEST

Suite* s21_add_suite(void) {
  Suite* s;
  s = suite_create("\033[33ms21_add\033[0m");

  TCase* tc_core;
  tc_core = tcase_create("s21_add_core");
  tcase_add_test(tc_core, add_test_1);
  tcase_add_test(tc_core, add_test_2);
  tcase_add_test(tc_core, add_test_3);
  tcase_add_test(tc_core, add_test_4);
  tcase_add_test(tc_core, add_test_5);
  tcase_add_test(tc_core, add_test_6);
  tcase_add_test(tc_core, add_test_7);
  tcase_add_test(tc_core, add_test_8);
  suite_add_tcase(s, tc_core);

  return s;
}
