#ifndef AVLTREE_H
#define AVLTREE_H

#include<vector>


template<typename T>
class AVLTree
{
	private:
		struct Node
		{
			Node(T element)
			{
				value = element;
				height = 0;
				rightChild = nullptr;
				leftChild = nullptr;
			}
			Node* rightChild;
			Node* leftChild;
			T value;
			size_t height;
		};
	private:
		Node *root;
		void insertRecursive(Node* nodePtr, T element);
		void removeRecursive(Node* &nodePtr, T element);
		int getHeight(Node* nodePtr);
		bool findRecursive(Node* nodePtr, T element);
		void deleteNodes(Node* &nodePtr);
		void preOrderRecursive(Node* nodeToWalk, std::vector<T> &preOrderVec);
		void postOrderRecursive(Node* nodeToWalk, std::vector<T> &postOrderVec);
		void inOrderRecursive(Node* nodeToWalk, std::vector<T> &inOrderVec);
		void singleRotateRight(Node* &nodePtr);
		void singleRotateLeft(Node* &nodePtr);
		void doubleRotateRight(Node* &nodePtr);
		void doubleRotateLeft(Node* &nodePtr);
																																
	public:
		AVLTree(); //klar
		void insert(T element); //klar
		void remove(T element); //klar
		bool find(T element); //klar
		std::vector<T> preOrderWalk();
		std::vector<T> inOrderWalk();
		std::vector<T> postOrderWalk();
		size_t getTreeHeight(); //klar
		T getMin(); //klar
		T getMax();	//klar
		~AVLTree(); //klar

		//Functions that was given out for the assignment
		std::string ToGraphviz(); // Member function of the AVLTree class
		void ToGraphvizHelper(std::string& listOfNodes, std::string& listOfConnections, Node* toWorkWith, size_t& uniqueID); // Member function of the AVLTree class
};

/*private functions*/

//insert
template<typename T>
void AVLTree<T>::insertRecursive(Node* nodePtr, T element)
{
	if(nodePtr == nullptr)
	{
		nodePtr = new Node(element);	
	}
	else if(nodePtr->value > element)
	{
		insertRecursive(nodePtr->leftChild, element);
		if((nodePtr->leftChild->height - nodePtr->rightChild->height) == 2)
		{
			if(nodePtr->leftChild->value < element)
				doubleRotateRight(nodePtr);
			else
				singleRotateRight(nodePtr);
		}
	}
	else if(nodePtr->value < element)
	{
		insertRecursive(nodePtr->rightChild, element);
		if((nodePtr->rightChild->height - nodePtr->leftChild->height) == 2)
		{
			if(nodePtr->rightChild->value < element)
				doubleRotateLeft(nodePtr);
			else
				singleRotateLeft(nodePtr);
		}
	}
	//setting height
	if(nodePtr->leftChild->height < nodePtr->rightChild->height) 
		nodePtr->height = nodePtr->rightChild->height + 1;
	else
		nodePtr->height = nodePtr->leftChild->height + 1;
}

//
template<typename T>
void AVLTree<T>::removeRecursive(Node* &nodePtr, T element)
{
	if(nodePtr != nullptr)
	{
		if(nodePtr->value == element)
		{
			Node *nodeToRemove = nodePtr;
			if(nodePtr->leftChild != nullptr)
				nodePtr = nodePtr->leftChild;
			else
				nodePtr = nodePtr->rightChild;
			delete nodeToRemove;
		}
		else if(element < nodePtr->value)
		{
			removeRecursive(nodePtr->leftChild, element);
		}
		else if(element > nodePtr->value)
		{
			removeRecursive(nodePtr->rightChild, element);
		}
		else
		{
			Node *tempNode = nodePtr;
			while(tempNode != nullptr)
			{
				tempNode = tempNode->leftChild;
			}
			nodePtr->value = tempNode->value;
			removeRecursive(nodePtr->rightChild, element);
		}
	}
}

//find
template<typename T>
bool AVLTree<T>::findRecursive(Node* nodePtr, T element)
{
	if(nodePtr == nullptr)
	{
		return false;	
	}
	else if(nodePtr->value > element)
	{
		return findRecursive(nodePtr->leftChild, element);
	}
	else if(nodePtr->value < element)
	{
		return findRecursive(nodePtr->rightChild, element);
	}
	else
	{
		return false;
	}	
}

//preorder
template<typename T>
void AVLTree<T>::preOrderRecursive(Node* nodeToWalk, std::vector<T> &preOrderVec)
{
	if(nodeToWalk != nullptr)
	{
		preOrderVec.push_back(nodeToWalk->value);
		preOrderRecursive(nodeToWalk->leftChild);
		preOrderRecursive(nodeToWalk->rightChild);
	}
}

template<typename T>
void AVLTree<T>::postOrderRecursive(Node* nodeToWalk, std::vector<T> &postOrderVec)
{
	if(nodeToWalk != nullptr)
	{
		postOrderRecursive(nodeToWalk->leftChild);
		postOrderRecursive(nodeToWalk->rightChild);
		postOrderVec.push_back(nodeToWalk->value);
	}
}

template<typename T>
void AVLTree<T>::inOrderRecursive(Node* nodeToWalk, std::vector<T> &postOrderVec)
{
	if(nodeToWalk != nullptr)
	{
		inOrderRecursive(nodeToWalk->leftChild, postOrderVec);
		postOrderVec.push_back(nodeToWalk->value);
		inOrderRecursive(nodeToWalk->rightChild, postOrderVec);
	}
}

//help functions
template<typename T>
int AVLTree<T>::getHeight(Node *nodePtr)
{
	if(nodePtr == nullptr)
		return -1;
	else 
		return static_cast<int>(nodePtr->height);
}

template<typename T>
void AVLTree<T>::deleteNodes(Node* &nodePtr)
{
	if(nodePtr != nullptr)
	{
		if(nodePtr->leftChild != nullptr)
		{
			deleteNodes(nodePtr->leftChild);
		}
		if(nodePtr->rightChild != nullptr)
		{
			deleteNodes(nodePtr->rightChild);
		}
		delete nodePtr;
	}
}

//balancing
template<typename T>
void AVLTree<T>::singleRotateLeft(Node* &nodePtr)
{
	Node *tempNode = nodePtr->rightChild;
	nodePtr->rightChild = tempNode->leftChild;
	tempNode->leftChild = nodePtr;
	if(nodePtr->leftChild->height > nodePtr->rightChild->height)
	{
		nodePtr->height = nodePtr->leftChild->height + 1;
	}
	else
	{
		nodePtr->height = nodePtr->rightChild->height + 1;
	}

	if(tempNode->leftChild->height > tempNode->rightChild->height)
	{
		tempNode->height = tempNode->leftChild->height + 1;
	}
	else
	{
		tempNode->height = tempNode->rightChild->height + 1;
	}
	nodePtr = tempNode;	 
}

template<typename T>
void AVLTree<T>::singleRotateRight(Node* &nodePtr)
{
	Node *tempNode = nodePtr->leftChild;
	nodePtr->leftChild = tempNode->rightChild;
	tempNode->rightChild = nodePtr;
	//updating height
	if(nodePtr->leftChild->height > nodePtr->rightChild->height)
	{
		nodePtr->height = nodePtr->leftChild->height + 1;
	}
	else
	{
		nodePtr->height = nodePtr->rightChild->height + 1;
	}

	if(tempNode->leftChild->height > tempNode->rightChild->height)
	{
		tempNode->height = tempNode->leftChild->height + 1;
	}
	else
	{
		tempNode->height = tempNode->rightChild->height + 1;
	}
	nodePtr = tempNode;
}

template<typename T>
void AVLTree<T>::doubleRotateLeft(Node* &nodePtr)
{
	singleRotateRight(nodePtr->rightChild);
	singleRotateLeft(nodePtr);
}

template<typename T>
void AVLTree<T>::doubleRotateRight(Node* &nodePtr)
{
	singleRotateLeft(nodePtr->leftChild);
	singleRotateRight(nodePtr);
}


/*public functions*/

template<typename T>
AVLTree<T>::AVLTree()
	: root(nullptr)
{
}

template<typename T>
void AVLTree<T>::insert(T element)
{
	insertRecursive(this->root, element);
}

template<typename T>
bool AVLTree<T>::find(T element)
{
	return findRecursive(this->root, element);
}

template<typename T>
void AVLTree<T>::remove(T element)
{
	removeRecursive(root, element);
}

template<typename T>
std::vector<T> AVLTree<T>::preOrderWalk()
{
	std::vector<T> preOrderVec;
	preOrderRecursive(root, preOrderVec);
	return preOrderVec;
}

template<typename T>
std::vector<T> AVLTree<T>::postOrderWalk()
{
	std::vector<T> postOrderVec;
	postOrderRecursive(root,postOrderVec);
	return postOrderVec;
}

template<typename T>
std::vector<T> AVLTree<T>::inOrderWalk()
{
	std::vector<T> inOrderVec;
	inOrderRecursive(root, inOrderVec);
	return inOrderVec;

}

template<typename T>
T AVLTree<T>::getMin()
{
	if(this->root == nullptr)
	{
		throw "Empty tree";
	}
	Node *nodePtr = this->root;
	while(nodePtr->leftChild != nullptr)
	{
		nodePtr = nodePtr->leftChild;
	}
	return nodePtr->value;
}

template<typename T>
T AVLTree<T>::getMax()
{
	if(this->root == nullptr)
	{
		throw "Empty tree";
	}
	Node *nodePtr = this->root;
	while(nodePtr->rightChild != nullptr)
	{
		nodePtr = nodePtr->rightChild;
	}
	return nodePtr->value;
}

template<typename T>
size_t AVLTree<T>::getTreeHeight()
{
	if(root == nullptr)
	{
		return static_cast<size_t>(-1);
	}
	return root->height;
}

template<typename T>
AVLTree<T>::~AVLTree()
{
	deleteNodes(this->root);
}

/*Functions from assignment*/

template<typename T>
std::string AVLTree<T>::ToGraphviz() // Member function of the AVLTree class
{
	std::string toReturn = "";
	if(root) // root is a pointer to the root node of the tree
	{
		std::string listOfNodes;
		std::string listOfConnections = std::string("\t\"Root\" -> ") + std::to_string(0) + std::string(";\n");
		toReturn += std::string("digraph {\n");
		size_t id = 0;
		ToGraphvizHelper(listOfNodes, listOfConnections, root, id);
		toReturn += listOfNodes;
		toReturn += listOfConnections;
		toReturn += std::string("}");
	}
	return std::move(toReturn);
}

template<typename T>
void AVLTree<T>::ToGraphvizHelper(std::string& listOfNodes, std::string& listOfConnections, Node* toWorkWith, size_t& uniqueID) // Member function of the AVLTree class
{
	size_t myID = uniqueID;
	listOfNodes += std::string("\t") + std::to_string(myID) + std::string(" [label=\"") + std::to_string(toWorkWith->element) + std::string("\"];\n");
	if(toWorkWith->leftChild)
	{
		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID + 1) + std::string(" [color=blue];\n");
		ToGraphvizHelper(listOfNodes, listOfConnections, toWorkWith->leftChild, ++uniqueID);
	}
	else
	{
		listOfNodes += std::string("\t") + std::to_string(++uniqueID) + std::string(" [label=") + std::string("nill, style = invis];\n");
		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID) + std::string(" [ style = invis];\n");
	}
			
	if(toWorkWith->rightChild)
	{
		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID + 1) + std::string(" [color=red];\n");
		ToGraphvizHelper(listOfNodes, listOfConnections, toWorkWith->rightChild, ++uniqueID);
	}
	else
	{
		listOfNodes += std::string("\t") + std::to_string(++uniqueID) + std::string(" [label=") + std::string("nill, style = invis];\n");
		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID) + std::string(" [ style = invis];\n");
	}
}

#endif