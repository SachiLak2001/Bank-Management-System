#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structure for a bank account
struct BankAccount {
    int accNumber;
    char accHolderName[50];
    char accType[15];
    double accBalance;
    char password[20];
};

// create a new bank account
void createAccount() {
    struct BankAccount account;

    printf("Enter account number: ");
    scanf("%d", &account.accNumber);

    printf("Enter account holder name: ");
    scanf("%s", account.accHolderName);

    printf("Enter account type (Savings/Checking): ");
    scanf("%s", account.accType);

    printf("Create a password:");
    scanf("%s", account.password);

    printf("Enter account balance: ");
    scanf("%lf", &account.accBalance);

    FILE *file1 = fopen("accounts.txt", "a");
    fprintf(file1, "%d %s %s %.2lf\n", account.accNumber, account.accHolderName, account.accType, account.accBalance);
    fclose(file1);

    FILE *file2 = fopen("passwords.txt", "a");
    fprintf(file2, "%s \n", account.password );
    fclose(file2);

    printf("\nAccount created successfully.\n");
}

// view account details
void viewAccount() {
    char password[20];
    int flag2 = 0;
    printf("\nEnter Your password: ");
    scanf("%s", password);

    FILE *file2 = fopen("passwords.txt", "r");
    if (file2 == NULL) {
        printf("Error: Password not found. Please contact branch office\n");
        return;
    }

    struct BankAccount account;
    while (fscanf(file2, "%s", account.password) != EOF) {
        if (strcmp(account.password, password) == 0) {
            flag2 = 1;

            int accNumber;
            printf("Enter account number to view: ");
            scanf("%d", &accNumber);

            FILE *file1 = fopen("accounts.txt", "r");
            if (file1 == NULL) {
                printf("Error: Accounts file not found or unable to open.\n");
                return;
            }

            int flag1 = 0;
            while (fscanf(file1, "%d %s %s %lf", &account.accNumber, account.accHolderName, account.accType, &account.accBalance) != EOF) {
                if (account.accNumber == accNumber) {
                    flag1 = 1;
                    printf("Account Details:\n");
                    printf("Account Number: %d\n", account.accNumber);
                    printf("Account Holder Name: %s\n", account.accHolderName);
                    printf("Account Type: %s\n", account.accType);
                    printf("Account Balance: %.2lf\n", account.accBalance);
                    break;
                }
            }

            if (!flag1) {
                printf("Account not found.\n");
            }

            fclose(file1);
            break; // Exit the loop.
        }
    }

    if (!flag2) {
        printf("Password is wrong.\n");
    }
    fclose(file2);
}
// Function to Deposit
void deposit() {
    int accNumber, found = 0;
    double depositAmount;
    struct BankAccount account;

    printf("Enter your account number: ");
    scanf("%d", &accNumber);

    FILE *file1 = fopen("accounts.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file1 == NULL || tempFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fscanf(file1, "%d %s %s %lf", &account.accNumber, account.accHolderName, account.accType, &account.accBalance) != EOF) {
        if (account.accNumber == accNumber) {
            found = 1;
            printf("Enter amount to deposit: ");
            scanf("%lf", &depositAmount);
            account.accBalance += depositAmount;
            printf("Deposit successful! New balance: %.2lf\n", account.accBalance);
        }
        fprintf(tempFile, "%d %s %s %.2lf\n", account.accNumber, account.accHolderName, account.accType, account.accBalance);
    }

    fclose(file1);
    fclose(tempFile);

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found) {
        printf("Account not found.\n");
    }
}


    // Function to Withdrawal
void withdrawal() {
    int accNumber, found = 0;
    double withdrawAmount;
    struct BankAccount account;

    printf("Enter your account number: ");
    scanf("%d", &accNumber);

    FILE *file1 = fopen("accounts.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file1 == NULL || tempFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fscanf(file1, "%d %s %s %lf", &account.accNumber, account.accHolderName, account.accType, &account.accBalance) != EOF) {
        if (account.accNumber == accNumber) {
            found = 1;
            printf("Enter amount to withdraw: ");
            scanf("%lf", &withdrawAmount);
            if (withdrawAmount > account.accBalance) {
                printf("Insufficient funds!\n");
            } else {
                account.accBalance -= withdrawAmount;
                printf("Withdrawal successful! New balance: %.2lf\n", account.accBalance);
            }
        }
        fprintf(tempFile, "%d %s %s %.2lf\n", account.accNumber, account.accHolderName, account.accType, account.accBalance);
    }

    fclose(file1);
    fclose(tempFile);

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found) {
        printf("Account not found.\n");
    }
}


// list all accounts
void listAllAccounts() {
    FILE *file1 = fopen("accounts.txt", "r");
    if (file1 == NULL) {
        printf("Error: File not found or unable to open.\n");
        return;
    }

    struct BankAccount account;

    printf("List of all accounts:\n");

    while (fscanf(file1, "%d %s %s %lf", &account.accNumber, account.accHolderName, account.accType, &account.accBalance) != EOF) {
        printf("Account Number: %d, Account Holder Name: %s, Account Type: %s, Account Balance: %.2lf\n", account.accNumber, account.accHolderName, account.accType, account.accBalance);
    }

    fclose(file1);
}

// Main function
int main() {
    int choice;

    while (1) {
        printf("\n~Bank Account Management System~\n\t Welcome!\n\n");
        printf("1. Create Account\n");
        printf("2. View Account\n");
        printf("3. List All Accounts\n");
        printf("4. Deposit\n");
        printf("5. Withdrawal\n");
        printf("6. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                viewAccount();
                break;
            case 3:
                listAllAccounts();
                break;
            case 4:
                deposit();
                break;
            case 5:
                withdrawal();
                break;
            case 6:
                printf("~~Exiting Bank Account Management System.~~\n\t Thank you!");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
