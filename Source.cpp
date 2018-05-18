#include "Header.h"

void expr_eval(char *file_name);
float eval(char *expr, int expr_len);
void push_operand(operand* oprnd, float val);
void push_opr(oprtor* oprtr, char op);
float pop_operand(operand* oprnd);
char pop_opr(oprtor *oprtr);
void push_pop_calc(operand *operd, oprtor* opr);
float val_conv(char *operand, int len);
int str_len(char* str);
int preced_val(char c);
int isdigit(char c);
void float_tochar(char *arr, float f);
void str_rev(char *arr, int len);
void write_to_file(char **buff, int len, int *invalid, char* file_name, float *val);

int main()
{
	char *file_name = (char*)malloc(sizeof(char) * 32);
	/*printf("Enter File name: \n");
	scanf("%s", file_name);*/
	file_name = "SampleFile_ExpressionEvaluator.txt";
	expr_eval(file_name);
	return 1;
}


float eval(char *expr, int expr_len)
{
	int i, j, len;
	i = j = 0;
	float opnd_val;
	char oprnd[10];
	char oprr = '\0';
	operand *operd = (operand*)malloc(sizeof(operand) * expr_len);
	operd->top = -1;
	oprtor *opr = (oprtor*)malloc(sizeof(int) * expr_len);
	opr->top = -1;
	while (i < expr_len)
	{
		j = 0;
		if (isdigit(expr[i]))
		{
			while ((expr[i] <= '9' && expr[i] >= '0' ) || expr[i] =='.')
			{
				oprnd[j++] = expr[i++];
			}
			oprnd[j] = '\0';
			len = str_len(oprnd);
			opnd_val = val_conv(oprnd, len);
			push_operand(operd, opnd_val);
			if (expr[i] == '\0')
				break;
		}
			if (!isdigit(expr[i]))
			{
				if (expr[i] == expr[i + 1])
				{
					oprr = '^';
					i += 2;
				}
				else
					oprr = expr[i++];
				if (opr->top == -1)
				{
					push_opr(opr, oprr);
					oprr = '\0';
				}
				else
				{
					if (preced_val(oprr) > preced_val(opr->opr[opr->top]))
					{
						push_opr(opr, oprr);
						oprr = '\0';
					}
					else
					{
						while ((preced_val(oprr) <= preced_val(opr->opr[opr->top])) && opr->top != -1)
						{
							push_pop_calc(operd, opr);
							
						}
						push_opr(opr, oprr);
						oprr = '\0';
					}
				}
			}
	}
	while (opr->top >= 0)
	{
		push_pop_calc(operd, opr);
	}
	opnd_val = pop_operand(operd);
	return opnd_val;
}

void expr_eval(char *file_name)
{
	int i, j, k, len,l;
	i = j = k = 0;
	float val[30];
	char *buff = (char*)malloc(sizeof(char) * 10000);
	int invalid[30] = { 0 };
	FILE *fp = fopen(file_name, "r+");
	fscanf(fp, "%[^\0]s", buff);
	fclose(fp);
	while (buff[i] != '\0')
	{
		if (buff[i++] == '\n')
			j++;
	}
	char **out_buff = (char**)malloc(sizeof(char*) *(j+2));
	for (i = 0; i < j + 2; i++)
		out_buff[i] = (char*)malloc(sizeof(char) * 64);
	i = j = 0;
	while (buff[i] != '\0')
	{
		j = 0;
		while (buff[i] != '\n' && buff[i] != '\0')
		{
			out_buff[k][j++] = buff[i++];
		}
		out_buff[k][j++] = '\0';
		buff[i++];
		if (validate(out_buff[k]))
		{
			len = str_len(out_buff[k]);
			val[k] = eval(out_buff[k], len);
		}
		else
		{
			invalid[k] = 1;
			val[k] = -99999;
		}
		k++;
	}
	
	write_to_file(out_buff, k, invalid, "result.txt", val);
	fclose(fp);
}

void write_to_file(char **buff, int len, int *invalid,char* file_name,float *val)
{
	int i;
	FILE *fpp = fopen(file_name, "w");
	char inval[25] = "Invalid Expression";
	for (i = 0; i < len; i++)
	{
		if (invalid[i])
		{
			fprintf(fpp, "%s  %s \n", buff[i], inval);
		}
		else
		{
			fprintf(fpp, "%s = %4f  \n", buff[i], val[i]);
		}
	}
	fprintf(fpp, "%c", '\0');
	fclose(fpp);
}