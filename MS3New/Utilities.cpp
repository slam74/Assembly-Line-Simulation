// Name: Simon
// Seneca Student ID: 150595197
// Seneca email: slam74@myseneca.ca
// Date of completion: 11-14-2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <string>
#include "Utilities.h"

char Utilities::m_delimiter = ' ';

Utilities::Utilities()
{
	m_widthField = 1;
}

void Utilities::setFieldWidth(size_t newWidth)
{
	m_widthField = newWidth;
}

size_t Utilities::getFieldWidth() const
{
	return m_widthField;
}

std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
{
	std::string token;
	size_t found;
	// find the next occurrence of delimiter starting at next_pos
	found = str.find(m_delimiter, next_pos);
	// if a delimiter character is found
	if (found != str.npos)
	{
		// if the next position is a delimiter character, it is an empty token
		if (found == next_pos)
		{
			// report an exception empty token
			throw "Empty token!";
		}
		else
		{
			// extract the token and adjust m_widthField if it is less than the length of the extracted token
			token = str.substr(next_pos, found - next_pos);
			if (m_widthField < token.size())
			{
				m_widthField = token.size();
			}
			// set next_pos to the next starting position
 			next_pos = str.find(m_delimiter, next_pos) + 1;
		}
		more = true;
	}
	else
	{
		// when there is no delimiter character found, extract the rest of the string into token and adjust m_widthField if necessary
		token = str.substr(next_pos, str.size() - next_pos);
		if (m_widthField < token.size())
		{
			m_widthField = token.size();
		}
		next_pos = str.size();
		more = false;
	}
	
	return token;
}

void Utilities::setDelimiter(const char newDelimiter)
{
	m_delimiter = newDelimiter;
}

char Utilities::getDelimiter()
{
	return m_delimiter;
}