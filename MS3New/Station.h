// Name: Simon
// Seneca Student ID: 150595197
// Seneca email: slam74@myseneca.ca
// Date of completion: 11-14-2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#ifndef STATION_H
#define STATION_H

class Station
{
	int m_id;
	std::string m_itemName;
	std::string m_desc;
	unsigned int m_serialNumber;
	unsigned int m_quantity;
	static unsigned int m_widthField;
	static int id_generator;
public:
	Station();
	Station(const std::string&);
	const std::string& getItemName() const;
	unsigned int getNextSerialNumber();
	unsigned int getQuantity() const;
	void updateQuantity();
	void display(std::ostream& os, bool full) const;
};

#endif