#include <stdio.h>

int calc(int input)
{
    int code = ((input % 10000) * 3897 + (input / 100000) * (input / 100000)) % 10000;
    return code;
}

int main()
{
    int input;

    printf("학번 입력: ");
    scanf("%d", &input);

    printf("Code: %d\n", calc(input));

    return 0;
}