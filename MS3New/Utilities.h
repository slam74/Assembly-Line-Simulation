// Name: Simon
// Seneca Student ID: 150595197
// Seneca email: slam74@myseneca.ca
// Date of completion: 11-14-2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#ifndef UTILITIES_H
#define UTILITIES_H

class Utilities
{
	size_t m_widthField;
	static char m_delimiter;
public:
	Utilities();
	void setFieldWidth(size_t newWidth);
	size_t getFieldWidth() const;
	std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
	static void setDelimiter(const char newDelimiter);
	static char getDelimiter();
};

#endif