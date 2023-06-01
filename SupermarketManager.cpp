#include<iostream>
#include<cstring>
#include<fstream>
#include<stdlib.h>
using namespace std;
#define key 8
class Employee{
    public:
    string name;
    string password;
    Employee *next;
    Employee *prev;
};
class Owner{
    Employee *head = NULL;
    public:
    //ADMIN PASSWORD
    string admin_password = "OwnerPW";
    
    
    void addemp(){
        Employee *temp = new Employee;
        Employee *temp2 = head;
        string valid;
        cout << "Enter the employee name: ";
        cin >> temp->name;
        char ch;
        label:
        cout << "Enter the Employee Password: ";
        cin>>valid;
        
        int length = valid.length();
        temp2 = head;
        while(temp2 != NULL){
            if(temp2->password == valid){
                cout<<"Password already assigned! Enter a new password";
           
				goto label;
               
            }
            temp2 = temp2->next;
        }
       
        if( length <= 8){
                cout<<"Invalid Password! Passwords must be have greater than 8 characters"<<endl;
            
				goto label;
           }
        temp->password = valid;
       
        for(int i = 0; valid[i] != '\0'; ++i) {
         ch = valid[i];
         //encrypt for lowercase letter
         if (ch >= 'a' && ch <= 'z'){
            ch = ch + key;
            if (ch > 'z') {
               ch = ch - 'z' + 'a' - 1;
            }  
            valid[i] = ch;
         }
         //encrypt for uppercase letter
         else if (ch >= 'A' && ch <= 'Z'){
            ch = ch + key;
            if (ch > 'Z'){
               ch = ch - 'Z' + 'A' - 1;
            }
            valid[i] = ch;
         }
      }
      ofstream  pwout("password.txt",ios::app);
      pwout<<valid<<endl;
      pwout.close();

        if (head == NULL){
            head = temp;
            temp->next = NULL;
            temp->prev = NULL;
            
        }
        else{
            temp2 = head;
           
            while (temp2->next != NULL){
                temp2 = temp2->next;
        	}
    	temp2->next = temp;
        temp->prev = temp2;
        temp->next = NULL;
      
    }
    }
    void displayemp(){
    	Employee *temp = head;
    	int i = 1;
		while(temp != NULL){
    		cout<<"Employee "<<i++<<": "<<temp->name<<endl;
    		temp = temp->next;
		}
		
	}
	bool searchbyname(string nm){
    	Employee *temp = head;
    	int i = 1;
		while(temp != NULL){
    		if(temp->name == nm){
    			return true;	
			}
			else{
				temp = temp->next;
			}	
		}
		return false;
		
	}
	bool searchbypassw(string pw){
    	Employee *temp = head;
    	int i = 1;
		while(temp != NULL){
    		if(temp->password == pw){
    			return true;	
			}
			else{
				temp = temp->next;
			}	
		}
		return false;
		
	}
	
	void displaypw(){
		string pw;
		Employee *temp = head;
		cout<<"Enter administrator password: ";
		cin>>pw;
		if(pw  == admin_password){
			cout<<"Employees : Passwords"<<endl<<endl;
			string msg;
			ifstream MyReadFile("password.txt");
			while (getline (MyReadFile, msg)) {
  				// Output the text from the file
  				

			
			
			char ch;
      		for(int i = 0; msg[i] != '\0'; ++i) {
        	 ch = msg[i];
         	//decrypt for lowercase letter
        	 if(ch >= 'a' && ch <= 'z') {
            ch = ch - key;
            if(ch < 'a'){
               ch = ch + 'z' - 'a' + 1;
            }
            msg[i] = ch;
         }
         //decrypt for uppercase letter
        	 else if(ch >= 'A' && ch <= 'Z') {
            ch = ch - key;
            if(ch < 'A') {
               ch = ch + 'Z' - 'A' + 1;
            }
            msg[i] = ch;
         }
      }
    cout <<temp->name<<" : "<< msg<<endl;;
	temp = temp->next;
	}}
	else{
		cout<<"Invalid Password"<<endl;
	}
	}

    
};
 bool checkLuhn(const string& cardNo)
{
    int nDigits = cardNo.length();
 
    int nSum = 0, isSecond = false;
    for (int i = nDigits - 1; i >= 0; i--) {
 
        int d = cardNo[i] - '0';
 
        if (isSecond == true)
            d = d * 2;
 
    
        nSum += d / 10;
        nSum += d % 10;
 
        isSecond = !isSecond;
    }
    return (nSum % 10 == 0);
}

class Item{
    public:
    string name;
    int price;
    Item *next = NULL;
    Item *prev  = NULL;
};
class List{
    Item *head = NULL;
    int count;
    public:
   
    List(){

    }
    void addtocart(){
        Item* temp = new Item;
        int valid;
        cout << "Enter the Product name: ";
        cin >> temp->name;
        label:
        cout << "Enter the Product Price: ";
        cin>>valid;
        if(valid > 0){
            temp->price = valid;
        }
        else{
            cout<<"Invalid Price!"<<endl;
            goto label;
        }
        if (head == NULL){
            head = temp;
        }
        else{
            Item* temp2 = head;
            while (temp2->next != NULL)
         {
                temp2 = temp2->next;
        }
        temp2->next = temp;
        temp->prev = temp2;
        count++;

    }
    }
    
    void checkout(){
        Item *temp = head;
        int total = 0;
        while(temp != NULL){
            total += temp->price;
            temp = temp->next;
        }
        string cname, ccredit;
        cout<<"Enter the customers name: ";
        cin>>cname;
        int choice;
        cout<<"Will the customer pay by cash(1) or credit card(2)?"<<endl;
        cin>>choice;
        if(choice == 1){
            cout<<"Kindly collect $"<<total<<" from the customer "<< cname <<endl;
            cout<<"Items brought:"<<endl;
            temp = head;
            while (temp != NULL)
            {
                cout<<"Item: "<<temp->name<<endl<<"Price: "<<temp->price<<endl;
                temp = temp->next;
            }
            
        }
        else if(choice == 2){
        	cred:
            cout<<"Enter the credit card number: ";
            cin>>ccredit;
            checkLuhn(ccredit);
            if(checkLuhn(ccredit)){
                cout<<"The Transaction has been successfull"<<endl;
            }
            else{
                cout<<"Invalid Credit Card!"<<endl;
                goto cred;
            }
        }
        else{
            cout<<"Invalid choice!"<<endl;
        }
    }
   
    bool isempty(){
        return(count == 0);
    }
    
};

int main(){
	Owner o1;
    while(1){
    string pw;
	cout<<"Enter the Administrator password: ";
	cin>>pw;
	if(pw == o1.admin_password){
		break;
	}
	else{
		cout<<"Wrong Password"<<endl;
	}
	}
	int empnum;
    system("CLS");
    cout<<"\t\tADMINISTRATOR PORTAL\n\n";
    cout<<"Enter the number of employees in the store: ";
    cin>>empnum;
    for(int i = 0;i<empnum;i++){
    	o1.addemp();
	}
	o1.displayemp();
	string un,epw;
    
	while(1){
        label3:
		cout<<"Enter your username: ";
		cin>>un;
		if(o1.searchbyname(un)){
			label2:
			cout<<"Enter your Password: ";
			cin>>epw;
			if(o1.searchbypassw(epw)){
				break;
			}
			else{
				cout<<"Invalid Password!"<<endl;
				goto label2;
			}
		}
		else{
			cout<<"Invalid Username"<<endl;
            goto label3;
		}
    }
    system("CLS");
    cout<<"\t\tEMPLOYEE PORTAL\n\n";
    List l1;
    ;
    while(1){
        int choice;
        cout<<"1)Add Items to Cart"<<endl;
        cout<<"2)Checkout Items"<<endl;
        cout<<"3)Display Empoyees and their passwords(Reuires administrator access)"<<endl;
        cout<<"4)Exit"<<endl;
        
        cout<<"Enter your choice: "<<endl;
        cin>>choice;
        if(choice  == 1){
            l1.addtocart();
        }
        else if(choice == 2){
            if(!l1.isempty())
                l1.checkout();
            else
                cout<<"No items added to cart!"<<endl;
        }
        else if(choice  == 3){
            o1.displaypw();
        }
        else if(choice  == 4){
            break;
        }
        else{
        	cout<<"Invalid Input"<<endl;
		}
    }
    

	
}
