#include<iostream.h>
#include<graphics.h>
#include<conio.h>
#include<process.h>
#include<dos.h>
#include<stdio.h>
#include<stddef.h>

#define MAXMENUS 6
#define MAXITEMS 9

#define TRUE 1
#define False 0

#define F1 59
#define ESC 27
#define ENTER 13

#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77

#define TAB 9
#define PGUP 73
#define PGDN 81
#define HOME 71
#define END 79
#define DEL 83
#define BKSP 8

#define BUFFLEN 4096

#define FileLength 8

#define PasswordLength 15
#define PwdSymbol '*'

char ScreenBuffer[BUFFLEN];
class Theme
{
	public:
		int FILE_BAR_BACKGROUND_COLOR,BAR_COLOR;
		int MENU_COLOR,MENU_BACKGROUND;
		int MENU_ACTIVE_COLOR,MENU_ACTIVE_BACKGROUND;
		int TASKBAR_COLOR,TASKBAR_BACKGROUND,TASKBAR_INFO_COLOR;
		int HELP_COLOR;
		int SCREEN_COLOR,SCREEN_BACKGROUND;
		int TEXT_COLOR;
}Obj;
class User
{
		char First_name[15],Middle_name[15],Last_name[15],Email[40];
		char Username[15],Password[10],renter_Password[10];
		long long int Mobile;
	public:
		User()
		{
			First_name[0]=Middle_name[0]=Last_name[0]=Email[0]='\0';
			Username[0],Password[0],renter_Password[0]='\0';
			Mobile=0;
		}
		~User(){};
		void SignUp()
		{
			cout<<"\nFirst Name: ";
			cout<<"\nMiddle Name: ";
			cout<<"\nLast_name: ";
			cout<<"\nMobile No: ";
		}

};
class Product:public User
{
		char Category[15],Product_Name[25],Address[50];
		int Year_of_model,Price;
		long int Alter_Mobile;
	public:
	       void Add_Menu();
};
char ch;
void Welcome(void);
void Add_Menu(void);
void Open(void);
void EXIT(void);
void Help(void);
void MenuAction(int);
void Home_Menu(void);
void Account_Menu(void);
void Filter_Menu(void);
void Search_Menu(void);
void BEEP(void);
char *Menu[MAXMENUS]={"HOME","FILTER","SEARCH","SELL","ACCOUNT","EXIT"};
char *MenuInfo[MAXMENUS]={
				"Products for Sell..",
				"Sort as you like...",
				"Search for product.",
				"Add product to Sell",
				"Manage Account.....",
				"Exit program (ESC)."
};

int X=0,Y=0;
int FMI=0,EMI=0,AMI=0;
int Menu_Item=0;
int FLength,PwLength;

//100 Extra for management
char OutputFile[FileLength+100],Password[PasswordLength+100];
char InputFile[FileLength+100];
char Pass[PasswordLength+100];
int main()
{
	asm{
	 /*   "movb $0x0, %%ah;"
	    "movb $0x10, %%al;"
	    "int $0x10;"
	    //:
	    //:"r"(alphabet)
	    //:"%ah","%al"
	    */
		mov ah,0X10
		mov al,0X10     //set Graphics Mode(Full screen)
		int 0X10
	};
	textmode(3);
	Welcome();
	getch();
	return 0;
}
void Welcome(void)
{
	FILE *fp;
	fp=fopen("PROEX.INF","rb");
	if(!fp)
	{
		Obj.FILE_BAR_BACKGROUND_COLOR=10;
		Obj.BAR_COLOR=0;
		Obj.MENU_COLOR=0;
		Obj.MENU_BACKGROUND=10;
		Obj.MENU_ACTIVE_COLOR=10;
		Obj.MENU_ACTIVE_BACKGROUND=0;
		Obj.TASKBAR_COLOR=0;
		Obj.TASKBAR_BACKGROUND=10;
		Obj.TASKBAR_INFO_COLOR=10;
		Obj.HELP_COLOR=4;
		Obj.SCREEN_COLOR=10;
		Obj.SCREEN_BACKGROUND=7;
		Obj.TEXT_COLOR=0;
	}
	else
	{
		fread(&Obj,sizeof(Obj),1,fp);
	}
	fclose(fp);	//Close the File
	window(1,1,80,25);
	textcolor(Obj.TEXT_COLOR);
	textbackground(0);
	_setcursortype(_NOCURSOR);
	clrscr();
	int x;
	gotoxy(1,1);
	textbackground(Obj.FILE_BAR_BACKGROUND_COLOR);
	for(x=0;x<80;x++)
	{
		cprintf(" ");
	}
	window(1,25,80,25);
	gotoxy(1,1);
	textbackground(Obj.TASKBAR_BACKGROUND);

	gotoxy(3,2);
     /*	window(3,2,8,7);
	readimagefile("12312.jpg",3,2,8,7);     */


	for(x=0;x<80;x++)
	{
		cprintf(" ");
	}
	window(1,1,80,25);
	textcolor(Obj.SCREEN_COLOR);
	textbackground(Obj.SCREEN_BACKGROUND);
	gotoxy(1,2);
	for(x=1;x<=80*23;x++)
		cprintf(" ");
	textcolor(Obj.HELP_COLOR);
	textbackground(Obj.TASKBAR_BACKGROUND);
	gotoxy(1,25);
	cprintf("F1: HELP  |");
	while(TRUE)
	{
		gotoxy(1,1);
		textcolor(15);
		textbackground(4);
		cprintf("Rent2buy.com ");

		textcolor(Obj.MENU_COLOR);
		textbackground(Obj.MENU_BACKGROUND);
		gotoxy(16,1);
		cprintf(Menu[0]);

		gotoxy(23,1);
		cprintf(Menu[1]);

		gotoxy(32,1);
		cprintf(Menu[2]);

		gotoxy(41,1);
		cprintf(Menu[3]);

		gotoxy(48,1);
		cprintf(Menu[4]);

		gotoxy(58,1);
		cprintf(Menu[5]);
		textcolor(Obj.TASKBAR_COLOR);
		textbackground(Obj.TASKBAR_BACKGROUND);
		gotoxy(13,25);
		cprintf(MenuInfo[Menu_Item]);

		switch(Menu_Item)
		{
			case 0:
				X=16;
				break;
			case 1:
				X=23;
				break;
			case 2:
				X=32;
				break;
			case 3:
				X=41;
				break;
			case 4:
				X=48;
				break;
			case 5:
				X=58;
		}
		textcolor(YELLOW);
		textbackground(BLACK);

		gotoxy(X,1);
		cprintf(Menu[Menu_Item]);

		ch=getch();

		if(ch==0)
			ch = getch();
		switch(ch)
		{
				case F1:
    //					Help();
					break;
				case ESC:
					EXIT();
					break;
				case RIGHT_ARROW:
					Menu_Item++;
					if(Menu_Item>5)
						Menu_Item=0;
					break;
				case LEFT_ARROW:
					Menu_Item--;
					if(Menu_Item<0)
						Menu_Item=5;
					break;
				case ENTER:
				case DOWN_ARROW:
					MenuAction(Menu_Item);
					break;
		}

	}
}

void MenuAction(int x)
{
	switch(x)
	{
		case 0:
    //			Home_Menu();
//			break;

		case 1:
       //			Filter_Menu();
			break;
		case 2:
	 //		Search_Menu();
			break;
		case 3:
	   //		Add_Menu();
			break;
		case 4:
			Account_Menu();
			break;
		case 5:
			EXIT();
			break;
		default:
		{
			BEEP();
			Welcome();
		}
       }
}
/*void Home_Menu(void)
{

}
void Product::Add_Menu(void)
{

}   */
void Account_Menu(void)
{
	User u;
	int opt;
	cout<<"1.Create ";
	cout<<"2.
	u.SignUp();
}
void BEEP(void)
{
	sound(666);
	delay(100);
	nosound();
}
void EXIT(void)
{
	textcolor(WHITE);
	textbackground(BLACK);

	_setcursortype(_NORMALCURSOR);
	clrscr();

	exit(1);
}

//--------------------------------------------------------------------------------


/*union REGS reg,i,o;
typedef enum Boolean
{false,true}boolean;
int etat();
int X();
int Y();
void MouseInit();
void MouseOn();
void MouseOff();
int Left();
int Right();
int MouseIn();
void cursor(int x,int y);
void MouseInit()
{
	reg.x.ax=0x00;
	int86(0x33,&i,&o);
}
void MouseOn()
{
	reg.x.ax=0x01;
	int86(0x33,&i,&o);
}
void MouseOff()
{
	reg.x.ax=0x02;
	int86(0x33,&i,&o);
}
int X()
{
	reg.x.ax=0x03;
	int86(0x33,&i,&o);
	return reg.x.cx;
}
int Y()
{
	reg.x.ax=0x03;
	int86(0x33,&i,&o);
	return reg.x.dx;
}
int Left()
{
	reg.x.ax=0x03;
	int86(0x33,&i,&o);
	return (reg.x.bx==1);
}
int Right()
{
	reg.x.ax=0x03;
	int86(0x33,&i,&o);
	return (reg.x.bx==2);
}
int etat(void)
{
	reg.x.ax=0x03;
	int86(0x33,&i,&o);
	return reg.x.bx;
}
int MouseIn(int x1,int x2,int y1,int y2)
{
	reg.x.ax=0x03;
	int86(0x33,&i,&o);
	reg.x.bx=2;
	return ((X()>=x1)&&(X()<=x2)&&(Y()<=y2)&&(Y()>=y1));
}
void cursor(int x,int y)
{
	while(!kbhit())
	{
		setcolor(0);
		outtextxy(x,y,"_");
		delay(150);
		setcolor(9);
		outtextxy(x,y,"__");
		delay(150);
	}
}
int main()
{
	int gd=DETECT,gm,maxx,maxy,button,x,y;
	initgraph(&gd,&gm,"C://TURBOC3//BGI");
	maxx=getmaxx();
	maxy=getmaxy();
	setbkcolor(8);
	setviewport(0,0,maxx,maxy,1);
	gotoxy(26,1);
	rectangle(10,10,200,465);
	setfillstyle(SOLID_FILL,YELLOW);
	floodfill(100,100,WHITE);
	getch();
	cleardevice();
	return 0;
}

  */
