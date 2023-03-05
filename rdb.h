#include<algorithm>
#include<vector>
#include<list>
#include<string>
#include<set>
using namespace std;
class Attr { //Base class for attributes
	public: 
	// int intdata;
	// float floatdata;
	// string *(string*)data;
	void* data;
	//Virtual operators to be overloaded in the function
	virtual bool operator== (const Attr & R) = 0;
	virtual bool operator!= (const Attr & R) = 0;
	virtual bool operator< (const Attr & R) = 0;
	virtual bool operator<= (const Attr & R) = 0;
	virtual bool operator> (const Attr & R) = 0;
	virtual bool operator>= (const Attr & R) = 0;
};
Attr* makeinstance(string, int=0, float=0, string="");//Function to create an instance of particular Attribute. Definition to be provided by the user in rdb-attr file
struct DNFformula{ //Structure to store DNFformual for selection operation
	list<list<tuple<string, char, Attr *>>>ops; 
};
class Relation;
class Record { //storing data for each record
	vector<Attr*> attrptr;//Vector of attributes
	public:
	Record(vector<Attr*> x)//Constructor
	{
		attrptr = x;
	}//Default cctor is being used
	bool operator == (const Record& R)//Overloaded operator to check for equality of 2 records
	{
		if(attrptr.size()!=R.attrptr.size())
		{
			return false;
		}
		for(int i=0; i<attrptr.size(); i++)//2 records are equal when all their attributes are equal. This is being checked here
		{
			if(*attrptr[i] != *(R.attrptr[i]))
			{
				return false;
			}
		}
		return true;
	}
	//Friend declarations
	friend class Relation;//Relation needs access to the internals as it is built on top of records
	//Friend function declarations
	friend Relation* projection(Relation*, list<string>);
	friend Relation* CartesianProduct(Relation*, Relation*);
	friend Relation* Union (Relation * R1, DNFformula * f);
	friend Relation* naturaljoin(Relation*, Relation*, list<string>);
};

class Relation { // storing a relation
	int natttr, nrecs; // number of attributes and records
	vector <string> attrnames; // schema
	vector <int> attrinds; // mapping schema to indices
	list <Record*> recs; // list of records
	int index;//Implementation variable used to store number of attributes added so far
	vector <string> orig;
public: 
	Relation(const Relation& R)//cctor
	{
		natttr = R.natttr;//Shallow copy of default data types
		nrecs = R.nrecs;
		attrnames = R.attrnames;
		attrinds = R.attrinds;
		orig = R.orig;
		for(auto it:R.recs)//Deep copy of udt
		{
			recs.push_back(new Record(*it));
		}
	}
	Relation():natttr(0),nrecs(0),index(0){}//ctor
	//Function declarations
	void addattr(string);//Function to add attribute to the relation
	void addrec();//Function to add record to relation
	void display();//Function to display the relation
	//Friend function declarations
	friend Relation* Union (Relation * R1, DNFformula * f);
	friend Relation* Union(Relation*, Relation*);
	friend Relation* difference(Relation*, Relation*);
	friend Relation* projection(Relation* ,list<string>);
	friend Relation* difference(Relation*, string, string);
	friend Relation* CartesianProduct(Relation*, Relation*);
	friend Relation* naturaljoin(Relation*, Relation*, list<string>);
	friend list<string> commonattributes(Relation*, Relation*);
	friend list<tuple<string,char,Attr*>> func(Relation*);
};
