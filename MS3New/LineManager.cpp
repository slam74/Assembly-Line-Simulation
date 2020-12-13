// Name: Simon
// Seneca Student ID: 150595197
// Seneca email: slam74@myseneca.ca
// Date of completion: 11-28-2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <fstream>
#include <string>
#include "LineManager.h"
#include "Utilities.h"

LineManager::LineManager(const std::string& filename, std::vector<Workstation*>& workstations, std::vector<CustomerOrder>& custOrders)
{
	std::ifstream file(filename);
	if (!file)
		throw std::string("Unable to open [") + filename + "] file.";

	std::string record;
	while (!file.eof())
	{
		std::getline(file, record);
		Utilities util;
		std::string firstItem, secondItem;
		size_t next_pos = 0;
		bool more;
		firstItem = util.extractToken(record, next_pos, more);
		if (more)
			secondItem = util.extractToken(record, next_pos, more);
		else
			secondItem = "";

		// read the records from file and setup all the m_pNextStation references in the Workstation objects, 
		//linking each Workstation object together to form the assembly line
		// and copy all the Workstation objects into AssemblyLine
		for (auto i = 0u;i < workstations.size();i++)
		{
			if (workstations[i]->getItemName() == firstItem)
			{
				for (auto j = 0u;j < workstations.size();j++)
				{
					if (workstations[j]->getItemName() == secondItem)
					{
						workstations[i]->setNextStation((Station&)*workstations[j]);
						j = workstations.size();
					}
				}
			}
		}
	}

	// copies the workstation object to the AssemblyLine
	AssemblyLine = workstations;

	// move all the CustomerOrder objects to the back of the ToBeFilled queue
	for (auto i = 0u;i < custOrders.size();i++)
	{
		ToBeFilled.push_back(std::move(custOrders[i]));
	}

	// set the number of CustomerOrder objects the assembly line started with
	m_cntCustomerOrder = ToBeFilled.size();
}

bool LineManager::run(std::ostream& os)
{
	static int cnt = 0;
	os << "Line Manager Iteration: " << ++cnt << std::endl;

	std::deque<Workstation*> sortedAssemblyLine;
	// sort the AssemblyLine in the order they are linked
	sortAssemblyLine(sortedAssemblyLine);
	
	// if there are CustomerOrders in the ToBeFilled queue, move the one at the front
	// of the queue onto the starting point of the AssemblyLine
	Workstation* station = nullptr;
	CustomerOrder order;
	
	if (!ToBeFilled.empty())
	{
		// move the CustomerOrder at the front of the queue to the starting point of the AssemblyLine
		station = sortedAssemblyLine.front();
		*station += std::move(ToBeFilled.front());
		ToBeFilled.pop_front();
	}

	// processes all orders on the AssemblyLine
	for (auto i = 0u;i < AssemblyLine.size();i++)
	{
		station = AssemblyLine[i];
		AssemblyLine[i]->runProcess(os);
	}

	// move all the orders and move to Completed if completed
	for (auto i = 0u;i < AssemblyLine.size();i++)
	{
		station = AssemblyLine[i];
		station->moveOrder();
		if (station->getIfCompleted(order))
		{
			Completed.push_back(std::move(order));
		}
	}

	return Completed.size() == m_cntCustomerOrder;
}

// displays all completed orders
void LineManager::displayCompletedOrders(std::ostream& os) const
{
	for (auto i = 0u;i < Completed.size();i++)
	{
		Completed[i].display(os);
	}
}

// displays all stations on the assembly line in the order they were received from the client
void LineManager::displayStations() const
{

	for (auto i = 0u;i < AssemblyLine.size();i++)
	{
		AssemblyLine[i]->display(std::cout);
	}
}

// displays all stations on the assembly line in the order they are linked
void LineManager::displayStationsSorted() const
{
	std::deque<Workstation*> sorted;
	sortAssemblyLine(sorted);
	std::deque<Workstation*>::iterator i;

	// display contents of organized container
	for (auto i = sorted.begin();i != sorted.end();i++)
	{
		(*i)->display(std::cout);
	}
}

// sorts the AssemblyLine in the order of linkage
void LineManager::sortAssemblyLine(std::deque<Workstation*>& sorted) const
{
	Workstation* workingStation = nullptr;

	for (auto i = 0u;i < AssemblyLine.size();i++)
	{
		if (AssemblyLine[i]->getNextStation() == nullptr)
		{
			workingStation = AssemblyLine[i];
			sorted.push_back(AssemblyLine[i]);
			// break out of loop
			i = AssemblyLine.size();
		}
	}

	bool done = false;
	while (!done)
	{
		for (auto i = 0u;i < AssemblyLine.size();i++)
		{
			if (AssemblyLine[i]->getNextStation() == workingStation)
			{
				sorted.push_front(AssemblyLine[i]);
				workingStation = AssemblyLine[i];
				// break out of loop
				i = AssemblyLine.size();
			}
		}
		if (AssemblyLine.size() == sorted.size())
		{
			done = true;
		}
	}
}