/*
 * fileIOconditioning.cpp
 *
 *  Created on: Apr 25, 2013
 *      Author: admin
 */

#include "fileIOconditioning.h"
/**@struct filestructurelist
 * @brief case list for each structure
 *
 * mendeljef = was testcase that loads in table of elements
 * gas = loads in a list of species into a gas struct
 * accelerator = loads all other required parameters for the simulator
 *
 *@todo: split accelerator into a field description, a grid description and a boundary description then adjust the sim itself
 *@todo: separate this struct from fileIO into external h file or such
 **/
std::map<std::string, std::map< std::string, int> > filestructurelist{
	{"#mendeljef#",
		{{"#KEY#",-1},{"#NAME#",0},{"#UNIT#",1},{"#SIUNIT#",2},{"#SIFACTOR#",3},{"#CONTENT#",4}}
	},
	{"#gas#",
		{{"#NAME#",0},{"#SPECIES#",1}}
	},
	{"#accelerator#",
		{{"#NAME#",0},{"#E#",1},{"#B#",2},{"#X0#",3},{"#V0#",4},{"#DT#",5},{"#STEPS#",6}}
	}
};

/**@fn GetSpeciesData
 * @brief loads in a species file, see example speciesexample.txt for detailed formating
 *
 * @todo: all these getxxxyyy functions can and should be folded into one template like
 * function with all handlers externalised to the objects being filled in
 *
 * @todo insert a way to insert/ignore comments into an inputfile
 **/
void GetSpeciesData(GAS &gaslist, std::string filename)
{
  std::ifstream inFile(filename);//, std::ifstream::in );//| std::ifstream::binary); the whole flag thing doesn't work here can be compiler related
  gaslist.filename=filename;
  if (inFile.fail()) {
	  flexcout("unable to open file for reading");
      return;
  }
  std::string datatype="";
  if(inFile.good())
  {
	  std::string datatype=DataTypeonKey(inFile, filestructurelist);	//get the name of the keylist
	  if(!datatype.compare("?"))	//returns 0 when not equal, and no valid string was found
	  {
		  flexcout("file format wrong, no datatype", 1);
		  inFile.close();
		  return;
	  }
	  else {
		  flexcout("datatype was: "); flexcout(datatype,1);	//debug information
	  }
	  if(filestructurelist.find(datatype)==filestructurelist.end()){	//compare to keylist
		  flexcout("no such datatype known",1);
		  inFile.close();
		  return;
	  }
	  gaslist.filestructure=datatype; //save name into struct,
  }
  while(inFile.good())
    {
  	  int formatmode=ModeonKey(inFile, filestructurelist[gaslist.filestructure]);
  	  flexcout(formatmode);
  	  LineonKey(inFile, formatmode, gaslist);
    }
    inFile.close();
    flexcout("loaded:");flexcout(filename,1);
    return;
}

/**@fn GetAcceleratorData
 * @brief loads in a species file, see example speciesexample.txt for detailed formating
 *
 * @todo: all these getxxxyyy functions can and should be folded into one template like
 * function with all handlers externalised to the objects being filled in
 *
 * @todo insert a way to insert/ignore comments into an inputfile
 **/
void GetAcceleratorData(ACCELERATOR& ACC, std::string filename)
{
  std::ifstream inFile(filename);//, std::ifstream::in );//| std::ifstream::binary); the whole flag thing doesn't work here can be compiler related
  if (inFile.fail()) {
	  flexcout("unable to open file for reading");
      return;
  }
  std::string datatype="";
  if(inFile.good())
  {
	  std::string datatype=DataTypeonKey(inFile, filestructurelist);	//get the name of the keylist
	  if(!datatype.compare("?"))	//returns 0 when not equal, and no valid string was found
	  {
		  flexcout("file format wrong, no datatype", 1);
		  inFile.close();
		  return;
	  }
	  else {
		  flexcout("datatype was: "); flexcout(datatype,1);	//debug information
	  }
	  if(filestructurelist.find(datatype)==filestructurelist.end())//compare to keylist
	  {
			  flexcout("no such datatype known",1);
			  inFile.close();
			  return;
	  }
	  ACC.filestructure=datatype; //save name into struct,
  }
  while(inFile.good())
  {
	  int formatmode=ModeonKey(inFile, filestructurelist[ACC.filestructure]);
	  flexcout(formatmode);
	  LineonKey(inFile, formatmode, ACC);
  }
  inFile.close();
  flexcout("loaded: ");flexcout(filename,1);
  return;
}
/**@fn GetAcceleratorData_DB
 * @brief loads in a species from the database
 *
 * @todo: all these getxxxyyy functions can and should be folded into one template like
 * function with all handlers externalised to the objects being filled in
 **/
void GetSpeciesData_DB(GAS &gaslist, Sqlitedb & db)
{
	gaslist.filename="filenameplaceholder";
	gaslist.filestructure="gasdb"; //save name into struct,
	gaslist.name="dbtableplaceholdername";
	db.exec("SELECT * FROM gas");
	for(unsigned int i=0;i<db.data.size();i++)
	{
		SPECIES spec={	db.data[i][0],
						e*boost::lexical_cast<int>(db.data[i][1]),//charge
						u*boost::lexical_cast<unsigned int>(db.data[i][2]),//mass
						boost::lexical_cast<unsigned int>(db.data[i][3])};//concentration
		gaslist.constituents.push_back(spec);
	}
    flexcout("loaded: ");flexcout(gaslist.filename,1);
    return;
}

/**@fn GetAcceleratorData_DB
 * @brief loads in a species file, see example speciesexample.txt for detailed formating
 *
 * @todo: all these getxxxyyy functions can and should be folded into one template like
 * function with all handlers externalised to the objects being filled in
 *
 * @todo insert a way to insert/ignore comments into an inputfile
 **/
void GetAcceleratorData_DB(ACCELERATOR& ACC, Sqlitedb & db)
{
	//dbg.Efield,dbg.Bfield, dbg.v0, dbg.x0, dbg.Dt, dbg.nrost
	/*std::string filestructure;
		std::string name;//0
		Field Efield;
		Field Bfield;
		VectorPoint x0;//3
		VectorPoint v0;
		mpelement Dt;
		unsigned int nrost;*/
	ACC.name="nameplaceholder";
	db.exec("SELECT * FROM efield");
	for(unsigned int i=0;i<db.data.size();i++)
	{
		ACC.Efield = Field( mpelement(db.data[i][1]), mpelement(db.data[i][2]), mpelement(db.data[i][3]));
	}
	db.exec("SELECT * FROM bfield");
	for(unsigned int i=0;i<db.data.size();i++)
	{
		ACC.Bfield = Field( mpelement(db.data[i][1]), mpelement(db.data[i][2]), mpelement(db.data[i][3]));
	}
	db.exec("SELECT X0 FROM start");
	for(unsigned int i=0;i<db.data.size();i++)
	{
		ACC.x0 = VectorPoint( mpelement(db.data[i][1]), mpelement(db.data[i][2]), mpelement(db.data[i][3]));
	}
	db.exec("SELECT V0 FROM start");
	for(unsigned int i=0;i<db.data.size();i++)
	{
		ACC.v0 = VectorPoint( mpelement(db.data[i][1]), mpelement(db.data[i][2]), mpelement(db.data[i][3]));
	}
	db.exec("SELECT DT FROM time");
	for(unsigned int i=0;i<db.data.size();i++)
	{
		ACC.Dt = mpelement(db.data[i][1]);
	}
	db.exec("SELECT STEPS FROM time");
	for(unsigned int i=0;i<db.data.size();i++)
	{
		ACC.nrost = boost::lexical_cast<unsigned int>(db.data[i][1]);
	}
    flexcout("loaded: ");flexcout(ACC.name,1);
    return;
}
/**@fn DataTypeonKey
 * @brief takes a line and returns the datatype for reading the correct keylist from \struct filestructurelist
 *
 * @param inFile filestream
 * @param keylist filestructurelist always now
 * @return string to be used as key for selecting keylist, "?" in case of failure
 */
template <class T> std::string DataTypeonKey(std::ifstream &inFile, T keylist){
	std::string line;
	std::getline(inFile,line);//get next line
	std::string type="?";//predefine fail value
	typename T::iterator it;
	if ( (it = keylist.find(line)) != keylist.end() )//look for the key
	{
	    type=it->first;
	}
	return type;
}

/**@fn ModeonKey
 * @brief takes a line and returns the mode for passing the correct case to the structs filler
 *
 * @param inFile filestream
 * @param keylist correct keylist from filestructurelist, determined by \fn DataTypeonKey
 * @return int to be passed to @fn lineonkey for modifying next line(s), -2 in case of failure
 */
template <class T> int ModeonKey(std::ifstream &inFile, T &keylist){
	std::string line;
	std::getline(inFile,line);
	//int type=-2;
	typename T::iterator it;
		if ( (it = keylist.find(line)) != keylist.end() )
		{
		    return it->second;
		}
	return -2;
}

/**@fn LineonKey
 * @brief calls filler with arguments
 *
 * @param inFile filestream
 * @param linemo int identifying what to do with next line(s), determined by \fn ModeeonKey
 * @param newset to be used as key for selecting keylist
 * @return 1 on success 0 on failure
 */
template <class T> int LineonKey(std::ifstream &inFile, int linemo, T &newset){
	newset.filler(inFile,linemo);
	return 1;
}
/**@fn outfile constructor
 * @brief to refer to an open output file
 *
 * @param filename, filename in string format
 * @param delim delimitor between inputs
 */
outfile::outfile(std::string filename,char delim){
	out.open(filename);
	this->filename=filename;
	this->delim=delim;
}
outfile::~outfile(){
	out.close();
}
std::ofstream& outfile::target(){
	return out;
}
/** @fn delim
 * @brief return delimiter
 * @return
 */
char outfile::delimit()
{
	return delim;
}
