#include <stdio.h>
#include <math.h>

#define MAX_DEGREE 4
#define TOLERANCE 1e-8

typedef struct {
    double coeffs[MAX_DEGREE + 1];
    int degree;
} Polynomial;

extern double evaluate(Polynomial p, double x);

void bisection(Polynomial p) {
    double a, b;
    int max_iter;
    double mid ,fmid;
    
    printf("\n--- Bisection Method ---\n");
    printf("Interval [a b]: ");
    scanf("%lf %lf", &a, &b);
    printf("Max iterations: ");
    scanf("%d", &max_iter);

    double fa = evaluate(p, a);
    double fb = evaluate(p, b);

    if (fa * fb >= 0) {
        printf("Invalid interval! f(a)=%.6f, f(b)=%.6f\n", fa, fb);
        return;
    }

    printf("\n%5s %10s %10s %10s %10s\n", 
           "Iter", "a", "b", "mid", "f(mid)");
    
    for (int i = 1; i <= max_iter; i++) {
         mid = (a + b) / 2;
         fmid = evaluate(p, mid);
        
        printf("%5d %10.6f %10.6f %10.6f %10.6f\n", 
              i, a, b, mid, fmid);

        if (fa * fmid < 0) {
            b = mid;
            fb = fmid;
        } else {
            a = mid;
            fa = fmid;
        }
    }
    ;
    printf("\nFinal root found: %.6f\n", mid);
}