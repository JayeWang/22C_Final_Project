// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by:

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "Queue.h"
#include "StackADT.h"
#include <iostream>
#include <iomanip>
template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
 	BinaryTree() {rootPtr = 0; count = 0;}
	BinaryTree(const BinaryTree<ItemType> & tree){rootPtr = copyTree(tree.rootPtr); count = tree.count;}
	virtual ~BinaryTree() {destroyTree(rootPtr);}
	BinaryTree & operator = (const BinaryTree & sourceTree);

	// common functions for all binary trees
 	bool isEmpty() const	{return count == 0;}
	int size() const	    {return count;}
	void preOrder(void visit(ItemType &)) const             {_preorder(visit, rootPtr);}
	void inOrder(void visit(ItemType &)) const              {_inorder(visit, rootPtr);}
	void postOrder(void visit(ItemType &)) const            {_postorder(visit, rootPtr);}
    void breadthFirstOrder(void visit(ItemType &)) const    {_breadthFirstOrder(visit, rootPtr);}
    void printIndented(void visit(ItemType &, int&)) const  {_printIndented(visit, rootPtr,0);}
    void clear (void visit (ItemType &))                    {_clear(visit,rootPtr);}

    //  iterative Algorithm Traverses
    void iterativePreorder(void visit(ItemType &)) const{_iterativePreorder(visit, rootPtr);}
    void iterativeInorder(void visit(ItemType &)) const{_iterativeInorder(visit, rootPtr);}

	// abstract functions to be implemented by derived class
    virtual bool insert(int compare(ItemType &, ItemType &), const ItemType & newData) = 0;
	virtual bool remove(int compare( ItemType &,  ItemType &), const ItemType & data) = 0;
	virtual bool getEntry(int compare(ItemType &, ItemType &), ItemType & anEntry, ItemType & returnedItem) const = 0;

private:
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);
    void _clear(void visit(ItemType &),BinaryNode<ItemType>* nodePtr) const;
	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
    // traverse in reverse order
	void _breadthFirstOrder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
    void _printIndented(void visit(ItemType &, int &), BinaryNode<ItemType>* nodePtr, int indent) const;
    // iterative traverses
	void _iterativePreorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _iterativeInorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
};

//////////////////////////////////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr)
{
	BinaryNode<ItemType>* newNodePtr = 0;

    if (nodePtr != NULL)
    {
        newNodePtr = new BinaryNode<ItemType>(nodePtr->getItem());
        newNodePtr->setLeftPtr(copyTree(nodePtr->getLeftPtr()));
        newNodePtr->setRightPtr(copyTree(nodePtr->getRightPtr()));
    }
    else
        return NULL;
    return newNodePtr;
}

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
    if (nodePtr != NULL)
    {
        destroyTree(nodePtr->getLeftPtr());
        destroyTree(nodePtr->getRightPtr());
        delete nodePtr;
		nodePtr = 0;
		count = 0;
    }
}

template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		_inorder(visit, nodePtr->getLeftPtr());
		ItemType item = nodePtr->getItem();
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		ItemType item = nodePtr->getItem();
		visit(item);
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_breadthFirstOrder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr!=NULL)
    {
        Queue<BinaryNode<ItemType>*>* q = new Queue<BinaryNode<ItemType>*>;
        BinaryNode<ItemType>* itemPtr;

        q->enqueue(nodePtr);
        while (!q->isEmpty())
        {
            q->dequeue(itemPtr);
            ItemType item = itemPtr->getItem();
            visit(item);
            if (itemPtr->getLeftPtr() != NULL)
                q->enqueue(itemPtr->getLeftPtr());
            if (itemPtr->getRightPtr() != NULL)
                q->enqueue(itemPtr->getRightPtr());
        }
    }
}

template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{
	if (this != &sourceTree)
	{
		this->clear();
		rootPtr = this->copyTree(sourceTree.rootPtr);
		count = sourceTree.count;
	}
	return *this;
}

template<class ItemType>
void BinaryTree<ItemType>::_printIndented(void visit(ItemType &, int&), BinaryNode<ItemType>* nodePtr, int indent) const
{
	if (nodePtr != 0)
	{
	    indent++;
		_printIndented(visit, nodePtr->getRightPtr(),indent);
		ItemType item = nodePtr->getItem();
		visit(item,indent);
		_printIndented(visit, nodePtr->getLeftPtr(),indent);
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_iterativePreorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr!=NULL)
    {
        Stack<BinaryNode<ItemType>*>* s = new Stack<BinaryNode<ItemType>*>;
        BinaryNode<ItemType>* itemPtr;

        s->push(nodePtr);
        while (!s->isEmpty())
        {
            s->pop(itemPtr);
            ItemType item = itemPtr->getItem();
            visit(item);
            if (itemPtr->getRightPtr() != NULL)
                s->push(itemPtr->getRightPtr());
            if (itemPtr->getLeftPtr() != NULL)
                s->push(itemPtr->getLeftPtr());
        }
    }
}

template<class ItemType>
void BinaryTree<ItemType>::_iterativeInorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr!=NULL)
    {
        Stack<BinaryNode<ItemType>*>* s = new Stack<BinaryNode<ItemType>*>;
        BinaryNode<ItemType>* itemPtr;

        itemPtr = nodePtr;

        while (itemPtr != NULL)
        {
            s->push(itemPtr);
            itemPtr = itemPtr->getLeftPtr();
        }

        while (!s->isEmpty())
        {
            s->pop(itemPtr);
            ItemType item = itemPtr->getItem();
            visit(item);
            if (itemPtr->getRightPtr() != NULL)
            {
                itemPtr = itemPtr->getRightPtr();
                while (itemPtr != NULL)
                {
                    s->push(itemPtr);
                    itemPtr = itemPtr->getLeftPtr();
                }
            }

        }
    }
}

template<class ItemType>
void BinaryTree<ItemType>::_clear (void visit (ItemType &),BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != NULL)
    {
        _clear(visit, nodePtr->getLeftPtr());
        _clear(visit, nodePtr->getRightPtr());
        ItemType item = nodePtr->getItem();
        visit (item);
    }
}
#endif
