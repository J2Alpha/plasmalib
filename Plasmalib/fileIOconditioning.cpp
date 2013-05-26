/*
 * fileIOconditioning.cpp
 *
 *  Created on: Apr 25, 2013
 *      Author: admin
 */

#include "fileIOconditioning.h"
//case list for each structure
//mendeljef = testcase loads in table of elements
//gas = loads in a list of species into a gas struct
//todo: separate into external h file
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
/*todo: all these getxxxyyy functions can and should be folded into one template like
 * function with all handlers externalised to the objects being filled in
 * btw getfiledata has become useless.
 */
void GetFileData(DataSet &newset, std::string filename)
{
  std::ifstream inFile(filename);//, std::ifstream::in );//| std::ifstream::binary); the whole flag thing doesn't work here can be compiler related
  if (inFile.fail()) {
	  flexcout("unable to open file for reading");
      return;
  }
  std::string filestructure="";
  if(inFile.good())
  {
	  std::string datatype=DataTypeonKey(inFile, filestructurelist);	//get the name of the keylist
	  if(!datatype.compare("?"))	//returns 0 when not equal, and no valid string was found
	  {
		  flexcout("file format wrong, no filestructure", 1);
		  inFile.close();
		  return;
	  }
	  else {
		  flexcout("filestructure was: "); flexcout(filestructure,1);	//debug information
	  }
	  if(filestructurelist.find(datatype)==filestructurelist.end()){	//compare to keylist
		  flexcout("no such filestructure known",1);
		  inFile.close();
		  return;
	  }
	  newset.filestructure=filestructure; //save name into struct,
  }
  //--NAME OFF LIST DONE--
  //start of key
  	  /*std::cout <<"content of keylist :";
  	  for(std::map< std::string, int>::iterator it = listtypekey[newset.datatype].begin(); it != listtypekey[newset.datatype].end(); ++it)
  	  {
  		  std::cout << it->first << "\n";
  	  }*/
  int formatmode=ModeonKey(inFile, filestructurelist[newset.filestructure]);//, datatype);//compare nextline sublist containing keys
  //flexcout(formatmode,1);
  //solved this, don't know how, I just wrote exactly the same but slightly different, refer now to newset.datatype
  //in stead of the original datatype variable, what the fuck was with that.
  if(formatmode==-1){
	  LineonKey(inFile, formatmode, newset);
  }
  else{
	  flexcout("first newline has to be KEY to data",1);
	  return;
  }
  flexcout("KEY position is : ");flexcout(newset.keyposition,1);
  //--KEY DONE--
  //start on filling the whole struct
  while(inFile.good())
  {
	  formatmode=ModeonKey(inFile, filestructurelist[newset.filestructure]);
	  flexcout(formatmode);
	  LineonKey(inFile, formatmode, newset);
  }
  inFile.close();
  flexcout("loaded:");flexcout(filename,1);
  return;
}

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

template <class T> int LineonKey(std::ifstream &inFile, int linemo, T &newset){
	newset.filler(inFile,linemo);
	return 1;
}

int RawStringData::filler(std::ifstream &inFile, int linemo)
{
	std::string line;
	std::vector<std::string> results;
	unsigned int kp=0;
	int ir=0;
	switch(linemo)
		{
			case -1://get the key position
				std::getline(inFile,line);
				try {
					kp = boost::lexical_cast<unsigned int>(line);
				} catch( boost::bad_lexical_cast const& ) {
					flexcout("key is not an unsigned int, keyline was: "); flexcout(line, 1);
					return 0;
				}
				if(kp<=0){
					flexcout("key cannot be 0 or less, key: "); flexcout(kp,1);
					return 0;
				}
				//flexcout("keynow: ");flexcout(kp);
				this->keyposition=(kp-1);//corrected for vectors possible keypos 0ness
				break;
			case 0://read in names of colls
				std::getline(inFile,line);
				boost::split(results, line, boost::is_any_of("\t"));
				this->names=results;
				for( std::vector<std::string>::const_iterator i = results.begin(); i != results.end(); ++i){
									flexcout(*i,1);
								}
				//flexcout("name done",1);
				//for( std::vector<std::string>::const_iterator i = newset.names.begin(); i != newset.names.end(); ++i){
						//flexcout(*i,1);
					//}
				break;
			case 1://read in units of colls
				std::getline(inFile,line);
				boost::split(results, line, boost::is_any_of(",\t"));
				this->units=results;
				//flexcout("unit done",1);
				break;
			case 2://read in SIunits of colls
				std::getline(inFile,line);
				boost::split(results, line, boost::is_any_of(",\t"));
				this->SIunits=results;
				//flexcout("si unit done",1);
				break;
			case 3://read in SIfactor to go from unit to siunit of colls
				std::getline(inFile,line);
				boost::split(results, line, boost::is_any_of(",\t"));
				this->SIfactors=results;
				//flexcout("factor done",1);
				break;
			case 4://read in ccontent //
				do{
				std::getline(inFile,line);
				//flexcout("line compared : ");flexcout(line, 1);
				//flexcout("valid: ");flexcout(line.compare("#END#"),1);
					if(inFile.good() && line.compare("#END#")){
						boost::split(results, line, boost::is_any_of("\t"));
						this->data.insert(make_pair(results[kp],results));
						flexcout("loading :");flexcout(ir,1);
						ir++;
					}
				}while(line.compare("#END#"));
				break;
			default:
				break;
		}
	return 1;
}

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
