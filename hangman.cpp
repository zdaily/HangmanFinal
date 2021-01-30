 //Ziah Daily                                                                                                                                                                                                
//hangman.cpp                                                                                                                                                                                               
//Implementation of hangman.h                                                                                                                                                                               

#include "hangman.h"

Hangman::Hangman()
{
  //set up hangman to display only noose                                                                                                                                                                    
  body[0].firstLine = "    ----\n";
  body[1].firstLine = "    |  |\n";
  body[2].firstLine = "       |\n";
  body[2].secondLine = "    O  |\n";
  body[3].firstLine = "       |\n";
  body[3].secondLine = "    |  |\n";
  body[4].firstLine = "       |\n";
  body[4].secondLine = "   -|  |\n";
  body[4].thirdLine = "   -|- |\n";
  body[5].firstLine = "       |\n";
  body[5].secondLine = "    |  |\n";
  body[6].firstLine = "       |\n";
  body[6].secondLine = "   /   |\n";
  body[6].thirdLine = "   / \\ |\n";
  body[7].firstLine = "       |\n";
  body[8].firstLine = "_______|___\n";

  for (int i = 0; i <BODY_SIZE; i++){
    body[i].displaySecond = false;
    body[i].displayThird = false;
  }

  //set up alpha list                                                                                                                                                                                       
  char letter = BEGIN;
  for (int i = 0; i < ALPHA_SIZE; i++){
    alphabet[i].letter = letter;
    letter++;
    alphabet[i].used = false;
  }

  currentWord = -1;
  totalWords = 0;
  wins = 0;
  losses = 0;
  correctChars = 0;
  badGuesses = 0;


  srand(time(0));
}

bool Hangman:: intitializeFile(string filename)
{
  ifstream inFile;

  inFile.open(filename);

  if (inFile.fail())
    return false;

  while (inFile >> list[totalWords].word){
    list[totalWords].used = false;
    totalWords++;
  }

  inFile.close();
  return true;
}

bool Hangman::newWord()
{
  bool done = false;
  int newIndex = 0;

  if (wins + losses == totalWords)
    return false;

  while (!done){
    newIndex = rand() % totalWords;
    if (!list[newIndex].used){
      currentWord = newIndex;
      list[newIndex].used = true;
      done = true;
    }
  }
//reset character count                                                                                                                                                                                   
  correctChars = 0;
  badGuesses = 0;

  return true;
}

void Hangman::displayGame()
{
  displayBody();
  cout << endl << endl;
  displayWord();
  cout << endl << endl;
  displayAlpha();
  cout << endl << endl;
}

bool Hangman::guess (char letter, bool& done, bool& won)
{
  int letterIndex = letter - BEGIN;
  unsigned countCorrect = 0;

  if(!isalpha(letter))
    return false;

  letter = toupper(letter);

  if (alphabet[letterIndex].used)
    return false;

  alphabet[letterIndex].used = true;

  for (unsigned i = 0; i < list[currentWord].word.length(); i++)
    if (list[currentWord].word.at(i) == letter)
      countCorrect++;

  if (countCorrect == 0)
    badGuesses++;
  else
    correctChars += countCorrect;

  if (correctChars == list[currentWord].word.length()){
    done = true;
    won = true;
    wins++;
  }

  if (badGuesses == MAX_BAD_GUESSES){
    done = true;
    losses++;

  }

//if charachter is not in word, print next body part                                                                                                                                                      
  switch (badGuesses){
  case HEAD:
    body[2].displaySecond = true;
    break;
  case NECK:
    body[3].displaySecond = true;
    break;
  case LT_ARM:
    body[4].displaySecond = true;
    break;
  case RT_ARM:
    body[4].displayThird = true;
    break;
  case TORSO:
    body[5].displaySecond = true;
    break;
  case LT_LEG:
    body[6].displaySecond = true;
    break;
  case RT_LEG:
    body[6].displaySecond = true;

  }
  return true;
}

void Hangman::displayStatistics()
{
  int numRemaining = 0;

  for (int i = 0; i < totalWords; i++)
    if (!list[i].used)
      numRemaining++;

  cout << "Total words: " << totalWords << endl;
  cout << "Words still available: " << numRemaining << endl;
  cout << "Wins: " << wins << endl;
  cout << "Losses: " << losses << endl;
}

void Hangman::displayBody()
{
  int blanks = (SCREEN_WIDTH - body[8].firstLine.length())/2;

  for (int i = 0; i < BODY_SIZE; i++){
    for (int b = 0; b < blanks; b++)
      cout << SPACE;
    if (body[i].displayThird)
      cout << body[i].thirdLine;
    else if (body[i].displaySecond)
      cout << body[i].secondLine;
    else
      cout << body[i].firstLine;
  }
}
void Hangman:: displayWord()
{
  int blanks = (SCREEN_WIDTH - (list[currentWord].word.length() * 2))/2;

  for (int i = 0; i < blanks; i++)
    cout << SPACE;

  for (unsigned i = 0; i < list[currentWord].word.length(); i++){
    if (alphabet[list[currentWord].word.at(i) - BEGIN].used)
      cout << list[currentWord].word.at(i) << SPACE;
    else
      cout << UNDERSCORE << SPACE;
  }
}

void Hangman::revealWord()
{
  int blanks = (SCREEN_WIDTH - (list[currentWord].word.length() * 2))/2;

  for (int i = 0; i < blanks; i++)
    cout << SPACE;

  for (unsigned i = 0; i < list[currentWord].word.length(); i++)
    cout << list[currentWord].word.at(i) << SPACE;

  cout << endl;

}
void Hangman::displayAlpha()
{
  int blanks = (SCREEN_WIDTH - (ALPHA_SIZE*2-1))/2;

  for (int i = 0; i < blanks; i++)
    cout << SPACE;

  for (int i = 0; i < ALPHA_SIZE; i++){
    if (!alphabet[i].used){
      cout << alphabet[i].letter << SPACE;
    }else
      cout << SPACE << SPACE;
  }
}

bool Hangman:: initializeFile(string filename)
{
  ifstream inFile;

  inFile.open(filename);

  if (inFile >> list[totalWords].word){
    list[totalWords].used = false;
    totalWords++;
  }

  inFile.close();
  return true;

}
