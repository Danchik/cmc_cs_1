// уравнения кривых - 10
// f1 = 1 + 4/(x^2 + 1)
// f2 = x^3
// f3 = 2^-x
// метод деленения отрезка пополам
// формула прямоугольников

#include <stdio.h>
#include <time.h>   // работа с измерением времени
#include <stdlib.h> // работа с динамической память, rand()
#include <math.h>
#include <stdbool.h>
#include <string.h>

// peronal type 
typedef double r_type;

// epsilons
const r_type eps = 0.001;
const r_type eps1 = 0.00001;
const r_type eps2 = 0.0001;

// global variables for number of iterations
int st1r = 0;
int st2r = 0;
int st3r = 0;
int st0r = 0;

//function declaration
extern double _f1(double x);
extern double _f2(double x);
extern double _f3(double x);

// function f1
r_type f1(r_type x)
{
    return _f1(x);
}

//function f2
r_type f2(r_type x)
{
    return _f2(x);
}

//function f3
r_type f3(r_type x)
{
    return _f3(x);
}


r_type root (r_type (*f)(r_type), r_type (*g)(r_type), r_type a, r_type b, r_type eps)
{
    if ((b - a) < eps)
    {
        return (a+b)/2;
    }
    st0r+=1;
    r_type c = (a + b) / 2;
    r_type q = f(a) - g(a);
    r_type w = f(b) - g(b);
    r_type r = f(c) - g(c);
    if (q * r  < 0)
    {
        return root (f, g, a, c, eps);
    }
    return root(f, g, c, b, eps);
}


r_type integral(r_type (*f)(r_type), r_type a, r_type b, r_type eps)
{
    r_type int_left = 0;
    r_type int_right = 2 * eps;
    unsigned steps = 100;
    r_type length = b-a;
    while (fabs(int_right - int_left) > eps){
        int_left = 0;
        int_right = 0;
        r_type dx = length/steps;
        for(r_type cursor = a; cursor < b; cursor=cursor+dx){
            int_left = int_left + (f(cursor)*dx);
            int_right = int_right + (f(cursor+dx)*dx);
        }
        steps*=2;
    }
    return (int_left+int_right)/2;
}


r_type square(r_type (*f)(r_type), r_type (*g)(r_type), r_type (*w)(r_type), r_type a, r_type b)
{
    st0r = 0;
    r_type root_1 = root(f, g, a, b, eps1);
    st1r = st0r;
    st0r = 0;
    r_type root_2 = root(f, w, a, b, eps1);
    st2r = st0r;
    st0r = 0;
    r_type root_3 = root(w, g, a, b, eps1);
    st3r = st0r;
    r_type s_f_1 = integral(f, root_2, root_3, eps2);
    r_type s_w_1 = integral(w, root_2, root_3, eps2);
    r_type s_1 = s_f_1-s_w_1;
    r_type s_f_2 = integral(f, root_3, root_1, eps2);
    r_type s_g_1 = integral(g, root_3, root_1, eps2);
    r_type s_2 = s_f_2-s_g_1;
    return (s_1 + s_2);
}

int main (int argc, char *argv[])
{
     if(argc <= 1) {
         printf("\t%s -help to request help message\n", argv[0]);
     }
    
    if(!strcmp(argv[1], "-help")) {
        printf("\t%s -help               Print help message\n", argv[0]);
        printf("\t%s -roots              Print roots for 3 functions\n", argv[0]);
        printf("\t%s -square             Print size of the square\n", argv[0]);
        printf("\t%s -iter               Print number of iterations\n", argv[0]);
        printf("\t%s -testr              Gets index of 1 func, index of 2 func, a, b and calculates root\n", argv[0]);
        printf("\t%s -testi              Gets index of func, a, b and calculates integral\n", argv[0]);

     } else if(!strcmp(argv[1], "-roots")) {
        printf("\n~ Roots of 3 functions:\n");
        printf("\nabscissas of intersection f1 and f2: %f\n", root(f1, f2, -2, 2, eps1));
        printf("abscissas of intersection f1 and f3: %f\n", root(f1, f3, -2, 2, eps1));
        printf("abscissas of intersection f2 and f3: %f\n\n", root(f2, f3, -2, 2, eps1));

    } else if(!strcmp(argv[1], "-square")) {
        printf("\nSize of square: %f\n\n", square(f1, f2, f3, -2, 2));

    } else if(!strcmp(argv[1], "-iter")) {
        square(f1, f2, f3, -2, 2);
        printf("\n~ Number of iteration:\n\n");
        printf("number of  iterations f1 and f2 in root: %d\n", st1r);
        printf("number of  iterations f2 and f3 in root: %d\n", st2r);
        printf("number of  iterations f3 and f1 in root: %d\n\n", st3r);

    } else if(!strcmp(argv[1], "-testr")) {
        if ((argc <= 5) || (argc > 6)) {
            printf("'-testr' operation requires 4 parameters.\n");
        } else {
            int q1, q2;
            float a, b;
            sscanf(argv[2], "%d", &q1);
            sscanf(argv[3], "%d", &q2);
            sscanf(argv[4], "%f", &a);
            sscanf(argv[5], "%f", &b);
            if (((q1 == 1) && (q2 == 2)) || ((q1 == 2) && (q2 == 1) ))
            {
                printf("\n~ Root of f1 and f2: %f\n\n", root(f1, f2, a, b, eps1));  
            }
            else if (((q1 == 1) && (q2 == 3)) || ((q1 == 3) && (q2 == 1) ))
            {
                printf("\n~ Root of f1 and f3: %f\n\n", root(f1, f3, a, b, eps1));  
            }
            else if (((q1 == 3) && (q2 == 2)) || ((q1 == 2) && (q2 == 3) ))
            {
                printf("\n~ Root of f2 and f3: %f\n\n", root(f2, f3, a, b, eps1));  
            }
            else 
            {
                printf("\nWRONG INPUT (try again)\n\n");
            }
        }  

    } else if(!strcmp(argv[1], "-testi")) {
        if ((argc <= 4) || (argc > 5)) {
            printf("'-testi' operation requires 4 parameters.\n");
        } else {
            int q1, q2;
            float a, b;
            sscanf(argv[2], "%d", &q1);
            sscanf(argv[3], "%f", &a);
            sscanf(argv[4], "%f", &b);
                
            if (q1 == 1)
            { 
                printf("\n~ Integral of f1: %f\n\n", integral(f1, a, b, eps1));  
            }
            else if (q1 == 2)
            {
                printf("\n~ Integral of f2: %f\n\n", integral(f2, a, b, eps1));  
            }
            else if (q1 == 3)
            {
                printf("\n~ Integral of f3: %f\n\n", integral(f3, a, b, eps1));  
            }
            else 
            {
                printf("\nWRONG INPUT (try again)\n\n");
            }
        }  

    } else {
            printf("\nWrong input %s\n\nType %s -help for help.\n\n", argv[1], argv[0]);
        }
    return 0;
}
