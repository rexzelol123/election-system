#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

typedef struct node{// structure for the voters
    int idNum;
    int age;
    string firstName;
    string lastName;
    string gender;
    string pw;
    struct node *next;
}REC;

typedef struct cand{
    string candFirst;
    string candLast;
    int tally;
    struct cand *then;
}CAND;

typedef struct done{
    int doneNum;
    struct done *after;
}VOTE;

typedef struct usb{
    int usbID;
    int usbAge;
    string usbFirst;
    string usbLast;
    string usbGender;
    string usbPw;
    struct usb *nxt;
}USB;

class myRec{
private:
    REC *L;
    CAND *C;
    VOTE *V;
    USB *U;
public:
    void makenull();
    void makenullCand();
    void makenullDone();
    void makenullUsb();
    void add(REC *y);
    void addCand(CAND *v);
    void addDone(VOTE *e);
    void addFlash(USB *u);
    void save();
    void savecand();
    void saveflash();
    void donesave();
    void retrieve();
    void retcand();
    void retflash();
    void doneretrieve();
    void dispStud();
    void remark(int a);
    void dispCand();
    void dispCandtwo();
    void vote(int x);
    void candTally(int x);
    void locate(int a);
    void locateidnum(int a);
    void del(int a);
    void delCand(int a);
    bool isEmpty();
    bool usbEmpty();
    bool duplicate(string l, string f);
    void moduleOne();
    void moduleTwo();
    void moduleThree();
    int editMenu();
};
char pass[51];
// Make 1st node equal to NULL
void myRec::makenull()
{
    L = NULL;
}
void myRec::makenullCand()
{
    C = NULL;
}
void myRec::makenullDone()
{
    V = NULL;
}
void myRec::makenullUsb()
{
    U = NULL;
}

void myRec::add(REC *y){

    REC *p,*q,*temp;
    p=q=L;
    temp = new REC;
    temp->idNum = y->idNum;
    temp->lastName = y->lastName;
    temp->firstName = y->firstName;
    temp->age = y->age;
    temp->gender = y->gender;
    temp->pw = y->pw;

    while(p!=NULL&& (y->lastName.compare(p->lastName))>0){
        q=p;
        p=p->next;
    }
    if(p==L) {// If first element
        L=temp;
    }else{
        q->next = temp;
    }
    temp->next = p;
}

void myRec::addCand( CAND *v){
    CAND *b, *n, *pen;
	b=n=C;
	pen = new CAND;
	pen->candFirst = v->candFirst;
	pen->candLast =	v->candLast;
	pen->tally = v->tally;
	while(b!=NULL){
		n=b;
		b=b->then;
	}
	if(b==C){
		C=pen;
	}
	else{
		n->then = pen;
	}
	pen->then = b;

}
void myRec::addDone(VOTE *e){

	VOTE *z, *x, *hen;
	z=x=V;

    hen = new VOTE;
	hen->doneNum = e->doneNum;

	while(z!=NULL){
		x=z;
		z=z->after;
	}if(z==V){
		V=hen;
	}else{
		x->after = hen;
	}
	hen->after = z;
}

void myRec::addFlash(USB *u){
    USB *p,*q,*temp;
    p=q=U;
    temp = new USB;
    temp->usbID = u->usbID;
    temp->usbLast = u->usbLast;
    temp->usbFirst = u->usbFirst;
    temp->usbAge = u->usbAge;
    temp->usbGender = u->usbGender;
    temp->usbPw = u->usbPw;

    while(p!=NULL){
        q=p;
        p=p->nxt;
    }
    if(p==U) {// If first element
        U=temp;
    }else{
        q->nxt = temp;
    }
    temp->nxt = p;
}

void myRec::save(){
    fstream fp;
    REC *p;
    p=L;
    fp.open("rexzelRecordl.dbf",ios::out);
    while(p!=NULL){
        fp<<p->idNum<<" "<<p->lastName<<" "<<p->firstName<<" "<<p->age<<" "<< p->gender<<" "<<p->pw<<endl;
        p = p->next;
}
fp.close();
}

void myRec::savecand(){

	fstream fp;
	CAND *b;
	b=C;
	fp.open("candidaterexl.dbf", ios::out);
	while(b!=NULL){
		fp<< b-> candFirst <<" " << b->candLast <<" " << b->tally<<endl;
		b = b->then;
	}
fp.close();
}
void myRec::donesave(){

	fstream fp;
	VOTE *b;
	b = V;
	fp.open("doneRecordl.dbf", ios::out);
	while(b!=NULL){
        fp<< b->doneNum <<endl;
        b=b->after;
	}
	fp.close();
}
void myRec::saveflash(){
    fstream fp;
    USB *p;
    p=U;
    fp.open("e:\\flashRecl.dbf",ios::out);
    while(p!=NULL){
        fp<<p->usbID<<" "<<p->usbLast<<" "<<p->usbFirst<<" "<<p->usbAge<<" "<< p->usbGender<<" "<<p->usbPw<<endl;
        p = p->nxt;
}
fp.close();
}
void myRec::retrieve(){//function to populate the records from the dbf file
        fstream fp;//declaration of the file
        REC y;// memory address declaration

        fp >>y.idNum>>y.lastName>>y.firstName>> y.age >> y.gender >>y.pw; //scans the data from the file
        fp.open("rexzelRecordl.dbf", ios::in);//opening the file
        if(!fp){
            fp.open("rexzelRecordl.dbf", ios::out);//opening the file
        }
        else{
            while(true){
                fp >>y.idNum>>y.lastName>>y.firstName>> y.age >> y.gender>>y.pw;//scans the data from the file

                if(fp.eof())//scans the file until it raised to the end of file
                {
                    break;//terminate the loop
                }
                add(&y);//passes the data to function for inserting student record

            }
        }

fp.close();
}
void myRec::retcand(){
        fstream fp;//declaration of the file
        CAND v;// memory address declaration

        fp>>v.candFirst>>v.candLast>>v.tally; //scans the data from the file
        fp.open("candidaterexl.dbf", ios::in);//opening the file
        if(!fp){
            fp.open("candidaterexl.dbf", ios::out);//opening the file
            fp<<"leni robredo 0\nbongbong marcos 0\nmanny pacquiao 0\nisko moreno 0"<<endl;
            fp.close();
            fp>>v.candFirst>>v.candLast>>v.tally;; //scans the data from the file
            fp.open("candidaterexl.dbf", ios::in);//opening the file
            while(true){
                fp>>v.candFirst>>v.candLast>>v.tally;//scans the data from the file
                if(fp.eof())//scans the file until it raised to the end of file
                {
                    break;//terminate the loop
                }
                addCand(&v);
            }
        }
        else{
            while(true){
                fp>>v.candFirst>>v.candLast>>v.tally;//scans the data from the file
                if(fp.eof())//scans the file until it raised to the end of file
                {
                    break;//terminate the loop
                }
                addCand(&v);//passes the data to function for inserting student record
            }
        }

fp.close();
}
void myRec::retflash(){
fstream fp;
USB p;
	fp>>p.usbID >> p.usbLast >> p.usbFirst >> p.usbAge >> p.usbGender >> p.usbPw;
	fp.open("e:\\flashRecl.dbf",ios::in);

	if(!fp){
		while(!fp){

			fp.open("e:\\flashRecl.dbf", ios::out);
			system("cls");
            system("color a");
			cout<<"INSERT FLASH DRIVE"<<endl;
			system("pause");
		}
    }else{
		    system("cls");
            system("color a");

			while(true){
				fp>>p.usbID >> p.usbLast >> p.usbFirst >> p.usbAge >> p.usbGender >> p.usbPw;
				if(fp.eof()){
					break;
				}
				addFlash(&p);

			}
		}
fp.close();
}

void myRec::doneretrieve(){//function to populate the records from the dbf file
        fstream fp;//declaration of the file
        VOTE v;// memory address declaration
	fp>>v.doneNum;

	fp.open("doneRecordl.dbf", ios::in);
	if(!fp){
		fp.open("doneRecordl.dbf", ios::in);
	}else{
		while(true){
			fp>>v.doneNum;
			if(fp.eof()){
				break;
			}
			addDone(&v);
		}

fp.close();
}
}



void myRec::dispStud(){
    REC *p;
    p=L;
    system("cls");
    if(isEmpty())
    {
        cout <<"\n\n\n\n\t\t\t\t\tThe list contains nothing\n\n";
    }
    else{
        cout<<"   ========================================================================================================="<<endl;
        cout<<"   |   ID Number   |   Last Name   |   First Name   |   Gender   |   Age   |   Password   |     remarks    |\n";
        cout<<"   ========================================================================================================="<<endl;
        while(p!=NULL)
        {
            cout <<"   |    "<<p->idNum <<"     |      "<<p->lastName <<"      |       " <<p->firstName <<"      |   ";
            if(p->gender=="m"){
                cout<<" male    |   ";
            }else{
                cout<<"female   |   ";
            }
            cout<<p->age<<"    |     " <<p->pw<<"   |";
            remark(p->idNum);
            //cout<<"   ========================================================================================================="<<endl;
            //cout<<"   ---------------------------------------------------------------------------------------------------------"<<endl;
            p=p->next;
        }
        cout<<"   ========================================================================================================="<<endl;

}
}

void myRec::remark(int a){

	VOTE *z,*x;
	z=x=V;

	while(z!=NULL&&z->doneNum!=a){
		z = z->after;
	}if(z==NULL){
		cout<<"    NOT VOTED   |"<<endl;
	}else{
		cout<<"  ALREADY VOTED |"<<endl;
 	}
}
void myRec::dispCandtwo(){
    CAND *b;
    b=C;
    int num =1;
    system("cls");
        cout<<"\n\t\t\t\t\t======================================";
        cout<<"\n\t\t\t\t\t|             CANDIDATES             |";
        cout<<"\n\t\t\t\t\t======================================"<<endl;
        while(b!=NULL)
        {
            cout<<"\t\t\t\t\t    [" <<num <<"]      "<<b->candFirst <<" "<<b->candLast<<endl;
            num++;
            b=b->then;
        }
        cout<<"\t\t\t\t\t======================================"<<endl;
}
void myRec::dispCand(){
    CAND *b;
    b=C;
    int num = 1;
    system("cls");
        cout<<"\n\t\t\t\t\t======================================";
        cout<<"\n\t\t\t\t\t     CANDIDATES     |      VOTE COUNT ";
        cout<<"\n\t\t\t\t\t======================================"<<endl;
        while(b!=NULL)
        {
            cout<<"\t\t\t\t\t[" <<num <<"]  "<<b->candFirst <<" "<<b->candLast <<" \t\t" <<b->tally<<endl;
            num++;
            b=b->then;
        }
        cout<<"\t\t\t\t\t======================================"<<endl;

}
bool myRec::isEmpty()
{
    return(L==NULL);
}
bool myRec::usbEmpty()
{
    return(U==NULL);
}
bool myRec::duplicate(string l, string f)
{
    REC *p;
    p=L;
    while(p!=NULL && p->lastName!=l && p->firstName!=f)
    {
        p=p->next;
    }
    if (p==NULL)
    {
        return false;
    }
    else
    {
        return true;
    }
}

char *pin(){//function for pin
 char ch;//declaring where the getch will be stored

 int i;
   while (1) {
      if (i < 0) {
         i = 0;
      }
      ch = getch();

      if (ch == 13)
         break;
      if (ch == 8) /*ASCII value of BACKSPACE*/
      {
         putch('b');
         putch('\0');
         putch('b');
         i--;
         continue;
      }

      pass[i++] = ch; //storing each value inputted in ch
      ch = '*';//printing * for privacy purposes
      putch(ch);
   }
   pass[i] = '\0';//storing null on the last value of array
return(pass);//returing the value of pass
}


void myRec::vote(int x){
	string pass;
	int num;
	USB *q, *p, y;
	VOTE z;
	p=q=U;
    z.doneNum = x;
	while(p!=NULL && p ->usbID!=x){
		p=p->nxt;
	}if(p==NULL){
		cout<<"\t\t\t\t\t\tRECORD NOT FOUND!\n\n\t\t\t\t\t\t";
		system("pause");
	}else{
		cout<<"\n\t\t\t\t\t\tENTER PASSWORD: ";
		pass = pin();

		if(pass == p->usbPw){
			dispCandtwo();
			cout<<"\t\t\t\t\tENTER NUMBER OF THE CANDIDATE YOU WANT TO VOTE: ";
			cin>>num;
			candTally(num);
			addDone(&z);
			system("pause");
		}else{
			cout<<"\n\n\t\t\t\t\t\tWRONG PASSWORD\n\n\t\t\t\t\t\t";
			system("pause");
		}
}
}

void myRec::candTally(int x){
	CAND *q, *p, y;
	p=q=C;
    int vote=1;
	while(p!=NULL && vote!=x){
	    vote++;
		p=p->then;
	}
	if(p==NULL){
		cout << "\t\t\t\t\t\tCANDIDATE NOT FOUND!\n\n\t\t\t\t\t\t" ;
	}else{
		p->tally = p->tally+1;
		cout<<"\t\t\t\t\t\tTHANK YOU FOR VOTING\n\n\t\t\t\t\t\t";
	}
}


void myRec::locate(int a){

	VOTE *z,*x;
	USB *p, *q;
	z=x=V;
	p=q=U;
    while(p!=NULL&&p->usbID!=a){
		p = p->nxt;
	}
	while(z!=NULL&&z->doneNum!=a){
		z = z->after;
	}if(p==NULL){
        cout<<"\n\t\t\t\t\t\tRECORD NOT FOUND\n\n\t\t\t\t\t\t";
        system("pause");
    }else if(z==NULL){
		vote(a);
	}else{
		cout<<"\n\t\t\t\t\t\tYOU ALREADY VOTED\n\n\t\t\t\t\t\t";
        system("pause");
}
}
void myRec::locateidnum(int a){

	USB *z,*x;
	REC *p, *q;
	int choice, edad;
	string first, last, sex, pass, pword;
	z=x=U;
	p=q=L;

	while(z!=NULL&&z->usbID!=a){
		z = z->nxt;
	}
	while(p!=NULL&&p->idNum!=a){
		p = p->next;
	}if(z==NULL){
		cout<<"\n\t\t\t\t\t\tRECORD NOT FOUND\n\n\t\t\t\t\t\t";
		system("pause");
	}else{
		cout<<"\n\t\t\t\t\t\tENTER PASSWORD: ";
		pword = pin();
		if(pword==z->usbPw){

			while(choice !=6){
			    system("cls");
                cout<<"\n\t\t\t\t\t      \xdb\xdb\xdb\xdb|EDITING SYSTEM MENU|\xdb\xdb\xdb\xdb";
                cout<<"\n\t\t\t\t\t---------------------------------------";
				cout<<"\n\t\t\t\t\t\tLast Name: "<< z->usbLast <<endl;
				cout<<"\t\t\t\t\t\tFirst Name: "<< z->usbFirst <<endl;
				cout<<"\t\t\t\t\t\tAge: "<< z->usbAge <<endl;
				cout<<"\t\t\t\t\t\tGender: " <<z->usbGender <<endl;
				cout<<"\t\t\t\t\t\tPassword: "<<z->usbPw <<endl;


				choice = editMenu();
				if(choice == 1){
					cout<<"\n\t\t\t\t\tEnter your new last name: ";
					cin>> last;
					cout<<"\n\t\t\t\t\tEnter your new first name: ";
					cin>>first;
					z->usbLast =last;
					z->usbFirst = first;
					p->lastName = last;
					p->firstName = first;
					cout<<"\n\n\t\t\t\t\tYour new name is: "<<first<<" "<<last<<"\n\t\t\t\t\t";
					system("pause");
				}else if(choice == 2){
					cout<<"\n\t\t\t\t\tEnter your new gender [m/f]: ";
					cin>>sex;
					z->usbGender = sex;
					p->gender = sex;
					cout<<"\n\n\t\t\t\t\tYour new gender is: "<<sex<<"\n\t\t\t\t\t";
					system("pause");
				}else if(choice == 3){
					cout<<"\n\t\t\t\t\tEnter your new age: ";
					cin>>edad;
					z->usbAge = edad;
					p->age = edad;
					cout<<"\n\n\t\t\t\t\tYour new age is: "<<edad<<"\n\t\t\t\t\t";
					system("pause");
				}else if(choice == 4){
					cout<<"\n\t\t\t\t\tEnter your new password";
					pass = pin();
					z->usbPw = pass;
					p->pw = pass;
					cout<<"\n\n\t\t\t\t\tYour new password is: " <<pass<<"\n\t\t\t\t\t";
					system("pause");
				}else if(choice==5){
				    del(a);
				}else if(choice==6){
				    cout<<"\n\t\t\t\t\t";
					system("pause");
				}else{
				    cout<<"\n\t\t\t\t\t1-6 only"<<"\n\t\t\t\t\t";
					system("pause");
				}
			}
                save();
                saveflash();
                makenullUsb();
                makenull();
                retrieve();
                retflash();
		}else{
			cout<<"\n\t\t\t\t\t\tWRONG PASSWORD\n\n\t\t\t\t\t\t";
			system("pause");
		}
	}
}
void myRec::del(int a){

        REC *p, *q;//memory address declaration for the struct
        p = q = L;//initialize data in p q and st to be equal
        USB *z,*x;
        z = x = U;


        if(isEmpty()){//tests if the list is empty
            cout << "The record is empty!" << endl;
        }else{
            while(p!=NULL && p->idNum!=a){//while p has content and the id save in p is not equal to input
                q=p; //address q is now = to address p
                p=p->next; //address p is now the address p next
            }
            while(z!=NULL && z->usbID!=a){
                z = z->nxt;
            }
            if(p==NULL&&z == NULL){//no match is found
                cout << "Record not found!" << endl;
            }else{
                if(p==L&&z==U){
                    L = L-> next;
                    U = U->nxt;
                }else{
                    q->next = p->next;//address q next is now address p next
                    x->nxt = z->nxt;
                    delete(p); //deletes p
                    delete(z); //deletes z
                }
            }
            }
}
void myRec::delCand(int a){

	CAND *p, *q;//memory address declaration for the struct
    p = q = C;//initialize data in p q and st to be equal
	int num = 1;

        if(isEmpty()){//tests if the list is empty
            cout << "The record is empty!" << endl;
        }else{
            while(p!=NULL && num!=a){//while p has content and the id save in p is not equal to input
                num++;
                q=p; //address q is now = to address p
                p=p->then; //address p is now the address p next
            }
            if(p==NULL){//no match is found
                cout << "Record not found!" << endl;
            }
            else{
                if(p==C){//if address p is equal to starting address
                    C=C->then;//address st is now address p next
                }
                else{
                    q->then=p->then;//address q next is now address p next
                    delete(p); //deletes p
                }
                cout << endl << "Record Deleted!" << endl;//prints text for successful delete
                }
            }
}




// Function to display the Menu and return user's choice
int menu(){
    int opt;
    system("cls");
    system("color a");
    cout<<"\n\n\n\t\t\t\t--------------------------------------------------------";
    cout<<"\n\n\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb|WELCOME TO OUR PROJECT|\xdb\xdb\xdb\xdb\xdb";
    cout<<"\n\n\t\t\t\t\t   Student Election Voting System ";
    cout<<"\n\n\t\t\t\t--------------------------------------------------------";
    cout<<"\n\t\t\t\t  CREATOR: CASIMSIMAN, JERALD FROM BSCS-2B-M";
    cout<<"\n\n\n\t\t\t\t\t---------------------------------------";
    cout<<"\n\t\t\t\t\t\t\t|MENU|";
    cout<<"\n\t\t\t\t\t---------------------------------------";
    cout<<"\n\t\t\t\t\tModule [1]: REGISTRATION";
    cout<<"\n\t\t\t\t\tModule [2]: VOTING SYSTEM";
    cout<<"\n\t\t\t\t\t       [3]: FOR ADMINISTRATOR ONLY";
    cout<<"\n\t\t\t\t\t       [4]: EXIT ";
    cout<<"\n\t\t\t\t\t---------------------------------------";
    cout<<"\n\n\t\t\t\t\tPlease Select only from 1-4: ";
    cin >> opt;
    return opt;
}
int regMenu() {
    system("cls");
    int opt;
    cout<<"\n\t\t\t\t\t      \xdb\xdb\xdb\xdb|REGISTRATION MENU|\xdb\xdb\xdb\xdb";
    cout<<"\n\t\t\t\t\t---------------------------------------";
    cout<<"\n\t\t\t\t\t       [1]: UPDATE ACCOUNT";
    cout<<"\n\t\t\t\t\t       [2]: NOT REGISTERED";
    cout<<"\n\t\t\t\t\t       [3]: BACK ";
    cout<<"\n\t\t\t\t\t---------------------------------------";
    cout<<"\n\n\t\t\t\t\tPlease Select only from 1-3: ";
    cin>>opt;
    return (opt);
}
int voteMenu() {
    system("cls");
    int opt;
    cout<<"\n\t\t\t\t\t      \xdb\xdb\xdb\xdb|VOTING SYSTEM MENU|\xdb\xdb\xdb\xdb";
    cout<<"\n\t\t\t\t\t---------------------------------------";
    cout<<"\n\t\t\t\t\t       [1]: VOTE";
    cout<<"\n\t\t\t\t\t       [2]: DISPLAY CANDIDATES";
    cout<<"\n\t\t\t\t\t       [3]: BACK ";
    cout<<"\n\t\t\t\t\t---------------------------------------";
    cout<<"\n\n\t\t\t\t\tPlease Select only from 1-3: ";
    cin>>opt;
    return (opt);
}
int admMenu() {
    system("cls");
    int opt;
    cout<<"\n\t\t\t\t\t      \xdb\xdb\xdb\xdb|ADMINISTRATOR SYSTEM MENU|\xdb\xdb\xdb\xdb";
    cout<<"\n\t\t\t\t\t---------------------------------------";
    cout<<"\n\t\t\t\t\t       [1]: DISPLAY ALL REGISTERED VOTERS";
    cout<<"\n\t\t\t\t\t       [2]: DISPLAY CANDIDATES AND RESULT";
    cout<<"\n\t\t\t\t\t       [3]: ADD CANDIDATE ";
    cout<<"\n\t\t\t\t\t       [4]: DELETE CANDIDATE ";
    cout<<"\n\t\t\t\t\t       [5]: BACK ";
    cout<<"\n\t\t\t\t\t---------------------------------------";
    cout<<"\n\n\t\t\t\t\tPlease Select only from 1-5: ";
    cin>>opt;
    return (opt);
}
int myRec::editMenu() {
    int opt;
    cout<<"\n\t\t\t\t\t       [1]: EDIT NAME";
    cout<<"\n\t\t\t\t\t       [2]: EDIT GENDER";
    cout<<"\n\t\t\t\t\t       [3]: EDIT AGE ";
    cout<<"\n\t\t\t\t\t       [4]: EDIT PASSWORD ";
    cout<<"\n\t\t\t\t\t       [5]: DELETE ACCOUNT ";
    cout<<"\n\t\t\t\t\t       [6]: BACK ";
    cout<<"\n\t\t\t\t\t---------------------------------------";
    cout<<"\n\n\t\t\t\t\tPlease Select only from 1-5: ";
    cin>>opt;
    return (opt);
}

int IDGen(){ // function for id generator
    //local declarations
    int ID;
    int lower = 100000;
    int higher = 999999;

    srand(time(NULL));

    ID = (rand() % (higher - lower + 1)) + lower;
    return (ID);
}

void myRec::moduleOne(){
       REC p;
       USB u;
       int id, number;
       while(1){
            switch(regMenu()){
                case 1:
                    if(usbEmpty()){
                        cout<<"\n\t\t\t\tREGISTER IN REGISTRATION MENU OPTION 2 'NOT REGISTERED'\n\n\t\t\t\t\t";
                        system("pause");
                    }else{
                        cout<<"\t\t\t\t\t\tENTER ID NUMBER: ";
                        cin>>number;
                        locateidnum(number);
                    }
                    break;
                case 2:
                    if(usbEmpty()){
                        system("cls");
                        id=IDGen();
                        cout<<"\t\tINSTRUCTIONS\n\n";
                        cout<<"\t\tthe 'bb' stands for backspace in inserting a pin\n";
                        cout<<"\t\texample: 12345 is inserted, if 2 is wrong the display will be **bb**** "<<"\n\n"<<endl;
                        p.idNum=id;
                        u.usbID = p.idNum;
                        cout<<"\t\tYour ID NUMBER is: "<<p.idNum<<endl;

                        cout<<"\t\tInput your last name: ";
                        cin>>p.lastName;
                        u.usbLast = p.lastName;
                        cout <<"\t\tInput your first name: ";
                        cin>>p.firstName;
                        u.usbFirst = p.firstName;
                        if(duplicate(p.lastName, p.firstName)==true){
                            cout<<"\n\t\tID already used\n\t\t";
                            system("pause");
                            break;
                        }
                        cout<<"\t\tInput your age: ";
                        cin>>p.age;
                        u.usbAge = p.age;
                        while(p.gender!="m"&&p.gender!="f"){
                            cout<<"\t\tEnter gender[m/f]: ";
                            cin>>p.gender;
                        }
                        u.usbGender = p.gender;
                        cout<<"\n\t\tInput password up to 50 characters:\n"; //getting the password
                        cout<<"\t\tPress enter to stop inputing password\n";
                        cout<<"\t\tEnter password: ";
                        p.pw = pin();
                        u.usbPw = p.pw;
                        add(&p);
                        addFlash(&u);
                        system("cls");
                        cout<<"\n\t\tPLEASE REMEMBER YOUR ID NUMBER AND PASSWORD FOR YOU TO VOTE\n"<<endl;
                        cout<<"\t\tID NUMBER: "<<p.idNum<<endl;
                        cout<<"\t\tLAST NAME: "<<p.lastName<<endl;
                        cout<<"\t\tFIRST NAME: "<<p.firstName<<endl;
                        cout<<"\t\tPASSWORD: "<<p.pw<<endl;
                        cout<<"\n\t\tAGAIN PLEASE REMEMBER YOUR ID NUMBER AND PASSWORD FOR YOU TO VOTE\n\t\t";
                        system("pause");
                    }else{
                        cout<<"\n\t\t\t\t\tYOU ALREADY REGISTERED\n\n\t\t\t\t\t";
                        system("pause");

                    }

                    break;
                case 3:
                    return;
                    break;
                default:
                    cout <<"\n\t\t\t\t\tNUMBER NOT FOUND! Please pick from 1-3 only!";
                    getch();
            }


       }
}

void myRec::moduleTwo(){
    REC y;
    while(1){
        switch(voteMenu()){
            case 1:
                if(usbEmpty()){
                    cout<<"\n\t\t\t\tREGISTER IN REGISTRATION MENU OPTION 2 'NOT REGISTERED'\n\n\t\t\t\t\t";
                    system("pause");
                }else{
                    cout<<"\n\n\t\t\t\t\t\tENTER YOUR ID NUMBER: ";
                    cin>>y.idNum;
                    locate(y.idNum);
                    savecand();
                }

                break;
            case 2:
                dispCand();
                getch();
                break;
            case 3:
                donesave();
                return;
                break;
            default:
                cout <<"\n\t\t\t\t\tNUMBER NOT FOUND! Please pick from 1-3 only!";
                getch();
        }
    }
}

void myRec::moduleThree(){
    system("cls");
    printf("\n\t\t\t\tusername: SIR\n\t\t\t\tpassword: POGI\n\n\t\t\t\tshowing the username and password for project purposes \n\t\t\t\tto access and fully understand our project.\n\n");
    //local declaration
    CAND p;
    int i, id, candNum;
    string username;
	string password;
	cout<<"\n\t\t\t\tEnter the username: ";//entering the username of the administrator
	cin>>username;

	cout<<"\n\t\t\t\tEnter the password: ";//entering the password of the administrator
	cin>>password;

	if(username == "SIR"){

		//username verification sucessful
		//next step is to verify the password
		if(password == "POGI"){
			//password verification also successful
			cout<<"\n\t\t\t\tUser successfully logged in...\n";
			cout<<"\n\t\t\t\t-----------------------------\n\t\t\t\t";
			system("pause");
            while(1){
                    switch(admMenu()){
                        case 1:
                            dispStud();
                            cout<<"\t\t\t\t\t";
                            system("pause");
                            break;
                        case 2:
                            dispCand();
                            getch();
                            break;
                        case 3:
                            dispCand();
                            cout<<"\n\n\t\t\t\tENTER FIRST NAME: ";
                            cin>> p.candFirst;
                            cout<<"\n\t\t\t\t\tENTER LAST NAME: ";
                            cin>>p.candLast;
                            p.tally = 0;
                            addCand(&p);
                            savecand();
                            makenullCand();
                            retcand();
                            cout<<"\n\t\t\t\t\t";
                            system("pause");
                            break;
                        case 4:
                            dispCandtwo();
                            cout<<"\n\t\t\t\tENTER THE NUMBER OF THE CANDIDATE YOU WANT TO DELETE: ";
                            cin>>candNum;
                            delCand(candNum);
                            savecand();
                            makenullCand();
                            retcand();
                            getch();
                            break;
                        case 5:
                            return;
                            break;
                        default:
                            cout <<"\n\t\t\t\t\tNUMBER NOT FOUND! Please pick from 1-6 only!";
                            getch();
                    }

            }

		}else{
            cout<<"\nPassword entered is invalid";
		}
		}else{
            cout<<"\nUsername entered is invalid";


		}
getch();
		}



int main(){
    int id, opt;
    CAND v;
    myRec L;
    L.makenull();
    L.makenullCand();
    L.makenullDone();
    L.makenullUsb();
    L.retrieve();
    L.retcand();
    L.doneretrieve();
    L.retflash();
    while(1){
       switch(menu()){
            case 1:
                L.moduleOne();
                break;
            case 2:
                L.moduleTwo();
                break;
            case 3:
                L.moduleThree();
                break;
            case 4:
                system("cls");
                L.save();
                L.saveflash();
                cout <<"\n\n\n\n\n\t\t\t\t\tTHANK YOU FOR USING THE PROGRAM";
                cout<<"\n\n\t\t\t\t\tCREATED BY: CASIMSIMAN , JERALD";
                cout<<"\n\n\t\t\t\t\t\tBS CS 2-B-M\n\n\n\n\n";
                exit(0);
            default:
                cout <<"\n\t\t\t\t\tNUMBER NOT FOUND! Please pick from 1-4 only!";
                getch();

       }

    }
}
