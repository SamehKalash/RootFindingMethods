#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_DEGREE 4
#define TOLERANCE 1e-8

typedef struct {
    double coeffs[MAX_DEGREE + 1];
    int degree;
} Polynomial;

// Methods
void bisection(Polynomial p);
void newton_raphson(Polynomial p);


void print_polynomial(Polynomial p) {
    char buffer[256] = {0};
    int first = 1;

    for(int i = 0; i <= p.degree; i++) {
        double coeff = p.coeffs[i];
        if(coeff == 0) continue;

        int exponent = p.degree - i;
        char term[32] = {0};

        if(first) {
            if(coeff < 0) strcat(buffer, "-");
            first = 0;
        } else {
            strcat(buffer, coeff > 0 ? " + " : " - ");
        }
        coeff = fabs(coeff);

        if(coeff != 1.0 || exponent == 0) {
            snprintf(term, sizeof(term), "%.2g", coeff);
        }

        if(exponent > 1) {
            size_t remaining = sizeof(term) - strlen(term);
            snprintf(term + strlen(term), remaining, "x^%d", exponent);
        } else if(exponent == 1) {
            strcat(term, "x");
        }

        strcat(buffer, term);
    }
    printf("Equation: %s\n", buffer[0] ? buffer : "0");
}

double evaluate(Polynomial p, double x) {
    double result = 0;
    for(int i = 0; i <= p.degree; i++) {
        result += p.coeffs[i] * pow(x, p.degree - i);
    }
    return result;
}

Polynomial derivative(Polynomial p) {
    Polynomial d = {.degree = p.degree - 1};
    for(int i = 0; i < p.degree; i++) {
        d.coeffs[i] = p.coeffs[i] * (p.degree - i);
    }
    return d;
}

int main() {
    Polynomial p = {0};
    
    printf("\n\n\nNumerical Root Finder\n");
    do {
        printf("Polynomial degree (0-4): ");
        scanf("%d", &p.degree);
    } while(p.degree < 0 || p.degree > 4);
    
    printf("Enter coefficients (x^%d to constant):\n", p.degree);
    for(int i = 0; i <= p.degree; i++) {
        printf("x^%d: ", p.degree - i);
        scanf("%lf", &p.coeffs[i]);
    }
    
    print_polynomial(p);

    int choice;
    printf("\n[1] Bisection\n[2] Newton-Raphson\nChoice: ");
    scanf("%d", &choice);

    if(choice == 1) bisection(p);
    else if(choice == 2) newton_raphson(p);
    else printf("Invalid choice!\n");

    return 0;
}