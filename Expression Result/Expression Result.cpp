#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <stdlib.h>
/*
	Name: ExpressionResult.cpp
	Copyright: null
	Author: runing
	Date: 26-03-15 15:15
	Description: getExpressionResult
*/

using namespace std;

/*
	字符是否为数字 
*/
bool isNum(char ch){
	if(ch <= '9' && ch >= '0'){
		return true;
	}else{
		return false;
	}
}

/*
	字符是否为运算符 
*/
bool isOperator(char ch){
	if(ch == '+' || ch == '-' || ch == '*'
				 || ch == '/' || ch == '='){
		return true;
	}else{
		return false;
	}
}

/*
	字符是否为算术表达式 
*/
bool isExpression(const string & str){
	int flag = 0;
	for(int i = 0;i < str.length() - 1;i++){
		const char ch = str[i];
		const char chb = str[i + 1];
		if((!isNum(ch) && i == 0) || !isNum(chb)
			&& (i == str.length() - 2) && ch != ')' && chb != ')'){
			cout<< "首尾不是数字---->"<< ch<< chb<< endl;
			return false;
		}
		if((ch == '.' && !isNum(chb)) || (!isNum(ch) && chb == '.')){
			cout<< "小数点前后不是数字--->"<< ch<< chb<< endl;
			return false;
		}
		if(isOperator(ch) && !isNum(chb) && chb != '('){
			cout<< "运算符不是数字--->"<< ch<< chb<< endl;
			return false;
		}
		if(isNum(ch) && !isOperator(chb) && chb != '.' && chb != ')'
				&& !isNum(chb)) {
			cout<< "数字后不是运算符--->"<< ch<< chb<< endl;
			return false;
		}
		if(ch == '('){
			flag++;
		}
		if(chb == ')'){
			flag--;
		}
	}
	if (flag != 0) {
		cout<< "括号不匹配--->"<< endl;
		return false;
	}
	return true;
}

/*
	字符串转换浮点型 
*/
double transformString(const string &str){
	char char_Str[30];
	int i = 0;
	for(i = 0;i<str.length();i++){
		char_Str[i] = str[i];
	}
	char_Str[i] = '\0';
	return atof(char_Str);
} 

/*
	浮点型转换字符串 
*/
string transformDouble(const double &d1){
	char char_str[30];
	gcvt(d1,8,char_str);
	string str = "";
	int i = 0;
	for(i = 0;char_str[i] != '\0';i++){
		str.append(1,char_str[i]);
	}
	return str;
}

/*
	分解算术表达式字符串 
*/
vector<string> & resolveString(vector<string> & s_vector,const string & str){
	string temp = "";
	for(int i = 0;i < str.length();i++){
		const char ch = str[i];
		if(isNum(ch) || ch == '.'){
			temp += ch;
		}else if(isOperator(ch) || ch == ')'){
			if(temp != ""){
				s_vector.push_back(temp);
				temp = "";
			}
			temp.append(1,ch);
			s_vector.push_back(temp);
			temp = "";
		}else if (ch == '('){
			temp.append(1,ch);
			s_vector.push_back(temp);
			temp = "";
		}
		if(i == str.length() - 1){
			s_vector.push_back(temp);
		}
	}
	return  s_vector;
}

/*
	字符串是否为数字
*/
bool isDouble(const string &str){
	if(str == ""){
		return false;
	}
	if(str[0] == '.' || str[str.length() - 1] == '.'){
		return false;		
	}
	if(str.length() > 1){
		if(str[0] == '0' && str[1] != '.'){
			return false;
		}	
	}
	for(int i = 0;i < str.length();i++){
		if(!isNum(str[i]) && str[i] != '.'){
			return false;
		}
	}
	return true;
}

/*
	字符串是否为运算符 
*/
bool isStrOperator(const string & str){
	if(str == "+" || str == "-" || str == "*" || str == "/"
			|| str == "(" || str == ")"){
		return true;
	}else{
		return false;
	}
}

/*
	比较运算符优先级 
*/
bool heightOperator(const string &o1,const string &o2){
	if((o1 == "*" || o1 == "/")
			&& (o2 == "+" || o2 == "-") || o2 == "("){
		return true;
	}else if((o1 == "+" || o1 == "-")
			&& (o2 == "*" || o2 == "/")){
		return false;
	}else if((o1 == "*" || o1 == "/")
			&& ((o2 == "*" || o2 == "/"))){
		return true;
	}else if((o1 == "+" || o1 == "-")
			&& (o2 == "+" || o2 == "-")){
		return true;
	}else{
		return false;
	}
}

/*
	中缀表达式转后缀 
*/
vector<string> & nifix_to_post(vector<string> & s_vector
								,vector<string> & post_v){
	stack<string> s_stack;
	for(int i = 0;i < s_vector.size();i++){
		const string str = s_vector[i]; 
		if(isDouble(str)){
			post_v.push_back(str);
		}if(isStrOperator(str) && s_stack.empty()){
			s_stack.push(str);
		}else if(isStrOperator(str) && !s_stack.empty()){
			string last = s_stack.top();
			if (heightOperator(str, last) || str == "("){
				s_stack.push(str);
			} else if(!heightOperator(str, last) && str != ")"){
				while(!s_stack.empty()){
					string pop = s_stack.top();
					post_v.push_back(pop);	
					s_stack.pop();
				}
				s_stack.push(str);
			} else if (str == ")"){
				while(!s_stack.empty()){
					string pop = s_stack.top();
					if (pop != "(") {
						post_v.push_back(pop);
						s_stack.pop();
					}else{
						s_stack.pop();
					}
					if (pop == "("){
						break;
					}
				}
			}
		}
	}
	while(!s_stack.empty()){
		post_v.push_back(s_stack.top());
		s_stack.pop();
	}
//	for(int i = 0;i < post_v.size();i++){
//		cout<< post_v[i]<< endl;
//	}
}

/*
	两数算术运算 
*/
double getCountResult(string oper, double num1, double num2) {
	if(oper == "+"){
		return num1 + num2;
	}else if(oper == "-"){
		return num1 - num2;
	}else if(oper == "*"){
		return num1 * num2;
	}else if(oper == "/"){
		return num1 / num2;
	}else{
		return 0;
	}
}

/*
	计算后缀表达式 
*/
double get_postfis_rearut(vector<string> & post_v){
	stack<string> e_stack;
	string temp = "";
	for(int i = 0;i < post_v.size();i++){
		string str = post_v[i];
		if(isDouble(str)){
			e_stack.push(str);
		}else if(isStrOperator(str)){
			double n2 = transformString(e_stack.top());
			e_stack.pop();
			double n1 = transformString(e_stack.top());
			e_stack.pop();
			double sum = getCountResult(str,n1,n2);
			temp += transformDouble(sum);
			e_stack.push(temp);
			temp = "";
		}
	}
	return transformString(e_stack.top());
}

int main(){
	string str = "4*((5-2)+5*2.4)";//"9+(3-1)*3+10/2";
	vector<string> s_vector;
	vector<string> post_v;
	if(!isExpression(str)){
		return 0; 
	}
	s_vector = resolveString(s_vector,str);
//	for(int i = 0;i < s_vector.size();i++){
//		cout<< s_vector[i]<< endl;
//	}
	nifix_to_post(s_vector,post_v);
	cout<< str<< " = "<< get_postfis_rearut(post_v);
 return 0;	
}
