//
//  HashTable.hpp
//  22C_HashTable_OpenAddressing
//
//  Created by ZHOU WANG on 11/25/17.
//  Copyright © 2017 ZHOU WANG. All rights reserved.
//

#ifndef HashTable_hpp
#define HashTable_hpp
#include "Entry.hpp"
#include <vector>
#include <ctime>

const int ADD_CHOICE = 1;
const int REMOVE_CHOICE = -1;
const int NOT_FOUND = -1;

template <class ItemType>
class HashTable
{

private:
   Entry<ItemType> * element; /* hold the address of an array of Entrys */
   int tableSize; /* Hash table size */
   int numTableItems;/* Current number of occupied items in the table */
   double loadFactor;/* ratio of the current number of items in the dictionary to the maximum size of the hash table, loadFactor measure how full the hash table is */
   int numCollisions;/* Counter of the number of collisions */

//   private member functions
   void alloc();
   void release();
   int hashIndex(const std::string& key);/* hashing function */
   int getNextHashIndex(const int& index,const int& offSet); /* collision resolution member funtion */
   void addEntry(const int& i,const std::string& key,const ItemType& item);
   void deleteEntry(const int& i);
   void updateStats(const int& choice);
   int search(const std::string& key, const int& index);
   void reHashing();
   bool isKeyExist(const std::string& key);

   static const int DEFAULT_SIZE = 101;
   const double MAX_LOAD_FACTOR = 0.75 ;

public:
   HashTable();
   HashTable(const int& size);
   ~HashTable();
   bool insert(const std::string& key, const ItemType& item);
   bool getItem(const std::string& key, ItemType& item);
   bool remove(const std::string& key);
   void displayItems(void visit(ItemType &)) const;
   std::vector<Entry<ItemType>> getItems();
   void displayStatistics();
   int getTableSize() const {return tableSize;};
   int getNumTableItems() const {return numTableItems;}
   double getLoadFactor() const {return loadFactor;}
   int getNumCollisions() const {return numCollisions;}
};


///////////////////////////////////////////////////////////////////////////////////////
////////////////////////////Private Member functions///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
// alloc alloctes memory for the hash table
template <class ItemType>
void HashTable<ItemType>::alloc()
{
   element = new Entry<ItemType> [tableSize];
}

// release release the memory the array of pointers
template <class ItemType>
void HashTable<ItemType>::release()
{
   delete [] element;
   element = nullptr;
   numCollisions = 0;
   numTableItems = 0;
   loadFactor = 0;
}

// hashIndex: address calculator, returns a hashed index
// based the parameter key
template <class ItemType>
int HashTable<ItemType>::hashIndex(const std::string& key)
{
   int hashCode = 0;
   for (int i = 0; i < key.size(); i++)
   {
      hashCode += ((int)key[i])*((int)key[i]);
   }
   return hashCode % tableSize;
}

// getNextHashIndex returns the next available index location
// based on the currrent collision index
template <class ItemType>
int HashTable<ItemType>::getNextHashIndex(const int& index,
                                          const int& offSet)
{

   //   linear probe by just looking for the right next location
   //   return (index+1) % tableSize;

   //   revised linear probe, using add 1 -2 +3 -4 pattern
   return (index+offSet) % tableSize;
}

// i : the location of the entry to be added to the hash table
// key: the key to be added to the hash table
// item: the item to be added to the hash table
template <class ItemType>
void HashTable<ItemType>::addEntry(const int& i,const std::string& key,const ItemType& item)
{
   element[i].setKey(key);
   element[i].setItem(item);
   element[i].setState(OCCUPIED);
   updateStats(ADD_CHOICE);

   if (loadFactor >= MAX_LOAD_FACTOR)
      reHashing();
}

// deleteEntry: remove the item at location i in the hash table
// by simply set the state of the item to REMOVED.
// Note: the actual entry is not removed neither reseted becasue
// the insert and remove operation only look at the state.
template <class ItemType>
void HashTable<ItemType>::deleteEntry(const int &i)
{
   element[i].setState(REMOVED);
   updateStats(REMOVE_CHOICE);
}

// updateStats: update numTableItems(the current number of items in the table)
// and loadFactor(ratio of the current number of items in the dictionary to the maximum
// size of the hash table)
// -----------------------
// choice: could be ADD_CHOICE if it is called by the insert operation
//               OR REMOVE_CHOICE if it is called by the remove operation
template <class ItemType>
void HashTable<ItemType>::updateStats(const int& choice)
{
   if (choice == ADD_CHOICE)
      numTableItems++;
   else
      numTableItems--;

   loadFactor = numTableItems*1./tableSize;
}

// search: search target key in a probe sequence
// return: -1 if not found
//         the index found based on key
template <class ItemType>
int HashTable<ItemType>::search(const std::string& key, const int &index)
{
   int i = index;
   Entry<ItemType> currEntry;
   
   int offSet = 0;
   int offSetCopy;
   
   while (1)
   {
      offSet++;
      offSetCopy = offSet;

      if (offSet%2 == 0)
         offSetCopy = -offSet;

      i = getNextHashIndex(i, offSetCopy);
      currEntry = element[i];

      if(currEntry.getState() == EMPTY || i == index)
         return -1; // not found

      //getItem operation continue probing when it encounters a location in the removed state. ***important***
      if(currEntry.getState() == REMOVED)
         continue;

      if (currEntry.getKey() == key)
         break;
   }

   return i;
}

// reHashing, release old tableSize of Entrys and recreate a new hash
// table with new table size(one larger the doubled original size)
template <class ItemType>
void HashTable<ItemType>::reHashing()
{
   // temperialy hold all Entries
   std::vector<Entry<ItemType>> items = getItems();
   release();
   tableSize = 2*tableSize + 1;
   alloc();
   
   for(int i = 0; i < items.size(); i++ )
      insert(items[i].getKey(), items[i].getItem());
   
   std::cout << "Hash Table is resized to " << tableSize << std::endl;
}


template <class ItemType>
bool HashTable<ItemType>::isKeyExist(const std::string & key)
{
   int i = hashIndex(key);
   
   if (element[i].getState() == OCCUPIED &&  element[i].getKey() == key)
      return true;
   
   i = search(key, i);
   
   if (i == NOT_FOUND)
      return false;
   else
      return true;
}

///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// ///////// Constructors////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

// Default constrcutor HashTable: create an hash table with default size
template <class ItemType>
HashTable<ItemType>::HashTable():tableSize(DEFAULT_SIZE),numTableItems(0), numCollisions(0),loadFactor(0)
{
   alloc();
}

// Constructor HashTable
template <class ItemType>
HashTable<ItemType>::HashTable(const int& size):tableSize(size),numTableItems(0), numCollisions(0),loadFactor(0)
{
   alloc();
}

///////////////////////////////////////////////////////////////////////////////////////
////////////////////////////Public Member functions////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

// Insert: insert an new entry to the hash table
// key: the key of the new entry to be added to the hash table
// item: the item of the new entry to be added to the hash table
template <class ItemType>
bool HashTable<ItemType>::insert(const std::string &key, const ItemType& item)
{
   // disallow duplicate insertion
   bool isExistAlready = isKeyExist(key);
   if (isExistAlready)
      return false;

   int i = hashIndex(key);
   if (element[i].getState() != OCCUPIED)
   {
      addEntry(i, key, item);
      return true;
   }
   
   int offSet = 0;
   int offSetCopy;
   while (element[i].getState() == OCCUPIED)
   {
      offSet++;
      offSetCopy = offSet;
      if (offSet%2 == 0)
         offSetCopy = -offSet;
      
      i = getNextHashIndex(i, offSetCopy);
      numCollisions++;
   }
   
   addEntry(i, key, item);
   return true;

}

// getItem: retrive the item that is associated with the particular key
// value specified in the argument.
// -----------------------------------------------------------------------------
// If the firstly hashed item is the target item, copy the target item to the arugment item
// and return true
// Otherwise, call search function to search in the probe sequence
//       if target item found, copy target item to arguement item and return true
//       else return false

template <class ItemType>
bool HashTable<ItemType>::getItem(const std::string &key, ItemType& item)
{
   int i = hashIndex(key);

   if (element[i].getState() == OCCUPIED && element[i].getKey() == key)
   {
      item = element[i].getItem();
      return true;
   }

   i = search(key, i);

   if (i == NOT_FOUND)
      return false;
   else
   {
      item = element[i].getItem();
      return true;
   }
}

// remove: removes the entry associated with same key value as the argument key
// -----------------------------------------------------------------------------
// If the hashed location is the target item, delete the Entry and return
// Otherwise search the linear probe sequence
//     if found delete the found entry and return true
//     else return false
template <class ItemType>
bool HashTable<ItemType>::remove(const std::string &key)
{
   int i = hashIndex(key);
   if (element[i].getState() == OCCUPIED && element[i].getKey() == key)
   {
      deleteEntry(i);
      return true;
   }
   
   i = search(key, i);

   if (i == NOT_FOUND)
      return false;
   else
   {
      deleteEntry(i);
      return true;
   }
}

// displayItems display items in unsorted order same as the hash table
// sequence
template <class ItemType>
void HashTable<ItemType>::displayItems(void visit(ItemType &)) const
{
   for (int i = 0; i < tableSize; i++)
   {
      Entry<ItemType> curr = element[i];
      if (curr.getState()==OCCUPIED)
      {
         ItemType temp = curr.getItem();
         visit(temp);
      }
   }
}

// getItems: return all Entrys that are occupied in the hash table as a vector of Entrys
template <class ItemType>
std::vector<Entry<ItemType>> HashTable<ItemType>::getItems()
{
   std::vector<Entry<ItemType>> items;

   for (int i = 0 ; i < tableSize; i++)
   {
      Entry<ItemType> curr = element[i];
      if (curr.getState()== OCCUPIED)
      {
         items.push_back(curr);
      }
   }

   return items;
}

// displayStatistics: display hash table size,
//                    number of items currently occupied,
//                    load factor,
//                    numbers of collisions occurred.
template <class ItemType>
void HashTable<ItemType>::displayStatistics()
{
   std::cout << "-------------------------------------\n";
   std::cout << "    HashTable size: " << tableSize << std::endl;
   std::cout << "    Filled items: " << numTableItems << std::endl;
   std::cout << "    Load Factor: " << loadFactor << std::endl;
   std::cout << "    Number of collisions: " << numCollisions << std::endl;
   std::cout << "-------------------------------------\n";
}


// Destructor ~HashTable release memory for the hash table
template <class ItemType>
HashTable<ItemType>::~HashTable()
{
   release();
}

#endif /* HashTable_hpp */
