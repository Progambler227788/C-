#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_LABEL_LENGTH 32

#define ADD_OPCODE 0x00
#define LW_OPCODE 0x23
#define SW_OPCODE 0x2B
#define JAL_OPCODE 0x3
#define J_OPCODE 0x2

#define REG_ZERO 0
#define REG_RA 31
#define REG_FP 30

typedef struct {
    char name[MAX_LABEL_LENGTH];
    int address;
} Label;

Label labels[MAX_LABEL_LENGTH];
int labelCount = 0;

void preprocessLine(char *line) {
    char *comment = strchr(line, '#');
    if (comment != NULL) {
        *comment = '\0';
    }

    while (*line == ' ' || *line == '\t') {
        line++;
    }

    int len = strlen(line);
    while (len > 0 && (line[len - 1] == ' ' || line[len - 1] == '\t' || line[len - 1] == '\n')) {
        line[len - 1] = '\0';
        len--;
    }
}

int findLabelAddress(const char *label) {
    for (int i = 0; i < labelCount; i++) {
        if (strcmp(label, labels[i].name) == 0) {
            return labels[i].address;
        }
    }
    return -1;
}

void assembleRInstruction(char *line, char *machineCode) {
    char opcode[7] = "000000";
    char funct[7] = "000000";

    char *mnemonic, *rd, *rs, *rt;
    mnemonic = strtok(line, " $,\t\n");
    rd = strtok(NULL, " $,\t\n");
    rs = strtok(NULL, " $,\t\n");
    rt = strtok(NULL, " $,\t\n");

    if (strcmp(mnemonic, "add") == 0) {
        strcpy(funct, "100000");
    } else if (strcmp(mnemonic, "sub") == 0) {
        strcpy(funct, "100010");
    } else {
        machineCode[0] = '\0';
        return;
    }

    int reg_rd = atoi(rd);
    int reg_rs = atoi(rs);
    int reg_rt = atoi(rt);

    sprintf(machineCode, "%s%05d%05d%05d%s%s", opcode, reg_rs, reg_rt, reg_rd, "00000", funct);
}

void assembleIInstruction(char *line, char *machineCode) {
    char opcode[7] = "000000";

    char *mnemonic, *rt, *offset, *base;
    mnemonic = strtok(line, " $,\t\n");
    rt = strtok(NULL, " $,\t\n");
    offset = strtok(NULL, " ($)\t\n");
    base = strtok(NULL, " ($)\t\n");

    if (strcmp(mnemonic, "lw") == 0) {
        strcpy(opcode, "100011");
    } else if (strcmp(mnemonic, "sw") == 0) {
        strcpy(opcode, "101011");
    } else {
        machineCode[0] = '\0';
        return;
    }

    int reg_rt = atoi(rt);
    int reg_base = atoi(base);
    int imm = atoi(offset);

    sprintf(machineCode, "%s%05d%05d%016d", opcode, reg_base, reg_rt, imm);
}

void assembleJInstruction(char *line, char *machineCode) {
    char opcode[7] = "000010";

    char *mnemonic, *label;
    mnemonic = strtok(line, " \t\n");
    label = strtok(NULL, " \t\n");

    if (strcmp(mnemonic, "j") != 0) {
        machineCode[0] = '\0';
        return;
    }

    int labelAddr = findLabelAddress(label);

    if (labelAddr == -1) {
        machineCode[0] = '\0';
        return;
    }

    char addrBinary[27];
    sprintf(addrBinary, "%026d", labelAddr);

    sprintf(machineCode, "%s%s", opcode, addrBinary);
}

void assembleInstruction(char *line, char *machineCode) {
    if (strstr(line, "add") != NULL || strstr(line, "sub") != NULL) {
        assembleRInstruction(line, machineCode);
    } else if (strstr(line, "lw") != NULL || strstr(line, "sw") != NULL) {
        assembleIInstruction(line, machineCode);
    } else if (strstr(line, "j") != NULL || strstr(line, "jal") != NULL) {
        if (strstr(line, "jal") != NULL) {
            assembleJInstruction(line, machineCode);
            if (strcmp(machineCode, "") == 0) {
                machineCode[0] = '\0';
                return;
            }
            machineCode[0] = '0';
            machineCode[1] = '1';
        } else {
            assembleJInstruction(line, machineCode);
        }
    } else if (strstr(line, ".text") != NULL) {
        // Handle the .text directive (just ignore it)
        machineCode[0] = '\0';
    } else if (line[strlen(line) - 1] == ':') {
        // Label declaration (ignore it)
        machineCode[0] = '\0';
    } else {
        // Unknown instruction or directive
        machineCode[0] = '\0';
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s input_file output_file\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    FILE *outputFile = fopen(argv[2], "w");

    if (inputFile == NULL || outputFile == NULL) {
        perror("Error opening input or output file");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int currentAddress = 0;

    while (fgets(line, sizeof(line), inputFile) != NULL) {
        preprocessLine(line);

        if (strlen(line) > 0 && line[strlen(line) - 1] == ':') {
            line[strlen(line) - 1] = '\0';
            strncpy(labels[labelCount].name, line, MAX_LABEL_LENGTH);
            labels[labelCount].address = currentAddress;
            labelCount++;
        } else {
            char machineCode[MAX_LINE_LENGTH];
            assembleInstruction(line, machineCode);
            if (machineCode[0] != '\0') {
                fprintf(outputFile, "%s\n", machineCode);
                currentAddress += 4;
            } else {
                fprintf(stderr, "Error assembling instruction: %s\n", line);
            }
        }
    }

    rewind(inputFile);

    while (fgets(line, sizeof(line), inputFile) != NULL) {
        preprocessLine(line);

        if (strlen(line) > 0 && line[strlen(line) - 1] != ':') {
            char machineCode[MAX_LINE_LENGTH];
            assembleInstruction(line, machineCode);

            if (machineCode[0] != '\0') {
                fprintf(outputFile, "%s\n", machineCode);
            } else {
                fprintf(stderr, "Error assembling instruction: %s\n", line);
            }
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}


