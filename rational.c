#include <stdlib.h>
#include <ctype.h>
#include "rational.h"

/* Intermediate API */
rational _rational_add(rational a, rational b);
rational _rational_sub(rational a, rational b);
rational _rational_mul(rational a, rational b);
rational _rational_div(rational a, rational b);
rational _rational_simplify(rational frac);

/*
 ******************************* Public API ***********************************

 ******************************************************************************
 */

/*
 * ------------------------- Rational arithmetic ------------------------------
 */

/* Add two rationals: return frac1 + frac2 */
rational rational_add(rational frac1, rational frac2){
  return _rational_add(frac1, frac2);
}

/* Subtract two rationals: return frac1 - frac2 */
rational rational_sub(rational frac1, rational frac2){
  return _rational_sub(frac1, frac2);
}

/* Multiply two rationals: return frac1 x frac2 */
rational rational_mul(rational frac1, rational frac2){
  return _rational_mul(frac1, frac2);
}

/* Divide two rationals: return frac1 / frac2 */
rational rational_div(rational frac1, rational frac2){
  return _rational_div(frac1, frac2);
}

/* Simlify a rational */
rational rational_simplify(rational frac){
  return _rational_simplify(frac);
}

/*
 * ------------------------- Rational Functions --------------------------------
 */

/*Used to check if a number could be rational*/
int isRational(char *argv){
    int i = 0;
    if (argv[strlen(argv)-1] == '/'){
      return 1;
    }
    else{
      //checks if a / exists in the argument
      for( i = 0; i<strlen(argv) && argv[i] != '/' ; ++i){}
      if(i<strlen(argv)){
          return 0;
				}
      return 1;
    }
    return 1;
  }

/*Completes the check if an argument is rational*/
rational rational_true(char *argv){
  char *endptr; //pointer used to find the end of string in strtol
  char *ptr = strchr(strrchr(argv, '/'), '/') + 1; //getting the denominator
  char *token = strtok(argv, "/"); // getting the numerator
  //if statement checks if the numerator and denominator are digits
  if ((strtol(token, &endptr, 10) && *endptr == '\0') && (strtol(ptr, &endptr, 10) && *endptr == '\0')){
    return rational_frac(token, ptr);
  }
  else{
    //either the num or denom are not integers
    fprintf(stderr, "Invalid token \"%s/%s\"\n", token, ptr);
    exit(1);
  }
}

/*Converts the argument into a rational number*/
rational rational_frac(char *token, char *ptr){
  bigint num = bigint_from_string_d(token);
  bigint denom = bigint_from_string_d(ptr);
  if (bigint_le(denom, bigint_from_string_d("0"))){ //if the denominator is 0
    //print error for invalid token
    fprintf(stderr, "Invalid token \"");
    bigint_print_d(num, stderr);
    fprintf(stderr, "/");
    bigint_print_d(denom, stderr);
    fprintf(stderr, "\"\n");
    exit(1);
  }
  //Join the numerator and denominator into a fraction
  else{
    rational fraction = rational_from_bigint(num, denom);
    return fraction;
  }
}

/*used to print rational numbers, it also checks if the number is being divided
by one and just prints the numbertor. the state arugment is used to either print
  using stdout or stderr.
  * 1 for stdout
  * 0 for stderr*/
void rational_print(rational fraction, int state){
  //if denom is 1 and stdoud
  if (bigint_eq(fraction.denominator,bigint_from_string_d("1")) && state == 1){
    bigint_print_d(fraction.numerator, stdout); //uses bigint to print
    fputc('\n', stdout);
  }
  //if denom is 1 and stderr
  else if(bigint_eq(fraction.denominator,bigint_from_string_d("1")) && state == 0){
    bigint_print_d(fraction.numerator, stderr);
  }
  /*If the print is part of stderr we cant print a new line to allow for
  quotation marks in our error messages*/
  else if(state == 0){
    bigint_print_d(fraction.numerator, stdout);
    fputc('/', stdout);
    bigint_print_d(fraction.denominator, stdout);
  }
  else{
    bigint_print_d(fraction.numerator, stdout);
    fputc('/', stdout);
    bigint_print_d(fraction.denominator, stdout);
    fputc('\n', stdout);
  }
}

/*Converts bigints into rationals, more specifically the numerator and denom
this makes use of our struct variables being bitints*/
rational rational_from_bigint(bigint num, bigint denom){
  rational frac;
  frac.numerator = num;
  frac.denominator = denom;
  return frac;
}

/*Add two rational numbers together*/
rational _rational_add(rational a, rational b){
  rational sum;
  /* uses the bigint functions to manipulate the numerator and denom separately*/
  /*Calculate the numberator by doing numerator1*denominator2 + numerator2 *denominator1
  for the denominators, multiply them together. We are calculating the common denominator
  and finding their respective numerators*/
  sum.numerator = bigint_add((bigint_mul(a.numerator, b.denominator)), (bigint_mul(a.denominator, b.numerator)));
  sum.denominator = bigint_mul(a.denominator, b.denominator);
  return sum;
}

/*Subtracts two rational numbers*/
rational _rational_sub(rational a, rational b){
    rational sum;
    /*Numerator: numerator1 * denom2 - numerator2* denom1
      Denominator: denominator1* denominator2*/
    sum.numerator = bigint_sub((bigint_mul(a.numerator, b.denominator)), (bigint_mul(a.denominator, b.numerator)));
    sum.denominator = bigint_mul(a.denominator, b.denominator);
    return sum;
}

/*Multipling two rational numbers*/
rational _rational_mul(rational a, rational b){
    rational prod;
    /*Numerator: numerator1 * numerator2
      Denominator: denominator1* denominator2*/
    prod.numerator = bigint_mul(a.numerator, b.numerator);
    prod.denominator = bigint_mul(a.denominator, b.denominator);
    return prod;
}

/*Dividing two rational numbers*/
rational _rational_div(rational a, rational b){
    rational div;
    /*Numerator: numerator1 * denominator2
      Denominator: denominator1 * numerator2*/
    div.numerator = bigint_mul(a.numerator, b.denominator);
    div.denominator = bigint_mul(a.denominator, b.numerator);
    //check for 0 division below
    if(bigint_eq(div.denominator, bigint_from_string_d("0"))){
      fprintf(stderr, "Zero division in ");
   	  bigint_print_d(div.numerator, stderr);
   	  fprintf(stderr, " / 0\n");
   	  exit(1);
    }
    else{
      //simplify the fraction
      return rational_simplify(div);
    }
}

/*The function below is used to simplify fractions, usually the modulus function
would be used for this. But because we are using bigints, the modulus function
was unusable. Therefore a method to find the greatest common divisor was used,
which imitates the modulus function*/
rational _rational_simplify(rational frac){
  rational simplifiedFrac;
  /*storing the sign of the bigints using the sign bit*/
  int sign1 = frac.numerator.s;
  int sign2 = frac.denominator.s;
  /*Setting the numerator and denominator values to positive*/
  frac.numerator.s=0;
  frac.denominator.s=0;
  bigint a = frac.numerator;
  bigint b = frac.denominator;
  bigint c; //place holding variable
  /*Loop until remainder = 0*/
  while(!bigint_eq(b, bigint_from_string_d("0"))){
    c = b;
    //finding the reminder from the division
    b = bigint_sub( a, ( bigint_mul( bigint_div(a,b),b)));
    a = c;
  }
  /*If the signs are different, reassign the signs to the fractions
  only need this cond as if the signs are both negative, they cancel*/
  if(sign1 != sign2){
    frac.numerator.s = sign1;
    frac.denominator.s = sign2;
   }
   //divide numberator and denominator by the gcd
   simplifiedFrac.numerator = bigint_div(frac.numerator, a);
   simplifiedFrac.denominator = bigint_div(frac.denominator, a);
   return simplifiedFrac;

}
