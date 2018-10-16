#include "stdafx.h"
#include "Parser.h"
#include <cmath>
#include <string>
Parser::Parser(char* to_parse, int lungime) :lungime(lungime)
{
	this->to_parse = new char[lungime + 1];
	this->original = to_parse;
	strncpy(this->to_parse, to_parse, lungime);
	this->to_parse[lungime - 1] = 0;
}
Parser::~Parser()
{
}
double Parser::parse() {
	return parse_dif();
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
	if (current_char_index < lungime&&*to_parse == '^')
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
	while (current_char_index < lungime&&*to_parse == '*')
	{
		current_char_index++;
		to_parse++;
		value *= parse_power();
	}
	return value;
}
double Parser::parse_dif()
{
	double value = parse_sum();
	while (current_char_index < lungime&&*to_parse == '-')
	{
		current_char_index++;
		to_parse++;
		value -= parse_sum();
	}
	return value;
}
double Parser::parse_division()
{
	double value = parse_product();
	while (current_char_index < lungime&&*to_parse == '/')
	{
		current_char_index++;
		to_parse++;
		value /= parse_product();
	}
	return value;
}
double Parser::parse_sum()
{
	double value = parse_division();
	while (current_char_index < lungime&&*to_parse == '+')
	{
		current_char_index++;
		to_parse++;
		value += parse_division();
	}
	return value;
}
