#include <stdio.h>

//华氏度转化摄氏度包装入函数
void fos(int n)
{
    float fahr;
    char *f = "华氏度";
    char *s = "摄氏度";
    printf("%s %s\n", f, s);
    for (fahr = 0; fahr <= n; fahr += 20)
        {
            //celsius = (5.0 / 9.0) * (fahr - 32.0);
            printf("%3.0f %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32.0));
        }
}
main()
{
    fos(300);
}