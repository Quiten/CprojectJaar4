#include <ijvm.h>
#include <functions.h>
#include <stdlib.h>

static uint32_t swap_uint32(uint32_t num)
{
    return((num>>24)&0xff) | ((num<<8)&0xff0000) |((num>>8)&0xff00) | ((num<<24)&0xff000000);
}
//////

int search(char *file)
{
  int len;
  FILE *fp;
  fp = fopen(file, "rb");
  fseek(fp, 0, SEEK_END);
  len = ftell(fp);
  return len; 
}

int dfdSearch(char *file)
{
    FILE* fp;
    fp = fopen(file, "rb");
    uint32_t deadfad;
    fread(&deadfad, sizeof(uint32_t), 1, fp);
    deadfad = swap_uint32(deadfad);
    return deadfad;
}

void cpdMake(bitFile_t* infoFile, byte_t* buffer, byte_t* ConstantPool)
{
    int start = 12;
    for (int i = 0; i < infoFile->cpSize; i++)
    {
        ConstantPool[i] = buffer[i+start];
    };
}

void programMake(bitFile_t* infoFile, byte_t* buffer, byte_t* instructions)
{
    int start = 20 + infoFile->cpSize;
    for (int i = 0; i < infoFile->textSize; i++)
    {
        instructions[i] = buffer[i+start];
        
    };
    
}

void textMake(bitFile_t* infoFile, char method, char *file)
{
    FILE* fp;
    fp = fopen(file, "rb");
    uint32_t buffer2 = 0;


    switch (method) 
    {
        /*
        C gaat de constantPool lezen in de bit file en t gaat de text size lezen. 
        */
        case 'c':
            fseek(fp,8, SEEK_SET);
            fread(&buffer2, sizeof(uint32_t), 1, fp);
            buffer2 = swap_uint32(buffer2);
            infoFile->cpSize = buffer2;
            fclose(fp);
            break;

        case 't':
            fseek(fp,16 + infoFile->cpSize, SEEK_SET);
            fread(&buffer2, sizeof(uint32_t), 1, fp);
            buffer2 = swap_uint32(buffer2);
            infoFile->textSize = buffer2;
            fclose(fp);
            break;

        default:
            printf("\nError #3");
    };
}

void stepInstructions(int currentStep, byte_t *instructions, byte_t* stack, machineState_t* machine, bitFile_t* infoFile){
    switch(instructions[currentStep]){
        case 0x10: printf("OP_BIPUSH\n"); op_BiPush(instructions, *stack, currentStep, *machine, *infoFile); break;
        case 0x59: printf("OP_DUP\n"); break;
        case 0xFE: printf("OP_ERR\n"); break;       
        case 0xA7: printf("OP_GOTO\n"); break;    
        case 0xFF: printf("OP_HALT\n"); break;       
        case 0x60: printf("OP_IADD\n"); break;    
        case 0x7E: printf("OP_IAND\n"); break;     
        case 0x99: printf("OP_IFEQ\n"); break;     
        case 0x9B: printf("OP_IFLT\n"); break;    
        case 0x9F: printf("OP_ICMPEQ\n"); break;    
        case 0x84: printf("OP_IINC\n"); break;     
        case 0x15: printf("OP_ILOAD\n"); break;    
        case 0xFC: printf("OP_IN\n"); break;   
        case 0xB6: printf("OP_INVOKEVIRTUAL\n"); break;  
        case 0xB0: printf("OP_IOR\n"); break; 
        case 0xAC: printf("OP_IRETURN\n"); break;   
        case 0x36: printf("OP_ISTORE\n"); break;  
        case 0x64: printf("OP_ISUB\n"); break;    
        case 0x13: printf("OP_LDC_W\n"); break;   
        case 0xFD: printf("OP_OUT\n"); break;  
        case 0x00: printf("OP_NOP\n"); break;   
        case 0x57: printf("OP_POP\n"); break;  
        case 0x5F: printf("OP_SWAP\n"); break; 
        case 0xC4: printf("OP_WIDE\n"); break;  

        default: printf("%02x\n", instructions[currentStep]); break;
        
    }
}

void op_BiPush(byte_t *instructions, byte_t* stack, int currentstep, machineState_t machine, bitFile_t infoFile){
    if (currentstep != infoFile.textSize){
    stack[machine.stackentries] = instructions[currentstep +1];
    machine.stackentries += 1;
    }

    else{printf(" error #5");}
}

//void op_out(){}
//void op_iadd(){}

/*
gebruikt recursie om de macht van base getal te berekenen
*/
int macht(int base, int power)
{
    int solution = 0;
    if (power > 0){ 
        solution = base * macht(base, power-1);
    } else if (power == 0)
    {
        return 1;
    } else{
        return 0;
    };
    return solution; 
}
/*
Haalt uit cpSize en textData hoeveel bits er aankomen
*/



