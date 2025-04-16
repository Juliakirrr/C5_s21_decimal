#include "test.h"

#define OK 0
#define BIG 1
#define SMALL 2
#define DIV_NULL 3

START_TEST(div_test_1) {  // краевые моменты
  s21_decimal plus_one = {{0x00000001, 0x00000000, 0x00000000,
                           0x00000000}};  //                     1
  s21_decimal minus_one = {{0x00000001, 0x00000000, 0x00000000,
                            0x80000000}};  //                    -1
  s21_decimal plus_null = {{0x00000000, 0x00000000, 0x00000000,
                            0x00000000}};  //                     0
  s21_decimal minus_null = {{0x00000000, 0x00000000, 0x00000000,
                             0x80000000}};  //                    -0
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0x00000000,
                          0x00000000}};  //  18446744073709551615
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0x00000000,
                          0x80000000}};  // -18446744073709551615
  s21_decimal result = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  // 18446744073709551615 / 18446744073709551615 = 1
  //    result = (s21_decimal) {{0x00000000, 0x00000000, 0x00000000,
  //    0x00000000}};
  ck_assert_int_eq(OK, s21_div(value_1, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(plus_one.bits[i], result.bits[i]);
  }
  // 18446744073709551615 / -18446744073709551615 = -1
  //    result = (s21_decimal) {{0x00000000, 0x00000000, 0x00000000,
  //    0x00000000}};
  ck_assert_int_eq(OK, s21_div(value_1, value_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(minus_one.bits[i], result.bits[i]);
  }
  //    // -18446744073709551615 / -18446744073709551615 = 1
  //    result = (s21_decimal) {{0x00000000, 0x00000000, 0x00000000,
  //    0x00000000}};
  ck_assert_int_eq(OK, s21_div(value_2, value_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(plus_one.bits[i], result.bits[i]);
  }
  //    // 18446744073709551615 / 1 = 18446744073709551615
  //    result = (s21_decimal) {{0x00000000, 0x00000000, 0x00000000,
  //    0x00000000}};
  ck_assert_int_eq(OK, s21_div(value_1, plus_one, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_1.bits[i], result.bits[i]);
  }
  // 18446744073709551615 / -1 = -18446744073709551615
  //    result = (s21_decimal) {{0x00000000, 0x00000000, 0x00000000,
  //    0x00000000}};
  ck_assert_int_eq(OK, s21_div(value_1, minus_one, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_2.bits[i], result.bits[i]);
  }
  // -18446744073709551615 / -1 = 18446744073709551615
  //    result = (s21_decimal) {{0x00000000, 0x00000000, 0x00000000,
  //    0x00000000}};
  ck_assert_int_eq(OK, s21_div(value_2, minus_one, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_1.bits[i], result.bits[i]);
  }
  // 0 / 18446744073709551615 = 0
  //    result = (s21_decimal) {{0x00000000, 0x00000000, 0x00000000,
  //    0x00000000}};
  ck_assert_int_eq(OK, s21_div(plus_null, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(plus_null.bits[i], result.bits[i]);
  }
  // -0 / 18446744073709551615 = 0
  //    result = (s21_decimal) {{0x00000000, 0x00000000, 0x00000000,
  //    0x00000000}};
  ck_assert_int_eq(OK, s21_div(minus_null, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(plus_null.bits[i], result.bits[i]);
  }
  //     18446744073709551615 / 0 = ERROR
  //    result = (s21_decimal) {{0x00000000, 0x00000000, 0x00000000,
  //    0x00000000}};
  ck_assert_int_eq(DIV_NULL, s21_div(value_1, plus_null, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(plus_null.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(div_test_2) {  // делятся нацело, без дробной части
  s21_decimal value_1 = {{0x00000002, 0x00000000, 0x00000000,
                          0x00000000}};  //                              2
  s21_decimal value_2 = {{0x00000004, 0x00000000, 0x00000000,
                          0x00000000}};  //                              4
  s21_decimal value_3 = {{0x0000900B, 0x00000000, 0x00000000,
                          0x00000000}};  //                          36875
  s21_decimal value_4 = {{0x0012D687, 0x00000000, 0x00000000,
                          0x80000000}};  //                       -1234567
  s21_decimal value_5 = {{0x1F4BD3D5, 0x00000000, 0x00000000,
                          0x00000000}};  //                      525063125
  s21_decimal value_6 = {{0xFFFFFFF4, 0x00000000, 0x00000000,
                          0x00000000}};  //                     4294967284
  s21_decimal value_7 = {{0x1EF81C39, 0x00019FDD, 0x00000000,
                          0x00000000}};  //                457247032876089
  s21_decimal value_8 = {{0x0A52B413, 0x00008A9F, 0x00000000,
                          0x80000000}};  //               -152415677625363
  s21_decimal value_9 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
                          0x00000000}};  //  79228162514264337593543950334

  s21_decimal result = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  s21_decimal answer_1 = {{0x00000003, 0x00000000, 0x00000000,
                           0x80000000}};  //                             -3
  s21_decimal answer_2 = {{0x0000379F, 0x00000000, 0x00000000,
                           0x00000000}};  //                          14239
  s21_decimal answer_3 = {{0x075BCD15, 0x00000000, 0x00000000,
                           0x00000000}};  //                      123456789
  s21_decimal answer_4 = {{0x3FFFFFFD, 0x00000000, 0x00000000,
                           0x00000000}};  //                     1073741821
  s21_decimal answer_5 = {{0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF,
                           0x00000000}};  //  39614081257132168796771975167

  // 525063125 / 36875 = 14239
  ck_assert_int_eq(OK, s21_div(value_5, value_3, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_2.bits[i], result.bits[i]);
  }
  //    result = (s21_decimal) {{0x00000000, 0x00000000, 0x00000000,
  //    0x00000000}};
  // 4294967284 / 4 = 1073741821
  ck_assert_int_eq(OK, s21_div(value_6, value_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_4.bits[i], result.bits[i]);
  }
  //    result = (s21_decimal) {{0x00000000, 0x00000000, 0x00000000,
  //    0x00000000}};
  // 457247032876089 / -152415677625363 = -3
  ck_assert_int_eq(OK, s21_div(value_7, value_8, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_1.bits[i], result.bits[i]);
  }
  //    result = (s21_decimal) {{0x00000000, 0x00000000, 0x00000000,
  //    0x00000000}};
  // -152415677625363 / -1234567 = 123456789
  ck_assert_int_eq(OK, s21_div(value_8, value_4, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_3.bits[i], result.bits[i]);
  }
  //    result = (s21_decimal) {{0x00000000, 0x00000000, 0x00000000,
  //    0x00000000}};
  // 79228162514264337593543950334 / 2 = 39614081257132168796771975167
  ck_assert_int_eq(OK, s21_div(value_9, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_5.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(div_test_3) {  // делятся полностью, частное меньше единицы
  s21_decimal value_1 = {{0x00000001, 0x00000000, 0x00000000,
                          0x00000000}};  //                     1
  s21_decimal value_2 = {{0x00000100, 0x00000000, 0x00000000,
                          0x00000000}};  //                   256
  s21_decimal value_3 = {{0x00000400, 0x00000000, 0x00000000,
                          0x00000000}};  //                  1024
  s21_decimal value_4 = {{0x00000800, 0x00000000, 0x00000000,
                          0x00000000}};  //                  2048
  s21_decimal value_5 = {{0x00002729, 0x00000000, 0x00000000,
                          0x00000000}};  //                 10025
  s21_decimal value_6 = {{0x004C4B40, 0x00000000, 0x00000000,
                          0x00000000}};  //               5000000
  s21_decimal value_7 = {{0x00BC614E, 0x00000000, 0x00000000,
                          0x00000000}};  //              12345678
  s21_decimal value_8 = {{0x0BEBC200, 0x00000000, 0x00000000,
                          0x00000000}};  //             200000000

  s21_decimal result = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  s21_decimal answer_1 = {{0x00000019, 0x00000000, 0x00000000,
                           0x00020000}};  //          25  scale  2
  s21_decimal answer_2 = {{0x000007D5, 0x00000000, 0x00000000,
                           0x00060000}};  //        2005  scale  6
  s21_decimal answer_3 = {{0x005E30A7, 0x00000000, 0x00000000,
                           0x00080000}};  //     6172839  scale  8
  s21_decimal answer_4 = {{0x02E90EDD, 0x00000000, 0x00000000,
                           0x000B0000}};  //    48828125  scale 11

  // 1 / 2048 = 0.00048828125
  //    result = (s21_decimal) {{0x00000000, 0x00000000, 0x00000000,
  //    0x00000000}};
  ck_assert_int_eq(OK, s21_div(value_1, value_4, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_4.bits[i], result.bits[i]);
  }
  // 256 / 1024 = 0.25
  //    result = (s21_decimal) {{0x00000000, 0x00000000, 0x00000000,
  //    0x00000000}};
  ck_assert_int_eq(OK, s21_div(value_2, value_3, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_1.bits[i], result.bits[i]);
  }
  // 10025 / 5000000 = 0.002005
  //    result = (s21_decimal) {{0x00000000, 0x00000000, 0x00000000,
  //    0x00000000}};
  ck_assert_int_eq(OK, s21_div(value_5, value_6, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_2.bits[i], result.bits[i]);
  }
  //    result = (s21_decimal) {{0x00000000, 0x00000000, 0x00000000,
  //    0x00000000}};
  // 12345678 / 200000000 = 0.06172839                        // все же поискать
  // число на несколько интов
  ck_assert_int_eq(OK, s21_div(value_7, value_8, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_3.bits[i], result.bits[i]);
  }
}
END_TEST
//
START_TEST(div_test_4) {  // делятся полностью, есть целая и дробная части
  s21_decimal value_1 = {
      {0x00000008, 0x00000000, 0x00000000, 0x00000000}};  //                  8
  s21_decimal value_2 = {
      {0x00000018, 0x00000000, 0x00000000, 0x00000000}};  //                 24
  s21_decimal value_3 = {
      {0x0000057A, 0x00000000, 0x00000000, 0x00000000}};  //               1402
  s21_decimal value_4 = {
      {0x000072E1, 0x00000000, 0x00000000, 0x00000000}};  //              29409
  s21_decimal value_5 = {
      {0x000088B8, 0x00000000, 0x00000000, 0x00000000}};  //              35000
  s21_decimal value_6 = {
      {0x000101D0, 0x00000000, 0x00000000, 0x00000000}};  //              66000
  s21_decimal value_7 = {
      {0x894611F3, 0x00000000, 0x00000000, 0x00000000}};  //         2303070707
  s21_decimal value_8 = {
      {0x8AF2853F, 0x00632C40, 0x00000000, 0x00000000}};  //  27914678415033663

  s21_decimal result = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  s21_decimal answer_1 = {{0x00004475, 0x00000000, 0x00000000,
                           0x00020000}};  //              17525  scale  2
  s21_decimal answer_2 = {{0x0012B29F, 0x00000000, 0x00000000,
                           0x00030000}};  //            1225375  scale  3
  s21_decimal answer_3 = {{0x2738976A, 0x00000000, 0x00000000,
                           0x00040000}};  //          658020202  scale  4
  s21_decimal answer_4 = {{0x7224BEDB, 0x000F06B4, 0x00000000,
                           0x00040000}};  //   4229496729550555  scale  4

  // 1402 / 8 = 175.25
  //    result = (s21_decimal) {{0x00000000, 0x00000000, 0x00000000,
  //    0x00000000}};
  ck_assert_int_eq(OK, s21_div(value_3, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_1.bits[i], result.bits[i]);
  }
  // 29409 / 24 = 1225.375
  //    result = (s21_decimal) {{0x00000000, 0x00000000, 0x00000000,
  //    0x00000000}};
  ck_assert_int_eq(OK, s21_div(value_4, value_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_2.bits[i], result.bits[i]);
  }
  // 2303070707 / 35000 = 65802.0202
  //    result = (s21_decimal) {{0x00000000, 0x00000000, 0x00000000,
  //    0x00000000}};
  ck_assert_int_eq(OK, s21_div(value_7, value_5, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_3.bits[i], result.bits[i]);
  }
  // 27914678415033663 / 66000 = 422949672955.0555
  //    result = (s21_decimal) {{0x00000000, 0x00000000, 0x00000000,
  //    0x00000000}};
  ck_assert_int_eq(OK, s21_div(value_8, value_6, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_4.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(div_test_5) {  // дробные на дробные
  s21_decimal value_1 = {{0x00000005, 0x00000000, 0x00000000,
                          0x00000000}};  //                       5
  s21_decimal value_2 = {{0x00000015, 0x00000000, 0x00000000,
                          0x00010000}};  //                      21 scale 1
  s21_decimal value_3 = {{0x00000054, 0x00000000, 0x00000000,
                          0x00010000}};  //                      84 scale 1
  s21_decimal value_4 = {{0x000004E3, 0x00000000, 0x00000000,
                          0x00010000}};  //                    1251 scale 1
  s21_decimal value_5 = {{0x0020924C, 0x00000000, 0x00000000,
                          0x00020000}};  //                 2134604 scale 2
  s21_decimal value_6 = {{0x0C108FC9, 0x00000008, 0x00000000,
                          0x00040000}};  //             34562150345 scale 4
  s21_decimal value_7 = {{0x07BBC100, 0x0000BB81, 0x00000000,
                          0x00050000}};  //         206162854920448 scale 5
  s21_decimal value_8 = {{0xC26A3F37, 0x03B07652, 0x0000020B,
                          0x00080000}};  //  9647912993025931493175 scale 8

  s21_decimal result = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};  //

  s21_decimal answer_1 = {{0x00000004, 0x00000000, 0x00000000,
                           0x00000000}};  //                       4
  s21_decimal answer_2 = {{0x000009C6, 0x00000000, 0x00000000,
                           0x00020000}};  //                    2502 scale 2
  s21_decimal answer_3 = {{0x05C1B6C0, 0x00000000, 0x00000000,
                           0x00030000}};  //                96581312 scale 3
  s21_decimal answer_4 = {{0xFE71D6FF, 0x00000040, 0x00000000,
                           0x00040000}};  //            279146780415 scale 4

  // 8.4 / 2.1 = 4
  ck_assert_int_eq(OK, s21_div(value_3, value_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_1.bits[i], result.bits[i]);
  }
  // 125.1 / 5 = 25.02
  ck_assert_int_eq(OK, s21_div(value_4, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_2.bits[i], result.bits[i]);
  }
  //   // 2061628549.20448 / 21346.04 = 96581.312
  ck_assert_int_eq(OK, s21_div(value_7, value_5, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_3.bits[i], result.bits[i]);
  }
  //    // 96479129930259.31493175 / 3456215.0345 = 27914678.0415
  ck_assert_int_eq(OK, s21_div(value_8, value_6, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_4.bits[i], result.bits[i]);
  }
}
END_TEST
//
START_TEST(div_test_6) {  // меньше 1 на меньше 1
  s21_decimal value_1 = {{0x00000003, 0x00000000, 0x00000000,
                          0x00080000}};  //                       3 scale  8
  s21_decimal value_2 = {{0x00000005, 0x00000000, 0x00000000,
                          0x00010000}};  //                       5 scale  1
  s21_decimal value_3 = {{0x0000004B, 0x00000000, 0x00000000,
                          0x00020000}};  //                      75 scale  2
  s21_decimal value_4 = {{0x00000100, 0x00000000, 0x00000000,
                          0x00040000}};  //                     256 scale  4
  s21_decimal value_5 = {{0x000004B5, 0x00000000, 0x00000000,
                          0x00050000}};  //                    1205 scale  5
  s21_decimal value_6 = {{0x00000800, 0x00000000, 0x00000000,
                          0x00050000}};  //                    2048 scale  5
  s21_decimal value_7 = {{0xB4E8F380, 0x00000000, 0x00000000,
                          0x000C0000}};  //              3035165568 scale 12
  s21_decimal value_8 = {{0xC80E439F, 0x00001B8E, 0x00000000,
                          0x00100000}};  //          30300055683999 scale 16

  s21_decimal result = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};  //

  s21_decimal answer_1 = {{0x00000008, 0x00000000, 0x00000000,
                           0x00010000}};  //                       8 scale 1
  s21_decimal answer_2 = {{0x0000000F, 0x00000000, 0x00000000,
                           0x00010000}};  //                      15 scale 1
  s21_decimal answer_3 = {{0x01805700, 0x00000000, 0x00000000,
                           0x00080000}};  //                25188096 scale 8
  s21_decimal answer_4 = {{0x9804C135, 0x0000092F, 0x00000000,
                           0x00080000}};  //          10100018561333 scale 8

  // 0.75 / 0.5 = 1.5
  ck_assert_int_eq(OK, s21_div(value_3, value_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_2.bits[i], result.bits[i]);
  }
  // 0.02048 / 0.0256 = 0.8
  ck_assert_int_eq(OK, s21_div(value_6, value_4, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_1.bits[i], result.bits[i]);
  }
  // 0.003035165568 / 0.01205 = 0.25188096
  ck_assert_int_eq(OK, s21_div(value_7, value_5, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_3.bits[i], result.bits[i]);
  }
  // 0.0030300055683999 / 0.00000003 = 101000.18561333
  ck_assert_int_eq(OK, s21_div(value_8, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_4.bits[i], result.bits[i]);
  }
}
END_TEST
//
START_TEST(div_test_7) {  // ошибки
  s21_decimal value_1 = {{0x00000000, 0x00000000, 0x00000000,
                          0x00000000}};  //                                0
  s21_decimal value_2 = {{0x00000001, 0x00000000, 0x00000000,
                          0x00020000}};  //                             0.01
  s21_decimal value_3 = {{0x00000001, 0x00000000, 0x00000000,
                          0x80020000}};  //                            -0.01
  s21_decimal value_4 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                          0x00000000}};  //    79228162514264337593543950335

  s21_decimal result = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};  //

  // 0.1 / 0 = ERROR
  ck_assert_int_eq(DIV_NULL, s21_div(value_2, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_1.bits[i], result.bits[i]);
  }
  // 79228162514264337593543950335 / 0.01 = ERROR - TOO BIG
  ck_assert_int_eq(BIG, s21_div(value_4, value_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_1.bits[i], result.bits[i]);
  }
  // 79228162514264337593543950335 / -0.01 = ERROR - TOO SMALL
  ck_assert_int_eq(SMALL, s21_div(value_4, value_3, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_1.bits[i], result.bits[i]);
  }
}
END_TEST

Suite* s21_div_suite(void) {
  Suite* s;
  s = suite_create("\033[33ms21_div\033[0m");

  TCase* tc_core;
  tc_core = tcase_create("s21_div_core");
  tcase_add_test(tc_core, div_test_1);
  tcase_add_test(tc_core, div_test_2);
  tcase_add_test(tc_core, div_test_3);
  tcase_add_test(tc_core, div_test_4);
  tcase_add_test(tc_core, div_test_5);
  tcase_add_test(tc_core, div_test_6);
  tcase_add_test(tc_core, div_test_7);
  suite_add_tcase(s, tc_core);

  return s;
}
