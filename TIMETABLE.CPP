
/*****************************
PROGRAM TO GENERATE TIMETABLE
******************************/
#include<graphics.h>
#include<conio.h>
#include<fstream.h>
#include<stdio.h>
#include<string.h>
#include<iomanip.h>
#include<stdlib.h>
/************************************
CLASS TO MAINTAIN DATABASE OF TEACHER
*************************************/
class teacher
{
   char tcode[3];       //TEACHER CODE
   char teachername[30];//TEACHER NAME
   char subcode[3];//SUBJECT CODE OF TEACHER
    int d;
   public:
   teacher()
   {
     d=0;
   }
   //FUNCTION TO ENTER DATA OF TEACHERS
   void enter();
   //FUNCTION TO DISPLAY DATA OF TEACHERS
   void show()
   {
       cout<<"\nteacher name is  :  "<<teachername;
       cout<<"\nsubject code : "<<subcode;
       cout<<"\nteacher code is : "<<tcode;
   }
   //FUNCTION TO ADD NEW TEACHERS
   void modify();
};
void teacher :: enter()
{
  cout<<"\nteachername is : ";
  gets(teachername);
  cout<<"\nteachercode is : ";
  gets(tcode);
  cout<<"\nsubject code is : ";
  gets(subcode);
}
void teacher :: modify()
{
   fstream f("TEACHER.DAT",ios :: app | ios :: binary);
   teacher t;
   int n;
   cout<<"\nenter the number of enteries : ";
   cin>>n;
   for(int i=0;i<n;i++)
   {
      t.enter();
      f.write((char*)&t,sizeof(t));
   }
   f.close();
}
/************************************
CLASS TO MAINTAIN DATABASE OF SUBJECT
*************************************/
class subjectname
{
   char subcode[4]; //SUBJECT CODE
   char subname[30];//SUBJECT NAME
   public:
   //FUNCTION TO ENTER DATA OF SUBJECTS
   void enter();
   //FUNCTION TO DISPLAY DATA OF SUBJECTS
   void show()
   {
     cout<<"\nsubject code is  :  "<<subcode;
     cout<<"\nsubname is  :  "<<subname;
   }
   void modify();
   //FUNCTION TO ADD NEW SUBJECTS
   friend void return4(char s1[4],char s2[30]);
   //FUNCTION TO COPY SUBJECT NAME ACCORDING TO SUBJECT CODE
};
void return4(char s1[4],char s2[30])
   {
      fstream f("SUBJECT.DAT",ios :: in|ios :: binary);
      subjectname s;
      f.read((char*)&s,sizeof(s));
      while(!f.eof())
      {
	 if(strcmpi(s1,s.subcode)==0)
	 {
	   strcpy(s2,s.subname);
	 }
	 f.read((char*)&s,sizeof(s));
      }
   }
void subjectname :: enter()
{
     cout<<"\nenter the subject :  ";
     gets(subname);
     cout<<"\nenter the subject code : ";
     gets(subcode);

}
void subjectname :: modify()
{
   fstream f("SUBJECT.DAT",ios :: app | ios :: binary);
   subjectname s1;
   int n;
   cout<<"\nenter the number of enteries : " ;
   cin>>n;
   for(int i=0;i<n;i++)
   {
      s1.enter();
      f.write((char*)&s1,sizeof(s1));
   }
   f.close();
}
//STRUCTURE TO ENTER THE CLASS AND SECTION
struct classandsection
{
   int classno;
   char section;
};
/
****************************************************************
CLASS TO MAINTAIN DATABASE OF CLASSES THAT ARE TAUGHT BY TEACHERS
*****************************************************************/
class subjectteacher
{
   classandsection c[5];
   char tcode[4];//TEACHER CODE
   char subcode[4];//SUBJECT CODE
   int i;//NUMBER OF CLASSES THAUGHT BY TEACHER
   public:
   //FUNCTION TO ENTER THE DATA
   void enter();
   //FUNCYION TO DISPLAY DATA
   void show();
   //FUNCTION ADD NEW TEACHER
   void add();
   //FUNCTION TO MODIFY DETAILS OF TEACHER
   void modify();
   //FUNCTION TO RETURN TEACHER CODE ACCORDING TO SUBJECT CODE
   friend void return2(char s[4],char t[4]);
};
void subjectteacher :: show()
 {

       int n;
       cout<<"\nenter the number of enteries : ";
       cin>>n;
       for(i=0;i<n;i++)
       {
	  cout<<"\nclass is  :  "<<c[i].classno;

	  cout<<"\section is  : "<<c[i].section;
       }
       cout<<"\nteacher code is  : "<<tcode;
       cout<<"\nsubject code is  : "<<subcode;
 }
void subjectteacher :: add()
 {
       fstream f("SUBJECTTEACHER.DAT",ios :: app | ios :: binary);
       subjectteacher s;
       int n;
       fstream f1("TEACHER.DAT",ios :: app | ios :: binary);
       teacher t;
       cout<<"\nenter the number of enteries : ";
       cin>>n;
       for(int i=0;i<n;i++)
       {
	  t.enter();
	  s.enter();
	  f1.write((char*)&t,sizeof(t));
	  f.write((char*)&s,sizeof(s));
	  f.close();
	  f1.close();
       }
 }

void subjectteacher :: enter()
{
   int n;
   cout<<"\nenter the number of enteries : ";
   cin>>n;
   for(i=0;i<n;i++)
   {
     cout<<"\nclass is  :  ";
     cin>>c[i].classno;
     cout<<"\section is  : ";
     cin>>c[i].section;
   }
   cout<<"\nenter the subcode : ";
   gets(subcode);
   cout<<"\nenter the tcode : ";
   gets(tcode);
}
void return2(char s[4],char t[4])
{
   fstream f("SUBJECTTEACHER.DAT",ios :: in | ios :: binary);
   subjectteacher s1;
   f.read((char*)&s1,sizeof(s1));
   while(!f.eof())
   {
      if(strcmpi(s,s1.subcode)==0)
      {
	strcpy(t,s1.tcode);
	break;
      }
      f.read((char*)&s1,sizeof(s1));
   }
   f.close();
}
//STRUCTURE OF SUBJECT CODE AND NUMBER OF PERIODS
struct  subject
{
   char subcode[4];
   int noofperiods;
};
/******************************************************
 CLASS TO MAINTAIN DATA OF NUMBER OF PERIODS IN A CLASS
*******************************************************/
class period
{
   int classno;//CLASS NUMBER
   int n;      //NUMBER OF SUBJECTS
   char section;//SECTION OF CLASS
   subject s[10];
   public:
   //CONSTRUCTOR
   period()
   {
     n=0;
   }
   //FUNCTION TO ENTER THE DATA
   void enter(int n1);
   //FUNCTION TO DISPLAY DATA
   void show();
   //FUNCTION TO ADD NEW CLASS
   void add();
   //FUNCTION TO RETURN NUMBER OF PERIODS AND SUBJECT CODE
   void return1(char s1[3],int & n1,int m)
   {
      strcpy(s1,s[m-1].subcode);
      n1=s[m-1].noofperiods;
   }
   //FUNCTION TO RETURN THE CLASS NUMBER
   int classno1()
   {
      return classno;
   }
   //FUNCTION TO RETURN SECTION
   char section1()
   {
      return section;
   }
   //FUNCTION TO RETURN NUMBER OF SUBJECTS
   int return3()
   {
     return n;
   }
   //FUNCTION TO ADD NEW CLASS
   void modify();
};
void period :: show()
{
   int j=0;
   for(j=0;j<n;j++)
   {
       cout<<"\nclass is  :  "<<classno;
       cout<<"\nsection is : "<<section;
       cout<<"\nnumber of periods is  : "<<s[j].noofperiods;
       cout<<endl<<"subject code is : "<<s[j].subcode;
       getch();
   }
}

void period :: enter(int n1)
{
   int j;
   cout<<"\nenter the class :  ";
   cin>>classno;
   cout<<"\nenter the section :  ";
   cin>>section;
   n=n1;
   for(j=0;j<n;j++)
     {
       cout<<"\nenter the subject code ";
       gets(s[j].subcode);
       cout<<"\nenter the number of periods : ";
       cin>>s[j].noofperiods;
     }
}
void period :: add()
{
  fstream f("PERIOD.DAT",ios :: app | ios :: binary);
  period p;
  int n,j;
  cout<<"\nenter the number of enteries : ";
  cin>>n;
  for(int i=0;i<n;i++)
  {
     cout<<"\nenter the number of subjects : ";
     cin>>j;
     p.enter(j);
     f.write((char*)&p,sizeof(p));
  }
  f.close();
}
void period :: modify()
{
   int classno1;
   char section1,sub[30];
   fstream f("PERIOD.DAT",ios :: in | ios :: out | ios :: binary);
   period p;
   cout<<"\nenter the class : ";
   cin>>classno1;
   cout<<"\nenter the section : ";
   cin>>section1;
   cout<<"\nenter the subject code : ";
   gets(sub);
   f.read((char*)&p,sizeof(p));
   while(!f.eof())
   {
      if(p.classno1()==classno1 && section1==p.section1())
      {
	break;
      }
      f.read((char*)&p,sizeof(p));
   }
   for(int i=0;i<n;i++)
   {
      if(strcmpi(sub,s[i].subcode)==0)
      {
	 cout<<"\nenter the number of period : ";
	 cin>>s[i].noofperiods;
       }
   }
   f.seekg(-sizeof(p),ios :: cur);
   f.write((char*)&p,sizeof(p));
   f.close();
}
//STRUCTURE FOR DATABASE OF SUBJECTS
struct subject2
{
  char subcode[4];//SUBJECT CODE
  int n[6];       //NUMBER OF PERIODS IN EACH DAY
  int d;          //NUMBER OF PERIODS IN A WEEK
  int m;          //VARIABLE USED FOR COMPAIRING NUMBER OF PERIODS
};
//STRUCTURE TO DATABASE OF SUBJECT AND TEACHETS
struct subject3
{
  char scode[4];//SUBJECTCODE
  char tcode[4];//TEACHERCODE
  char subname[30];//SUBJECTNAME
};
//FUNCTION TO GENERATE AND DISPLAY TIMETABLE
void display(int classno1,char section1,int classno2,char section2,int classno3,char section3)
{
  cleardevice();
  fstream f("PERIOD.DAT",ios :: in | ios :: binary);
  int i,j,k,c,l,l2,l3,m1,m2,m3,n1,n2,n3;
  /*n1,n2,n3 :- VARIABLES FOR STORING NUMBER OF SUBJECTS
    m1,m2,m3 :- RANDOM VARIABLES USED FOR GENERATING TIMETABLE*/
  subject2 s1[10],s2[10],s3[10];
  subject3 f1[6][8],f2[6][8],f3[6][8];
  period p,p1,p2,p3;
  f.read((char*)&p,sizeof(p));
  while(!f.eof())
   {
    //COMPAIRING THE CLASS NUMBER AND SECTION
    if(p.classno1()==classno1 && section1==p.section1())
     {
      p1=p;
     }
    else if(p.classno1()==classno2 && section2==p.section1())
    {
      p2=p;
    }
    else if(p.classno1()==classno3 && section3==p.section1())
    {
      p3=p;
    }
    f.read((char*)&p,sizeof(p));
  }
  f.close();
  //RETURNING NUMBER OF SUBJECTS
  n1=p1.return3();
  n2=p2.return3();
  n3=p3.return3();
  //LOOP FOR ENTERING DATA FROM OBJECT OF CLASS PERIOD
  for(i=0;i<n1;i++)
  {
     p1.return1(s1[i].subcode,s1[i].d,i+1);
     s1[i].m=0;
     for(j=0;j<6;j++)
      {
	s1[i].n[j]=0;
      }
  }
  //LOOP FOR ENTERING DATA FROM OBJECT OF CLASS PERIOD
  for(i=0;i<n2;i++)
  {
     p2.return1(s2[i].subcode,s2[i].d,i+1);
     s2[i].m=0;
     for(j=0;j<6;j++)
      {
	s2[i].n[j]=0;
      }

  }
  //LOOP FOR ENTERING DATA FROM OBJECT OF CLASS PERIOD
  for(i=0;i<n3;i++)
  {
     p3.return1(s3[i].subcode,s3[i].d,i+1);
     s3[i].m=0;
     for(j=0;j<6;j++)
      {
	s3[i].n[j]=0;
      }

  }
  randomize();
  m1=random(n1);
  m2=random(n2);
  m3=random(n3);
  //LOOP FOR GENERATING TIME TABLE
  for(i=0;i<6;i++)
  {
    for(j=0;j<8;j++)
    {
      //CHECKING THE CONDITION FOR NUMBER OF PERIODS IN A WEEK
      if(s1[m1].m==s1[m1].d)
	 {
	  l: m1=random(n1);
	 }
	//CHECKING THE CONDITION FOR NUMBER OF PERIODS IN A WEEK
	if(s1[m1].n[i]>=0&&s1[m1].n[i]<2)
	{
	   //COPYING THE SUBJECT CODE
	   strcpy(f1[i][j].scode,s1[m1].subcode);
	   //COPYING THE TEACHER CODE
	   return2(f1[i][j].scode,f1[i][j].tcode);
	   //COPYING THE SUBJECT NAME
	   return4(f1[i][j].scode,f1[i][j].subname);
	   (s1[m1].n[i])++;
	   (s1[m1].m)++;
	   m1=random(n1);
	}
	else
	{
	 goto l;
	}
      //CHECKING THE CONDITION FOR NUMBER OF PERIODS IN A WEEK
      if(s2[m2].m==s2[m2].d)
	{
	l2 : m2=random(n2);
	}
	//CHECKING THE CONDITION FOR NUMBER OF PERIODS IN A DAY
	if(s2[m2].n[i]>=0&&s2[m2].n[i]<2)
	{
	    //COPYING THE SUBJECT CODE
	    strcpy(f2[i][j].scode,s2[m2].subcode);
	    //COPYING THE TEACHER CODE
	    return2(f2[i][j].scode,f2[i][j].tcode);
	    //COPYING THE SUBJECT NAME
	    return4(f2[i][j].scode,f2[i][j].subname);
	    (s2[m2].n[i])++;
	    (s2[m2].m)++;
	    //CHECKING CONDITION FOR SAME TEACHER
	    if(strcmpi(f1[i][j].tcode,f2[i][j].tcode)==0)
	      goto l2;
	    m2=random(n2);
	}
	else
	{
	   goto l2;
	}
	//CHECKING THE CONDITION FOR NUMBER OF PERIODS IN A WEEK
	if(s3[m3].m==s3[m3].d)
	{
	l3: m3=random(n3);
	}
	//CHECKING THE CONDITION FOR NUMBER OF PERIODS IN A DAY
	if(s3[m3].n[i]>=0&&s3[m3].n[i]<2)
	{
	    //COPYING THE SUBJECT CODE
	    strcpy(f3[i][j].scode,s3[m3].subcode);
	    //COPYING THE TEACHER CODE
	    return2(f3[i][j].scode,f3[i][j].tcode);
	    //COPYING THE SUBJECT NAME
	    return4(f3[i][j].scode,f3[i][j].subname);
	   (s3[m3].n[i])++;
	   (s3[m3].m)++;
	   //CHECKING CONDITION FOR SAME TEACHER
	  if(strcmpi(f1[i][j].tcode,f3[i][j].tcode)==0)
	     goto l3;
	   m3=random(n3);
	}
	else
	{
	   goto l3;
	}
      }

  }
      char string[10];
      outtextxy(2,5,"\nCLASS IS : ");
      itoa(classno1,string , 10);
      //CONVERTING AN INTEGER DATA TYPE TO A STRING DATA TYPE
      outtextxy(100,5,string);
      string[0]=section1;
      string[1]='\0';
      outtextxy(120,5,string);
      int r=0,s=80,size=2,t;
      settextstyle(1,0,size);
      setcolor(RED);
      /*CHANGING COLOUR OF FONT TO RED*/
      t=67;
      i=0;
      for(i=0;i<9;i++)//LOOP FOR DISPLAYING TABLE
	 {
	 line(t,54,t,386);
	 t=t+67;
	 }
      t=55;
      for(i=0;i<7;i++)
	 {
	 line(0,t,605,t);
	 t=t+55;
	 }
      outtextxy(2,80,"MON" );
      outtextxy(2,130,"TUE");
      outtextxy(2,180,"WED");
      outtextxy(2,230,"THU");
      outtextxy(2,280,"FRI");
      outtextxy(2,330,"SAT");
      for(i=0;i<6;i++)
	{
	  r=69;
	  for(j=0;j<8;j++)
	    {
	     outtextxy(r,s,f1[i][j].subname );
	     r=r+69;
	    }
	  s=s+50;
	}
      getch();
      cleardevice();
      outtextxy(2,5,"\nCLASS IS : ");
      itoa(classno2,string , 10);
      //CONVERTING AN INTEGER DATA TYPE TO A STRING DATA TYPE
      outtextxy(100,5,string);
      string[0]=section2;
      string[1]='\0';
      outtextxy(129,5,string);
      r=0;
      s=80;
      settextstyle(1,0,size);
      setcolor(RED);
      /*CHANGING COLOUR OF FONT TO RED*/
      t=67;
      i=0;
      for(i=0;i<9;i++)//LOOP FOR DISPLAYING TABLE
	 {
	  line(t,54,t,386);
	  t=t+67;
	 }
      t=55;
      for(i=0;i<7;i++)
	 {
	  line(0,t,605,t);
	  t=t+55;
	 }
     outtextxy(2,80,"MON" );
     outtextxy(2,130,"TUE");
     outtextxy(2,180,"WED");
     outtextxy(2,230,"THU");
     outtextxy(2,280,"FRI");
     outtextxy(2,330,"SAT");
     for(i=0;i<6;i++)
     {
	 r=69;

	for(j=0;j<8;j++)
	{
	   outtextxy(r,s,f2[i][j].subname );
	   r=r+69;
	}
	s=s+50;
     }
     getch();
     cleardevice();
     outtextxy(2,5,"\nCLASS IS : ");
     itoa(classno3,string , 10);
     //CONVERTING AN INTEGER DATA TYPE TO A STRING DATA TYPE
     outtextxy(100,5,string);
     string[0]=section3;
     string[1]='\0';
     outtextxy(129,5,string);
     r=0;
     s=80;
     settextstyle(1,0,size);
     setcolor(RED);
     /*CHANGING COLOUR OF FONT TO RED*/
     t=67;
     i=0;
     for(i=0;i<9;i++)   //LOOP FOR DISPLAYING TABLE
	{
	line(t,54,t,386);
	t=t+67;
	}
     t=55;
     for(i=0;i<7;i++)
	{
	line(0,t,605,t);
	t=t+55;
	}
     outtextxy(2,80,"MON" );
     outtextxy(2,130,"TUE");
     outtextxy(2,180,"WED");
     outtextxy(2,230,"THU");
     outtextxy(2,280,"FRI");
     outtextxy(2,330,"SAT");
     for(i=0;i<6;i++)
	{
	 r=69;
	 for(j=0;j<8;j++)
	  {
	   outtextxy(r,s,f3[i][j].subname );
	   r=r+69;
	  }
	 s=s+50;
	}
     getch();
     cleardevice();
}
void main()
{
 int gdriver = DETECT, gmode, errorcode;
 int x,y;
 int midx,midy;
 /* initialize graphics and local variables */
 initgraph(&gdriver, &gmode, "/BGI");
 /* read result of initialization */
 errorcode = graphresult();
 if (errorcode != grOk)  /* an error occurred */
     {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1); /* terminate with an error code */
      closegraph();
     }
 cleardevice();
 int size=5;
 settextstyle(1,0,size);
 setcolor(RED);
 /*CHANGING COLOUR OF FONT TO RED*/
 setbkcolor(CYAN);
 /*CHANGING BACKGROUND TO CYAN COLOUR*/
 outtextxy(220,50," WELCOME " );
 outtextxy(320,150,"TO");
 outtextxy(200,250," TIMETABLE ");
 outtextxy(210,350,"\GENERATOR ");
 size=2;
 settextstyle(1,0,size);
 outtextxy(100,450,"\MADE BY ->  ");
 outtextxy(250,450,"\SOMIL JAIN");
 getch();
 cleardevice();
 int n=1;
 while(n!=6)
 {
      size=1;
      settextstyle(1,0,size);
      setcolor(WHITE);
      /*CHANGING COLOUR OF FONT TO WHITE*/
      outtextxy(0, 10 ,"ENTER YOU CHOICE :" );
      outtextxy(0, 30 ,"1. ADD SUBJECT");
      outtextxy(0, 50 ,"2. ADD TEACHERS ");
      outtextxy(0, 70 ,"3. ADD CLASS ");
      outtextxy(0, 90 ,"4. MODIFY PERIOD");
      outtextxy(0,110 ,"5. GENERATE TIMETABLE");
      outtextxy(0,130 ,"6. EXIT ");
      cin>>n;
      if(n==1)
      {
	 cleardevice();
	 subjectname s;
	 s.modify();
	 //MEMBER FUNCTION modify OF CLASS subjectname TO ADD SUBJECT
      }
      else if(n==2)
      {
	cleardevice();
	teacher t;
	t.modify();
	//MEMBER FUNCTION modify OF CLASS teacher TO ADD TEACHERS
      }
      else if(n==3)
      {
	 cleardevice();
	 period p;
	 p.add();
	 //MEMBER FUNCTION OF CLASS period TO ADD CLASS
      }
      else if(n==4)
      {
	 cleardevice();
	 period p;
	 p.modify();
	 //MEMBER FUNCTION OF CLASS period TO  MODIFY PERIOD
      }
      else if(n==5)
      {
	 cleardevice();
	 int c1,c2,c3;
	 char s1,s2,s3;
	 size=1;
	 setbkcolor(BLACK);
	 /*CHANGING BACKGROUND TO BLACK COLOUR*/
	 settextstyle(1,0,size);
	 setcolor(RED);
	 /*CHANGING COLOUR OF FONT TO RED*/
	 outtextxy(0,  4,"ENTER THE CLASS :  " );
	 cout<<"\n";
	 cin>>c1;
	 outtextxy(0, 40,"ENTER THE SECTION :  :  ");
	 cout<<"\n";
	 cin>>s1;
	 outtextxy(0, 76,"ENTER THE CLASS :   ");
	 cout<<"\n";
	 cin>>c2;
	 outtextxy(0,122,"ENTER THE SECTION :  ");
	 cout<<"\n";
	 cout<<"\n";
	 cin>>s2;
	 outtextxy(0,170,"ENTER THE CLASS :  ");
	 cout<<"\n";
	 cout<<"\n";
	 cin>>c3;
	 outtextxy(0,204,"ENTER THE SECTION :  ");
	 cout<<"\n";
	 cin>>s3;
	 display(c1,s1,c2,s2,c3,s3);
      }
      cleardevice();
   }
 size=8;
 settextstyle(1,0,size);
 outtextxy(75,204,"THANK YOU");
 getch();
}
