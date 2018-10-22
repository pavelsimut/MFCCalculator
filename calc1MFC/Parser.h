#pragma once
class Parser
{
public:
	Parser(char* , int);
	~Parser();
	double parse();
private:
	double parse_double();
	double parse_power();
	double parse_product();
	double parse_sum();
	char* to_parse;
	char*original;
	int lungime;
	int current_char_index = -1;
};
