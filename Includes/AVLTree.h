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
		Node &nodeFinder(Node *nodeToSearch, T element)
		{
			if(nodeToSearch == nullptr || nodeToSearch->value == element)
			{
				return nodeToSearch;
			}
			else
				{
				if (nodeToSearch->value > element)
				{
					nodeFinder(nodeToSearch->leftChild, element);
				}
				else
				{
					nodeFinder(nodeToSearch->rightChild, element);
				}
			}
		}																																				
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
		~AVLTree();

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
			return std::move(toReturn);
		}		

		void ToGraphvizHelper(std::string& listOfNodes, std::string& listOfConnections, Node* toWorkWith, size_t& uniqueID) // Member function of the AVLTree class
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
};
/*template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::nodeFinder(Node* nodeToSearch, T element)
{
	if(nodeToSearch == nullptr || nodeToSearch->value == element)
	{
		return nodeToSearch;
	}
	if (nodeToSearch->value > element)
	{
		nodeFinder(nodeToSearch->leftChild, element)
	}
	else
	{
		nodeFinder(nodeToSearch->rightChild, element)
	}
}*/


template<typename T>
AVLTree<T>::AVLTree()
	: root(nullptr)
{
}

template<typename T>
void AVLTree<T>::insert(T element)
{	
	Node *tempNode = new Node(element);
	nodeFinder(this->root, element) = tempNode;
}

template<typename T>
bool AVLTree<T>::find(T element)
{
	return nodeFinder(this->root, element) != nullptr;
}

template<typename T>
void AVLTree<T>::remove(T element)
{
	Node *nodeToRemove = nodeFinder(this->root, element);
	if(nodeToRemove != nullptr)
	{
		//nånting
	}
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

}