/*
  Feeding experimentation device 3 (FED3)
  Free Feeding mode

  alexxai@wustl.edu
  December, 2020

  This project is released under the terms of the Creative Commons - Attribution - ShareAlike 3.0 license:
  human readable: https://creativecommons.org/licenses/by-sa/3.0/
  legal wording: https://creativecommons.org/licenses/by-sa/3.0/legalcode
  Copyright (c) 2020 Lex Kravitz
*/

#include <FED3.h>                                       //Include the FED3 library 
String sketch = "FreeFeed";                             //Unique identifier text for each sketch (this will show up on the screen and in log file)
FED3 fed3 (sketch);                                     //Start the FED3 object

int pelletCount = 0;                                    // Counter for the number of pellets eaten
bool isFreeFeeding = true;                              // Flag to check if it's in the free feed schedule

void setup() {
  fed3.begin();                                         // Setup the FED3 hardware
  fed3.DisplayPokes = false;                            // Customize the DisplayPokes option to 'false' to not display the poke indicators
}

void loop() {
  fed3.run();                                           // Call fed.run at least once per loop

  if (isFreeFeeding) {
    fed3.Feed();                                        // Drop pellet
    pelletCount++;                                      // Increment pellet counter
    fed3.Timeout(3);                                    // 3s timeout (5s was kinda long imo bc it still took a while after the 5s was over to dispense)
    
    if (pelletCount >= 25) {
      isFreeFeeding = false;                            // Switch to fixed ratio schedule
    }
  } else {
    if (fed3.Left) {                                    // If left poke is triggered
      fed3.logLeftPoke();                               // Log left poke
      fed3.leftPokePixel(0,0,0,1);                                  
      fed3.Feed(); 
                                     
    }

    if (fed3.Right) {                                   // If right poke is triggered
      fed3.logRightPoke();                              // Log right poke
    }
  }
}












