// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include "map.h"
#include "playerVL.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

int cMap = 0;

map* currentMap[6];

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
bool roundActive = false;

COORD spawnpoint;

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
    changeMap();
    

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
        case S_MENU: mainMenu();
            break;
        case S_GAME1: updateGame(); // gameplay logic when we are in the game
            break;
        case S_LVLCOMP: renderLevelCompleted();
            break;
        case S_TRANS: renderTransition();
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
        g_sChar.m_bActive = !g_sChar.m_bActive;
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
    }
    if (checkCollision(new_x, new_y) == 3) {
        cMap += 1;
        g_eGameState = S_LVLCOMP;
        if (collected == currentMap[cMap]->getTotalCollectibles()) {
            
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
    if (g_skKeyEvent[K_ESCAPE].keyReleased)
        g_eGameState = S_MENU;
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
    case S_MENU: mainMenu();
        break;
    case S_GAME1: renderGame();
        break;
    case S_LVLCOMP: renderLevelCompleted();
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
            if (c.X <= g_sChar.m_cLocation.X + 7 && c.X >= g_sChar.m_cLocation.X - 7) {
                if (c.Y <= g_sChar.m_cLocation.Y + 4 && c.Y >= g_sChar.m_cLocation.Y - 4) {
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
                }
            }
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
    int scoren = collected * 2;
    totalscore += scoren;
    char round[18] = { "Level   Completed" };
    char score[9] = { "Score:  " };
    char total[15] = { "Total Score:  " };
    round[7] = (cMap - 1);
    score[8] = (char)scoren;
    total[14] = (char)totalscore;
    if (cMap == 1) {
        g_Console.writeToBuffer(c, "Tutorial Level Completed", 0xF6);
    }
    else {
        g_Console.writeToBuffer(c, round, 0xF6);
    }
    c.Y += 2;
    g_Console.writeToBuffer(c, score, 0xF6);
    c.Y += 2;
    g_Console.writeToBuffer(c, total, 0xF6);
    c.Y += 2;
    g_Console.writeToBuffer(c, "Press <SPACE> to Continue");
    if (g_skKeyEvent[K_SPACE].keyDown) {
        g_eGameState = S_GAME1;
    }
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
    ss << "Collected " << collected << ": " << NotCollected;
    c.X = 0;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());

    ss.str("");
    ss << "<Esc> to menu";
    c.X = 0;
    c.Y = 2;
    g_Console.writeToBuffer(c, ss.str());
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
    return collideType;
}

void changeMap() {
    collected = 0;
    NotCollected = currentMap[cMap]->getTotalCollectibles();
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 25; j++) {
            if (currentMap[cMap]->getMapVar(i, j) == 'S') {
                g_sChar.m_cLocation.X = 15 + i;
                g_sChar.m_cLocation.Y = j;
            }
        }
    }
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 25; j++) {
            if (currentMap[cMap]->getMapVar(i, j) == 'V') {
                g_sChar.m_cLocation.X = 15 + i;
                g_sChar.m_cLocation.Y = j;
            }
        }
    }
}

void mainMenu()
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

    //Keyboard Event

    //if (g_skKeyEvent[K_1].keyReleased)
    //    g_eGameState = S_GAME1;

    //else if (g_skKeyEvent[K_3].keyReleased)
    //    g_bQuitGame = true;

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
    }
}

void initializeMaps() {
    char maze_1_Array[25][50] = {
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',},
        {'#','#','#','#','#','#','#','#','#','#','#','#','E','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','H',' ',' ','P','#','#','#','#','#',},
        {'#','P','#','#','H',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#',},
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
        {'#',' ','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','P','#','#','#','#','V',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#',' ','#','#','#','#','#','#',' ','#',},
        {'#',' ',' ',' ','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#',' ','#','#','#','#','#',' ','#','#','#','#','#','#',' ','#',},
        {'#','#','#',' ','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#',' ','#','#','#','#','#',' ','#','#','#','#','#','#',' ','#',},
        {'#','#','#',' ','#',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#',' ','#','#','V',' ',' ',' ',' ',' ','#','#','#','#','#','#',' ','#','#','#','#','#',' ','#','#','#','#','#','#',' ','#',},
        {'#','#','#',' ','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#',' ','#','#',' ','#','#','#','#','#','#',' ','#','#','#','#','#',' ','#','#','#','#','#','#',' ','#',},
        {'#','#','#',' ',' ',' ',' ',' ',' ','#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#',' ','#','#',' ','#','#','#','#','#','#',' ','#','#','#','#','#',' ','#','#','#','#','#','#',' ','#',},
        {'#','#','#','#','#','#','#','#',' ','#','V',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#',' ','#','#',' ','#','#','#','#','#','#',' ','#','#','#','#','#',' ','#','#','#','#','#','#',' ','#',},
        {'#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#',' ','#','#',' ',' ',' ','P','#','#','#',' ','#','#','#','#','#',' ','#','#','#','#','#','#',' ','#',},
        {'#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ','P','#','#','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',},
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#',' ','#',},
        {'#','S',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#','#','P',' ',' ',' ',' ','#','#','#','#','#','#','P','#',},
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',}
    };
    char maze_2_Array[25][50] = {
        { '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#', },
        { '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','P','#','#','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#', },
        { '#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','P','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ','#','#','#','#',' ','#','#','#',' ',' ',' ','#','#','#',' ','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','P','#','#','#','#','#','P',' ',' ',' ','#', },
        { '#',' ','#','#','#','#',' ','#','#','#',' ','S',' ','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ','#','#','#','#',' ','#','#','#',' ',' ',' ','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#',' ',' ',' ','P','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ','#','#','#','#',' ','#','#','#','P','#','P','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ','#','#','#','#',' ','#','#','#',' ','#',' ','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#', },
        { '#',' ','#','#','#','#',' ','#','#','#',' ','#',' ','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ','#', },
        { '#',' ','#','#','#','#',' ','#','#','#',' ','#',' ','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#', },
        { '#','E','#','#','#','#',' ','#','#','#',' ','#',' ','#','#','#',' ','#','#','#','#',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#', },
        { '#','#','#','#','#','#',' ','#','#','#',' ','#',' ','#','#','#',' ','#','#','#','#',' ','#','#','#','#',' ','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#', },
        { '#','#','#','#','#','#',' ','#','#','#',' ','#',' ','#','#','#',' ','#','#','#','#',' ','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#', },
        { '#','P',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','P','#','#','#','#','P','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','P','#','#','#','#','#','#', },
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
        {'#',' ','#','#',' ',' ',' ',' ','S',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ','#',' ','#',},
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
        {'#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#',' ','#','#','#','#','#',' ','#','#','#','#','#',' ','#',' ','#',' ','#',' ','#','#','#','#','#','#',' ','#','#',' ','#',' ',' ',' ',' ','#',},
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
        {'#','#',' ','#',' ','#',' ',' ',' ','#','#','#','#','#','#','#',' ','#','#',' ','#',' ','#','#','#','#',' ',' ',' ',' ',' ','#','#',' ','#','#','#',' ','#','#',' ','#','#',' ',' ',' ',' ','#',' ','#',},
        {' ',' ',' ',' ',' ','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ','#','#','#',' ','#','#','#','#','#','#',' ',' ','#',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#',},
    };

    char maze_5_Array[25][50] = { 
        {'#','#','#','#','#','#',' ',' ',' ','#','#',' ',' ',' ',' ',' ','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ','#','#','#','#','#','#',' ',' ',' ',' ','#','#','#',' ','#','#',},
        {'#',' ','#','#','#','#',' ','#','#','#','#','#','#','#','#',' ','#','#','#','#','#',' ','#','#','#','#','#',' ','#',' ','#',' ','#',' ','#','#','#','#','#','#',' ','#','#',' ','#',' ',' ',' ',' ','#',},
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
        {'#','#',' ','#',' ','#',' ',' ',' ','#','#','#','#','#','#','#',' ','#','#',' ','#',' ','#','#','#','#',' ',' ',' ',' ',' ','#','#',' ','#','#','#',' ','#','#',' ','#','#',' ',' ',' ',' ','#',' ','#',},
        {' ',' ',' ',' ',' ','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ','#','#','#',' ','#','#','#','#','#','#',' ',' ','#',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#',},
    };
    for (int i = 0; i < 6; i++) {
        currentMap[i] = new map;
        switch (i) {
        case 0:
            for (int x = 0; x < 50; x++) {
                for (int y = 0; y < 25; y++) {
                    currentMap[i]->updateMap(x, y, maze_1_Array[y][x]);
                }
            }
            break;
        case 1:

            for (int x = 0; x < 50; x++) {
                for (int y = 0; y < 25; y++) {
                    currentMap[i]->updateMap(x, y, maze_2_Array[y][x]);
                }
            }
            break;
        case 2:

            for (int x = 0; x < 50; x++) {
                for (int y = 0; y < 25; y++) {
                    currentMap[i]->updateMap(x, y, maze_3_Array[y][x]);
                }
            }
            break;
        case 3:

            for (int x = 0; x < 50; x++) {
                for (int y = 0; y < 25; y++) {
                    currentMap[i]->updateMap(x, y, maze_4_Array[y][x]);
                }
            }
            break;
        case 4:

            for (int x = 0; x < 50; x++) {
                for (int y = 0; y < 25; y++) {
                    currentMap[i]->updateMap(x, y, maze_5_Array[y][x]);
                }
            }
            break;
        }
    }
}