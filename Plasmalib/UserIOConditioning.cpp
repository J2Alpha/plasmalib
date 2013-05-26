/*
 * UserIOConditioning.cpp
 *
 *  Created on: Apr 21, 2013
 *      Author: admin
 */

#include "UserIOConditioning.h"
//split a string on token character, returns vector of elements
std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> words;
	boost::split(words, s, boost::is_any_of(","), boost::token_compress_on); return words;// keep behind split to optimise return
}
//get and convert console input to string
std::string UserInputToString(int capturelength)
{
	char in [capturelength];
	gets(in);
	std::stringstream ssin;
	std::string sin;
	ssin<<in;
	ssin>>sin;
	return sin;
}
void UserInputToChar(char* out)
{
	gets(out);
}
//to de number to string
template <typename T> std::string NumberToString ( T Number )
{
	std::stringstream ss;
	ss << Number;
	return ss.str();
}
//to do string to number
template <typename T> T StringToNumber ( const std::string &Text )//Text not by const reference so that the function can be used with a
{                               //character array as argument
	std::stringstream ss(Text);
	T result;
	return ss >> result ? result : 0;
}

