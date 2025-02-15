#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define COLOR_BOLD  "\e[1m"
#define COLOR_OFF   "\e[m"

int arr_len;

typedef struct
{
    int month;
    int year;

} Date;

typedef struct
{
    char accountnumber[20];
    char name[50];
    char mobile[20];
    char email[30];
    double balance;
    Date dateopened;

} Account;

Account accounts[100];

int* getCurrentDate()
{
    int* date = malloc(2 * sizeof(int));
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    date[0] = tm.tm_mon + 1;
    date[1] = tm.tm_year + 1900;
    return date;
}

char* remove_space(char *string)
{
    int i,j;
    char *subs;
    subs=malloc((strlen(string)+1)*sizeof(char));
    strcpy(subs,string);
    int len=strlen(subs);
    for(i=0; i<len; i++)
    {
        if(subs[i]==' ')
        {
            for(j=i; j<len; j++)
                subs[j]=subs[j+1];
            len--;
        }
    }
    return subs;
}

char* get_name()
{
    printf("Enter your name: ");
    char *name = malloc(100 * sizeof(char));
    gets(name);
    int i = 0,space_found = 0;
    while(name[i] != '\0')
    {
        if(!isalpha(name[i]))
        {
            if(name[i] == ' ')
            {
                space_found = 1;
                if(!isalpha(name[i+1]))
                {
                    printf("Invalid name\nEnter a valid name: ");
                    gets(name);
                    space_found = 0;
                    i = 0;
                    continue;
                }
            }
            else
            {
                printf("Invalid name\nEnter a valid name: ");
                gets(name);
                i = 0;
            }
        }
        i++;
        if(name[i] == '\0' && !space_found)
        {
            printf("Invalid name\nEnter a valid name: ");
            gets(name);
            i = 0;
        }
    }
    return name;
}

char* get_email()
{
    char *email = malloc(100 * sizeof(char));
    printf("Enter your Email: ");
    gets(email);
    int i=0;
    int at_found = 0, dot_found = 0;
    while(email[i]!='\0')
    {
        if(email[i] == '@')
        {
            at_found = 1;
        }
        if(email[i] == '.')
        {
            dot_found = 1;
        }

        i++;
        if((email[i] == '\0') && ((!at_found)|| (!dot_found)))
        {
            printf("Invalid email\nEnter another E-mail: ");
            at_found = 0;
            dot_found = 0;
            gets(email);
            i = 0;
        }
    }
    return email;
}

char* get_mobile_number()
{
    char *mobile = malloc(12 * sizeof(char));
    printf("Enter mobile number: ");
    gets(mobile);
    int i;
    while(1)
    {
        i = 0;
        while(mobile[i] != '\0')
            i++;
        if(i != 11)
        {
            printf("Mobile number must be a 11-digit number\nPlease enter another mobile number: ");
            gets(mobile);
            continue;
        }
        i = 0;
        int counter=0;
        while(mobile[i] != '\0')
        {
            if(isdigit(mobile[i]))
            {
                counter++;
            }
            i++;
        }
        if(counter!=11)
        {
            printf("Mobile number must be a 11-digit number\nPlease enter another mobile number: ");
            gets(mobile);
            continue;
        }
        break;
    }
    return mobile;
}

char* get_acc_num()
{
    printf("Please enter account number: ");
    char* x = malloc(11 * sizeof(char));
    gets(x);
    int i;
    while(1)
    {
        i = 0;
        while(x[i] != '\0')
            i++;
        if(i != 10)
        {
            printf("Account number must be a 10-digit number\nPlease enter another account number: ");
            gets(x);
            continue;
        }
        i = 0;
        int counter=0;
        while(x[i] != '\0')
        {
            if(isdigit(x[i]))
            {
                counter++;
            }
            i++;
        }
        if(counter!=10)
        {
            printf("Account number must be a 10-digit number\nPlease enter another account number: ");
            gets(x);
            continue;
        }
        break;
    }
    return x;
}

double get_balance(double current_balance, char ch)
{
    char balance[100];
    gets(balance);
    int i = 0, dot_found = 0;
    while(balance[i] != '\0')
    {
        if(!isdigit(balance[i]))
        {
            if(!dot_found && balance[i] == '.')
            {
                dot_found = 1;
                if(!isdigit(balance[i+1]))
                {
                    printf("Invalid balance\nEnter a valid balance: ");
                    gets(balance);
                    dot_found = 0;
                    i = 0;
                    continue;
                }
            }
            else
            {
                printf("Invalid balance\nPlease enter another balance: ");
                gets(balance);
                i = 0;
                dot_found = 0;
                continue;
            }
        }
        i++;
    }
    double value = atof(balance);
    if(ch != 'n')
    {
        if(value > 10000.0)
        {
            printf("Maximum value to transact is 10,000.0 LE per transaction\n");
            return -1;
        }
        if(ch == 'w')
        {
            if(value > current_balance)
            {
                printf("Available balance is %0.2lf\n", current_balance);
                return -1;
            }
        }
    }
    return value;
}

char get_save_input()
{
    printf("Enter y to confirm or enter n to cancel: ");
    char ans[100];
    gets(ans);
    while(1)
    {
        if(strlen(ans) > 1)
        {
            printf("Invalid input\nEnter y to confirm or enter n to cancel: ");
            gets(ans);
            continue;
        }
        ans[0] = tolower(ans[0]);
        if(ans[0] == 'n' || ans[0] == 'y')
            break;
        else
        {
            printf("Invalid input\nenter y to confirm and enter n to cancel: ");
            gets(ans);
        }
    }
    return ans[0];
}

int get_menu_input(int n)
{
    printf("Enter your choice: ");
    char ans[20];
    gets(ans);
    int ans_int = 0;
    while(1)
    {
        int i = strlen(ans);
        if(i > 2)
        {
            printf("Invalid input\nEnter your choice: ");
            gets(ans);
            continue;
        }
        if(!isdigit(ans[0]) || !isdigit(ans[i-1]))
        {
            printf("Invalid input\nEnter your choice: ");
            gets(ans);
            continue;
        }
        ans_int = atoi(ans);
        if(ans_int > n || ans_int == 0)
        {
            printf("Invalid input\nEnter your choice: ");
            gets(ans);
            continue;
        }

        break;
    }
    return atoi(ans);
}

int Login()
{
    FILE *f1;
    f1 = fopen("users.txt", "r");
    if (f1 == NULL)
    {
        printf("Error opening file");
        exit(0);
    }

    char UN[30], un[30], PW[30], pw[30];
    int found = 0;

    printf("Enter username: ");
    gets(un);
    printf("Enter password: ");
    gets(pw);

    while(!feof(f1))
    {
        fscanf(f1,"%s%s",UN,PW);
        if ((strcmp(UN, un) == 0) && (strcmp(PW, pw) == 0))
        {
            found = 1;
            break;
        }
    }

    if (found)
    {
        printf("Correct Login\n");
    }
    else
    {
        printf("Incorrect Login\n");
    }
    return found;
}

void Quit()
{
    printf("See you soon!\n");
    exit(0);
}

int Load(Account accounts[])
{
    FILE *f2;
    f2=fopen("accounts.txt","r");
    if (f2 == NULL)
    {
        printf("Error opening the file.");
        exit(0);
    }
    char line[100];
    char* token;
    int count = 0;
    while(fgets(line, 100, f2))
    {
        token = strtok(line, ",");
        strcpy(accounts[count].accountnumber,token);

        token = strtok(NULL, ",");
        strcpy(accounts[count].name, token);

        token = strtok(NULL, ",");
        strcpy(accounts[count].email, token);

        token = strtok(NULL, ",");
        accounts[count].balance = atof(token);

        token = strtok(NULL, ",");
        strcpy(accounts[count].mobile, token);

        token = strtok(NULL, ",");
        sscanf(token, "%d-%d", &accounts[count].dateopened.month, &accounts[count].dateopened.year);

        count++;
    }
    fclose(f2);
    return count;
}

void print_month(Account Accounts [],int i)
{
    switch(accounts[i].dateopened.month)
    {
    case 1:
        printf("Date opened: January %d\n\n",accounts[i].dateopened.year);
        break;
    case 2:
        printf("Date opened: February%d\n\n",accounts[i].dateopened.year);
        break;
    case 3:
        printf("Date opened: March %d\n\n",accounts[i].dateopened.year);
        break;
    case 4:
        printf("Date opened: April %d\n\n",accounts[i].dateopened.year);
        break;
    case 5:
        printf("Date opened: May %d\n\n",accounts[i].dateopened.year);
        break;
    case 6:
        printf("Date opened: June %d\n\n",accounts[i].dateopened.year);
        break;
    case 7:
        printf("Date opened: July %d\n\n",accounts[i].dateopened.year);
        break;
    case 8:
        printf("Date opened: August %d\n\n",accounts[i].dateopened.year);
        break;
    case 9:
        printf("Date opened: September %d\n\n",accounts[i].dateopened.year);
        break;
    case 10:
        printf("Date opened: October %d\n\n",accounts[i].dateopened.year);
        break;
    case 11:
        printf("Date opened: November %d\n\n",accounts[i].dateopened.year);
        break;
    case 12:
        printf("Date opened: December %d\n\n",accounts[i].dateopened.year);
        break;
    }
}

void sortby_NAME(Account accounts[],int n)
{
    Account temp;
    for (int i=1; i<n; i++)
    {
        for (int j=0; j<n-i; j++)

        {
            if (strcasecmp(accounts[j].name, accounts[j + 1].name) > 0)
            {
                temp=accounts[j];
                accounts[j]=accounts[j+1];
                accounts[j+1]=temp;
            }
        }
    }
}

void sortby_BALANCE(Account accounts[],int n)
{
    int i,j;
    Account temp;
    for (i=1; i<n; i++)
    {
        for (j=0; j<n-i; j++)
        {
            if (accounts[j].balance>accounts[j+1].balance)
            {
                temp=accounts[j];
                accounts[j]=accounts[j+1];
                accounts[j+1]=temp;
            }
        }
    }
}

void sortby_DATEOPENED(Account accounts[],int n)
{
    int i,j;
    Account temp;
    for (i=1; i<n; i++)
    {
        for (j=0; j<n-i; j++)
        {
            if ((accounts[j].dateopened.year<accounts[j+1].dateopened.year)||(accounts[j].dateopened.year==accounts[j+1].dateopened.year)&&(accounts[j].dateopened.month<accounts[j+1].dateopened.month))
            {
                temp=accounts[j];
                accounts[j]=accounts[j+1];
                accounts[j+1]=temp;
            }
        }
    }
}

void PrintSorted(Account accounts[],int n)
{
    int i;
    printf("1)Sort by name\n2)Sort by balance\n3)Sort by date opened (newest first)\nEnter your choice: ");
    int choice = get_menu_input(3);
    switch(choice)
    {
    case 1:
        sortby_NAME(accounts,n);
        for (i=0; i<n; i++)
        {
            printf("Account Number: %s\n",accounts[i].accountnumber );
            printf("Name: %s\n",accounts[i].name );
            printf("E-mail: %s\n",accounts[i].email );
            printf("Balance: %f\n", accounts[i].balance);
            printf("Mobile: %s\n",accounts[i].mobile );
            print_month(accounts,i);
        }
        break;
    case 2:
        sortby_BALANCE(accounts,n);
        for (i=0; i<n; i++)
        {
            printf("Account Number: %s\n",accounts[i].accountnumber );
            printf("Name: %s\n",accounts[i].name );
            printf("E-mail: %s\n",accounts[i].email );
            printf("Balance: %f\n", accounts[i].balance);
            printf("Mobile: %s\n",accounts[i].mobile );
            print_month(accounts,i);

        }
        break;
    case 3:
        sortby_DATEOPENED(accounts,n);
        for (i=0; i<n; i++)
        {
            printf("Account Number: %s\n",accounts[i].accountnumber );
            printf("Name: %s\n",accounts[i].name );
            printf("E-mail: %s\n",accounts[i].email );
            printf("Balance: %f\n", accounts[i].balance);
            printf("Mobile: %s\n",accounts[i].mobile );
            print_month(accounts,i);
        }
        break;
    default:
        printf("Invalid choice\n");
        break;
    }
}

void Search(Account accounts[], int n)
{
    int found=0,i;
    char an[100];
    strcpy(an,get_acc_num());
    for (i=0; i<n; i++)
    {
        if (strcmp(an,accounts[i].accountnumber) ==0)
        {
            found=1;
            break;
        }
    }
    if (found)
    {
        printf("Account Number:%s\n",accounts[i].accountnumber );
        printf("Name: %s\n",accounts[i].name );
        printf("E-mail: %s\n",accounts[i].email );
        printf("Balance: %f\n", accounts[i].balance);
        printf("Mobile: %s\n",accounts[i].mobile );
        print_month(accounts, i);
    }
    else
        printf("Account is not found.\n");
}

void save_transac(char file_name[], char str[])
{
    FILE *transac;
    transac = fopen(file_name, "r");
    if(transac == NULL)
    {
        fclose(transac);
        transac = fopen(file_name, "w");
        fclose(transac);
        transac = fopen(file_name, "r");
    }
    char temp_arr[100][100];
    int i = 0;
    while(!feof(transac))
    {
        fgets(temp_arr[i],100,transac);
        i++;
    }
    int l = i;
    fclose(transac);
    transac = fopen(file_name, "w");
    fprintf(transac, "%s", str);
    fclose(transac);
    transac = fopen(file_name, "a");
    for(i = 0; i < l; i++)
    {
        fprintf(transac, "%s", temp_arr[i]);
    }
    fclose(transac);
}

void Delete(Account *clients, int n)
{
    char x[100];
    strcpy(x, get_acc_num());
    int i;
    for(i=0; i<n; i++)
    {
        if((strcmp(x, clients[i].accountnumber) == 0))
        {
            if(clients[i].balance == 0.0)
            {
                char ans = get_save_input();
                if(ans == 'y')
                {
                    Account temp = clients[i];
                    clients[i] = clients[n-1];
                    clients[n-1] = temp;
                    arr_len -= 1;
                    Save(clients,arr_len);
                    printf("Deleted successfully\n");
                }
                else
                    printf("Canceled.\n");
            }
            else
                printf("Account can't be deleted because your balance is more than 0.0!\n");
            return;
        }
    }
    printf("Account can't be found!\n");
}

void Modify(Account *client, int n)
{
    char x[100];
    strcpy(x, get_acc_num());
    int i;
    for(i = 0; i < n; i++)
    {
        if(strcmp(x, client[i].accountnumber) == 0)
        {
            char* temp_name;
            temp_name = get_name();
            char* temp_email;
            temp_email = get_email();
            char* temp_mobile;
            temp_mobile = get_mobile_number();
            char ans = get_save_input();
            if(ans == 'y')
            {
                strcpy(client[i].name, temp_name);
                strcpy(client[i].email, temp_email);
                strcpy(client[i].mobile, temp_mobile);
                Save(client,n);
                printf("Changes saved.\n");
            }
            else
                printf("Canceled.\n");
            return;
        }
    }
    printf("Account can't be found!\n");

}

void Withdraw(Account *client, int n)
{
    char x[100];
    strcpy(x, get_acc_num());
    int i;
    for(i = 0; i < n; i++)
    {
        if(strcmp(client[i].accountnumber, x) == 0)
        {
            printf("How much do you want to withdraw from your balance: ");
            double w = get_balance(client[i].balance, 'w');
            while(w == -1)
            {
                printf("1)Return to main menu\n2)Try again\n");
                int choice = get_menu_input(2);
                switch(choice)
                {
                case 1:
                    return;
                case 2:
                    printf("How much do you want to withdraw from your balance: ");
                    w = get_balance(client[i].balance, 'w');
                    break;
                }
            }
            double temp_balance = client[i].balance - w;
            char ans = get_save_input();
            if(ans == 'y')
            {
                client[i].balance = temp_balance;
                char file_name[100];
                strcpy(file_name, client[i].accountnumber);
                strcat(file_name, ".txt");
                char with[200];
                sprintf(with,"%0.2lf",w);
                strcat(with," has been withdrawn from this account\n");
                save_transac(file_name, with);
                Save(client,arr_len);
                printf("Successful transaction.\n");
                return;
            }
            else
            {
                printf("Canceled.\n");
                return;
            }

        }
    }
    printf("Account can't be found!\n");
}

void Deposit(Account *client, int n)
{
    char x[100];
    strcpy(x, get_acc_num());
    int i;
    for(i = 0; i < n; i++)
    {
        if(strcmp(client[i].accountnumber, x) == 0)
        {
            printf("How much do you want to deposit to your balance: ");
            double d = get_balance(client[i].balance, 'd');
            while(d == -1)
            {
                printf("1)Return to main menu\n2)Try again\n");
                int choice = get_menu_input(2);
                switch(choice)
                {
                case 1:
                    return;
                case 2:
                    printf("How much do you want to deposit to your balance: ");
                    d = get_balance(client[i].balance, 'd');
                    break;
                }
            }
            double temp_balance = client[i].balance + d;
            char ans = get_save_input();
            if(ans == 'y')
            {
                client[i].balance = temp_balance;
                char file_name[100];
                strcpy(file_name, client[i].accountnumber);
                strcat(file_name, ".txt");
                char dep[200];
                sprintf(dep,"%0.2lf",d);
                strcat(dep," has been deposited to this account\n");
                save_transac(file_name, dep);
                Save(client, arr_len);
                printf("Successful transaction.\n");
                return;
            }
            else
            {
                printf("Canceled.\n");
                return;
            }
        }
    }
    printf("Account can't be found!\n");
}

void Transfer(Account *client, int n)
{
    printf("Withdraw account:\n");
    char from_x[100];
    strcpy(from_x, get_acc_num());
    printf("Deposit account:\n");
    char to_x[100];
    strcpy(to_x, get_acc_num());
    while(strcmp(to_x, from_x) == 0)
    {
        printf("Invalid Data, withdraw account and deposit account are the same.\n");
        printf("1)Return to main menu\n2)Try again\n");
        int choice = get_menu_input(2);
        switch(choice)
        {
        case 1:
            return;
        case 2:
            printf("Withdraw account:\n");
            strcpy(from_x, get_acc_num());
            printf("Deposit account:\n");
            strcpy(to_x, get_acc_num());
            continue;
        }
    }
    int i, j;
    for(i = 0; i < n; i++)
    {
        if(strcmp(from_x, client[i].accountnumber) == 0)
        {
            for(j = 0; j < n; j++)
            {
                if(strcmp(to_x, client[j].accountnumber) == 0)
                {
                    printf("How much do you want to transfer: ");
                    double t = get_balance(client[i].balance, 'w');
                    while(t == -1)
                    {
                        printf("1)return to main menu\n2)try again\n");
                        int choice = get_menu_input(2);
                        switch(choice)
                        {
                        case 1:
                            return;
                        case 2:
                            printf("How much do you want to transfer: ");
                            t = get_balance(client[i].balance, 'w');
                            break;
                        }
                    }
                    double temp_balance_with = client[i].balance - t;
                    double temp_balance_dep = client[j].balance + t;
                    char ans = get_save_input();
                    if(ans == 'y')
                    {
                        client[i].balance = temp_balance_with;
                        client[j].balance = temp_balance_dep;
                        Save(client, arr_len);

                        char file_name_with[100], file_name_dep[100], with[100], dep[100];

                        strcpy(file_name_with, client[i].accountnumber);
                        strcat(file_name_with, ".txt");
                        sprintf(with,"%0.2lf",t);
                        strcat(with," has been withdrawn from this account\n");
                        save_transac(file_name_with, with);

                        strcpy(file_name_dep, client[j].accountnumber);
                        strcat(file_name_dep, ".txt");
                        sprintf(dep,"%0.2lf",t);
                        strcat(dep," has been deposited to this account\n");
                        save_transac(file_name_dep, dep);

                        printf("Successful transaction.\n");
                        return;
                    }
                    else
                    {
                        printf("Canceled.\n");
                        return;
                    }
                }
            }
        }
    }
    printf("Account can't be found!\n");
}

void Report(Account *client, int n)
{
    char x[100];
    strcpy(x, get_acc_num());
    int i;
    for(i = 0; i < n; i++)
    {
        if(strcmp(x, client[i].accountnumber) == 0)
        {
            char file_name[100];
            strcpy(file_name, client[i].accountnumber);
            strcat(file_name, ".txt");
            FILE *fl_ptr = NULL;
            fl_ptr = fopen(file_name, "r");
            char ch = fgetc(fl_ptr);
            if(fl_ptr == NULL || ch == EOF)
            {
                printf("No transactions to print.\n");
                return;
            }
            int counter = 0;
            fseek(fl_ptr, 0, SEEK_SET);
            char str[200][200];
            while(!feof(fl_ptr))
            {
                fgets(str[counter], 200, fl_ptr);
                printf("%s", str[counter]);
                counter++;
                if(counter >= 5)
                    return;
            }
            return;
        }
    }
    printf("Account can't be found!\n");
}

void Save(Account accounts[],int n)
{
    FILE *f2;
    f2=fopen("accounts.txt","w");
    if (f2 == NULL)
    {
        printf("Error opening the file");
        exit(1);
    }
    char ch='\n';
    int i;
    for(i = 0 ; i < n; i++)
    {
        fprintf(f2,"%s,",accounts[i].accountnumber );
        fprintf(f2,"%s,",accounts[i].name );
        fprintf(f2,"%s,",accounts[i].email );
        fprintf(f2,"%.2lf,", accounts[i].balance);
        fprintf(f2,"%s,",accounts[i].mobile );
        fprintf(f2,"%d-%d", accounts[i].dateopened.month,accounts[i].dateopened.year);
        if(i!=n-1)
            fputc(ch,f2);
    }
    fclose(f2);
}

void AdvancedSearch(Account accounts[],int n)
{
    char name[20];
    printf("Enter name to search for: ");
    gets(name);
    int m;
    for(m=0; m<strlen(name); m++)
        name[m]=tolower(name[m]);
    int i;
    int index[n];
    int z=0;
    for(i=0; i<n; i++)
    {
        char temp[20];
        strcpy(temp,accounts[i].name);
        int g;
        strcpy(temp,remove_space(temp));
        for(g=0; g<strlen(temp); g++)
            temp[g]=tolower(temp[g]);
        char *sub;
        sub=strstr(temp,name);
        if(sub)
        {
            index[z]=i;
            z++;
        }
    }
    if(z!=0)
    {
        int j;
        for (j=0; j<z; j++)
        {
            printf("Account Number: %s\n",accounts[*(index+j)].accountnumber );
            printf("Name: %s\n",accounts[*(index+j)].name );
            printf("E-mail: %s\n",accounts[*(index+j)].email );
            printf("Balance: %f\n", accounts[*(index+j)].balance);
            printf("Mobile: %s\n",accounts[*(index+j)].mobile );
            print_month(accounts, *(index+j));
        }
    }
    else
        printf("No account includes that name\n");
}

void Add(Account accounts[], int n)
{
    char *temp_acc_no, *temp_mob_no, *temp_name, *temp_email, choice;
    int *time, unique = 0, i;
    double temp_balance;
    time = getCurrentDate();
    temp_acc_no = get_acc_num();
    while(!unique)
    {
        for(i = 0; i < n; i++)
        {
            if(strcmp(temp_acc_no, accounts[i].accountnumber) == 0)
            {
                printf("Account number is already taken\n");
                temp_acc_no = get_acc_num();
                continue;
            }
        }
        unique = 1;
    }
    temp_name = get_name();
    temp_email = get_email();
    printf("Enter balance: ");
    temp_balance = get_balance(0.0, 'n');
    temp_mob_no = get_mobile_number();
    choice = get_save_input();
    if(choice == 'n')
        return;
    arr_len++;
    strcpy(accounts[arr_len-1].accountnumber,temp_acc_no);
    strcpy(accounts[arr_len-1].name, temp_name);
    strcpy(accounts[arr_len-1].email, temp_email);
    accounts[arr_len-1].balance = temp_balance;
    strcpy(accounts[arr_len-1].mobile, temp_mob_no);
    accounts[arr_len-1].dateopened.month = time[0];
    accounts[arr_len-1].dateopened.year = time[1];

    Save(accounts, arr_len);
    printf("Saved successfully!\n");
}

void Menu(Account accounts[])
{
    printf("1)LOGIN\n2)QUIT\n");
    int choice1 = get_menu_input(2), choice2;
    if(choice1 == 1)
    {
        int login_success = Login();
        while(1)
        {
            if(!login_success)
            {
                printf("1)LOGIN\n2)QUIT\n");
                choice1 = get_menu_input(2);
                if(choice1 == 2)
                    Quit();
                login_success = Login();
            }
            else
                break;
        }
        arr_len = Load(accounts);
    }
    switch(choice1)
    {
    case 1:
        while(1)
        {
            printf("-------------------------------------------------\n");
            printf("1)ADD\n2)DELETE\n3)MODIFY\n4)SEARCH\n5)ADVANCED SEARCH\n6)WITHDRAW\n7)DEPOSIT\n8)TRANSFER\n9)REPORT\n10)PRINT\n11)QUIT\n");
            choice2 = get_menu_input(11);
            switch(choice2)
            {
            case 1:
                printf("Add:\n");
                Add(accounts, arr_len);
                break;
            case 2:
                printf("Delete:\n");
                Delete(accounts,arr_len);
                break;
            case 3:
                printf("Modify:\n");
                Modify(accounts,arr_len);
                break;
            case 4:
                printf("Search:\n");
                Search(accounts, arr_len);
                break;
            case 5:
                printf("Advanced Search:\n");
                AdvancedSearch(accounts, arr_len);
                break;
            case 6:
                printf("Withdraw:\n");
                Withdraw(accounts,arr_len);
                break;
            case 7:
                printf("Deposit:\n");
                Deposit(accounts,arr_len);
                break;
            case 8:
                printf("Transfer:\n");
                Transfer(accounts,arr_len);
                break;
            case 9:
                printf("Report:\n");
                Report(accounts,arr_len);
                break;
            case 10:
                printf("Print:\n");
                PrintSorted(accounts, arr_len);
                break;
            case 11:
                Quit();
                break;
            default:
                printf("Invalid choice\n");
            }
        }
        break;
    case 2:
        Quit();
        break;
    default:
        printf("Invalid choice\n");
        Menu(accounts);
    }
}

int main()
{
    Menu(accounts);
    return 0;
}
