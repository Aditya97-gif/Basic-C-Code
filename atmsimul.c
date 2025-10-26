#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TX 20
#define TX_LINE 128

typedef struct {
    double balance;
    int pin;
    char tx[MAX_TX][TX_LINE];
    int tx_count;
} Account;

static void clear_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

static void record_transaction(Account *acc, const char *type, double amount) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char line[TX_LINE];
    snprintf(line, sizeof(line), "%04d-%02d-%02d %02d:%02d:%02d | %s | %.2f | Balance: %.2f",
             tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday,
             tm->tm_hour, tm->tm_min, tm->tm_sec,
             type, amount, acc->balance);
    if (acc->tx_count < MAX_TX) {
        strncpy(acc->tx[acc->tx_count++], line, TX_LINE-1);
        acc->tx[acc->tx_count-1][TX_LINE-1] = '\0';
    } else {
        /* rotate */
        for (int i = 1; i < MAX_TX; ++i) strncpy(acc->tx[i-1], acc->tx[i], TX_LINE);
        strncpy(acc->tx[MAX_TX-1], line, TX_LINE-1);
        acc->tx[MAX_TX-1][TX_LINE-1] = '\0';
    }

    /* append to file for persistence */
    FILE *fp = fopen("atm_transactions.txt", "a");
    if (fp) {
        fprintf(fp, "%s\n", line);
        fclose(fp);
    }
}

static int verify_pin(Account *acc) {
    int attempts = 3;
    int entered;
    while (attempts--) {
        printf("Enter PIN: ");
        if (scanf("%d", &entered) != 1) { clear_stdin(); printf("Invalid input.\n"); continue; }
        if (entered == acc->pin) return 1;
        printf("Incorrect PIN. %d attempt(s) left.\n", attempts);
    }
    return 0;
}

static void load_account(Account *acc) {
    /* try to load balance and pin from file, else set defaults */
    FILE *fp = fopen("atm_account.txt", "r");
    if (!fp) {
        acc->balance = 1000.0;
        acc->pin = 1234;
        acc->tx_count = 0;
        return;
    }
    if (fscanf(fp, "%lf %d", &acc->balance, &acc->pin) != 2) {
        acc->balance = 1000.0;
        acc->pin = 1234;
    }
    fclose(fp);

    /* load last MAX_TX transactions if present */
    acc->tx_count = 0;
    fp = fopen("atm_transactions.txt", "r");
    if (!fp) return;
    char line[TX_LINE];
    /* read all lines and keep only last MAX_TX */
    char tmp[MAX_TX][TX_LINE];
    int count = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (count < MAX_TX) strncpy(tmp[count++], line, TX_LINE-1);
        else {
            /* rotate */
            for (int i = 1; i < MAX_TX; ++i) strncpy(tmp[i-1], tmp[i], TX_LINE);
            strncpy(tmp[MAX_TX-1], line, TX_LINE-1);
        }
    }
    fclose(fp);
    for (int i = 0; i < count; ++i) {
        size_t len = strlen(tmp[i]);
        if (len && tmp[i][len-1] == '\n') tmp[i][len-1] = '\0';
        strncpy(acc->tx[acc->tx_count++], tmp[i], TX_LINE-1);
    }
}

static void save_account(Account *acc) {
    FILE *fp = fopen("atm_account.txt", "w");
    if (!fp) return;
    fprintf(fp, "%.2f %d\n", acc->balance, acc->pin);
    fclose(fp);
}

int main(void) {
    Account acc;
    load_account(&acc);

    printf("Welcome to Basic ATM Simulator\n");
    if (!verify_pin(&acc)) {
        printf("Too many incorrect attempts. Exiting.\n");
        return 1;
    }

    for (;;) {
        int choice;
        printf("\nMenu:\n");
        printf(" 1) Check balance\n");
        printf(" 2) Deposit\n");
        printf(" 3) Withdraw\n");
        printf(" 4) Mini statement\n");
        printf(" 5) Change PIN\n");
        printf(" 6) Exit\n");
        printf("Choose: ");
        if (scanf("%d", &choice) != 1) { clear_stdin(); printf("Invalid input.\n"); continue; }

        if (choice == 1) {
            printf("Current balance: %.2f\n", acc.balance);
        } else if (choice == 2) {
            double amt;
            printf("Enter amount to deposit: ");
            if (scanf("%lf", &amt) != 1 || amt <= 0) { clear_stdin(); printf("Invalid amount.\n"); continue; }
            acc.balance += amt;
            record_transaction(&acc, "Deposit", amt);
            save_account(&acc);
            printf("Deposited %.2f. New balance: %.2f\n", amt, acc.balance);
        } else if (choice == 3) {
            double amt;
            printf("Enter amount to withdraw: ");
            if (scanf("%lf", &amt) != 1 || amt <= 0) { clear_stdin(); printf("Invalid amount.\n"); continue; }
            if (amt > acc.balance) { printf("Insufficient funds.\n"); continue; }
            acc.balance -= amt;
            record_transaction(&acc, "Withdraw", amt);
            save_account(&acc);
            printf("Withdrawn %.2f. New balance: %.2f\n", amt, acc.balance);
        } else if (choice == 4) {
            printf("Mini statement (last %d):\n", MAX_TX);
            if (acc.tx_count == 0) printf(" No transactions.\n");
            for (int i = 0; i < acc.tx_count; ++i) printf(" %d) %s\n", i+1, acc.tx[i]);
        } else if (choice == 5) {
            int oldpin, newpin;
            printf("Enter current PIN: ");
            if (scanf("%d", &oldpin) != 1) { clear_stdin(); printf("Invalid input.\n"); continue; }
            if (oldpin != acc.pin) { printf("Incorrect PIN.\n"); continue; }
            printf("Enter new 4-digit PIN: ");
            if (scanf("%d", &newpin) != 1 || newpin < 0 || newpin > 9999) { clear_stdin(); printf("Invalid PIN.\n"); continue; }
            acc.pin = newpin;
            save_account(&acc);
            printf("PIN changed successfully.\n");
        } else if (choice == 6) {
            printf("Goodbye.\n");
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}