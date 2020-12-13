// Name: Simon
// Seneca Student ID: 150595197
// Seneca email: slam74@myseneca.ca
// Date of completion: 11-28-2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <vector>
#include "Workstation.h"
#ifndef LINE_MANAGER_H
#define LINE_MANAGER_H

class LineManager
{
	std::vector<Workstation*> AssemblyLine;	// contains all the references of the Workstation objects on the assembly line
	std::deque<CustomerOrder> ToBeFilled;	// a queue of CustomerOrders to be filled
	std::deque<CustomerOrder> Completed;	// a queue of CustomerOrders completed
	unsigned int m_cntCustomerOrder;		// number of CustomerOrder objects the assembly line started with
public:
	LineManager(const std::string& filename, std::vector<Workstation*>& workstations, std::vector<CustomerOrder>& custOrders);
	bool run(std::ostream& os);
	void displayCompletedOrders(std::ostream& os) const;
	void displayStations() const;
	void displayStationsSorted() const;
	void sortAssemblyLine(std::deque<Workstation*>& sorted) const;
};

#endif
