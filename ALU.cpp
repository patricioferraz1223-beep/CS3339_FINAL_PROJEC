uint32_t execute_alu(uint32_t A, uint32_t B, uint8_t control_code, bool &zero_flag) 
{
    uint32_t result = 0;
    //These operations connect to the ones specified in ALU control
    switch (control_code) 
    {
        case 0b0000: result = A & B; break; // AND
        case 0b0001: result = A | B; break; // OR
        case 0b0010: result = A + B; break; // ADD
        case 0b0110: result = A - B; break; // SUB
        case 0b0111: result = (A < B) ? 1 : 0; break; // SLT
        default:     result = 0;
    }

    //Zero Flag which needs to be set for branching
    zero_flag = (result == 0);

    return result;
}