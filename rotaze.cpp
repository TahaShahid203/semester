#include <iostream>
#include <windows.h>
#include <cmath>

using namespace std;

int robertX = 14;
int robertY = 7;

int verticalEnemyX = 80;
int verticalEnemyY = 10;

int horizontalEnemyX = 7;
int horizontalEnemyY = 15;

int smartEnemyX = 78;
int smartEnemyY = 30;

int diffX;
int diffY;

int score = 0;
int health = 100;
int verticalEnemyHealth = 100;
int horizontalEnemyHealth = 100;
int smartHealth = 100;
int robertReloadTime = 11;
int kenwayReloadTime = 11;
int destoReloadTime = 11;
int billReloadTime = 11;

// the bullets will only be fired if reloads are false

bool robertReload = false;
bool destoReload = false;
bool billReload = false;
bool kenwayReload = false;

int robertBulletCount = 0;
int robertBulletX[1000];
int robertBulletY[1000];
// dx and dy are directions of bullet
int bulletDx[1000];
int bulletDy[1000];
bool isRobertBulletActive[1000];

int topLeftX = 5;
int topLeftY = 5;
int bottomRightX = 100;
int bottomRightY = 40;
int numberOfTurns = 3;

int verticalEnemyBulletCount = 0;
int verticalEnemyBulletX[1000];
int verticalEnemyBulletY[1000];
int verticalEnemybulletDx[1000];
bool isVerticalEnemyBulletActive[1000];

int horizontalEnemyBulletCount = 0;
int horizontalEnemyBulletX[1000];
int horizontalEnemyBulletY[1000];
int horizontalEnemyBulletDy[1000];
bool isHorizontalEnemyBulletActive[1000];

string verticalDirection = "Up";
// initializing vertical enemy's direction
string horizontalDirection = "Right";
// initializing horizontal enemy's direction
void printMaze();
void gotoxy(int x, int y);
// for rotating the maze....a work in progress
void gotoxyWithOrigin(int x, int y, int centreX, int centreY);
char getCharAtxy(short int x, short int y);
char getCharAtxyWithOrigin(short int x, short int y, int centreX, int centreY);

void printRobert();
void eraseRobert();
void moveRobertLeft();
void moveRobertRight();
void moveRobertUp();
void moveRobertDown();

void verticalEnemyMovement();
void horizontalEnemyMovement();
void smartEnemyMovement();

void printVerticalEnemy();
void eraseVerticalEnemy();

void printHorizontalEnemy();
void eraseHorizontalEnemy();

void printSmartEnemy();
void eraseSmartEnemy();

void generateRobertBullet(int dx, int dy);
void moveRobertBullet();
void printRobertBullet(int bulletX, int bulletY);
void eraseRobertBullet(int bulletX, int bulletY);

void generateVerticalEnemyBullet(int dx);
void moveVerticalEnemyBullet();
void printVerticalEnemyBullet(int bulletX, int bulletY);
void eraseVerticalEnemyBullet(int bulletX, int bulletY);

void generateHorizontalEnemyBullet(int dy);
void moveHorizontalEnemyBullet();
void printHorizontalEnemyBullet(int bulletX, int bulletY);
void eraseHorizontalEnemyBullet(int bulletX, int bulletY);

void rotateMazeCalculations();
void rotateMazeImplementation(int centreX, int centreY, int newTopLeftX, int newTopLeftY, int newBottomRightX, int newBottomRightY, int angleDifference);

void printScore();
void eraseScore();

void eraseHealth();
void printHealth();

void printVerticalEnemyHealth();
void eraseVerticalEnemyHealth();

void printHorizontalEnemyHealth();
void eraseHorizontalEnemyHealth();

void printSmartEnemyHealth();
void eraseSmartEnemyHealth();

main()
{
    system("cls");
    printMaze();
    printRobert();
    printVerticalEnemy();
    printHorizontalEnemy();
    printSmartEnemy();
    printScore();
    printHealth();
    printHorizontalEnemyHealth();
    printVerticalEnemyHealth();
    printSmartEnemyHealth();
    int timer = 0;
    int dxx = 1; // initial direction of bullet
    int dyy = 0;
    while (true)
    {
        // once all bullets are fired, it will take 10 seconds to reload
        if (robertBulletCount == 999)
        {
            robertReload = true;
            robertReloadTime = 0;
            robertBulletCount = 0;
        }
        if (robertReloadTime == 10)
        {
            robertReload = false;
        }
        robertReloadTime++;

        if (verticalEnemyBulletCount == 999)
        {
            kenwayReload = true;
            kenwayReloadTime = 0;
            verticalEnemyBulletCount = 0;
        }
        if (kenwayReloadTime == 10)
        {
            kenwayReload = false;
        }
        kenwayReloadTime++;

        if (horizontalEnemyBulletCount == 999)
        {
            destoReload = true;
            destoReloadTime = 0;
            horizontalEnemyBulletCount = 0;
        }
        if (destoReloadTime == 10)
        {
            destoReload = false;
        }
        destoReloadTime++;

        if (GetAsyncKeyState(VK_LEFT))
        {
            moveRobertLeft();
            dxx = -1;
            dyy = 0;
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            moveRobertRight();
            dxx = 1;
            dyy = 0;
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            moveRobertDown();
            dxx = 0;
            dyy = 1;
        }
        if (GetAsyncKeyState(VK_UP))
        {
            moveRobertUp();
            dxx = 0;
            dyy = -1;
        }
        if (GetAsyncKeyState(VK_SPACE) && !(robertReload))
        {
            generateRobertBullet(dxx, dyy);
        }
        // timer makes sure that enemy is slower than robert
        if (timer == 3)
        {
            verticalEnemyMovement();
            horizontalEnemyMovement();
            smartEnemyMovement();
            timer = 0;
        }
        moveRobertBullet();
        moveVerticalEnemyBullet();
        moveHorizontalEnemyBullet();

        timer++;
        Sleep(30);
    }
}

void printMaze()
{
    gotoxy(topLeftX, topLeftY);

    cout << "################################################################################################################" << endl;
    gotoxy(topLeftX, topLeftY+1);
    cout << "#                                                                                                              #" << endl;
    gotoxy(topLeftX, topLeftY+2);
    cout << "#                                                                                                              #" << endl;
    gotoxy(topLeftX, topLeftY+3);
    cout << "#                                                                                                              #" << endl;
    gotoxy(topLeftX, topLeftY+4);
    cout << "#                                  #                                 #                                         #" << endl;
    gotoxy(topLeftX, topLeftY+5);
    cout << "#                                  #                                 #                                         #" << endl;
    gotoxy(topLeftX, topLeftY+6);
    cout << "#                                  #                                 #                                         #" << endl;
    gotoxy(topLeftX, topLeftY+7);
    cout << "#                                  #                                 #                                         #" << endl;
    gotoxy(topLeftX, topLeftY+8);
    cout << "#                                  #                                 #                                         #" << endl;
    gotoxy(topLeftX, topLeftY+9);
    cout << "#                                  #                                 #                                         #" << endl;
    gotoxy(topLeftX, topLeftY+10);
    cout << "#            #######################                                 #########################                 #" << endl;
    gotoxy(topLeftX, topLeftY+11);
    cout << "#                                                                                                              #" << endl;
    gotoxy(topLeftX, topLeftY+12);
    cout << "#                                                                                                              #" << endl;
    gotoxy(topLeftX, topLeftY+13);
    cout << "#                                                                                                              #" << endl;
    gotoxy(topLeftX, topLeftY+14);
    cout << "#                                                                                                              #" << endl;
    gotoxy(topLeftX, topLeftY+15);
    cout << "#                                                                                                              #" << endl;
    gotoxy(topLeftX, topLeftY+16);
    cout << "#                                                                                                              #" << endl;
    gotoxy(topLeftX, topLeftY+17);
    cout << "#                                         ######################                                               #" << endl;
    gotoxy(topLeftX, topLeftY+18);
    cout << "#                                                                                                              #" << endl;
    gotoxy(topLeftX, topLeftY+19);
    cout << "#                                                                                                              #" << endl;
    gotoxy(topLeftX, topLeftY+20);
    cout << "#                                                                                                              #" << endl;
    gotoxy(topLeftX, topLeftY+21);
    cout << "#                                                                                                              #" << endl;
    gotoxy(topLeftX, topLeftY+22);
    cout << "#                                                                                                              #" << endl;
    gotoxy(topLeftX, topLeftY+23);
    cout << "#                                                                                                              #" << endl;
    gotoxy(topLeftX, topLeftY+24);
    cout << "#                                                                                                              #" << endl;
    gotoxy(topLeftX, topLeftY+25);
    cout << "#                                                                                                              #" << endl;
    gotoxy(topLeftX, topLeftY+26);
    cout << "#                                                                                                              #" << endl;
    gotoxy(topLeftX, topLeftY+27);
    cout << "#                                                                                                              #" << endl;
    gotoxy(topLeftX, topLeftY+28);
    cout << "################################################################################################################" << endl;
}

void printRobert()
{
    gotoxy(robertX, robertY);
    cout << "R";
}

void eraseRobert()
{
    gotoxy(robertX, robertY);
    cout << " ";
}

void moveRobertUp()
{
    char next = getCharAtxy(robertX, robertY - 1);
    if (next == ' ')
    {
        eraseRobert();
        robertY--;
        printRobert();
    }
}
void moveRobertDown()
{
    char next = getCharAtxy(robertX, robertY + 1);
    if (next == ' ')
    {
        eraseRobert();
        robertY++;
        printRobert();
    }
}

void moveRobertRight()
{
    char next = getCharAtxy(robertX + 1, robertY);
    if (next == ' ')
    {
        eraseRobert();
        robertX++;
        printRobert();
    }
}
void moveRobertLeft()
{
    char next = getCharAtxy(robertX - 1, robertY);
    if (next == ' ')
    {
        eraseRobert();
        robertX--;
        printRobert();
    }
}

void verticalEnemyMovement()
{
    int dx;
    if ((verticalEnemyX - robertX) < 0)
    {
        dx = 1;
    }
    else if ((verticalEnemyX - robertX) > 0)
    {
        dx = -1;
    }
    if (!kenwayReload)
    {
        generateVerticalEnemyBullet(dx);
    }
    if (verticalDirection == "Up")
    {
        char next = getCharAtxy(verticalEnemyX, verticalEnemyY - 1);
        if (next == ' ')
        {
            eraseVerticalEnemy();
            verticalEnemyY--;
            printVerticalEnemy();
        }
        else
        {
            eraseVerticalEnemy();
            verticalDirection = "Down";
        }
    }

    else if (verticalDirection == "Down")
    {
        char next = getCharAtxy(verticalEnemyX, verticalEnemyY + 1);
        if (next == ' ')
        {
            eraseVerticalEnemy();
            verticalEnemyY++;
            printVerticalEnemy();
        }
        else
        {
            eraseVerticalEnemy();
            verticalDirection = "Up";
        }
    }
}

void printVerticalEnemy()
{
    gotoxy(verticalEnemyX, verticalEnemyY);
    cout << "K";
}

void eraseVerticalEnemy()
{
    gotoxy(verticalEnemyX, verticalEnemyY);
    cout << " ";
}

void horizontalEnemyMovement()
{
    int dy;
    if ((horizontalEnemyY - robertY) < 0)
    {
        dy = 1;
    }
    else if ((horizontalEnemyY - robertY) > 0)
    {
        dy = -1;
    }
    if (!destoReload)
    {
        generateHorizontalEnemyBullet(dy);
    }
    if (horizontalDirection == "Right")
    {
        char next = getCharAtxy(horizontalEnemyX + 1, horizontalEnemyY);
        if (next == ' ')
        {
            eraseHorizontalEnemy();
            horizontalEnemyX++;
            printHorizontalEnemy();
        }
        else
        {
            eraseHorizontalEnemy();
            horizontalDirection = "Left";
        }
    }

    else if (horizontalDirection == "Left")
    {
        char next = getCharAtxy(horizontalEnemyX - 1, horizontalEnemyY);
        if (next == ' ')
        {
            eraseHorizontalEnemy();
            horizontalEnemyX--;
            printHorizontalEnemy();
        }
        else
        {
            eraseHorizontalEnemy();
            horizontalDirection = "Right";
        }
    }
}

void printHorizontalEnemy()
{
    gotoxy(horizontalEnemyX, horizontalEnemyY);
    cout << "D";
}

void eraseHorizontalEnemy()
{
    gotoxy(horizontalEnemyX, horizontalEnemyY);
    cout << " ";
}

void smartEnemyMovement()
{
    eraseSmartEnemy();
    diffX = smartEnemyX - robertX;
    diffY = smartEnemyY - robertY;
    if (diffX < 0)
    {
        diffX++;
    }
    else if (diffX > 0)
    {
        diffX--;
    }

    if (diffY < 0)
    {
        diffY++;
    }
    else if (diffY > 0)
    {
        diffY--;
    }

    char nextX = getCharAtxy(robertX + diffX, smartEnemyY);
    char nextY = getCharAtxy(smartEnemyX, robertY + diffY);
    if (nextX == ' ')
    {
        smartEnemyX = robertX + diffX;
    }
    if (nextY == ' ')
    {
        smartEnemyY = robertY + diffY;
    }
    printSmartEnemy();
}

void printSmartEnemy()
{
    gotoxy(smartEnemyX, smartEnemyY);
    cout << "S";
}
void eraseSmartEnemy()
{
    gotoxy(smartEnemyX, smartEnemyY);
    cout << ' ';
}

void generateRobertBullet(int dx, int dy)
{
    char next = getCharAtxy(robertX + dx, robertY + dy);
    if (next != '#')
    {
        gotoxy(robertX + dx, robertY + dy);
        cout << ".";
        robertBulletX[robertBulletCount] = robertX + dx;
        robertBulletY[robertBulletCount] = robertY + dy;
        isRobertBulletActive[robertBulletCount] = true;
        bulletDx[robertBulletCount] = dx;
        bulletDy[robertBulletCount] = dy;

        robertBulletCount++;
    }
}
void printRobertBullet(int bulletX, int bulletY)
{
    gotoxy(bulletX, bulletY);
    cout << ".";
}
void eraseRobertBullet(int bulletX, int bulletY)
{
    gotoxy(bulletX, bulletY);
    cout << ' ';
}

void moveRobertBullet()
{
    for (int i = 0; i < robertBulletCount; i++)
    {
        if (isRobertBulletActive[i])
        {
            eraseRobertBullet(robertBulletX[i], robertBulletY[i]);
            char next = getCharAtxy(robertBulletX[i] + bulletDx[i], robertBulletY[i] + bulletDy[i]);
            if (next == ' ')
            {
                robertBulletX[i] += bulletDx[i];
                robertBulletY[i] += bulletDy[i];

                printRobertBullet(robertBulletX[i], robertBulletY[i]);
            }
            else if (next == 'D' || next == 'K' || next == 'S')
            {
                if (next == 'K')
                {
                    eraseVerticalEnemyHealth();
                    verticalEnemyHealth--;
                    printVerticalEnemyHealth();
                }
                else if (next == 'D')
                {
                    eraseHorizontalEnemyHealth();
                    horizontalEnemyHealth--;
                    printHorizontalEnemyHealth();
                }
                else if (next == 'S')
                {
                    eraseSmartEnemyHealth();
                    smartHealth--;
                    printSmartEnemyHealth();
                }
                eraseScore();
                score++;
                printScore();
                isRobertBulletActive[i] = false;
            }
            else
            {
                isRobertBulletActive[i] = false;
            }
        }
    }
}

void generateVerticalEnemyBullet(int dx)
{
    char next = getCharAtxy(verticalEnemyX + dx, verticalEnemyY);
    if (next != '#')
    {
        gotoxy(verticalEnemyX + dx, verticalEnemyY);
        cout << "-";
        verticalEnemyBulletX[verticalEnemyBulletCount] = verticalEnemyX + dx;
        verticalEnemyBulletY[verticalEnemyBulletCount] = verticalEnemyY;
        verticalEnemybulletDx[verticalEnemyBulletCount] = dx;
        isVerticalEnemyBulletActive[verticalEnemyBulletCount] = true;
        verticalEnemyBulletCount++;
    }
}
void printVerticalEnemyBullet(int bulletX, int bulletY)
{
    gotoxy(bulletX, bulletY);
    cout << "-";
}
void eraseVerticalEnemyBullet(int bulletX, int bulletY)
{
    gotoxy(bulletX, bulletY);
    cout << ' ';
}

void moveVerticalEnemyBullet()
{
    for (int i = 0; i < verticalEnemyBulletCount; i++)
    {
        if (isVerticalEnemyBulletActive[i])
        {
            eraseVerticalEnemyBullet(verticalEnemyBulletX[i], verticalEnemyBulletY[i]);
            char next = getCharAtxy(verticalEnemyBulletX[i] + verticalEnemybulletDx[i], verticalEnemyBulletY[i]);
            if (next == ' ' || next == 'S' || next == 'D')
            {
                verticalEnemyBulletX[i] += verticalEnemybulletDx[i];
                printVerticalEnemyBullet(verticalEnemyBulletX[i], verticalEnemyBulletY[i]);
            }
            else if (next == 'R')
            {
                eraseHealth();
                health--;
                printHealth();
                isVerticalEnemyBulletActive[i] = false;
            }
            else
            {
                isVerticalEnemyBulletActive[i] = false;
            }
        }
    }
}

void generateHorizontalEnemyBullet(int dy)
{
    char next = getCharAtxy(horizontalEnemyX, horizontalEnemyY + dy);
    if (next != '#')
    {
        gotoxy(horizontalEnemyX, horizontalEnemyY + dy);
        cout << "-";
        horizontalEnemyBulletX[horizontalEnemyBulletCount] = horizontalEnemyX;
        horizontalEnemyBulletY[horizontalEnemyBulletCount] = horizontalEnemyY + dy;
        horizontalEnemyBulletDy[horizontalEnemyBulletCount] = dy;
        isHorizontalEnemyBulletActive[horizontalEnemyBulletCount] = true;
        horizontalEnemyBulletCount++;
    }
}
void printHorizontalEnemyBullet(int bulletX, int bulletY)
{
    gotoxy(bulletX, bulletY);
    cout << "-";
}
void eraseHorizontalEnemyBullet(int bulletX, int bulletY)
{
    gotoxy(bulletX, bulletY);
    cout << ' ';
}

void moveHorizontalEnemyBullet()
{
    for (int i = 0; i < horizontalEnemyBulletCount; i++)
    {
        if (isHorizontalEnemyBulletActive[i])
        {
            eraseHorizontalEnemyBullet(horizontalEnemyBulletX[i], horizontalEnemyBulletY[i]);
            char next = getCharAtxy(horizontalEnemyBulletX[i], horizontalEnemyBulletY[i] + horizontalEnemyBulletDy[i]);
            if (next == ' ' || next == 'S' || next == 'K')
            {
                horizontalEnemyBulletY[i] += horizontalEnemyBulletDy[i];
                printHorizontalEnemyBullet(horizontalEnemyBulletX[i], horizontalEnemyBulletY[i]);
            }
            else if (next == 'R')
            {
                eraseHealth();
                health--;
                printHealth();
                isHorizontalEnemyBulletActive[i] = false;
            }
            else
            {
                isHorizontalEnemyBulletActive[i] = false;
            }
        }
    }
}

void printScore()
{
    gotoxy(120, 30);
    cout << "Score: " << score;
}

void eraseScore()
{
    gotoxy(127, 30);
    cout << "     ";
}

void printHealth()
{
    gotoxy(120, 32);
    cout << "Robert's Health: " << health;
}
void eraseHealth()
{
    gotoxy(137, 32);
    cout << "     ";
}

void printVerticalEnemyHealth()
{
    gotoxy(120, 34);
    cout << "Kenway's health: " << verticalEnemyHealth;
}
void eraseVerticalEnemyHealth()
{
    gotoxy(137, 34);
    cout << "      ";
}

void printHorizontalEnemyHealth()
{
    gotoxy(120, 36);
    cout << "Desto's health: " << horizontalEnemyHealth;
}
void eraseHorizontalEnemyHealth()
{
    gotoxy(136, 36);
    cout << "   ";
}

void printSmartEnemyHealth()
{
    gotoxy(120, 38);
    cout << "Bill's health: " << smartHealth;
}

void eraseSmartEnemyHealth()
{
    gotoxy(134, 38);
    cout << "     ";
}

void rotateMazeCalculations()
{
    int centreX = (topLeftX + bottomRightX) / 2;
    int centreY = (topLeftY + bottomRightY) / 2;
    int newTopLeftX = (topLeftX - bottomRightX) / 2;
    int newTopLeftY = (topLeftY - bottomRightY) / 2;
    int newBottomRightX = 0 - newTopLeftX;
    int newBottomRightY = 0 - newTopLeftY;
    int angleDifference = (90 * M_PI) / (180 * numberOfTurns);

    for (int i = 0; i < numberOfTurns; i++)
    {
        rotateMazeImplementation(centreX, centreY, newTopLeftX, newTopLeftY, newBottomRightX, newBottomRightY, angleDifference);
        Sleep(100);
    }
}

void rotateMazeImplementation(int centreX, int centreY, int newTopLeftX, int newTopLeftY, int newBottomRightX, int newBottomRightY, int angleDifference)
{
    int x, y;
    for (int i = newTopLeftY; i <= newBottomRightY; i++)
    {
        for (int j = newTopLeftX; j <= newBottomRightX; j++)
        {
            char c = getCharAtxyWithOrigin(i, j, centreX, centreY);
            x = j * cos(angleDifference) - i * sin(angleDifference);
            y = i * cos(angleDifference) + j * sin(angleDifference);
            gotoxyWithOrigin(x, y, centreX, centreY);
            cout << c;
        }
    }
}

void gotoxyWithOrigin(int x, int y, int centreX, int centreY)
{
    gotoxy(x + centreX, y + centreY);
}

char getCharAtxyWithOrigin(short int x, short int y, int centreX, int centreY)
{
    return getCharAtxy(x + centreX, y + centreY);
}

void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

char getCharAtxy(short int x, short int y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize;
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}