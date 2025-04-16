#include "s21_decimal.h"

void division_long_dec(long_decimal dividend, long_decimal divider,
                       long_decimal *result, long_decimal *rest) {  // ДЕЛЕНИЕ
  // long_decimal two = {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  // output_long_decimal(dividend);
  // printf("\n");
  // output_long_decimal(divider);

  long_decimal two_and_divider = {0};
  *result = two_and_divider;
  if (comparison_long_dec(dividend, divider) < 2) {
    while (1) {
      search_divider(divider, dividend, &two_and_divider,
                     result);  // ищем то что будем вычитать из дивидента и
                               // часть для ответа

      // printf("число для вычитания \n");
      // output_long_decimal(two_and_divider);
      // printf("число в результат \n");
      // output_long_decimal(*result);

      int c = 0;
      for (int i = 0; i < 13;
           i++) {  // вычитаем из делимого суммму получившуюся
        c = subtract_int_int(dividend.bits[i], two_and_divider.bits[i],
                             &dividend.bits[i], c);
      }
      if (comparison_long_dec(dividend, divider) == 2) {  // если
        (*rest) = dividend;
        break;
      } else if (comparison_long_dec(dividend, divider) == 0) {
        long_decimal one = {0};
        one.bits[0] = 1;
        add_for_mul(result, one);
        break;
      }
    }
  } else {
    // (*result) = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // результат 0 а
    // в остаток ушло все 1 число
    (*rest) = dividend;
  }
}

void search_divider(long_decimal divider, long_decimal dividend,
                    long_decimal *two_and_divider, long_decimal *result) {
  int a = 0;
  long_decimal two = {0};
  two.bits[0] = 1;
  long_decimal end_two = {0};
  long_decimal pre_two_and_divider = {0};
  while (1) {
    mul_long_dec(two, divider,
                 &pre_two_and_divider);  // умножаем делитель на степень 2

    // printf("divider\n");
    // output_long_decimal(divider);
    // printf("два\n");
    // output_long_decimal(two);
    // printf("пре результат\n");
    // output_long_decimal(pre_two_and_divider);

    a = comparison_long_dec(
        dividend,
        pre_two_and_divider);  // проверяем больше ли результат, делимого
    if (a == 1) {  // если больше то возводим в степень 2 и обнуляем
      end_two = two;

      // printf("два\n");
      // output_long_decimal(two);
      shift_left_long_dec(two, &two);
      // output_long_decimal(two);
      (*two_and_divider) = pre_two_and_divider;
    } else if (a == 0) {
      (*two_and_divider) = pre_two_and_divider;
      // (*result)= (*result) + two;
      add_for_mul(result, two);
      break;
    } else if (a == 2) {
      // (*result) = (*result) + end_two;
      add_for_mul(result, end_two);
      break;
    }
  }
}

int s21_get_bit(int number, int position) {
  unsigned mask = 1 << position;
  unsigned bit = (number & mask) >> position;
  return bit;
}

void print_longlong(unsigned long long value) {
  for (int i = 63; i >= 0; --i) {
    printf("%llu", (value >> i) & 1);
  }
  // printf("\n");
}

void change_bit_1(unsigned *number, int position) {
  unsigned mask = 1 << position;
  (*number) = ((*number) | mask);
}

void change_bit_0(unsigned *number, int position) {
  if (0 != s21_get_bit((*number), position)) {
    unsigned mask = 1 << position;
    (*number) = (*number) ^ mask;
  }
}

// void output(int a) { // вывести 1 инт в двоичном виде
//   for (int i = 31; i > -1; i--) {
//     int b = s21_get_bit(a, i);
//     printf("%d ", b);
//   }
//   printf("\n");
// }

// void output_all_decimal(s21_decimal a) { // вывести 1 инт в двоичном виде
//   for (int j = 3; j > -1; j--) {
//     for (int i = 31; i > -1; i--) {
//       int b = s21_get_bit(a.bits[j], i);
//       printf("%d", b);
//     }
//     printf(" ");
//   }
//   printf("\n");
// }

// void output_long_decimal(long_decimal a) { // вывести 1 инт в двоичном виде
//   for (int j = 13; j > -1; j--) {
//     for (int i = 31; i > -1; i--) {
//       int b = s21_get_bit(a.bits[j], i);
//       printf("%d", b);
//     }
//     if (j == 9 || j == 4) {
//       printf("\n");
//     } else {
//       printf(" ");
//     }
//   }
//   printf("\n");
// }

int get_degree(unsigned a, int *sign) {  // получить степень
  (*sign) = s21_get_bit(a, 31);
  change_bit_0(&a, 31);
  a = a >> 16;
  return a;
}

void put_degree(unsigned *bit_0, int degree,
                int sign) {  // записать степень и знак
  (*bit_0) = degree << 16;
  if (sign == 0) {  // +
    change_bit_0(bit_0, 31);
  } else {  // -
    change_bit_1(bit_0, 31);
  }
}

int add_int_int(unsigned a, unsigned b, unsigned *result,
                int c) {  // слагаемые и сумма и добавочное число которое
                          // передаем в некст инт
                          // int c = 0;
  for (int i = 0; i < 32; i++) {
    int bit_a = s21_get_bit(a, i);
    int bit_b = s21_get_bit(b, i);

    if (bit_a + bit_b + c == 0) {
      change_bit_0(result, i);
      c = 0;
    } else if (bit_a + bit_b + c == 1) {
      change_bit_1(result, i);
      c = 0;
    } else if (bit_a + bit_b + c == 2) {
      change_bit_0(result, i);
      c = 1;
    } else if (bit_a + bit_b + c == 3) {
      change_bit_1(result, i);
      c = 1;
    }
  }
  return c;
}

int subtract_int_int(
    unsigned a, unsigned b, unsigned *result,
    int c) {  // уменьшаемое, вычитаемое, разность, долг с прошлого раза
  // int c = 0;
  for (int i = 0; i < 32; i++) {
    int bit_a = s21_get_bit(a, i);
    int bit_b = s21_get_bit(b, i);

    if (bit_a > 0) {
      bit_a = bit_a - c;
      c = 0;
    }

    if (bit_a == 1 && bit_b == 1) {
      change_bit_0(result, i);
    } else if (bit_a == 0 && bit_b == 0) {
      if (c == 0) {
        change_bit_0(result, i);
      } else if (c == 1) {
        change_bit_1(result, i);
      }
    } else if (bit_a == 1 && bit_b == 0) {
      change_bit_1(result, i);
    } else if (bit_a == 0 && bit_b == 1) {
      if (c == 1) {
        change_bit_0(result, i);
        c = 1;
      } else if (c == 0) {
        change_bit_1(result, i);
        c = 1;
      }
    }
  }
  return c;
}

void write_to_long_decimal(s21_decimal a, long_decimal *b) {
  b->bits[0] = a.bits[0];
  b->bits[1] = a.bits[1];
  b->bits[2] = a.bits[2];
}

void mul_long_dec(long_decimal a, long_decimal b,
                  long_decimal *c) {  // умножаем 2 больштх децимала
  int bit = 0;
  long_decimal a_shift = {0};
  (*c) = a_shift;
  // output_long_decimal(*c);
  for (int i = 0; i < 14; i++) {
    for (int j = 0; j < 32; j++) {
      bit = s21_get_bit(b.bits[i], j);
      if (bit == 1) {
        int position = position_long_dec(i, j);
        if (position == 0) {
          (*c) = a;
        } else {
          record_with_shift(a, &a_shift, position);
          add_for_mul(c, a_shift);
        }
      }
    }
  }
}

void add_for_mul(long_decimal *result, long_decimal a) {  // сложение 2 лонг дец
  int c = 0;
  for (int i = 0; i < 13; i++) {
    c = add_int_int(result->bits[i], a.bits[i], &result->bits[i], c);
  }
}

void record_with_shift(long_decimal a, long_decimal *a_shift, int shift) {
  if (shift != 0) {
    shift_left_long_dec(a, a_shift);
    for (int i = 0; i < shift - 1; i++) {
      shift_left_long_dec((*a_shift), a_shift);
    }
  }
  // output_long_decimal(*a_shift);
  // printf("%d\n", shift);
}

void shift_left_long_dec(
    long_decimal a,
    long_decimal *num1) {  // смещение длинного дец на один влево
  int bit = 0;
  for (int i = 13; i > 0; i--) {
    bit = s21_get_bit(a.bits[i - 1], 31);
    if (bit == 0) {
      change_bit_0(&num1->bits[i], 0);
    } else if (bit == 1) {
      change_bit_1(&num1->bits[i], 0);
    }
    num1->bits[i - 1] = a.bits[i - 1] << 1;
  }
}

int position_long_dec(int i, int j) {
  int a = j + (i * 32);  // мб не 32 а 31
  return a;
}

int comparison_long_dec(
    long_decimal a, long_decimal b) {  // сравнивает два лонг дец. 0 если равны
                                       // . 1 если 1 больше. 2 если 2 больше.
  // int result = 0;
  for (int i = 13; i > -1; i--) {
    for (int j = 31; j > -1; j--) {
      int bit_a = s21_get_bit(a.bits[i], j);
      int bit_b = s21_get_bit(b.bits[i], j);
      if (bit_a > bit_b) {
        // result = 1;
        return 1;
      }
      if (bit_b > bit_a) {
        // result = 2;
        return 2;
      }
    }
  }
  return 0;
}

int reduction_function(long_decimal *long_result,
                       int *scale_result) {  // сокращаем лонг дец
  long_decimal rest = {0};
  long_decimal ten = {0};
  ten.bits[0] = 10;
  int h = 1, error = 0, ii = 0;
  // output_long_decimal(ten);
  for (int i = (*scale_result); i > 0 && h != 0; i--) {
    division_long_dec(*long_result, ten, long_result, &rest);
    h = check_long_dec(*long_result);
    ii++;
    ;
  }
  (*scale_result) = (*scale_result) - ii;

  // printf("scale = %d\n",*scale_result);

  if ((*scale_result) > 28) {
    for (int i = (*scale_result) - 28; i != 0; i--) {
      division_long_dec(*long_result, ten, long_result, &rest);
      h = check_long_dec(*long_result);
    }
    (*scale_result) = 28;
  }

  // output_long_decimal(*long_result);
  // printf("на сколько уменьшился скейдл %d\n", *scale_result);
  // printf("ошибка переполнения %d\n", h);
  // printf("остаок %d\n", rest.bits[0]);
  // printf("бит %d\n", s21_get_bit(long_result->bits[0], 0));

  if (h == 0) {
    // if(*sign_result == 0){      // если число положительное
    if ((rest.bits[0] == 5 && s21_get_bit(long_result->bits[0], 0) == 1) ||
        rest.bits[0] >
            5) {  // если осаток 5 и число четное надо прибавить 1 и проверить
                  // не вылез ли за мантису ИЛИ  число больше 5
      long_decimal one = {0};
      one.bits[0] = 1;
      // output_long_decimal(*long_result);
      add_for_mul(long_result, one);  //прибавили 1
      if (check_long_dec(*long_result) == 1 &&
          (*scale_result) >
              0) {  // если опять преполнение и есть куда сокращать то сократим
        // printf("zasheeeeeeeeeeel\n");
        div_ten_add_one(long_result);
        // output_long_decimal(*long_result);
        (*scale_result) = (*scale_result) - 1;
      } else if (check_long_dec(*long_result) == 1 &&
                 (*scale_result) == 0) {  // ошибка преполнения
        error = 1;
      }
    }
    //}
    // else if(*sign_result == 1){     // если число отрицательное

    // }
  } else {
    error = 1;
  }

  return error;
}

void div_ten_add_one(long_decimal *a) {
  long_decimal rest2 = {0};
  long_decimal ten = {0};
  ten.bits[0] = 10;
  long_decimal one = {0};
  one.bits[0] = 1;

  division_long_dec(*a, ten, a, &rest2);

  if (rest2.bits[0] == 5 && s21_get_bit(a->bits[0], 0) == 1) {
    add_for_mul(a, one);  //прибавили 1
  } else if (rest2.bits[0] > 5) {
    add_for_mul(a, one);  //прибавили 1
  }
}

void recording_to_normal_dec(long_decimal long_result, s21_decimal *result,
                             int scale_result, int sign_result) {
  result->bits[0] = long_result.bits[0];
  result->bits[1] = long_result.bits[1];
  result->bits[2] = long_result.bits[2];
  put_degree(&result->bits[3], scale_result, sign_result);
  if (long_result.bits[0] == 0 && long_result.bits[1] == 0 &&
      long_result.bits[2] == 0) {
    result->bits[3] = 0;
  }
}

void recording_to_normal_dec2(long_decimal long_result, s21_decimal *result,
                              int scale_result, int sign_result) {
  result->bits[0] = long_result.bits[0];
  result->bits[1] = long_result.bits[1];
  result->bits[2] = long_result.bits[2];
  put_degree(&result->bits[3], scale_result, sign_result);
}

int check_long_dec(long_decimal a) {
  int b = 0;
  for (int i = 13; i > 2; i--) {
    if (a.bits[i] != 0) {
      b++;
    }
  }
  return b;
}

void equalize_the_degree(long_decimal *a, int degree) {
  long_decimal ten = {0};
  ten.bits[0] = 10;
  long_decimal ab = {0};

  for (int i = 1; i < degree; i++) {
    ten.bits[0] = ten.bits[0] * 10;
  }

  mul_long_dec((*a), ten, &ab);
  (*a) = ab;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign1 = 0, sign2 = 0, sign_result = 0;
  int scale1 = get_degree(value_1.bits[3], &sign1);
  int scale2 = get_degree(value_2.bits[3], &sign2);
  int scale_result = scale1;
  long_decimal first = {0};
  long_decimal second = {0};
  long_decimal long_result = {0};
  write_to_long_decimal(value_1, &first);
  write_to_long_decimal(value_2, &second);

  // printf("%d %d\n", sign1, scale1);
  // printf("%d %d\n", sign2, scale2);

  if (scale1 != scale2) {  // если разные скейлы
    if (scale1 > scale2) {
      scale_result = scale1;
      equalize_the_degree(&second, scale1 - scale2);
    } else if (scale2 > scale1) {
      scale_result = scale2;
      equalize_the_degree(&first, scale2 - scale1);
    }
  }

  // output_long_decimal(first);
  // output_long_decimal(second);

  int size = comparison_long_dec(first, second);  // вычисляем какое больше
  int c = 0;

  if (sign1 != sign2) {
    if (size == 1) {
      sign_result = sign1;
      for (int i = 0; i < 13; i++) {
        c = subtract_int_int(first.bits[i], second.bits[i], &first.bits[i], c);
      }
      // printf("\n");
      // output_long_decimal(first);
      long_result = first;
    } else if (size == 2) {
      sign_result = sign2;
      for (int i = 0; i < 13; i++) {
        c = subtract_int_int(second.bits[i], first.bits[i], &second.bits[i], c);
      }
      long_result = second;
    }
  } else {  // равны
    add_for_mul(&first, second);
    long_result = first;
    if (sign1 == 1 && sign2 == 1) {
      sign_result = 1;
    }
  }

  // output_long_decimal(long_result);   // у нас есть результат

  int check_dec =
      check_long_dec(long_result);  // проверяем не переполнен ли лонг дец

  if (check_dec == 0) {  //   не переполнен просто записываем результат
    recording_to_normal_dec(long_result, result, scale_result, sign_result);
    return 0;
  } else if (check_dec > 0) {  // переполнен
    int error = reduction_function(&long_result, &scale_result);
    if (error == 1 && sign_result == 1) {
      error = 2;
    }
    // printf("zasheeeeeeeeeeel\n");
    if (error == 0) {
      recording_to_normal_dec(long_result, result, scale_result, sign_result);
    }
    if (error != 0) {
      for (int i = 0; i < 4; i++) {
        result->bits[i] = 0;
      }
    }
    return error;
  }

  // output_long_decimal(long_result);
  return 0;  // спорно
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign1 = 0, sign2 = 0, sign_result = 0;
  int scale1 = get_degree(value_1.bits[3], &sign1);
  int scale2 = get_degree(value_2.bits[3], &sign2);
  int scale_result = scale1;
  long_decimal first = {0};
  long_decimal second = {0};
  long_decimal long_result = {0};
  write_to_long_decimal(value_1, &first);
  write_to_long_decimal(value_2, &second);

  // printf("знак и степень 1 = %d %d\n", sign1, scale1);
  // printf("знак и степень 2 = %d %d\n", sign2, scale2);

  if (scale1 != scale2) {  // если разные скейлы
    if (scale1 > scale2) {
      scale_result = scale1;
      equalize_the_degree(&second, scale1 - scale2);
    } else if (scale2 > scale1) {
      scale_result = scale2;
      equalize_the_degree(&first, scale2 - scale1);
    }
  }

  int size = comparison_long_dec(first, second);  // вычисляем какое больше
  int c = 0;

  //   printf("size = %d \n", size);

  if (sign1 != sign2) {           // если знаки разные
    add_for_mul(&first, second);  // сложение
    long_result = first;
    if (sign1 == 0) {         //  получается 123-(-123) = 246
      sign_result = 0;        // положительный знак
    } else if (sign2 == 0) {  // там получается -123-123 = -246
      sign_result = 1;        // отрицательный знак
    }
  } else if (size == 1) {
    for (int i = 0; i < 13; i++) {  // вычитаем из 1-2
      c = subtract_int_int(first.bits[i], second.bits[i], &first.bits[i], c);
    }
    long_result = first;
    if (sign1 == 0 && sign2 == 0) {
      sign_result = 0;  // +
    } else if (sign1 == 1 && sign2 == 1) {
      sign_result = 1;  // -
    }
  } else if (size == 2) {
    for (int i = 0; i < 13; i++) {  //  вычитаем из 2-1
      c = subtract_int_int(second.bits[i], first.bits[i], &second.bits[i], c);
    }
    long_result = second;
    if (sign1 == 1 && sign2 == 1) {
      sign_result = 0;  // +
    } else if (sign1 == 0 && sign2 == 0) {
      sign_result = 1;  // -
    }
  }

  // output_long_decimal(long_result);   // у нас есть результат

  int check_dec =
      check_long_dec(long_result);  // проверяем не переполнен ли лонг дец

  if (check_dec == 0) {  //   не переполнен просто записываем результат
    recording_to_normal_dec(long_result, result, scale_result, sign_result);
    return 0;
  } else if (check_dec > 0) {  // переполнен
    int error = reduction_function(&long_result, &scale_result);
    if (error == 1 && sign_result == 1) {
      error = 2;
    }
    // printf("zasheeeeeeeeeeel\n");
    if (error == 0) {
      recording_to_normal_dec(long_result, result, scale_result, sign_result);
    }
    if (error != 0) {
      for (int i = 0; i < 4; i++) {
        result->bits[i] = 0;
      }
    }
    return error;
  }
  return 0;  // спорно
}

int s21_mul(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result) {  // решить вопрос с ооочень малнеьким числом
  long_decimal a = {0};
  long_decimal b = {0};
  long_decimal c = {0};
  write_to_long_decimal(value_1, &a);  // переписали в лонг дец
  write_to_long_decimal(value_2, &b);
  int sign1 = 0, sign2 = 0, sign_result = 0;
  int scale1 = get_degree(value_1.bits[3], &sign1);
  int scale2 = get_degree(value_2.bits[3], &sign2);

  int scale_result = scale1 + scale2;

  if ((sign1 == 1 && sign2 == 0) || (sign2 == 1 && sign1 == 0)) {
    sign_result = 1;
  }

  // printf("знак и степень 1 = %d %d\n", sign1, scale1);
  // printf("знак и степень 2 = %d %d\n", sign2, scale2);

  mul_long_dec(a, b, &c);  // перемножение длинного децимала
                           // printf("\n");
  // output_long_decimal(c);     // у нас есть терь результат лежащий в длинном
  // децимале
  int num = check_long_dec2(c);

  int check_dec = check_long_dec(c);  // проверяем не переполнен ли лонг дец

  if (check_dec == 0 &&
      scale_result < 29) {  //   не переполнен просто записываем результат
    recording_to_normal_dec(c, result, scale_result, sign_result);
    return 0;
  } else if (check_dec > 0 || scale_result > 28) {  // переполнен
    int error = reduction_function(&c, &scale_result);
    if (error == 1 && sign_result == 1) {
      error = 2;
    }
    if (check_long_dec2(c) == 0 && num > 0) {
      error = 2;
    }
    // printf("zasheeeeeeeeeeel\n");
    if (error == 0) {
      recording_to_normal_dec(c, result, scale_result, sign_result);
    }
    return error;
  }

  return 0;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  long_decimal dividend = {0};
  long_decimal divider = {0};
  long_decimal divider2 = {0};
  long_decimal middle_result = {0};
  long_decimal rest = {0};
  write_to_long_decimal(value_1, &dividend);
  write_to_long_decimal(value_2, &divider);
  int error = 0;
  if (check_long_dec2(divider) > 0 /*&& check_long_dec2(dividend) > 0*/) {
    int sign1 = 0, sign2 = 0, sign_result = 0;
    int scale1 = get_degree(value_1.bits[3], &sign1);
    int scale2 = get_degree(value_2.bits[3], &sign2);

    if ((sign1 == 1 && sign2 == 0) || (sign2 == 1 && sign1 == 0)) {
      sign_result = 1;
    }

    // printf("знак и степень 1 = %d %d\n", sign1, scale1);
    // printf("знак и степень 2 = %d %d\n\n", sign2, scale2);

    if (scale1 != scale2) {  // если разные скейлы
      if (scale1 > scale2) {
        equalize_the_degree(&divider, scale1 - scale2);
      } else if (scale2 > scale1) {
        equalize_the_degree(&dividend, scale2 - scale1);
      }
    }
    divider2 = divider;
    // output_long_decimal(divider);

    // output_long_decimal(divider);

    division_long_dec(dividend, divider, &middle_result,
                      &rest);  //   деление  у нас есть результат

    // output_long_decimal(middle_result);
    // output_long_decimal(rest);

    if (check_long_dec2(rest) != 0) {  // остаток есть
      long_decimal fractional_part = {0};
      int scale_fractional_part = get_fractional_part(
          rest, divider2, &fractional_part);  // получить дробную часть если
                                              // только она не равна 0
      part_consolidation(middle_result, fractional_part, scale_fractional_part,
                         &middle_result);
      // printf("%d\n", scale_fractional_part);
      // output_long_decimal(fractional_part);
      // printf("scale дробной = %d\n", scale_fractional_part);
      // output_long_decimal(fractional_part);
      // output_long_decimal(rest);

      int check_dec =
          check_long_dec(middle_result);  // проверяем не переполнен ли лонг дец

      if (check_dec == 0 &&
          scale_fractional_part <
              29) {  //   не переполнен просто записываем результат
        recording_to_normal_dec(middle_result, result, scale_fractional_part,
                                sign_result);
        // return 0;
      } else if (check_dec > 0 && scale_fractional_part > 28) {  // переполнен
        int error = reduction_function(&middle_result, &scale_fractional_part);
        if (error == 1 && sign_result == 1) {
          error = 2;
        }
        if (check_long_dec2(middle_result) ==
            0) {  // если число вышло 0 но ост был знасчит оно о маленькое
          error = 2;
        }
        // printf("zasheeeeeeeeeeel\n");
        if (error == 0) {
          recording_to_normal_dec(middle_result, result, scale_fractional_part,
                                  sign_result);
        }
        // return error;
      }

    } else if (check_long_dec2(rest) == 0) {     // остатка нет
      if (check_long_dec(middle_result) == 0) {  // переполнения нет
        recording_to_normal_dec(middle_result, result, 0, sign_result);
      } else if (check_long_dec(middle_result) != 0) {  // переполнение мантисы
        if (sign_result == 1) {
          error = 2;
        } else if (sign_result == 0) {
          error = 1;
        }
      }
    }
  } else if (check_long_dec2(divider) == 0) {
    error = 3;
  }
  // else if(check_long_dec2(dividend) == 0){

  // }
  //   if(error != 0){
  //   for(int i = 0 ; i < 4; i++){
  //   result->bits[i] = 0;
  //   }
  // }
  return error;
}

void part_consolidation(long_decimal middle_result,
                        long_decimal fractional_part, int scale_fractional_part,
                        long_decimal *result) {
  long_decimal ten = {0};
  ten.bits[0] = 10;
  long_decimal factor = {0};
  factor.bits[0] = 1;

  for (int i = 0; i < scale_fractional_part; i++) {
    mul_long_dec(factor, ten, &factor);
  }
  mul_long_dec(middle_result, factor, &middle_result);

  add_for_mul(&middle_result, fractional_part);
  // output_long_decimal(middle_result);
  (*result) = middle_result;
}

int get_fractional_part(long_decimal rest, long_decimal divider,
                        long_decimal *result) {
  long_decimal ten = {0};
  ten.bits[0] = 10;
  // long_decimal check = {0};
  int o = 0;
  int scale = 0;
  int drob = 0;
  int pravilo = 0;
  // output_long_decimal(divider);
  for (int i = 1; i < 30; i++) {  // или остаток == 0
    // output_long_decimal(rest);
    // printf("%d\n", i);
    scale = i;
    if (comparison_long_dec(rest, divider) == 2) {
      mul_long_dec(rest, ten, &rest);  // умножаем наше делимое(остаток)
      drob++;
      pravilo++;
      // printf("pravilo %d\n", pravilo);
      if (drob == 1 && pravilo == 1) {
        i--;
      }
      if (drob > 1 || pravilo > 1) {
        mul_long_dec(*result, ten, result);  // умножаем наш результат
        drob = 0;
        // printf("1 if %d  =  %d\n", i, 0);
      }
      // printf("%d\n", 0);
      // printf("%d\n", check_long_dec2(rest));
    } else if (comparison_long_dec(rest, divider) == 1) {
      o = divisor_multiplication(
          &rest, divider);  // подбираем результат для вычитания из остатка и
                            // его число на которе умножили делитель
      mul_long_dec(*result, ten, result);  // умножаем наш результат
      add_number(result, o);
      // printf("%d\n", o);
      // printf("2 if %d  =  %d\n", i, o);
      drob = 0;
      pravilo = 0;
      if (check_long_dec2(rest) == 0) {
        break;
      }
    } else if (comparison_long_dec(rest, divider) == 0) {
      mul_long_dec(*result, ten, result);  // умножаем наш результат
      add_number(result, 1);
      // printf("3 if %d\n", i);
      // printf("%d\n", 1);
      scale = i;
      break;
    }
  }
  return scale;
}

int check_long_dec2(long_decimal a) {
  int check = 0;
  for (int i = 0; i < 14; i++) {
    if (a.bits[i] != 0) {
      check++;
    }
  }
  return check;
}

void add_number(long_decimal *result, int a) {
  long_decimal b = {0};
  b.bits[0] = a;
  add_for_mul(result, b);
}

int divisor_multiplication(long_decimal *rest, long_decimal divider) {
  long_decimal a = {0};
  long_decimal b = {0};
  long_decimal f = {0};
  long_decimal result = {0};
  int num = 0;
  for (int i = 1; i < 10; i++) {
    a.bits[0] = i;
    mul_long_dec(divider, a, &b);  //умножаю делитель на число от 1-9
    if (comparison_long_dec(b, *rest) ==
        1) {  //если число больше значит берем предыдущее
      break;
    } else if (comparison_long_dec(b, *rest) == 2) {
      result = b;
      num = a.bits[0];
      b = f;
    } else if (comparison_long_dec(b, *rest) == 0) {
      result = b;
      num = a.bits[0];
      break;
    }
  }

  int c = 0;

  for (int i = 0; i < 13; i++) {
    c = subtract_int_int(rest->bits[i], result.bits[i], &rest->bits[i], c);
  }

  return num;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int sign1 = 0, sign2 = 0;
  int scale1 = get_degree(value_1.bits[3], &sign1);
  int scale2 = get_degree(value_2.bits[3], &sign2);
  int result = 0;

  long_decimal first = {0};
  long_decimal second = {0};

  write_to_long_decimal(value_1, &first);
  write_to_long_decimal(value_2, &second);

  // output_long_decimal(first);
  // output_long_decimal(second);

  if (scale1 != scale2) {  // если разные скейлы
    if (scale1 > scale2) {
      equalize_the_degree(&second, scale1 - scale2);
    } else if (scale2 > scale1) {
      equalize_the_degree(&first, scale2 - scale1);
    }
  }

  int size = comparison_long_dec(first, second);  // вычисляем какое больше
  int r1 = check_long_dec2(first);
  int r2 = check_long_dec2(second);

  if (r1 == 0 && r2 == 0) {
    result = 0;
  } else if (sign1 == 1 && sign2 == 1) {  // оба отрицательные
    if (size == 1) {
      result = 1;
    } else if (size == 2) {
      result = 0;
    } else if (size == 0) {
      result = 0;
    }
  } else if (sign1 == 0 && sign2 == 0) {  // оба положительные
    if (size == 1) {
      result = 0;
    } else if (size == 2) {
      result = 1;
    } else if (size == 0) {
      result = 0;
    }
  } else if (sign1 == 0 && sign2 == 1) {  // 1 положительное 2 отрицательное
    result = 0;
  } else if (sign1 == 1 && sign2 == 0) {  // 1 отрицательное 2 положительное
    result = 1;
  }
  return result;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int sign1 = 0, sign2 = 0;
  int scale1 = get_degree(value_1.bits[3], &sign1);
  int scale2 = get_degree(value_2.bits[3], &sign2);
  int result = 0;

  long_decimal first = {0};
  long_decimal second = {0};

  write_to_long_decimal(value_1, &first);
  write_to_long_decimal(value_2, &second);

  // output_long_decimal(first);
  // output_long_decimal(second);

  if (scale1 != scale2) {  // если разные скейлы
    if (scale1 > scale2) {
      equalize_the_degree(&second, scale1 - scale2);
    } else if (scale2 > scale1) {
      equalize_the_degree(&first, scale2 - scale1);
    }
  }

  int size = comparison_long_dec(first, second);  // вычисляем какое больше
  int r1 = check_long_dec2(first);
  int r2 = check_long_dec2(second);

  if (r1 == 0 && r2 == 0) {  // если два 0
    result = 1;
  } else if (sign1 == 1 && sign2 == 1) {  // оба отрицательные
    if (size == 1) {                      //    первое больше
      result = 1;
    } else if (size == 2) {  //  второе больше
      result = 0;
    } else if (size == 0) {  //  числа равны
      result = 1;
    }
  } else if (sign1 == 0 && sign2 == 0) {  // оба положительные
    if (size == 1) {                      //  первое больше
      result = 0;
    } else if (size == 2) {  //  второе больше
      result = 1;
    } else if (size == 0) {  //  числа равны
      result = 1;
    }
  } else if (sign1 == 0 && sign2 == 1) {  // 1 положительное 2 отрицательное
    result = 0;
  } else if (sign1 == 1 && sign2 == 0) {  // 1 отрицательное 2 положительное
    result = 1;
  }
  return result;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int sign1 = 0, sign2 = 0;
  int scale1 = get_degree(value_1.bits[3], &sign1);
  int scale2 = get_degree(value_2.bits[3], &sign2);
  int result = 0;

  long_decimal first = {0};
  long_decimal second = {0};

  write_to_long_decimal(value_1, &first);
  write_to_long_decimal(value_2, &second);

  // output_long_decimal(first);
  // output_long_decimal(second);

  if (scale1 != scale2) {  // если разные скейлы
    if (scale1 > scale2) {
      equalize_the_degree(&second, scale1 - scale2);
    } else if (scale2 > scale1) {
      equalize_the_degree(&first, scale2 - scale1);
    }
  }

  int size = comparison_long_dec(first, second);  // вычисляем какое больше
  int r1 = check_long_dec2(first);
  int r2 = check_long_dec2(second);

  if (r1 == 0 && r2 == 0) {  // если два 0
    result = 0;
  } else if (sign1 == 1 && sign2 == 1) {  // оба отрицательные
    if (size == 1) {                      //    первое больше
      result = 0;
    } else if (size == 2) {  //  второе больше
      result = 1;
    } else if (size == 0) {  //  числа равны
      result = 0;
    }
  } else if (sign1 == 0 && sign2 == 0) {  // оба положительные
    if (size == 1) {                      //  первое больше
      result = 1;
    } else if (size == 2) {  //  второе больше
      result = 0;
    } else if (size == 0) {  //  числа равны
      result = 0;
    }
  } else if (sign1 == 0 && sign2 == 1) {  // 1 положительное 2 отрицательное
    result = 1;
  } else if (sign1 == 1 && sign2 == 0) {  // 1 отрицательное 2 положительное
    result = 0;
  }
  return result;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int sign1 = 0, sign2 = 0;
  int scale1 = get_degree(value_1.bits[3], &sign1);
  int scale2 = get_degree(value_2.bits[3], &sign2);
  int result = 0;

  long_decimal first = {0};
  long_decimal second = {0};

  write_to_long_decimal(value_1, &first);
  write_to_long_decimal(value_2, &second);

  // output_long_decimal(first);
  // output_long_decimal(second);

  if (scale1 != scale2) {  // если разные скейлы
    if (scale1 > scale2) {
      equalize_the_degree(&second, scale1 - scale2);
    } else if (scale2 > scale1) {
      equalize_the_degree(&first, scale2 - scale1);
    }
  }

  int size = comparison_long_dec(first, second);  // вычисляем какое больше
  int r1 = check_long_dec2(first);
  int r2 = check_long_dec2(second);

  if (r1 == 0 && r2 == 0) {  // если два 0
    result = 1;
  } else if (sign1 == 1 && sign2 == 1) {  // оба отрицательные
    if (size == 1) {                      //    первое больше
      result = 0;
    } else if (size == 2) {  //  второе больше
      result = 1;
    } else if (size == 0) {  //  числа равны
      result = 1;
    }
  } else if (sign1 == 0 && sign2 == 0) {  // оба положительные
    if (size == 1) {                      //  первое больше
      result = 1;
    } else if (size == 2) {  //  второе больше
      result = 0;
    } else if (size == 0) {  //  числа равны
      result = 1;
    }
  } else if (sign1 == 0 && sign2 == 1) {  // 1 положительное 2 отрицательное
    result = 1;
  } else if (sign1 == 1 && sign2 == 0) {  // 1 отрицательное 2 положительное
    result = 0;
  }
  return result;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int sign1 = 0, sign2 = 0;
  int scale1 = get_degree(value_1.bits[3], &sign1);
  int scale2 = get_degree(value_2.bits[3], &sign2);
  int result = 0;

  long_decimal first = {0};
  long_decimal second = {0};

  write_to_long_decimal(value_1, &first);
  write_to_long_decimal(value_2, &second);

  // output_long_decimal(first);
  // output_long_decimal(second);

  if (scale1 != scale2) {  // если разные скейлы
    if (scale1 > scale2) {
      equalize_the_degree(&second, scale1 - scale2);
    } else if (scale2 > scale1) {
      equalize_the_degree(&first, scale2 - scale1);
    }
  }

  int size = comparison_long_dec(first, second);  // вычисляем какое больше
  int r1 = check_long_dec2(first);
  int r2 = check_long_dec2(second);

  if (r1 == 0 && r2 == 0) {  // если два 0
    result = 1;
  } else if (sign1 == 1 && sign2 == 1) {  // оба отрицательные
    if (size == 1) {                      //    первое больше
      result = 0;
    } else if (size == 2) {  //  второе больше
      result = 0;
    } else if (size == 0) {  //  числа равны
      result = 1;
    }
  } else if (sign1 == 0 && sign2 == 0) {  // оба положительные
    if (size == 1) {                      //  первое больше
      result = 0;
    } else if (size == 2) {  //  второе больше
      result = 0;
    } else if (size == 0) {  //  числа равны
      result = 1;
    }
  } else if (sign1 == 0 && sign2 == 1) {  // 1 положительное 2 отрицательное
    result = 0;
  } else if (sign1 == 1 && sign2 == 0) {  // 1 отрицательное 2 положительное
    result = 0;
  }
  return result;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  int sign1 = 0, sign2 = 0;
  int scale1 = get_degree(value_1.bits[3], &sign1);
  int scale2 = get_degree(value_2.bits[3], &sign2);
  int result = 0;

  long_decimal first = {0};
  long_decimal second = {0};

  write_to_long_decimal(value_1, &first);
  write_to_long_decimal(value_2, &second);

  // output_long_decimal(first);
  // output_long_decimal(second);

  if (scale1 != scale2) {  // если разные скейлы
    if (scale1 > scale2) {
      equalize_the_degree(&second, scale1 - scale2);
    } else if (scale2 > scale1) {
      equalize_the_degree(&first, scale2 - scale1);
    }
  }

  int size = comparison_long_dec(first, second);  // вычисляем какое больше
  int r1 = check_long_dec2(first);
  int r2 = check_long_dec2(second);

  if (r1 == 0 && r2 == 0) {  // если два 0
    result = 0;
  } else if (sign1 == 1 && sign2 == 1) {  // оба отрицательные
    if (size == 1) {                      //    первое больше
      result = 1;
    } else if (size == 2) {  //  второе больше
      result = 1;
    } else if (size == 0) {  //  числа равны
      result = 0;
    }
  } else if (sign1 == 0 && sign2 == 0) {  // оба положительные
    if (size == 1) {                      //  первое больше
      result = 1;
    } else if (size == 2) {  //  второе больше
      result = 1;
    } else if (size == 0) {  //  числа равны
      result = 0;
    }
  } else if (sign1 == 0 && sign2 == 1) {  // 1 положительное 2 отрицательное
    result = 1;
  } else if (sign1 == 1 && sign2 == 0) {  // 1 отрицательное 2 положительное
    result = 1;
  }
  return result;
}

// int s21_from_int_to_decimal(int src, s21_decimal *dst) {
//   int sign = 0;
//   if (src < 0) { // число отрицательное
//     sign = 1;
//     src = src * -1;
//   }
//   dst->bits[0] = src;
//   put_degree(&dst->bits[3], 0, sign);
//   return 0;
// }

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int result = 0;
  if (src > INT_MAX || src < INT_MIN) result = 1;
  if (dst && !result) {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    if (src < 0) {
      s21_negate(*dst, dst);
      src = -src;
    }
    dst->bits[0] = src;
  } else {
    result = 1;
  }
  return result;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int sign = 0;
  int error = 0;
  if (dst == NULL) {
    error = 1;
  } else {
    int scale = get_degree(src.bits[3], &sign);
    // printf("sign = %d scale = %d \n", sign, scale);
    if (scale != 0) {  //если скейл есть то надо его убрать
      long_decimal first = {0};
      long_decimal ten = {0};
      ten.bits[0] = 10;
      write_to_long_decimal(src, &first);
      scale_ten(&ten, scale);
      division_long_dec(first, ten, &first, &ten);
      // output_long_decimal(first);
      recording_to_normal_dec(first, &src, 0, sign);
      // output_all_decimal(src);
    }
    if (src.bits[2] == 0 && src.bits[1] == 0 &&
        s21_get_bit(src.bits[0], 31) == 0) {
      (*dst) = src.bits[0];
      if (sign == 1) {
        (*dst) = (*dst) * -1;
      }
    } else {
      error = 1;
    }
  }
  return error;
}

int get_first_non_zero_bit_for_decimal(s21_decimal decimal) {  // notme
  int result = 0;

  for (int i = 95; i >= 0; i--) {
    if (get_bit(decimal, i)) {
      result = i;
      break;
    }
  }
  return result;
}

int get_sign(s21_decimal decimal) {  // notme
  return get_bit(decimal, 127);
}

int get_bit(s21_decimal decimal, int bit_number) {  // notme
  int result = -1;
  int int_number = bit_number / 32;
  bit_number %= 32;
  result = ((1 << bit_number) & decimal.bits[int_number]) >> bit_number;
  return result;
}

int get_scale(s21_decimal decimal) {  // notme
  return (decimal.bits[3] & (0xFF << 16)) >> 16;
}

void scale_ten(long_decimal *a, int b) {
  long_decimal ten = {0};
  ten.bits[0] = 10;
  long_decimal one = {0};
  one.bits[0] = 1;
  for (int i = 1; i < b + 1; i++) {
    mul_long_dec(one, ten, &one);
  }
  *a = one;
  // output_long_decimal(*a);
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int result = 0;
  if (isnan(src) || isinf(src) || src == FLT_MIN || src == -FLT_MIN ||
      src == FLT_MAX || src == -FLT_MAX) {
    result = 1;
  }
  if (dst && !result) {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    int sign = 0;
    if (src < 0) {
      sign = 1;
      src = -(src);
    }
    int new = (int)src;
    int exp = 0;
    while (src - ((float)new / (int)(pow(10, exp))) != 0) {
      exp++;
      new = src *(int)(pow(10, exp));
    }
    s21_from_int_to_decimal(new, dst);

    if (sign) {
      s21_negate(*dst, dst);
    }
    dst->bits[3] += exp << 16;

  } else {
    result = 1;
  }
  return result;
}

// int s21_from_float_to_decimal(float src, s21_decimal *dst) {
//   if(isnan(src) || isinf(src) || src == FLT_MIN || src == -FLT_MIN || src ==
//   FLT_MAX || src == -FLT_MAX){
//     return 1;
//   }
//   else{
//     int scale = 7;
//   int sign = 0;
//   if (src < 0) {
//     src = src * -1.0;
//     sign = 1;
//   }
//   long long b = src; // целая часть
//   src = src - b;
//   // printf("целая часть %d\n", b);
//   // printf("%.7lf\n", src);
//   char buf[20];
//   sprintf(buf, "%.7lf", src);
//   // printf("%s\n", buf);
//   int part_float = 0;
//   for (int i = 2; i < 9; i++) {
//     part_float = part_float * 10;
//     part_float = part_float + (buf[i] - 48);
//   }
//    //printf("   %d\n", part_float);
//   long_decimal ten = {0};
//   ten.bits[0] = 10000000;
//   long_decimal abc = {0};
//   abc.bits[0] = b;
//   mul_long_dec(abc, ten, &abc);
//   ten.bits[0] = part_float;
//   add_for_mul(&abc, ten);
//   // output_long_decimal(abc);
//   long_decimal ten2 = {{10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
//   long_decimal result = {{10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
//   long_decimal rest = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
//   //output_long_decimal(abc);
//   for(int i = 7; i > 0; i--){
//     division_long_dec(abc, ten2 , &result, &rest);
//     if (check_long_dec2(rest) == 0){
//       abc = result;
//       scale--;
//     }
//     else{
//       break;
//     }
//   }
//   recording_to_normal_dec(abc, dst, scale, sign);
//   return 0;
//   }
// }

// int s21_from_decimal_to_float(s21_decimal src, float *dst) {
//   int sign = 0;
//   int scale = get_degree(src.bits[3], &sign);
//   long_decimal abc = {0};
//   long_decimal ten = {0};
//   ten.bits[0] = 10000000;
//   long_decimal rest = {0};
//   write_to_long_decimal(src, &abc);
//   if (scale > 7) {
//     abbreviation_float(&abc, scale - 7);
//     division_long_dec(abc, ten, &abc, &rest);
//     //*(dst)=abc.bits[0];
//     float fl = rest.bits[0] / 10000000.0;
//     *(dst) = abc.bits[0] + fl;
//     // printf("%.7lf\n", fl);
//   } else {
//     long_decimal del = {0};
//     scale_ten(&del, scale);
//     division_long_dec(abc, del, &abc, &rest);
//     *(dst) = abc.bits[0];
//     float fl2 = 1.0;
//     for (int i = 0; i < scale; i++) {
//       fl2 = fl2 * 10.0;
//     }
//     *(dst) = *(dst) + (rest.bits[0] / fl2);
//   }
//   if (sign == 1) {
//     *(dst) = *(dst) * -1.0;
//   }
//   // output_long_decimal(abc);
//   // output_long_decimal(rest);
//   return 0;
// }

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int result = 0;
  if (dst == NULL) {
    result = 1;
  } else {
    *dst = 0;

    for (int i = 0; i < 96; i++) {
      if (get_bit(src, i)) {
        *dst += pow(2, i);
      }
    }

    *dst = *dst * pow(10, -get_scale(src));

    if (get_sign(src)) {
      *dst = -*dst;
    }
  }
  return result;
}

// void abbreviation_float(long_decimal *result, int a) {
//   long_decimal ten = {0};
//   scale_ten(&ten, a);
//   division_long_dec(*result, ten, result, &ten);
// }

int s21_floor(s21_decimal value, s21_decimal *result) {
  long_decimal a = {0};
  long_decimal rest = {0};
  long_decimal ten = {0};
  ten.bits[0] = 10;
  long_decimal one = {0};
  one.bits[0] = 1;
  int sign = 1;
  int scale = get_degree(value.bits[3], &sign);
  write_to_long_decimal(value, &a);

  for (int i = 0; i < scale; i++) {
    division_long_dec(a, ten, &a, &rest);
  }

  if (sign == 1) {
    if (rest.bits[0] > 0) {
      add_for_mul(&a, one);
    }
  }
  recording_to_normal_dec(a, result, 0, sign);
  return 0;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  long_decimal a = {0};
  long_decimal rest = {0};
  long_decimal ten = {0};
  ten.bits[0] = 10;
  long_decimal one = {0};
  one.bits[0] = 1;
  int sign = 1;
  int scale = get_degree(value.bits[3], &sign);
  write_to_long_decimal(value, &a);

  for (int i = 0; i < scale; i++) {
    division_long_dec(a, ten, &a, &rest);
  }

  if (rest.bits[0] > 4) {
    add_for_mul(&a, one);
  }

  recording_to_normal_dec(a, result, 0, sign);
  return 0;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  long_decimal a = {0};
  long_decimal rest = {0};
  long_decimal ten = {0};
  ten.bits[0] = 10;
  int sign = 1;
  int scale = get_degree(value.bits[3], &sign);
  write_to_long_decimal(value, &a);

  for (int i = 0; i < scale; i++) {
    division_long_dec(a, ten, &a, &rest);
  }

  // output_long_decimal(a);

  recording_to_normal_dec2(a, result, 0, sign);
  if (scale > 28) {
    return 1;
  }
  return 0;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  result->bits[0] = value.bits[0];
  result->bits[1] = value.bits[1];
  result->bits[2] = value.bits[2];
  result->bits[3] = value.bits[3];

  if (s21_get_bit(value.bits[3], 31) == 1) {
    change_bit_0(&result->bits[3], 31);
  }
  if (s21_get_bit(value.bits[3], 31) == 0) {
    change_bit_1(&result->bits[3], 31);
  }
  return 0;
}
