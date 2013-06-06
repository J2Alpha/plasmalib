/*
 * Sqlitedb.cpp
 *
 *  Created on: 6-jun.-2013
 *      Author: admin
 */

#include "Sqlitedb.h"


Sqlitedb::Sqlitedb(std::string tablename): zErrMsg(0), rc(0), db_open(0)
{
	rc = sqlite3_open(tablename.c_str(), &db);
	if( rc ){
	    flexcout("Can't open database: ");flexcout(sqlite3_errmsg(db),1);
	    sqlite3_close(db);
	  }
	  db_open=1;
}

Sqlitedb::~Sqlitedb() {
	sqlite3_close(db);
}

int Sqlitedb::exec(std::string s_exe) {
    rc = sqlite3_get_table(
			db,              /* An open database */
			s_exe.c_str(),       /* SQL to be executed */
			&result,       /* Result written to a char *[]  that this points to */
			&nrow,             /* Number of result rows written here */
			&ncol,          /* Number of result columns written here */
			&zErrMsg          /* Error msg written here */
			);
    if(header.size()!=0)
    {
    	header.clear();
    }
    if(data.size()!=0)
    {
    	data.clear();
    }

   if( rc == SQLITE_OK ){
	   for(int i=0; i < ncol; ++i)
		   header.push_back(result[i]);   /* First row heading */
	   for(int j=0;j < nrow;j++){
		   for(int i=0; i < ncol; ++i){
			   data[j].push_back(result[j*ncol+i]);
		   }

	   }

   }
   sqlite3_free_table(result);
   return rc;
}
