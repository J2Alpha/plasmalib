/*
 * Gas.cpp
 *
 *  Created on: 10-mei-2013
 *      Author: admin
 */
#include "Gas.h"

int Gas::filler(std::ifstream &inFile, int linemo)
{
	std::string line;
	std::vector<std::string> results;
	switch(linemo)
	{
		case 0://read in name of a gas
			std::getline(inFile,line);
			this->name=line;
			flexcout("gasname done",1);
			break;
		case 1://read in a constituent
			std::getline(inFile,line);
			do{
				boost::split(results, line, boost::is_any_of("\t"));
				try
				{
					SPECIES spec={	results[0],
									e*boost::lexical_cast<int>(results[1]),//charge
									u*boost::lexical_cast<unsigned int>(results[2]),//mass
									boost::lexical_cast<unsigned int>(results[3])};//concentration
					this->constituents.push_back(spec);
				}
				catch( boost::bad_lexical_cast const& )
				{
						flexcout("casting went wrong when building gas list"); flexcout(line, 1);
						return 1;
				}
				catch (const std::out_of_range& range)
				{
					if(line.compare("#END#")) break;
				    std::cerr << "splitted line is too short, yields out  of range error possibly bad format, you didn't use spaces in stead of tabs, right?: " << range.what() << '\n';
				}
				flexcout("gas constituent done: ");flexcout(results[0],1);
				std::getline(inFile,line);
			}while(line.compare("#END#"));
			break;
		default:
			break;
	}
return 1;
}



