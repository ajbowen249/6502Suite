#pragma once
#include "MotherBoard.h"

class Core6502 {
	MotherBoard* _mobo;

	//6502 Registers
	byte A; //Accumulator
	byte X; //X index
	byte Y; //Y index
	byte StP; //Stack Pointer
	byte PC[2]; //Program Counter
	byte N; //N flag
	byte Z; //Z flag
	byte B; //B flag
	byte C; //C flag
	byte I; //I flag
	byte D; //D flag
	byte V; //V flag

	//containter for current instruction
	//some instructions are 2 or 3 bytes
	byte instruction[3];

	//container for the currently-pointed-to address
	byte address[2];

	//should the menu be brought up
	bool menuFlagged = false;

    byte fetchAndIncrement();
	void decodeAndExecute();
	void getAddress();
	byte getOperand();
    bool detectRollover(byte byte1, byte byte2);
    void branch();
    void push(byte value);
    byte pop();

    void I_BPL();
    void I_BMI();
    void I_BVC();
    void I_BVS();
    void I_BCC();
    void I_BCS();
    void I_BNE();
    void I_BEQ();
    void I_BRK();
    void I_JSR();
    void I_RTI();
    void I_RTS();
    void I_PHP();
    void I_PLP();
    void I_PHA();
    void I_PLA();
    void I_DEY();
    void I_TAY();
    void I_INX();
    void I_INY();
    void I_CLC();
    void I_SEC();
    void I_CLI();
    void I_SEI();
    void I_TYA();
    void I_CLV();
    void I_CLD();
    void I_SED();
    void I_TXA();
    void I_TXS();
    void I_TAX();
    void I_TSX();
    void I_DEX();
    void I_NOP();
    void I_ORA();
    void I_AND();
    void I_EOR();
    void I_ADC();
    void I_STA();
    void I_LDA();
    void I_CMP();
    void I_SBC();
    void I_ASL(bool isAccAddress);
    void I_ROL(bool isAccAddress);
    void I_LSR(bool isAccAddress);
    void I_ROR(bool isAccAddress);
    void I_STX();
    void I_LDX();
    void I_DEC();
    void I_INC();
    void I_BIT();
    void I_JMP(bool isAbsolute);
    void I_STY();
    void I_LDY();
    void I_CPY();
    void I_CPX();
public:
    //Vector table constants
    //defining these here so they can be
    //changed if needed for debugging
    static const byte NMI_HI[2];
    static const byte NMI_LO[2];
    static const byte RESET_HI[2];
    static const byte RESET_LO[2];
    static const byte IRQ_BRK_HI[2];
    static const byte IRQ_BRK_LO[2];

    Core6502(MotherBoard* mobo);
	void iterate();
	void reset();
};