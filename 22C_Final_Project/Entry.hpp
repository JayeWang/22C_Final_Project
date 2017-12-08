//
//  Entry.hpp
//  22C_HashTable_OpenAddressing
//
//  Created by ZHOU WANG on 11/25/17.
//  Copyright © 2017 ZHOU WANG. All rights reserved.
//

#ifndef Entry_h
#define Entry_h

#include <iostream>

const int OCCUPIED = 1;
const int EMPTY = 0;
const int REMOVED = -1;

template <class ItemType>
class Entry
{
private:
   int state;
   std::string key;
   ItemType item;
   
public:
   Entry():state(0), key("no key"), item(0){};
   ~Entry(){}
   void setState(const int& theState){state = theState;}
   void setKey(const std::string& theKey){key = theKey;}
   void setItem(const ItemType& theItem){item = theItem;}
   
   int getState() const {return state;}
   std::string getKey() const {return key;}
   ItemType getItem() const {return item;}
   
};

#endif
