#include <iostream>
#include <unordered_map>
#include <cstdint>
#include <iomanip>

#include "Program_Counter.h"
#include "ALU.h"
#include "ALU_Control.h"
#include "Adder.h"
#include "Register_File.h"
#include "Shift_Left_2.h"
#include "Sign_Extender.h"
#include "MUX.h"
#include "DataMemory.h"
#include "ControlUnit.h"
#include "assembler.h"
#include "imem.h"

using namespace std;
/*/////////////////////////////////////////////////////////////////////////////////////////
RUNNING THE SIMULATOR:
g++ -std=c++20 main.cpp assembler.cpp imem.cpp Program_Counter.cpp ALU.cpp ALU_Control.cpp Adder.cpp Register_File.cpp Shift_Left_2.cpp Sign_Extender.cpp DataMemory.cpp ControlUnit.cpp -o main && ./main


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
1. How many output bits are there from the control unit? 10
2. Does each stage need to be parallelized for the sake of simulating pipelining? Not literally, but state registers are needed
3. If the PC isn't what actually holds the instructions nor increments the instruction 
    address, what does it do? it holds the address of the instructions
3.1 On the same note, what is the input to the adder in the IF stage?
4. What is the 0 flag in the ALU?
5. Do we not care about the overflow flag in the ALU for this project?
//////////////////////////////////////////////////////////////////////////////////////////*/


/*/////////////////////////////////////////////////////////////////////////////////////////
COMMAND TO COMPILE AND RUN:
    g++ -std=c++20 main.cpp assembler.cpp imem.cpp Program_Counter.cpp ALU.cpp ALU_Control.cpp Adder.cpp Register_File.cpp Shift_Left_2.cpp Sign_Extender.cpp DataMemory.cpp ControlUnit.cpp -o main && ./main
//////////////////////////////////////////////////////////////////////////////////////////*/

int main() {
    // Declare state registers for each stage of the pipeline
    // FIXME: I need to change these types, theyre not all accurate
    // QUESTION: Do we need to store PC output in a state register? 

    assembler my_assembler(false);      // Set to false to disable debug output from assembler
    my_assembler.process_assembly_file("assembly_file.asm");    // Encode Assembly file
    
    struct sr_IF_ID {
        uint32_t instruction = 0;
        uint32_t pcPlus4 = 0;
    };

    struct sr_ID_EX {
        uint32_t readData1 = 0;
        uint32_t readData2 = 0;
        uint32_t signExtended = 0;
        uint8_t rs = 0;
        uint8_t rt = 0;
        uint8_t rd = 0;
        uint8_t funct = 0;
        uint8_t shamt = 0;
        ControlSignals ctrl = {0};
        uint8_t writeReg = 0;
        uint32_t pcPlus4 = 0;
    };

    struct sr_EX_MEM {
        uint32_t aluResult = 0;
        uint32_t writeData = 0;
        uint8_t writeReg = 0;
        uint32_t branchAddr = 0;
        bool zeroFlag = false;

        bool memRead = false;
        bool memWrite = false;
        bool branch = false;
        bool memToReg = false;
        bool regWrite = false;

        uint32_t pcPlus4 = 0;
    };

    struct sr_MEM_WB {
        uint32_t readData = 0;
        uint32_t aluResult = 0;
        uint8_t writeReg = 0;

        bool memToReg = false;
        bool regWrite = false;
    };

    // OLD state register variables. Commenting out but keeping them
    // in case there are mistakes in the structs
    /*
    uint32_t sr_imem_out = 0;

    uint32_t sr_reg_file_out_1 = 0;
    uint32_t sr_reg_file_out_2 = 0;

    uint32_t sr_alu_out = 0;
    uint32_t write_data_loc = 0;

    uint32_t sr_dmem_out = 0;
    uint32_t dmem_address = 0;
    */

    // Intialize Modules
    ProgramCounter      PC;
    InstructionMemory   IMem("program.bin");   // Load instruction memory with encoded instructions from assembly file
    RegisterFile       RegFile;
    DataMemory         DMem;

    //Initialize state registers
    sr_IF_ID    if_id_current,
                if_id_next;
    sr_ID_EX    id_ex_current,
                id_ex_next;
    sr_EX_MEM   ex_mem_current,
                ex_mem_next;
    sr_MEM_WB   mem_wb_current,
                mem_wb_next;

    // Instantiate MemtoReg Mux output here since its output is needed in the ID stage for writing to the register file
    uint32_t writeData = 0;

    int i = 0; // iterator
    int iterations = 0;

    while (i < (int)(IMem.get_size() / 4)){   // Divide by 4 since get_size() is in bytes
        iterations++;

        // FIXME: I haven't included the mux that selects between the branch address and 
        //  the next sequential address for the PC input
        // Pretty sure the above issue is solved with the nextPC mux.

        // Stage 1: Fetch Stage     //////////////////////////////////////////////////////////////////////////

        // Take PC output and feed it into IMem to get instruction
        uint32_t fetched_instruction_address = PC.get_address();

        // Read address from IMemand 
        uint32_t fetched_instruction = IMem.read_address(fetched_instruction_address); // Fetch instruction from memory

        // Calculate pcPlus4 value for PC incrementation
        uint32_t pc_plus_4 = adder(fetched_instruction_address, 4);

        // Load values into state register
        if_id_next.instruction = fetched_instruction;
        if_id_next.pcPlus4 = pc_plus_4;

        // Stage 2: Instruction Decode Stage    //////////////////////////////////////////////////////////////
        // Take values from state register
        uint32_t instruction_to_decode = if_id_current.instruction;

        // Shift and mask bits to extract fields from instruction
        uint8_t opcode = (instruction_to_decode >> 26) & 0x3F; // 31-26. used for R, I, J instructions
        uint8_t rs = (instruction_to_decode >> 21) & 0x1F;     // 25-21. used for R, I instructions
        uint8_t rt = (instruction_to_decode >> 16) & 0x1F;     // 20-16. used for R, I instructions
        uint8_t rd = (instruction_to_decode >> 11) & 0x1F;     // 15-11. used for R instructions
        uint8_t shamt = (instruction_to_decode >> 6) & 0x1F;  // 10-6. shift amount. Used for R instructions
        uint8_t funct = instruction_to_decode & 0x3F;  // 5-0. used for R instructions
        uint16_t immediate = instruction_to_decode & 0xFFFF;  // 15-0. used for I instructions
        uint32_t address = instruction_to_decode & 0x03FFFFFF;    // 25-0. used for J instructions

        // MUX 1 — which register gets the result?
        ControlSignals signals = controlUnit(opcode);
        uint8_t writeReg = mux<int>(rt, rd, signals.regDst);
        
        // Load instruction into the Register file and output the read addresses
        // sr_instruction -> Register_file;
        uint32_t data1, 
                 data2;
        RegFile.read(rs, rt, data1, data2);
         
        // Sign extend
        uint32_t extended_immediate = sign_extender(immediate);

        // Load values into state register
        id_ex_next.readData1 = data1;
        id_ex_next.readData2 = data2;
        id_ex_next.signExtended = extended_immediate;
        id_ex_next.rs = rs;
        id_ex_next.rt = rt;
        id_ex_next.rd = rd;
        id_ex_next.funct = funct;
        id_ex_next.shamt = shamt;
        id_ex_next.ctrl = signals;
        id_ex_next.writeReg = writeReg;

        id_ex_next.pcPlus4 = if_id_current.pcPlus4;

        // Stage 3: Execute     //////////////////////////////////////////////////////////////////////////

        // SL2: Send SE output to SL2
        uint32_t sl2_out = shift_left_2(id_ex_current.signExtended);

        // ADDER: Send SL2 output and PC+4 to Adder for branch address calculation
        // FIXME: I think this should be saved in a state register
        ex_mem_next.branchAddr = adder(if_id_current.pcPlus4, sl2_out);

        // MUX (ALU Input): Send SE output and Read Data 2 to Mux2
        uint32_t aluInput2 = mux<uint32_t>(id_ex_current.signExtended, id_ex_current.readData2, id_ex_current.ctrl.aluSrc);

        // ALU Control: Send ALU control bits to ALU control to get ALU operation code
        uint8_t aluControlCode = alu_control(id_ex_current.ctrl.aluOp, id_ex_current.funct); // For R-type, funct field determines operation
        
        // ALU: Send Mux2 output, Read Data 1, and ALU control to ALU for execution
        ex_mem_next.aluResult = execute_alu(id_ex_current.readData1, aluInput2, aluControlCode, ex_mem_next.zeroFlag);

        // Load Write Data (Read Data 2) into state register for memory access stage
        ex_mem_next.writeData = id_ex_current.readData2;
        ex_mem_next.writeReg = id_ex_current.writeReg;

        // Update control signals in EX/MEM state register for use in MEM and WB stages
        ex_mem_next.memRead = id_ex_current.ctrl.memRead;
        ex_mem_next.memWrite = id_ex_current.ctrl.memWrite;
        ex_mem_next.branch = id_ex_current.ctrl.branch;
        ex_mem_next.memToReg = id_ex_current.ctrl.memToReg;
        ex_mem_next.regWrite = id_ex_current.ctrl.regWrite;

        ex_mem_next.pcPlus4 = id_ex_current.pcPlus4;
        // Stage 4: Memory Access   //////////////////////////////////////////////////////////////////////////
        
        // MUX 3 — does PC go to next line or branch?
        int nextPC = mux<int>(ex_mem_current.pcPlus4, ex_mem_current.branchAddr, ex_mem_current.branch && ex_mem_current.zeroFlag);

        // Send ALU output and write data address to DMem
        DMem.write(ex_mem_current.aluResult, ex_mem_current.writeData, ex_mem_current.memWrite);

        uint32_t mem_read_data = DMem.read(ex_mem_current.aluResult, ex_mem_current.memRead);

        // Load up state registers
        mem_wb_next.readData = mem_read_data;
        mem_wb_next.aluResult = ex_mem_current.aluResult;
        mem_wb_next.writeReg = ex_mem_current.writeReg;

        mem_wb_next.memToReg = ex_mem_current.memToReg;
        mem_wb_next.regWrite = ex_mem_current.regWrite;

        // Stage 5: Write Back      //////////////////////////////////////////////////////////////////////////

        // MUX 4 — does result come from ALU or memory?
        // FIXME: the control signal needs to be carried through the pipeline
        writeData = mux<uint32_t>(mem_wb_current.aluResult, mem_wb_current.readData, mem_wb_current.memToReg);

        // QUESTION: Should I write to R8?
        if (mem_wb_current.regWrite) {
            cout << "Writing to register " << (int)mem_wb_current.writeReg << " value: 0x" << hex << writeData << dec << endl;
        }
        RegFile.write(mem_wb_current.writeReg, writeData, mem_wb_current.regWrite); // Write back data from WB stage into register file

        // Send DMem output and ALU output to Mux4 for selecting write back data

        // End of loop

        // Load values into state registers for the next stage
        if_id_current = if_id_next;
        id_ex_current = id_ex_next;
        ex_mem_current = ex_mem_next;
        mem_wb_current = mem_wb_next;

        //Increment program counter
        PC.update(nextPC);

        // Keep zero register hardwired to 0
        RegFile.write(0, 0, true);

        i++;
        
    } // end of while loop

    cout << "\nTotal iterations: " << iterations << endl;
    cout << "IMem size in bytes: " << IMem.get_size() << endl;
    cout << "Expected iterations: " << IMem.get_size() / 4 << endl << endl;

    RegFile.print_registers();

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