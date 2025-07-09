# Polykami Basic Example
A minimal example demonstrating the basic setup and window management using hte Polykami graphics library.

## Overview
This example shows how to:
- Initialize a Polykernel instance
- Create and manage a window
- Run a basic render loop
- Handle cleanup and error cases

## Code structure
The example creates a `polykami::core::Polykernel` object which manages the core graphics functionality. 
It then runs a standard game loop that:
1. Checks if the window should close
2. Updates the window state
3. Clears the frame buffer
4. Swaps the display buffers

## Running
The program will open a window and run until closed by the user. If initialization fails, an error message will be
printed to `std::cerr`.

### Error handling
The examples includes basic exception handling to catch any initialization errors that might occur during Polykami setup.