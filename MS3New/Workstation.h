// Name: Simon
// Seneca Student ID: 150595197
// Seneca email: slam74@myseneca.ca
// Date of completion: 11-28-2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <deque>
#include "Station.h"
#include "CustomerOrder.h"
#ifndef WORK_STATION_H
#define WORK_STATION_H

class Workstation :public Station
{
	std::deque<CustomerOrder> m_orders;	// double ended queue with new CustomerOrders coming in one side and exiting out the other once filled
	Station* m_pNextStation;			// a pointer to the next station on the assembly line
public:
	Workstation(const std::string& record);

	// Workstation object cannot be copied or moved
	Workstation(const Workstation&) = delete;
	Workstation& operator=(const Workstation&) = delete;
	Workstation(Workstation&&) = delete;
	Workstation& operator=(Workstation&&) = delete;
	//
	void runProcess(std::ostream& os);
	bool moveOrder();
	void setNextStation(Station& station);
	const Workstation* getNextStation() const;
	bool getIfCompleted(CustomerOrder& order);
	void display(std::ostream& os) const;
	Workstation& operator+=(CustomerOrder&& order);
};

#endif
