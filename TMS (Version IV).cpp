#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <math.h>

using namespace std;

//  DATA STRUCTURES
const int arrSize = 20;
string name[arrSize];
string username[arrSize];
string password[arrSize];
string email[arrSize];
string pkgType[arrSize];
int usage[arrSize];
float dueBill[arrSize];
int sortedIndices[arrSize]; // For sorting feature

//  For pending feature.
int pending = 0;
string tempName[5];
string tempUsername[5];
string tempPassword[5];
string tempEmail[5];
string tempPkgType[5];

// For feedback
int feedbackCount = 0;
string feedback[5];
int feedbackUserIndex[5];

// For username recommendation
string recUsername[3];
int recCount = 0;

// Default Packages Details
int ecSub = 10;
float ecPerMin = .01;
int ecLim = 1000;
int pSub = 25;
float pPerMin = .015;
int pLim = 10000;

// Global Variables essentially required
int users = 0;          // total users
int loginCustomer = -1; // to keep track which registered customer has logged in

// Admin Default Login Details
string sysUsername = "Admin";
string sysPass = "ad@tms.com";
//  Function Prototypes
void header();
void clearScreen();
char userType();
bool verification(string username, string password, string tempUsername, string tempPassword);
int validateInput(char input, int start, int end);
int managerMenu();
void packageAlter(char packageType);
void viewCustomers();
int getMaxIdx(int c);
void sortCustomers();
void cancelRegistration(int cancelReg);
void approveReg(char appReg);
void manFeedback();
bool validateCredentials(string oldC, string newC);
char cusType();
int rCusMenu();
void updateUsage();
void checkPayable();
void pkgUpgrade();
void cusFeedback();
int nCusMenu();
void packageView();
void viewServices();
void viewPaymentMethod();
bool validateUsername(string checkUsername);
bool validatePassword(string checkPassword);
bool validateEmail(string checkEmail);
void recommendUsername(string username);
void nRegistration(string nName, string nUsername, string nPassword, string nEmail, string nPkgType);
string slice(string line, int field);
int convert(string n);
void load();
void store();
void calculateBill();
void header()
{
    cout << "\n\n\n";
    cout << " |       _______   __  __    _____      |" << endl;
    cout << " |      |__   __| |  \\/  |  / ____|     |" << endl;
    cout << " |         | |    | \\  / | | (___       |" << endl;
    cout << " |         | |    | |\\/| |  \\___ \\      |" << endl;
    cout << " |         | |    | |  | |  ____) |     |  " << endl;
    cout << " |         |_|    |_|  |_| |_____/      |\n\n\n";
    cout << "-----------------------------------------" << endl;
    cout << "  Welcome to Telephone Management System" << endl;
    cout << "-----------------------------------------" << endl;
}
void clearScreen()
{
    system("pause");
    system("cls");
}
char userType()
{
    char userTypeOp = ' ';
    cout << "Which type of user you are? \nManager(M)/Customer(C) \n \n(Press 0 To Exit) " << endl;
    cin >> userTypeOp;
    while (userTypeOp != 'M' && userTypeOp != 'C' && userTypeOp != '0')
    {
        cout << "Wrong Selelction!!! Select from given menu. " << endl;
        cin >> userTypeOp;
    }
    return userTypeOp;
}
bool verification(string username, string password, string tempUsername, string tempPassword)
{
    system("cls");
    if (username == tempUsername && password == tempPassword)
    {
        return true;
    }
    return false;
}
int validateInput(char input, int start, int end)
{
    int check = input - 48;

    while (!(check >= start && check <= end))
    {
        cout << "You selected wrong option. Select from Given Menu" << endl;
        cin >> input;
        check = input - 48;
    }

    return check;
}
int managerMenu()
{
    char managerMenuOp;
    cout << "Welcome Back, Manager \nWhat do you Want to do today? \n";
    cout << "1- Alter Packages. \n";
    cout << "2- Check Total Number if users. \n";
    cout << "3- Check Customers according to their Usage time \n";
    cout << "4- Cancel registration of any user \n";
    cout << "5- Approve Requests for new Registrations- " << pending << "\n";
    cout << "6- See if any user has given Suggestion/Complaint/Feedback- " << feedbackCount << "\n";
    cout << "7 -Change your Username or password. \n";
    cout << "8- Log out." << endl;

    cin >> managerMenuOp;

    return validateInput(managerMenuOp, 1, 8);
}

void packageAlter(char packageType)
{
    if (packageType == 'E')
    {
        cout << "Previous Economy Package :- " << endl;
        cout << "Subscription Fee : " << ecSub << "$ \n"
             << "Per Minute Charges : " << ecPerMin << "$ \n"
             << "Limit : " << ecLim << " Minutes " << endl;
        cout << "-----------------------------" << endl;
        cout << "Enter New Subscription Fee: " << endl;
        cin >> ecSub;
        cout << "Enter New per minute charges :" << endl;
        cin >> ecPerMin;
        cout << "Enter New Minute Limit :" << endl;
        cin >> ecLim;
    }
    if (packageType == 'P')
    {
        cout << "Previous Premium Package :- " << endl;
        cout << "Subscription Fee : " << pSub << "$ \n"
             << "Per Minute Charges : " << pPerMin << "$ \n"
             << "Limit : " << pLim << " Minutes " << endl;
        cout << "-----------------------------" << endl;
        cout << "Enter New Subscription Fee: " << endl;
        cin >> pSub;
        cout << "Enter New per minute charges :" << endl;
        cin >> pPerMin;
        cout << "Enter New Minute Limit :" << endl;
        cin >> pLim;
    }
}

void viewCustomers()
{
    cout << "Total Customers : " << users << endl;
    if (users > 0)
    {
        cout << "Details:- \n";
        cout << "Reg#\tName\t\tPkg\tUsage\tDue-Bill" << endl;
        for (int i = 0; i < users; i++)
        {
            cout << i + 1 << "-\t" << name[i] << "\t" << pkgType[i] << "\t" << usage[i] << "\t" << dueBill[i] << endl;
        }
    }
}

int getMaxIdx(int c)
{
    int largest = 0;
    int largestIndex = 0;
    for (int i = 0; i < users; i++)
    {
        for (int j = 0; j <= c; j++)
        {
            if (i == sortedIndices[j])
            {
                goto jump;
            }
        }
        if (usage[i] >= largest)
        {
            largest = usage[i];
            largestIndex = i;
        }
    jump:
        continue;
    }
    return largestIndex;
}
void sortCustomers()
{
    // Initializing SortedIndices Array to eliminate possible errors.
    for (int i = 0; i < users; i++)
    {
        sortedIndices[i] = -1;
    }

    // Populating Sorted Indices Array.
    for (int i = 0; i < users; i++)
    {
        int largestIndex = getMaxIdx(i);
        sortedIndices[i] = largestIndex;
    }

    // Printing Sorted records
    cout << "Total Customers : " << users << endl;
    if (users > 0)
    {
        cout << "Details:- \n";
        cout << "Reg#\tName\t\tPkg\tUsage\tDue-Bill" << endl;
        for (int i = 0; i < users; i++)
        {
            cout << sortedIndices[i] + 1 << "-\t" << name[sortedIndices[i]] << "\t" << pkgType[sortedIndices[i]] << "\t" << usage[sortedIndices[i]] << "\t" << dueBill[sortedIndices[i]] << endl;
        }
    }
}
void cancelRegistration(int cancelReg)
{
    users = users - 1;
    for (int i = cancelReg; i < users; i++)
    {
        name[i] = name[i + 1];
        username[i] = username[i + 1];
        password[i] = password[i + 1];
        pkgType[i] = pkgType[i + 1];
        usage[i] = usage[i + 1];
        dueBill[i] = dueBill[i + 1];
    }
}
void approveReg(char appReg)
{
    int indApp = appReg - 49;
    if (appReg == 'A')
    {

        for (int i = 0; i < pending; i++)
        {
            name[users + i] = tempName[i];
            username[users + i] = tempUsername[i];
            password[users + i] = tempPassword[i];
            email[users + i] = tempEmail[i];
            pkgType[users + i] = tempPkgType[i];
        }
        users = users + pending;
        pending = 0;
    }
    else if (appReg == 'B')
    {
        pending = 0;
    }

    else if (indApp >= 0 && indApp <= pending)
    {
        name[users] = tempName[indApp];
        username[users] = tempUsername[indApp];
        password[users] = tempPassword[indApp];
        email[users] = tempEmail[indApp];
        pkgType[users] = tempPkgType[indApp];

        users = users + 1;
        pending = pending - 1;

        for (int i = appReg; i < pending; i++)
        {
            tempName[i] = tempName[i + 1];
            tempUsername[i] = tempUsername[i + 1];
            tempPassword[i] = tempPassword[i + 1];
            tempEmail[i] = tempEmail[i + 1];
            tempPkgType[i] = tempPkgType[i + 1];
        }
    }
    else
    {
        cout << "Invalid Input" << endl;
    }
}
void manFeedback()
{
    for (int i = 0; i < feedbackCount; i++)
    {
        cout << i + 1 << "- " << feedback[i] << " ----- " << name[feedbackUserIndex[i]] << endl;
    }
    feedbackCount = 0;
}
bool validateCredentials(string oldC, string newC)
{
    if (oldC == newC)
    {
        return false;
    }

    return true;
}
char cusType()
{
    char cusTypeOp;
    cout << "Which type of Customer you are? \nRegistered(R)/New Visitor(N) \n \n(Press 0 To go back to user type menu.) " << endl;
    cin >> cusTypeOp;
    while (cusTypeOp != 'R' && cusTypeOp != 'N' && cusTypeOp != '0')
    {
        cout << "Wrong Selelction!!! Select from given menu. " << endl;
        cin >> cusTypeOp;
    }
    return cusTypeOp;
}
int rCusMenu()
{
    char rCusMenuOp;

    cout << "Welcome... What do you want to do today??" << endl;
    cout << "1- Update your usage details." << endl;
    cout << "2- Check the Payeable due amount." << endl;
    cout << "3- Upgrade Your Package." << endl;
    cout << "4- Cancel Your Registration." << endl;
    cout << "5- Give Suggestions/Complaint/Feedback" << endl;
    cout << "6 - Change your username or password." << endl;
    cout << "7- Log out." << endl;
    cin >> rCusMenuOp;

    return validateInput(rCusMenuOp, 1, 7);
}
void updateUsage()
{
    cout << "Enter your usage: ";
    cin >> usage[loginCustomer];
}
void checkPayable()
{
    cout << "Total payable : ";
    if (pkgType[loginCustomer] == "Economy")
    {
        cout << ecSub + usage[loginCustomer] * ecPerMin << "$" << endl;
    }
    else
    {
        cout << pSub + usage[loginCustomer] * pPerMin << "$" << endl;
    }
}
void calculateBill()
{
    for (int i = 0; i < users; i++)
    {
        if (pkgType[i] == "Economy")
    {
        dueBill[i] =  ecSub + usage[i] * ecPerMin;
    }
    else
    {
        dueBill[i] = pSub + usage[i] * pPerMin;
    }
    }
}
void pkgUpgrade()
{
    if (pkgType[loginCustomer] == "Economy")
    {
        cout << "current Package Type : Economy " << endl;
        cout << "Upgraded to Premium." << endl;
        pkgType[loginCustomer] = "Premium";
    }
    else
    {
        cout << "You Already have Premium Package. " << endl;
    }
}
void cusFeedback()
{
    if (feedbackCount < 5)
    {
        cout << "Enter Your Suggestion/Feedback here : " << endl;
        cin.ignore();
        getline(cin, feedback[feedbackCount]);
        feedbackUserIndex[feedbackCount] = loginCustomer;
        feedbackCount++;
    }
    else
    {
        cout << "Feedback capacity filled!!! " << endl;
    }
}
int nCusMenu()
{
    char nCusMenuOp;
    cout << "WELCOME HERE..." << endl;
    cout << "What will you like to do here?" << endl;
    cout << "1- Check Packages available." << endl;
    cout << "2- See the services we provide." << endl;
    cout << "3- Check our biling system." << endl;
    cout << "4- GET YOURSELF REGISTERED!!!!" << endl;
    cout << "5 - Go back to Customer Type Menu" << endl;

    cin >> nCusMenuOp;

    return validateInput(nCusMenuOp, 1, 5);
}
void packageView()
{
    cout << "Packages             Economy     Premium\n"
         << endl;
    cout << "Subscription Fee     " << ecSub << "          " << pSub << endl;
    cout << "Limit                " << ecLim << "        " << pLim << endl;
    cout << "Per Minute Charges   " << ecPerMin << "        " << pPerMin << endl;
}
void viewServices()
{
    cout << "Services Provided: \n 1- Calling \n 2- Meassaging \n 3- Postpaid Calling" << endl;
}
void viewPaymentMethod()
{
    cout << "1-Cash \n2-Online payments" << endl;
}
bool validateUsername(string checkUsername)
{
    for (int i = 0; i < users; i++)
    {
        if (username[i] == checkUsername)
        {
            return false;
        }
    }
    return true;
}
bool validatePassword(string checkPassword)
{
    bool checks[4];
    for (int i = 0; i < 4; i++)
    {
        checks[i] = false;
    }
    for (int i = 0; checkPassword[i] != '\0'; i++)
    {
        int temp = checkPassword[i];
        if ((temp >= 33 && temp <= 47) || (temp >= 58 && temp <= 64) || (temp >= 91 && temp <= 96) || (temp >= 123 && temp <= 126))
        {
            checks[0] = true;
        }
        if (temp >= 48 && temp <= 57)
        {
            checks[1] = true;
        }
        if (temp >= 65 && temp <= 90)
        {
            checks[2] = true;
        }
        if (temp >= 97 && temp <= 122)
        {
            checks[3] = true;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        if (checks[i] == false)
        {
            return false;
        }
    }
    return true;
}
bool validateEmail(string checkEmail)
{
    for (int i = 0; i < checkEmail.length(); i++)
    {
        if (checkEmail[i] == '@')
        {
            return true;
        }
    }
    return false;
}
void recommendUsername(string username)
{
    string retain = username;
    int append = 48;
    int count = 0;
    while (true)
    {
        username += append;
        if (validateUsername(username))
        {
            recUsername[count] = username;
            count++;
        }
        if (count == 3)
        {
            break;
        }
        append++;
        username = retain;
    }
}
void nRegistration(string nName, string nUsername, string nPassword, string nEmail, string nPkgType)
{
    tempName[pending] = nName;
    tempUsername[pending] = nUsername;
    tempPassword[pending] = nPassword;
    tempEmail[pending] = nEmail;
    tempPkgType[pending] = nPkgType;
    pending++;
}

// Store and Load

string slice(string line, int field)
{
    string word;
    int comma = 0;

    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == ',')
        {
            comma++;
        }
        else if (comma == field)
        {
            word += line[i];
        }
    }
    return word;
}
int convert(string n)
{
    if (n == "0")
    {
        return 0;
    }
    float num = 0;
    int x;
    for (int i = 0; i < n.length(); i++)
    {
        x = (n[n.length() - i - 1]) - 48;
        num = num + x * pow(10, i);
    }

    return num;
}
void load()
{
    fstream file;
    string line;
    int i = -2;
    string fUsage;
    string fBill;
    file.open("TMS.txt", ios::in);
    while (!file.eof())
    {
        getline(file, line);
        if (i == -2)
        {
            sysUsername = line;
        }
        else if (i == -1)
        {
            sysPass = line;
        }
        else
        {

            name[i] = slice(line, 0);
            username[i] = slice(line, 1);
            password[i] = slice(line, 2);
            email[i] = slice(line, 3);
            pkgType[i] = slice(line, 4);
            fUsage = slice(line, 5);
            usage[i] = convert(fUsage);
            fBill = slice(line, 6);
            dueBill[i] = convert(fBill);
        }
        i++;
    }
    users = i - 1;
    file.close();
}
void store()
{
    fstream file;
    file.open("TMS.txt", ios::out);
    file << sysUsername << endl;
    file << sysPass << endl;
    for (int i = 0; i < users; i++)
    {
        file << name[i] << "," << username[i] << "," << password[i] << "," << email[i] << "," << pkgType[i] << "," << usage[i] << "," << dueBill[i] << endl;
    }
    file << "\b\b";
    file.close();
}

//               Main                   //

main()
{
    load();
    header();

    char userTypeOp = userType();
    system("cls");

    while (userTypeOp == 'M' || userTypeOp == 'C')
    {
        if (userTypeOp == 'M')
        {
            system("cls");
            cout << "Enter Username: ";
            string adUsername;
            cin >> adUsername;
            cout << "Enter Password: ";
            string adPassword;
            cin >> adPassword;

            if (verification(sysUsername, sysPass, adUsername, adPassword))
            {
                int managerMenuOp = managerMenu();
                while (managerMenuOp < 8)
                {
                    calculateBill();
                    if (managerMenuOp == 1)
                    {
                        system("cls");
                        char packageType;
                        cout << "Which Package you want to alter? \nEconomy Package (E) \nPremium Package (P)" << endl;
                        cin >> packageType;
                        packageAlter(packageType);
                        cout << "PACKAGE ALTERED..." << endl;
                        clearScreen();
                        managerMenuOp = managerMenu();
                    }
                    if (managerMenuOp == 2)
                    {
                        system("cls");
                        viewCustomers();
                        clearScreen();
                        managerMenuOp = managerMenu();
                    }
                    if (managerMenuOp == 3)
                    {
                        system("cls");
                        if (users > 0)
                        {
                            sortCustomers();
                        }
                        else
                        {
                            cout << "No Registered Customers yet." << endl;
                        }
                        clearScreen();
                        managerMenuOp = managerMenu();
                    }
                    if (managerMenuOp == 4)
                    {
                        system("cls");
                        int cancelReg;
                        if (users > 0)
                        {
                            cout << "Which Customers Registration You want to cancel?" << endl;
                            cout << "Name\t\tEmail\t\t\tPkg\tUsage\tDue-Bill" << endl;
                            for (int i = 0; i < users; i++)
                            {
                                cout << i + 1 << "- " << name[i] << "\t" << email[i] << "\t" << pkgType[i] << "\t" << usage[i] << "\t" << dueBill[i] << endl;
                            }
                            cin >> cancelReg;
                            cancelReg = cancelReg - 1;
                            cancelRegistration(cancelReg);
                        }
                        else
                        {
                            cout << "No Registered Customers yet." << endl;
                        }
                        clearScreen();
                        managerMenuOp = managerMenu();
                    }
                    if (managerMenuOp == 5)
                    {
                        system("cls");
                        char appReg;
                        if (pending > 0)
                        {
                            cout << "There are Pending Request(s)..." << endl;
                            cout << "Name\t\tUsername\tEmail\t\t\tPackage\n";
                            for (int i = 0; i < pending; i++)
                            {
                                cout << i + 1 << "- " << tempName[i] << "\t" << tempUsername[i] << "\t" << tempEmail[i] << "\t\t" << tempPkgType[i] << endl;
                            }
                            cout << "\nA- Approve All\nB- Delete All\n\t\tOr\nEnter index of customer to approve request." << endl;
                            cin >> appReg;
                            approveReg(appReg);
                        }
                        else
                        {
                            cout << "No pending requests.";
                        }
                        clearScreen();
                        managerMenuOp = managerMenu();
                    }
                    if (managerMenuOp == 6)
                    {
                        system("cls");
                        if (feedbackCount > 0)
                        {
                            manFeedback();
                        }
                        else
                        {
                            cout << " No feedback yet... " << endl;
                        }
                        clearScreen();
                        managerMenuOp = managerMenu();
                    }
                    if (managerMenuOp == 7)
                    {
                        system("cls");
                        cout << "Change:\n1-Username\n2-Password\n3-Both " << endl;
                        char response;
                        cin >> response;
                        system("cls");
                        if (response == '1')
                        {
                            cout << "Enter New Usename: ";
                            string newUsername;
                            cin >> newUsername;
                            while (!(validateCredentials(sysUsername, newUsername)))
                            {
                                cout << "You Entered Old Username." << endl;
                                cout << "New Username: ";
                                cin >> newUsername;
                            }

                            sysUsername = newUsername;
                        }
                        else if (response == '2')
                        {
                            cout << "Enter New Password: ";
                            string newPassword;
                            cin >> newPassword;

                            bool flag = false;
                            while (!(flag))
                            {
                                while (!(validatePassword(newPassword)))
                                {
                                    cout << "Weak Password. Use Integers, Special Characters, Upper and lower case letters." << endl;
                                    cout << "New Password: ";
                                    cin >> newPassword;
                                }
                                while (!validateCredentials(sysPass, newPassword))
                                {
                                    cout << "You Entered Old Password." << endl;
                                    cout << "New Password: ";
                                    cin >> newPassword;
                                }
                                if (validatePassword(newPassword))
                                {
                                    flag = true;
                                }
                            }
                            sysPass = newPassword;
                        }
                        else if (response == '3')
                        {
                            cout << "Enter New Usename: ";
                            string newUsername;
                            cin >> newUsername;
                            while (!(validateCredentials(sysUsername, newUsername)))
                            {
                                cout << "You Entered Old Username." << endl;
                                cout << "New Username: ";
                                cin >> newUsername;
                            }
                            sysUsername = newUsername;
                            cout << "Enter New Password: ";
                            string newPassword;
                            cin >> newPassword;
                            bool flag = false;
                            while (!(flag))
                            {
                                while (!(validatePassword(newPassword)))
                                {
                                    cout << "Weak Password. Use Integers, Special Characters, Upper and lower case letters." << endl;
                                    cout << "New Password: ";
                                    cin >> newPassword;
                                }
                                while (!validateCredentials(sysPass, newPassword))
                                {
                                    cout << "You Entered Old Password." << endl;
                                    cout << "New Password: ";
                                    cin >> newPassword;
                                }
                                if (validatePassword(newPassword))
                                {
                                    flag = true;
                                }
                            }
                            sysPass = newPassword;
                        }
                        clearScreen();
                        managerMenuOp = managerMenu();
                        system("cls");
                    }
                }
            }
            else
            {
                cout << "Wrong username or password." << endl;
                clearScreen();
            }
        }
        else if (userTypeOp == 'C')
        {
            char cusTypeOp = cusType();
            system("cls");
            while (cusTypeOp != '0')
            {
                if (cusTypeOp == 'R')
                {
                    if (users > 0)
                    {
                        string cusUsername, cusPassword;
                        bool flag = false;
                        cout << "Enter Username: ";
                        cin >> cusUsername;
                        cout << "Enter Password: ";
                        cin >> cusPassword;
                        for (int i = 0; i < users; i++)
                        {
                            if (verification(username[i], password[i], cusUsername, cusPassword))
                            {
                                loginCustomer = i;
                                flag = true;
                            }
                            if (flag)
                            {
                                system("cls");
                                int rCusMenuOp = rCusMenu();
                                while (rCusMenuOp < 7)
                                {
                                    if (rCusMenuOp == 1)
                                    {
                                        system("cls");
                                        updateUsage();
                                        clearScreen();
                                        rCusMenuOp = rCusMenu();
                                    }
                                    if (rCusMenuOp == 2)
                                    {
                                        system("cls");
                                        checkPayable();
                                        clearScreen();
                                        rCusMenuOp = rCusMenu();
                                    }
                                    if (rCusMenuOp == 3)
                                    {
                                        system("cls");
                                        pkgUpgrade();
                                        clearScreen();
                                        rCusMenuOp = rCusMenu();
                                    }
                                    if (rCusMenuOp == 4)
                                    {
                                        system("cls");
                                        cancelRegistration(loginCustomer);
                                        cout << "Registration cancelled Successfully." << endl;
                                        break;
                                    }
                                    if (rCusMenuOp == 5)
                                    {
                                        system("cls");
                                        cusFeedback();
                                        clearScreen();
                                        rCusMenuOp = rCusMenu();
                                    }
                                    if (rCusMenuOp == 6)
                                    {
                                        system("cls");
                                        cout << "Change:\n1-Username\n2-Password\n3-Both " << endl;
                                        char response;
                                        cin >> response;
                                        system("cls");
                                        if (response == '1')
                                        {
                                            cout << "Enter New Usename: ";
                                            string newUsername;
                                            cin >> newUsername;
                                            while (!(validateCredentials(username[loginCustomer], newUsername)))
                                            {
                                                cout << "You Entered Old Username." << endl;
                                                cout << "New Username: ";
                                                cin >> newUsername;
                                            }
                                            username[loginCustomer] = newUsername;
                                        }
                                        else if (response == '2')
                                        {
                                            cout << "Enter New Password: ";
                                            string newPassword;
                                            cin >> newPassword;
                                            bool flag = false;
                                            while (!(flag))
                                            {
                                                while (!(validatePassword(newPassword)))
                                                {
                                                    cout << "Weak Password. Use Integers, Special Characters, Upper and lower case letters." << endl;
                                                    cout << "New Password: ";
                                                    cin >> newPassword;
                                                }
                                                while (!validateCredentials(password[loginCustomer], newPassword))
                                                {
                                                    cout << "You Entered Old Password." << endl;
                                                    cout << "New Password: ";
                                                    cin >> newPassword;
                                                }
                                                if (validatePassword(newPassword))
                                                {
                                                    flag = true;
                                                }
                                            }
                                            password[loginCustomer] = newPassword;
                                        }
                                        else if (response == '3')
                                        {
                                            cout << "Enter New Usename: ";
                                            string newUsername;
                                            cin >> newUsername;
                                            while (!(validateCredentials(username[loginCustomer], newUsername)))
                                            {
                                                cout << "You Entered Old Username." << endl;
                                                cout << "New Username: ";
                                                cin >> newUsername;
                                            }
                                            username[loginCustomer] = newUsername;

                                            cout << "Enter New Password: ";
                                            string newPassword;
                                            cin >> newPassword;
                                            bool flag = false;
                                            while (!(flag))
                                            {
                                                while (!(validatePassword(newPassword)))
                                                {
                                                    cout << "Weak Password. Use Integers, Special Characters, Upper and lower case letters." << endl;
                                                    cout << "New Password: ";
                                                    cin >> newPassword;
                                                }
                                                while (!validateCredentials(password[loginCustomer], newPassword))
                                                {
                                                    cout << "You Entered Old Password." << endl;
                                                    cout << "New Password: ";
                                                    cin >> newPassword;
                                                }
                                                if (validatePassword(newPassword))
                                                {
                                                    flag = true;
                                                }
                                            }
                                            password[loginCustomer] = newPassword;
                                        }
                                        clearScreen();
                                        rCusMenuOp = rCusMenu();
                                    }
                                }
                            }
                            else
                            {
                                cout << "Wrong Username or Password." << endl;
                            }
                        }
                    }
                    else
                    {
                        cout << "No registered Customers yet..." << endl;
                    }
                    clearScreen();
                    cusTypeOp = cusType();
                    system("cls");
                }
                if (cusTypeOp == 'N')
                {
                    int nCusMenuOp = nCusMenu();
                    while (nCusMenuOp < 5)
                    {
                        if (nCusMenuOp == 1)
                        {
                            system("cls");
                            packageView();
                            clearScreen();
                            nCusMenuOp = nCusMenu();
                        }
                        if (nCusMenuOp == 2)
                        {
                            system("cls");
                            viewServices();
                            clearScreen();
                            nCusMenuOp = nCusMenu();
                        }
                        if (nCusMenuOp == 3)
                        {
                            system("cls");
                            viewPaymentMethod();
                            clearScreen();
                            nCusMenuOp = nCusMenu();
                        }
                        if (nCusMenuOp == 4)
                        {
                            system("cls");
                            if (pending < 5)
                            {
                                string nName, nUsername, nPassword, nEmail, nPkgType;
                                cout << "Enter Full Name: ";
                                cin.ignore();
                                getline(cin, nName);
                                cout << "New Username: ";
                                cin >> nUsername;
                                while (!(validateUsername(nUsername)))
                                {
                                    cout << "Username Exists. Recommended usernames: " << endl;
                                    recommendUsername(nUsername);
                                    for (int i = 0; i < 3; i++)
                                    {
                                        cout << recUsername[i] << ", ";
                                    }

                                    cin >> nUsername;
                                }
                                cout << "New Password: ";
                                cin >> nPassword;
                                while (!(validatePassword(nPassword)))
                                {
                                    cout << "Weak Password. Use Integers, Special Characters, Upper and lower case letters." << endl;
                                    cout << "New Password: ";
                                    cin >> nPassword;
                                }
                                cout << "Enter Email: ";
                                cin >> nEmail;
                                while (!validateEmail(nEmail))
                                {
                                    cout << "Incorrect Email." << endl;
                                    cout << "Enter Email: ";
                                    cin >> nEmail;
                                }
                                cout << "Package Type (Economy/Premium) : ";
                                cin >> nPkgType;
                                while (!(nPkgType == "Economy" || nPkgType == "Premium"))
                                {
                                    cout << "Wrong Package Type. Enter Again." << endl;
                                    cout << "Package Type (Economy/Premium) : ";
                                    cin >> nPkgType;
                                }
                                nRegistration(nName, nUsername, nPassword, nEmail, nPkgType);
                                system("cls");
                                cout << "Request Send to Admin." << endl;
                                clearScreen();
                                nCusMenuOp = nCusMenu();
                            }
                            else
                            {
                                cout << "Already too many pending registration requests. Try again later" << endl;
                                clearScreen();
                                nCusMenuOp = nCusMenu();
                            }
                        }
                    }
                    system("cls");
                    cusTypeOp = cusType();
                    system("cls");
                }
            }
        }
        system("cls");
        userTypeOp = userType();
        system("cls");
    }
    store();
    cout << "Program Terminated" << endl;
}
