#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static void clear_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main(void) {
    int choice;
    double a, b, result;
    long long ai, bi;
    printf("Simple Calculator\n");
    for (;;) {
        printf("\nSelect operation:\n");
        printf(" 1) Add (a + b)\n");
        printf(" 2) Subtract (a - b)\n");
        printf(" 3) Multiply (a * b)\n");
        printf(" 4) Divide (a / b)\n");
        printf(" 5) Modulo (a %% b) [integers]\n");
        printf(" 6) Power (a ^ b)\n");
        printf(" 7) Square root (sqrt(a))\n");
        printf(" 8) Exit\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            clear_stdin();
            continue;
        }

        if (choice == 8) {
            printf("Goodbye.\n");
            break;
        }

        if (choice == 7) {
            printf("Enter value a: ");
            if (scanf("%lf", &a) != 1) { printf("Invalid input.\n"); clear_stdin(); continue; }
            if (a < 0) { printf("Cannot take square root of negative number.\n"); continue; }
            result = sqrt(a);
            printf("sqrt(%.8g) = %.8g\n", a, result);
            continue;
        }

        /* operations that need two operands */
        printf("Enter value a: ");
        if (scanf("%lf", &a) != 1) { printf("Invalid input.\n"); clear_stdin(); continue; }
        printf("Enter value b: ");
        if (scanf("%lf", &b) != 1) { printf("Invalid input.\n"); clear_stdin(); continue; }

        switch (choice) {
            case 1:
                result = a + b;
                printf("%.8g + %.8g = %.8g\n", a, b, result);
                break;
            case 2:
                result = a - b;
                printf("%.8g - %.8g = %.8g\n", a, b, result);
                break;
            case 3:
                result = a * b;
                printf("%.8g * %.8g = %.8g\n", a, b, result);
                break;
            case 4:
                if (b == 0.0) {
                    printf("Error: division by zero.\n");
                } else {
                    result = a / b;
                    printf("%.8g / %.8g = %.8g\n", a, b, result);
                }
                break;
            case 5:
                /* modulo for integers */
                ai = (long long) a;
                bi = (long long) b;
                if (bi == 0) {
                    printf("Error: modulo by zero.\n");
                } else {
                    printf("%lld %% %lld = %lld\n", ai, bi, ai % bi);
                }
                break;
            case 6:
                result = pow(a, b);
                printf("%.8g ^ %.8g = %.8g\n", a, b, result);
                break;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
