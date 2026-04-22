// Mux.h
// A MUX takes 2 inputs and a control signal
// and outputs one of the inputs based on the signal

/*/////////////////////////////////////////////////////////////////////////////////////////
// NOTE: This could be a general mux type that uses templating so we can apply it in 
//  different contexts.


    Mux 1:
    - This mux Sets the destination register for writing back results in the WB stage.
    - INPUT: bits 15-11 of instruction
    - INPUT: bits 20-16 of instruction
    - INPUT: Control Unit output
    - OUTPUT: 8-bit value ()
//////////////////////////////////////////////////////////////////////////////////////////*/

#ifndef MUX_H
#define MUX_H

// T is a placeholder for any data type
template <typename T>
T mux(T input0, T input1, bool choose) 
{
    // if choose is false (0), return input0
    return choose ? input1 : input0;
}

#endif