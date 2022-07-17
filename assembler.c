/***************************************************************************
 * file name   : assembler.c                                               *
 * author      : Mohamed Sanogho                                           *
 * description : This program will assemble a .ASM file into a .OBJ file   *
 *               This program will use the "asm_parser" library to achieve *
 *			     its functionality.										   *
 *                                                                         *
 ***************************************************************************
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asm_parser.h"

int main(int argc, char** argv) {

    char* filename = NULL ;		            // name of ASM file
	char  program [ROWS][COLS] ; 			// ASM file line-by-line
	char  program_bin_str [ROWS][17] ; 		// instructions converted to a binary string
	unsigned short int program_bin [ROWS] ; // instructions in binary (HEX)

 /** Problem 1 starts here **/

    /** Checking whether argc has arguments **/
    if (argc > 1) filename = argv[1];
    else {
        printf("\nerror1: usage: ./assembler <assembly_file.asm>\n"); /* If not, print error message */
    }


    /**  Problem 2 starts here **/

    /**  Calling read_asm_file() to read entire ASM file
        into the array: program[][]
    **/
    read_asm_file (filename, program);

    /**  Displaying program[][] **/
    for(int i = 0; strcmp(program[i], "") != 0; i++) {
        printf("%s\n", program[i]);
    }

    printf("\n");

    /**  Calling parse_instruction() upon each row x of program[x][],
        and passing program_bin_str[x][] to str_to_bin()
    **/

    for(int x = 0; strcmp(program[x], "") != 0; x++) {

        parse_instruction(program[x], program_bin_str[x]);
        program_bin [x] = str_to_bin(program_bin_str[x]);
    }

    /** Displaying program_bin_str[][] **/
    for(int j = 0; strcmp(program_bin_str[j], "") != 0; j++) {
        printf("%s\n", program_bin_str[j]);
    }

    printf("\n");

   /** Displaying program_bin[] **/
    for(int k = 0; program_bin[k]!= 0; k++) {
       printf("0x%x\n", program_bin[k]);
   }

    write_obj_file(filename, program_bin);

return 0;
 }
