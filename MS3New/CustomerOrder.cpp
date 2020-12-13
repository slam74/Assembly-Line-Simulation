// Name: Simon
// Seneca Student ID: 150595197
// Seneca email: slam74@myseneca.ca
// Date of completion: 11-20-2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <iomanip>
#include <algorithm>
#include "CustomerOrder.h"
#include "Utilities.h"

size_t CustomerOrder::m_widthField = 0u;

CustomerOrder::CustomerOrder()
{
	m_name = "";
	m_product = "";
	m_cntItem = 0u;
	m_lstItem = nullptr;
}

CustomerOrder::CustomerOrder(std::string& record)
{
	size_t next_pos = 0;
	bool more = false;
	char delimiter;
	Utilities util;
	m_name = util.extractToken(record, next_pos, more);
	m_product = util.extractToken(record, next_pos, more);
	// get the delimiter
	delimiter = util.getDelimiter();
	// count the number of times the delimiter appears in the record
	int delimCnt = std::count(record.begin() + next_pos, record.end(), delimiter);
	m_cntItem = delimCnt + 1;
	// allocate memory for the products
	m_lstItem = new Item * [m_cntItem];

	for (auto i = 0u;i < m_cntItem;i++)
	{
		m_lstItem[i] = new Item(util.extractToken(record, next_pos, more));
	}
	if (m_widthField < util.getFieldWidth())
	{
		m_widthField = util.getFieldWidth();
	}
}

// throw an exception when copy constructor is called
CustomerOrder::CustomerOrder(const CustomerOrder& src)
{
	throw "Error!!!";
}

CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept
{
	m_lstItem = nullptr;
	m_cntItem = 0u;
	*this = std::move(src);
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept
{
	// check for self assignment
	if (this != &src)
	{
		// deallocate current resources
		if (m_lstItem != nullptr)
		{
			for (auto i = 0u;i < m_cntItem;i++)
			{
				if (m_lstItem[i] != nullptr)
				{
					delete m_lstItem[i];
					m_lstItem[i] = nullptr;
				}
			}
			delete[] m_lstItem;
			m_lstItem = nullptr;
		}

		// copy address to current object
		m_lstItem = src.m_lstItem;
		src.m_lstItem = nullptr;
		// swap variables
		m_name = src.m_name;
		m_product = src.m_product;
		m_cntItem = src.m_cntItem;
		src.m_name = "";
		src.m_product = "";
		src.m_cntItem = 0u;
	}
	return *this;
}

CustomerOrder::~CustomerOrder()
{
	if (m_lstItem != nullptr)
	{
		for (auto i = 0u;i < m_cntItem;i++)
		{
			if (m_lstItem[i] != nullptr)
			{
				delete m_lstItem[i];
				m_lstItem[i] = nullptr;
			}
		}
		delete[] m_lstItem;
		m_lstItem = nullptr;
	}
}

bool CustomerOrder::isOrderFilled() const
{
	// return true if all items in the order have been filled, otherwise return false
	bool allFilled = true;
	for (auto i = 0u;i < m_cntItem;i++)
	{
		if (!m_lstItem[i]->m_isFilled)
		{
			allFilled = false;
			// break out of the loop
			i = m_cntItem;
		}
	}
	return allFilled;
}

bool CustomerOrder::isItemFilled(const std::string& itemName) const
{
	// loop through all m_lstItem
	for (auto i = 0u;i < m_cntItem;i++)
	{
		if (m_lstItem[i]->m_itemName == itemName)
		{
			return m_lstItem[i]->m_isFilled;
		}
	}
	return true;
}

void CustomerOrder::fillItem(Station& station, std::ostream& os)
{
	for (auto i = 0u;i < m_cntItem;i++)
	{
		if (m_lstItem[i]->m_itemName == station.getItemName())
		{
			// fill item if it has not been filled already
			if (!m_lstItem[i]->m_isFilled)
			{
				// subtracts 1 from the inventory if inventory is not empty
				if (station.getQuantity() > 0)
				{
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;

					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
				else
				{
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
			}
			// break out of the for loop once there is a matching item name found
			//i = m_cntItem;
		}
	}
}

void CustomerOrder::display(std::ostream& os) const
{
	os << m_name << " - " << m_product << std::endl;
	for (auto i = 0u;i < m_cntItem;i++)
	{
		os << "[" << std::right << std::setfill('0') << std::setw(6) << m_lstItem[i]->m_serialNumber << std::setfill(' ') << "] " << std::left << std::setw(m_widthField) << m_lstItem[i]->m_itemName << " - ";
		if (m_lstItem[i]->m_isFilled)
		{
			os << "FILLED";
		}
		else
		{
			os << "MISSING";
		}
		os << std::endl;
	}
}