#ifndef __Notes_H_INCLUDED__
#define __Notes_H_INCLUDED__

#include <FS.h>

class Notes 
{
   private:
   File _noteList;

   public:
   Notes();
   String getNotesList();
   boolean addNote(String);
   boolean removeNote(int,int);
   boolean edditNote(int,int,String);
   String getNote(int);
   int getListLength();
  
};

#endif 
