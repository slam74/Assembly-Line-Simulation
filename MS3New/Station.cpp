// Name: Simon
// Seneca Student ID: 150595197
// Seneca email: slam74@myseneca.ca
// Date of completion: 11-14-2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

unsigned int Station::m_widthField = 0;
int Station::id_generator = 0;

Station::Station()
{
	m_id = 0;
	m_itemName = "";
	m_serialNumber = 0;
	m_quantity = 0;
	m_desc = "";
}

Station::Station(const std::string& str)
{
	// upon instantiating a Station object, we increment id_generator
	id_generator++;
	m_id = id_generator;
	size_t next_pos = 0;
	bool more = false;
	Utilities util;

	// using the Utilities object extractToken(), retrieve a token and store it in the appropriate attribute
	m_itemName = util.extractToken(str, next_pos, more);
	if(more)
		m_serialNumber = std::stoi(util.extractToken(str, next_pos, more));
	if(more)
		m_quantity = std::stoi(util.extractToken(str, next_pos, more));
	if (Station::m_widthField < util.getFieldWidth())
	{
		m_widthField = util.getFieldWidth();
	}
	if (more)
	{
		m_desc = util.extractToken(str, next_pos, more);
	}
}

const std::string& Station::getItemName() const
{
	return m_itemName;
}

unsigned int Station::getNextSerialNumber()
{
	return m_serialNumber++;
}

unsigned int Station::getQuantity() const
{
	return m_quantity;
}

void Station::updateQuantity()
{
	if (getQuantity() > 0)
	{
		m_quantity--;
	}
}

void Station::display(std::ostream& os, bool full) const
{
	if (full)
	{
		os << "[" << std::right << std::setw(3) << std::setfill('0') << m_id << std::setfill(' ') << "] Item: " << std::left << std::setw(m_widthField) << getItemName() << " [" << std::right << std::setw(6) << std::setfill('0') << m_serialNumber << std::setfill(' ') << "] Quantity: " << std::left << std::setw(m_widthField) << getQuantity() << " Description: " << m_desc << std::endl;
	}
	else
	{
		os << "[" << std::right << std::setw(3) << std::setfill('0') << m_id << std::setfill(' ') << "] Item: " << std::left << std::setw(m_widthField) << getItemName() << " [" << std::right << std::setw(6) << std::setfill('0') << m_serialNumber << std::setfill(' ') << "]" << std::endl;
	}
}