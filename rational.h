#include <stdio.h>
#include <string.h>
#include "bigint.h"

/*
 * Rational struct members
 *
 * numerator: numerator of the rational number
 * denominator: denominator of the rational number
 *
 */

struct _rational {
    bigint numerator;
    bigint denominator;
}; typedef struct _rational rational;


/* Add two rationals: return frac1 + frac2 */
rational rational_add(rational a, rational b);

/* Subtract two rationals: return frac1 - frac2 */
rational rational_sub(rational a, rational b);

/* Multiply two rationals: return frac1 x frac2 */
rational rational_mul(rational a, rational b);

/* Divide two rationals: return frac1 / frac2 */
rational rational_div(rational a, rational b);

/* Simlify a rational */
rational rational_simplify(rational frac);

/*Used to check if a number could be rational*/
int isRational(char *argv);

/*Completes the check if an argument is rational*/
rational rational_true(char *argv);

/*Converts the argument into a rational number*/
rational rational_frac(char *token, char *ptr);

/*used to print rational numbers*/
void rational_print(rational fraction, int state);

/*Converts bigints to rational*/
rational rational_from_bigint(bigint num, bigint denom);
