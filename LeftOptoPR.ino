#include <FED3.h>                                      // Include the FED3 library 

int poke_num = 0;                                      // This variable is the number of pokes since the last pellet
int pokes_required = 1;                                // Increase the number of pokes required each time a pellet is received using an exponential equation
String sketch = "LOptoPR";                             // Unique identifier text for each sketch
FED3 fed3(sketch);                                     // Start the FED3 object

void setup() {
  fed3.begin();                                        // Setup the FED3 hardware
}

void loop() {
  fed3.run();                                          // Call fed.run at least once per loop
  
  if (fed3.Left) {                                    // If right poke is triggered
    fed3.logLeftPoke();                               // Log right poke
    poke_num++;                                        // Increment poke count

    if (poke_num == pokes_required) {                  // Check if the required number of pokes is reached
      fed3.leftPokePixel(0,0,0,1);                    // White light indicator
      
      fed3.pulseGenerator(4, 50, 25);                  // deliver opto 500ms, 50Hz frequency, 4ms pulse width (25 repetitionss bc 500ms/50hz)
      fed3.pixelsOff();
      pokes_required += 1;
      fed3.Event = "50HzStim";                          //Label the event "50HzStim"
      fed3.logdata();                                    
      
      fed3.FR = pokes_required;
      poke_num = 0;                                    // Reset poke count for the next trial
      fed3.Left = false;
      
    }
  }

  if (fed3.Right) {                                     // If left poke is triggered
    fed3.logRightPoke();                                // Log left poke
  }
}

//if (activePoke == 0)  logfile.print("Right"); //
// if (activePoke == 1)  logfile.print("Left"); //

//Frequency of 50 Hz means 50 cycles per second (1s = 1000 ms)
//Period = 1000 ms / 50 = 20 ms per cycle
//Within each cycle (20 ms): Pulse width is 4 ms. remaining time within the cycle = 20ms-4ms = 16ms (this is off time after each pulse)
//Total duration = 500 ms -> Number of cycles = Total duration / Period = 500 ms / 20 ms = 25 cycles.
