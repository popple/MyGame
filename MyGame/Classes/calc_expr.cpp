#include "calc_expr.h"
#include <iostream>
#include <math.h>

using namespace std;

// 操作符优先级
int OPPriority(OPType op)
{
	switch(op)
	{
	case LEFT:
	case RIGHT:
		return -10;
	case POW:
		return -20;
	case MUL:
	case DIV:
	case MOD:
		return -30;
	case ADD:
	case SUB:
		return -40;
	case LT:
	case GT:
	case LE:
	case GE:
		return -50;
	case EQ:
	case NE:
		return -60;
	case AND:
		return -70;
	case OR:
		return -80;
	default:
		break;
	}

	// 正常情况不会返回这个值
	return -1000;
}

// 词法分析，解析表达式
bool ParseExpr(const string & expr, TokenVector & tokens)
{
	// 表达式的解析较简单，就不用状态机了，直接一个一个解析。。。
	int i = 0;
	Token token;
	string buffer;
	tokens.clear();
	while (i < expr.length())
	{
		// 空白跳过
		if (isblank(expr[i]))
		{
			++i;
			continue;
		}

		// 单个字符的操作符和括号
		if (expr[i] == '+' ||
			expr[i] == '-' ||
			expr[i] == '*' ||
			expr[i] == '/' ||
			expr[i] == '%' ||
			expr[i] == '^' ||
			expr[i] == '(' ||
			expr[i] == ')')
		{
			token.type = OP;
			if (expr[i] == '+') token.value.op = ADD;
			else if (expr[i] == '-') token.value.op = SUB;
			else if (expr[i] == '*') token.value.op = MUL;
			else if (expr[i] == '/') token.value.op = DIV;
			else if (expr[i] == '%') token.value.op = MOD;
			else if (expr[i] == '^') token.value.op = POW;
			else if (expr[i] == '(') token.value.op = LEFT;
			else if (expr[i] == ')') token.value.op = RIGHT;

			tokens.push_back(token);

			++i;
			continue;
		}
		// 整数或浮点数
		else if (isdigit(expr[i]))
		{
			buffer.clear();
			buffer += expr[i++];
			bool point = false;

			while (i < expr.length())
			{
				if (isdigit(expr[i]))
				{
					buffer += expr[i++];
				}
				else if (expr[i] == '.' && !point)
				{
					buffer += expr[i++];
					point = true;
				}
				else
				{
					break;
				}
			}
			if (point)
			{
				token.type = FLOAT;
				token.value.f = strtof(buffer.c_str(), NULL);
			}
			else
			{
				token.type = INT;
				token.value.i = strtoul(buffer.c_str(), NULL, 0);

			}
			tokens.push_back(token);
		}
		// 随机数
		else if (expr[i] == 'r')
		{
			token.type = RAND;
			token.value.i = 0;
			tokens.push_back(token);
			++i;
		}
		// 参数
		else if (expr[i] == 'x')
		{
			++i;
			buffer.clear();

			while (i < expr.length() && isdigit(expr[i]))
			{
				buffer += expr[i];
				++i;
			}
			if (buffer.empty())
			{
				return false;
			}

			token.type = ARG;
			token.value.index = strtoul(buffer.c_str(), NULL, 0);
			tokens.push_back(token);
			continue;
		}
		// > 或 >=
		else if (expr[i] == '>')
		{
			token.type = OP;
			++i;
			if (i < expr.length() && expr[i] == '=')
			{
				token.value.op = GE;
				++i;
			}
			else
			{
				token.value.op = GT;
			}
			tokens.push_back(token);
		}
		// < 或 <=
		else if (expr[i] == '<')
		{
			token.type = OP;
			++i;
			if (i < expr.length() && expr[i] == '=')
			{
				token.value.op = LE;
				++i;
			}
			else
			{
				token.value.op = LT;
			}
			tokens.push_back(token);
		}
		// ==
		else if (i + 1 < expr.length() && expr[i] == '=' && expr[i + 1] == '=')
		{
			token.type = OP;
			token.value.op = EQ;
			tokens.push_back(token);
			i += 2;
		}
		// !=
		else if (i + 1 < expr.length() && expr[i] == '!' && expr[i + 1] == '=')
		{
			token.type = OP;
			token.value.op = NE;
			tokens.push_back(token);
			i += 2;
		}
		// &&
		else if (i + 1 < expr.length() && expr[i] == '&' && expr[i + 1] == '&')
		{
			token.type = OP;
			token.value.op = AND;
			tokens.push_back(token);
			i += 2;
		}
		// ||
		else if (i + 1 < expr.length() && expr[i] == '|' && expr[i + 1] == '|')
		{
			token.type = OP;
			token.value.op = OR;
			tokens.push_back(token);
			i += 2;
		}
		else
		{
			return false;
		}
	}

	return true;
}

// 把解析好的表达式转换成逆波兰式
bool ConvertExpr(const TokenVector & input, TokenVector & output)
{
	TokenStack stack;
	output.clear();

	TokenVector::const_iterator it = input.begin();
	for (; it != input.end(); ++it)
	{
		if (it->type == OP)
		{
			// 左括号，直接压进操作符栈
			if (it->value.op == LEFT)
			{
				stack.push(*it);
			}
			// 右括号，从栈里弹出操作符，直到碰到右括号
			else if (it->value.op == RIGHT)
			{
				bool find_left = false;
				while (!stack.empty())
				{
					if (stack.top().value.op == LEFT)
					{
						find_left = true;
						stack.pop();
						break;
					}
					else
					{
						output.push_back(stack.top());
						stack.pop();
					}
				}
				if (!find_left) return false;
			}
			// 其它操作符，和栈顶操作符比较优先级
			else
			{
				while (!stack.empty() && stack.top().value.op != LEFT &&
					OPPriority(stack.top().value.op) >= OPPriority(it->value.op))
				{
					output.push_back(stack.top());
					stack.pop();
				}

				stack.push(*it);
			}
		}
		// 非操作符直接输出
		else
		{
			output.push_back(*it);
		}
	}

	while (!stack.empty())
	{
		output.push_back(stack.top());
		stack.pop();
	}

	return true;
}

// 算数运算模板（加、减、乘、除）
#define ARITHMETIC_CALC(OP) {\
if (token1.type == INT && token2.type == INT) \
{ \
	result.type = INT; \
	result.value.i = token1.value.i OP token2.value.i; \
}\
else if (token1.type == FLOAT && token2.type == INT)\
{\
	result.type = FLOAT;\
	result.value.f = token1.value.f OP token2.value.i;\
}\
else if (token1.type == INT && token2.type == FLOAT)\
{\
	result.type = FLOAT;\
	result.value.f = token1.value.i OP token2.value.f;\
}\
else if (token1.type == FLOAT && token2.type == FLOAT)\
{\
	result.type = FLOAT;\
	result.value.f = token1.value.f OP token2.value.f;\
}\
else\
{\
	return false;\
}\
return true;\
}

bool Add(const Token &token1, const Token &token2, Token &result)
{
	ARITHMETIC_CALC(+)
}

bool Sub(const Token &token1, const Token &token2, Token &result)
{
	ARITHMETIC_CALC(-)
}

bool Mul(const Token &token1, const Token &token2, Token &result)
{
	ARITHMETIC_CALC(*)
}

bool Div(const Token &token1, const Token &token2, Token &result)
{
	ARITHMETIC_CALC(/)
}

bool Mod(const Token &token1, const Token &token2, Token &result)
{
	if (token1.type == INT && token2.type == INT)
	{
		result.type = INT;
		result.value.i = token1.value.i % token2.value.i;
	}
	else
	{
		return false;
	}

	return true;
}

bool Pow(const Token &token1, const Token &token2, Token &result)
{
	float a1, a2;

	if (token1.type == INT) a1 = token1.value.i;
	else if (token1.type == FLOAT) a1 = token1.value.f;
	else return false;

	if (token2.type == INT) a2 = token2.value.i;
	else if (token2.type == FLOAT) a2 = token2.value.f;
	else return false;

	result.type = FLOAT;
	result.value.f = pow(a1, a2);

	return true;
}

// 比较运算模板（大于，大于等于，小于，小于等于）
#define COMPARE_CALC(OP) {\
if (token1.type == INT && token2.type == INT)\
{\
	result.type = BOOL;\
	result.value.b = (token1.value.i OP token2.value.i);\
}\
else if (token1.type == FLOAT && token2.type == INT)\
{\
	result.type = BOOL;\
	result.value.b = (token1.value.f OP token2.value.i);\
}\
else if (token1.type == INT && token2.type == FLOAT)\
{\
	result.type = BOOL;\
	result.value.b = (token1.value.i OP token2.value.f);\
}\
else if (token1.type == FLOAT && token2.type == FLOAT)\
{\
	result.type = BOOL;\
	result.value.b = (token1.value.f OP token2.value.f);\
}\
else\
{\
	return false;\
}\
return true;\
}

bool Less(const Token &token1, const Token &token2, Token &result)
{
	COMPARE_CALC(<)
}

bool LessEqual(const Token &token1, const Token &token2, Token &result)
{
	COMPARE_CALC(<=)
}

bool Greater(const Token &token1, const Token &token2, Token &result)
{
	COMPARE_CALC(>)
}

bool GreaterEqual(const Token &token1, const Token &token2, Token &result)
{
	COMPARE_CALC(>=)
}

bool Equal(const Token &token1, const Token &token2, Token &result)
{
	if (token1.type == BOOL && token2.type == BOOL)
	{
		result.type = BOOL;
		result.value.b = (token1.value.b == token2.value.b);
		return true;
	}

	COMPARE_CALC(==)
}

bool NotEqual(const Token &token1, const Token &token2, Token &result)
{
	if (token1.type == BOOL && token2.type == BOOL)
	{
		result.type = BOOL;
		result.value.b = (token1.value.b != token2.value.b);
		return true;
	}

	COMPARE_CALC(!=)
}

bool GetBoolValue(const Token & token, bool & b)
{
	if (token.type == INT)
	{
		b = (token.value.i != 0);
		return true;
	}
	else if (token.type == FLOAT)
	{
		b = (token.value.f != 0);
		return true;
	}
	else if (token.type == BOOL)
	{
		b = token.value.b;
		return true;
	}
	else
	{
		return false;
	}
}

bool And(const Token &token1, const Token &token2, Token &result)
{
	bool a, b;
	if (GetBoolValue(token1, a) && GetBoolValue(token2, b))
	{
		result.type = BOOL;
		result.value.b = a && b;
		return true;
	}

	return false;
}

bool Or(const Token &token1, const Token &token2, Token &result)
{
	bool a, b;
	if (GetBoolValue(token1, a) && GetBoolValue(token2, b))
	{
		result.type = BOOL;
		result.value.b = a || b;
		return true;
	}

	return false;
}

bool GetValue(OPType op, const Token &token1, const Token &token2, Token &result)
{
	switch (op)
	{
	case ADD:
		return Add(token1, token2, result);
	case SUB:
		return Sub(token1, token2, result);
	case MUL:
		return Mul(token1, token2, result);
	case DIV:
		return Div(token1, token2, result);
	case MOD:
		return Mod(token1, token2, result);
	case POW:
		return Pow(token1, token2, result);
	case LT:
		return Less(token1, token2, result);
	case LE:
		return LessEqual(token1, token2, result);
	case GT:
		return Greater(token1, token2, result);
	case GE:
		return GreaterEqual(token1, token2, result);
	case EQ:
		return Equal(token1, token2, result);
	case NE:
		return NotEqual(token1, token2, result);
	case AND:
		return And(token1, token2, result);
	case OR:
		return Or(token1, token2, result);
	}

	return false;
}

// 逆波兰式计算求值
bool CalcExpr(const TokenVector & input, const TokenVector & expr, Token & result)
{
	TokenStack stack;

	TokenVector::const_iterator it = expr.begin();
	for (; it != expr.end(); ++it)
	{
		if (it->type == INT || it->type == FLOAT || it->type == BOOL)
		{
			stack.push(*it);
		}
		else if (it->type == ARG)
		{
			if (it->value.index >= input.size()) return false;
			const Token & a = input[it->value.index];
			if (a.type == INT || a.type == FLOAT || a.type == BOOL)
			{
				stack.push(a);
			}
			else
			{
				return false;
			}
		}
		else if (it->type == RAND)
		{
			Token a;
			a.type = INT;
			a.value.i = rand();
			stack.push(a);
		}
		else if (it->type == OP)
		{
			if (stack.size() < 2) return false;
			Token a = stack.top();
			stack.pop();
			Token b = stack.top();
			stack.pop();
			Token c;
			if (GetValue(it->value.op, b, a, c))
			{
				stack.push(c);
			}
			else
			{
				return false;
			}
		}
	}

	if (!stack.empty())
	{
		result = stack.top();
		return true;
	}
	else
	{
		return false;
	}
}

bool CalcExpr(const string & expr, int a1, int a2, Token & result)
{
	TokenVector a;
	bool r = ParseExpr(expr, a);
	if (!r) return false;

	TokenVector b;
	r = ConvertExpr(a, b);
	if (!r) return false;

	TokenVector input;
	Token x;
	x.type = INT;
	x.value.i = a1;
	input.push_back(x);
	x.value.i = a2;
	input.push_back(x);

	return CalcExpr(input, b, result);
}

void PrintToken(const Token & token)
{
	if (token.type == OP)
	{
		cout << "OP: ";
		switch (token.value.op)
		{
		case ADD:
			cout << '+' << endl; break;
		case SUB:
			cout << '-' << endl; break;
		case MUL:
			cout << '*' << endl; break;
		case DIV:
			cout << '/' << endl; break;
		case MOD:
			cout << '%' << endl; break;
		case POW:
			cout << '^' << endl; break;
		case LT:
			cout << '<' << endl; break;
		case LE:
			cout << "<=" << endl; break;
		case GT:
			cout << '>' << endl; break;
		case GE:
			cout << ">=" << endl; break;
		case EQ:
			cout << "==" << endl; break;
		case NE:
			cout << "!=" << endl; break;
		case AND:
			cout << "&&" << endl; break;
		case OR:
			cout << "||" << endl; break;
		case LEFT:
			cout << "(" << endl; break;
		case RIGHT:
			cout << ")" << endl; break;
		}
	}
	else if (token.type == INT)
		cout << "INT: " << token.value.i << endl;
	else if (token.type == FLOAT)
		cout << "FLOAT: " << token.value.f << endl;
	else if (token.type == ARG)
		cout << "ARG: " << token.value.index << endl;
	else if (token.type == BOOL)
		cout << "BOOL: " << (token.value.b ? "true" : "false") << endl;
	else if (token.type == RAND)
		cout << "RAND: " << endl;
}

void PrintTokenVector(const TokenVector & tokens)
{
	TokenVector::const_iterator it = tokens.begin();
	for (; it != tokens.end(); ++it)
	{
		PrintToken(*it);
	}
}
