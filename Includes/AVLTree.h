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
		void insertRecursive(Node* NodeToSearch, T element);
		int getHeight(Node *nodePtr);
		bool findRecursive(Node* NodeToSearch, T element);
		void deleteNodes(Node* &nodeToRemove);
		std::vector<T> preOrderRec(Node *noteToWalk);
		void singleRotateRight(Node *&nodeToSearch);
		void singleRotateLeft(Node *&nodeToSearch);
		void doubleRotateRight(Node *&nodeToSearch);
		void doubleRotateLeft(Node *&nodeToSearch);
																																
	public:
		AVLTree(); //klar
		void insert(T element); //klar
		void remove(T element); 
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
void AVLTree<T>::insertRecursive(Node* NodeToSearch, T element)
{
	if(NodeToSearch == nullptr)
	{
		NodeToSearch = new Node(element);	
	}
	else if(NodeToSearch->value > element)
	{
		insertRecursive(NodeToSearch->leftChild, element);
		if((NodeToSearch->leftChild->height - NodeToSearch->rightChild->height) == 2)
		{
			if(NodeToSearch->leftChild->value < element)
				doubleRotateRight();
			else
				singleRotateRight();
		}
	}
	else if(NodeToSearch->value < element)
	{
		insertRecursive(NodeToSearch->rightChild, element);
		if((NodeToSearch->rightChild->height - NodeToSearch->leftChild->height) == 2)
		{
			if(NodeToSearch->rightChild->value < element)
				doubleRotateLeft();
			else
				singleRotateLeft();
		}
	}
	//setting height
	if(NodeToSearch->leftChild->height < NodeToSearch->rightChild->height) 
		NodeToSearch->height = NodeToSearch->rightChild->height + 1;
	else
		NodeToSearch->height = NodeToSearch->leftChild->height + 1;
}

//find
template<typename T>
bool AVLTree<T>::findRecursive(Node* NodeToSearch, T element)
{
	if(NodeToSearch == nullptr)
	{
		return false;	
	}
	else if(NodeToSearch->value > element)
	{
		return findRecursive(NodeToSearch->leftChild, element);
	}
	else if(NodeToSearch->value < element)
	{
		return findRecursive(NodeToSearch->rightChild, element);
	}
	else
	{
		return false;
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
void AVLTree<T>::deleteNodes(Node* &nodeToRemove)
{
	if(nodeToRemove != nullptr)
	{
		if(nodeToRemove->leftChild != nullptr)
		{
			deleteNodes(nodeToRemove->leftChild);
		}
		if(nodeToRemove->rightChild != nullptr)
		{
			deleteNodes(nodeToRemove->rightChild);
		}
		delete nodeToRemove;
	}
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
	return findNodeRecursive(this->root, element);
}

template<typename T>
void AVLTree<T>::remove(T element)
{

}

template<typename T>
T AVLTree<T>::getMin()
{
	if(this->root == nullptr)
	{
		throw "Empty tree";
	}
	Node *nodeToSearch = this->root;
	while(nodeToSearch->leftChild != nullptr)
	{
		nodeToSearch = nodeToSearch->leftChild;
	}
	return nodeToSearch->value;
}

template<typename T>
T AVLTree<T>::getMax()
{
	if(this->root == nullptr)
	{
		throw "Empty tree";
	}
	Node *nodeToSearch = this->root;
	while(nodeToSearch->rightChild != nullptr)
	{
		nodeToSearch = nodeToSearch->rightChild;
	}
	return nodeToSearch->value;
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

