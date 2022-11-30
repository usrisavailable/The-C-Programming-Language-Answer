#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#define debug(fmt, ...) fprintf(stderr, "line %d: " fmt "\n", __LINE__, __VA_ARGS__)

#define swap(t, x, y) {double temp;  temp = *((t) + (x));  *((t) + (x)) = *((t) + (y)); \
                        *((t) + (y)) = temp;}

int main(int argc, char **argv)
{
    char s[2] = {'a','b'};
    swap(s, 0, 1);
    debug("%d", s[0]);
    debug("%d", s[1]);
    return 0;
}
