#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void generatePassword(int length) {
    char chars[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789"
        "!@#$%^&*";

    int n = strlen(chars);

    printf("\nSuggested Strong Password: ");
    for(int i = 0; i < length; i++)
        printf("%c", chars[rand() % n]);
    printf("\n");
}

int main() {
    srand(time(NULL));

    char password[100];

    printf("Enter Password: ");
    scanf("%99s", password);

    int len = strlen(password);

    int upper = 0, lower = 0, digit = 0, special = 0;

    char weakPasswords[][20] = {
        "password",
        "123456",
        "12345678",
        "admin",
        "qwerty"
    };

    for(int i = 0; i < 5; i++) {
        if(strcmp(password, weakPasswords[i]) == 0) {
            printf("\nCommon Weak Password Detected!\n");
            return 0;
        }
    }

    for(int i = 0; i < len; i++) {
        if(isupper(password[i]))
            upper = 1;
        else if(islower(password[i]))
            lower = 1;
        else if(isdigit(password[i]))
            digit = 1;
        else
            special = 1;
    }

    int charset = 0;

    if(upper) charset += 26;
    if(lower) charset += 26;
    if(digit) charset += 10;
    if(special) charset += 32;

    double entropy = len * log2(charset);

    int score = upper + lower + digit + special;

    printf("\n===== Password Report =====\n");
    printf("Length: %d\n", len);
    printf("Entropy: %.2f bits\n", entropy);

    if(len < 8 || score <= 2)
        printf("Strength: Weak\n");
    else if(score == 3)
        printf("Strength: Medium\n");
    else
        printf("Strength: Strong\n");

    printf("\nSuggestions:\n");

    if(len < 8)
        printf("- Increase length to at least 8 characters\n");

    if(!upper)
        printf("- Add uppercase letters\n");

    if(!lower)
        printf("- Add lowercase letters\n");

    if(!digit)
        printf("- Add numbers\n");

    if(!special)
        printf("- Add special characters\n");

    FILE *fp = fopen("password_report.txt", "w");

    fprintf(fp, "Password Length: %d\n", len);
    fprintf(fp, "Entropy: %.2f bits\n", entropy);

    fclose(fp);

    generatePassword(14);

    printf("\nReport saved in password_report.txt\n");

    return 0;
}