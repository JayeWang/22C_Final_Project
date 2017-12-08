// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.
// Modified by:

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE
#include <iostream>
#include "BinaryTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(int compare(ItemType &,ItemType &), BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);

	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(int compare(ItemType &, ItemType &),BinaryNode<ItemType>* nodePtr, ItemType target, bool & success);

	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);

	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);

	// search for target node
	BinaryNode<ItemType>* findNode(int compare( ItemType &,ItemType &),BinaryNode<ItemType>* treePtr, ItemType & target) const;

	// find the largest node
	BinaryNode<ItemType>* _findLargest(BinaryNode<ItemType>* rootPtr) const;

	// find the smallest node
    BinaryNode<ItemType>* _findSmallest(BinaryNode<ItemType>* rootPtr) const;

public:
	// insert a node at the correct location
    bool insert(int compare(ItemType &, ItemType &), const ItemType & newEntry);
	// remove a node if found
	bool remove(int compare(ItemType &, ItemType &),const ItemType & anEntry);
	// find a target node
	bool getEntry(int compare( ItemType &, ItemType &), ItemType & target, ItemType & returnedItem) const;
	// find the largest node
	bool findLargest(ItemType & target) const;
	// find the smallest node
    bool findSmallest(ItemType & target) const;
    // find the target node (the function just return true or false, not return any data that match with the target)
    bool search(void visit (ItemType &),int compare( ItemType &, ItemType &), ItemType & target);
};


///////////////////////// public function definitions ///////////////////////////

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(int compare(ItemType &,ItemType &), const ItemType & newEntry)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	this->rootPtr = _insert(compare, this->rootPtr, newNodePtr);
	return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(int compare(ItemType &,ItemType &),const ItemType & target)
{
	bool isSuccessful = false;
	this->rootPtr = _remove(compare,this->rootPtr, target, isSuccessful);
	return isSuccessful;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(int compare(ItemType &, ItemType &), ItemType& anEntry, ItemType & returnedItem) const
{
    BinaryNode<ItemType>* data = findNode(compare,this->rootPtr, anEntry);
    if (data == NULL)
        return false;
    else
    {
        returnedItem = data->getItem();
        return true;
    }
}

template<class ItemType>
bool BinarySearchTree<ItemType>::findLargest(ItemType & returnedItem) const
{
    BinaryNode<ItemType>* data = _findLargest(this->rootPtr);
    if (data == NULL)
        return false;
    else
    {
        returnedItem = data->getItem();
        return true;
    }
}


template<class ItemType>
bool BinarySearchTree<ItemType>::findSmallest(ItemType & returnedItem) const
{
    BinaryNode<ItemType>* data = _findSmallest(this->rootPtr);
    if (data == NULL)
        return false;
    else
    {
        returnedItem = data->getItem();
        return true;
    }
}
template<class ItemType>
bool BinarySearchTree<ItemType>::search(void visit(ItemType &), int compare(ItemType &,ItemType &), ItemType & target)
{
    bool found = false;
    BinaryNode<ItemType>* nodePtr = this->rootPtr;
    BinaryNode<ItemType>* data = findNode(compare, nodePtr, target);
    if(data != NULL) found = true;
    while(data != NULL){
        ItemType item = data->getItem();
        visit(item);
        data = findNode(compare, data->getLeftPtr(), target);
    }
    return found;
}
//////////////////////////// private functions ////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(int compare(ItemType&, ItemType&), BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr)
{
    if (nodePtr == NULL)
        return newNodePtr;
	else
	{
		BinaryNode<ItemType>* tempPtr;
		ItemType temp1 = nodePtr->getItem();
		ItemType temp2 = newNodePtr->getItem();
		if (compare(temp1, temp2) >= 0)
		{
			tempPtr = _insert(compare, nodePtr->getLeftPtr(), newNodePtr);
			nodePtr->setLeftPtr(tempPtr);
		}
		else
		{
			tempPtr = _insert(compare, nodePtr->getRightPtr(), newNodePtr);
			nodePtr->setRightPtr(tempPtr);
		}
	}
    return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(int compare(ItemType &,ItemType &),BinaryNode<ItemType>* nodePtr,
                                                           ItemType target,
                                                          bool & success)
{
	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}
    ItemType temp1 = nodePtr->getItem();
	if (compare(temp1,target) > 0)
		nodePtr->setLeftPtr(_remove(compare,nodePtr->getLeftPtr(), target, success));
	else if (compare(temp1,target) < 0)
		nodePtr->setRightPtr(_remove(compare,nodePtr->getRightPtr(), target, success));
	else
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
	}
	return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else
	{
		ItemType newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}
}


template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(int compare(ItemType &, ItemType &),BinaryNode<ItemType>* nodePtr, ItemType & target) const
{
    if (nodePtr == NULL)
        return NULL;
    else
    {
        ItemType temp1 = nodePtr->getItem();
        if (compare(temp1,target) == 0)
            return nodePtr;
        else if (compare(temp1,target) > 0)
            return findNode(compare,nodePtr->getLeftPtr(),target);
        else
            return findNode(compare,nodePtr->getRightPtr(),target);
    }
}


template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_findLargest(BinaryNode<ItemType>* nodePtr) const
{
    BinaryNode<ItemType>* lastPtr = NULL;
    while (nodePtr != NULL)
    {
        lastPtr = nodePtr;
        nodePtr = nodePtr->getRightPtr();
    }
    return lastPtr;
}


template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_findSmallest(BinaryNode<ItemType>* nodePtr) const
{
    BinaryNode<ItemType>* lastPtr = NULL;
    while (nodePtr != NULL)
    {
        lastPtr = nodePtr;
        nodePtr = nodePtr->getLeftPtr();
    }
    return lastPtr;
}
#endif
