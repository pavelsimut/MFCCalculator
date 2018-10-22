#include "stdafx.h"
#include "Parser.h"
#include <cmath>
#include <string>
Parser::Parser(char* to_parse, int lungime) :lungime(lungime)
{
	this->to_parse = new char[lungime + 1];
	this->original = this-> to_parse;
	strncpy(this->to_parse, to_parse, lungime);
	this->to_parse[lungime - 1] = 0;
}
Parser::~Parser()
{
	delete[] original;
}

double Parser::parse() {
	return parse_sum();
}

double Parser::parse_double()
{
	size_t i = current_char_index;
	double moon = std::stod(to_parse, &i);
	current_char_index += i;
	to_parse += i;
	return moon;
}

double Parser::parse_power()
{
	double value = parse_double();
	if (current_char_index < lungime && *to_parse == '^')
	{
		current_char_index++;
		to_parse++;
		double exponent = parse_power();
		return std::pow(value, exponent);
	}
	return value;
}

double Parser::parse_product()
{
	double value = parse_power();
	while (current_char_index < lungime && (*to_parse == '*' || *to_parse == '/'))
	{
		current_char_index++;
		
		if (*to_parse == '*')
		{
			to_parse++;
			value *= parse_power();
			
		}
		else
		{
			to_parse++;
			value /= parse_power();
			
		}

	}
	return value;
}

double Parser::parse_sum()
{
	double value = parse_product();
	while (current_char_index < lungime && (*to_parse == '+' || *to_parse == '-'))
	{
		current_char_index++;
		if (*to_parse == '+')
		{
			to_parse++;
			value += parse_product();
		}
		else if (*to_parse  == '-')
		{
			to_parse++;
			value -= parse_product();
		}
	}
	return value;
}
