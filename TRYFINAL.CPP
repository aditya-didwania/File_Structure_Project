#include<iostream.h>
#include<dos.h>
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<iomanip.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define datafile "60.txt"
#define indexfile "61.txt"
#define sindexfile "62.txt"

fstream dfile,ifile,sifile,infile;
int i,indsize,sindsize,year1,count=0;
char buffer[100],skey[20],headbuf[11];
char count_copy[3];
char year2[5];
int j,li,lp,rec,valid;

int ch,flag;


int isAlpha(char ch)
{
	if(isalpha(ch))
		return 1;
	else
		return 0;
}


int checkName(char *Name)
{
	int valid=1,i;
	for(i=0;i<strlen(Name);i++)
	if(!(isalpha(Name[i])||(Name[i]==' ')))
	{
		valid=0;
		break;
	 }
	 return(valid);

}

/*int checkreg(char *reg)//check if urn is valid
{
	if(((strlen(reg)==7)&&isdigit(reg[0]))&&(isdigit(reg[1]))&&(isdigit(reg[2]))&&(isdigit(reg[3]))&&(isdigit(reg[5]))&&(isdigit(reg[6]))&&(reg[4]=='-'))
		return 1;
	else
		return 0;
}*/

void Get_Fees(char *fee1,char *c)
{
	int i,fe;
	i=atoi(c);
	switch(i)
	{
		case 1:
			fe= 1050;
			break;
		case 2:
			fe= 1250;
			break;
		case 3:
			fe= 1450;
			break;
		case 4:
			fe= 1650;
			break;
		case 5:
			fe= 1850;
			break;
		case 6:
			fe= 2050;
			break;
		case 7:
			fe= 2250;
			break;
		case 8:
			fe= 2450;
			break;
		case 9:
			fe= 2650;
			break;
		case 10:
			fe= 2850;
			break;
		case 11:
			fe= 3050;
			break;
		case 12:
			fe= 3250;
			break;
	}
	itoa(fe,fee1,10);
}



//function to open
void opener(fstream &file, char *fn,int mode)
{
	file.open(fn,mode);
	if(!file)
	{
		cout<<"Some Technical error.Unable To Open the file";
		getch();
		exit(1);
	}
}
class student
{
	char dusn[10],name[20],fees[6],Class[3],fees_paid[6],balance[6];
	public:
		void read();
		void pack();
		friend int search(char *);
		void remove();
		void datadisp();
		void unpack();
		void pack1();
		int getyear1();
		void modify();
		void classFile();
}s;

class index
{
	public:
		char iusn[15],addr[5];
		void initial();
		void write();
}id[50],in;


class sindex
{
	public :
		char sname[20],susn[15];
		void sinitial();
		void swrite();
}sid[50],sin;


// function to copy index file to array structure

void index::initial()
{
	ifile.open(indexfile,ios::in);
	if(!ifile)
	{
		indsize=0;
		return;
	}
	for(indsize=0;;indsize++)
	{
		ifile.getline(id[indsize].iusn,15,'|');
		ifile.getline(id[indsize].addr,5,'\n');
		if(ifile.eof())
			break;
	}
	ifile.close();
}

int student::getyear1()
{
	int y1;
	struct date dt;
	getdate(&dt);
	y1=dt.da_year;
	return y1;
}

//function to copy sindex file to array structure

void sindex::sinitial()
{
	sifile.open(sindexfile,ios::in);
	if(!sifile)
	{
		sindsize=0;
		return;
	}
	for(sindsize=0;;sindsize++)
	{
		sifile.getline(sid[sindsize].sname,20,'|');
		sifile.getline(sid[sindsize].susn,15,'\n');
		if(sifile.eof())
			break;
	}
	sifile.close();
}


// function to update the index file

void index::write()
{
	opener(ifile,indexfile,ios::out);
	for(i=0;i<indsize;i++)
	ifile<<id[i].iusn<<"|"<<id[i].addr<<"\n";
}

//function to upadate the secondary file

void sindex::swrite()
{

	 opener(sifile,sindexfile,ios::out);
			for(i=0;i<sindsize;i++)
	sifile<<sid[i].sname<<"|"<<sid[i].susn<<"\n";

}



// function to read the student record

void student::read()
{
	int k,flag,flag1,flag2,dig_check,n=0;
	char c[3];
	float f,fp,f1,fp1,bal=0.0;
	year1=s.getyear1();
	opener(dfile,datafile,ios::in|ios::out);
	dfile.getline(c,3,'|');
	dfile.close();
	count=atoi(c);
	count=count+1;
	dig_check=count;
	while(dig_check>0)
	{
		dig_check=dig_check/10;
		n++;
	}
	itoa(year1,year2,10);
	itoa(count,count_copy,10);
		cout<<"\nYour roll number is:";
		for(int j=0;j<4;j++)
			dusn[j]=year2[j];
		dusn[4]='-';
		if(n>1)
		{
			dusn[5]=count_copy[0];
			dusn[6]=count_copy[1];
		}
		else
		{
			dusn[5]='0';
			dusn[6]=count_copy[0];
		}

		cout<<dusn;
	for(i=indsize;i>0;i--)
	{
		if(strcmp(dusn,id[i-1].iusn)<0)
		id[i]=id[i-1];
		else
			break;
	}

	Get_Name:
		cout<<"\nEnter the Student's Name:";
		gets(name);
		flag=checkName(name);
		if(flag==0)
		{
			cout<<"\nInvalid Name";
			goto Get_Name;
		}

	cout<<"\nEnter the class:";
	gets(Class);
	flag2=atoi(Class);
	while(flag2<1 || flag2>12)
	{
		cout<<"\nWrong Class Entered.Please Try again";
		cout<<"\nEnter the class:";
		gets(Class);
		flag2=atoi(Class);
	}
	Get_Fees(fees,Class);
	f=atoi(fees);
	cout<<"\nThe Fees is:"<<f<<endl;
	cout<<"\nEnter the Fees Paid:";
	gets(fees_paid);
	fp=atoi(fees_paid);
	while(f<0)
	{
		cout<<"\nNegative fees Entered.Please Try again";
		cout<<"\nEnter the Fees:";
		gets(fees);
		f=atoi(fees);
	}
	while(fp>f)
	{
		cout<<"\nFees Paid is more than fees.Please Try again.";
		cout<<"\nEnter the Fees Paid:";
		gets(fees_paid);
		fp=atoi(fees_paid);
	}
	bal=f-fp;
	cout<<"\nAmount left to be paid:"<<bal;
	itoa (bal,balance,10);
	opener(dfile,datafile,ios::in|ios::out);
	dfile.seekp(0,ios::beg);
	pack1();
	dfile.clear();
	dfile.seekp(0,ios::end);
	k=dfile.tellg();
	pack();
	strcpy(id[i].iusn,dusn);
	itoa(k,id[i].addr,10);
	indsize++;
	for(i=sindsize;i>0;i--)
	{
			if(strcmp(name,sid[i-1].sname)<0)
				sid[i]=sid[i-1];
			else if((strcmp(name,sid[i-1].sname)==0) && (strcmp(dusn,sid[i-1].susn)<0))
				sid[i]=sid[i-1];
			else
				 break;
	}
	strcpy(sid[i].sname,name);
	strcpy(sid[i].susn,dusn);
	sindsize++;
}

void student::pack1()
{

	strcpy(headbuf,count_copy);
	strcat(headbuf,"|");
	strcat(headbuf,"6");
	strcat(headbuf,"|");
	strcat(headbuf,year2);
	strcat(headbuf,"|");
	dfile<<headbuf<<"#";

}
 void student::pack()
  {
    strcpy(buffer,dusn);
    strcat(buffer,"|");
    strcat(buffer,name);
    strcat(buffer,"|");
    strcat(buffer,Class);
    strcat(buffer,"|");
    strcat(buffer,fees);
    strcat(buffer,"|");
    strcat(buffer,fees_paid);
    strcat(buffer,"|");
    strcat(buffer,balance);
    strcat(buffer,"|");
    dfile<<buffer<<"*";
  }



//function to search based on usn number


int search(char * fusn)
{
	int low=0,high=indsize-1,mid;
	while(low <=high)
	{
		mid = (low+high)/2;
		if(strcmp(fusn,id[mid].iusn)==0)
			return mid;
		if(strcmp(fusn,id[mid].iusn)>0)
			low=mid+1;
		else
			high=mid-1;
	}
	return -1;
}


//function to search based on secondary key


int sec_search()
{
	int pos,j,flag=-1;
	cout<<"\n\n\nEnter the name to search(sec key):";
	gets(skey);
	cout<<"\nThe searched record details are :"<<endl;
	cout<<setiosflags(ios::left);
	cout<<"Roll No"<<"\t\tName"<<endl;
	opener(dfile,datafile,ios::in|ios::out);
	for(j=0;j<sindsize;j++)
	if(strcmp(skey,sid[j].sname)==0)
	{
		cout<<sid[j].susn<<"\t\t"<<sid[j].sname<<endl;
		flag=j;
	 }
	return flag;
}

// function to remove the record

void student::remove()
{
	char rusn[10];
	int pos,spos;
	cout<<"\nEnter the Roll number above listed:";
	cin>>rusn;
	for(i=0;i<sindsize;i++)
	{
		if(strcmp(sid[i].susn,rusn)==0)
		{
			spos=i;
			break;
		}
	}
	if(strcmp(sid[spos].sname,skey)==0)
	{
		pos=search(rusn);
		dfile.seekp(atoi(id[pos].addr),ios::beg);
		dfile.put('$');
		for(i=pos;i<indsize;i++)
			id[i]=id[i+1];
		indsize--;
		for(i=spos;i<sindsize;i++)
			sid[i]=sid[i+1];
		sindsize--;
		cout<<"Record Deleted Successfully";
	}
	else
		cout<<"\nRoll number and Name doesn't match.";
}


//function to display the datafile

void student::datadisp()
{
	char header[20];
	dfile.getline(header,11,'#');
	cout<<setiosflags(ios::left);
	cout<<setw(8)<<"Roll"<<setw(16)<<"Name"<<setw(8)<<"Class";
	cout<<setw(8)<<"Fees"<<setw(8)<<"Paid"<<setw(8)<<"Bal"<<endl;
	while(1)
	{
		unpack();
		if(dfile.eof())
			break;
		 if(dusn[0]!='$')
		{
			cout<<setw(8)<<dusn<<setw(16)<<name<<setw(8)<<Class;
			cout<<setw(8)<<fees<<setw(8)<<fees_paid<<setw(8)<<balance<<endl;
		}
	}
	cout<<endl<<"\nThe index file details are:"<<endl;
	cout<<setw(10)<<"Roll"<<setw(10)<<"Address";
	for(i=0;i<indsize;i++)
		cout<<endl<<setw(10)<<id[i].iusn<<setw(10)<<id[i].addr;
		cout<<endl<<"\nThe secondary file details are:" <<endl;
		cout<<setw(20)<<"Name"<<setw(15)<<"Primary Reference";
		for(i=0;i<sindsize;i++)
			cout<<endl<<setw(20)<<sid[i].sname<<setw(15)<<sid[i].susn;
}



//function to unpack the data file

void student::unpack()
{
	char dummy[75];
	dfile.getline(dusn,10,'|');
	dfile.getline(name,20,'|');
	dfile.getline(Class,4,'|');
	dfile.getline(fees,7,'|');
	dfile.getline(fees_paid,7,'|');
	dfile.getline(balance,7,'|');
	dfile.getline(dummy,75,'*');
}
void student::modify()
{
	char rusn[10];
	int pos,spos;
	list1:
	cout<<"\nEnter the Roll number above listed:";
	cin>>rusn;
	for(i=0;i<sindsize;i++)
	{
		if(strcmp(sid[i].susn,rusn)==0)
		{
			spos=i;
			break;
		}
	}
	if(strcmp(sid[spos].sname,skey)==0)
	{
		pos=search(rusn);
		dfile.seekp(atoi(id[pos].addr),ios::beg);
		dfile.put('$');
		for(i=pos;i<indsize;i++)
			id[i]=id[i+1];
		indsize--;
		for(i=spos;i<sindsize;i++)
			sid[i]=sid[i+1];
		sindsize--;
	}
	else
	{
		cout<<"\nRoll number and Name doesn't match.Please try again";
		goto list1;
	}
	in.write();
	sin.swrite();
	dfile.close();
	ifile.close();
	sifile.close();
	cout<<endl<<"\nEnter new student details:" <<endl;
	int k,flag,flag1,flag2;
	float f,fp,f1,fp1,bal=0.0;
	cout<<"\nYour roll number is:";
	cout<<rusn;
	strcpy(dusn,rusn);
	for(i=indsize;i>0;i--)
	{
		if(strcmp(dusn,id[i-1].iusn)<0)
		id[i]=id[i-1];
		else
			break;
	}

	Get_Name:
		cout<<"\nEnter the Student's Name:";
		gets(name);
		flag=checkName(name);
		if(flag==0)
		{
			cout<<"\nInvalid Name";
			goto Get_Name;
		}

	cout<<"\nEnter the class:";
	gets(Class);
	flag2=atoi(Class);
	while(flag2<1 || flag2>12)
	{
		cout<<"\nWrong Class Entered.Please Try again";
		cout<<"\nEnter the class:";
		gets(Class);
		flag2=atoi(Class);
	}
	Get_Fees(fees,Class);
	f=atoi(fees);
	cout<<"\nThe Fees is:"<<f<<endl;
	cout<<"\nEnter the Fees Paid:";
	gets(fees_paid);
	fp=atoi(fees_paid);
	while(f<0)
	{
		cout<<"\nNegative fees Entered.Please Try again";
		cout<<"\nEnter the Fees:";
		gets(fees);
		f=atoi(fees);
	}
	while(fp>f)
	{
		cout<<"\nFees Paid is more than fees.Please Try again.";
		cout<<"\nEnter the Fees Paid:";
		gets(fees_paid);
		fp=atoi(fees_paid);
	}
	bal=f-fp;
	cout<<"\nAmount left to be paid:"<<bal;
	itoa (bal,balance,10);
	opener(dfile,datafile,ios::in|ios::out);
	dfile.seekp(0,ios::beg);
	pack1();
	dfile.clear();
	dfile.seekp(0,ios::end);
	k=dfile.tellg();
	pack();
	strcpy(id[i].iusn,dusn);
	itoa(k,id[i].addr,10);
	indsize++;
	for(i=sindsize;i>0;i--)
	{
			if(strcmp(name,sid[i-1].sname)<0)
				sid[i]=sid[i-1];
			else if((strcmp(name,sid[i-1].sname)==0) && (strcmp(dusn,sid[i-1].susn)<0))
				sid[i]=sid[i-1];
			else
				 break;
	}
	strcpy(sid[i].sname,name);
	strcpy(sid[i].susn,dusn);
	sindsize++;
	in.write();
	sin.swrite();
}
void student::classFile()
{
	fstream ofile(datafile,ios::in);
	//opener(ofile,datafile,ios::in);
	opener(infile,"214.txt",ios::out);
	int arr[13];
	int c;
	for(int i=1;i<13;i++)
		arr[i]=0;
	char Ibuf[50]="";
	ofile.getline(Ibuf,50,'#');
	while(1)
	{
		if(ofile.fail())
			break;
		char dummy[75];
	ofile.getline(dusn,10,'|');
	ofile.getline(name,20,'|');
	ofile.getline(Class,4,'|');
	ofile.getline(fees,7,'|');
	ofile.getline(fees_paid,7,'|');
	ofile.getline(balance,7,'|');
	ofile.getline(dummy,75,'*');
		c=atoi(Class);
		if(dusn[0]!='$')
		switch(c)
		{
			case 1:
				arr[1]+=1;
				break;
			case 2:
				arr[2]+=1;
				break;
			case 3:
				arr[3]+=1;
				break;
			case 4:
				arr[4]+=1;
				break;
			case 5:
				arr[5]+=1;
				break;
			case 6:
				arr[6]+=1;
				break;
			case 7:
				arr[7]+=1;
				break;
			case 8:
				arr[8]+=1;
				break;
			case 9:
				arr[19]+=1;
				break;
			case 10:
				arr[10]+=1;
				break;
			case 11:
				arr[11]+=1;
				break;
			case 12:
				arr[12]+=1;
				break;

		}
	}
	infile<<setw(8)<<"Class"<<setw(16)<<"No of Students"<<"\n";
	for(int j=1;j<13;j++)
		infile<<setw(8)<<j<<setw(16)<<arr[j]<<"\n";
	ofile.close();
	infile.close();
}



class DRAW
{
	public :
			void LINE_HOR(int, int, int, char) ;
			void LINE_VER(int, int, int, char) ;
			void BOX(int,int,int,int,char) ;
} ;






void mainmenu()
{

	clrscr();
	textcolor(WHITE);
	for(li=10;li<=30;li++)
	{
		textcolor(WHITE);
		gotoxy(li,5);
		delay(5);
		printf("*");
	}
	for(li=80;li>=60;li--)
	{
		textcolor(WHITE);
		gotoxy(li,30);
		delay(5);
		printf("*");
	}
	for(lp=5;lp<20;lp++)
	{
		gotoxy(10,lp);
		delay(5);
		printf("*");
	}
	for(lp=19;lp>=5;lp--)
	{
		gotoxy(51,lp);
		delay(5);
		printf("*");
	}
		for(i=51;i>=10;i--)
	{
		gotoxy(i,20);
		delay(5);
		printf("*");
	}
	gotoxy(15,5);
	textcolor(LIGHTGRAY);
	cprintf("\nPress To Select:");
	gotoxy(15,7);
	textcolor(BROWN);
	cprintf("\n1: Enter the Details");
	gotoxy(15,9);
	textcolor(LIGHTMAGENTA);
	cprintf("\n2: Display all Records");
	gotoxy(15,11);
	textcolor(LIGHTBLUE);
	cprintf("\n3: Search");
	gotoxy(15,13);
	textcolor(LIGHTRED);
	cprintf("\n4: Delete");
	gotoxy(15,15);
	textcolor(BLUE);
	cprintf("\n5: Modify");
	 gotoxy(15,17);
	textcolor(GREEN);
	cprintf("\n6: QUIT:");
	cin>>ch;
	textcolor(WHITE);
	s.classFile();
	switch(ch)
	{
		case 1:
		       cout<<endl<<"\n\n\n\nEnter student details:" <<endl;
				 s.read();
				 in.write();
				 sin.swrite();
				 dfile.close();
				 ifile.close();
				 sifile.close();

				gotoxy(33,40);
				cout<<"\nPress any key to return to Main Menu";
			       getch();
			       mainmenu();
			break;
		case 2:
			 opener(dfile,datafile,ios::in);
				cout<<"\n\n\nThe Datafile Contains:\n" <<endl;
				s.datadisp();
				 dfile.close();
				 ifile.close();
				 sifile.close();
				 gotoxy(33,40);
				 cout<<"\nPress any key to return to Main Menu";
				    getch();
				   mainmenu();
				    break;
		case 3:
			cout<<"\n\n\nTo Search based on  Sec key....";
				flag=sec_search();
				if(flag==-1)
					cout<<"\nNo Data record.";
				 dfile.close();
				 ifile.close();
				 sifile.close();
				 gotoxy(33,40);
				 cout<<"\nPress any key to return to Main Menu";
				    getch();
				    mainmenu();
			       break;
		case 4:
		       flag=sec_search();
				if(flag==-1)
				cout<<"\nNo Data record found";
				else
				{
					s.remove();
					in.write();
					sin.swrite();
				 }

				  dfile.close();
				  ifile.close();
				  sifile.close();
				  gotoxy(33,40);
				 cout<<"\nPress any key to return to Main Menu";
				  getch();
				   mainmenu();
			break;
		case 5:	cout<<"\n\n\nEnter the name whoose record is needed to be modified";
				flag=sec_search();
				if(flag==-1)
				cout<<"\nNo Data record found";
				else
				{
					s.modify();
				 }
				   dfile.close();
				   ifile.close();
				   sifile.close();
				   gotoxy(33,40);
				 cout<<"\n Press any key to return to Main Menu";
				   getch();
				    mainmenu();
				   break;
		case 6:exit(0);
			break;
		default:gotoxy(33,40);
			cout<<"\nPress any key to return to Main Menu";
			getch();
			mainmenu();
	}
}



void DRAW :: LINE_HOR(int column1, int column2, int row, char c)
{
	for ( column1; column1<=column2; column1++ )
	{
		gotoxy(column1,row) ;
		cout <<c ;
	}
}



void DRAW :: LINE_VER(int row1, int row2, int column, char c)
{
	for ( row1; row1<=row2; row1++ )
	{
		gotoxy(column,row1) ;
		cout <<c ;
	}
}


//**********************************************************
// FUNCTION TO DRAW BOX LINE
//**********************************************************

void DRAW :: BOX(int column1, int row1, int column2, int row2, char c)
{
	char ch=218 ;
	char c1, c2, c3, c4 ;
	char l1=196, l2=179 ;
	if (c == ch)
	{
		c1=218 ;
		c2=191 ;
		c3=192 ;
		c4=217 ;
		l1 = 196 ;
		l2 = 179 ;
	}
	else
	{
		c1=c ;
		c2=c ;
		c3=c ;
		c4=c ;
		l1 = c ;
		l2 = c ;
	}
	gotoxy(column1,row1) ;
	cout <<c1 ;
	gotoxy(column2,row1) ;
	cout <<c2 ;
	gotoxy(column1,row2) ;
	cout <<c3 ;
	gotoxy(column2,row2) ;
	cout <<c4 ;
	column1++ ;
	column2-- ;
	LINE_HOR(column1,column2,row1,l1) ;
	LINE_HOR(column1,column2,row2,l1) ;
	column1-- ;
	column2++ ;
	row1++ ;
	row2-- ;
	LINE_VER(row1,row2,column1,l2) ;
	LINE_VER(row1,row2,column2,l2) ;
}




//**********************************************************
// MAIN FUNCTION TO CREATE MENU AND CALL OTHER FUNCTIONS
//**********************************************************

void main()
{
	in.initial();
	sin.sinitial();
	clrscr();
	textcolor(MAGENTA);
	for(i=10;i<71;i++)
	{
		textcolor(MAGENTA);
		gotoxy(i,15);
		delay(5);
		printf("/");
	}
	for(i=70;i>=10;i--)
	{
		gotoxy(i,22);
		delay(5);
		printf("\"");
	}
	for(j=16;j<=21;j++)
	{
		gotoxy(10,j);
		delay(5);
		printf("-");
	}
	for(j=21;j>=16;j--)
	{
		gotoxy(70,j);
		delay(5);
		printf("-");
	}
	gotoxy(16,17);
	textcolor(BLINK + MAGENTA);
	cprintf("\nWelcome To Fee Structure System   ");
	gotoxy(36,20);
	textcolor(LIGHTGREEN);
	cprintf("\nDesigned and Coded By");
	gotoxy(15,28);
	textcolor(LIGHTGREEN);
	cprintf("\n");
	gotoxy(15,34);
	textcolor(3);
	cprintf("\nAditya & Ekalavaya                                       \n");
	gotoxy(40,48);
	textcolor(WHITE);
	cprintf("\nPress Any Key To Continue");
	getch();
	mainmenu();
	dfile.close();
	ifile.close();
	sifile.close();
	getch();
}








