#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100
#define FILE_NAME "accounts.txt"

typedef struct {
    int accountNumber;
    char name[100];
    float balance;
} Account;

Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

void loadAccounts() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) return;

    accountCount = 0;
    while (fscanf(file, "%d %s %f", &accounts[accountCount].accountNumber, accounts[accountCount].name, &accounts[accountCount].balance) != EOF) {
        accountCount++;
    }
    fclose(file);
}

void saveAccounts() {
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Error saving accounts.\n");
        return;
    }

    for (int i = 0; i < accountCount; i++) {
        fprintf(file, "%d %s %.2f\n", accounts[i].accountNumber, accounts[i].name, accounts[i].balance);
    }
    fclose(file);
}

void createAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Cannot create more accounts!\n");
        return;
    }

    Account newAccount;
    newAccount.accountNumber = 1000 + accountCount;
    printf("Enter your name: ");
    scanf("%s", newAccount.name);
    newAccount.balance = 0.0;

    accounts[accountCount++] = newAccount;
    saveAccounts();
    printf("Account created successfully! Your account number is %d\n", newAccount.accountNumber);
}

int findAccount(int accNumber) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accNumber) return i;
    }
    return -1;
}

void depositMoney() {
    int accNumber;
    float amount;
    printf("Enter account number: ");
    scanf("%d", &accNumber);

    int index = findAccount(accNumber);
    if (index == -1) {
        printf("Account not found!\n");
        return;
    }

    printf("Enter deposit amount: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid amount!\n");
        return;
    }

    accounts[index].balance += amount;
    saveAccounts();
    printf("Amount deposited successfully! New balance: %.2f\n", accounts[index].balance);
}

void withdrawMoney() {
    int accNumber;
    float amount;
    printf("Enter account number: ");
    scanf("%d", &accNumber);

    int index = findAccount(accNumber);
    if (index == -1) {
        printf("Account not found!\n");
        return;
    }

    printf("Enter withdrawal amount: ");
    scanf("%f", &amount);

    if (amount <= 0 || amount > accounts[index].balance) {
        printf("Invalid amount or insufficient balance!\n");
        return;
    }

    accounts[index].balance -= amount;
    saveAccounts();
    printf("Amount withdrawn successfully! New balance: %.2f\n", accounts[index].balance);
}

void checkBalance() {
    int accNumber;
    printf("Enter account number: ");
    scanf("%d", &accNumber);

    int index = findAccount(accNumber);
    if (index == -1) {
        printf("Account not found!\n");
        return;
    }

    printf("Account Number: %d\n", accounts[index].accountNumber);
    printf("Account Holder: %s\n", accounts[index].name);
    printf("Balance: %.2f\n", accounts[index].balance);
}

int main() {
    loadAccounts();

    int choice;
    do {
        printf("\nBank Management System\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: checkBalance(); break;
            case 5: printf("Thank you for using our service!\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 5);

    return 0;
}
