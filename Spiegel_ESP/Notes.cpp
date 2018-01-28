#include "Notes.h"



  Notes::Notes(){
    SPIFFS.begin();
    if(!SPIFFS.exists("/noteList.txt")){
      _noteList=SPIFFS.open("/noteList.txt","a");
      _noteList.print("0#");
      _noteList.close();
      }
    }

  String Notes::getNotesList(){
    _noteList=SPIFFS.open("/noteList.txt","r");
    String listContent = _noteList.readString();
    _noteList.close();
    return listContent;
    }


  boolean Notes::addNote(String note){
    _noteList=SPIFFS.open("/noteList.txt","a");
    if(!_noteList)return false;
    else{
      _noteList.print(note+",");
      _noteList.close();
      return true;
      }
    }

    boolean Notes::removeNote(int index,int checknumber_user){
      _noteList=SPIFFS.open("/noteList.txt","w");
     // int checknumber_local = toInt(_noteList.readStringUntil("#"));
      String listContent = _noteList.readString();
      String List;
      int count=0;
      int index_local = 0;
        while(listContent.indexOf(",",index_local) != -1)
        {
          index_local = listContent.indexOf("-",index_local);
          int tmp = listContent.indexOf(",",index_local);
            if(count!=index){
                 List += listContent.substring(index_local,tmp);
                 index_local = tmp;
                 count++;
            }
            else index_local=tmp;
            count++;
        }
        _noteList.print(List);
        _noteList.close();
        return true;
      }
      

    boolean Notes::edditNote(int index,int checknumber_user,String note){
      _noteList=SPIFFS.open("/noteList.txt","w");
     // int checknumber_local = toInt(_noteList.readStringUntil("#"));
      String listContent = _noteList.readString();
      String List;
      int count=0;
      int index_local = 0;
        while(listContent.indexOf(",",index_local) != -1)
        {
          index_local = listContent.indexOf("-",index_local);
          int tmp = listContent.indexOf(",",index_local);
          
            if(count!=index){
                 List += note;
                 index_local = tmp;
                 count++;
            }
            else {
            index_local=tmp;
            count++;
            }
        }
        _noteList.print(List);
        _noteList.close();
        return true;
      }
      

      int Notes::getListLength(){
        _noteList=SPIFFS.open("/noteList.txt","r");
        String listContent = _noteList.readString();
        int index_local=0;
        int listLength=0;
        while(listContent.indexOf(",",index_local) !=-1)
          {
            index_local = listContent.indexOf("-",index_local);
            int tmp = listContent.indexOf(",",index_local);
            index_local=tmp;
            listLength++;
          }
        return listLength;
        }

        String Notes::getNote(int index){
          _noteList=SPIFFS.open("/noteList.txt","r");
          String listContent = _noteList.readString();
          String note;
          int count=0;
          int index_local = 0;
            while(listContent.indexOf(",",index_local) != -1)
            {
              index_local = listContent.indexOf("-",index_local);
              int tmp = listContent.indexOf(",",index_local);
                if(count==index){
                     note=listContent.substring(index_local,tmp);
                     index_local = tmp;
                     count++;
            }
            else count++;
            _noteList.close();
          }
        return note;
        }

