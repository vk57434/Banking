#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define long long int llf

long long int ACCOUNT_NUMBER = 9060000000;

int INDEX = 0;
int currCustomerIndex = -1;

struct customer {
    char name[40];
    char mobile_no[11];
    char email[40];
    long long int accountNumber;
    char gender[12];
    char address[100];
    long long int balance;
} a1[100], a2, currentUser;
FILE *adm;

bool compareString(char *original, char *enteredString) {
    int i = 0;
    if (strlen(original) != strlen(enteredString))
        return false;
    while (original[i] != '\0' && enteredString[i] != '\0') {
        if (original[i] != enteredString[i]) {
            return false;
        }
        i++;
    }
    return true;
}

int main() {

    int ch = 1;
    FILE *fp;
    fp = fopen("banking.txt", "a+");
    printf("\t\t WELCOME TO BANKING SYSTEM\n");

    if (fp == NULL) {
        printf("File are not found....");
        exit(1);
    }
    loadData();
    while (ch <= 2) {
        printf("1.> Admin Login\n");
        printf("2.> Customer Login\n");
        printf("Enter ur choice: ");
        scanf("%d", &ch);
        switch (ch) {
        case 1:
            admin();
            break;
        case 2:
            customerLogin();
            break;
        }
    }
}
void customerLogin() {
    bool found;
    int i;
    int ch = 1;
    FILE *cust;
    cust = fopen("customer.txt", "r");
    char mobile_no[11];
    long long int acno;
retry:
    printf("Enter mobile number: ");
    scanf("%s", mobile_no);
    printf("Enter account number: ");
    scanf("%lld", &acno);
    for (i = 0; i < INDEX; i++) {
        if (compareString(mobile_no, a1[i].mobile_no) &&
            (acno == a1[i].accountNumber)) {
            currentUser = a1[i];
            currCustomerIndex = i;
            printf("login success...\n");
            printf("%s-%s-%s-%s-%s-%lld-%lld\n", a1[i].name, a1[i].mobile_no,
                   a1[i].email, a1[i].gender, a1[i].address, a1[i].balance,
                   a1[i].accountNumber);
            found = true;
            break;
        } else {
            found = false;
        }
    }
    if (!found) {
        puts("account number and mobile no. not found plz enter valid id....");
        goto retry;
    }
    printf("\t\t\t\t..........Customer Menu.......\n");
    while (ch <= 5) {
        printf("1> tranfer money..\n");
        printf("2> withdraw..\n");
        printf("3> deposit..\n");
        printf("4> User details..\n");
        printf("Plzz enter ur choice: ");
        scanf("%d", &ch);
        switch (ch) {
        case 1:
            transfer();
            break;
        case 2:
            doTransaction(1);
            break;
        case 3:
            doTransaction(2);
            break;
        case 4:
            details();
            break;
        }
    }
    fclose(cust);
}
int admin() {
    char s[200];
    int i, ch;
    FILE *adm;
    adm = fopen("admin.txt", "r");
    char userName[20], pass[20];
    char user[20], password[20];
    if (adm == NULL) {
        printf("Admin File not Found...");
        exit(2);
    }
    fgets(s, 100, adm);
    bool flag = false;
    int j = 0;
    for (i = 0; s[i] != '\0'; i++) {
        if (flag) {
            pass[j++] = s[i];
        } else {
            if (s[i] == ':') {
                flag = true;
            } else {
                userName[i] = s[i];
            }
        }
    }
retryAdmin:
    printf("Enter username: ");
    scanf("%s", user);
    printf("Enter password: ");
    scanf("%s", password);
    if (((compareString(pass, password)) && (compareString(user, userName)))) {
        adminMenu();
    } else {
        printf("Username or password not matched...\n");
        goto retryAdmin;
    }
}
void loadData() {
    FILE *fp;
    fp = fopen("customer.txt", "a+");
    int q;
    for (; INDEX < 100; INDEX++) {
        if (feof(fp)) {
            break;
        }
        fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%lld,%lld\n", &q,
               a1[INDEX].name, a1[INDEX].mobile_no, a1[INDEX].email,
               a1[INDEX].gender, a1[INDEX].address, &a1[INDEX].accountNumber,
               &a1[INDEX].balance);
        // printf("%s-%s-%s-%s-%s-%lld-%lld\n",a1[INDEX].name,a1[INDEX].mobile_no,a1[INDEX].email,a1[INDEX].gender,a1[INDEX].address,a1[INDEX].balance,a1[INDEX].accountNumber);
        if (a1[INDEX].accountNumber > ACCOUNT_NUMBER) {
            ACCOUNT_NUMBER = a1[INDEX].accountNumber;
        }
    }
    fclose(fp);
}
void adminMenu() {
    int ch = 1;
    printf("\n\n\t\t\t********list of banking system********\n\n");

    while (ch <= 4) {
        printf("Press 1 for create account..\n");
        printf("Press 2 for all acoount.. \n");
        printf("Press 3 for user details.. \n");
        printf("press 4 for update account details.. \n");
        printf("Plzz Enter ur choice: ");
        scanf("%d", &ch);
        switch (ch) {
        case 1:
            create_account();
            break;

        case 2:
            all_account();
            break;

        case 3:
            user_details();
            break;

        case 4:
            update_account();
            break;

        default:
            printf("options are not available....\n");
            exit(0);
            break;
        }
    }
}

void create_account() {
    int i;
    FILE *fp;
    fp = fopen("customer.txt", "a+");
    printf("Enter name: ");
    scanf("\n%[^\n]", &a2.name);

retryNumber:
    printf("Enter mobile number: ");
    scanf("%s", &a2.mobile_no);
    if (strlen(a2.mobile_no) != 10) {
        printf("Invalid number plz enter valid number..\n");
        goto retryNumber;
    }
    printf("Enter email: ");
    scanf("%s", &a2.email);
    printf("Gender: ");
    scanf("%s", &a2.gender);
    printf("Enter address: ");
    scanf("\n%[^\n]", &a2.address);
    printf("Enter deposit amount: ");
    scanf("%lld", &a2.balance);
    long long int acNo = ++ACCOUNT_NUMBER;
    a2.accountNumber = acNo;
    a1[INDEX++] = a2;
    fprintf(fp, "%d,%s,%s,%s,%s,%s,%lld,%lld\n", INDEX, a2.name, a2.mobile_no,
            a2.email, a2.gender, a2.address, acNo, a2.balance);
    fclose(fp);
}
void all_account() {
    int i = 0;
    FILE *fp;
    fp = fopen("customer.txt", "r");
    for (i = 0; i < INDEX; i++) {
        // printf("%d- user details:",i+1);
        // fscanf(fp,"%d[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%lld,%lld\n",INDEX,a1[INDEX].name,a1[INDEX].mobile_no,a1[INDEX].email,a1[INDEX].gender,a1[INDEX].address,&a1[INDEX].accountNumber,&a1[INDEX].balance);
        printf("%d:- %s-%s-%s-%s-%s-%lld-%lld\n", i + 1, a1[i].name,
               a1[i].mobile_no, a1[i].email, a1[i].gender, a1[i].address,
               a1[i].balance, a1[i].accountNumber);
    }
}
void user_details() {
    int i;
    long long int ac_no;
    printf("Enter user account number: ");
    scanf("%lld", &ac_no);
    i = getIndex(ac_no);
    if (i == -1) {
        printf("account not found");
    } else {
        printf("%s-%s-%s-%s-%s-%lld-%lld\n", a1[i].name, a1[i].mobile_no,
               a1[i].email, a1[i].gender, a1[i].address, a1[i].balance,
               a1[i].accountNumber);
    }
}
void update_account() {

    char buffer[1000];
    int i;
    bool found;
    FILE *upd;
    FILE *fp;

    fp = fopen("customer.txt", "r");
    upd = fopen("update", "a+");
    long long int ac_no;
retry:
    printf("Enter user account number: ");
    scanf("%lld", &ac_no);
    for (i = 0; i < INDEX; i++) {
        if (ac_no == a1[i].accountNumber) {
            printf("Enter mobile number: ");
            scanf("%s", &a1[i].mobile_no);
            printf("Enter address: ");
            scanf("%s", a1[i].address);
            printf("Enter email: ");
            scanf("%s", &a1[i].email);
            printf("%s-%s-%s-%s-%s-%lld-%lld", a1[i].name, a1[i].mobile_no,
                   a1[i].email, a1[i].gender, a1[i].address, a1[i].balance,
                   a1[i].accountNumber);
            found = true;
            break;
        } else {
            found = false;
        }
    }
    if (!found) {

        puts("Account number not found plz enter valid account number...\n");
        goto retry;
    }
    int count = 0;
    while ((fgets(buffer, 1000, fp)) != NULL) {
        count++;
        if (count == i + 1)
            fprintf(upd, "%d,%s,%s,%s,%s,%s,%lld,%lld\n", i + 1, a1[i].name,
                    a1[i].mobile_no, a1[i].email, a1[i].gender, a1[i].address,
                    a1[i].accountNumber, a1[i].balance);
        else
            fputs(buffer, upd);
    }

    fclose(upd);
    fclose(fp);
    remove("customer.txt");
    rename("update", "customer.txt");
    printf("\n");
}
void transfer() {
    int i;
    long long int bal;
    long long int acNo;
retry:
    printf("Enter account number: ");
    scanf("%lld", &acNo);
    i = getIndex(acNo);
    if (i == -1) {
        puts("Accont number not found....");
        goto retry;
    }
retryBal:
    printf("Enter ammount: ");
    scanf("%lld", &bal);
    if (currentUser.balance >= bal) {
        currentUser.balance -= bal;
        a1[i].balance += bal;
    } else {
        puts("balance not available..");
        goto retryBal;
    }
    //	printf("amount: %lld\n",a1[i].balance-bal);

    a1[currCustomerIndex] = currentUser;
    saveToFile();
}
void saveToFile() {
    int i;
    FILE *fp = fopen("customer.txt", "w+");
    for (i = 0; i < INDEX; i++)
        fprintf(fp, "%d,%s,%s,%s,%s,%s,%lld,%lld\n", i + 1, a1[i].name,
                a1[i].mobile_no, a1[i].email, a1[i].gender, a1[i].address,
                a1[i].accountNumber, a1[i].balance);
    fclose(fp);
}
int getIndex(long long int acNo) {
    int i;
    for (i = 0; i < INDEX; i++) {
        if (acNo == a1[i].accountNumber) {
            return i;
        }
    }
    return -1;
}
void doTransaction(int choice) {
    int bal;
retry:
    printf("Enter amount: ");
    scanf("%d", &bal);
    if (choice == 1) {
        if (currentUser.balance >= bal) {
            currentUser.balance -= bal;
        } else {
            puts("balance not available..");
            goto retry;
        }
    } else {

        currentUser.balance += bal;
    }
    a1[currCustomerIndex] = currentUser;
    puts("remaining balance ");
    printf("%lld\n", currentUser.balance);

    saveToFile();
}
void details() {
    printf("%s-%s-%s-%s-%s-%lld-%lld\n", currentUser.name, currentUser.email,
           currentUser.mobile_no, currentUser.gender, currentUser.address,
           currentUser.balance, currentUser.accountNumber);
}
