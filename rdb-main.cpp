#include<iostream>
#include<algorithm>
#include<vector>
#include<list>
#include<set>
#include<tuple>
#include "rdb.h"
using namespace std;
int main()
{
	vector<Relation>rel;//Vector of relations to store the realtions
    int last=-1;//Stores the size of the vector
    while(1)
    {
        //Taking input from user to perform operations
        cout<<endl<<endl;
        if(rel.size()>0)
        {
            cout<<"List of all tables stored currently are: \n";
            for(int i=1;i<=rel.size();i++)
            {
                cout<<"Table "<<i<<":"<<endl;
                rel[i-1].display();
            }
        }
        cout<<"Please choose the operation you wish to perform(type the index of the operation and press enter)"<<endl;
        cout<<"\t1)Create a new table\n";
        cout<<"\t2)Delete an existing table with all the data in it\n";
        cout<<"\t3)Add a record to an existing table\n";
        cout<<"\t4)Print an existing table\n";
        cout<<"\t5)Create a new table using basic operations or perform basic operations on existing tables\n";
        int x;
        cin>>x;
        cout<<endl<<endl;
        if(x==1)//Adding a new relation
        {
            cout<<"Please choose the attributes to add to the new table:"<<endl;//Asking users to select attributes
            Relation temp;
            while(1)//Taking input from user
            {
                cout<<"1)Integer Attribute"<<endl;
                cout<<"2)Float Attribute"<<endl;
                cout<<"3)String Attribute"<<endl;
                cout<<"4)Stop adding attributes"<<endl;
                int x;
                cin>>x;
                if(x==1)//Adding attributes to the relation
                {
                    temp.addattr("integerAttribute");
                }
                else if(x==2)
                {
                    temp.addattr("floatAttribute");
                }
                else if(x==3)
                {
                    temp.addattr("stringAttribute");
                }
                else if(x==4)
                {
                    break;
                }
                else
                {
                    cout<<"Please enter a valid value: ";
                }
            }
            rel.push_back(temp);//Adding the relation to the stored vector
            last++;
        }
        else if(x==3)
        {
            cout<<"Enter the index of the table you wish to add a record to: ";
            int k;
            cin>>k;
            k--;
            while(k>last||k<0)
            {
                cout<<"Please enter a valid value of index: ";
                cin>>k;
                k--;
            }
            (rel[k]).addrec();
        }
        else if (x==2)//Function for deleting a table
        {
            if(last==-1)//Case of empty vector
            {
                cout<<"No tables have been stored currently"<<endl;
                continue;
            }
            cout<<"Enter the index of the table you wish to delete: ";//Taking input of index from user
            int k;
            cin>>k;
            k--;
            while(k>last||k<0)//Checking for valid index
            {
                cout<<"Please enter a valid value of index: ";
                cin>>k;
                k--;
            }
            rel.erase(rel.begin()+k);//Deleting the element
            last--;
        }
        else if(x==4)
        {
            cout<<"Enter the index of the table you wish to view: ";//Taking input of index from user
            int k;
            cin>>k;
            k--;
            while(k>last||k<0)
            {
                cout<<"Please enter a valid value of index: ";
                cin>>k;
                k--;
            }
            cout<<"Requested table is:\n";
            (rel[k]).display();//Displaying the relation
        }
        else if(x==5)
        {
            cout<<"Select the operation you wish to perform:"<<endl;//Taking input of operation user wishes to perform
            cout<<"\t1)Union of 2 tables\n";
            cout<<"\t2)Difference of 2 tables\n";
            cout<<"\t3)Cartesian product of 2 tables\n";
            cout<<"\t4)Projection of 1 table\n";
            cout<<"\t5)Rename attribute in a table\n";
            cout<<"\t6)Selection of an existing table\n";
            cout<<"\t7)Natural join of 2 existing tables\n";
            int k;
            cin>>k;
            while(k>7||k<1)//Asking user to choose valid index
            {
                cout<<"Please select a valid operation: ";
                cin>>k;
            }
            if(k==1)//Performing union of 2 relations
            {
                cout<<"Enter the indices of the tables on which operation is to be performed: ";//Taking input of indices of the 2 relations from user
                int a,b;
                cin>>a>>b;
                a--;
                b--;
                while(a>last||a<0)//Forcing user to input valid index for the first and second relation
                {
                    cout<<"Please enter valid index for the first table: ";
                    cin>>a;
                    a--;
                }
                while(b<0||b>last)
                {
                    cout<<"Please enter valid index for the second table: ";
                    cin>>b;
                    b--;
                }
                if(Union(&rel[a],&rel[b]) != NULL)//Null is returned when the 2 relations are not union compatible
                {
                    rel.push_back(*(Union(&rel[a],&rel[b])));//Pushing the union of 2 relations into the vector
                    last++;
                }
            }
            if(k==2)//Performing difference of 2 relations
            {
                cout<<"Enter the indices of the tables on which operation is to be performed: ";//Taking input of indices
                int a,b;
                cin>>a>>b;
                a--;
                b--;
                while(a>last||a<0)
                {
                    cout<<"Please enter valid index for the first table: ";
                    cin>>a;
                    a--;
                }
                while(b<0||b>last)
                {
                    cout<<"Please enter valid index for the second table: ";
                    cin>>b;
                    b--;
                }
                rel.push_back(*difference(&rel[a],&rel[b]));//Storing the difference of 2 relations
                last++;
            }
            if(k==3)//Calculating Cartesian Product of 2 relations
            {
                cout<<"Enter the indices of the tables on which operation is to be performed: ";//Taking input of relations on which operation is to be performed
                int a,b;
                cin>>a>>b;
                a--;
                b--;
                while(a>last||a<0)
                {
                    cout<<"Please enter valid index for the first table: ";
                    cin>>a;
                    a--;
                }
                while(b<0||b>last)
                {
                    cout<<"Please enter valid index for the second table: ";
                    cin>>b;
                    b--;
                }
                rel.push_back(*CartesianProduct(&rel[a],&rel[b]));//Storing the cartesian product of the 2 relations
                last++;
            }
            if(k==4)//Calculating the projection of relation
            {
                cout<<"Enter the index of table on which operation is to be performed: ";//Taking input of relartion on which operation is to be performed
                int a;
                cin>>a;
                a--;
                while(a<0||a>last)
                {
                    cout<<"Enter a valid index of a: ";
                    cin>>a;
                    a--;
                }
                cout<<"Enter the attributes to be considered in the resultant relation(Press -1 to stop): ";//Taking input of attributes from the user to perform projections
                list<string> temp;
                string s;
                cin>>s;
                while(s != "-1")
                {
                    temp.push_back(s);
                    cin>>s;
                }
                rel.push_back(*projection(&rel[a],temp));//Storing the result of projection of the relation
                last++;
            }
            if(k==5)//Renaming an attribute of the relation
            {
                cout<<"Enter the index of table whose attribute is to be renamed: ";//Taking input of relation on which operation is to be performed
                int a;
                cin>>a;
                a--;
                while(a<0||a>last)
                {
                    cout<<"Enter a valid index: ";
                    cin>>a;
                    a--;
                }
                cout<<"Enter the old name of the attribute: ";//Taking in old name of the attribute
                string old;
                cin>>old;
                cout<<"Enter the new name of the attribute: ";//Taking in new name of the attribute
                string newname;
                cin>>newname;
                difference(&rel[a],old,newname);
            }
            if(k==6)//Calculating the selection of a relation
            {
                DNFformula f;
                cout<<"Enter the index of table on which operation is to be performed: ";//Taking in the input of relation on which operation is to be performed
                int a;
                cin>>a;
                a--;
                while(a<0||a>last)//Forcing the user to input valid index
                {
                    cout<<"Enter a valid index: ";
                    cin>>a;
                    a--;
                }
                while(1)//Taking input of conditions for the selection operation
                {
                    cout<<"Choose the operation you want to perform: \n";
                    cout<<"\t1)Enter a new set of conditions\n";
                    cout<<"\t2)Stop adding conditions\n";
                    int l;
                    cin>>l;
                    while(l>2||l<1)//Fprcing user to provide valid input
                    {
                        cout<<"PLease choose a valid option: ";
                        cin>>l;
                    }
                    if(l==2)//Stopping taking input
                    {
                        break;
                    }
                    list<tuple<string,char,Attr*>>temp;//Taking the set of input on which intersection is to be performed
                    // cout<<"Do you want to add a condition on integerAttribute:(Y/n) ";
                    // char input;
                    // cin>>input;
                    // char scheme[]={'<','=','>'};
                    // if(input == 'Y')//Taking input conditions for integerattribute
                    // {
                    //     cout<<"Choose the type of comparison you wish to perform: \n";
                    //     int optinput;
                    //     cout<<"\t1)<\n";
                    //     cout<<"\t2)=\n";
                    //     cout<<"\t3)>\n";
                    //     cin>>optinput;
                    //     char optioninput = scheme[optinput-1];
                    //     cout<<"Enter the value to compare with: ";
                    //     int valinput;
                    //     cin>>valinput;
                    //     temp.push_back(make_tuple("integerAttribute",optioninput,makeinstance("integerAttribute",valinput)));
                    // }
                    // cout<<"Do you want to add a condition on floatAttribute:(Y/n) ";
                    // cin>>input;
                    // if(input == 'Y')//Taking input of conditions for floatattributes
                    // {
                    //     cout<<"Choose the type of comparison you wish to perform: \n";
                    //     int optinput;
                    //     cout<<"\t1)<\n";
                    //     cout<<"\t2)=\n";
                    //     cout<<"\t3)>\n";
                    //     cin>>optinput;
                    //     char optioninput = scheme[optinput-1];
                    //     cout<<"Enter the value to compare with: ";
                    //     float valinput;
                    //     cin>>valinput;
                    //     temp.push_back(make_tuple("floatAttribute",optioninput,makeinstance("floatAttribute",0,valinput)));
                    // }
                    // cout<<"Do you want to add a condition on stringAttribute:(Y/n) ";
                    // cin>>input;
                    // if(input == 'Y')//Taking input of conditions for stringattributes
                    // {
                    //     cout<<"Choose the type of comparison you wish to perform: \n";
                    //     int optinput;
                    //     cout<<"\t1)<\n";
                    //     cout<<"\t2)=\n";
                    //     cout<<"\t3)>\n";
                    //     cin>>optinput;
                    //     char optioninput = scheme[optinput-1];
                    //     cout<<"Enter the value to compare with: ";
                    //     string valinput;
                    //     cin>>valinput;
                    //     temp.push_back(make_tuple("stringAttribute",optioninput,makeinstance("stringAttribute",0,0,valinput)));
                    // }
                    temp = func(&rel[a]);
                    f.ops.push_back(temp);
                }
                rel.push_back(*Union(&rel[a],&f));
                last++;
            }
            if(k==7)//Performing natural join of 2 relations
            {
                cout<<"Enter the indices of tables on which the opertaion is to be performed: ";//Taking input of relations on which operations is to be performed
                int a,b;
                cin>>a>>b;
                a--;
                b--;
                while(a<0||a>last)//Forcing user to enter valid inputs
                {
                    cout<<"Please enter valid index for first table: ";
                    cin>>a;
                    a--;
                }
                while(b<0||b>last)
                {
                    cout<<"Please enter a valid index for the second table: ";
                    cin>>b;
                    b--;
                }
                rel.push_back(*naturaljoin(&rel[a],&rel[b],commonattributes(&rel[a],&rel[b])));//Storing natural join of the 2 relations
                last++;
            }
        }
    }
}
