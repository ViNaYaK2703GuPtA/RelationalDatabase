#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<tuple>
#include<list>
#include<set>
#include "rdb.h"
using namespace std;
Relation* Union(Relation*R1,Relation*R2)//Function to perform union of 2 relations
{
	list<Record> temp;
	if(R1->natttr != R2->natttr)//Checking if the 2 relations are union compatible
	{
		cout<<"Given Relations are not union compatible"<<endl;
		return NULL;
	}
	for(int i=0;i<R1->natttr;i++)//Checking if the 2 relations are union campatible
	{
		if(R1->attrnames[i] != R2->attrnames[i])
		{
			cout<<"Given Relations are not union compatible"<<endl;
			return NULL;
		}
	}
	for(auto it:R1->recs)//Implementing the union of the relations
	{
		bool flag=true;
		for(auto it2:temp)//Checking if the record has already been added to the union relation
		{
			if(*it == it2)
			{
				flag = false;
				break;
			}
		}
		if(flag)//Adding the record to the return relation if it has not been added to the return relation
		{
			temp.push_back(*it);
		}
	}
	for(auto it:R2->recs)//Checking for the records of the second relation
	{
		bool flag=true;
		for(auto it2:temp)//Checking if the record has already been added to the return relation
		{
			if(*it == it2)
			{
				flag = false;
				break;
			}
		}
		if(flag)//Adding the record to the return relation if it has not been added to the return relation
		{
			temp.push_back(*it);
		}
	}
	//Building the return relation
	Relation* retrelation = new Relation();
	retrelation->natttr = R1->natttr;//Copying the attributes of the parent relation
	retrelation->nrecs = temp.size();
	retrelation->attrinds = R1->attrinds;
	retrelation->attrnames = R1->attrnames;
	retrelation->orig = R1->orig;
	for(auto it:temp)
	{
		retrelation->recs.push_back(new Record(it));
	}
	return retrelation;
}

Relation* difference (Relation * R1, Relation * R2)//Function to calculate the difference of the 2 relations
{
	if(R1->natttr != R2->natttr)//If the 2 Relations are not union compatible, then the difference is the first relation itself
	{
		return new Relation(*R1);
	}
	for(int i=0;i<R1->natttr;i++)//Checking if the relations are not union compatible
	{
		if(R1->attrnames[i] != R2->attrnames[i])
		{
			return new Relation(*R1);
		}
	}
	Relation* temp = new Relation();//Building the return relation
	temp->attrinds = R1->attrinds;//Copying the attributes of parent relation into return relations
	temp->attrnames = R1->attrnames;
	temp->natttr = R1->natttr;
	temp->orig = R1->orig;
	temp->nrecs=0;
	for(auto it:R1->recs)//Checking for each record of the relation R1 if it is present in R2
	{
		bool flag = true;
		for(auto it2:R2->recs)
		{
			if(*it == *it2)
			{
				flag = false;
				break;
			}
		}
		if(flag)//If the record is not present in r2, it is added to the return relation
		{
			temp->nrecs++;
			temp->recs.push_back(new Record(*it));
		}
	}
	return temp;
}

Relation* CartesianProduct(Relation* R1,Relation* R2)//Function to calculate Cartesian product of the 2 Relations
{
	Relation* temp = new Relation();
	for(auto it:R1->orig)//Pushing the attributes of R1 into the resultant relation
	{
		temp->orig.push_back(it);
		temp->attrinds.push_back(temp->natttr);
		temp->natttr++;
	}
	for(auto it: R2->orig)//Pushing the attributes of R2 into resultant relation
	{
		temp->orig.push_back(it);
		temp->attrinds.push_back(temp->natttr);
		temp->natttr++;
	}
	for(auto it: R1->attrnames)
	{
		temp->attrnames.push_back(it);
	}
	for(auto it: R2->attrnames)
	{
		temp->attrnames.push_back(it);
	}
	for(auto it1: R1->recs)//Looping over the recs of R1 and R2 one inside the other to calculate the cartesian product
	{
		vector<Attr*> tempo(temp->natttr);
		for(int i=0;i<it1->attrptr.size();i++)//First adding the Attribute values of R1 into the resultant record 
		{
			tempo[i] = it1->attrptr[i];
		}
		int j=it1->attrptr.size();
		for(auto it2: R2->recs)//Adding the attributes of R2 into the resultant record
		{
			for(int i=j;i<j+it2->attrptr.size();i++)
			{
				tempo[i] = it2->attrptr[i-j];
			}
			temp->recs.push_back(new Record(tempo));//Pushing the resulatant record into the relation
			temp->nrecs++;
		}
	}
	return temp;//Returning the resultant Cartesian Product 
}

Relation* projection(Relation* R1, list<string> projectattrs)//Function to calculate projection of a relation
{
	Relation* temp = new Relation();//Return relation
	for(int i=0;i<R1->attrnames.size();i++)
	{
		if(find(projectattrs.begin(),projectattrs.end(),R1->attrnames[i])!=projectattrs.end())
		{
			temp->attrnames.push_back(R1->attrnames[i]);
			temp->orig.push_back(R1->orig[i]);
		}
	}
	temp->natttr = temp->attrnames.size();
	for(auto it: R1->recs)//Looping over the records of input relation and choosing attributes which are to be present in the return relation
	{
		vector<Attr*>tempo;//Temporary attribute vector to store the resultant record after taking projection
		int i=0;
		for(auto it2: it->attrptr)//Checking for the presence of the attribute in the projectattrs list
		{
			string s = R1->attrnames[i];
			bool flag = 0;
			for(auto it3: projectattrs)
			{
				if(it3 == s)
				{
					flag = true;
					//cout<<it3<<endl;
					break;
				}
			}
			if(flag)//Pushing the atrribute into the record if it exists in the list
			{
				tempo.push_back(it2);
			}
			i++;
		}
		temp->recs.push_back(new Record(tempo));//Pushing the record into the resultant relation
		temp->nrecs++;
	}
	return temp;
}

Relation* difference(Relation* R1,string s1, string s2)//Function to renae an attribute in the relation
{
	for(int i=0;i<R1->natttr;i++)//Looping over all the attributes and searching for the given names
	{
		if(R1->attrnames[i] == s1)
		{
			R1->attrnames[i] = s2;//Renaming the attribute
		}
	}
	return R1;
}

Relation* Union(Relation*R1, DNFformula* f)//Funtion to calculate selection of a relation
{
	vector<Relation> temp;//Temporary list of vectors to store the relations of disjunction
	for(auto it: f->ops)//Looping over the DNFformula and applying the conjunction conditions
	{
		Relation tempo;//Temporary relation to store the records satisfying all conjunction conditions
		tempo.attrinds = R1->attrinds;
		tempo.attrnames = R1->attrnames;
		tempo.natttr = R1->natttr;
		tempo.orig = R1->orig;
		tempo.nrecs = 0;
		for(auto it2: R1->recs)//Checking and evaluating the conjunction conditions
		{
			bool flag = true;
			int i=0;
			for(auto it4: it2->attrptr)//Looping over the attributes of the record and checking the condition for each record
			{
				for(auto it3: it)
				{
					if(R1->attrnames[i] == get<0>(it3))//If there is a condition on the attribute, this part of the code checks if the attribute satisfies the condition.
					{
						//cout<<R1->attrnames[i]<<endl;
						if(get<1>(it3) == '<')
						{
							if(flag)
							flag = (*it4) < *(get<2>(it3));
							//cout<<(it4->floatdata)<<endl;cout<<get<2>(it3)->floatdata<<endl;cout<<flag<<endl;
						}
						if(get<1>(it3) == '=')
						{
							if(flag)
							flag = (*it4) == *(get<2>(it3));
						}
						if(get<1>(it3) == '>')
						{
							if(flag)
							flag = (*it4) > *(get<2>(it3));
						}
					}
				}
				//cout<<flag<<endl;
				i++;
			}
			if(flag)//If all the attributes of the record satisfy all the conditions, the record is added to the resultant relation
			{
				tempo.recs.push_back(it2);
				tempo.nrecs++;
			}
		}
		temp.push_back(tempo);
	}
	if(temp.size()==0)
	{
		return R1;
	}
	if(temp.size()==1)
	{
		temp[0].display();
		return (new Relation(temp[0]));
	}
	else//Taking the union of relations satisfying various different conditions
	{
		Relation * retval = Union(new Relation(temp[0]),new Relation(temp[1]));
		for(int i = 2;i < temp.size();i++)
		{
			retval = Union(new Relation(temp[i]),retval);
		}
		return retval;
	}
}

list<string> commonattributes(Relation* R1,Relation*R2)//Function to generate commonattributes between 2 function to take natural join of the relations
{
	list<string> retval;
	for(auto it:R1->attrnames)
	{
		bool flag = false;
		for(auto it2: R2->attrnames)
		{
			if(it==it2)
			{
				flag = true;
				break;
			}
		}
		if(flag)
		{
			retval.push_back(it);
		}
	}
	return retval;
}
list<tuple<string,char,Attr*>> func(Relation* R1)
{
	list<tuple<string,char,Attr*>> temp;
	for(int i=0;i<R1->attrnames.size();i++)
	{
		cout<<"Do you want to add a condition on "<<R1->attrnames[i]<<"?:(Y/n) ";
		string s;
		cin>>s;
		if(s == "Y")
		{
			cout<<"Choose comparison to perform:\n1)<\n2)=\n3)>\n";
			char scheme[]={'<','=','>'};
			int optinput;
			cin>>optinput;
            char optioninput = scheme[optinput-1];
			cout<<"Enter the value to compare with: ";
			if(R1->orig[i] == "integerAttribute")
			{
				int k;
				cin>>k;
				temp.push_back(make_tuple(R1->attrnames[i],optioninput,makeinstance("integerAttribute",k)));
			}
			if(R1->orig[i] == "floatAttribute")
			{
				float k;
				cin>>k;
				temp.push_back(make_tuple(R1->attrnames[i],optioninput,makeinstance("floatAttribute",0,k)));
			}
			if(R1->orig[i] == "stringAttribute")
			{
				string k;
				cin>>k;
				temp.push_back(make_tuple(R1->attrnames[i],optioninput,makeinstance("stringAttribute",0,0,k)));
			}
		}
	}
	return temp;
}