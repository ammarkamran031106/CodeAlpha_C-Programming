// TASK 4: High - Banking System (Mini Project)
// Build a Bank Account Management System in C. 
// Functions: Deposit, Withdraw, Balance Enquiry, and Exit. 
// Implement using functions, structures, and file handling.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account
{
    int accountNo;
    char name[50];
    float balance;
};

void createAccount()
{
    FILE *fp = fopen("accounts.dat", "rb+");

    if(fp == NULL)
        fp = fopen("accounts.dat", "wb+");

    Account acc, temp;

    printf("Enter Account Number: ");
    scanf("%d",&acc.accountNo);

    rewind(fp);

    while(fread(&temp,sizeof(Account),1,fp))
    {
        if(temp.accountNo==acc.accountNo)
        {
        	printf("\n");
            printf("Account Number Already Exists! \n");
            fclose(fp);
            return;
        }
    }

    printf("Enter Account Holder Name: ");
    scanf("%s",acc.name);

    printf("Enter Initial Deposit: ");
    scanf("%f",&acc.balance);

    fseek(fp,0,SEEK_END);
    fwrite(&acc,sizeof(Account),1,fp);

    fclose(fp);

    printf("\nAccount Created Successfully!\n");
}

void deposit()
{
    FILE *fp=fopen("accounts.dat","rb");
    FILE *temp=fopen("temp.dat","wb");

    if(fp==NULL)
    {
        printf("No Accounts Found!\n");
        return;
    }

    int accNo;
    float amount;
    int found=0;

    Account acc;

    printf("Enter Account Number: ");
    scanf("%d",&accNo);

    printf("Enter Deposit Amount: ");
    scanf("%f",&amount);

    while(fread(&acc,sizeof(Account),1,fp))
    {
        if(acc.accountNo==accNo)
        {
            acc.balance+=amount;
            found=1;
        }

        fwrite(&acc,sizeof(Account),1,temp);
    }

    fclose(fp);
    fclose(temp);

    remove("accounts.dat");
    rename("temp.dat","accounts.dat");

    if(found)
        printf("\nAmount Deposited Successfully!\n");
    else
        printf("\nAccount Not Found!\n");
}

void withdraw()
{
    FILE *fp=fopen("accounts.dat","rb");
    FILE *temp=fopen("temp.dat","wb");

    if(fp==NULL)
    {
        printf("No Accounts Found!\n");
        return;
    }

    int accNo;
    float amount;
    int found=0;

    Account acc;

    printf("Enter Account Number: ");
    scanf("%d",&accNo);

    printf("Enter Withdraw Amount: ");
    scanf("%f",&amount);

    while(fread(&acc,sizeof(Account),1,fp))
    {
        if(acc.accountNo==accNo)
        {
            found=1;

            if(acc.balance>=amount)
            {
                acc.balance-=amount;
            }
            else
            {
                printf("\nInsufficient Balance!\n");
            }
        }

        fwrite(&acc,sizeof(Account),1,temp);
    }

    fclose(fp);
    fclose(temp);

    remove("accounts.dat");
    rename("temp.dat","accounts.dat");

    if(found)
        printf("\nTransaction Completed!\n");
    else
        printf("\nAccount Not Found!\n");
}

void balanceEnquiry()
{
    FILE *fp=fopen("accounts.dat","rb");

    if(fp==NULL)
    {
        printf("No Accounts Found!\n");
        return;
    }

    int accNo;
    int found=0;

    Account acc;

    printf("Enter Account Number: ");
    scanf("%d",&accNo);

    while(fread(&acc,sizeof(Account),1,fp))
    {
        if(acc.accountNo==accNo)
        {
            printf("\nAccount Number : %d\n",acc.accountNo);
            printf("Name           : %s\n",acc.name);
            printf("Balance        : %.2f\n",acc.balance);

            found=1;
            break;
        }
    }

    if(!found)
        printf("\nAccount Not Found!\n");

    fclose(fp);
}

void displayAccounts()
{
    FILE *fp=fopen("accounts.dat","rb");

    if(fp==NULL)
    {
        printf("No Accounts Found!\n");
        return;
    }

    Account acc;

    printf("\n========== ALL ACCOUNTS ==========\n");

    while(fread(&acc,sizeof(Account),1,fp))
    {
        printf("\nAccount Number : %d  \n",acc.accountNo);
        printf("Name           : %s   \n",acc.name);
        printf("Balance        : %.2f  \n",acc.balance);
    }

    fclose(fp);
}

int main()
{
    int choice;

    do
    {
        printf("\n========== BANK MANAGEMENT ==========\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Balance Enquiry\n");
        printf("5. Display All Accounts\n");
        printf("6. Exit\n");

        printf("Enter Choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                createAccount();
                break;

            case 2:
                deposit();
                break;

            case 3:
                withdraw();
                break;

            case 4:
                balanceEnquiry();
                break;

            case 5:
                displayAccounts();
                break;

            case 6:
                printf("\nThank You!\n");
                break;

            default:
                printf("\nInvalid Choice!\n");
        }

    }while(choice != 6);

    return 0;
}
