#include <iostream>
#include <string>

using namespace std;

struct element
{
    int a = 0;
    int b = 0;
    int base = 2;

    void print(void) { cout << a << " + " << b << "√" << base << endl; }
    std::string getString(void) { return to_string(a)+"+"+to_string(b)+"√"+to_string(base); }
};

int
add_inv(int a, int n)
{
    return n - a;
}

int
add(int a, int b, int n)
{
    return (a + b) % n;
}

int
sub(int a, int b, int n)
{
    return add(a, add_inv(b, n), n);
}

int
extgcd(int a, int b, int &x, int &y)
{
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int gcd = extgcd(b, a % b, x, y);
    int oldX = x;
    x = y;
    y = oldX - a / b * y;
    return gcd;
}

int
mul_inv(int a, int n)
{
    int x, y;
    extgcd(a, n, x, y);
    return x < 0 ? x + n : x;
}
int
mul(int a, int b, int n)
{
    return (a * b) % n;
}

int
div(int a, int b, int n)
{
    return mul(a, mul_inv(b, n), n);
}

element
add_inv(element a, int p)
{
    element e;
    e.a = add_inv(a.a, p);
    e.b = add_inv(a.b, p);
    return e;
}

element
add(element a, element b, int p)
{
    element e;
    e.a = add(a.a, b.a, p);
    e.b = add(a.b, b.b, p);
    return e;
}

element
sub(element a, element b, int p)
{
    return add(a, add_inv(b, p), p);
}

element
mul(element a, element b, int p)
{
    element e;
    e.a = add(mul(a.a, b.a, p), mul(mul(2, a.b, p), b.b, p), p);
    e.b = add(mul(a.a, b.b, p), mul(a.b, b.a, p), p);
    return e;
}

element
div(element a, element b, int p)
{
    element e;
    e.a = div(sub(mul(a.a, b.a, p), mul(mul(2, a.b, p), b.b, p), p),
              sub(mul(b.a, b.a, p), mul(mul(2, b.b, p), b.b, p), p), p);
    e.b = div(sub(mul(a.b, b.a, p), mul(a.a, b.b, p), p),
              sub(mul(b.a, b.a, p), mul(mul(2, b.b, p), b.b, p), p), p);
    return e;
}

element
pow(element a, int n, int p)
{
    element ans;
    ans.a = 1;
    while(n != 0) {
        if(n % 2 == 1) ans = mul(ans, a, p);
        a = mul(a, a, p);
        n >>= 1;
    }
    return ans;
}

void
printRationalPoint(int p)
{
    int count = 0;
    element one, two;
    one.a = 1;
    two.a = 2;
    element x, y;
    element left, right;
    for(int i = 0; i < p; ++i) {
        for(int j = 0; j < p; ++j) {
            y.a = i;
            y.b = j;
            left = pow(y, 2, p);
            for(int k = 0; k < p; ++k) {
                for(int l = 0; l < p; ++l) {
                    x.a = k;
                    x.b = l;
                    right = add(add(pow(x, 3, p), mul(two, x, p), p), one, p);
                    if(left.a == right.a && left.b == right.b) {
                        cout << count++ << ": (x,y)=" << "(" << x.getString() << "," << y.getString() << ")" << endl;

                    }
                }
            }
        }
    }
}

int main(void)
{
    element v1, v2;
    v1.a = 1;
    v1.b = 4;
    v2.a = 3;
    v2.b = 3;
    element r1 = add(v1, v2, 5);
    element r2 = sub(v1, v2, 5);
    element r3 = mul(v1, v2, 5);
    element r4 = div(v1, v2, 5);
    element r5 = pow(v1, 2, 5);

    cout << "Test in F_5(√2)" << endl;
    cout << "(1 + 4√2) + (3 + 3√2): ";
    r1.print();
    cout << "(1 + 4√2) - (3 + 3√2): ";
    r2.print();
    cout << "(1 + 4√2) * (3 + 3√2): ";
    r3.print();
    cout << "(1 + 4√2) / (3 + 3√2): ";
    r4.print();
    cout << "(1 + 4√2)^2: ";
    r5.print();
    printRationalPoint(5);
    return 0;
}
