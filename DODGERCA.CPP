#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <process.h>
#include <dos.h>

void car();
void grass();
void Master();
void obstacle(int,int);
void clearobject(int,int);
void direction();

int POSX,POSY;
int OBS_POSX_1,OBS_POSY_1;
int OBS_POSX_2,OBS_POSY_2;
const int speed = 10;
int maxx,maxy;
int crash = 1;

void Master()
{
	/* request auto detection */
	int gdriver = DETECT, gmode, errorcode;

	/* initialize graphics and local variables */
	initgraph(&gdriver, &gmode, "C:\\turboc3\\bgi");

	/* read result of initialization */
	errorcode = graphresult();
	if (errorcode != grOk)  /* an error occurred */
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1); /* terminate with an error code */
	}
	maxx = getmaxx();
	maxy = getmaxy();
	POSX = maxx/2;
	POSY = maxy-50;
	grass();
	car();
	/*DIRECTION CONTROL*/
	int i = 0;
	while(crash!=0)
	{
		OBS_POSX_1 = 190+random(maxx-370);
		OBS_POSY_1 = 30;
		while(OBS_POSY_1<=maxy)
		{
			obstacle(OBS_POSX_1,OBS_POSY_1);
			delay(speed);
			clearobject(OBS_POSX_1,OBS_POSY_1);
			OBS_POSY_1+=5;
			while(kbhit())
			{
				direction();
			}
			if(POSX-20<=OBS_POSX_1+20&&POSX+20>=OBS_POSX_1-20&&POSY-15<=OBS_POSY_1+40&&POSY+40>=OBS_POSY_1-15)
			{
				crash = 0;
			}
		}
		i++;
	}

	/* clean up */
	closegraph();
}

void grass()
{
	int poly[8];
	/*LEFT GRASS*/
	poly[0] = 0;
	poly[1] = 0;

	poly[2] = 160;
	poly[3] = 0;

	poly[4] = 160;
	poly[5] = maxy;

	poly[6] = 0;
	poly[7] = maxy;

	setcolor(GREEN);
	setfillstyle(SOLID_FILL,GREEN);

	fillpoly(4,poly);

	/*RIGHT GRASS*/
	poly[0] = maxx-160;
	poly[1] = 0;

	poly[2] = maxx;
	poly[3] = 0;

	poly[4] = maxx;
	poly[5] = maxy;

	poly[6] = maxx-160;
	poly[7] = maxy;

	setcolor(GREEN);
	setfillstyle(SOLID_FILL,GREEN);

	fillpoly(4,poly);

	/*ROAD*/
	poly[0] = 160;
	poly[1] = 0;

	poly[2] = maxx-160;
	poly[3] = 0;

	poly[4] = maxx-160;
	poly[5] = maxy;

	poly[6] = 160;
	poly[7] = maxy;

	setcolor(LIGHTGRAY);
	setfillstyle(SOLID_FILL,LIGHTGRAY);

	fillpoly(4,poly);


	setcolor(WHITE);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	outtextxy(10,10,"LEVEL 1");
	outtextxy(10,30,"CONTROLS:");
	outtextxy(10,40,"\'A\'->LEFT");
	outtextxy(10,50,"\'D\'->RIGHT");

	/*BORDER LINE*/
	setcolor(BLACK);
	line(160,0,160,maxy);
	line(maxx-160,0,maxx-160,maxy);
}

void direction()
{
	char dir = getch();

	switch(dir)
	{
	case 'a':
		if(POSX-15<=182)
		{}
		else
		{
			clearobject(POSX,POSY);
			POSX-=15;
			car();
		}
		break;

	case 'd':
		if(POSX+15>=maxx-182)
		{}
		else
		{
			clearobject(POSX,POSY);
			POSX+=15;
			car();
		}

		break;

	case 'e':
		exit(0);
	}
}

void car()
{
	/* our polygon array */
	int poly[8];
	/*HEAD*/
	setcolor(RED);

	poly[0] = POSX-10;
	poly[1] = POSY-15;

	poly[2] = POSX+10;
	poly[3] = POSY-15;

	poly[4] = POSX+20;
	poly[5] = POSY;

	poly[6] = POSX-20;
	poly[7] = POSY;

	/* set fill pattern */
	setfillstyle(SOLID_FILL, RED);

	/* draw a filled polygon */
	fillpoly(4, poly);

	/*MAIN BODY*/

	poly[0] = POSX-20;
	poly[1] = POSY;

	poly[2] = POSX+20;
	poly[3] = POSY;

	poly[4] = POSX+20;
	poly[5] = POSY+40;

	poly[6] = POSX-20;
	poly[7] = POSY+40;

	/* set fill pattern */
	setfillstyle(SOLID_FILL, RED);

	/* draw a filled polygon */
	fillpoly(4, poly);

	/*WINDSCREEN*/

	poly[0] = POSX-8;
	poly[1] = POSY-10;

	poly[2] = POSX+8;
	poly[3] = POSY-10;

	poly[4] = POSX+15;
	poly[5] = POSY-2;

	poly[6] = POSX-15;
	poly[7] = POSY-2;

	/* set fill pattern */
	setfillstyle(SOLID_FILL, CYAN);

	/* draw a filled polygon */
	fillpoly(4, poly);

	/*LEFT WINDOW*/

	poly[0] = POSX-20;
	poly[1] = POSY+10;

	poly[2] = POSX-15;
	poly[3] = POSY+10;

	poly[4] = POSX-15;
	poly[5] = POSY+30;

	poly[6] = POSX-20;
	poly[7] = POSY+30;

	/* set fill pattern */
	setcolor(LIGHTGRAY);
	setfillstyle(SOLID_FILL,LIGHTGRAY);

	/* draw a filled polygon */
	fillpoly(4, poly);

	/*RIGHT WINDOW*/

	poly[0] = POSX+15;
	poly[1] = POSY+10;

	poly[2] = POSX+20;
	poly[3] = POSY+10;

	poly[4] = POSX+20;
	poly[5] = POSY+30;

	poly[6] = POSX+15;
	poly[7] = POSY+30;

	/* set fill pattern */
	setcolor(LIGHTGRAY);
	setfillstyle(SOLID_FILL, LIGHTGRAY);

	/* draw a filled polygon */
	fillpoly(4, poly);

	/*TAIL*/
	setcolor(LIGHTGRAY);
	setfillstyle(SOLID_FILL, BROWN);
	pieslice(POSX,POSY+40,0,180,10);
}

void obstacle(int POSX,int POSY)
{
	/* our polygon array */
	int poly[8];
	/*HEAD*/

	poly[0] = POSX-10;
	poly[1] = POSY-15;

	poly[2] = POSX+10;
	poly[3] = POSY-15;

	poly[4] = POSX+20;
	poly[5] = POSY;

	poly[6] = POSX-20;
	poly[7] = POSY;

	setcolor(YELLOW);
	/* set fill pattern */
	setfillstyle(SOLID_FILL, YELLOW);

	/* draw a filled polygon */
	fillpoly(4, poly);

	/*MAIN BODY*/

	poly[0] = POSX-20;
	poly[1] = POSY;

	poly[2] = POSX+20;
	poly[3] = POSY;

	poly[4] = POSX+20;
	poly[5] = POSY+40;

	poly[6] = POSX-20;
	poly[7] = POSY+40;

	/* set fill pattern */
	setfillstyle(SOLID_FILL, YELLOW);

	/* draw a filled polygon */
	fillpoly(4, poly);

	/*WINDSCREEN*/

	poly[0] = POSX-8;
	poly[1] = POSY-10;

	poly[2] = POSX+8;
	poly[3] = POSY-10;

	poly[4] = POSX+15;
	poly[5] = POSY-2;

	poly[6] = POSX-15;
	poly[7] = POSY-2;

	/* set fill pattern */
	setfillstyle(SOLID_FILL, CYAN);

	/* draw a filled polygon */
	fillpoly(4, poly);

	/*LEFT WINDOW*/

	poly[0] = POSX-20;
	poly[1] = POSY+10;

	poly[2] = POSX-15;
	poly[3] = POSY+10;

	poly[4] = POSX-15;
	poly[5] = POSY+30;

	poly[6] = POSX-20;
	poly[7] = POSY+30;

	/* set fill pattern */
	setcolor(LIGHTGRAY);
	setfillstyle(SOLID_FILL,LIGHTGRAY);

	/* draw a filled polygon */
	fillpoly(4, poly);

	/*RIGHT WINDOW*/

	poly[0] = POSX+15;
	poly[1] = POSY+10;

	poly[2] = POSX+20;
	poly[3] = POSY+10;

	poly[4] = POSX+20;
	poly[5] = POSY+30;

	poly[6] = POSX+15;
	poly[7] = POSY+30;

	/* set fill pattern */
	setcolor(LIGHTGRAY);
	setfillstyle(SOLID_FILL, LIGHTGRAY);

	/* draw a filled polygon */
	fillpoly(4, poly);

	/*TAIL*/
	setcolor(LIGHTGRAY);
	setfillstyle(SOLID_FILL, BROWN);
	pieslice(POSX,POSY+40,0,180,10);
}

void clearobject(int POSX,int POSY)
{
	int poly[8];

	poly[0] = POSX-20;
	poly[1] = POSY-20;

	poly[2] = POSX+20;
	poly[3] = POSY-20;

	poly[4] = POSX+20;
	poly[5] = POSY+40;

	poly[6] = POSX-20;
	poly[7] = POSY+40;

	setcolor(LIGHTGRAY);
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	fillpoly(4,poly);
}

void main()
{
	Master();
}
