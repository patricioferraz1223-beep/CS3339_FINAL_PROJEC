// Mux.h
// A MUX takes 2 inputs and a control signal
// and outputs one of the inputs based on the signal

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