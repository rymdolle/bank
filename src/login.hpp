#ifndef LOGIN_H
#define LOGIN_H

#include <iostream>
#include <vector>
#include <filesystem>

#ifdef _WIN32
#include <conio.h>
#elif __linux__ || __APPLE__
#include <termios.h>
#include <unistd.h>
#define _getch()  getchar()
#define _putch(c) putchar(c)
#endif

#include "user.hpp"
#include "account.hpp"

std::string read_username()
{
  std::string text;
  std::getline(std::cin, text);
  return text;
}

std::string read_password()
{
  std::string password;

#ifdef __linux__ || __APPLE__

  // On linux systems we have to unset the echo and canonical flags in
  // the terminal to not echo back what is written and to read one
  // char instead of reading until enter is pressed.

  struct termios term, old;
  // Get old flags
  tcgetattr(STDIN_FILENO, &old);
  term = old;

  // Unset echo and canonical mode
  term.c_lflag &= ~ECHO;
  term.c_lflag &= ~ICANON;

  // Read one char with blocking read
  term.c_cc[VMIN] = 1;
  term.c_cc[VTIME] = 0;
  tcsetattr(STDIN_FILENO, TCSANOW, &term);
#endif

  // Read password from stdin
  for (;;) {
    char letter = _getch();
    if (letter == '\r' || letter == '\n') break;
    if (letter == 0x7f || letter == '\b') {
      // Backspace, remove last letter from password
      if (!password.empty()) {
        password.pop_back();
        // Remove char from screen
        _putch('\b');
        _putch(' ');
        _putch('\b');
      }
    } else {
      // Mask with asterisk
      _putch('*');
      password.push_back(letter);
    }
  }

#ifdef __linux__ || __APPLE__

  // Restore flags to original state
  tcsetattr(STDIN_FILENO, TCSANOW, &old);
#endif

  return password;
}

bool login(User &currentUser)
{
  int count = 0;
  do {
    std::cout << "Enter username:";
    std::string username = read_username();
    std::cout << "Enter pin code:";
    std::string password = read_password();

    for (User &user : User::loadFromFile("data/users.txt")) {
      if (user.verify(username, password)) {
        std::cout << "\nLogin successful.\n"
                  << "Welcome " << username << "!\n\n";
        currentUser = user;
        return true;
      }
    }

    ++count;
    std::cout << "\nUsername or pin code is incorrect (" << count << "/3).\n";
  } while (count < 3);
  return false;
}

#endif /* LOGIN_H */
