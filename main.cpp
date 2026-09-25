#include <iostream>
//I cant remember if this was in the repo but i wanted it anyways
using namespace std;

//gives a generalized rating for the colorblind friendliness of the color.
//
//uses the value generated from getDiff(). 

//the ratings are mostly arbitrary.
int colorBlindnessRating(int val){
  //compare the colors
  //
  //i didnt need brackets but I remember this code existed as a 
  //larger snippet with multiple lines within the if statements
  //
  //val is the combined difference between the RGB values. if the colors are
  //FFFFFF and FFFF00 (after colorblindness operations), then val
  //would equal 255
  if(val < 80){
    //this color is visually easy to confuse
    std::cout << "Too close to use!";
  } else if(val < 140){
    //these colors are close but you can use them if its your only option
    std::cout << "A little too similar...";
  } else  if(val < 200){
    //these colors are still close, but they arent indistinguishable
    std::cout << "Decently seperated. ";
  } else {
    //the color is clearly seperated in the colorblind's context
    std::cout << "Colorblind friendly";
  }

  //colorBlindnessRating returns val for ease of use reasons.
  //I could probably get rid of it without too much difficulty
  //but im lazy and im doing comments after I wrote it
  return val;
}

//idk if I actually need this, but ill provide if std::stoi cant / shouldnt be used
int getDiffRGB(int valueOneRed, int valueOneGreen, int valueOneBlue, int valueTwoRed, int valueTwoGreen, int valueTwoBlue, char blindnessType){

  //give the rgb values to the user. debug only at the moment
  //std::cout << "Red 1: " << valueOneRed << ", Green 1: " << valueOneGreen << ", Blue 1: " << valueOneBlue << std::endl;
  //std::cout << "Red 2: " << valueTwoRed << ", Green 2: " << valueTwoGreen << ", Blue 2: " << valueTwoBlue << std::endl;

  //modify colors according to the blindness type
  switch(blindnessType){
    //if your value is wrong, then default to protanopia and tell you
    default:
    case('p'):
      //protanopia halves the red value
      valueOneRed = valueOneRed / 2;
      valueTwoRed = valueTwoRed / 2;

      //protanopia merges reds and greens into a homogenous yellow
      valueOneRed = (valueOneRed + valueOneGreen) / 2;
      valueTwoRed = (valueTwoRed + valueTwoGreen) / 2;
      //if the reds are the same as the greens then just set the reds to the greens
      valueOneGreen = valueOneRed;
      valueTwoGreen = valueTwoRed;

      //tell the user that its doing protanopia 
      std::cout << "(P)";
    break;
    case('d'):
      //protanopia and deutronopia look the exact fucking same
      //go look it up on https://www.color-blindness.com and tell me im wrong
      //there is a difference between the final green sections but i dont know how the math maths there
      valueOneRed = valueOneRed / 2;
      valueTwoRed = valueTwoRed / 2;

      //deutronopia merges reds and greens into a homogenous yellow
      valueOneRed = (valueOneRed + valueOneGreen) / 2;
      valueTwoRed = (valueTwoRed + valueTwoGreen) / 2;
      //if the reds are the same as the greens then just set the reds to the greens
      valueOneGreen = valueOneRed;
      valueTwoGreen = valueTwoRed;

      //tell the user that its doing deutronopia 
      std::cout << "(D)";
    break;
    case('t'):
      //tritanopia seems to fuck with green and blue
      //it seems to be the same as protonopia but swapping out red with blue?
      valueOneBlue = valueOneBlue / 2;
      valueTwoBlue = valueTwoBlue / 2;

      //tritanopia merges blues and greens into a homogenous tealish color
      valueOneBlue = (valueOneBlue + valueOneGreen) / 2;
      valueTwoBlue = (valueTwoBlue + valueTwoGreen) / 2;
      //if the blues are the same as the greens then just set the blues to the greens
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

  //add the difference together
  int totalDiff = redDiff + blueDiff + greenDiff;

  //i was too lazy to get the absolute value through a function
  //so this gets the positive version of totalDiff if its below 0
  if(totalDiff < 0){
    totalDiff = totalDiff * -1;
  }

  //this is the only function that's called like a normal ass function
  //so it actually returns something. in this case, totalDiff because
  //the function is getDiff
  return totalDiff;
}

//takes two hex codes, turns them into RGB for math purposes, does math depending on
//the blindness type, then returns the average difference between the two colors.
//
//the individual RGB values are generated, and the difference between the values are generated, 
//but those values are not useful for fulfilling the requirements
//
//sounds like i wont be able to use this. that's fine, ill make a version of this that uses RGB. 
//I convert to rgb already so it's not too hard
int getDiff(string colorOne, string colorTwo, char blindnessType){
  //get the RGB values for the first color
  //i looked up how to turn string based hex values into ints
  int valueOneRed = std::stoi(colorOne.substr(0, 2), nullptr, 16);
  int valueOneGreen = std::stoi(colorOne.substr(2, 2), nullptr, 16);
  int valueOneBlue = std::stoi(colorOne.substr(4, 2), nullptr, 16);

  /*

  I know what std:stoi does i swear!

  std::stoi(string hex value, idx, int base)

  hex value - the value that's going to become an integer

  idx - a variable that gets modified in some way. 
  the output of this is a pointer to the character after the numbers, which I dont need so it's unused (nullptr works fine). 

  int base - the base numerical system to use. 

  */

  //get RGB for the second color
  int valueTwoRed = std::stoi(colorTwo.substr(0, 2), nullptr, 16);
  int valueTwoGreen = std::stoi(colorTwo.substr(2, 2), nullptr, 16);
  int valueTwoBlue = std::stoi(colorTwo.substr(4, 2), nullptr, 16);

  return getDiffRGB(valueOneRed, valueOneGreen, valueOneBlue, valueTwoRed, valueTwoGreen, valueTwoBlue, blindnessType);
}


int twoColorsPalette(char blindnessType)
{
  //some strings for holding info
  string colorOne, colorTwo;

  //fancy stuff. seperates colorblindness type from the color palette
  //std:cout << std::endl;

  //get the first hex code
  std::cout << "Enter a hex color value (EX FF00FF): ";
  std::cin >> colorOne; 

  //get the second value
  std::cout << "Enter a second hex color value: ";
  std::cin >> colorTwo;

  //another seperation
  std::cout << std::endl;

  //moved to a function to be better utilized in variable size section
  int totalDiff = getDiff(colorOne, colorTwo, blindnessType);

  //more fancy line seperation
  std::cout << std::endl;

  //give an evaluation of the total difference between the colors
  //using the context of the colorblindness
  colorBlindnessRating(totalDiff);

  //show the rgb of the colorblind version of the colors
  //std::cout << "\n\nRed 1: " << valueOneRed << ", Green 1: " << valueOneGreen << ", Blue 1: " << valueOneBlue << std::endl;
  //std::cout << "Red 2: " << valueTwoRed << ", Green 2: " << valueTwoGreen << ", Blue 2: " << valueTwoBlue << std::endl;

  //show the colorblind version of the difference
  std::cout << "\nThe difference value is: " << totalDiff << std::endl;

  //bail, we're done here
  return 0;
}

int twoColorsPaletteRGB(char blindnessType)
{
  //some strings for holding info
  int valueOneRed, valueOneGreen, valueOneBlue, valueTwoRed, valueTwoGreen, valueTwoBlue;

  //fancy stuff. seperates colorblindness type from the color palette
  //std:cout << std::endl;

  //get the first rgb value
  std::cout << "Please enter the first red value (0 - 255): ";
  std::cin >> valueOneRed;
  std::cout << "Please enter the first green value (0 - 255): ";
  std::cin >> valueOneGreen;
  std::cout << "Please enter the first blue value (0 - 255): ";
  std::cin >> valueOneBlue;

  td::cout << "Please enter the second red value (0 - 255): ";
  std::cin >> valueTwoRed;
  std::cout << "Please enter the second green value (0 - 255): ";
  std::cin >> valueTwoGreen;
  std::cout << "Please enter the second blue value (0 - 255): ";
  std::cin >> valueTwoBlue;

  //another seperation
  std::cout << std::endl;

  //moved to a function to be better utilized in variable size section
  int totalDiff = getDiff(colorOne, colorTwo, blindnessType);

  //more fancy line seperation
  std::cout << std::endl;

  //give an evaluation of the total difference between the colors
  //using the context of the colorblindness
  colorBlindnessRating(totalDiff);

  //show the rgb of the colorblind version of the colors
  //std::cout << "\n\nRed 1: " << valueOneRed << ", Green 1: " << valueOneGreen << ", Blue 1: " << valueOneBlue << std::endl;
  //std::cout << "Red 2: " << valueTwoRed << ", Green 2: " << valueTwoGreen << ", Blue 2: " << valueTwoBlue << std::endl;

  //show the colorblind version of the difference
  std::cout << "\nThe difference value is: " << totalDiff << std::endl;

  //bail, we're done here
  return 0;
}

//same as the above function, but ill use rgb instead of hex. just in case
int multiColorsPaletteRGB(char blindnessType){
  int arrayLength;// need to remember what the array length is for 2 seconds

  //ultra super line seperation 4
  std::cout << std::endl;

  //get the length of the array (this shouldnt change, but 
  //allowing the user to input exit instead of specifying a 
  //length would be more useful. too bad i dont know
  //about how vectors work!)
  std::cout << "How large is your palette: ";
  std::cin >> arrayLength;

  //initialize the array with the length specified before
  int* reds = new int[arrayLength];
  int* greens = new int[arrayLength];
  int* blues = new int[arrayLength];

  //when one line seperation isnt enough
  std::cout << std::endl;

  //populate the array because its junk data right now (idk if c++ 
  //auto sets entries to 0 or gets junk data)
  for(int l = 0; l < arrayLength; l++){
    std::cout << "Please enter the red value " << l + 1 << " (0 - 255): ";
    std::cin >> reds[l];
    std::cout << "Please enter the green value " << l + 1 << " (0 - 255): ";
    std::cin >> greens[l];
    std::cout << "Please enter the blue value " << l + 1 << " (0 - 255): ";
    std::cin >> blues[l];
  }

  //ALL OF THE fancy line seperation
  std::cout << std::endl;

  //now each difference needs to be listed. 
  //two for loops will be used to check all of the values 
  //against all of the other values

  //efficiency? never heard of it
  for(int in = 0; in < arrayLength - 1; in++){
    for(int out = in + 1; out < arrayLength; out++){
      //dont compare one value to itself
      if(in == out)
        continue;

      //get the difference between the colors currently selected by the double loops
      int val = getDiffRGB(reds[in], greens[in], blues[in], reds[out], greens[out], blues[out], blindnessType);

      //get the difference between the two listed values
      std::cout << "The difference value for color #" << in + 1 << " and #" << out + 1 << " is: " << val << ". ";

      //RATE! THOSE! COLOORRRRRRRRRRSSSSSSSSSS!
      colorBlindnessRating(val);

      //getDiff() prints out the colorblindness value. 

      //excessive line seperation? I DONT THINK SO!
      std::cout << std::endl;
    }
  }

    delete[] reds;
    delete[] greens;
    delete[] blues;

  return 0;
}

//The main loop. its the thing that starts when the program is run
//
//it asks you if youre going to have more than 2 colors, then gets the colorblindness type,
//runs the appropriate amount of color comparisons, then makes sure that you can see them
//before closing
int main(){
  //char isLargerThanTwo; // me being lazy and not looking up how to directly get a bool
  char blindnessType;// used thru the code to remember what the type of blindness is
  char isLargerThanTwo;// used thru the code to remember what the type of blindness is
  char retry;// used thru the code to remember what the type of blindness is

  //get the colorblindness type (currently only protonopia is implemented)
  std::cout << "Will your palette contain more than 2 entries? (y or n) ";
  std::cout << "\n\nFor instructors: selecting Y will provide the excessive version.";
  std::cout << "\nThe excessive version does not follow the guidelines set for the project.";
  std::cout << "\nFor instructors: selecting N will provide the acceptable version.";
  std::cout << "\nThe acceptable version only uses code that has been taught in class (excluding functions)\n";
  std::cin >> isLargerThanTwo;

  //get the colorblindness type (protanopia and deuteranopia are copies because they look the same)
  std::cout << "\nWhat colorblindness? (protonopia = p, deuteranopia = d, tritanopia = t): ";
  std::cin >> blindnessType;

  if(isLargerThanTwo == 'y'){
    multiColorsPaletteRGB(blindnessType);
  } else {
    //some strings for holding info
    int valueOneRed, valueOneGreen, valueOneBlue, valueTwoRed, valueTwoGreen, valueTwoBlue;

    //fancy stuff. seperates colorblindness type from the color palette
    //std:cout << std::endl;

    //get the first rgb value
    std::cout << "Please enter the first red value (0 - 255): ";
    std::cin >> valueOneRed;
    std::cout << "Please enter the first green value (0 - 255): ";
    std::cin >> valueOneGreen;
    std::cout << "Please enter the first blue value (0 - 255): ";
    std::cin >> valueOneBlue;

    td::cout << "Please enter the second red value (0 - 255): ";
    std::cin >> valueTwoRed;
    std::cout << "Please enter the second green value (0 - 255): ";
    std::cin >> valueTwoGreen;
    std::cout << "Please enter the second blue value (0 - 255): ";
    std::cin >> valueTwoBlue;

    //another seperation
    std::cout << std::endl;

    //moved to a function to be better utilized in variable size section
    //
    //im not going to paste the getDiffRGB function content here
    int totalDiff = getDiffRGB(colorOne, colorTwo, blindnessType);

    //more fancy line seperation
    std::cout << std::endl;

    //give an evaluation of the total difference between the colors
    //using the context of the colorblindness
    //
    //I'd like this to be consistent between implementations. 
    //I could paste the function content tho
    colorBlindnessRating(totalDiff);

    //show the rgb of the colorblind version of the colors
    //std::cout << "\n\nRed 1: " << valueOneRed << ", Green 1: " << valueOneGreen << ", Blue 1: " << valueOneBlue << std::endl;
    //std::cout << "Red 2: " << valueTwoRed << ", Green 2: " << valueTwoGreen << ", Blue 2: " << valueTwoBlue << std::endl;

    //show the colorblind version of the difference
    std::cout << "\nThe difference value is: " << totalDiff << std::endl;
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
