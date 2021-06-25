#include <ijvm.h>
#include <functions.h>
#include <stdlib.h>
#include <string.h>

machineState_t machine;
bitFile_t infoFile;
byte_t *constantPool;
byte_t *instructions;
byte_t *stack;


int init_ijvm(char *binary_file)
{
  // Implement loading of binary here
  FILE *fp;
  fp = fopen(binary_file, "rb");// Open read-only

  infoFile.bufferSize = search(binary_file);
  byte_t buffer[infoFile.bufferSize];
  fread(&buffer, sizeof(char), infoFile.bufferSize, fp);

  //print het bestand 
  /*
  printf("\n");
  
  for (int i = 0; i < infoFile.bufferSize; i++) 
  {
    printf(" %02x ", buffer[i]);
  };
  printf("\n");
  */

  /*
  Check if the first couple of bits are 0xdeadfad
  */
 
  if (dfdSearch(binary_file) == MAGIC_NUMBER){
    /*
    Reading all the information of the .ijvm file
    */

    //lezen van 1deadfad en de grote van alle arrays inlezen 
    dfdSearch(binary_file);
    textMake(&infoFile, 'c' , binary_file);
    textMake(&infoFile,'t' , binary_file);

    //De lijsten maken 
    constantPool = (byte_t*)malloc(infoFile.cpSize);
    instructions = (byte_t*)malloc(infoFile.textSize);
    stack = (byte_t*)malloc(infoFile.textSize);
    
    //Alles in de lijsten toevoegen 
    cpdMake(&infoFile, buffer, constantPool);
    programMake(&infoFile, buffer, instructions); 


    //Alle gelezen waarden bekijken 
    /*
    for (int i = 0; i < infoFile.textSize; i++){
      printf("\n %02x ", constantPool[i]);
      printf(" %02x ", instructions[i]);
    } 
    printf(" \n border \n");
    */

    return 1;

  } else if (dfdSearch(binary_file) == MAGIC_NUMBER) {
    //printf("\n Test: %02x and Checked: %02x", dfdSearch(binary_file), MAGIC_NUMBER);
    //printf("\n TEST 2 \n");
    
    // When reading integer from IJVM binary
    /*
    FILE  *fp;
    uint32_t size;
    fread(&size, sizeof(uint32_t), 1, fp);
    size = swap_uint32(size);
    */

    return 1;
  } else {
    return -1;
  }
  
  printf("\n");
  return -1;
}


void destroy_ijvm()
{
  // Reset IJVM state
  memset(&infoFile, 0, sizeof(bitFile_t));
  memset(&machine, 0, sizeof(machineState_t));
  memset(&instructions, 0, 0);
  memset(&constantPool, 0, 0);

  //&infoFile = (bitFile_t*)realloc(&infoFile, 0);
  //&machine = (machineState_t*)realloc(&machineState_t, 0);


}

void run()
{
  // Step while you can
  machine.stackentries = 0;
  for (machine.steps = 0; machine.steps < infoFile.textSize; machine.steps++){
    if (step() == true){
      stepInstructions(machine.steps, instructions, stack, &machine, &infoFile);
    } else if (step() == false){
      stepInstructions(machine.steps, instructions, stack, &machine, &infoFile);
    }
    else {printf(" Error #4 or nothing \n");}
  };

}

void set_input(FILE *fp)
{
  // TODO: implement me
}

void set_output(FILE *fp)
{
  // TODO: implement me
}

bool step(){
    switch (instructions[machine.steps])
    {
       case 0x10: case 0x59: case 0xFE: case 0xA7: case 0xFF: case 0x60: case 0x7E: case 0x99: case 0x9B: case 0x9F: case 0x84: case 0x15: case 0xFC:
       case 0xB6: case 0xB0: case 0xAC: case 0x36: case 0x64: case 0x13: case 0xFD: case 0x00: case 0x57: case 0x5F: case 0xC4: return true;
       
      default: return false;

    };
}

/**
 * Returns the currently loaded program text as a byte array.
 **/
byte_t *get_text(void){
  return ("%s", instructions);
}



/**
 * Returns the size of the currently loaded program text.
 **/
int text_size(void){
  return infoFile.textSize;
}


/**
 * Returns the value of the program counter (as an offset from the first instruction).
 **/
int get_program_counter(void){
  return machine.steps;
}

/**
 * @return The value of the current instruction represented as a byte_t.
 *
 * This should NOT increase the program counter.
 **/
byte_t get_instruction(void){
  return instructions[machine.steps];
}

/**
 * This function should return the word at the top of the stack of the current
 * frame, interpreted as a signed integer.
 **/
word_t tos(void){
  
}

