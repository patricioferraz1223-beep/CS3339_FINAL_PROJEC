#include <cstdint>

uint8_t alu_control(uint8_t alu_op, uint8_t funct) {
    //00 = Store or Load, 0010 = Add, 0110 Subtract, 
    if (alu_op == 0b00) return 0b0010; //Load -> Add
    if (alu_op == 0b01) return 0b0110; //Branch -> Subtract
    
    if (alu_op == 0b10) {
        //Logic performed ONLY using registers
        switch(funct) {
            case 0x00: return 0b1000; // SLL
            case 0x02: return 0b1001; // SRL
            case 0x20: return 0b0010; //0x20 = Add instruction; 0010 for ALU control is perform addition
            case 0x22: return 0b0110; //0x22 = Sub instruction; 0110 for ALU control is perform subtraction
            case 0x24: return 0b0000; //0x24 = And instruction; 0000 is ALU control bitwise AND
            case 0x25: return 0b0001; //0x25 = Or instruction; 0001 is ALU control bitwise OR
            case 0x2A: return 0b0111; //Slt = Set less than, in order to compare 2 inputs and output either a 0 or 1 depending. Used for comparisons
            default:   return 0b0010; //Default to Add, since it's the most common operation
        }
    }

    if (alu_op == 0b11) {
        // MUL special opcode path (opcode 0x1C)
        switch(funct) {
            case 0x02: return 0b1010; // MUL
            default:   return 0b0010; // Default ADD
        }
    }

    return 0b0010; 
}
