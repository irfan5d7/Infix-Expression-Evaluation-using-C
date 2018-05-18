#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>




struct operands
{
	int top;
	float val[32];
};

typedef struct operands operand;


struct operatr
{
	int top;
	char opr[32];
};
typedef struct operatr oprtor;

void push_operand(operand* oprnd, float val)
{
	oprnd->val[++(oprnd->top)] = val;
}

void push_opr(oprtor* oprtr, char op)
{
	oprtr->opr[++(oprtr->top)] = op;
}

float pop_operand(operand* oprnd)
{
	float val = oprnd->val[(oprnd->top)--];
	return val;
}

char pop_opr(oprtor *oprtr)
{
	char c = oprtr->opr[(oprtr->top)--];
	return c;
}
void push_pop_calc(operand *operd, oprtor* opr)
{
	float res;
	char op = pop_opr(opr);
	float val1 = pop_operand(operd);
	float val2 = pop_operand(operd);
	switch (op)
	{
	case '+': res = val2 + val1;
			break;
	case '-': res = val2 - val1;
			break;
	case '*': res = val2 * val1;
			break;
	case '/': res = val2 / val1;
			break;
	case '^': res = pow(val2, val1);
			break;
	}
	push_operand(operd, res);
}

float val_conv(char *operand, int len)
{
	int i, d, val, c;
	d = val = 0;
	int m = 1;
	val = c = 0;
	float r;
	for (i = 0; i < len - 1; i++)
	{
		if (operand[i] == '.')
		{
			d = i;
			break;
		}
	}
	if (d != 0)
	{
		for (i = d + 1; i < len; i++)
		{
			c++;
		}
		for (i = len-1; i >= 0; i--)
		{
			if (i != d)
			{
				val += (operand[i] - '0')*m;
				m *= 10;

			}
		}
		r = pow(10.0, c);
		r = (float)val / r;
	}
	else
	{
		for (i = len - 1; i >= 0; i--)
		{
			val += (operand[i] - '0')*m;
			m *= 10;
		}
		r = (float)val;
	}

	return r;
}


int str_len(char* str)
{
	int len = 0;
	while (str[len] != '\0'){ len++; }
	return len;
}


int preced_val(char c)
{
	switch (c)
	{
	case '-': return 1;
	case '+':return 2;
	case '*':return 3;
	case '/':return 4;
	case '^':return 5;
	}
}


int isdigit(char c)
{
	if ((c <= '9' && c >= '0')||c=='.')
		return 1;
	else
		return 0;
}


void str_rev(char *arr, int len)
{
	int i, j;
	i = 0;
	j = len - 1;
	char temp;
	while (i<j)
	{
		temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
		i++, j--;
	}


}
void float_tochar(char *arr, float f)
{
	f = f * 100;
	int n, i, s, len;
	n = (int)f;
	if (n < 0)
		n *= -1;
	i = 0;
	while (n != 0)
	{
		s = n % 10;
		n /= 10;
		arr[i++] = s + 48;
	}
	if (f < 0)
		arr[i++] = '-';
	arr[i] = '\0';
	i = len = str_len(arr);
	str_rev(arr, len);
	arr[i] = arr[i - 1];
	arr[i - 1] = arr[i - 2];
	arr[i - 2] = '.';
	arr[i + 1] = '\0';
}

int validate(char *expr)
{
	int len = str_len(expr);
	int i, d;
	i = d = 0;
	if (!(isdigit(expr[i]) && isdigit(expr[len - 1])))
		return 0;
	while (expr[i] !='\0')
	{
		if (!(isdigit(expr[i]) || isdigit(expr[i + 1])))
		{
			if (!((expr[i] == '*' && expr[i + 1] == '*') && (isdigit(expr[i + 2]))))
				return 0;
		}
		else if (expr[i] == '.' && expr[i + 1] == '.')
				return 0;
		i++;
	}
	i = 0;
	while (expr[i] != '\0')
	{
		d = 0;
		while (isdigit(expr[i]))
		{
			if (expr[i] == '.')
				d++;
			i++;
		}
		if (d > 1)
			return 0;
		i++;
	}
	return 1;
}

