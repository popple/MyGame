#include "calc_expr.h"
#include <iostream>

using namespace std;

int main()
{
	// 用随机数前要先初始化一下随机数种子
	srand(time(NULL));

	// 以下都是测试的例子，先按照解析、转换、计算分步骤测试
	TokenVector a;
	string expr = "(1 + 2.9) * 30 * x0 - 455 * 5 / 6 > 10 && 3 < 4 && r % 2";

	cout << "Expression: " << expr << endl;

	cout << "--------------------------" << endl;

	// 第一步：词法分析，先解析表达式为符号
	bool r = ParseExpr(expr, a);
	if (r)
	{
		PrintTokenVector(a);
	}
	else
	{
		cout << "ParseExpr error" << endl;
		return -1;
	}

	cout << "--------------------------" << endl;

	// 第二部：转换成逆波兰式
	TokenVector b;
	r = ConvertExpr(a, b);
	if (r)
	{
		PrintTokenVector(b);
	}
	else
	{
		cout << "ConvertExpr error" << endl;
		return -1;
	}

	cout << "--------------------------" << endl;

	// 第二部：表达式求值
	TokenVector input;
	Token x1;
	x1.type = INT;
	x1.value.i = 10;
	input.push_back(x1);

	Token result;
	r = CalcExpr(input, b, result);
	if (r)
	{
		PrintToken(result);
	}
	else
	{
		cout << "CalcExpr error" << endl;
		return -1;
	}

	cout << "--------------------------" << endl;

	// 测试整合三个步骤的函数，没特殊需求就用这个就OK了
	string expr2 = "(100 - x0) * 3 + 20 - x1 / 3 + r % 3";
	cout << "Expression: " << expr2 << endl;

	r = CalcExpr(expr2, 10, 100, result);
	if (r)
	{
		PrintToken(result);
	}
	else
	{
		cout << "CalcExpr error" << endl;
		return -1;
	}

	return 0;
}


