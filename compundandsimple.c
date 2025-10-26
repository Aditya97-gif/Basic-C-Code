#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static void clear_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

static void calc_simple_interest(void) {
    double p, r, t;
    printf("\nSimple Interest Calculator\n");
    printf("Enter principal (P): ");
    if (scanf("%lf", &p) != 1 || p < 0) { clear_stdin(); printf("Invalid principal.\n"); return; }
    printf("Enter annual rate in percent (R): ");
    if (scanf("%lf", &r) != 1) { clear_stdin(); printf("Invalid rate.\n"); return; }
    printf("Enter time in years (T): ");
    if (scanf("%lf", &t) != 1 || t < 0) { clear_stdin(); printf("Invalid time.\n"); return; }

    double interest = (p * r * t) / 100.0;
    double amount = p + interest;
    printf("Simple Interest = %.2f\nTotal Amount = %.2f\n", interest, amount);
}

static void calc_compound_interest(void) {
    double p, r, t;
    int n;
    printf("\nCompound Interest Calculator\n");
    printf("Enter principal (P): ");
    if (scanf("%lf", &p) != 1 || p < 0) { clear_stdin(); printf("Invalid principal.\n"); return; }
    printf("Enter annual rate in percent (R): ");
    if (scanf("%lf", &r) != 1) { clear_stdin(); printf("Invalid rate.\n"); return; }
    printf("Enter time in years (T): ");
    if (scanf("%lf", &t) != 1 || t < 0) { clear_stdin(); printf("Invalid time.\n"); return; }
    printf("Enter compounding frequency per year (n) e.g. 1,2,4,12,365: ");
    if (scanf("%d", &n) != 1 || n <= 0) { clear_stdin(); printf("Invalid frequency.\n"); return; }

    double rate_per_period = r / (100.0 * n);
    double periods = n * t;
    double amount = p * pow(1.0 + rate_per_period, periods);
    double interest = amount - p;
    printf("Compound Interest = %.2f\nTotal Amount = %.2f\n", interest, amount);
}

int main(void) {
    int choice;
    printf("Interest Calculator (Simple & Compound)\n");
    for (;;) {
        printf("\nMenu:\n");
        printf(" 1) Simple Interest\n");
        printf(" 2) Compound Interest\n");
        printf(" 3) Exit\n");
        printf("Choose: ");
        if (scanf("%d", &choice) != 1) { clear_stdin(); printf("Invalid choice.\n"); continue; }

        if (choice == 1) {
            calc_simple_interest();
        } else if (choice == 2) {
            calc_compound_interest();
        } else if (choice == 3) {
            printf("Exiting.\n");
            break;
        } else {
            printf("Invalid option.\n");
        }
    }
    return 0;
}