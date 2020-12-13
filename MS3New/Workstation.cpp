// Name: Simon
// Seneca Student ID: 150595197
// Seneca email: slam74@myseneca.ca
// Date of completion: 11-28-2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include "Workstation.h"

Workstation::Workstation(const std::string& record) :Station(record)
{
	m_pNextStation = nullptr;
}

// runs a single cycle of the assembly line for the current station
void Workstation::runProcess(std::ostream& os)
{
	// if there are CustomerOrders in the queue, 
	//fill the order in the front at the current Workstation
	if (!m_orders.empty())
	{
		m_orders.front().fillItem(*this, os);
	}
}

// if the order at the front of the queue doesn't require service at the current station, 
//move it to the next station on the assembly line and return true, 
//otherwise do nothing and return false. 
bool Workstation::moveOrder()
{
	// If the queue is empty, return false
	if (m_orders.empty())
	{
		return false;
	}
	else
	{
		if (m_orders.front().isItemFilled(getItemName()))
		{
			if (m_pNextStation != nullptr)
			{
				*(Workstation*)m_pNextStation += std::move(m_orders.front());
				m_orders.pop_front();
				return true;
			}
		}
	}
	return false;
}

// stores station into the m_pNextStation pointer
void Workstation::setNextStation(Station& station)
{
	m_pNextStation = &station;
}

// return the next station on the assembly line
const Workstation* Workstation::getNextStation() const
{
	return (Workstation*)m_pNextStation;
}

// if the order at the front of the queue is completed, 
//remove from queue, place it in the parameter and return true, 
//otherwise return false
bool Workstation::getIfCompleted(CustomerOrder& order)
{
	// if the queue is empty, return false;
	if (m_orders.empty())
	{
		return false;
	}
	else
	{
		if (m_orders.front().isOrderFilled())
		{
			order = std::move(m_orders.front());
			m_orders.pop_front();
			return true;
		}
		else
		{
			return false;
		}
	}
}

void Workstation::display(std::ostream& os) const
{
	if (m_pNextStation == nullptr)
		os << getItemName() << " --> " << "END OF LINE" << std::endl;
	else
		os << getItemName() << " --> " << m_pNextStation->getItemName() << std::endl;
}

Workstation& Workstation::operator+=(CustomerOrder&& order)
{
	m_orders.push_back(std::move(order));
	return *this;
}