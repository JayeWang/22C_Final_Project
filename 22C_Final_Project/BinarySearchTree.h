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
	BinaryNode<ItemType>* _insert(bool compare(ItemType &, ItemType &), BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);

	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);

	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);

	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);

	// search for target node
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType & target) const;

	// find the largest node
	BinaryNode<ItemType>* _findLargest(BinaryNode<ItemType>* rootPtr) const;

	// find the smallest node
    BinaryNode<ItemType>* _findSmallest(BinaryNode<ItemType>* rootPtr) const;

public:
	// insert a node at the correct location
    bool insert(bool compare(ItemType &, ItemType &), const ItemType & newEntry);
	// remove a node if found
	bool remove(const ItemType & anEntry);
	// find a target node
	bool getEntry(const ItemType & target, ItemType & returnedItem) const;
	// find the largest node
	bool findLargest(ItemType & target) const;
	// find the smallest node
    bool findSmallest(ItemType & target) const;
};


///////////////////////// public function definitions ///////////////////////////

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(bool compare(ItemType &, ItemType &), const ItemType & newEntry)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	this->rootPtr = _insert(compare, this->rootPtr, newNodePtr);
	return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target)
{
	bool isSuccessful = false;
	this->rootPtr = _remove(this->rootPtr, target, isSuccessful);
	return isSuccessful;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry, ItemType & returnedItem) const
{
    BinaryNode<ItemType>* data = findNode(this->rootPtr, anEntry);
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
//////////////////////////// private functions ////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(bool compare(ItemType&, ItemType&), BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr)
{
    if (nodePtr == NULL)
        return newNodePtr;
	else
	{
		BinaryNode<ItemType>* tempPtr;
		ItemType temp1 = nodePtr->getItem();
		ItemType temp2 = newNodePtr->getItem();
		if (compare(temp1, temp2))
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
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
                                                          const ItemType target,
                                                          bool & success)
{
	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}
	if (nodePtr->getItem() > target)
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (nodePtr->getItem() < target)
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
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
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
                                                           const ItemType & target) const
{
    if (nodePtr == NULL)
        return NULL;
    else if (nodePtr->getItem() == target)
        return nodePtr;
    else if (nodePtr->getItem() > target)
        return findNode(nodePtr->getLeftPtr(),target);
    else
        return findNode(nodePtr->getRightPtr(),target);
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
