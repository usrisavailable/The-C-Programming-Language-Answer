#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#define debug(fmt, ...) fprintf(stderr, "line %d: " fmt "\n", __LINE__, __VA_ARGS__)
#define MAX_LINE 1000

double atof(char *s);
int getline(char *s, int lim);

int main(int argc, char **argv)
{
    char s[MAX_LINE] = "123.45e-6";
    char t[MAX_LINE] = "ould";
    double atof(char []);
    debug("%.8f", atof(s));
    return 0;
}

double atof(char *s)
{
    int i = 0;
    int sign;
    double val = 0;
    double power = 1.0;
    int counte = 0;
    int direction;

    while(isspace(s[i]))
        i++;

    sign = s[i] == '-'?-1:1;

    if (s[i] == '+' || s[i] == '-')
        i++;
    
    while(isdigit(s[i]))
    {
        int temp = s[i++] - '0';
        val = val * 10 + temp;
        debug("%f", val);
    }
    if (s[i] == '.')
        i++;
    while(isdigit(s[i]))
    {
        int temp = s[i++] - '0';
        val = val * 10 + temp;
        power *= 10;
    }
    if (s[i] == 'e' || s[i] == 'E')
    {
        i++;
        switch(s[i])
        {
            case '-':
                {
                    direction = -1;
                    i++;
                    while (isdigit(s[i]))
                    {
                        int temp = s[i++] - '0';
                        counte = counte * 10 + temp;
                    }
                    break;
                }
            case '+': 
            {
                direction = 1;
                i++;
                while (isdigit(s[i]))
                {
                    int temp = s[i++] - '0';
                    counte = counte * 10 + temp;
                }
                break;
            }
            default:
            {
                direction = 1;
                while (isdigit(s[i]))
                {
                    int temp = s[i++] - '0';
                    counte = counte * 10 + temp;
                }
            }
        }
    }
    //指数需要处理前后补0的问题
    val =  val / power;
    while(counte--)
    {
        //debug("%d", counte);
        debug("%f", val);
        if (direction == 1)
            val = val * 10;
        else
            val = val / 10;
    }
    return val;
}
