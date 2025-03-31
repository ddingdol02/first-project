typedef struct Complex {
    int real;
    int imag;
}Complex;

Complex complex_add(Complex a, Complex b) {
    Complex c;
    c.real = a.real + b.real;
    c.imag = a.imag + b.imag;
    return c;
}