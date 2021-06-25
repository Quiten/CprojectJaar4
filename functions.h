#include<ijvm.h>
#include<util.h>

typedef struct bitFile{
  uint32_t magicNmbr;
  int cpSize;
  int textSize;
  int bufferSize;
} bitFile_t; 

typedef struct machineState{
  int steps;
  int stackentries;
} machineState_t;

/*
Geeft de len waarde in int van de bite file.
*/
int search(char *file);

int dfdSearch(char *file);

/*
Enter Constant Pool Size value into cpSize
*/
void cpsMake(bitFile_t* infoFile, byte_t* buffer);

/*
Enter Constant Pool Data value into cpData
*/
void cpdMake(bitFile_t* infoFile, byte_t* buffer, byte_t* ConstantPool);

/*
Enter Text Size value into struct textSize
*/
void textMake(bitFile_t* infoFile, char method, char *file);

/*
Enter "actual program" value into struct textProgram
*/
void programMake(bitFile_t* infoFile, byte_t* buffer, byte_t* Instructions);

/*
Enter 1deadfad value into struct magicNmbr
*/
void dfdMake(bitFile_t* infoFile, byte_t* buffer);

/*
Size waarde naar int omzetten 
*/
int numberCon(bitFile_t* infoFile, char path);

/*
Machts functie 
*/
int macht(int base, int power);

int dynamicStruc(bitFile_t* infoFile);

void stepInstructions(int CurrentStep, byte_t *Instructions, byte_t* stack, machineState_t* machine, bitFile_t* infoFile);

void op_BiPush(byte_t *instructions, byte_t* stack, int currentstep, machineState_t machine, bitFile_t infoFile);

