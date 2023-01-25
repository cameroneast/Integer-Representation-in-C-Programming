#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// BEGIN STRINGBUILDER IMPLEMENTATION

// This code is a very rudimentary stringbuilder-like implementation
// To create a new stringbuilder, use the following line of code
//
//     stringbuilder sb = new_sb();
//
// If you want to append a character to the stringbuilder, use the
// following line of code. Replace whatever character you want to
// append where the 'a' is.
//
//     sb_append_char(sb, 'a');
//
// Though there are some other functions that might be useful to you,
// the driver code provided uses the functions, so there is no need
// to use them manually.

typedef struct {
  char** cars;
  size_t* len;
  size_t* alloc_size;
} stringbuilder;

stringbuilder new_sb() {
  stringbuilder sb;
  sb.cars = malloc(sizeof(char*));
  *sb.cars = malloc(8*sizeof(char));
  (*sb.cars)[0] = 0;
  sb.len = malloc(sizeof(size_t));
  *sb.len = 0;
  sb.alloc_size = malloc(sizeof(size_t));
  *sb.alloc_size = 8;
  return sb;
}

void sb_append(stringbuilder sb, char a) {
  int len = *sb.len;
  if (len >= (*sb.alloc_size)-1) {
    *sb.alloc_size = (*sb.alloc_size)*2;
    char* newcars = malloc((*sb.alloc_size)*sizeof(char));
    for (int i = 0; i < *sb.len; i++) {
      newcars[i] = (*sb.cars)[i];
    }
    free(*sb.cars);
    (*sb.cars) = newcars;
  }
  (*sb.cars)[len] = a;
  len++;
  (*sb.cars)[len] = 0;
  *sb.len = len;
}

void delete_sb(stringbuilder sb) {
  free(*sb.cars);
  free(sb.cars);
  free(sb.len);
  free(sb.alloc_size);
}

bool sb_is_equal(stringbuilder sb1, stringbuilder sb2) {
  if (*sb1.len != *sb2.len)
    return false;
  for (int i = 0; i < *sb1.len; i++) {
    if ((*sb1.cars)[i] != (*sb2.cars)[i])
      return false;
  }
  return true;
}

void print_sb(const stringbuilder sb) {
  printf("%s", *sb.cars);
}

// END STRINGBUILDER IMPLEMENTATION

// ============================================================

// Write your solutions to the tasks below

const unsigned UNS_MAX = -1;      // 1111...
const unsigned UNS_MIN = 0;       // 0000...
const int INT_MAX = UNS_MAX >> 1; // 0111...
const int INT_MIN = ~INT_MAX;     // 1000...

// Task 1

// For this function, you must return an integer holding the value
// x+1, however you may not use any constants or the symbol '+'
// anywhere in your solution. This means that
//
//     return x - (-1);
//
// is not a valid soltion, because it uses the constant -1.
//
// Hint: Consider what internally happens when you do -x.
int plus_one(int x) {
  return -~x;
}

// Task 2

// For this function, you must build a string that when printed,
// will output the entire binary representation of the integer x,
// no matter how many bits an integer is. You may NOT use
// division (/) or mod (%) awhere in your code, and should
// instead rely on bitwise operations to read the underlying binary
// representation of x.
stringbuilder get_bin_1(int x) {
  stringbuilder sb = new_sb();
  unsigned divisor = INT_MIN;
  while (divisor > 0) {
    if ((x & divisor))
      sb_append(sb, '1');
    else
      sb_append(sb, '0');
    x>>1;
    divisor >>= 1;
  }
  return sb;
}

// Task 3

// For this function, you must return the largest power of 2 that
// is less than or equal to x (which will be positive). You may
// not use multiplication or some sort of power function to do this,
// and should instead rely on bitwise operations and the underlying
// binary representation of x. If x is 0, then you should return 0.
unsigned largest_po2_le(unsigned x) {
  unsigned lpo2 = 0;
  unsigned po2 = 1;
  while (po2 <= x) {
    lpo2 = po2;
    po2 = po2<<1;
  }
  return lpo2;
}

// Task 4

// For this function, you must build a string that when printed,
// will output the binary representation of the integer x without
// leading zeroes, using a similar method as you did above. If x
// is negative, then the string should start with '-' and be
// followed by the binary for the positive version of the number.
// So if x is -5, then the string should be '-101', and
// if x is 9, then the string should be '1001'. The same
// restrictions from Task 2 apply.
// 
// Hint: It may be useful to use the function from Task 3, and
// borrow concepts from Task 2.
stringbuilder get_bin_2(int x) {
  stringbuilder sb = new_sb();
  if (x < 0) {
    sb_append(sb, '-');
    x = -x;
  }
  unsigned divisor = largest_po2_le(x);
  if(divisor == 0)
    sb_append(sb, '0');
  while (divisor > 0) {
    if ((x & divisor))
      sb_append(sb, '1');
    else
      sb_append(sb, '0');
    x>>1;
    divisor >>= 1;
  }
  return sb;
}

/************************************************* 
 *                                               *
 *  DO NOT MODIFY THE CODE BELOW FOR SUBMISSION  *
 *                                               *
 *************************************************/
// If this code is discovered to be maliciously modified
// at grading (e.g. making it always output 'TESTS PASSED'),
// you will recieve a 0 for the assignment.

// You may read this code if you want, but it is not necessary
// for the assignment

int task_1_check(int x) {
  return x + 1;
}

stringbuilder task_2_check(int x) {
  stringbuilder sb = new_sb();
  unsigned divisor = INT_MIN;
  while (divisor > 0) {
    if ((x / divisor) > 0)
      sb_append(sb, '1');
    else
      sb_append(sb, '0');
    x %= divisor;
    divisor /= 2;
  }
  return sb;
}

unsigned task_3_check(unsigned x) {
  unsigned lpo2 = 0;
  unsigned po2 = 1;
  while (po2 <= x) {
    lpo2 = po2;
    po2 = 2*po2;
  }
  return lpo2;
}

stringbuilder task_4_check(int x) {
  stringbuilder sb = new_sb();
  if (x < 0) {
    sb_append(sb, '-');
    x = -x;
  }
  unsigned divisor = largest_po2_le(x);
  if (divisor == 0) {
    sb_append(sb, '0');
    return sb;
  }
  while (divisor > 0) {
    if ((x / divisor) > 0)
      sb_append(sb, '1');
    else
      sb_append(sb, '0');
    x %= divisor;
    divisor /= 2;
  }
  return sb;
}

int main(void) {
  int x;
  printf("Input a number (1234 to exit): ");
  scanf("%d", &x);
  while (x != 1234) {
    // Task 1
    int task_1_ans = task_1_check(x);
    int task_1 = plus_one(x);
    printf("\n");
    if (task_1 != task_1_ans)
      printf("FAILED");
    else
      printf("PASSED");
    printf(": PLUS ONE (Task 1)\n");
    printf("Expected: %d\n", task_1_ans);
    printf("     Got: %d\n", task_1);

    // Task 2
    stringbuilder task_2_ans = task_2_check(x);
    stringbuilder task_2 = get_bin_1(x);
    printf("\n");
    if (!sb_is_equal(task_2, task_2_ans))
      printf("FAILED");
    else
      printf("PASSED");
    printf(": GET BINARY 1 (Task 2)\n");
    printf("Expected: \"%s\"\n", *task_2_ans.cars);
    printf("     Got: \"%s\"\n", *task_2.cars);
    delete_sb(task_2_ans);
    delete_sb(task_2);

    // Task 3
    printf("\n");
    if (x >= 0) {
      int task_3_ans = task_3_check(x);
      int task_3 = largest_po2_le(x);
      if (task_3 != task_3_ans) 
        printf("FAILED");
      else
        printf("PASSED");
      printf(": LARGEST PO2 LESS THAN OR EQUAL TO (Task 3)\n");
      printf("Expected: %u\n", task_3_ans);
      printf("     Got: %u\n", task_3);
    }
    else {
      printf("SKIPPED: LARGEST PO2 LESS THAN OR EQUAL TO (Task 3)\n");
      printf("\tNumber input was negative.\n");
    }

    // Task 4
    stringbuilder task_4_ans = task_4_check(x);
    stringbuilder task_4 = get_bin_2(x);
    printf("\n");
    if (!sb_is_equal(task_4, task_4_ans))
      printf("FAILED");
    else
      printf("PASSED");
    printf(": GET BINARY 2 (Task 4)\n");
    printf("Expected: \"%s\"\n", *task_4_ans.cars);
    printf("     Got: \"%s\"\n", *task_4.cars);
    delete_sb(task_4_ans);
    delete_sb(task_4);


    printf("\n");
    printf("Input a number (1234 to exit): ");
    scanf("%d", &x);
  }
}