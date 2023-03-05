#include<iostream>
#include<algorithm>
#include<vector>
#include<list>
#include<tuple>
#include<set>
#include "rdb.h"
using namespace std;
class integerAttribute: public Attr
{
	public:
	//Constructor
	integerAttribute(int x_){
		data = new int(x_);
	}
	//Overriden operators
	bool operator== (const Attr& R)
	{
		if(*(int*)data == *(int*)R.data)
			return true;
		return false;
	}
	bool operator!= (const Attr& R)
	{
		if(*(int*)data != *(int*)R.data)
			return true;
		return false;
	}
	bool operator< (const Attr& R)
	{
		if(*(int*)data < *(int*)R.data)
			return true;
		return false;
	}
	bool operator<= (const Attr& R)
	{
		if(*(int*)data <= *(int*)R.data)
			return true;
		return false;
	}
	bool operator> (const Attr& R)
	{
		if(*(int*)data > *(int*)R.data)
			return true;
		return false;
	}
	bool operator>= (const Attr& R)
	{
		if(*(int*)data >= *(int*)R.data)
			return true;
		return false;
	}
};
class floatAttribute: public Attr
{
	public:
	//Constructor
	floatAttribute(float x_){
		data = new float(x_);
	}
	//Overriden operators
	bool operator== (const Attr& R)
	{
		if(*(float*)data == *(float*)R.data)
			return true;
		return false;
	}
	bool operator!= (const Attr& R)
	{
		if(*(float*)data != *(float*)R.data)
			return true;
		return false;
	}
	bool operator< (const Attr& R)
	{
		if(*(float*)data < *(float*)R.data)
			return true;
		return false;
	}
	bool operator<= (const Attr& R)
	{
		if(*(float*)data <= *(float*)R.data)
			return true;
		return false;
	}
	bool operator> (const Attr& R)
	{
		if(*(float*)data > *(float*)R.data)
			return true;
		return false;
	}
	bool operator>= (const Attr& R)
	{
		if(*(float*)data >= *(float*)R.data)
			return true;
		return false;
	}
};
class stringAttribute: public Attr
{
	public:
	//Constructor
	stringAttribute(string s)
	{
		data = new string(s);
	}
	//Overriden operators
	bool operator == (const Attr& R)
	{
		return *(string*)data == *(string*)R.data;
	}
	bool operator < (const Attr& R)
	{
		return *(string*)data < *(string*)R.data;
	}
	bool operator <= (const Attr& R)
	{
		return *(string*)data <= *(string*)R.data;
	}
	bool operator > (const Attr& R)
	{
		return *(string*)data > *(string*)R.data;
	}
	bool operator >= (const Attr& R)
	{
		return *(string*)data >= *(string*)R.data;
	}
	bool operator != (const Attr& R)
	{
		return *(string*)data != *(string*)R.data;
	}
};

Attr* makeinstance(string s, int a, float b, string s1)//Function to create a new instance of user defined classes
{
	//s stores the attribute name, a, b, s1 store the attribute values(overloaded in header file)
	//Checking of s and returning appropriate instance
	if(s == "integerAttribute")
	{
		return new integerAttribute(a); 
	}
	if(s == "floatAttribute")
	{
		return new floatAttribute(b);
	}
	if(s== "stringAttribute")
	{
		return new stringAttribute(s1);
	}
}

void Relation::addattr(string attrname)//Function to add a new attribute to the relation
{
	attrnames.push_back(attrname);//Pushing attribute name and attribute index into their respective vectors
	attrinds.push_back(++index);
	sort(attrnames.begin(),attrnames.end());
	natttr++;//Increasing the count of attributes
	orig = attrnames;
}
void Relation::addrec()//Function to add a record
{
	vector<Attr*> temp;//Temporary vector of attribute pointers to construct the record from
	int i=0;
	for(auto it:orig)//Looping over the attributenames list and taking input for each attribute
	{
		if(it == "integerAttribute")
		{
			cout<<"Enter the value of "<<attrnames[i]<<" of the record: ";
			int k;
			cin>>k;
			temp.push_back(new integerAttribute(k));//Pushing new attribute into the temporary vector
		}
		if(it == "floatAttribute")
		{
			cout<<"Enter the value of "<<attrnames[i]<<" of the record: ";
			float k;
			cin>>k;
			temp.push_back(new floatAttribute(k));
		}
		if(it == "stringAttribute")
		{
			cout<<"Enter the value of "<<attrnames[i]<<" of the record: ";
			string s;
			cin>>s;
			temp.push_back(new stringAttribute(s));
		}
		i++;
	}
	recs.push_back(new Record(temp));//Constructing a new record from temporary vector and adding it into the recs vector of the object
	nrecs++;//Increasing the count of records stored
}
void Relation::display()//Function to display the relation
{
	int k=0;
	//cout<<orig.size()<<endl;
	for(auto it:recs)//iterating over the records and listing them
	{
		int i=0;
		cout<<"Rec_id: "<<++k;//printing the record number
		for(int j=0;j<natttr;j++)//Printing each attribute of the record
		{
			cout<<", "<<attrnames[j]<<": ";
			if(orig[j] == "integerAttribute")
			{
				cout<<*((int*)(*it).attrptr[i]->data);
			}
			if(orig[j] == "floatAttribute")
			{
				cout<<*((float*)(*it).attrptr[i]->data);
			}
			if(orig[j] == "stringAttribute")
			{
				cout<<*((string*)(*it).attrptr[i]->data);
			}
			i++;
		}
		cout<<endl;
	}
}
Relation* naturaljoin(Relation* R1, Relation* R2, list<string>attributes)//Function to implement natural join
{
	Relation* rel1 = new Relation(*R1);//Making copy of relations to prevent original relations from getting altered
	Relation* rel2 = new Relation(*R2);
	int i=0;
	// for(auto it:rel2->attrnames)//Renaming the common attributes in relation 3
	// {
	// 	if(find(attributes.begin(),attributes.end(),it) != attributes.end())
	// 	{
	// 		//cout<<rel2->attrnames[i];
	// 		rel2->attrnames[i] = "temp";
	// 	}
	// 	i++;
	// }
	Relation* crossprod = CartesianProduct(rel1,rel2);//Taking Cartesian product of the 2 relations
	crossprod->display();
	DNFformula f;
	for(auto it:rel1->recs)//Creating the DNFformula for selecting the records
	{
		list<tuple<string,char,Attr*>>temp;
		int i=0;
		for(auto it2: it->attrptr)
		{
			if(find(attributes.begin(),attributes.end(),rel1->attrnames[i])!=attributes.end())//Pushing the common attributes into the tuples
			{
				temp.push_back(make_tuple(rel1->attrnames[i],'=',it2));
			}
			i++;
		}
		f.ops.push_back(temp);
	}
	Relation* retval = Union(crossprod, &f);//Selecting the viable records
	retval->display();
	i = R1->attrnames.size();
	for(auto it:rel2->attrnames)//Renaming the common attributes in relation 3
	{
		if(find(attributes.begin(),attributes.end(),it) != attributes.end())
		{
			//cout<<rel2->attrnames[i];
			retval->attrnames[i] = "temp";
		}
		i++;
	}
	retval->display();
	i=0;
	list<string> projectionattr;//Creating projectionattributes list to take projection
	// for(auto it:rel1->attrnames)
	// {
	// 	projectionattr.push_back(it);
	// }
	// for(auto it:rel2->attrnames)
	// {
	// 	if(find(attributes.begin(),attributes.end(),it) == attributes.end() && it != "temp")
	// 	{
	// 		projectionattr.push_back(it);
	// 	}
	// }
	Relation* retrelation = new Relation();
	retrelation->natttr = retval->natttr;
	retrelation->nrecs = retval->nrecs;
	for(int i=0;i<retval->attrnames.size();i++)
	{
		if(retval->attrnames[i] != "temp")
		{
			retrelation->attrnames.push_back(retval->attrnames[i]);
			retrelation->orig.push_back(retval->orig[i]);
		}
	}
	cout<<retrelation->attrnames.size()<<endl<<retrelation->orig.size();
	retrelation->natttr = retrelation->attrnames.size();
	for(auto it:retval->recs)
	{
		vector<Attr*>temprecord;
		for(int i=0;i<retval->attrnames.size();i++)
		{
			if(retval->attrnames[i] != "temp")
			{
				temprecord.push_back(it->attrptr[i]);
			}
		}
		retrelation->recs.push_back(new Record(temprecord));
	}
	return retrelation;
}