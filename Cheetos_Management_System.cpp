#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>

using namespace std;

// You have to sign in with this for the first time:

// username: adminOriginal001
// password: OAdminO10!

// Only the last four features, namely: Adding users, deleting users, retrieving users, updating users, work yet. Other features will be added soon.

/* the arrays for usernames, passwords and roles must be global so that all functions can access them*/
/* The length of the array has been hardcored according to the capacity of the factory to house employees and admins */
const int maximumOccupancy = 50;
string usernames[maximumOccupancy];
string passwords[maximumOccupancy];
string roles[maximumOccupancy];

/* Although the length of the username, password and roles arrays have been set according to the factory's capacity, we must only check
that portion of the array that is being used. Initially there's only one user in the system i.e the original admin. So, we must access
only the first element of the arrays by setting countUsers = 1.

As the admin adds more users in the system, the countUsers variable will keep incrementing*/

int countUsers = 1;

/* To get the role of a user as an admin or an employee once his credentials have been verified after signing in*/
string getRole(string username);

/* To validate whether the user who has signed in actually exists in the system or not*/
bool signInInterface(string username, string password);

/*To show all the options that users get once signed in*/
void adminInterface();
void employeeInterface();

/*To see the choice that the admin has accessed*/
string adminChoice();
string employeeChoice();

/* function choosers based on the option that the user chose in the above functions */
bool adminFunctionChoosers(string option, string usernameOfUser);
bool employeeFunctionChoosers(string option);

/* display invalid user prompt */
void invalidUserPrompt();

/* The header of the system*/
void header();
void subHeader(string nameMenu);

/* admin option functions */
/* a function to count the number of admins in the system. This number must always be greater than 0*/

int adminCount();

/* A function to return a user's index by using his username */
int userIndex(string username);

/* adding users */
/* user adding menu */
bool addUserInterface(string usernameOfUser);
/* To check whether a user already exists in the system */
bool userAuthenticate(string name);
/* To add an authenticated user */
void addUser(string username, string password, string role);

/*retrieving users */
void viewUsersInfo();
void viewSpecificUser(int index);

/* Updating user info */

void updateUserInterface(string username);

void updateUserInfo(string username);

/* deleting users */
bool deleteUserInterface(string username);
void deleteUser(string username);


// users in file
void addUsersToFile(); // to add users in file.
void loadUsersFromFile();
//-------------------------------------------------------------------------------------------------------------------------------------
// Manufacturing orders
// Adding orders

const int maximumOrders = 50;
int manufacturingOrdersCount = 0;

string manufacturingOrderFlavors[maximumOrders];      // flavors of the ordered cheetos will be stored here
int manufacturingOrderIndividualPrice[maximumOrders]; // price of each order will be stored in parallel here
int manufacturingOrderQuantity[maximumOrders];        // quantity of each order will be stored in parallel here

void addManufacturingOrder();                    // function to add order to the arrays
bool orderPriceVerification(string price);       // function to validate order price before converting them to int and storing in array
bool orderQuantityVerification(string quantity); // function to validate order quantity before converting them to int and storing in array

// view manufacturing orders

void viewManufacturingOrders();

// update manufacturing orders

void updateManufacturingOrders();

// delete manufacturing orders
void deleteManufacturingOrderInterface();  // interface
void deleteManufacturingOrders(int index); // deletor
//..........................................................................................................................................................
// ingredients

const int maximumIngredients = 50;
int ingredientsOrdersCount = 0;

string ingredientsOrdered[maximumIngredients];
int quantitiesOfIngredientsOrdered[maximumIngredients];

// add ingredients

void addIngredients();
// view ingredients ordered

void viewIngredientsOrdered();

// update ingredients ordered

void updateIngredientsOrdered();

// delete ingredients ordered

void deleteIngredientsOrdered();

//-------------------------------------------------------------------------------------------------------------------------------------
// ingredients in table

const int maximumRecipeIngredients = 50;
int numberOfTableIngredients = 0;
string recipeIngredients[maximumRecipeIngredients];
// add ingredients to the table

void addIngredientsToTheTable();

// view ingredients in table

void viewIngredientsInTheTable();

// helpful side functions
bool stringNumberValidate(string number);
string parse(string line, int field);

main()
{
    /* The original user of the system aka the first admin must be hardcored into the system*/
    usernames[0] = "adminOriginal001";
    passwords[0] = "OAdminO10!";
    roles[0] = "admin";

    while (true)
    {
        string username, password, role;
        string exitAnswer = "N";
        bool result = false;       // result will check if the signed in credentials are valid or not
        bool flagAdmin = false;    // flagAdmin will allow us to quickly jump from choosing an admin option to the login page
        bool flagEmployee = false; // similar to flagAdmin but for employees
        system("cls");
        header();
        subHeader("Sign In");
        cout << "Enter username: (Enter 0 to exit the program)";
        cin >> username;

        if (username == "0")
        {
            cout << "Are you sure you want to leave? (Y/N)";
            cin >> exitAnswer;
            if (exitAnswer == "Y" || exitAnswer == "y")
            {
                system("cls");
                cout << "Thank you for your time" << endl;
                break;
            }
            else
            {
                continue;
            }
        }

        cout << "Enter password: ";
        cin >> password;
        /* result is to check whether the signed in credentials are valid or not*/
        result = signInInterface(username, password);

        if (result)
        {
            /* if the user is valid, we obtain his role as an admin or employee and display the appropriate screens accordingly*/
            role = getRole(username);
            if (role == "admin")
            {
                while (true)
                {
                    system("cls");
                    header();
                    subHeader("Admin main");
                    adminInterface();              // show all available features for admin
                    string option = adminChoice(); // show admin's chosen option

                    /* after getting the option chosen by the admin, the proper function will be called*/
                    if (!adminFunctionChoosers(option, username))
                    {
                        flagAdmin = true;
                        break;
                    }
                }
                if (flagAdmin)
                {
                    continue;
                }
            }
            else if (role == "employee")
            {
                while (true)
                {
                    system("cls");
                    header();
                    subHeader("Employee Main");
                    employeeInterface();                      // show employee's available options
                    string employeeOption = employeeChoice(); // show employee's chosen option
                    /* After getting the option chosen by the employee, the proper function will be displayed */

                    if (!employeeFunctionChoosers(employeeOption))
                    {
                        flagEmployee = true;
                        break;
                    }
                }
                if (flagEmployee)
                {
                    continue;
                }
            }
            /*If the role is invalid, we tell user to try again*/

            else
            {
                invalidUserPrompt();
                continue;
            }
        }
        /*If the user is invalid, we tell him/her to try again*/

        else
        {
            invalidUserPrompt();
            continue;
        }
    }
}

bool signInInterface(string username, string password)
{
    bool flag = false;

    /* As soon as the user is found in the system, we turn our flag true*/

    for (int i = 0; i < countUsers; i++)
    {
        if (username == usernames[i] && password == passwords[i])
        {
            flag = true;
        }
    }

    return flag;
}

string getRole(string username)
{
    /*using the index of his username, we access his role in another parallel array*/
    for (int i = 0; i < countUsers; i++)
    {
        if (username == usernames[i])
        {
            return roles[i];
        }
    }
    /*if no role is found, we return invalid*/

    return "invalid";
}

void invalidUserPrompt()
{
    char c;
    cout << "Invalid user" << endl;
    cout << endl;
    cout << "Enter any key to try again" << endl;
    getch();
}

void adminInterface()
{
    /*The menu that the admin will see upon signing in*/
    cout << "1  Create ingredients order: " << endl;
    cout << "2  Create manufacturing order: " << endl;
    cout << "3  View ingredients order: " << endl;
    cout << "4  View manufacturing order: " << endl;
    cout << "5  Update an ingredients order: " << endl;
    cout << "6  Update a manufacturing order: " << endl;
    cout << "7  Delete an ingredients order: " << endl;
    cout << "8  Delete a manufacturing order: " << endl;
    cout << "9  View recommended ingredients: " << endl;
    cout << "10 View excess ingredients in factory stock:" << endl;
    cout << "11 View ingredients table:" << endl;
    cout << "12 Add ingredients to the table:" << endl;
    cout << "13 View profit/loss:" << endl;
    cout << "14 message employee/employees:" << endl;
    cout << "15 Add user: " << endl;
    cout << "16 Update user info" << endl;
    cout << "17 View user info" << endl;
    cout << "18 Delete user info" << endl;
    cout << "19 Delete ingredient from the table" << endl;
    cout << endl;
    cout << "Enter 0 to exit to login screen" << endl;
}

void employeeInterface()
{
    /*The menu that the emplyee will see upon signing in*/
    cout << "1  Upload a new request" << endl;
    cout << "2  View requests: " << endl;
    cout << "3  Edit requests " << endl;
    cout << "4  Delete requests: " << endl;
    cout << "5  View current orders: " << endl;
    cout << "6  View ingredients received: " << endl;
    cout << "7  Log shortage/excess of ingredients " << endl;
    cout << "8  Give a suggestion " << endl;
    cout << "9  View your suggestions " << endl;
    cout << "10 request section leader for delay in deadline " << endl;
    cout << "11 request section leader for editing recipes " << endl;
    cout << endl;

    cout << "Enter 0 to exit to login screen" << endl;
}

string adminChoice()
{
    string choice;
    char c;
    while (true)
    {
        /*the admin will enter his choice till he gets it right. Otherwise the system will keep asking for option*/

        cout << "Enter choice: ";
        cin >> choice;
        if (!(choice == "0" || choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7" || choice == "8" || choice == "9" || choice == "10" || choice == "11" || choice == "12" || choice == "13" || choice == "14" || choice == "15" || choice == "16" || choice == "17" || choice == "18" || choice == "19"))
        {
            cout << "That is not an available option." << endl;
            cout << "Press any key to continue: " << endl;
            getch();
            continue;
        }
        return choice;
    }
}

string employeeChoice()
{
    string choice;
    char c;
    while (true)
    {
        /*the employee will enter his choice till he gets it right. Otherwise the system will keep asking for option*/

        cout << "Enter choice: ";
        cin >> choice;
        if (!(choice == "0" || choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7" || choice == "8" || choice == "9" || choice == "10" || choice == "11"))
        {
            cout << "That is not an available option." << endl;
            cout << "Press any key to continue: " << endl;
            getch();
            continue;
        }
        return choice;
    }
}

bool adminFunctionChoosers(string option, string usernameOfUser) /* the function chooser is bool because after choosing and excuting,
the control might return to the option */
{
    char c;

    if (option == "0")
    {
        return false;
    }

    else if (option == "1")
    {
        addIngredients();
    }
    else if (option == "2")
    {
        addManufacturingOrder();
    }
    else if (option == "3")
    {
        viewIngredientsOrdered();
    }
    else if (option == "4")
    {
        viewManufacturingOrders();
    }
    else if (option == "5")
    {
        updateIngredientsOrdered();
    }
    else if (option == "6")
    {
        updateManufacturingOrders();
    }
    else if (option == "7")
    {
        deleteIngredientsOrdered();
    }
    else if (option == "8")
    {
        deleteManufacturingOrderInterface();
    }
    else if (option == "9")
    {
        cout << "Coming soon" << endl;
        cout << "Enter any key to continue: " << endl;
        getch();
    }
    else if (option == "10")
    {
        cout << "Coming soon" << endl;
        cout << "Enter any key to continue: " << endl;
        getch();
    }
    else if (option == "11")
    {
        viewIngredientsInTheTable();
    }
    else if (option == "12")
    {
        addIngredientsToTheTable();
    }
    else if (option == "13")
    {
        cout << "Coming soon" << endl;
        cout << "Enter any key to continue: " << endl;
        getch();
    }
    else if (option == "14")
    {
        cout << "Coming soon" << endl;
        cout << "Enter any key to continue: " << endl;
        getch();
    }
    else if (option == "15")
    {
        if (addUserInterface(usernameOfUser))
        {
            cout << "User added successfully" << endl;
            cout << "Press any key to continue" << endl;
            getch();
        }
        else
        {
            system("cls");
            header();
            subHeader("User Adding");
            cout << "Maximum occupancy reached" << endl;
            cout << "Press any key to continue" << endl;
            getch();
        }
    }
    else if (option == "16")
    {
        updateUserInterface(usernameOfUser);
    }
    else if (option == "17")
    {
        viewUsersInfo();
    }
    else if (option == "18")
    {
        if (deleteUserInterface(usernameOfUser))
        {
            cout << "User deleted successfully" << endl;
            cout << "Press any key to continue" << endl;
            getch();
        }
        else
        {
            return false;
        }
    }
    else if (option == "19")
    {
        deleteIngredientsFromTheTable();
    }

    return true;
}
bool employeeFunctionChoosers(string employeeOption)
{
    char c;
    bool flag = true;
    if (employeeOption == "0")
    {
        flag = false;
    }

    else if (employeeOption == "1")
    {
        cout << "Coming soon" << endl;
        cout << "Enter any key to continue: " << endl;
        getch();
    }
    else if (employeeOption == "2")
    {
        cout << "Coming soon" << endl;
        cout << "Enter any key to continue: " << endl;
        getch();
    }
    else if (employeeOption == "3")
    {
        cout << "Coming soon" << endl;
        cout << "Enter any key to continue: " << endl;
        getch();
    }
    else if (employeeOption == "4")
    {
        cout << "Coming soon" << endl;
        cout << "Enter any key to continue: " << endl;
        getch();
    }
    else if (employeeOption == "5")
    {
        cout << "Coming soon" << endl;
        cout << "Enter any key to continue: " << endl;
        getch();
    }
    else if (employeeOption == "6")
    {
        cout << "Coming soon" << endl;
        cout << "Enter any key to continue: " << endl;
        getch();
    }
    else if (employeeOption == "7")
    {
        cout << "Coming soon" << endl;
        cout << "Enter any key to continue: " << endl;
        getch();
    }
    else if (employeeOption == "8")
    {
        cout << "Coming soon" << endl;
        cout << "Enter any key to continue: " << endl;
        getch();
    }
    else if (employeeOption == "9")
    {
        cout << "Coming soon" << endl;
        cout << "Enter any key to continue: " << endl;
        getch();
    }
    else if (employeeOption == "10")
    {
        cout << "Coming soon" << endl;
        cout << "Enter any key to continue: " << endl;
        getch();
    }
    else if (employeeOption == "11")
    {
        cout << "Coming soon" << endl;
        cout << "Enter any key to continue: " << endl;
        getch();
    }

    return flag;
}
// Adding users to the system
bool addUserInterface(string usernameOfUser)
{
    bool flag = true;
    char c;
    bool roleFlag = true;
    bool usernameFlag = true;
    bool passwordFlag = true;

    string role, username, password;
    while (true)
    {
        if (countUsers >= maximumOccupancy)
        {
            flag = false;
            break;
        }
        if (flag)
        {
            system("cls");
            header();
            subHeader("User Adding");
            if (roleFlag)
            {
                cout << "Enter type of user (employee, admin): ";
                cin >> role;
            }

            if (usernameFlag)
            {
                cout << "Enter username: ";
                cin >> username;
            }

            if (passwordFlag)
            {
                cout << "Enter password: ";
                cin >> password;
            }
            if (!(role == "admin" || role == "employee"))
            {
                cout << "Invalid role" << endl;
                cout << "Try again" << endl;
            }
            else
            {
                roleFlag = false;
            }

            if (username.length() < 5)
            {
                cout << "Username must have more than 5 letters." << endl;
                cout << "Try again" << endl;
            }
            else if (!(userAuthenticate(username))) // to check whether the username is unique or not
            {
                cout << "Username already exists. Try again" << endl;
            }
            else
            {
                usernameFlag = false;
            }

            if (password.length() < 5)
            {
                cout << "password must have more than 5 letters." << endl;
                cout << "Try again" << endl;
            }
            else
            {
                passwordFlag = false;
            }

            if (roleFlag || passwordFlag || usernameFlag)
            {
                cout << "Enter any key to continue" << endl;
                getch();
            }
            else
            {
                addUsersToFile();
                break; // if all validations are passed, we break the loop and call the function to add the user in our array
            }
        }
    }

    if (flag)
    {
        addUser(username, password, role);
    }
    return flag;
}
bool userAuthenticate(string username)
{
    bool flag = true;
    for (int i = 0; i < countUsers; i++)
    {
        if (usernames[i] == username)
        {
            flag = false;
            break;
        }
    }
    return flag;
}
void addUser(string username, string password, string role)
{
    usernames[countUsers] = username;
    passwords[countUsers] = password;
    roles[countUsers] = role;
    countUsers++; // increment the global variable that shows how many users have been added into the system.
}

// retrieving users from the system

void viewUsersInfo()
{
    string option;
    char c;

    while (true)
    {
        bool flag = false;
        system("cls");
        header();
        subHeader("Users Info");
        cout << "Sr. no"
             << "\t"
             << "\t"
             << "username" << endl;
        for (int i = 0; i < countUsers; i++)
        {
            cout << i + 1 << "\t"
                 << "\t" << usernames[i] << endl;
        }

        cout << "Select user to view all details: (Enter 0 to go back)";
        cin >> option;

        for (int i = 0; i < option.length(); i++)
        {
            if (!(option[i] >= 48 && option[i] <= 57))
            {
                cout << "Option must only contain numbers" << endl;
                cout << "Enter any key to continue" << endl;
                getch();
                flag = true;
                break;
            }
        }
        if (flag)
        {
            continue;
        }
        int option2 = stoi(option);

        if (option2 > 0 && option2 <= countUsers)
        {
            option2--;
            viewSpecificUser(option2);
        }
        else if (option2 == 0)
        {
            break;
        }
        else
        {
            cout << "You entered the wrong option. Try again" << endl;
            getch();
            continue;
        }
    }
}

void viewSpecificUser(int option)
{
    char c;
    system("cls");
    header();
    subHeader("User Info");
    cout << "Username: " << usernames[option] << endl;
    if (roles[option] != "admin")
    {
        cout << "Password: " << passwords[option] << endl;
    }
    cout << "Role: " << roles[option] << endl;

    cout << "Press any key to go back" << endl;
    getch();
}

// update user info
void updateUserInterface(string username)
{
    char c;
    string usernameToUpdate, roleToUpdate;
    while (true)
    {
        system("cls");
        header();
        subHeader("Update User");
        cout << "Enter the username you want to update: (Enter 0 to go back)";
        cin >> usernameToUpdate;

        if (usernameToUpdate == "0")
        {
            break;
        }

        for (int i = 0; i < countUsers; i++)
        {
            if (usernameToUpdate == usernames[i])
            {
                roleToUpdate = roles[i];
                break;
            }
        }

        if (roleToUpdate == "employee" || usernameToUpdate == username)
        {
            updateUserInfo(usernameToUpdate);
        }

        else if (roleToUpdate == "admin")
        {
            cout << "You cannot update an admin account without signing into it" << endl;
            cout << "press any key to continue" << endl;
            getch();
            continue;
        }
        else
        {
            cout << "Username does not exist" << endl;
            cout << "press any key to continue" << endl;
            getch();
            continue;
        }
    }
}
void updateUserInfo(string username)
{
    char c;
    string newUsername, newPassword, oldPassword, newRole;
    while (true)
    {
        system("cls");
        header();
        subHeader("Update User");
        cout << "Enter new username: ";
        cin >> newUsername;

        cout << "Enter new password: ";
        cin >> newPassword;

        cout << "Enter new role: ";
        cin >> newRole;
        if (newUsername != username)
        {
            if (!(userAuthenticate(newUsername)))
            {
                cout << "Username already exists. Try again" << endl;
                getch();
                continue;
            }
        }
        if (newRole == "employee")
        {
            if (adminCount() == 1 && getRole(username) == "admin")
            {
                cout << "You cannot change your role to employee because there will be no more admins left" << endl;
                cout << "press any key to continue" << endl;
                getch();
                newRole = "admin";
            }
        }
        for (int i = 0; i < countUsers; i++)
        {
            if (username == usernames[i])
            {
                usernames[i] = newUsername;
                passwords[i] = newPassword;
                roles[i] = newRole;
                addUsersToFile();
                break;
            }
        }
        break;
    }
}

// delete user

bool deleteUserInterface(string username)
{
    string usernameToBeDeleted;
    char c;
    bool flag = true;
    while (true)
    {
        system("cls");
        header();
        subHeader("User Deleting");

        cout << "Enter username: (Press 0 to go back)";
        cin >> usernameToBeDeleted;

        if (usernameToBeDeleted == "0")
        {
            break;
        }

        if (!(userAuthenticate(usernameToBeDeleted)))
        {
            if (roles[userIndex(usernameToBeDeleted)] == "admin")
            {
                if (usernameToBeDeleted != username)
                {

                    cout << "You cannot delete an admin without signin into his account" << endl;
                    cout << "Press any key to try again" << endl;
                    getch();
                    continue;
                }
                else
                {
                    if (adminCount() == 1)
                    {
                        cout << "You cannot delete this account or there will be no more users left" << endl;
                        cout << "Press any key to continue" << endl;
                        getch();
                        continue;
                    }
                    else
                    {
                        flag = false;
                    }
                }
            }
            deleteUser(usernameToBeDeleted);
            cout << "Press any key to continue" << endl;
            getch();
        }
        else
        {
            cout << "Username does not exist. Please try again" << endl;
            cout << "Press any key to continue" << endl;
            getch();
            continue;
        }
    }
    return flag;
}

void deleteUser(string username)
{
    int index = userIndex(username);
    for (int i = index; i < countUsers - 1; i++)
    {
        usernames[i] = usernames[i + 1];
        passwords[i] = passwords[i + 1];
        roles[i] = roles[i + 1];
    }
    usernames[countUsers - 1] = "temporary123";
    passwords[countUsers - 1] = "temporary123";
    roles[countUsers - 1] = "temporary123";
    countUsers--;
}
int adminCount()
{
    int count = 0;
    for (int i = 0; i < countUsers; i++)
    {
        if (roles[i] == "admin")
        {
            count++;
        }
    }
    return count;
}

int userIndex(string username)
{
    for (int i = 0; i < countUsers; i++)
    {
        if (usernames[i] == username)
        {
            return i;
        }
    }

    return -1;
}

// adding users to the file
void addUsersToFile()
{
    fstream fileUser;
    fileUser.open("users.txt", ios::out);

    for (int i = 0; i < countUsers; i++)
    {
        fileUser << usernames[i] << "," << passwords[i] << "," << roles[i] << endl;
    }
    fileUser.close();
}
// loading users from sile
void loadUsersFromFile()
{
    string line;
    fstream fileUser;
    fileUser.open("users.txt", ios::in);

    while(!fileUser.eof())
    {
        getline(fileUser, line);
        usernames[countUsers] = parse(line, 1);
        passwords[countUsers] = parse(line, 2);
        roles[countUsers] = parse(line, 3);
        countUsers++;
    }
    fileUser.close();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------
// manufacturing orders
// adding

void addManufacturingOrder()
{
    string choice, numberOfOrders, temporaryQuantity, temporaryPrice;
    while (true)
    {
        system("cls");
        header();
        subHeader("Manufacturing orders");
        cout << "Enter the number of orders that you wish to enter: (Enter 0 to go back)" << endl;
        cout << "You can enter " << maximumOrders - manufacturingOrdersCount << " orders";
        cin >> numberOfOrders;
        if (numberOfOrders == "0")
        {
            break;
        }
        if (!stringNumberValidate(numberOfOrders))
        {
            cout << "Enter a correct number!" << endl;
            cout << "Press any key to continue" << endl;
            getch();
            continue;
        }
        if (stoi(numberOfOrders) + manufacturingOrdersCount > 50)
        {
            cout << "You cannot add so many orders. " << endl;
            cout << "Enter under " << maximumOrders - manufacturingOrdersCount << " orders" << endl;
            cout << "Press any key to continue" << endl;
            getch();
            continue;
        }
        for (int i = 0; i < stoi(numberOfOrders); i++)
        {
            cout << "Enter Flavor: ";
            cin >> manufacturingOrderFlavors[manufacturingOrdersCount];

            cout << "Enter quantity: ";
            cin >> temporaryQuantity;

            if (orderQuantityVerification(temporaryQuantity) && stringNumberValidate(temporaryQuantity))
            {
                manufacturingOrderQuantity[manufacturingOrdersCount] = stoi(temporaryQuantity);
            }
            else
            {
                cout << "Not a valid quantity. Press any key to try again" << endl;
                getch();
                i--;
                continue;
            }

            cout << "Enter price: ";
            cin >> temporaryPrice;

            if (orderPriceVerification(temporaryPrice) && stringNumberValidate(temporaryPrice))
            {
                manufacturingOrderIndividualPrice[manufacturingOrdersCount] = stoi(temporaryPrice);
            }
            else
            {
                cout << "Not a valid price. Press any key to try again" << endl;
                getch();
                i--;
                continue;
            }
            manufacturingOrdersCount++;
        }
    }
}
bool orderPriceVerification(string price)
{
    return true;
}
bool orderQuantityVerification(string quantity)
{
    return true;
}

// view manufacturing orders
void viewManufacturingOrders()
{
    system("cls");
    cout << "Serial number:"
         << "\t"
         << "Flavor:"
         << "\t\t"
         << "Quantity"
         << "\t\t"
         << "Price" << endl
         << endl;
    for (int i = 0; i < manufacturingOrdersCount; i++)
    {
        cout << i + 1 << "\t\t\t" << manufacturingOrderFlavors[i] << "\t\t\t" << manufacturingOrderQuantity[i] << "\t\t\t" << manufacturingOrderIndividualPrice[i] << endl;
    }
    cout << endl;
    cout << "Press any key to continue:" << endl;
    getch();
}

// update manufaturing orders
void updateManufacturingOrders()
{
    string serialNumberToUpdate, temporaryQuantity, temporaryPrice;
    bool flavorFlag = true;
    bool quantityFlag = true;
    bool priceFlag = true;
    bool serialNumberFlag = true;
    while (true)
    {
        system("cls");
        header();
        subHeader("Update Order");
        if (serialNumberFlag)
        {
            cout << "Enter serial number of the order you want to update: ";
            cout << "Enter 0 to go back";
            cin >> serialNumberToUpdate;
        }
        if (serialNumberToUpdate == "0")
        {
            break;
        }
        if (stringNumberValidate(serialNumberToUpdate))
        {
            if (stoi(serialNumberToUpdate) > 0 && stoi(serialNumberToUpdate) <= manufacturingOrdersCount)
            {
                serialNumberFlag = false;
                if (flavorFlag)
                {
                    cout << "Enter new flavor: ";
                    cin >> manufacturingOrderFlavors[stoi(serialNumberToUpdate) - 1];
                }
                if (quantityFlag)
                {
                    cout << "Enter new quantity: ";
                    cin >> temporaryQuantity;
                }
                if (priceFlag)
                {
                    cout << "Enter new price: ";
                    cin >> temporaryPrice;
                }
                if (stringNumberValidate(temporaryQuantity) && orderQuantityVerification(temporaryQuantity))
                {
                    manufacturingOrderQuantity[stoi(serialNumberToUpdate) - 1] = stoi(temporaryQuantity);
                    quantityFlag = false;
                }
                if (stringNumberValidate(temporaryPrice) && orderPriceVerification(temporaryPrice))
                {
                    manufacturingOrderIndividualPrice[stoi(serialNumberToUpdate) - 1] = stoi(temporaryPrice);
                    priceFlag = false;
                }
                flavorFlag = false; // future validations for flavor will be called here
                if (serialNumberFlag || flavorFlag || priceFlag || quantityFlag)
                {
                    system("cls");
                    cout << "Enter correct information. Press any key to continue" << endl;
                    getch();
                    continue;
                }
                else
                {
                    break;
                }
            }
            else
            {
                system("cls");
                cout << "Enter correct information. Press any key to continue" << endl;
                getch();
                continue;
            }
        }
        else
        {
            system("cls");
            cout << "Enter correct information. Press any key to continue" << endl;
            getch();
            continue;
        }
    }
}

// delete manufacturing orders
// interface with validations
void deleteManufacturingOrderInterface()
{
    string serialNumberToDelete;
    while (true)
    {
        system("cls");
        header();
        subHeader("Delete Manufacturing orders");
        cout << "Enter serial number of order you want to delete. (Press 0 to exit)" << endl;
        cin >> serialNumberToDelete;

        if (serialNumberToDelete == "0")
        {
            break;
        }

        if (stringNumberValidate(serialNumberToDelete))
        {
            if (stoi(serialNumberToDelete) > 0 && stoi(serialNumberToDelete) < manufacturingOrdersCount)
            {
                deleteManufacturingOrders(stoi(serialNumberToDelete) - 1);
            }
            else
            {
                cout << "Enter valid number. Press any key to continue" << endl;
                getch();
            }
        }
        else
        {
            cout << "Enter valid number. Press any key to continue" << endl;
            getch();
        }
    }
}
// deletor
void deleteManufacturingOrders(int index)
{
    for (int i = index; i < manufacturingOrdersCount - 1; i++)
    {
        manufacturingOrderFlavors[i] = manufacturingOrderFlavors[i + 1];
        manufacturingOrderIndividualPrice[i] = manufacturingOrderIndividualPrice[i + 1];
        manufacturingOrderQuantity[i] = manufacturingOrderQuantity[i + 1];
    }
    manufacturingOrdersCount--;
}

// ingredients

// add ingredients

void addIngredients()
{
    string ingredientTobeOrdered, quantityOfIngredient;
    while (true)
    {
        system("cls");
        header();
        subHeader("Adding ingredients");
        cout << "Enter the name of the ingredient that you want to order: (Press 0 to go back)";
        cin >> ingredientTobeOrdered;

        if (ingredientTobeOrdered == "0")
        {
            break;
        }

        // ingredients' validatons will be called here in the future

        ingredientsOrdered[ingredientsOrdersCount] = ingredientTobeOrdered;

        cout << "Enter quantity of the ingredient to be ordered: ";
        cin >> quantityOfIngredient;

        if (stringNumberValidate(quantityOfIngredient))
        {
            quantitiesOfIngredientsOrdered[ingredientsOrdersCount] = stoi(quantityOfIngredient);
        }
        else
        {
            cout << "Enter valid quantity. Press any key to try again" << endl;
            getch();
            continue;
        }
        ingredientsOrdersCount++;
    }
}

// view ingredients ordered

void viewIngredientsOrdered()
{
    system("cls");
    header();
    subHeader("View ingredients");

    cout << "Serial number"
         << "\t\t"
         << "Ingredients"
         << "\t\t"
         << "Qunatity ordered" << endl
         << endl;
    for (int i = 0; i < ingredientsOrdersCount; i++)
    {
        cout << i + 1 << "\t\t" << ingredientsOrdered[i] << "\t\t" << quantitiesOfIngredientsOrdered[i] << endl;
    }

    cout << "Press any key to continue: ";
    getch();
}

// update ingredients ordered
void updateIngredientsOrdered()
{
    string serialNumberToUpdate, newTemporaryIngredeint, newTemporaryQuantity;
    while (true)
    {
        system("cls");
        header();
        subHeader("Update Ingredients");

        cout << "Enter serial number of the ingredient you want to update: (Enter 0 to go back)";
        cin >> serialNumberToUpdate;

        if (serialNumberToUpdate == "0")
        {
            break;
        }

        if (stringNumberValidate(serialNumberToUpdate))
        {
            if (stoi(serialNumberToUpdate) > 0 && stoi(serialNumberToUpdate) < ingredientsOrdersCount)
            {
                cout << "Enter new ingredient: ";
                cin >> newTemporaryIngredeint;

                // ingredients validation will be added here

                ingredientsOrdered[stoi(serialNumberToUpdate) - 1] = newTemporaryIngredeint;
                cout << "Enter new quantity: ";
                cin >> newTemporaryQuantity;

                if (stringNumberValidate(newTemporaryQuantity))
                {
                    quantitiesOfIngredientsOrdered[stoi(serialNumberToUpdate) - 1] = stoi(newTemporaryQuantity);
                }
            }
            else
            {
                cout << "Enter valid number. Press any key to try again";
                getch();
            }
        }
        else
        {
            cout << "Enter valid number. Press any key to try again";
            getch();
        }
    }
}

// delete ingredients

void deleteIngredientsOrdered()
{
    string serialNumberToDelete;
    while (true)
    {
        system("cls");
        header();
        subHeader("Delete ingredinets");
        cout << "Enter serial number of the ingredient you want to delete: (Enter 0 to go back)";
        cin >> serialNumberToDelete;

        if (serialNumberToDelete == "0")
        {
            break;
        }
        if (stringNumberValidate(serialNumberToDelete))
        {
            if (stoi(serialNumberToDelete) > 0 && stoi(serialNumberToDelete) < ingredientsOrdersCount)
            {
                for (int i = stoi(serialNumberToDelete); i < ingredientsOrdersCount - 1; i++)
                {
                    ingredientsOrdered[i] = ingredientsOrdered[i + 1];
                    quantitiesOfIngredientsOrdered[i] = quantitiesOfIngredientsOrdered[i + 1];
                }
                ingredientsOrdersCount--;
            }
            else
            {
                cout << "Invalid number. Press any key to try again";
                continue;
            }
        }
        else
        {
            cout << "Invalid number. Press any key to try again";
            continue;
        }
    }
}
//--------------------------------------------------------------------------------------------------

// Add ingredients to the table

void addIngredientsToTheTable()
{
    string tableIngredient;
    while (true)
    {
        system("cls");
        header();
        subHeader("Ingredients Table");
        cout << "Enter name of ingredient that you want to add: " << endl;
        cout << "(Press 0 to go back)" << endl;
        cin >> tableIngredient;

        if (tableIngredient == "0")
        {
            break;
        }
        recipeIngredients[numberOfTableIngredients] = tableIngredient;
        numberOfTableIngredients++;
    }
}

// view ingredients in the table
void viewIngredientsInTheTable()
{
    system("cls");
    header();
    subHeader("Table Ingredients");
    cout << "Serial Number"
         << "\t\t"
         << "Ingredient" << endl;
    for (int i = 0; i < numberOfTableIngredients; i++)
    {
        cout << i + 1 << "\t\t" << recipeIngredients[i] << endl;
    }

    cout << "Press any key to continue" << endl;
    getch();
}

// delete ingredients from the table

void deleteIngredientsFromTheTable()
{
    string serialNumberToDelete;
    while (true)
    {
        system("cls");
        header();
        subHeader("Deleting Table Ingredients");
        cout << "Enter serial number (from the recipee table) of the ingredient you want to delete: " << endl;
        cin >> serialNumberToDelete;
        if (stringNumberValidate(serialNumberToDelete))
        {
            if (stoi(serialNumberToDelete) > 0 && stoi(serialNumberToDelete) < numberOfTableIngredients)
            {
                for (int i = stoi(serialNumberToDelete); i < numberOfTableIngredients - 1; i++)
                {
                    recipeIngredients[i] = recipeIngredients[i + 1];
                }
                numberOfTableIngredients--;
            }
            else
            {
                cout << "Enter a valid number. Press any key to try again" << endl;
                getch();
            }
        }
        else
        {
            cout << "Enter a valid number. Press any key to try again" << endl;
            getch();
        }
    }
}
// helpful side functions
bool stringNumberValidate(string number) // to check if a string can be correctly evaluated into a number
{
    bool flag = true;
    for (int i = 0; i < number.length(); i++)
    {
        if (number[i] < 48 || number[i] > 57)
        {
            flag = false;
            break;
        }
    }
    return flag;
}
string parse(string line, int field)
{

}

void header()
{
    cout << "    ##############################" << endl;
    cout << "" << endl;
    cout << "  /$$$$$$  /$$                             /$$" << endl;
    cout << " /$$__  $$| $$                            | $$" << endl;
    cout << "| $$  \\__/| $$$$$$$   /$$$$$$   /$$$$$$  /$$$$$$    /$$$$$$   /$$$$$$$" << endl;
    cout << "| $$      | $$__  $$ /$$__  $$ /$$__  $$|_  $$_/   /$$__  $$ /$$_____/" << endl;
    cout << "| $$      | $$  \\ $$| $$$$$$$$| $$$$$$$$  | $$    | $$  \\ $$|  $$$$$$ " << endl;
    cout << "| $$    $$| $$  | $$| $$_____/| $$_____/  | $$ /$$| $$  | $$ \\____  $$" << endl;
    cout << "|  $$$$$$/| $$  | $$|  $$$$$$$|  $$$$$$$  |  $$$$/|  $$$$$$/ /$$$$$$$/" << endl;
    cout << " \\______/ |__/  |__/ \\_______/ \\_______/   \\___/   \\______/ |_______/ " << endl;
    cout << " " << endl;
    cout << "                                  ######################################" << endl;
}

void subHeader(string nameMenu)
{
    cout << endl;
    cout << "----------------------------------------------------------------------------------------------" << endl;
    cout << "                               " << nameMenu << " Menu                                        " << endl;
    cout << "----------------------------------------------------------------------------------------------" << endl;
}
