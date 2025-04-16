#include "test.h"

//                 банковское округление
//        |       у меня       |         в тестах         |
// 333.49 | 333.49->333.5->334 | 333.49->333 (0.49 < 0.5) |
// 334.51 | 334.51->334.5->334 | 334.51->335 (0.51 > 0.5) |

#define OK 0
#define BIG 1
#define SMALL 2

START_TEST(sub_test_1) {  // общий тест включая ошибки
  s21_decimal value_1 = {{0x00000000, 0x00000000, 0x00000000,
                          0x00000000}};  //                              0
  s21_decimal value_2 = {{0x00000000, 0x00000000, 0x00000000,
                          0x80000000}};  //                             -0
  s21_decimal value_3 = {{0x00000001, 0x00000000, 0x00000000,
                          0x00000000}};  //                              1
  s21_decimal value_4 = {{0x00000001, 0x00000000, 0x00000000,
                          0x80000000}};  //                             -1
  s21_decimal value_5 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                          0x00000000}};  //  79228162514264337593543950335
  s21_decimal value_6 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                          0x80000000}};  // -79228162514264337593543950335

  s21_decimal result = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  s21_decimal answer_1 = {{0x00000002, 0x00000000, 0x00000000,
                           0x00000000}};  //                              2
  s21_decimal answer_2 = {{0x00000002, 0x00000000, 0x00000000,
                           0x80000000}};  //                             -2
  s21_decimal answer_3 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
                           0x00000000}};  //  79228162514264337593543950334
  s21_decimal answer_4 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
                           0x80000000}};  // -79228162514264337593543950334

  // 0 - 0 = 0
  ck_assert_int_eq(OK, s21_sub(value_1, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_1.bits[i], result.bits[i]);
  }
  // 0 - (-0) = 0
  ck_assert_int_eq(OK, s21_sub(value_1, value_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_1.bits[i], result.bits[i]);
  }
  // (-0) - 0 = 0
  ck_assert_int_eq(OK, s21_sub(value_2, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_1.bits[i], result.bits[i]);
  }
  // (-0) - (-0) = 0
  ck_assert_int_eq(OK, s21_sub(value_2, value_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_1.bits[i], result.bits[i]);
  }
  // // 0 - 1 = (-1)

  ck_assert_int_eq(OK, s21_sub(value_1, value_3, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_4.bits[i], result.bits[i]);
  }
  // 1 - 0 = 1
  ck_assert_int_eq(OK, s21_sub(value_3, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_3.bits[i], result.bits[i]);
  }
  // 0 - (-1) = 1
  ck_assert_int_eq(OK, s21_sub(value_1, value_4, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_3.bits[i], result.bits[i]);
  }
  // (-1) - 0 = (-1)
  ck_assert_int_eq(OK, s21_sub(value_4, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_4.bits[i], result.bits[i]);
  }
  // 1 - 1 = 0
  ck_assert_int_eq(OK, s21_sub(value_3, value_3, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_1.bits[i], result.bits[i]);
  }
  // 1 - (-1) = 2
  ck_assert_int_eq(OK, s21_sub(value_3, value_4, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_1.bits[i], result.bits[i]);
  }
  // (-1) - 1 = (-2)
  ck_assert_int_eq(OK, s21_sub(value_4, value_3, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_2.bits[i], result.bits[i]);
  }
  // (-1) - (-1) = 0
  ck_assert_int_eq(OK, s21_sub(value_4, value_4, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_1.bits[i], result.bits[i]);
  }
  // 79228162514264337593543950335 - 1 = 79228162514264337593543950334
  ck_assert_int_eq(OK, s21_sub(value_5, value_3, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_3.bits[i], result.bits[i]);
  }
  // (-79228162514264337593543950335) - (-1) = (-79228162514264337593543950334)
  ck_assert_int_eq(OK, s21_sub(value_6, value_4, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_4.bits[i], result.bits[i]);
  }
  // 0 - 79228162514264337593543950335 = (-79228162514264337593543950335)
  ck_assert_int_eq(OK, s21_sub(value_1, value_5, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_6.bits[i], result.bits[i]);
  }
  // 0 - (-79228162514264337593543950335) = 79228162514264337593543950335
  ck_assert_int_eq(OK, s21_sub(value_1, value_6, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_5.bits[i], result.bits[i]);
  }
  // 79228162514264337593543950335 - 0 = 79228162514264337593543950335
  ck_assert_int_eq(OK, s21_sub(value_5, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_5.bits[i], result.bits[i]);
  }
  // (-79228162514264337593543950335) - 0 = (-79228162514264337593543950335)
  ck_assert_int_eq(OK, s21_sub(value_6, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_6.bits[i], result.bits[i]);
  }
  //     // 79228162514264337593543950335 - (-1) = ERROR - TOO BIG
  ck_assert_int_eq(BIG, s21_sub(value_5, value_4, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_1.bits[i], result.bits[i]);
  }
  // (-79228162514264337593543950335) - 1 = ERROR - TOO SMALL
  ck_assert_int_eq(SMALL, s21_sub(value_6, value_3, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_1.bits[i], result.bits[i]);
  }
  // 79228162514264337593543950335 - 79228162514264337593543950335 = 0
  ck_assert_int_eq(OK, s21_sub(value_5, value_5, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_1.bits[i], result.bits[i]);
  }
  // (-79228162514264337593543950335) - (-79228162514264337593543950335) = 0
  ck_assert_int_eq(OK, s21_sub(value_6, value_6, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(value_1.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(sub_test_2) {  // целое из целого
  s21_decimal value_1 = {{0x00010C87, 0x00000000, 0x00000000,
                          0x00000000}};  //                          68743
  s21_decimal value_2 = {{0xC3C8168F, 0x00000000, 0x00000000,
                          0x00000000}};  //                     3284670095
  s21_decimal value_3 = {{0xBB8EADED, 0x00000050, 0x00000000,
                          0x00000000}};  //                   346744073709
  s21_decimal value_4 = {{0xB6159B8D, 0xAB587251, 0x00000000,
                          0x00000000}};  //           12346744073709001613
  s21_decimal value_5 = {{0x6BA928EE, 0x14F5A824, 0x0019D4D2,
                          0x00000000}};  //     31228162511287697590003950
  s21_decimal value_6 = {{0xBF90E2FF, 0x3D8EBD4B, 0x7B85984A,
                          0x00000000}};  //  38228162511234337590003950335

  s21_decimal result = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  s21_decimal answer_1 = {{0xC3C70A08, 0x00000000, 0x00000000,
                           0x00000000}};  //                     3284601352
  s21_decimal answer_2 = {{0xFA86EDA0, 0xAB587200, 0x00000000,
                           0x00000000}};  //           12346743726964927904
  s21_decimal answer_3 = {{0x53E7BA11, 0x28991527, 0x7B6BC378,
                           0x00000000}};  //  38196934348723049892413946385

  // 3284670095 - 68743 = 3284601352
  ck_assert_int_eq(OK, s21_sub(value_2, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_1.bits[i], result.bits[i]);
  }
  // 12346744073709001613 - 346744073709 = 12346743726964927904
  ck_assert_int_eq(OK, s21_sub(value_4, value_3, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_2.bits[i], result.bits[i]);
  }
  // 38228162511234337590003950335 - 31228162511287697590003950 =
  // 38196934348723049892413946385
  ck_assert_int_eq(OK, s21_sub(value_6, value_5, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_3.bits[i], result.bits[i]);
  }
}
END_TEST
//
START_TEST(sub_test_3) {  // дробное из целого
  s21_decimal value_1 = {{0x00001D09, 0x00000000, 0x00000000,
                          0x00020000}};  //                          74.33
  s21_decimal value_2 = {{0x00010C87, 0x00000000, 0x00000000,
                          0x00000000}};  //                          68743
  s21_decimal value_3 = {{0xE229E779, 0x0000000A, 0x00000000,
                          0x00040000}};  //                   4674407.0009
  s21_decimal value_4 = {{0x2C2D9B8A, 0x20914F4D, 0x00000000,
                          0x00000000}};  //            2346744073709001610
  s21_decimal value_5 = {{0xB3B5473F, 0xF5329307, 0x00000010,
                          0x00060000}};  //         312816251128769.759039
  s21_decimal value_6 = {{0x14E0E2FF, 0x6FA21317, 0x00000CF8,
                          0x00000000}};  //        61251234337590003950335

  s21_decimal result = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  s21_decimal answer_1 = {{0x0068C7B3, 0x00000000, 0x00000000,
                           0x00020000}};  //                       68668.67
  s21_decimal answer_2 = {{0xD361D727, 0x2C29B682, 0x000004F8,
                           0x00040000}};  //       2346744073704327202.9991
  s21_decimal answer_3 = {{0xCBFA3681, 0xDA985F4C, 0xC5E9D551,
                           0x00060000}};  // 61251234024773752821565.240961

  // 68743 - 74.33 = 68668.67
  ck_assert_int_eq(OK, s21_sub(value_2, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_1.bits[i], result.bits[i]);
  }
  //   2346744073709001610 - 4674407.0009 = 2346744073704327202.9991
  ck_assert_int_eq(OK, s21_sub(value_4, value_3, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_2.bits[i], result.bits[i]);
  }
  //     61251234337590003950335 - 312816251128769.759039 =
  //     61251234024773752821565.240961
  ck_assert_int_eq(OK, s21_sub(value_6, value_5, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_3.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(sub_test_4) {  // дробное из дробного
  s21_decimal value_1 = {{0x00074A89, 0x00000000, 0x00000000,
                          0x00020000}};  //                        4778.33
  s21_decimal value_2 = {{0x0048E963, 0x00000000, 0x00000000,
                          0x00030000}};  //                       4778.339
  s21_decimal value_3 = {{0x00477A44, 0x00000000, 0x00000000,
                          0x000C0000}};  //                 0.000004684356
  s21_decimal value_4 = {{0x05CFDAED, 0x0000009D, 0x00000000,
                          0x00110000}};  //            0.00000674407373549
  s21_decimal value_5 = {{0x2E5535FF, 0xC7C16F02, 0x0000069F,
                          0x00080000}};  //       312816251128769.00759039
  s21_decimal value_6 = {{0xA8DA332F, 0x9B4F75AC, 0x0005110B,
                          0x00050000}};  //     61251234337597241139.00335

  s21_decimal result = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  s21_decimal answer_1 = {{0x00000009, 0x00000000, 0x00000000,
                           0x00030000}};  //                          0.009
  s21_decimal answer_2 = {{0xF4DFD86D, 0x0000002F, 0x00000000,
                           0x00110000}};  //            0.00000205971773549
  s21_decimal answer_3 = {{0x6602B999, 0xE6A23B71, 0x13CA8EB6,
                           0x00080000}};  //  61250921521346112369.99575961

  // 4778.339 - 4778.33 = 0.009
  ck_assert_int_eq(OK, s21_sub(value_2, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_1.bits[i], result.bits[i]);
  }
  //     0.00000674407373549 - 0.000004684356 = 0.00000205971773549
  ck_assert_int_eq(OK, s21_sub(value_4, value_3, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_2.bits[i], result.bits[i]);
  }
  //     61251234337597241139.00335 - 312816251128769.00759039 =
  //     61250921521346112369.99575961
  ck_assert_int_eq(OK, s21_sub(value_6, value_5, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_3.bits[i], result.bits[i]);
  }
}
END_TEST
//
START_TEST(sub_test_5) {  // целое из дробного
  s21_decimal value_1 = {{0x00000D95, 0x00000000, 0x00000000,
                          0x00000000}};  //                              3477
  s21_decimal value_2 = {{0xD01B839F, 0x00000001, 0x00000000,
                          0x00050000}};  //                       77864.31391
  s21_decimal value_3 = {{0x9033BDED, 0x00000139, 0x00000000,
                          0x00000000}};  //                     1346744073709
  s21_decimal value_4 = {{0xB3F45881, 0x388077B2, 0x00000000,
                          0x00060000}};  //              4071385672549.947521
  s21_decimal value_5 = {{0x6259ECD9, 0x10D4C9F4, 0x00000000,
                          0x00000000}};  //               1212816251128769753
  s21_decimal value_6 = {{0xB78C2A07, 0x403585A9, 0x003BAE9E,
                          0x00070000}};  //       7215123433759724185.2439047

  s21_decimal result = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  s21_decimal answer_1 = {{0xBB62087F, 0x00000001, 0x00000000,
                           0x00050000}};  //                       74387.31391
  s21_decimal answer_2 = {{0x2F2AC341, 0x25CFDF19, 0x00000000,
                           0x00060000}};  //              2724641598840.947521
  s21_decimal answer_3 = {{0x38F69787, 0x3E60F473, 0x0031A661,
                           0x00070000}};  //       6002307182630954432.2439047

  // 77864.31391 - 3477 = 74387.31391
  ck_assert_int_eq(OK, s21_sub(value_2, value_1, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_1.bits[i], result.bits[i]);
  }
  // 4071385672549.947521 - 1346744073709 = 2724641598840.947521
  ck_assert_int_eq(OK, s21_sub(value_4, value_3, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_2.bits[i], result.bits[i]);
  }
  // 7215123433759724185.2439047 - 1212816251128769753 =
  // 6002307182630954432.2439047
  ck_assert_int_eq(OK, s21_sub(value_6, value_5, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_3.bits[i], result.bits[i]);
  }
}
END_TEST
//
START_TEST(sub_test_6) {  // целое из целого (первое меньше)
  s21_decimal value_1 = {{0x00010C87, 0x00000000, 0x00000000,
                          0x00000000}};  //                          68743
  s21_decimal value_2 = {{0xC3C8168F, 0x00000000, 0x00000000,
                          0x00000000}};  //                     3284670095
  s21_decimal value_3 = {{0xBB8EADED, 0x00000050, 0x00000000,
                          0x00000000}};  //                   346744073709
  s21_decimal value_4 = {{0xB6159B8D, 0xAB587251, 0x00000000,
                          0x00000000}};  //           12346744073709001613
  s21_decimal value_5 = {{0x6BA928EE, 0x14F5A824, 0x0019D4D2,
                          0x00000000}};  //     31228162511287697590003950
  s21_decimal value_6 = {{0xBF90E2FF, 0x3D8EBD4B, 0x7B85984A,
                          0x00000000}};  //  38228162511234337590003950335

  s21_decimal result = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

  s21_decimal answer_1 = {{0xC3C70A08, 0x00000000, 0x00000000,
                           0x80000000}};  //                    -3284601352
  s21_decimal answer_2 = {{0xFA86EDA0, 0xAB587200, 0x00000000,
                           0x80000000}};  //          -12346743726964927904
  s21_decimal answer_3 = {{0x53E7BA11, 0x28991527, 0x7B6BC378,
                           0x80000000}};  // -38196934348723049892413946385

  // 68743 - 3284670095 = -3284601352
  ck_assert_int_eq(OK, s21_sub(value_1, value_2, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_1.bits[i], result.bits[i]);
  }
  // 346744073709 - 12346744073709001613 = -12346743726964927904
  ck_assert_int_eq(OK, s21_sub(value_3, value_4, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_2.bits[i], result.bits[i]);
  }
  // 31228162511287697590003950 - 38228162511234337590003950335 =
  // -38196934348723049892413946385
  ck_assert_int_eq(OK, s21_sub(value_5, value_6, &result));
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer_3.bits[i], result.bits[i]);
  }
}
END_TEST

Suite* s21_sub_suite(void) {
  Suite* s;
  s = suite_create("\033[33ms21_sub\033[0m");

  TCase* tc_core;
  tc_core = tcase_create("s21_sub_core");
  tcase_add_test(tc_core, sub_test_1);
  tcase_add_test(tc_core, sub_test_2);
  tcase_add_test(tc_core, sub_test_3);
  tcase_add_test(tc_core, sub_test_4);
  tcase_add_test(tc_core, sub_test_5);
  tcase_add_test(tc_core, sub_test_6);
  suite_add_tcase(s, tc_core);

  return s;
}
