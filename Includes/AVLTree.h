#ifndef AVLTREE_H
#define AVLTREE_H

#include <vector>
#include <string>

template<typename T>
class AVLTree
{
	private:
		struct Node
		{
			Node* rightChild;
			Node* leftChild;
			T value;
			size_t height;
			Node(T element)
			{
				value = element;
				height = 0;
				rightChild = nullptr;
				leftChild = nullptr;
			}
		};
	private:
		Node *root;
		void insertRecursive(Node* &nodePtr, const T &element);
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
		void balancing(Node* &nodePtr);
		T& findMin(Node*) const;
		
		void ToGraphvizHelper(std::string& listOfNodes, std::string& listOfConnections, Node* toWorkWith, size_t& uniqueID) // Member function of the AVLTree class
		{
			size_t myID = uniqueID;
			listOfNodes += std::string("\t") + std::to_string(myID) + std::string(" [label=\"") + std::to_string(toWorkWith->value) + std::string("\"];\n");
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
																																
	public:
		AVLTree(); //klar
		void insert(const T &element); //klar
		void remove(T element); //klar
		bool find(T element); //klar
		std::vector<T> preOrderWalk();
		std::vector<T> inOrderWalk();
		std::vector<T> postOrderWalk();
		size_t getTreeHeight(); //klar
		T &getMin() const; //klar
		T &getMax() const;	//klar
		~AVLTree(); //klar

		//Functions that was given out for the assignment
		std::string ToGraphviz() // Member function of the AVLTree class
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
			return toReturn;
		}
};

/*private functions*/

//insert
template<typename T>
void AVLTree<T>::insertRecursive(Node* &nodePtr, const T &element)
{
	if(nodePtr == nullptr)
	{
		nodePtr = new Node(element);	
	}
	else if(element < nodePtr->value)
	{
		insertRecursive(nodePtr->leftChild, element);
		
	}
	else if(element > nodePtr->value)
	{
		insertRecursive(nodePtr->rightChild, element);
		
	}

	balancing(nodePtr);


	/*if((getHeight(nodePtr->leftChild) - getHeight(nodePtr->rightChild)) >= 2)
		{
			if(nodePtr->leftChild->value > element)
				singleRotateRight(nodePtr);
			else
				doubleRotateRight(nodePtr);
		}
	
	if((getHeight(nodePtr->rightChild) - getHeight(nodePtr->leftChild)) >= 2)
		{
			if(nodePtr->rightChild->value < element)
				singleRotateLeft(nodePtr);
			else
				doubleRotateLeft(nodePtr);
		}*/
	//setting height
	
	
}

template<typename T>
void AVLTree<T>::balancing(Node* &nodePtr)
{
	if(nodePtr == nullptr)
		return;
	
	if((getHeight(nodePtr->leftChild) - getHeight(nodePtr->rightChild)) > 1)
	{
		if(getHeight(nodePtr->leftChild->leftChild) >= getHeight(nodePtr->leftChild->rightChild))
			singleRotateRight(nodePtr);
		else
			doubleRotateRight(nodePtr);
	}

	else if((getHeight(nodePtr->rightChild) - getHeight(nodePtr->leftChild)) > 1)
	{
		if(getHeight(nodePtr->rightChild->rightChild) >= getHeight(nodePtr->rightChild->leftChild))
			singleRotateLeft(nodePtr);
		else
			doubleRotateLeft(nodePtr);
	}

	nodePtr->height = std::max(getHeight(nodePtr->leftChild), getHeight(nodePtr->rightChild)) + 1;
	
}

template<typename T>
void AVLTree<T>::removeRecursive(Node* &nodePtr, T element)
{
	if(nodePtr == nullptr)
		return;
	
	if(element < nodePtr->value)
		removeRecursive(nodePtr->leftChild, element);
	else if(element > nodePtr->value)
		removeRecursive(nodePtr->rightChild, element);
	else if(nodePtr->leftChild != nullptr && nodePtr->rightChild != nullptr)
	{
		nodePtr->value = findMin(nodePtr->rightChild);
		removeRecursive(nodePtr->rightChild, nodePtr->value);
	}
	else
	{
		Node *nodeToRemove = nodePtr;
		if(nodePtr->leftChild != nullptr)
			nodePtr = nodePtr->leftChild;
		else
			nodePtr = nodePtr->rightChild;
		delete nodeToRemove;
	}
	balancing(nodePtr);
}

//find
template<typename T>
bool AVLTree<T>::findRecursive(Node* nodePtr, T element)
{
	
	if(nodePtr == nullptr)
	{
		return false;
	}
	if(nodePtr->value == element)
	{
		return true;	
	}
	else if(nodePtr->value > element)
	{
		return findRecursive(nodePtr->leftChild, element);
	}
	else if(nodePtr->value < element)
	{
		return findRecursive(nodePtr->rightChild, element);
	}
	return false;
}

//preorder
template<typename T>
void AVLTree<T>::preOrderRecursive(Node* nodeToWalk, std::vector<T> &preOrderVec)
{
	if(nodeToWalk != nullptr)
	{
		preOrderVec.push_back(nodeToWalk->value);
		preOrderRecursive(nodeToWalk->leftChild, preOrderVec);
		preOrderRecursive(nodeToWalk->rightChild, preOrderVec);
	}	
}

template<typename T>
void AVLTree<T>::postOrderRecursive(Node* nodeToWalk, std::vector<T> &postOrderVec)
{
	if(nodeToWalk != nullptr)
	{
		postOrderRecursive(nodeToWalk->leftChild, postOrderVec);
		postOrderRecursive(nodeToWalk->rightChild, postOrderVec);
		postOrderVec.push_back(nodeToWalk->value);
	}
}

template<typename T>
void AVLTree<T>::inOrderRecursive(Node* nodeToWalk, std::vector<T> &inOrderVec)
{
	if(nodeToWalk != nullptr)
	{
		inOrderRecursive(nodeToWalk->leftChild, inOrderVec);
		inOrderVec.push_back(nodeToWalk->value);
		inOrderRecursive(nodeToWalk->rightChild, inOrderVec);
	}
}

//help functions
template<typename T>
int AVLTree<T>::getHeight(Node *nodePtr)
{
	if(nodePtr == nullptr)
		return -1;
	else 
		return nodePtr->height;
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

template<typename T>
T& AVLTree<T>::findMin(Node* nodePtr) const 
{
	if(nodePtr == nullptr)
		throw "empty tree";
	else if(nodePtr->leftChild == nullptr)
		return nodePtr->value;
	else
		return findMin(nodePtr->leftChild);
	
}

//balancing
template<typename T>
void AVLTree<T>::singleRotateLeft(Node* &nodePtr)
{
	Node *tempNode = nodePtr->rightChild;
	nodePtr->rightChild = tempNode->leftChild;
	tempNode->leftChild = nodePtr;
	nodePtr->height = std::max(getHeight(nodePtr->leftChild), getHeight(nodePtr->rightChild)) + 1;
	tempNode->height = std::max(getHeight(nodePtr->rightChild), getHeight(nodePtr)) + 1;
	/*if(getHeight(nodePtr->leftChild) > getHeight(nodePtr->rightChild))
	{
		nodePtr->height = getHeight(nodePtr->leftChild) + 1;
	}
	else
	{
		nodePtr->height = getHeight(nodePtr->rightChild) + 1;
	}

	if(getHeight(nodePtr->rightChild) > getHeight(nodePtr))
	{
		tempNode->height = getHeight(nodePtr->rightChild) + 1;
	}
	else
	{
		tempNode->height = getHeight(nodePtr) + 1;
	}*/
	nodePtr = tempNode;	 
}

template<typename T>
void AVLTree<T>::singleRotateRight(Node* &nodePtr)
{
	Node *tempNode = nodePtr->leftChild;
	nodePtr->leftChild = tempNode->rightChild;
	tempNode->rightChild = nodePtr;
	//updating height
	nodePtr->height = std::max(getHeight(nodePtr->leftChild), getHeight(nodePtr->rightChild)) + 1;
	tempNode->height = std::max(getHeight(tempNode->leftChild), getHeight(nodePtr)) + 1;
	/*if(getHeight(nodePtr->leftChild) > getHeight(nodePtr->rightChild))
	{
		nodePtr->height = getHeight(nodePtr->leftChild) + 1;
	}
	else
	{
		nodePtr->height = getHeight(nodePtr->rightChild) + 1;
	}

	if(getHeight(tempNode->leftChild) > getHeight(nodePtr))
	{
		tempNode->height = getHeight(tempNode->leftChild) + 1;
	}
	else
	{
		tempNode->height = getHeight(nodePtr) + 1;
	}*/
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
void AVLTree<T>::insert(const T &element)
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
T &AVLTree<T>::getMin() const
{
	return findMin(root);
}

template<typename T>
T &AVLTree<T>::getMax() const
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

#endif