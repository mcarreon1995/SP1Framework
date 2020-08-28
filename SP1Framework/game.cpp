// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include "map.h"
#include "playerVL.h"
#include "Entity.h"
#include "Enemy_Fire.h"
#include "Bat.h"
#include "BatBullet.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>

int cMap = 0;

Enemy_Fire FIRE('F');
map* currentMap[6] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
Entity* enemyPtr[6][5];

double  g_dElapsedTime;
double  g_dDeltaTime;
SKeyEvent g_skKeyEvent[K_COUNT];
SMouseEvent g_mouseEvent;
int roundnumber;
bool LevelCompleted = false;
int collected = 0;
int NotCollected = 0;
int score = 0;
int totalscore = 0;
int pointsChar = 0;
bool roundActive = false;
double saveTime = 0;

int arrowMenu = 0;

// Game specific variables here
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_MENU; // initial state

// Console object
Console g_Console(80, 25, "M - Reversal");


//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------

void init( void )
{ 
    // sets the initial state for the game
    g_eGameState = S_MENU;

    // Set precision for floating point output
    g_dElapsedTime = 0.0;    
    initializeMaps();
    initializeEnemy();
    changeMap();
    FIRE.setposX(4);
    FIRE.setposY(2);

    g_sChar.m_cLocation.X = 15 + 1;
    g_sChar.m_cLocation.Y = 23;
    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");

    // remember to set your keyboard handler, so that your functions can be notified of input events
    g_Console.setKeyboardHandler(keyboardHandler);
    g_Console.setMouseHandler(mouseHandler);
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Get all the console input events
//            This function sets up the keyboard and mouse input from the console.
//            We will need to reset all the keyboard status, because no events will be sent if no keys are pressed.
//
//            Remember to set the handlers for keyboard and mouse events.
//            The function prototype of the handler is a function that takes in a const reference to the event struct
//            and returns nothing. 
//            void pfKeyboardHandler(const KEY_EVENT_RECORD&);
//            void pfMouseHandlerconst MOUSE_EVENT_RECORD&);
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput( void )
{
    // resets all the keyboard events
    memset(g_skKeyEvent, 0, K_COUNT * sizeof(*g_skKeyEvent));
    // then call the console to detect input from user
    g_Console.readConsoleInput();    
}

//--------------------------------------------------------------
// Purpose  : This is the handler for the keyboard input. Whenever there is a keyboard event, this function will be called.
//            Ideally, you should pass the key event to a specific function to handle the event.
//            This is because in some states, some keys would be disabled. Hence, to reduce your code complexity, 
//            it would be wise to split your keyboard input handlers separately.
//            
//            The KEY_EVENT_RECORD struct has more attributes that you can use, if you are adventurous enough.
//
//            In this case, we are not handling any keyboard event in the Splashscreen state
//            
// Input    : const KEY_EVENT_RECORD& keyboardEvent - reference to a key event struct
// Output   : void
//--------------------------------------------------------------
void keyboardHandler(const KEY_EVENT_RECORD& keyboardEvent)
{    
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: // don't handle anything for the splash screen
        break;
    case S_GAME1: gameplayKBHandler(keyboardEvent); // handle gameplay keyboard event 
        break;
    case S_LVLCOMP: gameplayKBHandler(keyboardEvent);
        break;
    case S_MENU: gameplayKBHandler(keyboardEvent);
        break;
    case S_ENDGAME: gameplayKBHandler(keyboardEvent);
    }
}

//--------------------------------------------------------------
// Purpose  : This is the handler for the mouse input. Whenever there is a mouse event, this function will be called.
//            Ideally, you should pass the key event to a specific function to handle the event.
//            This is because in some states, some keys would be disabled. Hence, to reduce your code complexity, 
//            it would be wise to split your keyboard input handlers separately.
//            
//            For the mouse event, if the mouse is not moved, no event will be sent, hence you should not reset the mouse status.
//            However, if the mouse goes out of the window, you would not be able to know either. 
//
//            The MOUSE_EVENT_RECORD struct has more attributes that you can use, if you are adventurous enough.
//
//            In this case, we are not handling any mouse event in the Splashscreen state
//            
// Input    : const MOUSE_EVENT_RECORD& mouseEvent - reference to a mouse event struct
// Output   : void
//--------------------------------------------------------------
void mouseHandler(const MOUSE_EVENT_RECORD& mouseEvent)
{    
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: // don't handle anything for the splash screen
        break;
    case S_GAME1: gameplayMouseHandler(mouseEvent); // handle gameplay mouse event
        break;
    case S_MENU: gameplayMouseHandler(mouseEvent);
        break;
    case S_LVLCOMP:;
        break;
    case S_ENDGAME:;
    }
}

//--------------------------------------------------------------
// Purpose  : This is the keyboard handler in the game state. Whenever there is a keyboard event in the game state, this function will be called.
//            
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : const KEY_EVENT_RECORD& keyboardEvent
// Output   : void
//--------------------------------------------------------------
void gameplayKBHandler(const KEY_EVENT_RECORD& keyboardEvent)
{
    // here, we map the key to our enums
    EKEYS key = K_COUNT;
    switch (keyboardEvent.wVirtualKeyCode)
    {
    case VK_UP: key = K_UP; break;
    case VK_DOWN: key = K_DOWN; break;
    case VK_LEFT: key = K_LEFT; break; 
    case VK_RIGHT: key = K_RIGHT; break; 
    case VK_SPACE: key = K_SPACE; break;
    case VK_ESCAPE: key = K_ESCAPE; break;
    //case 0x31: key = K_1; break;
    //case 0x32: key = K_2; break;
    //case 0x33: key = K_3; break;
    }
    // a key pressed event would be one with bKeyDown == true
    // a key released event would be one with bKeyDown == false
    // if no key is pressed, no event would be fired.
    // so we are tracking if a key is either pressed, or released
    if (key != K_COUNT)
    {
        g_skKeyEvent[key].keyDown = keyboardEvent.bKeyDown;
        g_skKeyEvent[key].keyReleased = !keyboardEvent.bKeyDown;
    }    
}

//--------------------------------------------------------------
// Purpose  : This is the mouse handler in the game state. Whenever there is a mouse event in the game state, this function will be called.
//            
//            If mouse clicks are detected, the corresponding bit for that mouse button will be set.
//            mouse wheel, 
//            
// Input    : const KEY_EVENT_RECORD& keyboardEvent
// Output   : void
//--------------------------------------------------------------
void gameplayMouseHandler(const MOUSE_EVENT_RECORD& mouseEvent)
{
    if (mouseEvent.dwEventFlags & MOUSE_MOVED) // update the mouse position if there are no events
    {
        g_mouseEvent.mousePosition = mouseEvent.dwMousePosition;
    }
    g_mouseEvent.buttonState = mouseEvent.dwButtonState;
    g_mouseEvent.eventFlags = mouseEvent.dwEventFlags;
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;

    switch (g_eGameState)
    {
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;
        case S_MENU: menuInput();
            break;
        case S_GAME1: updateGame(); // gameplay logic when we are in the game
            break;
        case S_LVLCOMP: renderLevelCompleted();
            break;
        case S_TRANS: renderTransition();
            break;
        case S_SCORE: scorePage();
            break;
        case S_ENDGAME: endInput();
    }
}


void splashScreenWait()    // waits for time to pass in splash screen
{
    if (g_dElapsedTime > 3.0) // wait for 3 seconds to switch to game mode, else do nothing
        g_eGameState = S_MENU;
}

void updateGame()       // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
    moveEnemy();
}

void moveCharacter()
{    

    // Updating the location of the character based on the key release
    // providing a beep sound whenver we shift the character
    int pos_x = g_sChar.m_cLocation.X - 15;
    int pos_y = g_sChar.m_cLocation.Y;

    if (g_skKeyEvent[K_UP].keyDown && g_sChar.m_cLocation.Y > 0 && checkCollision(pos_x, pos_y - 1) != 1)
    {
        //Beep(783.99, 30);
        g_sChar.m_cLocation.Y--;      

    }
    if (g_skKeyEvent[K_LEFT].keyDown && g_sChar.m_cLocation.X > 15 && checkCollision(pos_x - 1, pos_y) != 1)
    {
        //Beep(783.99, 30);
        g_sChar.m_cLocation.X--;        
    }
    if (g_skKeyEvent[K_DOWN].keyDown && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1 && checkCollision(pos_x, pos_y + 1) != 1)
    {
        //Beep(783.99, 30);
        g_sChar.m_cLocation.Y++;        
    }
    if (g_skKeyEvent[K_RIGHT].keyDown && g_sChar.m_cLocation.X < 64 && checkCollision(pos_x + 1, pos_y) != 1)
    {
        //Beep(783.99, 30);
        g_sChar.m_cLocation.X++;        

    }
    if (g_skKeyEvent[K_SPACE].keyDown)
    {
        cMap += 1;
    }
    int new_x = g_sChar.m_cLocation.X - 15;
    int new_y = g_sChar.m_cLocation.Y;
    if (checkCollision(new_x, new_y) == 2)
    {
        Beep(440.00, 30);
        Beep(659.25, 30);
        Beep(880.00, 30);
        NotCollected -= 1;
        collected += 1;
        currentMap[cMap]->updateMap(new_x, new_y, ' ');

        if (g_dElapsedTime <= 10.9)
        {
            pointsChar += 10;
        }

        if (g_dElapsedTime > 10.9 && g_dElapsedTime <= 25.9)
        {
            pointsChar += 5;
        }

        if (g_dElapsedTime > 26.0 && g_dElapsedTime < 35.0)
        {
            pointsChar += 3;
        }

        else
        {
            pointsChar += 1;
        }

        
    }
    if (checkCollision(new_x, new_y) == 3) {
        if (collected == currentMap[cMap]->getTotalCollectibles()) {
            score += pointsChar;
            totalscore += score;
            cMap += 1;
            g_eGameState = S_LVLCOMP;
        }
        else {
            g_sChar.m_cLocation.Y = pos_y;
            Beep(660.00, 30);
        }
    }
}
void processUserInput()
{
    // quits the game if player hits the escape key
    if (g_skKeyEvent[K_ESCAPE].keyDown) {
        resetGame();
        g_eGameState = S_MENU;
    } 
}

//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: renderSplashScreen();
        break;
    case S_MENU: renderMenu();
        break;
    case S_GAME1: renderGame();
        break;
    case S_LVLCOMP: renderLevelCompleted();
        break;
    case S_SCORE: scorePage();
        break;
    case S_ENDGAME: renderEndscreen();
    }
    renderFramerate();      // renders debug information, frame rate, elapsed time, etc
    renderInputEvents();    // renders status of input events
    renderToScreen();       // dump the contents of the buffer to the screen, one frame worth of game
    
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0);
}

void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}

void renderSplashScreen()  // renders the splash screen
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X / 2 - 9;
    g_Console.writeToBuffer(c, "M - Reversal", 0x03);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 20;
    g_Console.writeToBuffer(c, "Press <Space> to change character colour", 0x09);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);
}

void renderGame()
{
    renderMap();        // renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer
    renderScore();
    
}

void renderMap()
{
    /*for (int i = 0; i < 12; ++i)
    {
        c.X = 5 * i;
        c.Y = i + 1;
        colour(colors[i]);
        g_Console.writeToBuffer(c, " °±²Û", colors[i]);
    }
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 25; j++) {
            c.X = 15 + i;
            c.Y = j;
            g_Console.writeToBuffer(c, " ", colors[13]);
        }
    }*/


    // Set up sample colours, and output shadings
    const WORD colors[] = {
        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6, 0, 0
    };

    COORD c;
    for (int i = 0; i < 80; i++) {
        for (int j = 0; j < 25; j++) {
            c.X = i;
            c.Y = j;
            g_Console.writeToBuffer(c, " ", colors[13]);
        }
    }
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 25; j++) {
            c.X = 15 + i;
            c.Y = j;
            g_Console.writeToBuffer(c, " ", colors[11]);
        }
    }
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 25; j++) {
            c.X = 15 + i;
            c.Y = j;
            /*if (c.X <= g_sChar.m_cLocation.X + 7 && c.X >= g_sChar.m_cLocation.X - 7) {
                if (c.Y <= g_sChar.m_cLocation.Y + 4 && c.Y >= g_sChar.m_cLocation.Y - 4) {*/
                    if (currentMap[cMap]->getMapVar(i, j) != '#') {
                        g_Console.writeToBuffer(c, " ", colors[12]);
                    }
                    else
                        g_Console.writeToBuffer(c, "²", colors[11]);
                    if (currentMap[cMap]->getMapVar(i, j) == 'C') {
                        g_Console.writeToBuffer(c, " ", colors[3]);
                    }
                    else if (currentMap[cMap]->getMapVar(i, j) == 'E') {
                        g_Console.writeToBuffer(c, " ", colors[4]);
                    }
                    else if (currentMap[cMap]->getMapVar(i, j) == 'F') {
                        g_Console.writeToBuffer(c, "F", colors[9]);
                    }
                    else if (currentMap[cMap]->getMapVar(i, j) == 'f') {
                        g_Console.writeToBuffer(c, "f", colors[9]);
                    }
                    else if (currentMap[cMap]->getMapVar(i, j) == '*') {
                        g_Console.writeToBuffer(c, "*");
                    }
                    else if (currentMap[cMap]->getMapVar(i, j) == 'b') {
                        g_Console.writeToBuffer(c, "B", colors[6]);
                    }
              /*  }
            }*/
        }
    }
}

void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0C;
    COORD c;
    if (g_sChar.m_bActive)
    {
        charColor = 0x0A;
    }
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)1, charColor);
    
}

void renderLevelCompleted()
{
    std::ostringstream ss;
    COORD c;
    for (int i = 0; i < 80; i++) {
        for (int j = 0; j < 25; j++) {
            c.X = i;
            c.Y = j;
            g_Console.writeToBuffer(c, " ", 0);
        }
    }
    c.X = 25;
    c.Y = 12;
    ss << "Level " << std::to_string(cMap-1) << " Completed";
    if (cMap == 1) {
        g_Console.writeToBuffer(c, "Tutorial Level Completed");
    }
    else {
        g_Console.writeToBuffer(c, ss.str());
    }
    c.Y += 2;
    ss.str("");
    ss << "Score : " << std::to_string(score);
    g_Console.writeToBuffer(c, ss.str());
    c.Y += 2;
    ss.str("");
    ss << "Total Score : " << std::to_string(totalscore);
    g_Console.writeToBuffer(c, ss.str());
    c.Y += 2;
    g_Console.writeToBuffer(c, "Press <SPACE> to Continue");
    if (g_skKeyEvent[K_SPACE].keyDown) {
        g_eGameState = S_GAME1;
        changeMap();
    }

    std::ifstream input("Highest_Score.txt");
    //incase for some odd reason the txt file cant be opened
    if (!input.is_open())
    {
        std::cout << "Unable to read file\n";
        return;
    }

    int Highest_Score;
    input >> Highest_Score;
    input.close();

    std::ofstream output("Highest_Score.txt");
    // if the totalscore is higher than the highest_score integer stored inside the text file it will delete the old highest_Score and update the totalscore in.
    // if the totalscore is lower than the highest_Score integer stored, then it will not update the data stored in it.
    if (totalscore > Highest_Score) 
    {
        output << totalscore;
    }
    else
    {
        output << Highest_Score;
    }

    output.close();
    
    //Instructions: If u need to cout the text in the file the code is :
    // string <anything>; (used to output the text file)
    //std::ifstream input("Highest_Score.txt")
    //while (getline (input, <wtv name u gave to to define the string above>))
    //{
    //cout << <wtv name u gave to to define the string above>
    //}

    std::ifstream time("Time_Check.txt");
    //incase for some odd reason the txt file cant be opened
    if (!time.is_open())
    {
        std::cout << "Unable to read file\n";
        return;
    }

    double Time_Check;
    time >> Time_Check;
    time.close();

    std::ofstream timeout("Time_Check.txt");
    // if the totalscore is higher than the highest_score integer stored inside the text file it will delete the old highest_Score and update the totalscore in.
    // if the totalscore is lower than the highest_Score integer stored, then it will not update the data stored in it.
    if (g_dElapsedTime < Time_Check)
    {
        timeout << g_dElapsedTime;
    }
    else
    {
        timeout << Time_Check;
    }

    timeout.close();
}

void renderTransition()
{
    std::ostringstream ss;
    COORD c;
    c.X = 12;
    c.Y = 40;

    if (roundnumber == 1)
    {
        g_Console.writeToBuffer(c, "Tutorial Level", 0xF6);
    }
    else if (roundnumber == 2)
    {
        g_Console.writeToBuffer(c, "Level 1", 0xF6);
    }
    else if (roundnumber == 3)
    {
        g_Console.writeToBuffer(c, "Level 2", 0xF6);
    }
    else if (roundnumber == 4)
    {
        g_Console.writeToBuffer(c, "Level 3", 0xF6);
    }
    else if (roundnumber == 5)
    {
        g_Console.writeToBuffer(c, "Level 4", 0xF6);
    }
    else if (roundnumber == 6)
    {
        g_Console.writeToBuffer(c, "Level 5", 0xF6);
    }
}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    /*ss << std::fixed << std::setprecision(3);
    ss << 1.0 / g_dDeltaTime << "fps";
    c.X = g_Console.getConsoleSize().X - 9;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());*/

    /* displays the elapsed time
    ss.str("");
    ss << g_dElapsedTime << "secs";
    c.X = g_Console.getConsoleSize().X - 11;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str(), 0x59); */
}

void renderScore()
{
    while (roundActive == true)
    {
        if (NotCollected -= 1)
        {
            collected += 1;
        }
    }
    COORD c;
    std::ostringstream ss;
    ss << "Collected " << collected << "/" << currentMap[cMap]->getTotalCollectibles();
    c.X = 0;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());

    ss.str("");
    ss << "<Esc> to menu";
    c.X = 0;
    c.Y = 2;
    g_Console.writeToBuffer(c, ss.str());

    ss.str("");
    ss << g_dElapsedTime << "secs";
    c.X = g_Console.getConsoleSize().X - 11;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str(), 0x59);
}


// this is an example of how you would use the input events
void renderInputEvents()
{

}

int checkCollision(int x, int y) {
    int collideType = 0;
    if (currentMap[cMap]->getMapVar(x, y) == '#') {
        collideType = 1;
    }
    else if (currentMap[cMap]->getMapVar(x, y) == 'C') {
        collideType = 2;
    }
    else if (currentMap[cMap]->getMapVar(x, y) == 'E') {
        collideType = 3;
    }
    else if (x == g_sChar.m_cLocation.X && y == g_sChar.m_cLocation.Y) {
        collideType = 4;
    }
    return collideType;
}

void changeMap() {
    collected = 0;
    pointsChar == 0;
    g_dElapsedTime = 0;
    score = 0;


    NotCollected = currentMap[cMap]->getTotalCollectibles();
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 25; j++) {
            if (currentMap[cMap]->getMapVar(i, j) == 'B') {
                g_sChar.m_cLocation.X = 15 + i;
                g_sChar.m_cLocation.Y = j;
            }
        }
    }
    
    
    //for (int i = 0; i < 50; i++) {
    //    for (int j = 0; j < 25; j++) {
    //        if (currentMap[cMap]->getMapVar(i, j) == 'V') {
    //            g_sChar.m_cLocation.X = 15 + i;
    //            g_sChar.m_cLocation.Y = j;
    //        }
    //    }
    //}
}

void renderMenu()
{
    COORD c = g_Console.getConsoleSize();
    std::ostringstream ss;
    const WORD colors[] = {
        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6, 0, 0x434343
    };

    //Moving Banner
    char banner[20][20] = { {'-', '-', '-', ' ', ' ', '-', '-', '-', ' ', '-', '-', '-', ' ', ' ', '-', '-', '-'},
                            {' ', ' ', '|', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', '|', ' ', '|'},
                            {' ', ' ', '|', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', '|', ' ', '|'},
                            {' ', ' ', '|', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', '|', ' ', '|'},
                            {'-', '-', '-', ' ', ' ', '|', ' ', '|', ' ', '-', '-', '-', ' ', ' ', '|', ' ', '|'},
                            {'|', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', '|', ' ', '|'},
                            {'|', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', '|', ' ', '|'},
                            {'-', '-', '-', ' ', ' ', '-', '-', '-', ' ', '-', '-', '-', ' ', ' ', '-', '-', '-'},
    };

    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            c.Y = 2 + i;
            c.X = 29 + j;
            g_Console.writeToBuffer(c, banner[i][j], 11);
        }
    }

    c.Y = 13;
    c.X = 25;
    g_Console.writeToBuffer(c, "+-----------------------+", 4);

    c.Y = 14;
    c.X = 33;
    g_Console.writeToBuffer(c, "1. Play", 0x03);

    c.Y = 15;
    c.X = 33;
    g_Console.writeToBuffer(c, "2. Scores", 0x09);

    c.Y = 16;
    c.X = 33;
    g_Console.writeToBuffer(c, "3. Quit", 0x09);

    c.Y = 17;
    c.X = 25;
    g_Console.writeToBuffer(c, "+-----------------------+", 4);

    if ((g_mouseEvent.mousePosition.X >= 31) && (g_mouseEvent.mousePosition.X <= 38) && (g_mouseEvent.mousePosition.Y >= 14) && (g_mouseEvent.mousePosition.Y <= 16))
    {
        c.X = 18;
        c.Y = g_mouseEvent.mousePosition.Y;
        ss.str("");
        ss << "__________||";
        g_Console.writeToBuffer(c, ss.str(), 5);
        ss.str("");

        c.X = 45;
        c.Y = g_mouseEvent.mousePosition.Y;
        ss.str("");
        ss << "||__________";
        g_Console.writeToBuffer(c, ss.str(), 5);
        ss.str("");

        arrowMenu = g_mouseEvent.mousePosition.Y - 14;
    }
    else {
        c.X = 18;
        c.Y = arrowMenu+14;
        ss.str("");
        ss << "__________||";
        g_Console.writeToBuffer(c, ss.str(), 5);
        ss.str("");

        c.X = 45;
        c.Y = arrowMenu+14;
        ss.str("");
        ss << "||__________";
        g_Console.writeToBuffer(c, ss.str(), 5);
        ss.str("");
    }
}

//Leaderboard Page
void scorePage()
{
    COORD c;

    c.Y = 8;
    c.X = 28.9;
    g_Console.writeToBuffer(c, "DEFENDING CHAMPION", 4);

    c.Y = 9;
    c.X = 25;
    g_Console.writeToBuffer(c, "+-----------------------+", 12);

    std::string HighS;
    std::ifstream input("Highest_Score.txt");
    while (getline(input, HighS))
    {
        std::ostringstream ss;
        ss << "Highscore: " << HighS;
        c.Y = 11;
        c.X = 25;
        g_Console.writeToBuffer(c, ss.str(), 12);
        ss.str("");
    }
    input.close();

    std::string HighT;
    std::ifstream time("Time_Check.txt");
    while (getline(time, HighT))
    {
        std::ostringstream ss;
        ss << "Best Time : " << HighT;
        c.Y = 12;
        c.X = 25;
        g_Console.writeToBuffer(c, ss.str(), 13);
        ss.str("");
    }
    time.close();

    c.Y = 14;
    c.X = 25;
    g_Console.writeToBuffer(c, "+-----------------------+", 12);

    


}

void menuInput() {
    //Keyboard Event
    if (g_skKeyEvent[K_1].keyReleased){
        g_eGameState = S_GAME1;
    }
    if (g_skKeyEvent[K_3].keyReleased) {
        g_bQuitGame = true;
    }
    if (g_skKeyEvent[K_DOWN].keyReleased) {
        if (arrowMenu < 2) {
            arrowMenu++;
        }
    }
    if (g_skKeyEvent[K_UP].keyReleased) {
        if (arrowMenu > 0) {
            arrowMenu--;
        }
    }
    if (g_skKeyEvent[K_SPACE].keyReleased) {
        switch (arrowMenu) {
        case 0:
            g_eGameState = S_ENDGAME;
            break;
        case 1:
            g_eGameState = S_SCORE;
            break;
        case 2:
            g_bQuitGame = true;
        }
    }
    //Mouse Event
    switch (g_mouseEvent.eventFlags)
    {
    case 0:
        if ((g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED) && (g_mouseEvent.mousePosition.X >= 31) && (g_mouseEvent.mousePosition.X <= 38) && (g_mouseEvent.mousePosition.Y == 14))
        {
            g_eGameState = S_GAME1;
        }
        else if ((g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED) && (g_mouseEvent.mousePosition.X >= 31) && (g_mouseEvent.mousePosition.X <= 37) && (g_mouseEvent.mousePosition.Y == 16))
        {
            g_bQuitGame = true;
        }
        else if ((g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED) && (g_mouseEvent.mousePosition.X >= 31) && (g_mouseEvent.mousePosition.X <= 37) && (g_mouseEvent.mousePosition.Y == 15))
        {
            g_eGameState = S_SCORE;
        }
    }
}

void initializeMaps() {
    
    srand(time(NULL));
    char maze_1_Array[25][50] = {
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',},
        {'#','#','#','#','#','#','#','#','#','#','#','#','E','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','S',' ',' ','P','#','#','#','#','#',},
        {'#','P','#','#','S',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#',},
        {'#',' ','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#',},
        {'#',' ','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','P','#',},
        {'#',' ','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#',' ','#',},
        {'#',' ','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#',' ','#',},
        {'#',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','P',' ',' ',' ','#','#','#','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ','#',},
        {'#',' ','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#',' ','#',},
        {'#',' ','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#',' ','#',},
        {'#',' ','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#',' ','#',},
        {'#',' ','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','P','#','#','#','#','#',' ','#','#','#','#','#','#',' ','#',},
        {'#',' ','#','#',' ',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#',' ','#','#','#','#','#',' ','#','#','#','#','#','#',' ','#',},
        {'#',' ','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','P','#','#',' ','#','D',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#',' ','#','#','#','#','#','#',' ','#',},
        {'#',' ',' ',' ','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#',' ','#','#',' ','#',' ','#','#','#','#','#','#',' ','#','#','#','#','#',' ','#','#','#','#','#','#',' ','#',},
        {'#','#','#',' ','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#',' ','#','#',' ','#',' ','#','#','#','#','#','#',' ','#','#','#','#','#',' ','#','#','#','#','#','#',' ','#',},
        {'#','#','#',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','D',' ',' ',' ',' ',' ','#','#','#','#','#','#',' ','#','#','#','#','#',' ','#','#','#','#','#','#',' ','#',},
        {'#','#','#',' ','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#',' ','#','#',' ','#','#','#','#','#','#',' ','#','#','#','#','#',' ','#','#','#','#','#','#',' ','#',},
        {'#','#','#',' ',' ',' ',' ',' ',' ','#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#',' ','#','#',' ','#','#','#','#','#','#',' ','#','#','#','#','#',' ','#','#','#','#','#','#',' ','#',},
        {'#','#','#','#','#','#','#','#',' ','#','D',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#',' ','#','#',' ','#','#','#','#','#','#',' ','#','#','#','#','#',' ','#','#','#','#','#','#',' ','#',},
        {'#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#',' ','#','#',' ',' ',' ','P','#','#','#',' ','#','#','#','#','#',' ','#','#','#','#','#','#',' ','#',},
        {'#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ','P','#','#','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',},
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#',' ','#',},
        {'#','B',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#','#','P',' ',' ',' ',' ','#','#','#','#','#','#','P','#',},
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',}
    };
    char maze_2_Array[25][50] = {
        { '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#', },
        { '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','P','#','#','#','#','#','#','#','#','#','#','D',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#', },
        { '#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ','#','#','#','#','S','#','#','#','#',' ','#','#','#','#','S','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','P','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ','#','#','#','#',' ','#','#','#',' ',' ',' ','#','#','#',' ','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','P','#','#','#','#','#','P',' ',' ',' ','#', },
        { '#',' ','#','#','#','#',' ','#','#','#',' ','B',' ','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ','#','#','#','#',' ','#','#','#',' ',' ',' ','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#',' ',' ',' ','P','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ','#','#','#','#',' ','#','#','#','P','#','P','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ','#','#','#','#',' ','#','#','#',' ','#',' ','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ','#','#','#','#',' ','#','#','#',' ','#',' ','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ','#', },
        { '#',' ','#','#','#','#',' ','#','#','#',' ','#',' ','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#', },
        { '#','E','#','#','#','#',' ','#','#','#',' ','#',' ','#','#','#',' ','#','#','#','#',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','A','#','#','#','#','#', },
        { '#','#','#','#','#','#',' ','#','#','#',' ','#',' ','#','#','#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#', },
        { '#','#','#','#','#','#',' ','#','#','#',' ','#',' ','#','#','#',' ','#','#','#','#',' ','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#', },
        { '#','P',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','P','#','#','#','#','P','#','#','#','#','#','#','W','#','#','#','#','#','#','#','#','#','P','#','#','#','#','#','#', },
        { '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#', }
    };
    char maze_3_Array[25][50] = {
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',},
        {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',},
        {'#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#',},
        {'#',' ','#','#','#','#','#','#','#','#','#','P',' ',' ',' ',' ','#',' ','P','#',' ','#','#','#','#','#','#',' ','#','#','#','#',' ','#','P','#','#','#','#','#','#','#','#','#','#','#','P','#',' ','#',},
        {'#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#',' ',' ',' ','#','#',' ','#','#','#','#','P',' ',' ','#','#','#','#',' ','#',' ','#','#','#','#','#',' ','#','#','P','#','#',' ','#',' ','#',},
        {'#',' ','#','#','P','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#',' ','#','#','#','#',' ',' ',' ','#','P',' ',' ','#',' ','#','#',' ','#','#',' ','#',' ','#',},
        {'#',' ','#','#',' ','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ','#','#','P','#','#',' ','#','#','#','#',' ','#',' ','#','#',' ','#','#',' ','#',' ','#',},
        {'#',' ','#','#',' ','#',' ',' ',' ',' ',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#',' ','#','#','#','#',' ','#',' ','#','#',' ','#','#',' ','#',' ','#',},
        {'#',' ','#','#',' ','#',' ',' ',' ',' ',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#',' ','#','#','#','#',' ','#',' ','#','#',' ','#','#',' ','#',' ','#',},
        {'#',' ','#','#',' ',' ',' ',' ','B',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ','#',' ','#',},
        {'#',' ','#','#',' ','#',' ',' ',' ',' ',' ','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#',' ','#',' ','#',' ','#','#','#',' ','#','#','#','#','#',' ','#',' ','#',},
        {'#',' ','#','#',' ','#',' ',' ',' ',' ',' ','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#',' ','#',' ','#',' ','#','#','#',' ',' ',' ','#','#','#',' ','#',' ','#',},
        {'#',' ','#','#',' ','#','#','#','#','#','#','#','#','#','#',' ',' ',' ','#','#','#','#','#',' ','#','#','#','#','#','#','#','#',' ','#',' ','#',' ','#','#','#','#','#',' ','#','#','#',' ','#',' ','#',},
        {'#',' ','#','#',' ','#','#','#','#','#','#','#','#','#','#',' ','#',' ','#','#','#','#','#',' ','#','#','#','#','#','#','#','#',' ','#',' ','#',' ','#','#','#','#','#',' ','#','#','#',' ','#',' ','#',},
        {'#',' ','#','#',' ','#','#','#','#','#','#','#','#','#','#',' ','#',' ',' ',' ','#','#','#',' ',' ',' ',' ',' ',' ',' ','P','#',' ','#',' ','#',' ','#','#','#','#','#',' ','#','#','#',' ','#','E','#',},
        {'#',' ','#','#',' ','#','#','#','#','#','#','P',' ',' ',' ',' ','#','#','#',' ','#','#','#','#','#','#','#','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#','#','#',' ','#','#','#',' ','#','#','#',},
        {'#',' ','#','#',' ','#','#','#','#','#','#','#','#','#','#',' ','#','#','#',' ','#','#','#','#','#','#','#','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',},
        {'#',' ','#','#',' ','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','P','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ','#',' ','#',' ','#','#','#',' ',' ',' ','#','#','#','#','#',' ','#',},
        {'#',' ','#','#',' ',' ',' ','P','#','#','#','#','#','#','#',' ','#','#','#','#','#','P','#','#','#','#','#','#','#','#','#','#',' ','#',' ','#',' ',' ',' ','#',' ',' ',' ','#','#','#','#','#',' ','#',},
        {'#',' ','#','#',' ','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#',' ','#',' ','#',' ','#','#','#',' ',' ',' ','#','#','#','#','#',' ','#',},
        {'#',' ','#','#',' ','#','#','#','#','#','#','P','#','#','#',' ','#','#','#','#','#',' ',' ',' ','#','#','P',' ','#','#','#','#','P','#',' ',' ',' ','#','P','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',},
        {'#',' ','#','#',' ','#','#','#','#','#','#',' ','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#',' ','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#',},
        {'#',' ','#','#',' ','#','#','#','#','#','#',' ','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#',' ','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#',},
        {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',},
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',}
    };

    char maze_4_Array[25][50] = {
        {'#','#','#','#','#','#',' ',' ',' ','#','#',' ',' ',' ',' ',' ','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ','#','#','#','#','#','#',' ',' ',' ',' ','#','#','#',' ','#','#',},
        {'#','B','#','#','#','#',' ','#','#','#','#','#','#','#','#',' ','#','#','#','#','#',' ','#','#','#','#','#',' ','#',' ','#',' ','#',' ','#','#','#','#','#','#',' ','#','#',' ','#',' ',' ',' ',' ','#',},
        {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ','#',' ','#','#','#','#','#',' ',' ',' ','#',' ','#',' ','#','#',' ',' ',' ',' ',' ','#','#',' ','#','#',' ','#',' ','#',},
        {'#','#',' ','#','#','#','#','#','#',' ','#','#',' ','#','#','#','#','#','#',' ',' ',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ','#',' ','#','#','#',' ','#','#','#','#','#',' ','#',' ',' ','#',' ',' ',},
        {'#','#',' ','#',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ','#','#','#',' ','#',' ','#',' ','#',' ',' ',' ','#','#','#','#','#',' ','#','#','#',' ','#','#','#','#','#',' ','#',' ','#','#','#',' ',},
        {' ',' ',' ','#','#','#',' ','#','#',' ','#','#','#','#','#',' ',' ',' ',' ',' ','#',' ','#',' ','#','#','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
        {' ','#',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ','#','#','#',' ','#',' ','#','#','#','#','#','#','#',' ','#','#',' ','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#',' ','#',' ',},
        {' ','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#',' ','#',' ','#','#','#','#','#','#','#',' ','#','#',' ','#','#',' ','#','#','#','#',' ','#','#','#',' ',' ',' ',' ','#',' ',},
        {' ','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#','#',' ','#','#',' ',' ',' ',' ',' ',' ','#','#',' ','#','#','#','#','#','#',' ','#',' ',},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#',' ','#','#',' ','#','#','#',' ','#','#','#',' ',' ',' ',' ',' ',' ',' ','#','#','#','#',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',},
        {'#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#',' ','#','#','#',' ','#','#','#','#',' ','#','#','#',' ','#','#','#',' ',' ',' ','#','#',' ','#','#','#','#',' ','#',' ','#',' ',},
        {'#','#',' ',' ','#','#',' ',' ','#','#',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ','#',' ','#','#',' ','#','#','#',' ','#','#',' ',' ','#',' ','#','#',' ','#','#',' ',' ',' ','#',' ','#',' ',},
        {'#','#',' ','#','#','#','#','#','#','#',' ','#','#',' ','#','#','#','#',' ','#','#','#',' ','#',' ',' ',' ',' ','#','#','#',' ','#','#','#','#','#',' ','#','#',' ','#','#',' ','#','#','#',' ','#',' ',},
        {'#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ','#','#','#','#',' ','#','#','#',' ','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ','#','#','#',' ','#',' ',},
        {'#','#','#',' ','#','#','#','#','#',' ','#','#','#',' ',' ',' ',' ',' ',' ','#','#','#',' ','#','#','#','#',' ','#',' ','#','#','#','#','#','#','#',' ','#','#',' ','#','#',' ','#','#','#',' ','#',' ',},
        {'#','#','#',' ',' ',' ',' ','#','#',' ','#','#','#','#',' ','#','#',' ','#','#','#','#',' ','#','#','#','#',' ','#',' ','#',' ',' ',' ','#','#','#',' ','#','#',' ','#','#',' ','#','#','#',' ','#',' ',},
        {' ',' ',' ',' ','#','#',' ','#','#',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ',' ',' ','#',' ','#','#',' ','#','#',' ','#','#','#',' ','#',' ',},
        {'#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#',' ',' ',' ',' ','#',' ','#','#','#','#','#',' ',' ',' ','#','#','#',' ','#',' ','#',' ','#',' ','#','#',' ','#','#',' ','#','#','#',' ',' ',' ',},
        {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#',' ','#','#',' ','#',' ','#','#','#',' ','#','#','#','#','#',' ','#',' ','#',' ','#',' ',' ',' ',' ','#','#',' ','#','#',' ',' ','#','#',},
        {'#',' ','#','#','#','#','#','#',' ','#','#',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ','#','#','#',' ',' ',' ',' ',' ',' ',' ','#',' ','#',' ','#','#','#','#',' ','#','#',' ','#','#',' ','#','#','#',},
        {'#',' ','#','#','#','#','#','#',' ','#','#','#','#',' ','#',' ','#','#','#',' ','#','#','#','#','#',' ','#','#',' ','#','#','#','#',' ','#',' ','#','#','#','#',' ','#','#',' ','#',' ',' ','#','#','#',},
        {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ','#','#','#',' ','#','#',' ',' ',' ',' ','#','#',' ','#','#','#','#',' ','#',' ',' ',' ','#','#',' ','#','#',' ','#','#',' ',' ',' ','#',},
        {'#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#',' ','#',' ',' ',' ',' ','#','#','#',' ','#','#',' ','#','#',' ','#','#',' ','#',' ','#',},
        {'#','#',' ','#',' ','#',' ',' ',' ','#','#','#','#','#','#','#',' ','#','#',' ','#',' ','#','#','#','#',' ',' ',' ',' ',' ','#','#',' ','#','#','#',' ','#','#',' ','#','#',' ',' ',' ',' ','#','E','#',},
        {' ',' ',' ',' ',' ','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ','#','#','#',' ','#','#','#','#','#','#',' ',' ','#',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#',},
    };

    char maze_5_Array[25][50] = {
        {'#','#','#','#','#','#',' ',' ','P','#','#','P',' ',' ',' ',' ','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ','#','P','#',' ',' ',' ','#','#','#','#','#','#',' ',' ',' ',' ','#','#','#',' ','#','#',},
        {'#','B','#','#','#','#',' ','#','#','#','#','#','#','#','#',' ','#','#','#','#','#',' ','#','#','#','#','#',' ','#',' ','#',' ','#',' ','#','#','#','#','#','#',' ','#','#',' ','#','P',' ',' ',' ','#',},
        {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ','#',' ','#','#','#','#','#',' ','#',' ','#',' ','#',' ','#','#',' ',' ',' ',' ',' ','#','#',' ','#','#',' ','#',' ','#',},
        {'#','#',' ','#','#','#','#','#','#',' ','#','#',' ','#','#','#','#','#','#',' ',' ',' ',' ',' ','#','P','#',' ','#',' ',' ',' ','#',' ','#','#','#',' ','#','#','#','#','#',' ','#',' ',' ','#',' ',' ',},
        {'#','#',' ','#','P',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ','#','#','#',' ','#',' ','#',' ','#',' ',' ',' ','#','#','#','#','#',' ','#','#','#',' ','#','#','#','#','#',' ','#',' ','#','#','#',' ',},
        {' ',' ',' ','#','#','#',' ','#','#',' ','#','#','#','#','#',' ',' ',' ',' ',' ','#',' ','#','P','#','#','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
        {' ','#',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ','#','#','#',' ','#',' ','#','#','#','#','#','#','#',' ','#','#',' ','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#',' ','#',' ',},
        {' ','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#',' ','#',' ','#','#','#','#','#','#','#',' ','#','#',' ','#','#',' ','#','#','#','#',' ','#','#','#','P',' ',' ',' ','#',' ',},
        {' ','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#','#',' ','#','#',' ',' ',' ',' ',' ',' ','#','#',' ','#','#','#','#','#','#',' ','#',' ',},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#',' ','#','#',' ','#','#','#',' ','#','#','#',' ',' ',' ',' ',' ',' ',' ','#','#','#','#',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',},
        {'#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#',' ','#','#','#',' ','#','#','#','#',' ','#','#','#',' ','#','#','#',' ',' ',' ','#','#',' ','#','#','#','#',' ','#',' ','#',' ',},
        {'#','#',' ',' ','#','#',' ',' ','#','#',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ','#','P','#','#',' ','#','#','#',' ','#','#','P',' ','#',' ','#','#',' ','#','#',' ',' ',' ','#',' ','#',' ',},
        {'#','#',' ','#','#','#','#','#','#','#',' ','#','#',' ','#','#','#','#',' ','#','#','#',' ','#',' ',' ',' ',' ','#','#','#',' ','#','#','#','#','#',' ','#','#',' ','#','#',' ','#','#','#',' ','#',' ',},
        {'#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ','#','#','#','#',' ','#','#','#',' ','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ','#','#','#',' ','#',' ',},
        {'#','#','#',' ','#','#','#','#','#',' ','#','#','#',' ',' ',' ',' ',' ',' ','#','#','#',' ','#','#','#','#',' ','#',' ','#','#','#','#','#','#','#',' ','#','#',' ','#','#',' ','#','#','#',' ','#',' ',},
        {'#','#','#',' ',' ',' ',' ','#','#',' ','#','#','#','#',' ','#','#',' ','#','#','#','#',' ','#','#','#','#',' ','#',' ','#',' ',' ',' ','#','#','#',' ','#','#',' ','#','#',' ','#','#','#',' ','#',' ',},
        {' ',' ',' ',' ','#','#',' ','#','#',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ',' ',' ','#',' ','#','#',' ','#','#',' ',' ','P','#',' ','#',' ',},
        {'#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#',' ',' ',' ',' ','#',' ','#','#','#','#','#',' ',' ',' ','#','#','#',' ','#',' ','#',' ','#',' ','#','#',' ','#','#',' ','#','#','#',' ',' ',' ',},
        {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#',' ','#','#',' ','#','P','#','#','#',' ','#','#','#','#','#',' ','#',' ','#',' ','#',' ',' ',' ',' ','#','#',' ','#','#',' ',' ','#','#',},
        {'#',' ','#','#','#','#','#','#',' ','#','#',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ','#','#','#',' ',' ',' ',' ',' ',' ',' ','#',' ','#',' ','#','#','#','#',' ','#','#',' ','#','#',' ','#','#','#',},
        {'#',' ','#','#','#','#','#','#',' ','#','#','#','#',' ','#',' ','#','#','#',' ','#','#','#','#','#',' ','#','#',' ','#','#','#','#',' ','#',' ','#','#','#','#',' ','#','#',' ','#',' ',' ','#','#','#',},
        {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ','#','#','#',' ','#','#',' ',' ',' ',' ','#','#',' ','#','#','#','#',' ','#',' ',' ',' ','#','#',' ','#','#',' ','#','#',' ',' ',' ','#',},
        {'#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#',' ','#',' ',' ',' ',' ','#','#','#',' ','#','#',' ','#','#',' ','#','#',' ','#',' ','#',},
        {'#','#',' ','#','P','#',' ',' ',' ','#','#','#','#','#','#','#',' ','#','#',' ','#',' ','#','#','#','#',' ',' ',' ',' ',' ','#','#',' ','#','#','#',' ','#','#',' ','#','#',' ',' ',' ',' ','#','E','#',},
        {'P',' ',' ',' ',' ','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','P',' ','#',' ','P','#','#','#','P','#','#','#','#','#','#',' ',' ','#','P',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#',},
    };
    for (int i = 0; i < 6; i++) {
        int currentCollectibles = 0;
        currentMap[i] = new map;
        switch (i) {
        case 0:
            currentMap[i]->setTotalCollectibles(8);
            for (int x = 0; x < 50; x++) {
                for (int y = 0; y < 25; y++) {
                    currentMap[i]->updateMap(x, y, maze_1_Array[y][x]);
                }
            }
            break;
        case 1:
            currentMap[i]->setTotalCollectibles(8);
            for (int x = 0; x < 50; x++) {
                for (int y = 0; y < 25; y++) {
                    currentMap[i]->updateMap(x, y, maze_2_Array[y][x]);
                }
            }
            break;
        case 2:
            currentMap[i]->setTotalCollectibles(10);
            for (int x = 0; x < 50; x++) {
                for (int y = 0; y < 25; y++) {
                    currentMap[i]->updateMap(x, y, maze_3_Array[y][x]);
                }
            }
            break;
        case 3:
            currentMap[i]->setTotalCollectibles(0);
            for (int x = 0; x < 50; x++) {
                ;
                for (int y = 0; y < 25; y++) {
                    currentMap[i]->updateMap(x, y, maze_4_Array[y][x]);
                }
            }
            break;
        case 4:
            currentMap[i]->setTotalCollectibles(12);
            for (int x = 0; x < 50; x++) {
                for (int y = 0; y < 25; y++) {
                    currentMap[i]->updateMap(x, y, maze_5_Array[y][x]);
                }
            }
            break;
        }
        while (currentCollectibles < currentMap[i]->getTotalCollectibles()) {
            for (int x = 0; x < 50; x++) {
                for (int y = 0; y < 25; y++) {
                    if (currentMap[i]->getMapVar(x, y) == 'P') {
                        if (rand() % 10 == 1) {
                            currentMap[i]->updateMap(x, y, 'C');
                            x = 50;
                            y = 25;
                            currentCollectibles += 1;
                        }
                    }
                }
            }
        }
    }
}

void initializeEnemy() {
    int enemyNumber = 0;
    char enemyDir;
    for (int i = 0; i < 6; i++) {
        enemyNumber = 0;
        for (int x = 0; x < 50; x++) {
            for (int y = 0; y < 25; y++) {
                switch (currentMap[i]->getMapVar(x, y)) {
                case 'W': case 'A': case 'S': case 'D':
                    enemyDir = currentMap[i]->getMapVar(x, y);
                    switch (i) {
                    case 0:
                        enemyPtr[i][enemyNumber] = new Enemy_Fire(enemyDir);
                        enemyPtr[i][enemyNumber]->setposX(x);
                        enemyPtr[i][enemyNumber]->setposY(y);
                        enemyPtr[i][enemyNumber]->changeSpeed(90);
                        break;
                    case 1:
                        int change_x = 0;
                        int change_y = 0;
                        switch (enemyDir) {
                        case 'W': 
                            change_y = -1;
                            break;
                        case 'A': 
                            change_x = -1;
                            break;
                        case 'S': 
                            change_y = 1;
                            break;
                        case 'D':
                            change_x = 1;
                            break;
                        }
                        enemyPtr[i][enemyNumber] = new BatBullet(enemyDir, (x+change_x),(y+change_y));
                        currentMap[i]->updateMap(x, y, 'b');
                        enemyPtr[i][enemyNumber]->setposX(x + change_x);
                        enemyPtr[i][enemyNumber]->setposY(y + change_y);
                        enemyPtr[i][enemyNumber]->changeSpeed(45);
                    }
                    enemyNumber++;
                }
            }
        }
    }
}
int moveTimer = 0;
void moveEnemy() {
    int moveSpeed = 0;
    switch (cMap) {
    case 0:
        moveSpeed = 90;
    case 1:
        moveSpeed = 18;
    }
    int new_x = 0;
    int new_y = 0;
    moveTimer += 1;
    if (moveTimer == moveSpeed) {
        for (int i = 0; i < 5; i++) {
            new_x = enemyPtr[cMap][i]->getposX();
            new_y = enemyPtr[cMap][i]->getposY();
            enemyPtr[cMap][i]->move(*currentMap[cMap]);
        }
        moveTimer = 0;
    }
}

void resetGame() {
    cMap = 0;
    changeMap();
}
char letter[3] = { 65, 65, 65 };
int letterNum[3] = { 65, 65, 65 };
int arrowPos = 0;
std::string s = "";
std::string n = "";
std::string b = "";

bool Save = false;

void renderEndscreen() {
    COORD c;
    c.X = 40;
    c.Y = 12;

    for (int i = 0; i < 3; i++) {
       
        
        s = letter[arrowPos];
        
        if (i == arrowPos) {
            c.Y += 1;
            g_Console.writeToBuffer(c, '^');
            c.Y -= 1;
        }
        
        g_Console.writeToBuffer(c, letter[i]);
        
       c.X += 1; 

      
        
        
    }
    
    s = letter[0];
    n = letter[1];
    b = letter[2];
    
   
    
    
    
    s.append(n);
    s.append(b);
    
    
    /*return s;*/
}

void endInput() {
    
    if (g_skKeyEvent[K_UP].keyReleased)
    {
        if (letterNum[arrowPos] > 65) {
            letterNum[arrowPos]--;
            letter[arrowPos] = letterNum[arrowPos];
        } 
    }
    if (g_skKeyEvent[K_LEFT].keyReleased)
    {
        if (arrowPos > 0) {
            arrowPos -= 1;
        }
    }
    if (g_skKeyEvent[K_DOWN].keyReleased)
    {
        if (letterNum[arrowPos] < 90) {
            letterNum[arrowPos]++;
            letter[arrowPos] = letterNum[arrowPos];
        }
    }
    if (g_skKeyEvent[K_RIGHT].keyReleased)
    {
        if (arrowPos < 2) {
            arrowPos += 1;
        }
    }
    std::ifstream Name("Name_Check.txt");
    //incase for some odd reason the txt file cant be opened
    if (!Name.is_open())
    {
        std::cout << "Unable to read file\n";
        return;
    }

    string Letters;
    Name >> Letters;
    Name.close();

    std::ofstream NameOut("Name_Check.txt");
    // if the totalscore is higher than the highest_score integer stored inside the text file it will delete the old highest_Score and update the totalscore in.
    // if the totalscore is lower than the highest_Score integer stored, then it will not update the data stored in it.
    if (g_skKeyEvent[K_SPACE].keyReleased)
    {
        NameOut << s;
    }
    else
    {
        NameOut << Letters;
    }
       

    NameOut.close();
    
}