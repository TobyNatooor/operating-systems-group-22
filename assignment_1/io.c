
#include <errno.h>
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
    ssize_t result = write(1, s, 1);
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
  char charBuff[64];
  charBuff[63] = '\0';
  int temp = n;
  int i;
  for (int i = 62; temp != 0; i--) {
    charBuff[i] = (temp % 10) + '0';
    temp = temp / 10;
  }
  ssize_t result = write(1, charBuff + i, 63 - i);
  if (result == -1)
    return EOF;
  return 0;
}
