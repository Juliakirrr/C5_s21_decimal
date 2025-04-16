
#ifndef DECIMAL_H
#define DECIMAL_H

#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  unsigned bits[4];
} s21_decimal;

typedef struct {
  unsigned bits[14];
} long_decimal;

// ---------- Arithmetic Operators ----------
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// ---------- Comparison Operators ----------
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

// ---------- Convertors and parsers ----------
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// ---------- Another functions ----------
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// -----------Helpers------------------
int s21_get_bit(int number, int position);
void change_bit_1(unsigned *number, int position);
void change_bit_0(unsigned *number, int position);
void output(int a);
int get_degree(unsigned a, int *sign);
void put_degree(unsigned *bit_0, int degree, int sign);
int add_int_int(unsigned a, unsigned b, unsigned *result, int c);
int subtract_int_int(unsigned a, unsigned b, unsigned *result, int c);
void output_all_decimal(s21_decimal a);
void multiplication_10(s21_decimal a, s21_decimal *result);
void shift_recording(s21_decimal a, s21_decimal *num2, int shift);
void output_long_decimal(long_decimal a);
void print_longlong(unsigned long long value);
void write_to_long_decimal(s21_decimal a, long_decimal *b);
void mul_long_dec(long_decimal a, long_decimal b, long_decimal *c);
void shift_left_long_dec(long_decimal a, long_decimal *num1);
int position_long_dec(int i, int j);
void record_with_shift(long_decimal a, long_decimal *a_shift, int shift);
void add_for_mul(long_decimal *result, long_decimal a);
int comparison_long_dec(long_decimal a, long_decimal b);
void division_long_dec(long_decimal dividend, long_decimal divider,
                       long_decimal *result, long_decimal *rest);
void search_divider(long_decimal divider, long_decimal dividend,
                    long_decimal *two_and_divider, long_decimal *result);
void equalize_the_degree(long_decimal *a, int degree);
int check_long_dec(long_decimal a);
void recording_to_normal_dec(long_decimal long_result, s21_decimal *result,
                             int scale_result, int sign_result);
int reduction_function(long_decimal *long_result, int *scale_result);
void div_ten_add_one(long_decimal *a);
int get_fractional_part(long_decimal rest, long_decimal divider,
                        long_decimal *result);
int divisor_multiplication(long_decimal *rest, long_decimal divider);
void add_number(long_decimal *result, int a);
int check_long_dec2(long_decimal a);
void part_consolidation(long_decimal middle_result,
                        long_decimal fractional_part, int scale_fractional_part,
                        long_decimal *result);
void scale_ten(long_decimal *a, int b);
void abbreviation_float(long_decimal *result, int a);
void recording_to_normal_dec2(long_decimal long_result, s21_decimal *result,
                              int scale_result, int sign_result);

int get_scale(s21_decimal decimal);
int get_bit(s21_decimal decimal, int bit_number);
int get_sign(s21_decimal decimal);

int get_first_non_zero_bit_for_decimal(s21_decimal decimal);

#endif