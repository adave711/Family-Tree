#include<iostream>
#include<string>

using namespace std;
#define COUNT 5;

const int numOFChildren = 6;
const string eldest = "eldest";

struct  person 
{
	string name;
	char gender;
	person * parent;
	person * children[numOFChildren];

};
person* createPerson(string name, char gender, person* parent);
person* createPersonUserInput();
person* findPerson(string);
person* elderstPerson;
void removePerson(string personTODelete);
int checkAvailableChild(person* parent);
void displayPerson(string name);
void outputPerson(person* person);
void navigateFamily(string name);
int mianMenuDisplay();
void selectOption(int option);
bool markChild(person* parent, person* child);
person* check(person* toCheck, string nameTOFind);
bool unMarkParent(person* parent, person* person);
person* unMarkChild(person* p);
void displayTotalTree();
void initializedChild();
bool isValidInput();

person* printTree(person* eldest, int space);

int main() {

	char choice;

	initializedChild();
	elderstPerson = createPerson(eldest, 'M', NULL);
    Menu :int option = mianMenuDisplay();
	selectOption(option);

	flag:cout << " \nPress(Y) to continue or (n) exit ! : ";
	cin >> choice;
	if (!isValidInput()) {
		cout << "Invalid input try again.. !";
		goto flag;
	}
	choice = toupper(choice);
	if (choice == 'Y')
	{
		goto Menu;
	}
	else if (choice == 'N')
	{
		exit(1);
	}
	else
	{
		cout << "Invalid input.. please try again..!";
		goto flag;
	}
	system("pause");
	return 0;
}

void initializedChild()
{

	person initP;

	for (int i = 0; i < numOFChildren; i++)
	{
		initP.children[i] = NULL;
	}
}

int mianMenuDisplay() {

	int option;
	system("CLS");
	
	 cout << "__________________________________________________\n"<< endl;
	 cout << " (1) Create Person" << endl;
	 cout << " (2) Find person" << endl;
	 cout << " (3) Remove person" << endl;
	 cout << " (4) Display person" << endl;
	 cout << " (5) Navigate family" << endl;
	 cout << " (6) Display total tree (Bonus)" << endl;
	 cout << " (7) Exit " << endl;
	 cout << "__________________________________________________" << endl;
	 
	 choice:cout << "\n select choice from above options (1-7) : ";	 
	 cin >> option;
	 cout << endl;
	
	
	 if (!isValidInput()) {
		 cout << "Invalid input try again.. !";
		 goto choice;
	 }
	
	 if (option > 6 || option < 1) 
	 {
		 cout << "Invalid input try again ..!"<<endl;
		 goto choice;
	 }
	
	
	return option;

}

void selectOption(int option)
{
	string name; 
	person* pp;
	
	switch (option)
	{
	case 1: createPersonUserInput();
		break;
	case 2: name:cout << "Please enter the person name : ";
			cin >> name;
			if (!isValidInput()) {
				cout << "Invalid input try again.. !";
				goto name;
			}
		    pp= findPerson(name);
			if (pp == NULL) 
			{
				cout << "Person isn't found !" << endl;
			}
			else
			{
				cout << "Person is found" << endl;
			}
	   	break;
	case 3: pname:cout << "Please enter the person name : ";
		    cin >> name;
			if (!isValidInput()) {
				cout << "Invalid input try again.. !";
				goto pname;
			}
			removePerson(name);
		break;
	case 4:  dname:cout << " Please enter the person name : ";
		     cin >> name;
			 if (!isValidInput()) {
				 cout << "Invalid input try again.. !";
				 goto dname;
			 }
   		     displayPerson(name);
		break;
	case 5: nname:cout << " Please enter the person name to navigate family : ";
		    cin >> name;
			if (!isValidInput()) {
				cout << "Invalid input try again.. !";
				goto nname;
			}
		    navigateFamily(name);
		break;
	case 6: displayTotalTree();
		break;
	case 7: exit(1);
		break;
	}

}

person* createPersonUserInput() {

	 string parentName, name;
	 person* pn;
	 char gender;
	 parent :cout << "Enter  parentname (please enter 'eldest' as parent for first level child):";
	 cin >> parentName;
	 if (!isValidInput()) {
		 cout << "Invalid input try again.. !";
		 goto parent;
	 }
	 person* p = findPerson(parentName);

	 if (p == NULL) 
	 {

		 cout << "\n Parent doesn't exist.. try again!" << endl;
		 goto parent;
	 }
	 else
	 {
		 flag: cout << "\nPlease enter the person name :";
		 cin >> name ;
		 cout << endl;

		 if (cin.fail() || cin.peek() != '\n')
		 {

			 cin.clear();
			 cin.ignore(512, '\n');
			 cout << "Invalid person name try again ..!" << endl;
			 goto flag;
		 }
		 
		

	    gender: cout << "\nplease enter the person gender(M) for male and (F) for female  : ";
		 cin >> gender;
		 
		 gender = toupper(gender);
		 cin.clear();
		 cin.ignore(512, '\n');
		 if (gender == 'M' || gender == 'F'){}
		 else 
		 {
			 cin.clear();
			 cin.ignore(512, '\n');
			 cout << "\nInvalid gender try again.. !" << endl;
			 goto gender;
		 }
		 cout << endl;

		 pn=  createPerson(name, gender, p);
		 if (pn == NULL) 
		 {		 
			 goto flag;
		 }
		 else
		 {
			 cout << "\nPerson is created!"<< endl;
		 }
	 }
	
	 return pn;
	


}


person* createPerson(string name , char gender, person* parent)
{
	person* pp;
	person * toReturn = new person();

	if (name != eldest)
	{
		 pp = findPerson(name);
			 if (pp != NULL)
			 {
				 cout << "person name is already exist " << endl;
				 return NULL;
			 }
	}
	

	(*toReturn).name = name;

	(*toReturn).gender = gender;

	(*toReturn).parent = parent;

	if(name != eldest)
	{
		bool isMarked = markChild(parent, toReturn);
		if (isMarked)
		{
			return toReturn;

		}
		else
		{
			delete toReturn;
			return NULL;
		}
	}
	else
	{
		return toReturn;
	}
	
}

bool markChild(person* parent, person* child) 
{
	int availChild = checkAvailableChild(parent);
    if (availChild != -1 )
	{
		 parent->children[availChild] = child;
		return true;
	}
	else
	{
		cout << "This parent is already having 6 children!..please enter another parent name"<< endl;
		return false;
	}

}

int checkAvailableChild(person* parent)
{
	
	for (int i = 0; i < numOFChildren; i++) {

		if (parent->children[i] == nullptr) {
			return i;
		}
		else
		{
			continue;
		}
	}
	return -1 ;
}

person* findPerson(string nameTOFind)
{

	person* toRetun = check(elderstPerson, nameTOFind);

	return toRetun;
}

person* check(person* toCheck, string nameTOFind)
{
	if (toCheck->name == nameTOFind) {
		return toCheck;
	}

	else
	{
		for (int i = 0; i < numOFChildren; i++) {

			if (toCheck->children[i] != nullptr) {
				person* p = (check(toCheck->children[i], nameTOFind));
					   if(p!=NULL){

						   return p;
				  }
			}
			
		}
	}
	return NULL;
}

void removePerson(string nameTODelete)
{
	remove:person* pp = findPerson(nameTODelete);

	if (pp == nullptr)
	{
		cout << "person name you entered isn't exist .. try again!"<< endl;
		name :cout << "\nEnter the person name to remove :";
		cin >> nameTODelete;

		if (cin.fail() || cin.peek() != '\n')
		{
			cin.clear();
			cin.ignore(512, '\n');
			cout << "Invalid person name try again ..!" << endl;
			goto name;
		}
		cout << endl;
		goto remove;
	}
	else
	{
		if (pp->parent != nullptr)
		{
			bool result=unMarkParent(pp->parent,pp);
			if (!result) 
			{
				cout << "something went wong try again..!" << endl;
			}
		}		
		 person* p=	unMarkChild(pp);

		 if (p != nullptr) {
			 delete p;
			 cout << "Person is removed successfully.!" << endl;
		  }		 
	}
}

bool unMarkParent(person* parent, person* person) {

	for (int i = 0; i < numOFChildren; i++) 
	{
		if (parent->children[i] != NULL) {
			if (parent->children[i]->name == person->name) {
				parent->children[i] = NULL;
				return true;
			}
		}
		
	}
	return false;
}

person* unMarkChild(person* p) {

		for (int i = 0; i < numOFChildren; i++)
		{
			if (p->children[i] != nullptr) {
				
				person* pp= unMarkChild(p->children[i]);
				if (pp!= NULL)
				{
					delete pp;
				}
			}		
		}			
		return p;	
}

void displayPerson(string name) 
{
	char choice;
	person* pp;

		flag:pp = findPerson(name);
		if (pp == NULL)
		{
			choice :cout << "person doesn't exist..wants to try again? enter (y) or (n) : ";
			cin >> choice;
			cout << endl;

			if (!isValidInput()) {
				cout << "Invalid input try again.. !";
				goto choice;
			}

			choice = toupper(choice);
			if (choice == 'Y') {
				goto flag;
			}
			else if (choice=='N')
			{ 
				exit(1);
			}
			else
			{
				cout << "Invalid input try again..!!" << endl;
				goto choice;
			}
		}
		outputPerson(pp);
}

void outputPerson(person* person) 
{
	string children;
	cout << endl;
	cout << "************************************" << endl;
	cout << "Name : " << person->name << endl;
	cout << "Gender : " << ((person->gender == 'M')? "Male":"Female" )<< endl;
	cout << "Parent : "<<((person->parent == NULL)? "Parent doesn't exist": person->parent->name) << endl;
	for (int i = 0; i < numOFChildren; i++) 
	{
		if (person->children[i] != nullptr) 
		{ 
			if (i == 0) 
			{
				children += (person->children[i]->name) ;

			}
			else
			{
				children +=  ", " + (person->children[i]->name) ;

			}
		}

	}
	cout << "children : " << ((children =="")?  "child doesn't exist" :children )<< endl;
	cout << "************************************" << endl;
}

void navigateFamily(string name) 
{
	string parentName, childName;
	char choice; int cnt;
	displayPerson(name);
	cnt:cout << "To naviagate other persons enter (1) or to quit enter(-1) :";
	cin >> cnt;
	cout << endl;

	if (cnt == 1)
	{
	    choice:cout << "please enter (p) to Naviagte  parents or enter (c) to naviagte child : ";
		cin >> choice;

		if (!isValidInput()) {
			cout << "Invalid input try again.. !";
			goto choice;
		}
		cout << endl;
		if (choice == 'p')
		{		
			person* p = findPerson(name);
			if (p->parent != NULL)
			{
			    parent:cout << " Please enter parent name : ";
				cin >> parentName;
				cout << endl;
				
				if ((p->parent->name) == parentName)
				{
					displayPerson(parentName);
					name = parentName;
					goto cnt;
				}
				else
				{
					cout << "Invalid parents name..! try again  " << endl;
					goto parent;
				}
			}
			else
			{
				cout << "Parent doesn't exist try again..!" << endl;
				goto cnt;
			}

		}
		else if (choice == 'c')
		{			
			    person* p = findPerson(name);	
				int flag = 0;
			    cout << " Please enter child name : ";
				cin >> childName;
				cout << endl;
				for (int i = 0; i < numOFChildren; i++)
				{
					if (p->children[i] != nullptr)
					{
						if (p->children[i]->name == childName)
						{
							displayPerson(childName);
							name = childName;
							flag = 1;
							goto cnt;
						}
					}				
				}
				if (flag == 0) {
					cout << "This child name doesn't exist please try again..!" << endl;
					goto cnt;
				}	
		}
		else
		{
			cout << "Invalid input.. please try again..!" << endl;
			goto choice;
		}
	}
	else if ( cnt ==-1)
	{
		exit(1);
	}
	else 
	{
		cout << "Invalid input.. please try again..!" << endl;
	    goto cnt;
	}
	
	
}


void displayTotalTree() {

	person* p = elderstPerson;
	if (p != nullptr) {
		cout << p->name;
		cout << endl;
		printTree(p, 0);
	}
	
	
}

person*  printTree(person* pp, int space) 
{
	int a = COUNT;
	space += COUNT;
	for (int i = 0; i < numOFChildren; i++)
	{		
		if (pp->children[i] !=NULL) 
		{
			cout << endl;
			for (int i = a; i < space; i++) 
			{
				cout << " ";
			}
			cout  << " | ";
			cout <<"--> ";
 			cout << pp->children[i]->name ;
			person* p = (printTree(pp->children[i], space));
		}				
	}	
	return pp;
}

bool isValidInput() {

	if (cin.fail() || cin.peek() != '\n')
	{
		cin.clear();
		cin.ignore(512, '\n');
		return false;
	}
	else
	{
		return true;
	}
}