#include <iostream>
//I cant remember if this was in the repo but i wanted it anyways
#include <fstream>
using namespace std;
#include <string> 

bool writeToFile;

//writes the result to a file that the user can reference later
void writeResultsToFile(string name, string something){
  ofstream colorFile;
  colorFile.open("colorComparison_" + name + ".txt");
  colorFile << name << ": " << something << "\n";
  colorFile.close();
}

//gives a generalized rating for the colorblind friendliness of the color.
string colorBlindnessRating(int val){
  //compare the colors
  if(val < 80){//this color is visually easy to confuse
    return "Too close to use!";
  } else if(val < 140){//these colors are close but you can use them if its your only option
    return "A little too similar...";
  } else  if(val < 200){//these colors are still close, but they arent indistinguishable
    return "Decently seperated. ";
  } else {//the color is clearly seperated in the colorblind's context
    return "Colorblind friendly";
  }
}

//takes two hex codes, turns them into RGB for math purposes, does math
int getDiff(string colorOne, string colorTwo, char blindnessType, string name = "color"){
  //get the RGB values for the first color
  //i looked up how to turn string based hex values into ints
  int valueOneRed = std::stoi(colorOne.substr(0, 2), nullptr, 16);
  int valueOneGreen = std::stoi(colorOne.substr(2, 2), nullptr, 16);
  int valueOneBlue = std::stoi(colorOne.substr(4, 2), nullptr, 16);

  //get RGB for the second color
  int valueTwoRed = std::stoi(colorTwo.substr(0, 2), nullptr, 16);
  int valueTwoGreen = std::stoi(colorTwo.substr(2, 2), nullptr, 16);
  int valueTwoBlue = std::stoi(colorTwo.substr(4, 2), nullptr, 16);

  switch(blindnessType){
    //if the user doesnt specify they get protanopia
    default:
    case('p'):
      //protanopia halves the red value
      valueOneRed = valueOneRed / 2;
      valueTwoRed = valueTwoRed / 2;

      //protanopia merges reds and greens
      valueOneRed = (valueOneRed + valueOneGreen) / 2;
      valueTwoRed = (valueTwoRed + valueTwoGreen) / 2;
      valueOneGreen = valueOneRed;
      valueTwoGreen = valueTwoRed;

      std::cout << "(P)";
    break;
    case('d'):
      //protanopia and deutronopia look the exact fucking same
      valueOneRed = valueOneRed / 2;
      valueTwoRed = valueTwoRed / 2;

      //deutronopia merges reds and greens
      valueOneRed = (valueOneRed + valueOneGreen) / 2;
      valueTwoRed = (valueTwoRed + valueTwoGreen) / 2;
      valueOneGreen = valueOneRed;
      valueTwoGreen = valueTwoRed;

      std::cout << "(D)";
    break;
    case('t'):
      valueOneBlue = valueOneBlue / 2;
      valueTwoBlue = valueTwoBlue / 2;

      //tritanopia merges blues and greens
      valueOneBlue = (valueOneBlue + valueOneGreen) / 2;
      valueTwoBlue = (valueTwoBlue + valueTwoGreen) / 2;

      valueOneGreen = valueOneBlue;
      valueTwoGreen = valueTwoBlue;

      //tell the user that its doing tritanopia 
      std::cout << "(T)";
    break;
  }

  //calculate the difference between each color
  int redDiff = valueOneRed - valueTwoRed;
  int blueDiff = valueOneBlue - valueTwoBlue;
  int greenDiff = valueOneGreen - valueTwoGreen;

  //ensure all values are positive
  if(redDiff < 0){ redDiff = redDiff * -1; }
  if(blueDiff < 0){ blueDiff = blueDiff * -1; }
  if(greenDiff < 0){ greenDiff = greenDiff * -1; }

  //add the difference together
  int totalDiff = redDiff + blueDiff + greenDiff;

  //write stuff to file
  if (writeToFile){
    string tomp = "r-" + to_string(valueOneRed);
    tomp += ", g-" + to_string(valueOneGreen);
    tomp += ", b-" + to_string(valueOneBlue);
    tomp += ", difference-" + to_string(totalDiff);
    tomp += ", rating-" + colorBlindnessRating(totalDiff);
    writeResultsToFile(name, tomp);
  }

  return totalDiff;
}

//gets two colors and compares them
int twoColorsPalette(char blindnessType)
{
  //some strings for holding info
  string colorOne, colorTwo;
  //get the first hex code
  std::cout << "Enter a hex color value (EX FF00FF): ";
  std::cin >> colorOne; 

  //get the second value
  std::cout << "Enter a second hex color value: ";
  std::cin >> colorTwo;

  std::cout << std::endl;

  int totalDiff = getDiff(colorOne, colorTwo, blindnessType);

  std::cout << std::endl;

  //give an evaluation of the total difference between the colors
  std::cout << colorBlindnessRating(totalDiff);

  //show the colorblind version of the difference
  std::cout << "\nThe difference value is: " << totalDiff << std::endl;

  return 0;
}

//gets an array of colors, then compares all of the colors to eachother
int multiColorsPalette(char blindnessType){
  int arrayLength;// need to remember what the array length is for 2 seconds

  std::cout << endl << "How large is your palette: ";
  std::cin >> arrayLength;

  //initialize the array with the length specified before
  string* colors = new string[arrayLength];

  std::cout << endl << "When you insert your hex value, please do not include the pound symbol (#)" << endl;
  for(int l = 0; l < arrayLength; l++){
    std::cout << "Please enter hex value #" << l + 1 << ": ";
    std::cin >> colors[l];
  }

  std::cout << std::endl;

  for(int in = 0; in < arrayLength - 1; in++){
    for(int out = in + 1; out < arrayLength; out++){
      if(in == out)
        continue;

      std::cout << colors[in] << " " << colors[out] << endl;
      //get the difference between the colors currently selected by the double loops
      int val = getDiff(colors[in], colors[out], blindnessType, "Color #" + std::to_string(in) + " to #" + std::to_string(out));

      //get the difference between the two listed values
      std::cout << "The difference value for color #" << in + 1 << " and #" << out + 1 << " is: " << val << ". ";

      std::cout << colorBlindnessRating(val);
      std::cout << std::endl;
    }
  }

    delete[] colors;

  return 0;
}

int main(){
  char blindnessType;
  char isLargerThanTwo;
  char retry;

  //for testing. Im compiling an executable on my local machine (which i didnt know i could do!)
  std::cout << "\nWould you like to write the results to a file? (Y or N)";
  std::cin >> retry;

  if(retry == 'y'){
    writeToFile = true;
  } else {
    writeToFile = false;
  }

  //get the colorblindness type
  std::cout << "Will your palette contain more than 2 entries? (y or n) ";
  std::cin >> isLargerThanTwo;

  //get the colorblindness type (protanopia and deuteranopia are copies because they look the same)
  std::cout << "\nWhat colorblindness? (protonopia = p, deuteranopia = d, tritanopia = t): ";
  std::cin >> blindnessType;

  if(isLargerThanTwo == 'y'){
    multiColorsPalette(blindnessType);
  } else {
    twoColorsPalette(blindnessType);
  }

  //for testing. Im compiling an executable on my local machine (which i didnt know i could do!)
  std::cout << "\nWould you like to restart? (Y or N)";
  std::cin >> retry;

  if(retry == 'y'){
    return main();
  } else {
    return 0;
  }
}

/*

//some strings for holding info
    int valueOneRed, valueOneGreen, valueOneBlue, valueTwoRed, valueTwoGreen, valueTwoBlue;

    //get the first rgb value
    std::cout << "Please enter the first red value (0 - 255): ";
    std::cin >> valueOneRed;
    std::cout << "Please enter the first green value (0 - 255): ";
    std::cin >> valueOneGreen;
    std::cout << "Please enter the first blue value (0 - 255): ";
    std::cin >> valueOneBlue;

    std::cout << "Please enter the second red value (0 - 255): ";
    std::cin >> valueTwoRed;
    std::cout << "Please enter the second green value (0 - 255): ";
    std::cin >> valueTwoGreen;
    std::cout << "Please enter the second blue value (0 - 255): ";
    std::cin >> valueTwoBlue;

    //another seperation
    std::cout << std::endl;

    int totalDiff = getDiffRGB(valueOneRed, valueOneGreen, valueOneBlue, valueTwoRed, valueTwoGreen, valueTwoBlue, blindnessType);

    //more fancy line seperation
    std::cout << std::endl;

    //give an evaluation of the total difference between the colors
    colorBlindnessRating(totalDiff);

    //show the colorblind version of the difference
    std::cout << "\nThe difference value is: " << totalDiff << std::endl;

fuck i need sources

this told me the math behind protanopia. 
everything I use here is based off of this source, 
and extrapolation from the information in this source
https://rgblind.com/blog/protanopia-explained

a clearer showcase of the protanopia math
https://www.color-blindness.com/protanopia-red-green-color-blindness/

deutranopia source. There is a difference between deutranopia and protanopia
but for the purposes of a silly little tool I couldnt see enough of a difference 
from protanopia. 
https://www.color-blindness.com/deuteranopia-red-green-color-blindness/

tritanopia source (has a color bar, thats how i brained out the math)
https://www.color-blindness.com/tritanopia-blue-yellow-color-blindness/

c++'s std::stoi
https://cplusplus.com/reference/string/stoi/

c++ arrays
https://www.geeksforgeeks.org/cpp/why-variable-length-array-were-removed-in-cpp/


*/
