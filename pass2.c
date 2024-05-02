#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE_LENGTH 100

char line[MAX_LINE_LENGTH];
char t1[20], t2[20], t3[20], t4[20], address[20], label[20], opcode[20], operand[20], length[20], size[10], oprval[10], end_addr[20];
FILE *fpinter, *fpsym, *fpopt, *fplen, *fpassm, *fpobj;

struct SYMTAB
{
    char label[20];
    int addr[20];
} ST[30];

struct OPTAB
{
    char opcode[20], hexcode[20];
} OT[30];

void read_OPTAB()
{
    int i = 0;
    while (fscanf(fpopt, "%s%s", OT[i].opcode, OT[i].hexcode) != EOF )
    {
        i++;
    }
}

void read_SYMTAB()
{
    int i = 0;
    while (fscanf(fpsym, "%s%s", ST[i].label, ST[i].addr) != EOF)
    {
        i++;
    }
}
void read_Line()
{
    strcpy(address, "");
    strcpy(label, "");
    strcpy(opcode, "");
    strcpy(operand, "");

    if (fgets(line, MAX_LINE_LENGTH, fpinter) != NULL)
    {   
        int num_items = sscanf(line, "%s%s%s%s", t1, t2, t3, t4);
        switch (num_items)
        {
        case 4:
            strcpy(address, t1);
            strcpy(label, t2);
            strcpy(opcode, t3);
            strcpy(operand, t4);
            break;
        case 3:
            strcpy(address, t1);
            strcpy(opcode, t2);
            strcpy(operand, t3);
            break;
        case 2:
            strcpy(address, t1);
            strcpy(opcode, t2);
            break;
        default:
            break;
        }
    }
}

int main()
{
    int i, j;
    fpinter = fopen("intermed.txt", "r");
    fpsym = fopen("symtab.txt", "r");
    fpopt = fopen("optab.txt", "r");
    fplen = fopen("length.txt", "r");
    fpassm = fopen("assmlist.txt", "w");
    fpobj = fopen("objcode.txt", "w");
    read_OPTAB();
    read_SYMTAB();
    fscanf(fplen, "%s%s", length, size);
    fgets(line, MAX_LINE_LENGTH, fpinter);
    sscanf(line, "%s%s%s", label, opcode, operand);
    strcpy(end_addr, operand);
    if (strcmp(opcode, "START") == 0)
    {
        fprintf(fpassm, "%-10s%-10s%-10s%-10s\n", "", label, opcode, operand);
        fprintf(fpobj, "H^%s^00%s^0000%s\n", label, operand, length);
        fprintf(fpobj, "T^00%s^%s", operand, size);
    }
    read_Line();
    while (strcmp(opcode, "END") != 0)
    {

        if (strcmp(opcode, "BYTE") == 0)
        {
            fprintf(fpassm, "%-10s%-10s%-10s%-10s", address, label, opcode, operand);
            fprintf(fpobj, "^");
            for (i = 2; i < strlen(operand); i++)
            {
                fprintf(fpobj, "%x", operand[i]);
                fprintf(fpassm, "%x", operand[i]);
            }
            fprintf(fpassm, "\n");
        }
        else if (strcmp(opcode, "WORD") == 0)
        {
            sprintf(oprval, "%x", atoi(operand));
            fprintf(fpassm, "%-10s%-10s%-10s%-10s00000%s\n", address, label, opcode, operand, oprval);
            fprintf(fpobj, "^00000%s", oprval);
        }
        else if (strcmp(opcode, "RESB") == 0 || strcmp(opcode, "RESW") == 0)
        {
            fprintf(fpassm, "%-10s%-10s%-10s%-10s\n", address, label, opcode, operand);
        }
        else
        {
            j = 0;
            while (strcmp(opcode, OT[j].opcode) != 0)
            {
                j++;
            }
            i = 0;
            while (strcmp(operand, ST[i].label) != 0)
            {
                i++;
            }
            fprintf(fpassm, "%-10s%-10s%-10s%-10s%s%s\n", address, label, opcode, operand, OT[j].hexcode, ST[i].addr);
            fprintf(fpobj, "^%s%s", OT[j].hexcode, ST[i].addr);
        }
        read_Line();
    }
    fprintf(fpassm, "%-10s%-10s%-10s%-10s", address, label, opcode, operand);
    fprintf(fpobj, "\nE^00%s", end_addr);

    fclose(fpinter);
    fclose(fpsym);
    fclose(fpopt);
    fclose(fplen);
    fclose(fpassm);
    fclose(fpobj);
    return 0;
}