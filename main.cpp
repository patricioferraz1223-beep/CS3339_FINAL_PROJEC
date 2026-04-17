#include <iostream>
#include <unordered_map>
/*/////////////////////////////////////////////////////////////////////////////////////////
While there are remaining instructions:
- Program counter outputs the address of the current instruction
- Instruction memory outputs the instruction at the address given by the program counter

Instruction Fetch (IF):

    Program Counter:
    - INPUT: 32-bit address
    - OUTPUT: 32-bit instruction address 
    Instruction Memory:
    - INPUT: 32-bit instruction address (from PC)
    - OUTPUT: 32-bit instruction
    Adder:
    - INPUT: Program counter + 4
    - OUTPUT: 32-bit address of next instruction

Instruction Decode (ID) Stage:

    Control Unit:
    - INPUT: bits 31-26 of instruction
    - OUTPUT: 10 control signals; uint16_t
    - NOTE: Each control signal is 1 bit, except for the ALUOp signal which is 2 bits (bits 1-0 of control output)
    Mux 1:
    - INPUT: bits 15-0 of instruction
    - INPUT: bits 20-16 of instruction
    - INPUT: Control Unit output
    - OUTPUT: 16-bit value ()
    Register File:
    - INPUT: bits 25-21 of instruction (Read Addr 1)
    - INPUT: bits 20-16 of instruction (Read Addr 2)
    - INPUT: Write address (Mux 1 output)
    - INPUT: Write Data (32 bits, from WB stage)
    - INPUT: Control Unit output
    - OUTPUT: Read Data 1 (32 bits)
    - OUTPUT: Read Data 2 (32 bits)
    Sign Extend:
    - INPUT: bits 15-0 of instruction
    - OUTPUT: 32-bit sign-extended value

Execute (EX) Stage:

    Shift Left 2:
    - INPUT : Sign Extend output (32 bit sign extended value)
    - OUTPUT: 32-bit value shifted left by 2 bits
    Adder:
    - INPUT: Program counter + 4
    - INPUT: SL2 output
    - OUTPUT: 32-bit address of next instruction (for branch)
    Mux 2:
    - INPUT: Read Data 2 from Register File
    - INPUT: Sign Extend output
    - INPUT: Control Unit output
    - OUTPUT: 32-bit value (second operand for ALU)
    ALU
    - INPUT: 32-bit Register File output 1
    - INPUT: 32-bit Mux 2 output
    - INPUT: 2-bit Control Unit output
    - INPUT: 4-bit ALU Control output
    - OUTPUT: 32-bit ALU result
    - OUTPUT: Zero flag (1 bit)
    ALU Control
    - INPUT: 2-bit Control Unit output
    - OUTPUT: 4-bit operation code for ALU (uint4_t)

Memory (MEM) Stage:

    AND Gate:
    Mux 3:
    Data Memory:

Write back (WB) Stage:

    Mux 4:

ALU Control Encoding Example:

| ALU Control (4 bits) | Operation |
| -------------------- | --------- |
| 0000                 | AND       |
| 0001                 | OR        |
| 0010                 | ADD       |
| 0110                 | SUB       |
| 0111                 | SLT       |
| 1100                 | NOR       |


QUESTIONS:
1. How many output bits are there from the control unit?
2. Does each stage need to be parallelized for the sake of simulating pipelining? 
3. If the PC isn't what actually holds the instructions nor increments the instruction 
    address, what does it do?
3.1 On the same note, what is the input to the adder in the IF stage?
4. What is the 0 flag in the ALU?
5. Do we not care about the overflow flag in the ALU for this project?
//////////////////////////////////////////////////////////////////////////////////////////*/

/*/////////////////////////////////////////////////////////////////////////////////////////
// FIXME: Not implemented    

    Program Counter:
    - INPUT: 32-bit address
    - OUTPUT: 32-bit instruction address 
//////////////////////////////////////////////////////////////////////////////////////////*/
unint32_t program_counter(uint32_t address) {
    // For this project, the program counter will simply output the address given to it.
    return address;
}

/*/////////////////////////////////////////////////////////////////////////////////////////
// FIXME: Not implemented    

    Instruction Memory:
    - INPUT: 32-bit instruction address (from PC)
    - OUTPUT: 32-bit instruction
//////////////////////////////////////////////////////////////////////////////////////////*/
class InstructionMemory {
    private:
        unordered_map<uint32_t, uint32_t> memory; // Address to instruction mapping

    public:
        uint32_t read_address(uint32_t address) {
            // For this project, we will return a dummy instruction based on the address.
            // In a real implementation, this would access memory to fetch the instruction.
            return 0xFFFFFFFF; // Example dummy instruction
        }
        void load_instructions(uint32_t address, uint32_t instruction) {
        }
};

/*/////////////////////////////////////////////////////////////////////////////////////////
// FIXME: Not implemented    
// NOTE: This could be a general mux type that uses templating so we can apply it in 
//  different contexts.


    Mux 1:
    - This mux Sets the destination register for writing back results in the WB stage.
    - INPUT: bits 15-11 of instruction
    - INPUT: bits 20-16 of instruction
    - INPUT: Control Unit output
    - OUTPUT: 8-bit value ()
//////////////////////////////////////////////////////////////////////////////////////////*/
uint8_t mux1(uint8_t input1, uint8_t input2, bool control_signal) {
    // For this project, we will return one of the inputs based on the control signal.
    return control_signal ? input1 : input2;
}

/*/////////////////////////////////////////////////////////////////////////////////////////
// FIXME: Not implemented    

    Sign Extend:
    - INPUT: bits 15-0 of instruction
    - OUTPUT: 32-bit sign-extended value
//////////////////////////////////////////////////////////////////////////////////////////*/
uint32_t sign_enxtender(uint16_t input) {
    return 0; 
}

/*/////////////////////////////////////////////////////////////////////////////////////////
// FIXME: Not implemented    

    Register File:
    - INPUT: bits 25-21 of instruction (Read Addr 1)
    - INPUT: bits 20-16 of instruction (Read Addr 2)
    - INPUT: Write address (Mux 1 output), 5 bits
    - INPUT: Write Data (32 bits, from WB stage)
    - INPUT: Control Unit output
    - OUTPUT: Read Data 1 (32 bits)
    - OUTPUT: Read Data 2 (32 bits)
//////////////////////////////////////////////////////////////////////////////////////////*/
class register_file {
    private:
        int memory_amount = 32; // Number of registers
        uint32_t registers[memory_amount]; // Register number to value mapping

    public:
        uint64_t read_instructions(uint8_t read_data_1, uint8_t read_data_2, uint8_t write_addr, uint32_t write_data, bool control_signal);
}

/*/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////*/

int main() {
    // Declare state registers for each stage of the pipeline
    uint32_t sr_imem_out = 0;

    uint32_t sr_reg_file_out_1 = 0;
    uint32_t sr_reg_file_out_2 = 0;

    uint32_t sr_alu_out = 0;
    uint32_t write_data_loc = 0;

    uint32_t sr_dmem_out = 0;
    uint32_t dmem_address = 0;

    // Intialize Modules
    program_counter     PC;
    InstructionMemory   IMem;
    register_file       RegFile;
    mux1                M1;
    sign_enxtender      SE;

    while (true){   // FIXME: set condition (while instructions remain)

        // FIXME: I haven't included the mux that selects between the branch address and 
        //  the next sequential address for the PC input

        // Stage 1: Fetch Stage

        // Take PC output and feed it into IMem to get instruction
        uint32_t instruction_address = program_counter(0x00000000); // Example usage of program counter
        InstructionMemory instr_mem;

        // Read address from IMemand 
        uint32_t instruction = instr_mem.read_address(instruction_address); // Fetch instruction from memory

        // Stage 2: Instruction Decode Stage
        
        // Load instruction into the Register file and output the read addresses
        // sr_instruction -> Register_file;

        // void read_instructions(uint8_t read_data_1, uint8_t read_data_2, uint8_t write_addr, uint32_t write_data, bool control_signal);
        uint8_t read_addr_1 = (sr_imem_out >> 21) & 0x1F;   // bits 21-25
        RegFile.read_instructions(read_addr_1); // FIXME: Need to fill in the other parameters

        // Sign extend
        // QUESTION: Is this for the immediate?

        // Stage 3: Execute

        // Send SE output to SL2
        // Send SE output and Read Data 2 to Mux2
        // Send SL2 output and PC+4 to Adder for branch address calculation
        // Send Mux2 output and Read Data 1 to ALU for execution

        // Stage 4: Memory Access

        // Send ALU output and write data address to DMem

        // Stage 5: Write Back

        // Send DMem output and ALU output to Mux4 for selecting write back data

        // Load values into state registers for the next stage
    }

    

/*/////////////////////////////////////////////////////////////////////////////////////////
    While instructions remain
        IF:
            Produce instruction

        ID: 
            Decode instructions and create outputs

        At the End:
            Load the outputs of each stage into the state registers
//////////////////////////////////////////////////////////////////////////////////////////*/


    return 0;
}