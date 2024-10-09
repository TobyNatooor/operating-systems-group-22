#include "list.h"
#include <unistd.h>

#include "io.h"

/* Reads next char from stdin. If no more characters, it returns EOF */
int read_char() {
  char c;
  ssize_t size = read(0, &c, 1);
  if (size == -1)
    return EOF;
  return c;
}

/* Writes c to stdout.  If no errors occur, it returns 0, otherwise EOF */
int write_char(char c) {
  ssize_t result = write(1, &c, 1);
  if (result == -1)
    return EOF;
  return 0;
}

/* Writes a null-terminated string to stdout.  If no errors occur, it returns 0,
 * otherwise EOF */
int write_string(char *s) {
  if (s == NULL)
    return EOF;
  while (*s != '\0') {
    ssize_t result = write_char(*s);
    if (result == -1)
      return EOF;
    s = s + 1;
  }
  return 0;
}

/* Writes n to stdout (without any formatting).
 * If no errors occur, it returns 0, otherwise EOF
 */
int write_int(int n) {
  int val = 1;
  while ((n / val) > 10) {
    val *= 10;
  }
  while (val >= 10) {
    write_char((n / val) + '0');
    val /= 10;
  }
  write_char((n / val) + '0');
  return 0;
}
