double slow_power(double x, int n)
{
    int i;
    double result = 1.0;

    for(i=0; i<n; i++)  // n번
        result *= x;    // 제곱하기
    return(result);
}