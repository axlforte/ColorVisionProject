# Goofy little colorblind tool

## Description

**version 2.2**

The user provides the amount of colors, then the user provides the desired colorblind type, then provides the colors as hex values. 
From there, the program applies colorblind modifications and tells the user the usability of the colors.

### New features

The user can now ask the program to output results to a file. 
- for 2 color comparisons: the program writes (or overwrites) a single file called colorComparison_color.txt
- for multicolor comparisons: the program writes (or overwrites) a file for each comparison. The files hold the first compared color and second compared color in the title.

The output file contains the RGB value of the first color, the RGB value of the second color, the total difference between the colors, and the same rating provided when the program is run.

The user can supply 'na' as the palette length during multicolor comparisons. The program will ask for colors until the user provides the word quit as a color. 

### Removed features

Providing RGB colors has been removed over UX concerns. The user is no longer prompted to choose RGB or HEX, and all colors are expected to be provided as hex values. 
The output files 

## Developer

Davis Williams: the guy who made the program

## Example

To run the program, give the following commands:

```
g++ --std=c++11 *.cpp -o cvp
./cvp
```

Here is an example of the program running:

<img width="821" height="420" alt="image" src="https://github.com/user-attachments/assets/25b0abc2-8014-4a16-8e01-98910f3f77ba" />
