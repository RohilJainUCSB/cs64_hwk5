#include <iostream>     // for use of cin, cout, endl
#include <string>       // for use of strings
#include <cmath>        // for use of pow(x,y) function
// NO OTHER LIBRARIES ARE ALLOWED!

using namespace std;

//Helper function to return the register name based on its binary val
string binToReg(int reg)
{
    switch (reg)
    {
        case 8:
            return "t0";
        case 9:
            return "t1";
        case 10:
            return "t2";
        case 11:
            return "t3";
        case 12:
            return "t4";
        case 13:
            return "t5";
        case 14:
            return "t6";
        case 15:
            return "t7";

        case 16:
            return "s0";
        case 17:
            return "s1";
        case 18:
            return "s2";
        case 19:
            return "s3";
        case 20:
            return "s4";
        case 21:
            return "s5";
        case 22:
            return "s6";
        case 23:
            return "s7";
    }
    return "";
}


// function: disassemble takes in a string representing
//          an assembled MIPS instruction as a string
//          and returns the instruction itself
//
//          Level 1 difficulty: assume the input is:
//          a) legitimate (an actual MIPS instruction)
//          b) is ONLY an I-type and ONLY one of: addi, addiu, andi, ori, slti
//          c) has only registers $t0 thru $t7 or $s0 thru $s7 in the instruction
//
string disassemble( string hex ) {

    // You want to retrieve all the separate fields of an I-type instruction
    //      to help you figure out what the assembly instruction is.
    //
    // HINT: Use bitwise masking and bit-shifting to isolate the different parts of the hex instruction!
    //
    // YOUR CODE GOES HERE!!
    //Citing a helpful resource used: https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c
    int hexToDec = 0;
    int positionInHex = hex.size();
    //Convert the hex string into a decimal value stored as int so that bitwise manipulation can be done to it
    for(char c: hex)
    {
        positionInHex --;
        //Citing a helpful resource used: https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c
        switch(c)
        {
            case 'A':
                hexToDec += 10 * pow(16, positionInHex);
                break;
            case 'B':
                hexToDec += 11 * pow(16, positionInHex);
                break;
            case 'C':
                hexToDec += 12 * pow(16, positionInHex);
                break;
            case 'D':
                hexToDec += 13 * pow(16, positionInHex);
                break;
            case 'E':
                hexToDec += 14 * pow(16, positionInHex);
                break;
            case 'F':
                hexToDec += 15 * pow(16, positionInHex);
                break;
            default:
                //If it is numerical, simply cast to int and add the val multiplied by 16^pos
                hexToDec += ((int)c - '0') * pow(16, positionInHex);
                break;
        }
    }
    //Now hexToDec stores the integer value of the hex string
    //opcode is the 6 most significant bits (shift right 26 times)
    int opcode = hexToDec >> 26;
    //rt is the 5 msb after rs. shift these 5 to lsb position and use and-mask of 2^5-1 (6 1's)
    int rt = (hexToDec >> 16) & ((int)pow(2, 5) - 1);
    //rs is the 5 msb after opcode. shift these 5 to lsb position and use and-mask of 2^5-1 (6 1's)
    int rs = (hexToDec >> 21) & ((int)pow(2, 5) - 1);
    //immediate is the first 16 bits which can be isolated by fully arithmetic shifting front and back
    int immediate = (hexToDec << 16) >> 16;

    string result = "";
    //Begin with adding in the opcode
    switch(opcode)
    {
        case 8:
            result += "addi";
            break;
        case 9:
            result += "addiu";
            break;
        case 12:
            result += "andi";
            break;
        case 13:
            result += "ori";
            break;
        case 10:
            result += "slti";
            break;
    }
    result += " $";
    //Add in the rt
    result += binToReg(rt);
    result += ", $";
    //Add in the rs
    result += binToReg(rs);
    result += ", ";
    result += to_string(immediate);
    return result;
}

int main() {
// Don't change any code in main() function!!

    string hex, inst;
    
    cout << "Enter your assembled instruction as a hex number: 0x";
    cin >> hex;
    
    inst = disassemble( hex );
    cout << "Your instruction is:\n" << inst << endl;

    return 0;
}
