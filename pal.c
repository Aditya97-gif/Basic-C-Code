#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_palindrome(const char *s) {
    int i = 0, j = (int)strlen(s) - 1;
    while (i < j) {
        while (i < j && !isalnum((unsigned char)s[i])) i++;
        while (i < j && !isalnum((unsigned char)s[j])) j--;
        if (i < j) {
            if (tolower((unsigned char)s[i]) != tolower((unsigned char)s[j])) return 0;
            i++; j--;
        }
    }
    return 1;
}

int main(void) {
    char buf[1024];
    printf("Enter text to check (press Enter to submit):\n");
    if (!fgets(buf, sizeof(buf), stdin)) return 1;
    /* remove newline */
    size_t len = strlen(buf);
    if (len && buf[len-1] == '\n') buf[len-1] = '\0';

    if (is_palindrome(buf))
        printf("Result: palindrome\n");
    else
        printf("Result: not a palindrome\n");

    return 0;
}
