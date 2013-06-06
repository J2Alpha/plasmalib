/*
 * Sqlitedb.h
 *
 *  Created on: 6-jun.-2013
 *      Author: admin
 */

#ifndef SQLITEDB_H_
#define SQLITEDB_H_

#include <vector>
#include <string>

#include "sqlite_amalgated\sqlite3.h"
#include "UserIOconditioning.h"

class Sqlitedb
{
	private:
	    sqlite3 *db;
	    char *zErrMsg;
	    char **result;
	    int rc;
	    int nrow,ncol;
	    int db_open;

	public:

	    Sqlitedb(std::string tablename="temp.db");//start a db connector or make a new one
	    ~Sqlitedb();//
	    int exec(std::string s_exe);//get a vector of vector table of results
	    std::vector< std::string> header;
	    std::vector< std::vector< std::string > > data;

};

#endif /* SQLITEDB_H_ */
