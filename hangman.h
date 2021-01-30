//Ziah Daily                                                                                                                                                                                                
// hangman.h                                                                                                                                                                                                
//Purpose : Allows user to play a game of hangman with single words                                                                                                                                         
// and all uppercase letters. There is a maximum 0f 100 words per game.                                                                                                                                     


#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <cctype>

using namespace std;

#ifndef HANGMAN_H
#define HANGMAN_H

class Hangman
{
 public:
  Hangman();

  bool initializeFile(string filename);
  //intializes the list of words from the file                                                                                                                                                              
  //returns false if the file is bad                                                                                                                                                                        


  bool newWord();
  //chooses new word for game, returns false if no words available                                                                                                                                          

  void displayGame();
  // displays the game board including the word space, the hangman                                                                                                                                          
  // and the available letters                                                                                                                                                                              

  bool guess (char letter, bool& done, bool& won);
  // processes the user's guess, returning false if letter not available                                                                                                                                    
  // post: done returns true if no more guesses are available (or if word                                                                                                                                   
  //is guessed correctly); won returns true if word has been guessed                                                                                                                                        
  //correctly                                                                                                                                                                                               

  void displayStatistcs();
  //display wins; losses and how many words remain for this game                                                                                                                                            

  void revealWord();
  //reveals word for the round                                                                                                                                                                              

private:
  static const int LIST_SIZE = 100;
  static const int BODY_SIZE = 9;
  static const int ALPHA_SIZE = 26;
  static const char UNDERSCORE = '_';
  static const char SPACE = ' ';
  static const char BEGIN = 'A';
  static const int SCREEN_WIDTH = 80;
  static const int MAX_BAD_GUESSES = 7;
  static const int HEAD = 1;
  static const int NECK = 2;
  static const int LT_ARM = 3;
  static const int RT_ARM = 4;
  static const int TORSO = 5;
  static const int LT_LEG = 6;
  static const int RT_LEG = 7;


  struct BodyPart{
    string firstLine;
    string secondLine;
    string thirdLine;
    bool displaySecond;
    bool displayThird;
  };

  struct WordList{
    string word;
    bool used;
  };

  struct AlphaList{
    char letter;
    bool used;
  };
WordList list[LIST_SIZE];
  BodyPart body[BODY_SIZE];
  AlphaList alphabet[ALPHA_SIZE];
  int currentWord;          //index of current words                                                                                                                                                        
  int totalWords;           //number of words in file                                                                                                                                                       
  int wins;                 //number of words guessed                                                                                                                                                       
  int losses;               //number of words played, not guesses                                                                                                                                           
  unsigned correctChars;    //numbernumber of chars guessed correctly in word                                                                                                                               
  unsigned badGuesses;      //number of bad guesses                                                                                                                                                         


  void displayBody();
  //display body in its current state                                                                                                                                                                       

  void displayWord();
  //displays word with blanks and guessed letters                                                                                                                                                           

  void displayAlpha();
  //displays the available letters                                                                                                                                                                          
};


#endif // HANGMAN_H                                                                                                                                                                                         




