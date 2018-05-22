#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

/***************************** DECLERATE VARIABLE ****************************/
typedef struct OperationCodeTable
{
	char Mnemonic[8];
	char Format;
	unsigned short int  ManchineCode;
}SIC_OPTAB;
typedef struct RegisterTable      //format2를 위한 레지스터 테이블 추가
{
	char Register;
	int Number;
}REG_TAB;
typedef struct SymbolTable
{
	char Label[10];
	int Address;
}SIC_SYMTAB;

typedef struct IntermediateRecord {
	unsigned short int LineIndex;
	unsigned short int Loc;
	unsigned long long ObjectCode;   //byte c'...' 의 길이 증가를 위한 자료형 변환(int->long)
	unsigned short int format;      //format 변수 추가
	unsigned short int relocation;   //relocation 여부확인 변수
	char LabelField[32];
	char OperatorField[32];
	char OperandField[32];
}IntermediateRec;


int Counter;
int LOCCTR[100];
int LocctrCounter = 0;
int ProgramLen;
int Index;
int j;
int ManchineCode;
int SymtabCounter = 0;
int start_address;
int program_length;
int ArrayIndex = 0;
long base_address = 0;            // base 주소 변수 추가
unsigned short int FoundOnSymtab_flag = 0;
unsigned short int FoundOnOptab_flag = 0;

char Buffer[256];
char Label[32];
char Mnemonic[32];
char Operand[32];

SIC_SYMTAB SYMTAB[20];
IntermediateRec* IMRArray[100];


static SIC_OPTAB OPTAB[] =
{
	{ "ADD",  '3',  0x18 },
	{ "AND",  '3',  0x40 },
	{ "COMP",  '3',  0x28 },
	{ "DIV",  '3',  0x24 },
	{ "J",  '3',  0x3C },
	{ "JEQ",  '3',  0x30 },
	{ "JGT",  '3',  0x34 },
	{ "JLT",  '3',  0x38 },
	{ "JSUB",  '3',  0x48 },
	{ "LDA",  '3',  0x00 },
	{ "LDCH",  '3',  0x50 },
	{ "LDL",  '3',  0x08 },
	{ "LDT",  '3',  0x74 },
	{ "LDX",  '3',  0x04 },
	{ "MUL",  '3',  0x20 },
	{ "OR",  '3',  0x44 },
	{ "RD",  '3',  0xD8 },
	{ "RSUB",  '3',  0x4C },
	{ "STA",  '3',  0x0C },
	{ "STCH",  '3',  0x54 },
	{ "STL",  '3',  0x14 },
	{ "STSW",  '3',  0xE8 },
	{ "STX",  '3',  0x10 },
	{ "SUB",  '3',  0x1C },
	{ "TD",  '3',  0xE0 },
	{ "TIX",  '3',  0x2C },
	{ "WD",  '3',  0xDC },
	//SET 1 추가
	{ "ADDR",  '2',  0x90 },
	{ "CLEAR",  '2',  0xB4 },
	{ "COMPR",  '2',  0xA0 },
	{ "DIVR",  '2',  0x9C },
	{ "HIO",  '1',  0xF4 },
	{ "LDB",  '3',  0x68 },
	{ "LDS",  '3',  0x6C },
	{ "LPS",  '3',  0xD0 },
	{ "MULR",  '2',  0x98 },
	{ "RMO",  '2',  0xAC },
	{ "SHIFTL",  '2',  0xA4 },
	{ "SHIFTR",  '2',  0xA8 },
	{ "SIO",  '1',  0xF0 },
	{ "SSK",  '3',  0xEC },
	{ "STB",  '3',  0x78 },
	{ "STI",  '3',  0xD4 },
	{ "STS",  '3',  0x7C },
	{ "STT",  '3',  0x84 },
	{ "SUBR",  '2',  0x94 },
	{ "SVC",  '2',  0xB0 },
	{ "TIO",  '1',  0xF8 },
	{ "TIXR",  '2',  0xB8 },
	//SET2 추가
	{ "ADDF",  '3',  0x58 },
	{ "COMPF",  '3',  0x88 },
	{ "DIVF",  '3',  0x64 },
	{ "FIX",  '1',  0xC4 },
	{ "FLOAT",  '1',  0xC0 },
	{ "LDF",  '3',  0x70 },
	{ "MULF",  '3',  0x60 },
	{ "NORM",  '1',  0xC8 },
	{ "STF",  '3',  0x80 },
	{ "SUBF",  '3',  0x5C }

};
static REG_TAB REGTAB[] =         //format2를 위한 레지스터 테이블 추가
{
	{ 'A', 0 },
	{ 'X', 1 },
	{ 'L', 2 },
	{ 'B', 3 },
	{ 'S', 4 },
	{ 'T', 5 },
	{ 'F', 6 }

};

/****************************** DFINATE FUNCTION *****************************/
char* ReadLabel() {
	j = 0;//zeroing
	while (Buffer[Index] != ' ' && Buffer[Index] != '\t' && Buffer[Index] != '\n')      //Buffer에 들어있는 문자가 공백이 아니면 라벨에 복사
		Label[j++] = Buffer[Index++];
	Label[j] = '\0';
	return(Label);
}

void SkipSpace()      //버퍼 공백 넘기는 함수
{
	while (Buffer[Index] == ' ' || Buffer[Index] == '\t')
		Index++;
}

char* ReadOprator() {
	j = 0;//zeroing
	while (Buffer[Index] != ' ' && Buffer[Index] != '\t' && Buffer[Index] != '\n')
		Mnemonic[j++] = Buffer[Index++];
	Mnemonic[j] = '\0';
	return(Mnemonic);
}

char* ReadOperand() {
	j = 0;//zeroing
	while (Buffer[Index] != ' ' && Buffer[Index] != '\t' && Buffer[Index] != '\n')
		Operand[j++] = Buffer[Index++];
	Operand[j] = '\0';
	return(Operand);
}

void RecordSymtab(char* label) {
	strcpy(SYMTAB[SymtabCounter].Label, label);
	SYMTAB[SymtabCounter].Address = LOCCTR[LocctrCounter - 1];
	SymtabCounter++;
}

int SearchSymtab(char* label) {
	FoundOnSymtab_flag = 0;

	for (int k = 0; k <= SymtabCounter; k++) {
		if (!strcmp(SYMTAB[k].Label, label)) {
			FoundOnSymtab_flag = 1;
			return (FoundOnSymtab_flag);
			break;
		}
	}
	return (FoundOnSymtab_flag);
}

int SearchOptab(char * Mnemonic) {
	int size = sizeof(OPTAB) / sizeof(SIC_OPTAB);
	char temp[10];
	FoundOnOptab_flag = 0;
	if (Mnemonic[0] == '+')
	{
		for (int i = 0; i < strlen(Mnemonic); i++)
			temp[i] = Mnemonic[i + 1];
	}
	else
		strcpy(temp, Mnemonic);
	for (int i = 0; i<size; i++) {
		if (!strcmp(temp, OPTAB[i].Mnemonic)) {
			Counter = i;
			FoundOnOptab_flag = 1;
			break;
		}
	}
	return (FoundOnOptab_flag);
}

int StrToDec(char* c)      //문자 10진수로 변환 
{
	int dec_num = 0;
	char temp[10];
	strcpy(temp, c);

	int len = strlen(c);
	for (int k = len - 1, l = 1; k >= 0; k--)
	{
		dec_num = dec_num + (int)(temp[k] - '0')*l;
		l = l * 10;
	}
	return (dec_num);
}

int StrToHex(char* c)         //16진수로 변환
{
	int hex_num = 0;
	char temp[10];
	strcpy(temp, c);

	int len = strlen(temp);
	for (int k = len - 1, l = 1; k >= 0; k--)
	{
		if (temp[k] >= '0' && temp[k] <= '9')
			hex_num = hex_num + (int)(temp[k] - '0')*l;
		else if (temp[k] >= 'A' && temp[k] <= 'F')
			hex_num = hex_num + (int)(temp[k] - 'A' + 10)*l;
		else if (temp[k] >= 'a' && temp[k] >= 'f')
			hex_num = hex_num + (int)(temp[k] - 'a' + 10)*l;
		else;
		l = l * 16;
	}
	return (hex_num);
}
int ComputeLen(char* c)            //C' ..." , X'..." 인 경우의 byte수 계산
{
	unsigned int b;
	char len[32];

	strcpy(len, c);
	if (len[0] == 'C' || len[0] == 'c' && len[1] == '\'') {
		for (b = 2; b <= strlen(len); b++) {
			if (len[b] == '\'') {
				b -= 2;
				break;
			}
		}
	}
	if (len[0] == 'X' || len[0] == 'x' && len[1] == '\'')
		b = 1;
	return (b);
}

void CreateProgramList() {
	int loop;
	FILE *fptr_list;

	fptr_list = fopen("sic.list", "w");

	if (fptr_list == NULL)         //오류 검사
	{
		printf("ERROR: Unable to open the sic.list.\n");
		exit(1);
	}

	fprintf(fptr_list, "%-4s\t%-10s%-10s%-10s\t%s\n", "LOC", "LABEL", "OPERATOR", "OPERAND", "OBJECT CODE");
	for (loop = 0; loop < ArrayIndex; loop++)
	{
		if (!strcmp(IMRArray[loop]->OperatorField, "START") || !strcmp(IMRArray[loop]->OperatorField, "RESW") || !strcmp(IMRArray[loop]->OperatorField, "RESB"))
			fprintf(fptr_list, "%04x\t%-10s%-10s%-10s\n", IMRArray[loop]->Loc, IMRArray[loop]->LabelField, IMRArray[loop]->OperatorField, IMRArray[loop]->OperandField);
		else if (!strcmp(IMRArray[loop]->OperatorField, "BASE") || !strcmp(IMRArray[loop]->OperatorField, "END"))
			fprintf(fptr_list, "\t%-10s%-10s%-10s\n", IMRArray[loop]->LabelField, IMRArray[loop]->OperatorField, IMRArray[loop]->OperandField);
		else
		{   //포맷에 따라 출력되는 숫자 수 조정                                              
			if (IMRArray[loop]->format == 1)
				fprintf(fptr_list, "%04x\t%-10s%-10s%-10s\t%02x\n", IMRArray[loop]->Loc, IMRArray[loop]->LabelField, IMRArray[loop]->OperatorField, IMRArray[loop]->OperandField, IMRArray[loop]->ObjectCode);
			else if (IMRArray[loop]->format == 2)
				fprintf(fptr_list, "%04x\t%-10s%-10s%-10s\t%04x\n", IMRArray[loop]->Loc, IMRArray[loop]->LabelField, IMRArray[loop]->OperatorField, IMRArray[loop]->OperandField, IMRArray[loop]->ObjectCode);
			else if (IMRArray[loop]->format == 4)
				fprintf(fptr_list, "%04x\t%-10s%-10s%-10s\t%08x\n", IMRArray[loop]->Loc, IMRArray[loop]->LabelField, IMRArray[loop]->OperatorField, IMRArray[loop]->OperandField, IMRArray[loop]->ObjectCode);
			else
				fprintf(fptr_list, "%04x\t%-10s%-10s%-10s\t%06x\n", IMRArray[loop]->Loc, IMRArray[loop]->LabelField, IMRArray[loop]->OperatorField, IMRArray[loop]->OperandField, IMRArray[loop]->ObjectCode);
		}
	}
	fclose(fptr_list);
}

void CreateObjectCode() {
	int first_address;
	int last_address;
	int temp_address;
	int temp_objectcode[30];
	int first_index;
	int last_index;
	int x, xx;
	int loop;
	int temp_format[12];            //format 상태를 받기 위한 변수 추가

	char temp_operator[12][10];
	char temp_operand[12][10];

	FILE *fptr_obj;
	fptr_obj = fopen("sic.obj", "w");
	if (fptr_obj == NULL)
	{
		printf("ERROR: Unable to open the sic.obj.\n");
		exit(1);
	}

	printf("Creating Object Code...\n\n");

	loop = 0;
	if (!strcmp(IMRArray[loop]->OperatorField, "START"))
	{
		printf("H%-6s%06x%06x\n", IMRArray[loop]->LabelField, start_address, program_length);
		fprintf(fptr_obj, "H^%-6s^%06x^%06x\n", IMRArray[loop]->LabelField, start_address, program_length);
		loop++;
	}

	while (1)
	{

		first_address = IMRArray[loop]->Loc;
		last_address = IMRArray[loop]->Loc + 27;
		first_index = loop;

		for (x = 0, temp_address = first_address; temp_address <= last_address; loop++)
		{
			if (!strcmp(IMRArray[loop]->OperatorField, "END"))
				break;
			else if (strcmp(IMRArray[loop]->OperatorField, "RESB") && strcmp(IMRArray[loop]->OperatorField, "RESW") && strcmp(IMRArray[loop]->OperatorField, "BASE"))//조건에 BASE도 추가
			{
				temp_objectcode[x] = IMRArray[loop]->ObjectCode;
				strcpy(temp_operator[x], IMRArray[loop]->OperatorField);
				strcpy(temp_operand[x], IMRArray[loop]->OperandField);
				temp_format[x] = IMRArray[loop]->format;
				last_index = loop + 1;
				x++;
			}
			else;
			temp_address = IMRArray[loop + 1]->Loc;
		}

		printf("T%06x%02x", first_address, (IMRArray[last_index]->Loc - IMRArray[first_index]->Loc));
		fprintf(fptr_obj, "T^%06x^%02x", first_address, (IMRArray[last_index]->Loc - IMRArray[first_index]->Loc));

		for (xx = 0; xx<x; xx++)
		{
			if ((strcmp(temp_operator[xx], "BYTE") == 0) && (temp_operand[xx][0] == 'X' || temp_operand[xx][0] == 'x')) {
				printf("%02x", temp_objectcode[xx]);
				fprintf(fptr_obj, "^%02x", temp_objectcode[xx]);
			}
			//포맷에 따라 출력되는 숫자 수 조정
			else if (temp_format[xx] == 1)
			{
				printf("%02x", temp_objectcode[xx]);
				fprintf(fptr_obj, "^%02x", temp_objectcode[xx]);
			}
			else if (temp_format[xx] == 2)
			{
				printf("%04x", temp_objectcode[xx]);
				fprintf(fptr_obj, "^%04x", temp_objectcode[xx]);
			}
			else {
				printf("%06x", temp_objectcode[xx]);
				fprintf(fptr_obj, "^%06x", temp_objectcode[xx]);
			}
		}

		printf("\n");
		fprintf(fptr_obj, "\n");

		if (!strcmp(IMRArray[loop]->OperatorField, "END"))
			break;
	}
	loop = 0;
	//modification record 추가(한번 더 돌면서 pass2에서 체크한 relocation여부를 바탕으로 생성)
	for (; strcmp(IMRArray[loop]->OperatorField, "END"); loop++)
	{
		if (!(IMRArray[loop]->relocation))
		{
			printf("M%06x%02x\n", IMRArray[loop]->Loc + 1, 5);
			fprintf(fptr_obj, "M^%06x^%02x\n", IMRArray[loop]->Loc + 1, 5);
		}
	}

	printf("E%06x\n\n", start_address);
	fprintf(fptr_obj, "E^%06x\n\n", start_address);
	fclose(fptr_obj);
}

/******************************* MAIN FUNCTION *******************************/
void main(void)
{
	FILE* fptr;

	char filename[10];
	char label[32];
	char opcode[32];
	char operand[32];

	int loc = 0;
	int line = 0;
	int loop;
	int is_empty_line;
	int is_comment;
	int loader_flag = 0;

	printf(" ******************************************************************************\n");
	printf(" * Program: SIC ASSEMBYER                                                     *\n");
	printf(" *                                                                            *\n");
	printf(" * Procedure:                                                                 *\n");
	printf(" *   - Enter file name of source code.                                        *\n");
	printf(" *   - Do pass 1 process.                                                     *\n");
	printf(" *   - Do pass 2 process.                                                     *\n");
	printf(" *   - Create \"program list\" data on sic.list.(Use Notepad to read this file) *\n");
	printf(" *   - Create \"object code\" data on sic.obj.(Use Notepad to read this file)   *\n");
	printf(" *   - Also output object code to standard output device.                     *\n");
	printf(" ******************************************************************************\n");


	printf("\nEnter the file name you want to assembly (sic.asm):");
	scanf("%s", filename);
	fptr = fopen(filename, "r");
	if (fptr == NULL)
	{
		printf("ERROR: Unable to open the %s file.\n", filename);
		exit(1);
	}

	/********************************** PASS 1 ***********************************/
	printf("Pass 1 Processing...\n");
	while (fgets(Buffer, 256, fptr) != NULL)
	{
		is_empty_line = strlen(Buffer);

		Index = 0;
		j = 0;
		strcpy(label, ReadLabel());
		if (Label[0] == '.')
			is_comment = 1;
		else
			is_comment = 0;

		if (is_empty_line>1 && is_comment != 1)
		{
			Index = 0;
			j = 0;

			IMRArray[ArrayIndex] = (IntermediateRec*)malloc(sizeof(IntermediateRec));/* [A] */

			IMRArray[ArrayIndex]->LineIndex = ArrayIndex;
			strcpy(label, ReadLabel());
			strcpy(IMRArray[ArrayIndex]->LabelField, label);
			SkipSpace();

			if (line == 0)
			{
				strcpy(opcode, ReadOprator());
				strcpy(IMRArray[ArrayIndex]->OperatorField, opcode);/* [A] */
				if (!strcmp(opcode, "START"))
				{
					SkipSpace();
					strcpy(operand, ReadOperand());
					strcpy(IMRArray[ArrayIndex]->OperandField, operand);/* [A] */
					LOCCTR[LocctrCounter] = StrToHex(operand);
					start_address = LOCCTR[LocctrCounter];
				}
				else
				{
					LOCCTR[LocctrCounter] = 0;
					start_address = LOCCTR[LocctrCounter];
				}
			}
			else
			{
				strcpy(opcode, ReadOprator());
				strcpy(IMRArray[ArrayIndex]->OperatorField, opcode);
				SkipSpace();
				strcpy(operand, ReadOperand());
				strcpy(IMRArray[ArrayIndex]->OperandField, operand);

				if (strcmp(opcode, "END"))
				{
					if (label[0] != '\0')
					{
						if (SearchSymtab(label))
						{
							fclose(fptr);
							printf("ERROR: Duplicate Symbol\n");
							FoundOnSymtab_flag = 0;
							exit(1);
						}
						RecordSymtab(label);
					}

					if (opcode[0] == '+')
						LOCCTR[LocctrCounter] = loc + 4;      //format 4인 경우 loc 4증가
					else if (SearchOptab(opcode))
						LOCCTR[LocctrCounter] = loc + (int)(OPTAB[Counter].Format - '0');
					else if (!strcmp(opcode, "WORD"))
						LOCCTR[LocctrCounter] = loc + 3;
					else if (!strcmp(opcode, "RESW"))
						LOCCTR[LocctrCounter] = loc + 3 * StrToDec(operand);
					else if (!strcmp(opcode, "RESB"))
						LOCCTR[LocctrCounter] = loc + StrToDec(operand);
					else if (!strcmp(opcode, "BYTE"))
						LOCCTR[LocctrCounter] = loc + ComputeLen(operand);
					else if (!strcmp(opcode, "BASE"))         //BASE인 경우 loc증가 x
						LOCCTR[LocctrCounter] = loc;
					else {
						fclose(fptr);
						printf("ERROR: Invalid Operation Code\n");
						exit(1);
					}
				}
			}

			loc = LOCCTR[LocctrCounter];
			IMRArray[ArrayIndex]->Loc = LOCCTR[LocctrCounter - 1];
			LocctrCounter++;
			ArrayIndex++;
		}
		FoundOnOptab_flag = 0;
		line += 1;
	}
	program_length = LOCCTR[LocctrCounter - 2] - LOCCTR[0];

	/********************************** PASS 2 ***********************************/
	printf("Pass 2 Processing...\n");

	unsigned long inst_fmt;
	unsigned long inst_fmt_opcode;
	char inst_fmt_format;         //format 변수 추가
	unsigned long inst_fmt_index;
	long inst_fmt_address;         //p==1일 때 주소값이 음수가 나올 수 있으므로 unsigned를 signed로 교체 
								   //SIC/XE구현을 위한 변수 추가
	unsigned long inst_fmt_n;
	unsigned long inst_fmt_i;
	unsigned long inst_fmt_b;
	unsigned long inst_fmt_p;
	unsigned long inst_fmt_e;
	unsigned long inst_fmt_reg;//for format2

	for (loop = 1; loop<ArrayIndex; loop++) {
		inst_fmt_opcode = 0;
		inst_fmt_format = 0;
		inst_fmt_index = 0;
		inst_fmt_address = 0;
		inst_fmt_reg = 0;
		inst_fmt_n = 0;
		inst_fmt_i = 0;
		inst_fmt_b = 0;
		inst_fmt_p = 0;
		inst_fmt_e = 0;

		strcpy(opcode, IMRArray[loop]->OperatorField);
		if (SearchOptab(opcode)) {
			inst_fmt_format = OPTAB[Counter].Format;
			//opcode앞에 '+'있는경우 4형식 으로 인식
			if (opcode[0] == '+')
			{
				inst_fmt_format = '4';
				for (int i = 0; i < strlen(opcode); i++)
					opcode[i] = opcode[i + 1];
				inst_fmt_e = 0x00100000;
			}
			inst_fmt_opcode = OPTAB[Counter].ManchineCode;
			IMRArray[loop]->format = (short int)inst_fmt_format - 48;
			if (inst_fmt_format == '2')
				inst_fmt_opcode <<= 8;
			if (inst_fmt_format == '3')
				inst_fmt_opcode <<= 16;
			if (inst_fmt_format == '4')
				inst_fmt_opcode <<= 24;
			IMRArray[loop]->ObjectCode = inst_fmt_opcode;
			strcpy(operand, IMRArray[loop]->OperandField);

			if (operand[strlen(operand) - 2] == ',' && operand[strlen(operand) - 1] == 'X'&&inst_fmt_format != '2')      //index check
			{
				if (inst_fmt_format == '3')
					inst_fmt_index = 0x008000;
				else if (inst_fmt_format == '4')
					inst_fmt_index = 0x00800000;
				operand[strlen(operand) - 2] = '\0';
			}
			else
				inst_fmt_index = 0x000000;
			//immediate mode
			if (operand[0] == '#')
			{
				char temp[10];
				int flag = 0;

				for (int i = 0; i < strlen(operand); i++)
					temp[i] = operand[i + 1];
				for (int search_symtab = 0; search_symtab < SymtabCounter; search_symtab++)
				{
					//operand가 label인 경우
					if (!strcmp(temp, SYMTAB[search_symtab].Label) && inst_fmt_format != '4')
					{
						inst_fmt_address = (long)SYMTAB[search_symtab].Address - IMRArray[loop + 1]->Loc;
						if (inst_fmt_address > -2048 && inst_fmt_address<2047)
						{
							inst_fmt_p = 0x002000;
							if (inst_fmt_address < 0)
								inst_fmt_address += 0x001000;      //object code에서 주소가나타나는 부분이 3halfbyte이므로
						}
						//p 표시범위 벗어나면 b레지스터 사용
						else
						{
							inst_fmt_b = 0x004000;
							inst_fmt_address = (long)SYMTAB[search_symtab].Address - base_address;
						}
						flag = 1;
						break;
					}
				}
				//operand가 상수인 경우
				if (flag == 0)
				{
					inst_fmt_address = atoi(temp);
				}
				//4형식일때
				if (inst_fmt_format == '4')
				{
					inst_fmt_n = 0x00000000;
					inst_fmt_i = 0x01000000;
					for (int search_symtab = 0; search_symtab<SymtabCounter; search_symtab++)
					{
						if (!strcmp(temp, SYMTAB[search_symtab].Label)) {
							inst_fmt_address = (long)SYMTAB[search_symtab].Address;
							IMRArray[loop]->relocation = 0;         //obj파일을 만들 때 modification record에 추가
							break;
						}
					}
				}
				else
				{
					inst_fmt_n = 0x000000;
					inst_fmt_i = 0x010000;
				}
			}
			//indirect mode
			else if (operand[0] == '@')
			{
				char temp[10];

				for (int i = 0; i < strlen(operand); i++)
					temp[i] = operand[i + 1];
				for (int search_symtab = 0; search_symtab < SymtabCounter; search_symtab++)
				{
					if (!strcmp(temp, SYMTAB[search_symtab].Label) && inst_fmt_format != '4')
					{
						inst_fmt_address = (long)SYMTAB[search_symtab].Address - IMRArray[loop + 1]->Loc;
						if (inst_fmt_address > -2048 && inst_fmt_address<2047)
						{
							inst_fmt_p = 0x002000;
							if (inst_fmt_address < 0)
								inst_fmt_address += 0x001000;
						}
						else
						{
							inst_fmt_b = 0x004000;
							inst_fmt_address = (long)SYMTAB[search_symtab].Address - base_address;
						}
						break;
					}
				}
				if (inst_fmt_format == '4')
				{
					inst_fmt_n = 0x02000000;
					inst_fmt_i = 0x00000000;
					for (int search_symtab = 0; search_symtab<SymtabCounter; search_symtab++)
					{
						if (!strcmp(temp, SYMTAB[search_symtab].Label))
						{
							inst_fmt_address = (long)SYMTAB[search_symtab].Address;
							IMRArray[loop]->relocation = 0;
							break;
						}
					}
				}
				else
				{
					inst_fmt_n = 0x020000;
					inst_fmt_i = 0x000000;
				}
			}
			//format 1
			else if (inst_fmt_format == '1')
			{
				//아무것도 하지 않음
			}
			//format 2
			else if (inst_fmt_format == '2')
			{
				if (operand[0] >= 48 && operand[0] <= 57)         // SVC n 을 위한 코드
					inst_fmt_reg = operand[0] - 48;
				for (int i = 0; i < 7; i++)
				{
					if (REGTAB[i].Register == operand[0])
					{
						inst_fmt_reg = REGTAB[i].Number;
						inst_fmt_reg <<= 4;
						break;
					}
				}
				if (operand[strlen(operand) - 2] == ',')
				{
					if (operand[strlen(operand) - 1] >= 48 && operand[strlen(operand) - 1] <= 57)         // SHIFTL r1,n / SHIFTR r1,n을 위한 코드
						inst_fmt_reg += operand[strlen(operand) - 1] - 48;
					for (int i = 0; i < 7; i++)
					{
						if (REGTAB[i].Register == operand[strlen(operand) - 1])
						{
							inst_fmt_reg += REGTAB[i].Number;
							break;
						}
					}
				}
				IMRArray[loop]->ObjectCode += inst_fmt_reg;
			}
			//simple mode
			else
			{
				for (int search_symtab = 0; search_symtab < SymtabCounter; search_symtab++)
				{
					if (!strcmp(operand, SYMTAB[search_symtab].Label) && inst_fmt_format != '4')
					{
						inst_fmt_address = (long)SYMTAB[search_symtab].Address - IMRArray[loop + 1]->Loc;
						if (inst_fmt_address > -2048 && inst_fmt_address<2047)
						{
							inst_fmt_p = 0x002000;
							if (inst_fmt_address < 0)
								inst_fmt_address += 0x001000;
						}
						else
						{
							inst_fmt_b = 0x004000;
							inst_fmt_address = (long)SYMTAB[search_symtab].Address - base_address;
						}
						break;
					}
				}
				if (inst_fmt_format == '4')
				{
					inst_fmt_n = 0x02000000;
					inst_fmt_i = 0x01000000;
					for (int search_symtab = 0; search_symtab<SymtabCounter; search_symtab++)
					{
						if (!strcmp(operand, SYMTAB[search_symtab].Label))
						{
							inst_fmt_address = (long)SYMTAB[search_symtab].Address;
							IMRArray[loop]->relocation = 0;
							break;
						}
					}
				}
				else
				{
					inst_fmt_n = 0x020000;
					inst_fmt_i = 0x010000;
				}
			}

			inst_fmt = inst_fmt_opcode + inst_fmt_index + inst_fmt_address + inst_fmt_reg + inst_fmt_n + inst_fmt_i + inst_fmt_e + inst_fmt_p + inst_fmt_b;
			IMRArray[loop]->ObjectCode = inst_fmt;
		}
		//BASE 지시자 추가
		else if (!strcmp(opcode, "BASE"))
		{
			strcpy(operand, IMRArray[loop]->OperandField);
			for (int search_symtab = 0; search_symtab < SymtabCounter; search_symtab++)
			{
				if (!strcmp(operand, SYMTAB[search_symtab].Label))
				{
					base_address = (long)SYMTAB[search_symtab].Address;
					break;
				}
			}
		}
		else if (!strcmp(opcode, "WORD")) {
			strcpy(operand, IMRArray[loop]->OperandField);
			IMRArray[loop]->ObjectCode = StrToDec(operand);
		}
		else if (!strcmp(opcode, "BYTE")) {
			strcpy(operand, IMRArray[loop]->OperandField);
			IMRArray[loop]->ObjectCode = 0;

			if (operand[0] == 'C' || operand[0] == 'c' && operand[1] == '\'') {
				for (int x = 2; x <= (int)(strlen(operand) - 2); x++) {
					IMRArray[loop]->ObjectCode = IMRArray[loop]->ObjectCode + (int)operand[x];
					if (x<strlen(operand) - 2)
						IMRArray[loop]->ObjectCode <<= 8;
				}
			}

			if (operand[0] == 'X' || operand[0] == 'x' && operand[1] == '\'') {
				char *operand_ptr;
				operand_ptr = &operand[2];
				*(operand_ptr + 2) = '\0';
				for (int x = 2; x <= (int)(strlen(operand) - 2); x++) {
					IMRArray[loop]->ObjectCode = IMRArray[loop]->ObjectCode + StrToHex(operand_ptr);
					if (x<strlen(operand) - 2)
						IMRArray[loop]->ObjectCode <<= 8;
				}
			}


		}
		else
			/* do nothing */;
	}

	CreateProgramList();
	CreateObjectCode();

	for (loop = 0; loop<ArrayIndex; loop++)
		free(IMRArray[loop]);

	printf("Compeleted Assembly\n");
	fclose(fptr);
}