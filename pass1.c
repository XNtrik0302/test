#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE_LENGTH 100

char line[MAX_LINE_LENGTH];
char label[20], opcode[20], operand[20], t1[20], t2[20], t3[20];
int locctr, start, len, symb_count = -1, size = 0, opd, NOT_IN_OPTAB;
FILE *fpin, *fpopt, *fpsym, *fpinter, *fplen;

struct SYMTAB
{
    char label[20];
    int addr;
} ST[30];

struct OPTAB
{
    char opcode[20];
    char hexcode[20];
} OT[30];

void read_OPTAB()
{
    int i = 0;
    while (i < 30 && fscanf(fpopt, "%s%s", OT[i].opcode, OT[i].hexcode) != EOF)
    {
        i++;
    }
}

void read_Line()
{
    strcpy(label, "");
    strcpy(opcode, "");
    strcpy(operand, "");

    if (fgets(line, MAX_LINE_LENGTH, fpin) != NULL)
    {
        int num_items = sscanf(line, "%s%s%s", t1, t2, t3);
        switch (num_items)
        {
        case 3:
            strcpy(label, t1);
            strcpy(opcode, t2);
            strcpy(operand, t3);
            break;
        case 2:
            strcpy(opcode, t1);
            strcpy(operand, t2);
            break;
        case 1:
            strcpy(opcode, t1);
            break;
        default:
            break;
        }
    }
}

int main()
{
    fpin = fopen("input.txt", "r");
    fpopt = fopen("optab.txt", "r");
    fpsym = fopen("symtab.txt", "w");
    fpinter = fopen("intermed.txt", "w");
    fplen = fopen("length.txt", "w");
    read_OPTAB();
    fgets(line, MAX_LINE_LENGTH, fpin);
    sscanf(line, "%s%s%x", label, opcode, &opd);
    if (strcmp(opcode, "START") == 0)
    {
        start = opd;
        locctr = start;
        fprintf(fpinter, "%-10s%-10s%-10s%x\n", "", label, opcode, opd);
    }
    else
    {
        locctr = 0;
    }
    read_Line();
    while (strcmp(opcode, "END") != 0)
    {
        fprintf(fpinter, "%-10x%-10s%-10s%s\n", locctr, label, opcode, operand);
        if (strcmp(label, "") != 0) // FOR FILLING LABELS IN SYMTAB
        {
            for (int i = 0; i <= symb_count; i++)
            {
                if (strcmp(ST[i].label, label) == 0)
                {
                    printf("Error: Duplicate label '%s'\n", label);
                    exit(1);
                }
            }
            symb_count++;
            strcpy(ST[symb_count].label, label);
            ST[symb_count].addr = locctr;
        }
        NOT_IN_OPTAB = 1;
        for (int i = 0; i <= 30; i++) // FOR FINDING OPCODE is IN OPTAB
        {
            if (strcmp(opcode, OT[i].opcode) == 0)
            {
                locctr += 0x3;
                size += 3;
                NOT_IN_OPTAB = 0;
                break;
            }
        }
        if (NOT_IN_OPTAB)
        {
            if (strcmp(opcode, "WORD") == 0)
            {
                locctr += 0x3;
                size += 3;
            }
            else if (strcmp(opcode, "RESW") == 0)
            {
                locctr += (0x3 * (atoi(operand)));
            }
            else if (strcmp(opcode, "RESB") == 0)
            {
                locctr += (atoi(operand));
            }
            else if (strcmp(opcode, "BYTE") == 0)
            {
                len = strlen(operand);
                if (operand[0] == 'C' || operand[0] == 'c')
                {
                    len = len - 3;
                }
                else
                {
                    len = (len - 2) / 2;
                }
                locctr += len;
                size += len;
            }
        }
        read_Line();
    }
    fprintf(fpinter, "%-10x%-10s%-10s%s\n", locctr, label, opcode, operand);
    for (int i = 0; i <= symb_count; i++)
    {
        fprintf(fpsym, "%-10s%x\n", ST[i].label, ST[i].addr);
    }

    fprintf(fplen, "%x\n%x", locctr - start, size);
    fclose(fpin);
    fclose(fpopt);
    fclose(fpsym);
    fclose(fpinter);
    fclose(fplen);
    printf("");
    return 0;
}