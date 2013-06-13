#ifndef CALC_EXPR_H_
#define CALC_EXPR_H_

#include <string>
#include <vector>
#include <stack>

// 符号类型定义
typedef enum
{
	OP, // 操作符
	ARG, // 参数
	RAND, // 随机数
	INT, // 整数
	FLOAT, // 浮点数
	BOOL, // 布尔值

} TokenType;

// 操作符类型定义
typedef enum
{
	LEFT,	// 左括号 (
	RIGHT,	// 右括号 )
	POW,	// 幂 ^
	MUL,	// 乘 *
	DIV,	// 除 /
	MOD,	// 取余 %
	ADD,	// 加 +
	SUB,	// 减 =
	LT,		// 小于 <
	GT,		// 大于 >
	LE,		// 小于等于 <=
	GE,		// 大于等于 >=
	EQ,		// 等于 ==
	NE,		// 不等于 !=
	AND,	// 与 &&
	OR,		// 或 ||
} OPType;

// 符号
typedef struct
{
	TokenType type;
	union
	{
		int index;		// 参数下标
		int i;			// 整数
		float f;		// 浮点数
		bool b;			// 布尔值
		OPType op;		// 操作符类型
	} value;
} Token;

typedef std::vector<Token> TokenVector;
typedef std::stack<Token> TokenStack;

// 表达式解析
bool ParseExpr(const std::string & expr, TokenVector & tokens);

// 把解析好的表达式转换成逆波兰式
bool ConvertExpr(const TokenVector & input, TokenVector & output);

// 逆波兰式计算求值
bool CalcExpr(const TokenVector & input, const TokenVector & expr, Token & result);

// 整合三个步骤的表达式求值，可以传两个整形参数
bool CalcExpr(const std::string & expr, int a1, int a2, Token & result);

// 两个辅助函数，调试时打印Token和TokenVector用
void PrintToken(const Token & token);
void PrintTokenVector(const TokenVector & tokens);

#endif /* CALC_EXPR_H_ */
