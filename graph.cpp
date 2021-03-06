// graph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

enum ConsoleColor
{
	Black = 0,
	Red = 4,
	White = 15
};

void SetColor(ConsoleColor text, ConsoleColor background)
{
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleHandle, background | text);
}

class vertex {
private:
	string name;
	list <string> data;
public:
	vertex();
	vertex(string name);
	~vertex();
	inline void showName();
	inline string getName();
	friend std::ostream& operator<< (std::ostream &out, const vertex &v);
};

vertex::vertex() {};
vertex::vertex(string name) { this->name = name; }
vertex::~vertex() { system("color 04"); }

ostream& operator<< (ostream &out, const vertex &v)
{
	out << v.name;
	return out;
}
inline string vertex::getName() { return name; }

inline void vertex::showName(){	cout << this->name; }

class joint {
private:
	vertex *v1, *v2;
public:
	joint();
	joint(vertex * v1, vertex * v2);

	void show();
	vertex * getFirstVertex();
	vertex * getSecondVertex();
	string getFirstVertexName();
	string getSecondVertexName();
};

joint::joint() {};

joint::joint(vertex * v1, vertex * v2) {
	this->v1 = v1;
	this->v2 = v2;
}
void joint::show() {
	v1->showName();
	v2->showName();
}
vertex* joint::getFirstVertex() { return v1; }
vertex* joint::getSecondVertex() { return v2; }
string joint::getFirstVertexName() { return v1->getName(); }
string joint::getSecondVertexName() { return v2->getName(); }



class Graph {
private:
	vector <vertex*> vertexes;
	vector <joint> joints;
public:
	Graph() {};
	void addVertex() {
		cout << "Enter vertex's name: ";
		string name;
		cin >> name;
		
		for (auto iter = vertexes.begin(); iter != vertexes.end(); iter++)
		{
			if (!(*iter)->getName().compare(name))
			{
				throw 2;
			}
		}

		vertex * v = new vertex(name);
		vertexes.insert(vertexes.end(), v);

	}
	void addJoint()
	{
		string name1, name2;
		cout << "Enter name of first vertex: ";
		cin >> name1;
		cout << "Enter name of first vertex: ";
		cin >> name2;
		bool found1 = false, found2 = false;
		auto iter1 = vertexes.begin();
		auto iter2 = vertexes.begin();

		for (; iter1 != vertexes.end(); iter1++)
		{
			if ((*iter1)->getName() == name1)
			{
				found1 = true;
				break;
			}
		}
		for (; iter2 != vertexes.end(); iter2++)
		{
			if ((*iter2)->getName() == name2)
			{
				found2 = true;
				break;
			}
		}

		if (found1 == true && found2 == true)
		{
			for (auto iter = joints.begin(); iter != joints.end(); iter++)
			{
				string temp_name_1 = (*iter).getFirstVertex()->getName();
				string temp_name_2 = (*iter).getSecondVertex()->getName();
			
				if(!temp_name_1.compare(name1) && !temp_name_2.compare(name2))
				{
					throw 1;
				}
			}
			joint j((*iter1), (*iter2));
			joints.insert(joints.end(), j);
		}
		else
		{
			cout << "Some element was not found" << endl;
		}
	}

	void showJoints() {
		for (auto iter = joints.begin(); iter != joints.end(); iter++)
			cout << '<' << *((*iter).getFirstVertex()) << ';'
				<< *((*iter).getSecondVertex()) << ">, ";

		cout << endl;
	}

	void showVertexes() {
		for (auto iter = vertexes.begin(); iter != vertexes.end(); iter++)
		{
			cout << *(*iter) << ' ';
		}
		cout << endl;
	}
};

int main()
{
	Graph graph;
	char var;
	SetColor(White, Black);
	cout << "To quit programm enter 0\n\\";
	for (int i = 0; i < 5; i++)
	{
		cout << '.';
		Sleep(500);
	}
	cout << '\\' << endl;
	Sleep(500);
	system("cls");

	while (true)
	{
		cout << "1 - Add vertex;" << endl
			<< "2 - Add joint;" << endl
			<< "3 - Show Vertexes" << endl
			<< "4 - Show Joints" << endl;
		cin >> var;	
		system("cls");
		switch (var)
		{
		case'1':
			try {
				graph.addVertex();
			}
			catch (int i) {
				if (i == 2) {
					system("color 04");
					cout << "(!) VertexExistance - vertex with this name already exists.";
					system("color 07");
				}
			}
			cin.ignore(256, '\n');
			break;
		case'2':
			try {
				graph.addJoint();
			}
			catch (int i)
			{
				if (i == 1) {
					SetColor(Red, Black);
					cout << "(!) JointExistance - such joint already exists." << endl;
					SetColor(White, Black);
				}
			}
			cin.ignore(256, '\n');
			break;
		case'3':
			graph.showVertexes();
			break;
		case'4':
			graph.showJoints();
			break;
		case'0':
			return 0;
			break;

		default:
			break;
		}
	}



	return 0;
}


