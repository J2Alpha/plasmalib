/*
 * Accelerator.cpp
 *
 *  Created on: 21-mei-2013
 *      Author: admin
 */

#include "Accelerator.h"
//todo: don't return, break into exceptions!
int Accelerator::filler(std::ifstream &inFile, int linemo)
{
	std::string line;
	std::vector<std::string> results;
	switch(linemo)
	{
		case 0://read in name of a gas
			std::getline(inFile,line);
			this->name=line;
			//flexcout("ACCname done: ");flexcout(this->name,1);
			break;
		case 1://read in Efield
			std::getline(inFile,line);
			flexcout(line);
			boost::split(results, line, boost::is_any_of("[,]"));
			/*important: splitting a string that begins with a is_any_of token make the 0th element be an empty string or ""*/
			//flexcout("here :");flexcout((std::string)results[1],1);flexcout((std::string)results[2],1);
			try{
				this->Efield=Field(VectorPoint(mpelement(results[1]),mpelement(results[2]),mpelement(results[3])));
			}
			catch (const std::out_of_range& range)
			{
				std::cerr << "splitted line is too short, or bad format, format should be [x,y,z] failed at rangenum: " << range.what() << '\n';
			}
			//flexcout("Efield done");
			break;
		case 2://read in Bfield
			std::getline(inFile,line);
			boost::split(results, line, boost::is_any_of("[,]"));
			//flexcout(results[2]);
			try{
				this->Bfield=Field(VectorPoint(mpelement(results[1]),mpelement(results[2]),mpelement(results[3])));
			}
			catch (const std::out_of_range& range)
			{
				std::cerr << "splitted line is too short, or bad format, format should be [x,y,z] failed at rangenum: " << range.what() << '\n';
			}
			//flexcout("Bfield done");
			break;
		case 3://read in start position
			std::getline(inFile,line);
			boost::split(results, line, boost::is_any_of("[,\t]"));
			try{
				this->x0=VectorPoint(mpelement(results[1]),mpelement(results[2]),mpelement(results[3]));
			}
			catch (const std::out_of_range& range)
			{
				std::cerr << "splitted line is too short, or bad format, format should be [x,y,z] failed at rangenum: " << range.what() << '\n';
			}
			//flexcout("X done");
			break;
		case 4://read in start velocity
			std::getline(inFile,line);
			boost::split(results, line, boost::is_any_of("[,\t]"));
			try{
				this->v0=VectorPoint(mpelement(results[1]),mpelement(results[2]),mpelement(results[3]));
			}
			catch (const std::out_of_range& range)
			{
				std::cerr << "splitted line is too short, or bad format, format should be [x,y,z] failed at rangenum: " << range.what() << '\n';
			}
			//flexcout("V done");
			break;
		case 5://read in stepsize
			std::getline(inFile,line);
			try{
				this->Dt=(mpelement)line;
			}
			catch( boost::bad_lexical_cast const& )
			{
					flexcout("casting went wrong on stepsize"); flexcout(line, 1);
					return 1;
			}
			break;
		case 6://read in nr of steps
			std::getline(inFile,line);
			try
			{
				this->nrost=boost::lexical_cast<unsigned int>(line);
			}
			catch( boost::bad_lexical_cast const& )
			{
					flexcout("casting went wrong on steps"); flexcout(line, 1);
					return 1;
			}
			break;
		default:
			break;
	}
	return 1;
}


