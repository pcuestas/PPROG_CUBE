#ifndef MENU_H
#define MENU_H

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


/*NOT USED ANY MORE*/
/**
  @brief Prints the main menu with the cursor in the right position
  @param pos place to print the cursor 

 */
void print_menu(int pos);

#endif