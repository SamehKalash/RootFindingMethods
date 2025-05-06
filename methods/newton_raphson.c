#include <stdio.h>
#include <math.h>

#define MAX_DEGREE 4
#define TOLERANCE 1e-8

typedef struct {
    double coeffs[MAX_DEGREE + 1];
    int degree;
} Polynomial;

extern double evaluate(Polynomial p, double x);
extern Polynomial derivative(Polynomial p);

void newton_raphson(Polynomial p) {
    Polynomial d = derivative(p);
    double x0, next_x;
    int max_iter;
    
    printf("\n--- Newton-Raphson Method ---\n");
    printf("Initial guess: ");
    scanf("%lf", &x0);
    printf("Max iterations: ");
    scanf("%d", &max_iter);

    printf("\n%5s %12s %12s %12s\n", 
           "Iter", "x", "f(x)", "New x");
    
    for(int iter = 1; iter <= max_iter; iter++) {
        double fx = evaluate(p, x0);
        double dfx = evaluate(d, x0);
        next_x = x0 - fx / dfx;
        
        printf("%5d %12.8f %12.8f %12.8f\n", 
              iter, x0, fx, next_x);

        if(fabs(fx) < TOLERANCE) break;
        if(fabs(dfx) < 1e-12) {
            printf("Zero derivative!\n");
            break;
        }
        
        x0 = next_x;
    }
    
    printf("\nFinal approximation: %.8f\n", x0);
}