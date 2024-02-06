/*BS CS 2 - B - M
CASIMSIMAN, JERALD
VALLOYAS, JON REXZEL

STUDENT ELECTION SYSTEM
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define MAX 100
#define MIN 1

typedef struct voter{// structure for the voters
    int idNum;
    int age;
    char Fname[31];
    char Lname[31];
    char gender[2];
    char pw[51];
}REC;
typedef struct usb{// structure for the voter in flashdrive
    int  ID;
    int edad;
    char firstN[31];
    char lastN[31];
    char sex[2];
    char pincode[51];
}USB;
typedef struct candidates{//structure for the candidates
    char candsF[31];
    char candsL[31];
    int tally;
}RECS;
typedef struct done{ // structure for those who are done voting
    char Fn[31];
    char Ln[31];
}VOTES;

typedef struct list{// structure to access all the structures above
    REC stud[MAX];
    USB u[MIN];
    VOTES v[MAX];
    RECS cans[MAX];
    int last;
    int p;
    int ends;
    int t;
} LIST;

LIST L;
//MODULE ONE
void moduleONE(); // for switch case in module one
void insert(int id, char Fn[31],char Ln[31], char a[51], char gend[2], int ag); //for inserting voters
void retflash();//retrieving data in flash drive
void saveflash();//saving inputted data in flash drive
char pass[51];//global declaration for inputting pin
char *pin();//function for storing the pin
void makenull();//to make null the value of L.last
void know(int x);//to know if the id number is registered or not
int loc(int x); //funtion that locates the id number
int IDGen(); // id number generator
char locate(char n[31]); // locate the first name of the voter
char Llocate(char n[31]);// locate the last name of the voter
int isfull();// function to know if the list of voters is full
int isempty();
//MODULE TWO
void moduleTWO(); //for switch case in module two
void locid(int x);//accessing the voters account to vote
void display(); //for displaying candidates
void candvote(int x);
void candidate(char c[31], char d[31]);//locating the candidate who the voters vote to add the vote count
int ispack();// function to know if the list of candidates is full
int isfree();// function to know if the list of cadidates is empty
//menus
int menu();// menu for the switch case in the main menu
int regMenu();// menu for the switch case in module 1
int voteMenu(); // mene for the switch case in module 2
int admMenu(); // menu for switch case in Administrator
//done voting
void retvote(); // retrieving all the list of those who are done voting
void savevote();// saving the name of those who are done voting
void makezero(); // making the function of L.v zero
char locvote(char c[31]); // locating the first name of the voters who are done voting
char Llocvote(char c[31]); // locating the last name of the voters who are done voting
//flash drive
void makenone(); // make the value of L.u zero
int isclear(); // to know if the function is not full in flash drive
int isnot(); //to know if the function is full in flash drive
//admin
void admin();
void displaycans();
void add(char c[31], char d[31]); //for adding candidates
void voteadd(int x);// the vote count that scanned in the file will go to this function to store
void retrieve(); //retrieving data for the general file for voters
void save();//saving the inputted data for voters
void disp(); //displaying all inputted datas of all the voters
void makevoid();// make the value of L.ends null
void retcand();//retrieving the the content from the file candidate.dbf
void retcandtwo();
void savecand();// saving the names and vote counts of the candidates
char track(char c[31]);// to track  if there are duplicate records found in Firs name of the candidates
char Ttrack(char c[31]);// to track if there are duplicate records found in Last name of the candidates


int main() {
    //local declaration
    int option;
    char passw[7];
    char n[31];
    char c[31];
    //calling all the functions to make zeros and retrieving all the datas
    makenull();
    makevoid();
    makezero();
    makenone();
    retrieve();
    retcand();
    retvote();
    retflash();
    while(1) {
        option = menu();
        switch(option) {
        case 1:
            moduleONE(); // go to the function moduleONE
            break;
        case 2:
            moduleTWO();// go to the function moduleTWO
            break;
        case 3:
            admin();// go to the function admin
            break;
        case 4: //exit the program
            printf("\n\t\t\t\t\tTHANK YOU FOR USING THE PROGRAM");
            exit(0);
            break;
            default:
                printf("\n\t\t\t\t\tNUMBER NOT FOUND! Please pick from 1-4 only!");
                getch();
        }
        }

    return 0;
}

void moduleONE(){
    //local declarations
    int regOpt;
    int id, edad;
    char Fn[31], Ln[31], p[51], gen[2];
    int a;
while(1){
            regOpt = regMenu(); // passes the value in regMenu option
            switch(regOpt){
            case 1: // to know if the id number is registered or not
                system("cls");
                if(isclear()){
                    printf("\t\t\tYour are not registered yet.");
                    printf("\n\t\t\tGo to module 1 option 2 to register\n\t\t\t");
                    system("pause");
                }else{
                printf("\nInput id number to display details: ");
                scanf("%d", &id);
                if(id!=L.u[L.t].ID){
                    printf("wrong id number");
                }else{
                    know(id);
                }
                }
                getch();
                break;
            case 2:// registering the voters
                system("cls");
                printf("\t\tINSTRUCTIONS\n\n");
                printf("\t\tthe 'bb' stands for backspace in inserting a pin\n");
                printf("\t\texample: 12345 is inserted, if 2 is wrong the display will be **bb**** ");
                if(isnot()){ // calling the function to know if the flash drive is registered by the voters
                    printf("\n\nYou already registered\n");
                    system("pause");
                }else{// getting all the informations of the voters
                printf("\n\n\t\tInput First Name:");//getting the first name
                scanf(" %[^\n]s", Fn);//scanning
                printf("\n\t\tInput Last Name:");//getting the last name
                scanf(" %[^\n]s", Ln);//scanning
                printf("\n\t\tEnter gender[m/f]: ");
                scanf("%s", gen);
                printf("\n\t\tEnter age: ");
                scanf("%d", &edad);
                printf("\n\t\tInput password up to 50 characters:\n");//getting the password
                printf("\t\tPress enter to stop inputing password\n");
                printf("\t\tEnter password: ");
                strcpy(p,pin());
                printf("\n\n\t\t");
                while(a>=0){// if the id number had the same else generate another id number
                    id=IDGen();// id generator
                    a=loc(id); // to know if the number generator has a duplicate record
                }
                insert(id,Fn,Ln,p,gen,edad); // passes the value of all the informations inputted
                }
                getch();
                save(); // saving the information in general information
                saveflash(); // saving the information in flash drive
                break;
            case 3: // return to the main function
                system("cls");
                fflush(stdin);
                return;
                break;
            }
            }



}
void moduleTWO(){ // function moduleTWO
//local declaration
int voteOpt, id ;
while(1){
            voteOpt = voteMenu();//passes the value in function voteMenu
            switch (voteOpt) {
            case 1:// voting candidate
                system("cls");
                if(isclear()){
                    printf("Your are not registered yet.");
                    printf("\nGo to module 1 option 2 to register\n");
                    system("pause");
                }else{
                printf("\nInput id number to vote:\n");//input the id number
                scanf("%d", &id);
                if(id!=L.u[L.t].ID){// if id is not the id of the flash drive wrong password
                    printf("Wrong ID number\n");
                    system("pause");
                }else{//if true go to the locid function
                    locid(id);
                }
                }
                savecand();//saving the vote count
                savevote();//saving people who done voting
                break;
            case 2:
                display();
                getch();
                break; //display case function
            case 3:
                system("cls");
                fflush(stdin);
                return;
                break;
            }
            }



}

void know (int x){//function for case 1 module 1
char pwrd[51];
int p, pas;
if (isempty()){
    printf("List is empty.");
    getch();
    }
else{
    p= loc(x); //value of locate function
    if (p<0){
        printf("Not found.");
        }
    else {
        printf("FOUND\n");
            printf("Enter Pincode: ");
            strcpy(pwrd,pin());//inputting the pin code
            pas=strcmp(pwrd,L.stud[p].pw);//comparing the password inputted in the password saved in the file
            if(pas==0){//if the password is correct then proceed in voting
                printf("\n\nYour ID number is: %d\nYour name is: %s %s\nGender: %s\nAge: %d\npincode is: %s", L.u[L.t].ID, L.u[L.t].firstN,L.u[L.t].lastN, L.u[L.t].sex, L.u[L.t].edad, L.stud[L.last].pw);
                getch();
    }else{
        printf("wrong password");
    }

}
}
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
int loc(int x){//function to locate id number
for(int i=0;i<=L.last;i++){//loop untile it finds the idnumber
    if ( L.stud[i].idNum==x)//comparing all the id number in the value of x(id number inputter)
        return (i);// return the value of i if it is located
    }
return(-1);//else return -1
}
                                                                    //CASE 1-2
                                                                    //CASE 1-2
                                                                    //CASE 1-2
void insert(int id, char Fn[31], char Ln[31], char a[7], char gend[2], int ag){//function to insert all the details the voters inputted
int i, p;
    if (isfull()){                                                  //informs the user if the list is already full
        printf("List is full\n");
        getch();
    }else{
        i=locate(Fn); //locating the first name if there is a same first name
        p=Llocate(Ln); //locating the last name if there is a same last name
      if(i>=0&&p>=0){ //if both of the located the same first and last name it is a duplicate record
          printf("\nDuplicate Record Found.\n");
          printf("Press any key to continue");
      }else{//else storing the inputted data on the array of structures(VOTERS)
        L.last++; //increment
        strcpy(L.stud[L.last].Fname, Fn);
        strcpy(L.stud[L.last].Lname, Ln);
        strcpy(L.stud[L.last].pw,a);
        strcpy(L.stud[L.last].gender, gend);
        L.stud[L.last].age = ag;
        L.stud[L.last].idNum = id;

        printf("\nYour ID number is: %d\nYour name is: %s %s\nGender: %s\nAge: %d\npincode is: %s", L.stud[L.last].idNum, L.stud[L.last].Fname, L.stud[L.last].Lname, L.stud[L.last].gender,L.stud[L.last].age, L.stud[L.last].pw);
        printf("\n\nTHANK YOU. You are now a registered voter :)\n");
            //stoing also in array of structure in (USB)
            L.t++;//increment
            strcpy(L.u[L.t].firstN, Fn);
            strcpy(L.u[L.t].lastN, Ln);
            strcpy(L.u[L.t].pincode,a);
            strcpy(L.u[L.t].sex,gend);
            L.u[L.t].ID =id;
            L.u[L.t].edad =ag;
            system("pause");
        }
    }
}

char locate(char n[31]){ // function to locate the first name of the registering voter
    for(int i=0;i<=L.last;i++){//loop
        if(strcmp(L.stud[i].Fname,n)==0)//comparing if the same name it is equals to 0 then the loop will stop
            return(i);//returning the value of i
        }return(-1); //else return -1
}
char Llocate(char n[31]){// function to locate the last name of the registering voter
    for(int i=0;i<=L.last;i++){//loop
        if(strcmp(L.stud[i].Lname,n)==0)//comparing if the same name it is equals to 0 then the loop will stop
            return(i);//returning the value of i
        }return(-1);//else return -1
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

                                                                                                                                                                                                        //CASE 2-1
                                                                                                    //CASE 1-3
                                                                                                    //CASE 1-3
void disp(){ //displaying all the list of registered voters for
    system ("cls");
    printf("\tID Number\t|\tName\t|\tGender\t|\tAge\t|\tPassword\t|\tremarks\n");
    for(int i=0;i<=L.last;i++){
        printf("\t %d \t\t%s %s        %s\t\t  %d\t\t%s\t\t\t", L.stud[i].idNum,L.stud[i].Fname, L.stud[i].Lname, L.stud[i].gender, L.stud[i].age, L.stud[i].pw);

        if(locvote(L.stud[i].Fname)>=0&&Llocvote(L.stud[i].Lname)>=0){//condition if the voter voted or not
                    printf("voted\n");
        }else{
            printf("not voted\n");

        }
}
        getch();

}

                                                                                                    //CASE 2-1
                                                                                                    //CASE 2-1
                                                                                                    //CASE 2-1
void locid(int x){// functions for voting candidates
//local declaration
char Fn[31];
char Ln[31];
char c[31];
char d[31];
char pwrd[7];
int p, result, Lresult, pas,a,b;
if (isempty()){//checking if the list is empty or not
    system("pause");
    }
else{
    p= loc(x);//locating the id number inputted by the user
    if (p<0){//checking if not found
        printf("Cannot found.");
        system("pause");
        }
    else {//if not true then proceed to entering the name
        printf("FOUND\n");
        printf("Enter  First name:");
        scanf("%s", Fn);
        printf("Enter  Last name:");
        scanf("%s", Ln);
        result = strcmp(L.stud[p].Fname,Fn);
        Lresult = strcmp(L.stud[p].Lname,Ln);
        if(result==0&&Lresult==0){//if true proceed inputting the password
            printf("Enter Pincode: ");
            strcpy(pwrd,pin());//inputting the pin code
            pas=strcmp(pwrd,L.stud[p].pw);//comparing the password inputted in the password saved in the file
            if(pas==0){//if the password is correct then proceed in voting
                locvote(Fn);//locating the first name
                Llocvote(Ln);//locating the last name
                if(locvote(Fn)>=0&&Llocvote(Ln)>=0){//comparing if the they voted or not
                    printf("\nyou voted\n");
                    system("pause");
                }else{//if not voted then log in
                printf("\nyou are now log in\n");
                getch();
                system("cls");
                display();//displaying the candidates
                printf("Enter number of the candidate you want to vote:");
                scanf("%d", &a);
                candvote(a);
                L.p++;
                strcpy(L.v[L.p].Fn,L.stud[p].Fname);//copying the first name in structure VOTERS to structure DONE
                strcpy(L.v[L.p].Ln,L.stud[p].Lname);//copying the last name in structure VOTERS to structure DONE
                printf("THANK YOU FOR VOTING\n");
                system("pause");
            }
            }else{
                printf("\nwrong password\n");
                system("pause");
        }}else{
            printf("\nwrong credentials\n");
            system("pause");
            }
        }
    }
    }


char locvote(char c[31]){//function to locate the first name in structure DONE
    for(int i=0;i<=L.p;i++){//loop to find the first name
        if(strcmp(L.v[i].Fn,c)==0)
            return(i);
        }return(-1);
}
char Llocvote(char c[31]){//function to locate the last name in structure DONE
    for(int i=0;i<=L.p;i++){//loop to find the last name
        if(strcmp(L.v[i].Ln,c)==0)
            return(i);
        }return(-1);


}
void candvote(int x){
int i;
i=x-1;
L.cans[i].tally=L.cans[i].tally+1;

}
void voteadd(int x){//function where the vote counts in the file stored
    L.cans[L.ends].tally = x;
}

                                                                                                    //CASE 2-2
                                                                                                    //CASE 2-2
                                                                                                    //CASE 2-2


void display() // display function
{
    if(isfree())
    {
        printf("List is empty!\n");
        printf("Exit to the program in order to have candidates");
        printf("Press any key to go back to Menu\n");
        getch();
    }
    else
    {
    int i;
    system("cls");
    printf("\n    NAME OF CANDIDATES\n");
        for(i=0;i<=L.ends;i++) //loop for displaying the values of the structure array variables as well as computing individual average
        {
        printf("%d.) %s %s\n",i+1,L.cans[i].candsF, L.cans[i].candsL); //display all the list of the candidates
        }
    }
}



                                                                                                    //CASE 2-3
                                                                                                    //CASE 2-3
                                                                                                    //CASE 2-3

void add(char c[31],  char d[31]) //function for adding another candidate
{
  int i,p;
  if (ispack()) //informs the user if the list is already full
  {
    printf("List is full");
    getch();

    }else{
      if(track(c)>=0&&Ttrack(d)>=0){//locating if value of first and last name if existed then duplicate record founded
          printf("\nDuplicate Record Found.\n");
          system("pause");
      }else{//if not exist storing the added candidate
        L.ends++;
        strcpy(L.cans[L.ends].candsF, c);
        strcpy(L.cans[L.ends].candsL, d);
    }
}
}

char track(char c[31]){//locating the first name of the candidate then comparing
    for(int i=0;i<=L.ends;i++){//loop untile it finds the first name of the candidate
        if(strcmp(L.cans[i].candsF,c)==0)
            return(i);
        }return(-1);
}

char Ttrack(char c[31]){//locating the last name of the candidate then comparing
    for(int i=0;i<=L.ends;i++){//loop untile it finds the last name of the candidate
        if(strcmp(L.cans[i].candsL, c)==0)
            return(i);
        }return(-1);
}

                                                                                                    //ADMINISTRATOR
                                                                                                    //ADMINISTRATOR
                                                                                                    //ADMINISTRATOR
void admin(){//function for the administrator switch case
    system("cls");
    printf("\n\t\t\t\tusername: SIR\n\t\t\t\tpassword: POGI\n\n\t\t\t\tshowing the username and password for project purposes \n\t\t\t\tto access and fully understand our project.\n\n");
    //local declaration
    int i, admOpt;
    char username[15];
	char password[12];
	char Fn[31];
	char Ln[31];
	printf("\n\t\t\t\tEnter the username: ");//entering the username of the administrator
	scanf("%s",&username);

	printf("\n\t\t\t\tEnter the password: ");//entering the password of the administrator
	scanf("%s",&password);

	if(strcmp(username, "SIR") == 0)
              {
		//username verification sucessful
		//next step is to verify the password
		if(strcmp(password, "POGI") == 0)
                            {
			//password verification also successful
			printf("\n\t\t\t\tUser successfully logged in...\n");
			printf("\n\t\t\t\t-----------------------------\n\t\t\t\t");
			system("pause");
			while(1){
                    admOpt=admMenu();//passes the value in the admMENU
                    switch(admOpt){
                case 1:
                    disp();//displaying all the information of the registered votes
                    getch();
                    break;
                case 2:
                    displaycans();//displaying the candidates and vote counts
                    getch();
                    break;
                case 3://case for adding candidates
                    system("cls");
                    printf("\nEnter Candidate's Name\n");
                    printf("First Name: "); //Print the Name of the students
                    scanf("%s", Fn); //Scan student's name
                    printf("Last Name:");
                    scanf("%s", Ln);
                    add(Fn, Ln); //converts the local variables to structure array variables
                    L.cans[L.ends].tally = 0;
                    savecand();
                    getch();
                    break;
                case 4://exiting from the switch case
                    system("cls");
                    fflush(stdin);
                    return;
                    break;
                    }



			}
		}else
		{
			//invalid password. Report it
			printf("\nPassword entered is invalid");
		}
	}else
                            {
		//invalid username. Report it
		printf("\nUsername entered is invalid");
                            }
	getch();
}
void displaycans(){//function on displaying candidates and their vote counts
    if(isfree())
    {// to know if the list is empty or not
        printf("List is empty!\n");
        printf("Press any key to go back to Menu\n");
        getch();
    }
    else
    {
    int i;
    system("cls");
    printf("\n    NAME OF CANDIDATES\n");
        for(i=0;i<=L.ends;i++) //loop for displaying the values of the structure array variables as well as computing individual average
        {
        printf("%d.) %s %s: %d\n",i+1,L.cans[i].candsF,L.cans[i].candsL ,L.cans[i].tally); //Display the value of an integer variable and will answer if the conditional statement inside is either paspassed or failed
        }
    }


}

                                                                                                    //ALL MENUS
                                                                                                    //ALL MENUS
                                                                                                    //ALL MENUS
int menu() {
    system("cls");
    system("color a");
    printf("\n\n\n\t\t\t\t--------------------------------------------------------");
    printf("\n\n\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb|WELCOME TO OUR PROJECT|\xdb\xdb\xdb\xdb\xdb");
    printf("\n\n\t\t\t\t\t   Student Election Voting System ");
    printf("\n\n\t\t\t\t--------------------------------------------------------");
    printf("\n\t\t\t\t\tCREATOR: rexzelol123");
    int opt;
    printf("\n\n\n\t\t\t\t\t---------------------------------------");
    printf("\n\t\t\t\t\t\t\t|MENU|");
    printf("\n\t\t\t\t\t---------------------------------------");
    printf("\n\t\t\t\t\tModule [1]: REGISTRATION");
    printf("\n\t\t\t\t\tModule [2]: VOTING SYSTEM");
    printf("\n\t\t\t\t\t       [3]: FOR ADMINISTRATOR ONLY");
    printf("\n\t\t\t\t\t       [4]: EXIT ");
    printf("\n\t\t\t\t\t---------------------------------------");
    printf("\n\n\t\t\t\t\tPlease Select only from 1-4: ");
    scanf("%d", &opt);
    return (opt);
}

int regMenu() {
    system("cls");
    int opt;
    printf("\n\t\t\t\t\t      \xdb\xdb\xdb\xdb|REGISTRATION MENU|\xdb\xdb\xdb\xdb");
    printf("\n\t\t\t\t\t---------------------------------------");
    printf("\n\t\t\t\t\t       [1]: FOR REGISTERED VOTER TO DISPLAY DETAIL");
    printf("\n\t\t\t\t\t       [2]: NOT REGISTERED");
    printf("\n\t\t\t\t\t       [3]: BACK ");
    printf("\n\t\t\t\t\t---------------------------------------");
    printf("\n\n\t\t\t\t\tPlease Select only from 1-4: ");
    scanf("%d", &opt);
    return (opt);
}

int voteMenu() {
    system("cls");
    int opt;
    printf("\n\t\t\t\t\t      \xdb\xdb\xdb\xdb|VOTING SYSTEM MENU|\xdb\xdb\xdb\xdb");
    printf("\n\t\t\t\t\t---------------------------------------");
    printf("\n\t\t\t\t\t       [1]: VOTE");
    printf("\n\t\t\t\t\t       [2]: DISPLAY CANDIDATES");
    printf("\n\t\t\t\t\t       [3]: BACK ");
    printf("\n\t\t\t\t\t---------------------------------------");
    printf("\n\n\t\t\t\t\tPlease Select only from 1-3: ");
    scanf("%d", &opt);
    return (opt);
}
int admMenu() {
    system("cls");
    int opt;
    printf("\n\t\t\t\t\t      \xdb\xdb\xdb\xdb|VOTING SYSTEM MENU|\xdb\xdb\xdb\xdb");
    printf("\n\t\t\t\t\t---------------------------------------");
    printf("\n\t\t\t\t\t       [1]: DISPLAY ALL REGISTERED VOTERS");
    printf("\n\t\t\t\t\t       [2]: DISPLAY CANDIDATES AND RESULT");
    printf("\n\t\t\t\t\t       [3]: ADD CANDIDATE ");
    printf("\n\t\t\t\t\t       [4]: BACK ");
    printf("\n\t\t\t\t\t---------------------------------------");
    printf("\n\n\t\t\t\t\tPlease Select only from 1-4: ");
    scanf("%d", &opt);
    return (opt);
}
                                                                            //ALL FILES SAVING AND RETRIEVAL
                                                                            //ALL FILES SAVING AND RETRIEVAL
                                                                            //ALL FILES SAVING AND RETRIEVAL
void save(){//saving file to for the registered voter
    FILE *fp;
    int i;
    fp = fopen("voterx.dbf", "w+");
    for (i=0;i<=L.last;i++){
        fprintf(fp,"%d %s %s %s %d %s\n", L.stud[i].idNum, L.stud[i].Fname, L.stud[i].Lname, L.stud[i].gender, L.stud[i].age, L.stud[i].pw);
    }
    fclose(fp);
}
void retrieve(){//retrieving file for all registered voter
    FILE *fp;
    if((fp = fopen("voterx.dbf", "r")) !=NULL){ //if file does not exist, creates a new file for storing and retrieving data
        for (int i=0; i<MAX; i++){
            if(feof(fp)){
                break;
            }
            fscanf(fp,"%d %s %s %s %d %s\n",&L.stud[i].idNum, L.stud[i].Fname, L.stud[i].Lname, L.stud[i].gender, &L.stud[i].age,  L.stud[i].pw);
                if(strcmp(L.stud[i].Fname, "")!=0&&strcmp(L.stud[i].Lname, "")!=0)
            {
                L.last++;
            }
        }
    }else
    {
        fp=fopen("voterx.dbf", "w+");
    }

    fclose(fp);
}
void saveflash(){//saving the file in the flash drive
    FILE *fp;
    int i;
    fp = fopen("e:\\flashvote.dbf", "w+");
    for (i=0;i<=L.t;i++){
        fprintf(fp,"%d %s %s %s %d %s\n", L.u[i].ID, L.u[i].firstN, L.u[i].lastN,L.u[i].sex, L.u[i].edad, L.u[i].pincode);
    }
    fclose(fp);
}
void retflash(){//retrieving the file in the flash drive

   FILE *fp;
   do{
    if((fp = fopen("e:\\flashvote.dbf", "r"))==NULL){
    system("cls");
    system("color a");
    printf("Insert Card\n");
    system("pause");
   }else{
        system("cls");
        system("color a");
        printf("Card Inserted\n");
        system("pause");
        if((fp = fopen("e:\\flashvote.dbf", "r")) !=NULL){ //if file does not exist, creates a new file for storing and retrieving data
        for (int i=0; i<MAX; i++){
            if(feof(fp)){
                break;
            }
            fscanf(fp,"%d %s %s %s %d %s\n",&L.u[i].ID, L.u[i].firstN, L.u[i].lastN, L.u[i].sex, &L.u[i].edad, L.u[i].pincode);
                if(strcmp(L.u[i].firstN, "")!=0&&strcmp(L.u[i].lastN,"")!=0)
            {
                L.t++;
            }
        }
    }else{
        fp=fopen("e:\\flashvote.dbf", "w+");
        }
   }
   }while((fp = fopen("e:\\flashvote.dbf", "a"))==NULL);

}
void savecand(){//saving the candidate
    FILE *fp;
    int i;
    fp = fopen("candidatex.dbf", "w+");
    for (i=0;i<=L.ends;i++){
        fprintf(fp,"%s %s %d\n",L.cans[i].candsF,L.cans[i].candsL, L.cans[i].tally);
    }
    fclose(fp);
}
void retcand(){//retrieving the list of candidate
    FILE *fp;

    char Fn[31];
    char Ln[31];
    int numvote;
    if((fp = fopen("candidatex.dbf", "r")) ==NULL){//if file does not exist, creates a new file for storing and retrieving data
        fp=fopen("candidatex.dbf", "w+");
        fprintf(fp, "leni robredo 0\nbongbong marcos 0\nmanny pacquiao 0\nisko moreno 0\n");
        fclose(fp);
        retcandtwo();
    }else{
        while(!feof(fp)){
            fscanf(fp,"%s %s %d\n",Fn, Ln, &numvote);
            add(Fn, Ln);
            voteadd(numvote);
        }
    }
    fclose(fp);
}
void retcandtwo(){
    FILE *fp;

    char Fn[31];
    char Ln[31];
    int numvote;
fp = fopen("candidatex.dbf", "r");
        while(!feof(fp)){
            fscanf(fp,"%s %s %d\n",Fn, Ln, &numvote);
            add(Fn, Ln);
            voteadd(numvote);
}
fclose(fp);
}
void retvote(){
    FILE *fp;
    if((fp = fopen("done.dbf", "r")) !=NULL){ //if file does not exist, creates a new file for storing and retrieving data
        for (int i=0; i<MAX; i++){
            if(feof(fp)){
                break;
            }
            fscanf(fp,"%s %s\n",L.v[i].Fn,L.v[i].Ln );
                if(strcmp(L.v[i].Fn, "")!=0&&strcmp(L.v[i].Ln,"")!=0)
            {
                L.p++;
            }
        }
    }
    fclose(fp);
}
void savevote(){
    FILE *fp;
    int i;
    fp = fopen("done.dbf", "w+");
    for(i=0;i<=L.p;i++){
        fprintf(fp,"%s %s\n",L.v[i].Fn, L.v[i].Ln);
    }
    fclose(fp);
}


                                                                        //OTHERS
                                                                        //OTHERS
                                                                        //OTHERS
void makenull(){
    L.last = -1;
}
void makevoid(){
    L.ends = -1;
}
void makezero(){
    L.p = -1;
}
void makenone(){
    L.t=-1;
}
int isfull(){
    return(L.last==MAX-1);
}

int isempty(){
return(L.last==-1);
}

int ispack(){
    return(L.ends==MAX-1);
}
int isfree(){
return(L.ends==-1);
}

int isclear(){

return(L.t==-1);
}

int isnot(){

return(L.t==MIN-1);
}
