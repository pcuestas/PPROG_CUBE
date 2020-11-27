#ifndef MENU_H
#define MENU_H

/**
 * @brief Manages the main menu and the NewGameMenu at the same time.
 * @return 3 if 3x3 cube is selected, 2 in the case of the 2x2 cube and 0 to exit the game 
 * @param use_saved_game stores after the call to this function TRUE or FALSE
 */
int MenusDisplay(int *use_saved_game);

/**
 *@brief Deals with the main menu, reading the keyboard for moving the cursor and selecting an option
 *
 * 
 */
int ShowMainMenu();

/**
 * @brief Reads the keyboard for moving the key in the menu. Needs configuration of the terminal
 * @return 1 for DOWN_KEY, -1 if UP_KEY, 0 for ENTER
 */
int read_keyMenu();


int ShowNewGameMenu();


/*NOT USED ANY MORE*/
/**
  @brief Prints the main menu with the cursor in the right position
  @param pos place to print the cursor 

 */
void print_menu(int pos);

#endif