/***************************************************************************
 * file name   : asm_parser.c                                              *
 * author      : Mohamed Sanogho                                           *
 * description : the functions are declared in asm_parser.h                *
 *               The intention of this library is to parse a .ASM file     *
 *			        										               *
 *                                                                         *
 ***************************************************************************
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asm_parser.h"

/* to do - implement all the functions in asm_parser.h */
int read_asm_file(char* filename, char program [ROWS][COLS] ) {

    /* opening filename */
    FILE *asmFile;
    asmFile = fopen(filename, "r");

    /* testing whether the file opened; if it didn't, program alerts user */
    if(asmFile == NULL) {
        printf("\nerror2: read_asm_file() failed.\n");
        return 2;
    }

    /* streaming in the strings from the input file until we hit
     * EOF
     * */
    char currtRow[COLS];
    int row = 0;
    int i;

    while (!feof(asmFile)) {

        /* Feeding program[][] row by row */
        fgets(currtRow, COLS, asmFile);

        int l = strlen(currtRow);
        for(i = 0; i < l; i++) program[row][i] = currtRow[i];

        /* changing potential carriage return with NULL */
        if(program[row][i - 1] == '\n') program[row][i - 1] = '\0';
        else program[row][i] = '\0';

        row++;
    }

    program[row][0] = '\0';

    /* Closing the input file */
    fclose(asmFile);

    return 0;
}


int parse_instruction (char* instr, char* instr_bin_str ) {
    /* Saving the string pointed by instr from strtok() */
    char * instrTemp = calloc(strlen(instr) + 1, sizeof(char));
    strcpy(instrTemp, instr);

    /* Making sure that calloc succeeded */
    if(instrTemp == NULL) {
        return 3;
        fprintf(stderr, "\nerror3: parse_instruction() failed.\n");
    }

    /* Tokenizing row to detect opcode and call related parse function */
    char * opcodeToken = strtok(instrTemp, " ");

    if (strcmp(opcodeToken, "ADD") == 0) parse_add(instr, instr_bin_str);
    else if (strcmp(opcodeToken, "MUL") == 0) parse_mul(instr, instr_bin_str);
    else if (strcmp(opcodeToken, "SUB") == 0) parse_sub(instr, instr_bin_str);
    else if (strcmp(opcodeToken, "DIV") == 0) parse_div(instr, instr_bin_str);
    else if (strcmp(opcodeToken, "AND") == 0) parse_and(instr, instr_bin_str);
    else if (strcmp(opcodeToken, "OR") == 0) parse_or(instr, instr_bin_str);
    else if (strcmp(opcodeToken, "XOR") == 0) parse_xor(instr, instr_bin_str);

    /* In case of any error */
    else{
        return 3;
        printf("\nerror3: parse_instruction() failed.\n");
    }

    free(instrTemp);
    return 0;
}


int parse_add(char* instr, char* instr_bin_str ) {

    /*copying opcode */
    strcpy(instr_bin_str, "0001");

    /* Saving the string pointed by instr from strtok() */
    char * instrTemp1 = calloc(strlen(instr) + 1, sizeof(char));
    strcpy(instrTemp1, instr);

    /* Making sure that calloc succeeded */
    if(instrTemp1 == NULL) {
        return 4;
        fprintf(stderr, "\nerror4: parse_add() failed.\n");
    }

    /* Tokenizing row to detect registers */
    char * regToken = strtok(instrTemp1, " ");

    /* moving to registers string area */
    regToken = strtok(NULL, " ");

    /* Fetching registers Rd and Rs */
    for (int i = 0; i < 2; i++) {
        if (regToken[0] == 'R') parse_reg(regToken[1], instr_bin_str);

        /* In case of any error */
        else {
            return 4;
            fprintf(stderr, "\nerror4: parse_add() failed.\n");
        }
        regToken = strtok(NULL, " ");
    }
    /* Inserting sub-opcode */
    strcat(instr_bin_str, "000");

    /* Fetching register Rt */
    parse_reg(regToken[1], instr_bin_str);

    free(instrTemp1);
    return 0;
}


int parse_mul(char* instr, char* instr_bin_str ) {

    /*copying opcode */
    strcpy(instr_bin_str, "0001");

    /* Saving the string pointed by instr from strtok() */
    char * instrTemp2 = calloc(strlen(instr) + 1, sizeof(char));
    strcpy(instrTemp2, instr);

    /* Making sure that calloc succeeded */
    if(instrTemp2 == NULL) {
        return 4;
        fprintf(stderr, "\nerror4: parse_mul() failed.\n");
    }

    /* Tokenizing row to detect registers */
    char * regToken1 = strtok(instrTemp2, " ");

    /* moving to registers string area */
    regToken1 = strtok(NULL, " ");

    /* Fetching registers Rd and Rs */
    for (int i = 0; i < 2; i++) {

        if (regToken1[0] == 'R') parse_reg(regToken1[1], instr_bin_str);

        /* In case of any error */
        else {
            return 4;
            fprintf(stderr, "\nerror4: parse_mul() failed.\n");
        }

        regToken1 = strtok(NULL, " ");
    }

    /* Inserting sub-opcode */
    strcat(instr_bin_str, "001");

    /* Fetching register Rt */
    parse_reg(regToken1[1], instr_bin_str);

    free(instrTemp2);
    return 0;
}

int parse_sub(char* instr, char* instr_bin_str ) {

    /*copying opcode */
    strcpy(instr_bin_str, "0001");

    /* Saving the string pointed by instr from strtok() */
    char * instrTemp3 = calloc(strlen(instr) + 1, sizeof(char));
    strcpy(instrTemp3, instr);

    /* Making sure that calloc succeeded */
    if(instrTemp3 == NULL) {
        return 4;
        fprintf(stderr, "\nerror4: parse_sub() failed.\n");
    }

    /* Tokenizing row to detect registers */
    char * regToken2 = strtok(instrTemp3, " ");

    /* moving to registers string area */
    regToken2 = strtok(NULL, " ");

    /* Fetching registers Rd and Rs */
    for (int i = 0; i < 2; i++) {

        if (regToken2[0] == 'R') parse_reg(regToken2[1], instr_bin_str);

        /* In case of any error */
        else {
            return 4;
            fprintf(stderr, "\nerror4: parse_sub() failed.\n");
        }

        regToken2 = strtok(NULL, " ");
    }

    /* Inserting sub-opcode */
    strcat(instr_bin_str, "010");

    /* Fetching register Rt */
    parse_reg(regToken2[1], instr_bin_str);

    free(instrTemp3);
    return 0;
}


int parse_div(char* instr, char* instr_bin_str ) {

    /*copying opcode */
    strcpy(instr_bin_str, "0001");

    /* Saving the string pointed by instr from strtok() */
    char * instrTemp4 = calloc(strlen(instr) + 1, sizeof(char));
    strcpy(instrTemp4, instr);

     /* Making sure that calloc succeeded */
    if(instrTemp4 == NULL) {
        return 4;
        fprintf(stderr, "\nerror4: parse_div() failed.\n");
    }

    /* Tokenizing row to detect registers */
    char * regToken3 = strtok(instrTemp4, " ");

    /* moving to registers string area */
    regToken3 = strtok(NULL, " ");

    /* Fetching registers Rd and Rs */
    for (int i = 0; i < 2; i++) {

        if (regToken3[0] == 'R') parse_reg(regToken3[1], instr_bin_str);

        /* In case of any error */
        else {
            return 4;
            fprintf(stderr, "\nerror4: parse_div() failed.\n");
        }

        regToken3 = strtok(NULL, " ");

    }

    /* Inserting sub-opcode */
    strcat(instr_bin_str, "011");

    /* Fetching register Rt */
    parse_reg(regToken3[1], instr_bin_str);

    free(instrTemp4);
    return 0;
}


int parse_and(char* instr, char* instr_bin_str ) {

    /*copying opcode */
    strcpy(instr_bin_str, "0101");

    /* Saving the string pointed by instr from strtok() */
    char * instrTemp5 = calloc(strlen(instr) + 1, sizeof(char));
    strcpy(instrTemp5, instr);

    /* Making sure that calloc succeeded */
    if(instrTemp5 == NULL) {
        return 4;
        fprintf(stderr, "\nerror4: parse_and() failed.\n");
    }

    /* Tokenizing row to detect registers */
    char * regToken4 = strtok(instrTemp5, " ");

    /* moving to registers string area */
    regToken4 = strtok(NULL, " ");

    /* Fetching registers Rd and Rs */
    for (int i = 0; i < 2; i++) {

        if (regToken4[0] == 'R') parse_reg(regToken4[1], instr_bin_str);

        /* In case of any error */
        else {
            return 4;
            fprintf(stderr, "\nerror4: parse_and() failed.\n");
        }

        regToken4 = strtok(NULL, " ");
    }

    /* Inserting sub-opcode */
    strcat(instr_bin_str, "000");

    /* Fetching register Rt */
    parse_reg(regToken4[1], instr_bin_str);

    free(instrTemp5);
    return 0;
}


int parse_or(char* instr, char* instr_bin_str ) {

    /*copying opcode */
    strcpy(instr_bin_str, "0101");

    /* Saving the string pointed by instr from strtok() */
    char * instrTemp6 = calloc(strlen(instr) + 1, sizeof(char));
    strcpy(instrTemp6, instr);

     /* Making sure that calloc succeeded */
    if(instrTemp6 == NULL) {
        return 4;
        fprintf(stderr, "\nerror4: parse_or() failed.\n");
    }

    /* Tokenizing row to detect registers */
    char * regToken5 = strtok(instrTemp6, " ");

    /* moving to registers string area */
    regToken5 = strtok(NULL, " ");

    /* Fetching registers Rd and Rs */
    for (int i = 0; i < 2; i++) {

        if (regToken5[0] == 'R') parse_reg(regToken5[1], instr_bin_str);

        /* In case of any error */
        else {
            return 4;
            fprintf(stderr, "\nerror4: parse_or() failed.\n");
        }

        regToken5 = strtok(NULL, " ");
    }

    /* Inserting sub-opcode */
    strcat(instr_bin_str, "010");

    /* Fetching register Rt */
    parse_reg(regToken5[1], instr_bin_str);

    free(instrTemp6);
    return 0;
}

int parse_xor(char* instr, char* instr_bin_str ) {

    /*copying opcode */
    strcpy(instr_bin_str, "0101");

    /* Saving the string pointed by instr from strtok() */
    char * instrTemp7 = calloc(strlen(instr) + 1, sizeof(char));
    strcpy(instrTemp7, instr);

     /* Making sure that calloc succeeded */
    if(instrTemp7 == NULL) {
        return 4;
        fprintf(stderr, "\nerror4: parse_xor() failed.\n");
    }

    /* Tokenizing row to detect registers */
    char * regToken6 = strtok(instrTemp7, " ");

    /* moving to registers string area */
    regToken6 = strtok(NULL, " ");

    /* Fetching registers Rd and Rs */
    for (int i = 0; i < 2; i++) {

        if (regToken6[0] == 'R') parse_reg(regToken6[1], instr_bin_str);

        /* In case of any error */
        else {
            return 4;
            fprintf(stderr, "\nerror4: parse_xor() failed.\n");
        }

        regToken6 = strtok(NULL, " ");
    }

    /* Inserting sub-opcode */
    strcat(instr_bin_str, "011");

    /* Fetching register Rt */
    parse_reg(regToken6[1], instr_bin_str);

    free(instrTemp7);
    return 0;
}


int parse_reg(char reg_num, char* instr_bin_str) {

    /* Testing out register number */
    switch (reg_num) {

    /* Pulling register numbers in binary forms */
    case '0':
    strcat(instr_bin_str, "000");
    return 0;
    break;

    case '1':
    strcat(instr_bin_str, "001");
    return 0;
    break;

    case '2':
    strcat(instr_bin_str, "010");
    return 0;
    break;

    case '3':
    strcat(instr_bin_str, "011");
    return 0;
    break;

    case '4':
    strcat(instr_bin_str, "100");
    return 0;
    break;

    case '5':
    strcat(instr_bin_str, "101");
    return 0;
    break;

    case '6':
    strcat(instr_bin_str, "110");
    return 0;
    break;

    case '7':
    strcat(instr_bin_str, "111");
    return 0;
    break;

    /* In case of any error */
    default:
        return 5;
        fprintf(stderr, "\nerror5: parse_reg() failed.\n");

    }
}

unsigned short int str_to_bin (char* instr_bin_str) {
    unsigned short int xBin = 0;
    long ret;
    char* ptr;

    /* Converting string-format binary numbers */
    ret = strtol (instr_bin_str, &ptr, 2);

    /* In case of any error */
    if (ret == 0) {
        return 6;
        fprintf(stderr, "\nerror6: str_to_bin() failed.\n");
    }

    /* explicit casting  */
    xBin = (unsigned short) ret;

    return xBin;
}


int write_obj_file(char* filename, unsigned short int program_bin[ROWS]) {

    /* Saving the string pointed by filename from strtok() */
    char * objFilename = calloc(strlen(filename) + 1, sizeof(char));
    strcpy(objFilename, filename);

    /* Making sure that calloc succeeded */
    if(objFilename == NULL) {
        return 7;
        fprintf(stderr, "\nerror7: write_obj_file() failed.\n");
    }

    /* Changing last three letters in filename to "obj" */
    objFilename = strtok(objFilename, ".");
    strcat(objFilename, ".obj");

    /* Opening filename for writing and in binary form */
    FILE * hexFile = fopen(objFilename, "wb");

    /* testing whether the file opened; if it didn't, program alerts user */
    if(hexFile == NULL) {
        return 7;
        fprintf(stderr, "\nerror7: write_obj_file() failed.\n");
    }
    /* creating a copy of program_bin[] */
    unsigned short int * program_bin1;
    program_bin1 = malloc(ROWS * sizeof(unsigned short int));
    for(int k = 0; program_bin[k]!= 0; k++) program_bin1[k] = program_bin[k];

       /* Making sure that malloc succeeded */
    if(program_bin1 == NULL) {
        return 7;
        fprintf(stderr, "\nerror7: write_obj_file() failed.\n");
    }

    /* shifting the content of program_bin1[] */
    for(int w = 0; program_bin1[w]!= 0; w++) {
        unsigned short int tempVal = program_bin1[w] >> 8 ;
        unsigned short int tempVal1 = program_bin1[w] << 8;
        unsigned short int tempVal2 = tempVal + tempVal1;
        program_bin1[w] = tempVal2;
    }


    /* Writing 0xCADE in the header */
    unsigned short int codeHeader[3];
    unsigned short int xCADE = 0xDECA;    //little-endian format
    codeHeader[0] = xCADE;

    /* Writing out the address where the program should load */
    unsigned short int address = 0x0000;
    codeHeader[1] = address;

    /*  Count the number of rows that contain data in
        program_bin[], then write out <n>
    */
    unsigned short int n =0;
    for(int i = 0; program_bin[i]!= 0; i++) n++;
    int shiftedN = n << 8;    //little-endian format
    codeHeader[2] = shiftedN;

    /* writint out the <n> rows of data in program_bin[] */

    /* Writing out the CODE header */
    fwrite(codeHeader, sizeof(unsigned short int), 3, hexFile);

    /* Writing out the n words in the .obj file */
    fwrite(program_bin1, sizeof(unsigned short int), n, hexFile);

     /* Closing the file */
    fclose(hexFile);

    free(objFilename);
    free(program_bin1);
    return 0;


}
