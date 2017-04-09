#include "Core6502.h"
const byte Core6502::NMI_HI[2] = {
    0xFF, 0xFB };
const byte Core6502::NMI_LO[2] = {
    0xFF, 0xFA };

const byte Core6502::RESET_HI[2] = {
    0xFF, 0xFD };
const byte Core6502::RESET_LO[2] = {
    0xFF, 0xFC };

const byte Core6502::IRQ_BRK_HI[2] = {
    0xFF, 0xFF };
const byte Core6502::IRQ_BRK_LO[2] = {
    0xFF, 0xFE };

Core6502::Core6502(MotherBoard* mobo)
    : _mobo(mobo) {
}

void Core6502::iterate() {
    instruction[0] = fetchAndIncrement();
    decodeAndExecute();
}

byte Core6502::fetchAndIncrement() {
    byte inst = _mobo->readMemory(PC[0], PC[1]);

    if (PC[1] == 0xFF) {
        ++PC[0];
    }

    ++PC[1];

    return inst;
}

void Core6502::reset() {
    //load up the starting program address from memory
    PC[0] = _mobo->readMemory(RESET_HI[0], RESET_HI[1]);
    PC[1] = _mobo->readMemory(RESET_LO[0], RESET_LO[1]);

    //set up the status register
    I = 0x01;
    D = 0x00;

    //reset the stack ponter
    StP = 0xFF;
}

void Core6502::decodeAndExecute() {
    //these instructions don't fit a defined pattern
    switch (instruction[0]) {
        //branching instructions
    case 0x10: I_BPL();  return;
    case 0x30: I_BMI(); return;
    case 0x50: I_BVC(); return;
    case 0x70: I_BVS(); return;
    case 0x90: I_BCC(); return;
    case 0xB0: I_BCS(); return;
    case 0xD0: I_BNE(); return;
    case 0xF0: I_BEQ(); return;

        //interrupt and subroutine instructions
    case 0x00: I_BRK(); return;
    case 0x20: I_JSR(); return;
    case 0x40: I_RTI(); return;
    case 0x60: I_RTS(); return;

        //other instructions
    case 0x08: I_PHP(); return;
    case 0x28: I_PLP(); return;
    case 0x48: I_PHA(); return;
    case 0x68: I_PLA(); return;
    case 0x88: I_DEY(); return;
    case 0xA8: I_TAY(); return;
    case 0xC8: I_INY(); return;
    case 0xE8: I_INX(); return;

    case 0x18: I_CLC(); return;
    case 0x38: I_SEC(); return;
    case 0x58: I_CLI(); return;
    case 0x78: I_SEI(); return;
    case 0x98: I_TYA(); return;
    case 0xB8: I_CLV(); return;
    case 0xD8: I_CLD(); return;
    case 0xF8: I_SED(); return;

    case 0x8A: I_TXA(); return;
    case 0x9A: I_TXS(); return;
    case 0xAA: I_TAX(); return;
    case 0xBA: I_TSX(); return;
    case 0xCA: I_DEX(); return;
    case 0xEA: I_NOP(); return;
    }

    //the method for decoding the remaining instructions
    //is inspired by the breakdown provided at
    //http://www.llx.com/~nparker/a2/opcodes.html
    byte opcode = instruction[0] & 0xE0;
    byte addressMode = instruction[0] & 0x1C;
    byte instructionType = instruction[0] & 0x03;

    if (instructionType == 0x01) {
        switch (opcode) {
        case 0x00: I_ORA(); return;
        case 0x20: I_AND(); return;
        case 0x40: I_EOR(); return;
        case 0x60: I_ADC(); return;
        case 0x80: I_STA(); return;
        case 0xA0: I_LDA(); return;
        case 0xC0: I_CMP(); return;
        case 0xE0: I_SBC(); return;
        }
    } else if (instructionType == 0x02) {
        switch (opcode) {
        case 0x00: I_ASL(addressMode == 0x08); return;
        case 0x20: I_ROL(addressMode == 0x08); return;
        case 0x40: I_LSR(addressMode == 0x08); return;
        case 0x60: I_ROR(addressMode == 0x08); return;
        case 0x80: I_STX(); return;
        case 0xA0: I_LDX(); return;
        case 0xC0: I_DEC(); return;
        case 0xE0: I_INC(); return;
        }
    } else if (instructionType == 0x00) {
        switch (opcode) {
        case 0x20: I_BIT(); return;
        case 0x40: I_JMP(true); return;
        case 0x60: I_JMP(false); return;
        case 0x80: I_STY(); return;
        case 0xA0: I_LDY(); return;
        case 0xC0: I_CPY(); return;
        case 0xE0: I_CPX(); return;
        }
    }
}

void Core6502::getAddress() {
    byte addressMode = instruction[0] & 0x1C;
    byte instructionType = instruction[0] & 0x03;

    if (instructionType == 0x01) {
        instruction[1] = fetchAndIncrement();

        if (addressMode == 0x0C ||
            addressMode == 0x18 ||
            addressMode == 0x1C) {
            instruction[2] = fetchAndIncrement();
        }

        byte baseLSB;
        byte baseMSB;

        switch (addressMode) { //Indexed Indirect 
        case 0x00:
            baseLSB = _mobo->readMemory(0x00, instruction[1] + X);
            baseMSB = _mobo->readMemory(0x00, instruction[1] + X + 1);
            address[0] = baseMSB;
            address[1] = baseLSB;
            break;
            //zero page
        case 0x04:
            address[0] = 0x00;
            address[1] = instruction[1];
            break;
            //absolute
        case 0x0C:
            address[0] = instruction[2];
            address[1] = instruction[1];
            break;
            //Indirect Indexed
        case 0x10:
            baseLSB = _mobo->readMemory(0x00, instruction[1]);
            baseMSB = _mobo->readMemory(0x00, instruction[1] + 1);
            if (detectRollover(baseLSB, Y)) ++baseMSB;
            baseLSB += Y;
            address[0] = baseMSB;
            address[1] = baseLSB;
            break;
            //zero page, X
        case 0x14:
            address[0] = 0x00;
            address[1] = instruction[1] + X;
            break;
            //absolute, Y
        case 0x18:
            address[0] = instruction[2];
            address[1] = instruction[1] + Y;
            if (detectRollover(instruction[1], Y)) ++address[0];
            break;
            //absolute, X
        case 0x1C:
            address[0] = instruction[2];
            address[1] = instruction[1] + X;
            if (detectRollover(instruction[1], X)) ++address[0];
            break;
        }
    } else if (instructionType == 0x02 || instructionType == 0x00) {
        instruction[1] = fetchAndIncrement();
        byte opcode = (instruction[0] & 0x1C);
        byte offset;
        if (opcode == 0x96 || opcode == 0xB6 || opcode == 0xBE) {
            offset = Y;
        } else {
            offset = X;
        }

        if (addressMode == 0x0C ||
            addressMode == 0x18 ||
            addressMode == 0x1C) {
            instruction[2] = fetchAndIncrement();
        }

        switch (addressMode) { //zero page
        case 0x04:
            address[0] = 0x00;
            address[1] = instruction[1];
            break;
            //absolute
        case 0x0C:
            address[0] = instruction[2];
            address[1] = instruction[1];
            break;
            //zero page, X/Y
        case 0x14:
            address[0] = 0x00;
            address[1] = instruction[1] + offset;
            break;
            //absolute, X/Y
        case 0x1C:
            address[0] = instruction[2];
            address[1] = instruction[1] + offset;
            if (detectRollover(instruction[1], offset)) ++address[0];
            break;
        }
    }
}

byte Core6502::getOperand() {
    byte addressMode = instruction[0] & 0x1C;
    byte instructionType = instruction[0] & 0x03;
    getAddress();

    if (instructionType == 0x01) {
        if (addressMode == 0x08) {
            return instruction[1];
        } else {
            return _mobo->readMemory(address[0], address[1]);
        }
    } else if (instructionType == 0x02 || instructionType == 0x00) {
        if (addressMode == 0x00) {
            return instruction[1];
        } else {
            return _mobo->readMemory(address[0], address[1]);
        }
    }
}

bool Core6502::detectRollover(byte byte1, byte byte2) {
    byte result = byte1 + byte2;
    return result < byte1;
}

void Core6502::branch() {
    if (instruction[1] & 0x80) {
        byte negOffset = (byte)((~instruction[1]) + 1);
        if (negOffset > PC[1]) --PC[0];
        PC[1] -= negOffset;
    } else {
        if (detectRollover(PC[1], instruction[1])) ++PC[0];
        PC[1] += instruction[1];
    }
}

void Core6502::push(byte value) {
    _mobo->writeMemory(0x01, StP, value);
    --StP;
}

byte Core6502::pop() {
    ++StP;
    return _mobo->readMemory(0x01, StP);
}

//implementation of the actual CPU instructions
void Core6502::I_BPL() {
    instruction[1] = fetchAndIncrement();
    if (!(N)) branch();
}

void Core6502::I_BMI() {
    instruction[1] = fetchAndIncrement();
    if (N) branch();
}

void Core6502::I_BVC() {
    instruction[1] = fetchAndIncrement();
    if (!(V)) branch();
}

void Core6502::I_BVS() {
    instruction[1] = fetchAndIncrement();
    if (V) branch();
}

void Core6502::I_BCC() {
    instruction[1] = fetchAndIncrement();
    if (!(C)) branch();
}

void Core6502::I_BCS() {
    instruction[1] = fetchAndIncrement();
    if (C) branch();
}

void Core6502::I_BNE() {
    instruction[1] = fetchAndIncrement();
    if (!(Z)) branch();
}

void Core6502::I_BEQ() {
    instruction[1] = fetchAndIncrement();
    if (Z) branch();
}

void Core6502::I_BRK() {
    fetchAndIncrement();

    push(PC[0]);
    push(PC[1]);

    I_PHP();

    I = 1;

    PC[0] = _mobo->readMemory(IRQ_BRK_HI[0], IRQ_BRK_HI[1]);
    PC[0] = _mobo->readMemory(IRQ_BRK_LO[0], IRQ_BRK_LO[1]);
}

void Core6502::I_JSR() {
    instruction[1] = fetchAndIncrement();
    instruction[2] = fetchAndIncrement();

    push(PC[0]);
    push(PC[1]);

    PC[1] = instruction[1];
    PC[0] = instruction[2];
}

void Core6502::I_RTI() {
    byte stat = pop();
    N = !((stat & 0x80) == 0);
    V = !((stat & 0x40) == 0);
    B = !((stat & 0x10) == 0);
    D = !((stat & 0x08) == 0);
    I = !((stat & 0x04) == 0);
    Z = !((stat & 0x02) == 0);
    C = !((stat & 0x01) == 0);

    PC[1] = pop();
    PC[0] = pop();
}

void Core6502::I_RTS() {
    PC[1] = pop();
    PC[0] = pop();
}

void Core6502::I_PHP() {
    byte stat = 0x00;
    if (N) stat |= 0x80;
    if (V) stat |= 0x40;
    if (B) stat |= 0x10;
    if (D) stat |= 0x08;
    if (I) stat |= 0x04;
    if (Z) stat |= 0x02;
    if (C) stat |= 0x01;

    push(stat);
}

void Core6502::I_PLP() {
    byte stat = pop();
    N = !((stat & 0x80) == 0);
    V = !((stat & 0x40) == 0);
    B = !((stat & 0x10) == 0);
    D = !((stat & 0x08) == 0);
    I = !((stat & 0x04) == 0);
    Z = !((stat & 0x02) == 0);
    C = !((stat & 0x01) == 0);
}

void Core6502::I_PHA() {
    push(A);
}

void Core6502::I_PLA() {
    A = pop();

    N = ((A & 0x80) == 0x80);
    Z = (A == 0);
}

void Core6502::I_DEY() {
    --Y;

    N = ((Y & 0x80) == 0x80);
    Z = (Y == 0);
}

void Core6502::I_TAY() {
    Y = A;

    N = ((Y & 0x80) == 0x80);
    Z = (Y == 0);
}

void Core6502::I_INX() {
    ++X;

    N = ((X & 0x80) == 0x80);
    Z = (X == 0);
}

void Core6502::I_INY() {
    ++Y;

    N = ((Y & 0x80) == 0x80);
    Z = (Y == 0);
}

void Core6502::I_CLC() {
    C = 0;
}

void Core6502::I_SEC() {
    C = 1;
}

void Core6502::I_CLI() {
    I = 0;
}

void Core6502::I_SEI() {
    I = 1;
}

void Core6502::I_TYA() {
    A = Y;

    N = ((A & 0x80) == 0x80);
    Z = (A == 0);
}

void Core6502::I_CLV() {
    V = 0;
}

void Core6502::I_CLD() {
    D = 0;
}

void Core6502::I_SED() {
    D = 1;
}

void Core6502::I_TXA() {
    A = X;

    N = ((A & 0x80) == 0x80);
    Z = (A == 0);
}

void Core6502::I_TXS() {
    StP = X;
}

void Core6502::I_TAX() {
    X = A;

    N = ((X & 0x80) == 0x80);
    Z = (X == 0);
}

void Core6502::I_TSX() {
    X = StP;

    N = ((X & 0x80) == 0x80);
    Z = (X == 0);
}

void Core6502::I_DEX() {
    --X;

    N = ((X & 0x80) == 0x80);
    Z = (X == 0);
}

void Core6502::I_NOP() {
    //literally do nothing
}

void Core6502::I_ORA() {
    byte operand = getOperand();
    A |= operand;

    N = ((A & 0x80) == 0x80);
    Z = (A == 0);
}

void Core6502::I_AND() {
    byte operand = getOperand();
    A &= operand;

    N = ((A & 0x80) == 0x80);
    Z = (A == 0);
}

void Core6502::I_EOR() {
    byte operand = getOperand();
    A ^= operand;

    N = ((A & 0x80) == 0x80);
    Z = (A == 0);
}

void Core6502::I_ADC() {
    byte operand = getOperand();
    byte result = A + operand;
    if (C) ++result;

    N = ((result & 0x80) == 0x80);
    Z = (result == 0);
    C = detectRollover(A, operand);

    //if the signs of A and the operand were the same,
    //but the result's is different, there is overflow
    byte ASign = (A & 0x80);
    byte oSign = (operand & 0x80);
    if (ASign == oSign) {
        byte resultSign = (result & 0x80);
        V = (resultSign != oSign);
    } else {
        V = 0;
    }

    A = result;
}

void Core6502::I_STA() {
    getAddress();
    _mobo->writeMemory(address[0], address[1], A);
}

void Core6502::I_LDA() {
    A = getOperand();

    N = ((A & 0x80) == 0x80);
    Z = (A == 0);
}

void Core6502::I_CMP() {
    byte operand = getOperand();
    byte result = A - operand;

    N = ((result & 0x80) == 0x80);
    Z = (A == operand);
    C = (A >= operand);
}

void Core6502::I_SBC() {
    byte operand = getOperand();

    operand = ~operand;
    if (C) operand++;
    byte result = A + operand;

    N = ((result & 0x80) == 0x80);
    Z = (result == 0);

    C = detectRollover(A, operand) || ((A == operand) && C);

    //if the signs of A and the operand were the same,
    //but the result's is different, there is overflow
    byte ASign = (A & 0x80);
    byte oSign = (operand & 0x80);
    if (ASign == oSign) {
        byte resultSign = (result & 0x80);
        V = (resultSign != oSign);
    } else {
        V = 0;
    }

    A = result;
}

void Core6502::I_ASL(bool isAccAddress) {
    byte operand = (isAccAddress) ? A : getOperand();

    byte MSB = operand & 0x80;
    C = (MSB != 0);

    operand <<= 1;
    operand &= 0xFE;

    N = ((operand & 0x80) == 0x80);
    Z = (operand == 0);

    if (isAccAddress) {
        A = operand;
    } else {
        _mobo->writeMemory(address[0], address[1], operand);
    }
}

void Core6502::I_ROL(bool isAccAddress) {
    byte operand = (isAccAddress) ? A : getOperand();

    byte MSB = operand & 0x80;
    bool setLSB = C;
    C = (MSB != 0);

    operand <<= 1;

    if (setLSB) {
        operand |= 0x01;
    } else {
        operand &= 0xFE;
    }

    N = ((operand & 0x80) == 0x80);
    Z = (operand == 0);

    if (isAccAddress) {
        A = operand;
    } else {
        _mobo->writeMemory(address[0], address[1], operand);
    }
}

void Core6502::I_LSR(bool isAccAddress) {
    byte operand = (isAccAddress) ? A : getOperand();

    byte LSB = operand & 0x01;
    C = (LSB != 0);

    operand >>= 1;
    operand &= 0x7F;

    N = ((operand & 0x80) == 0x80);
    Z = (operand == 0);

    if (isAccAddress) {
        A = operand;
    } else {
        _mobo->writeMemory(address[0], address[1], operand);
    }
}

void Core6502::I_ROR(bool isAccAddress) {
    byte operand = (isAccAddress) ? A : getOperand();

    byte LSB = operand & 0x01;
    bool setMSB = C;
    C = (LSB != 0);

    operand >>= 1;

    if (setMSB) {
        operand |= 0x80;
    } else {
        operand &= 0x7F;
    }

    N = ((operand & 0x80) == 0x80);
    Z = (operand == 0);

    if (isAccAddress) {
        A = operand;
    } else {
        _mobo->writeMemory(address[0], address[1], operand);
    }
}

void Core6502::I_STX() {
    getAddress();
    _mobo->writeMemory(address[0], address[1], X);
}

void Core6502::I_LDX() {
    X = getOperand();

    N = ((X & 0x80) == 0x80);
    Z = (X == 0);
}

void Core6502::I_DEC() {
    byte operand = getOperand();
    --operand;

    N = ((operand & 0x80) == 0x80);
    Z = (operand == 0);

    _mobo->writeMemory(address[0], address[1], operand);
}

void Core6502::I_INC() {
    byte operand = getOperand();
    ++operand;

    N = ((operand & 0x80) == 0x80);
    Z = (operand == 0);

    _mobo->writeMemory(address[0], address[1], operand);
}

void Core6502::I_BIT() {
    byte operand = getOperand();
    Z = ((operand & A) == 0);

    N = ((operand & 0x80) == 0x80);
    V = ((operand & 0x40) == 0x40);
}

void Core6502::I_JMP(bool isAbsolute) {
    getAddress();
    if (!isAbsolute) {
        byte addressHigh = _mobo->readMemory(address[0], address[1] + 1);
        byte addressLow = _mobo->readMemory(address[0], address[1]);

        address[0] = addressHigh;
        address[1] = addressLow;
    }

    PC[0] = address[0];
    PC[1] = address[1];
}

void Core6502::I_STY() {
    getAddress();
    _mobo->writeMemory(address[0], address[1], Y);
}

void Core6502::I_LDY() {
    Y = getOperand();

    N = ((Y & 0x80) == 0x80);
    Z = (Y == 0);
}

void Core6502::I_CPY() {
    byte operand = getOperand();
    byte result = Y - operand;

    N = ((result & 0x80) == 0);
    Z = (Y == operand);
    C = (operand >= Y);
}

void Core6502::I_CPX() {
    byte operand = getOperand();
    byte result = X - operand;

    N = ((result & 0x80) == 0);
    Z = (X == operand);
    C = (operand >= X);
}
