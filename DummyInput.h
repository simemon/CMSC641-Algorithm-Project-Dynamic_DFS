/* Dummy input file
List L = List of all vertices
Map of all edges 
*/
#include<iostream>

class Lists
{
	public:
		std::vector<char> L(8);
		std::vector<pair <char,char> > E(L.size+1);

	void insertIntoL()
	{	
	L.push_back('x');
	L.push_back('z');
	L.push_back('w');
	L.push_back('s');
	L.push_back('t');
	L.push_back('y');
	L.push_back('u');
	L.push_back('v');
}

void insertIntoE()
{
	E.push_back(std::make_pair('z','x'));
	E.push_back(std::make_pair('u','x'));
	E.push_back(std::make_pair('s','x'));
	E.push_back(std::make_pair('y','z'));
	E.push_back(std::make_pair('t','z'));
	E.push_back(std::make_pair('v','u'));
	E.push_back(std::make_pair('x','u'));
	E.push_back(std::make_pair('u','v'));
	E.push_back(std::make_pair('z','y'));
	E.push_back(std::make_pair('z','w'));
	E.push_back(std::make_pair('w','z'));
	E.push_back(std::make_pair('x','z'));
	E.push_back(std::make_pair('s','w'));
	E.push_back(std::make_pair('t','w'));
	E.push_back(std::make_pair('w','s'));
	E.push_back(std::make_pair('x','s'));
	E.push_back(std::make_pair('z','t'));
	E.push_back(std::make_pair('w','t'));

}
	
	//std::map<char, List<pair <char,char> >> adjacencyList;	

	//adjacencyList.insert('x',make_pair('x','z'));
};
