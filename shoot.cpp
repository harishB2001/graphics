//This program only works in windows based systems
/*because it uses "windows.h" header file to get the screen resolution-
 -and store it in horizontal and vertical(global variables)*/
#include<string>
#include<sstream>
#include<iostream>
#include<ctime>
#include <math.h>
#include<GL/glut.h>
#include<windows.h>
using namespace std;


void display(); 
void reshape(int w,int h);
void processKeyboardPress(unsigned char key,int x,int y); 
void drawDesign(int flag,int index,float,float,float);
void drawBalloon(float,float,float);
void drawLine();
void drawCone(float, float,float);
void passiveMouseMotion(int , int);
void drawTargetLines(int angle);
void drawGun();
void selectOrder();
void increaseScore(int balloonNumber);
void GetDesktopResolution();
void processMouseClick(int button,int state,int x,int y);
void shooting();
void bigBlack();
void smallBlack();
void brownHold();
void goldSystem();
void gun();
void timer(int);
void recoilTimer(int);
void welcomeScreen();
void printSentences(float lineWidth , float xt ,float yt , char message[]);
void endScreen(int);
void endGameTimer();
void setOrthographicProjection();
void restorePerspectiveProjection();
void fireTimer(int);


float gunZvariable = 0; 
int mList[10][6] = {{1,4,5,0,2,3},{5,0,1,3,4,2},{0,2,1,4,3,5},{1,5,4,2,3,0},{3,4,1,0,5,2},
				 	{3,2,0,5,4,1},{2,4,3,1,0,5},{5,3,4,1,2,0},{0,3,2,4,5,1},{2,5,0,1,4,3}}; //and random array is choosen
float passivex = 0;
float gunRotate = 0;
int m[6] = {0,0,0,0,0,0}; //baloon order to show off from the machine
int hasRaised[6] = {0,0,0,0,0,0};
int order[6] ;
int otv = 1;
float rise[6] = {-5,-5,-5,-5,-5,-5} ;
int lock[6] = {0,0,0,0,0,0};
int current = 0;
float riseSpeed = 0.01;
int evalLock = 1;
int score = 0;
float hasShot[6] ={1,1,1,1,1,1};
float horizontal;
float vertical;
string rinstring;
float mousex = 0;
float mousey = 0;
float recoil ;
float refPoint;
float fire = 0;
float isbullet = 1;
bool canShoot = 1;
int whichScreen = 1;

int main(int argc, char **argv){
	GetDesktopResolution(); //function call to to get screen's horizontal and vertical distances
	char *resolution;
	int size = rinstring.length();
	resolution = (char*)calloc(size,sizeof(char));
	for (int i = 0; i < size; i++) resolution[i] = rinstring[i];
	cout<<"\n The gameModeString is: "<<resolution<<"\n";
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutGameModeString(resolution);
	glutEnterGameMode();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutKeyboardFunc(processKeyboardPress);
	glutSetCursor(GLUT_CURSOR_NONE);
	glutPassiveMotionFunc(passiveMouseMotion);
	glutMouseFunc(processMouseClick);
	if(otv){ //this block executes only once and set the condition to false 
		selectOrder(); //an random array is selected to shoot the balloon
		otv = 0;
		m[order[0]] = 1;
	}
	glutMainLoop();
	return 1;
}
 

 

float count;
void display(){
	glClearColor(0.4,0.6,1.0,0.0);
 	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glLoadIdentity();
	
	//This block displays game scene
	if(whichScreen == 2){

	gluLookAt(	0, 8.0f, 3,
/*refPoint*/	refPoint, 8.0f,  -0.1,
				0.0f, 8.0f,  0.0f);
	glTranslatef(0.0,0.0,0.0);
	
	
	glBegin(GL_QUADS);
	glColor3f(0.3961,0.4,0.1294);
	glVertex3f(-100.0,0.0,-100.0);
	glVertex3f(-100.0,0.0,100.0);
	glVertex3f(100.0,0.0,100.0);
    glVertex3f(100.0,0.0,-100.0);
   	glEnd();

//The red-brown wall 
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(0.5,0.34,0.24);
	glVertex3f(-100,7,-40);
	glVertex3f(-100,0,-40);
	glVertex3f(100,0,-40);
    glVertex3f(100,7,-40);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(0.0,1.0,0.0);
	glTranslatef(0.0,1.0,-5);
	

//balloon machines
	glPushMatrix();
	glTranslatef(-25,0,-30);
	drawDesign(m[0],0,1.0,0.647,0.0);
	glPopMatrix();
 

	glPushMatrix();
	glTranslatef(-15,0,-30);
	drawDesign(m[1],1,1.0,1.0,0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5,0,-30);
	drawDesign(m[2],2,0.0,1.0,1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5,0,-30);
	drawDesign(m[3],3,0.0,1.0,0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15,0,-30);
	drawDesign(m[4],4,1.0,0.0,1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(25,0,-30);
	drawDesign(m[5],5,1.0,1.0,1.0);
	glPopMatrix();
	glPopMatrix();


//draw bullseye
glPushMatrix();
glTranslatef(passivex,6.0,-29);
glScalef(0.3, 0.3, 0.3);
glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= 300; i++) {
        double angle = 2 * M_PI * i / 300;
        double x = cos(angle);
        double y = sin(angle);
        glVertex2d(x, y);
    }
    glEnd();
    for(int i = 45;i<=315;i+=90)
    drawTargetLines(i);
    glPopMatrix();
    
    //position gun
	glPushMatrix();
	float passivePer = (passivex/30.0) * 100.0;
	float zper = 100.0 - ((0.5f * passivePer) + 50.0);
	gunZvariable = ((zper * (-1.44f)) / 100.0f) - 0.06;
   	glTranslatef(4.0,5.5,gunZvariable);
   	glRotatef(90,0.0,-1.0,0.0);
   
   	glPushMatrix();
   	drawGun();
   	glRotatef(gunRotate,0.0,1.0,0.0);
   	glPopMatrix();

	glPopMatrix();
	}
	
	//this block displays starting screen
	if(whichScreen == 1){
		setOrthographicProjection();
		glPushMatrix();
		glLoadIdentity();
		welcomeScreen();
		glPopMatrix();
restorePerspectiveProjection();
	}
	
	//This block displays ending screen
if(whichScreen == 3){
	setOrthographicProjection();
	glPushMatrix();
		glLoadIdentity();
		endGameTimer();
		glPopMatrix();
restorePerspectiveProjection();
}
	glutSwapBuffers();

}
float ratio;
void reshape(int w ,int h){
	 ratio =  w* 1.0 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,w,h);
	gluPerspective(90,ratio,0.1,100.0);
	glMatrixMode(GL_MODELVIEW);}


void processKeyboardPress(unsigned char key,int x,int y){
	
	switch(key){
		case 113 :
			exit(0);
		case 81 :
			exit(0);
		case 32:
			if(whichScreen == 1){
			whichScreen =  2;}
			break;
		}
}



void drawDesign(int flag,int index,float r,float g, float b){
float temprise = rise[index];

if(current<=6){	
glPushMatrix();
glScalef(1.5,1.0,1.5);
glBegin(GL_QUADS);
//front
    glColor3f(1.0,0.0,0.0);
    glVertex3f(-1.0,1.0,1.0);
    glVertex3f(-1.0,-1.0,1.0);
    glColor3f(0.0,0.0,1.0);
    glVertex3f(1.0,-1.0,1.0);
    glColor3f(1.0,1.0,0.0);
    glVertex3f(1.0,1.0,1.0);
    //back
    glColor3f(0.0,1.0,0.0);
    glVertex3f(1.0,1.0,-1.0);
    glColor3f(1.0,1.0,0.0);
    glVertex3f(1.0,-1.0,-1.0);
    glColor3f(1.0,0.0,1.0);
    glVertex3f(-1.0,-1.0,-1.0);
    glColor3f(0.0,1.0,1.0);
    glVertex3f(-1.0,1.0,-1.0);
    //right
    glColor3f(0.0,0.0,1.0);
    glVertex3f(1.0,1.0,1.0);
    glColor3f(0.0,1.0,1.0);
    glVertex3f(1.0,-1.0,1.0);
    glColor3f(1.0,1.0,0.0);
    glVertex3f(1.0,-1.0,-1.0);
    glColor3f(1.0,0.0,1.0);
    glVertex3f(1.0,1.0,-1.0);
    //left
    glColor3f(1.0,1.0,0.0);
    glVertex3f(-1.0,1.0,-1.0);
    glColor3f(1.0,0.0,0.0);
    glVertex3f(-1.0,-1.0,-1.0);
     glColor3f(0.0,1.0,0.0);
    glVertex3f(-1.0,-1.0,1.0);
    glColor3f(0.0,0.0,1.0);
    glVertex3f(-1.0,1.0,1.0);
    //top
    glColor3f(0.0,1.0,1.0);
    glVertex3f(-1.0,1.0,-1.0);
    glVertex3f(-1.0,1.0,1.0);
    glVertex3f(1.0,1.0,1.0);
    glVertex3f(1.0,1.0,-1.0);
    //bottom
    glColor3f(1.0,0.0,1.0);
    glVertex3f(-1.0,-1.0,-1.0);
    glVertex3f(-1.0,-1.0,1.0);
    glVertex3f(1.0,-1.0,1.0);
    glVertex3f(1.0,-1.0,-1.0);

glEnd();
glPopMatrix();
	
	glPushMatrix();
	//This is the black cone
	glTranslatef(0.0,1.5,0.0);
	glRotatef(90,1,0,0);
	glColor3f(0.0,0.0,0.0);
	glutSolidCone(1.5,2,24,24); //This is the black funnel
	glPopMatrix();
	
	if(flag){
		glPushMatrix();
	//balloon to show off from the funnel
	glTranslatef(0.0,temprise,0.0);
	drawCone(r,g,b); 
	drawLine();
	glPopMatrix();
	if(temprise<=0 && lock[index] == 0){
	temprise+=riseSpeed;
	rise[index] = temprise;
	if(temprise == 0)
	lock[index] == 1;
	}
	else if(hasRaised[index] != 1) {
	hasRaised[index]= 1;
	m[order[current+1]] = 1 ;
	riseSpeed+=0.02;
	current+=1;
	}
	}
	}
	}



void drawLine(){
	glPushMatrix();
	glColor3f(0.0,0.0,0.0);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(0.0,4.0,0.0);
	glEnd();
	glPopMatrix();
}



void drawBalloon(float r,float g, float b){
	glPushMatrix();
	glTranslatef(0.0,0,-0.25);
	glColor3f(r,g,b);
	glutSolidSphere(1,100,100);
	glPopMatrix();
}


void drawCone(float r, float g, float b){
glPushMatrix();
glColor3f(r,g,b);
glRotatef(90,1,0,0);
glTranslatef(0.0,0,-5.0);
glutSolidCone(1,2,24,24);
glPushMatrix();
glColor3f(0.0,0.0,0.0);
glTranslatef(0.0,0.0,2.0);
glutSolidTorus(0.1,0.1,100,100);
glPopMatrix();
drawBalloon(r,g,b);
glPopMatrix();
}



double mousePosPer;
void passiveMouseMotion(int x,int y ){
//The gun will rotate with respect to the cursor's positon
mousePosPer = (x*100.0)/horizontal;
if(mousePosPer>=50){
	passivex = (((mousePosPer-50.0)*2.0)*30.0)/100;
	gunRotate =-1.0* ((((mousePosPer-50.0)*2.0)*37.125)/100);
	
}
if(mousePosPer<=50){
	passivex = -1.0*((((50.0-mousePosPer)*2.0)*30.0)/100);
	gunRotate = (((50.0-mousePosPer)*2.0)*37.125)/100;
}
//The camera will rotate with respect to cursor's position
refPoint = (passivex/30.0)*0.3;

}


 void drawTargetLines(int angle){
 	glPushMatrix();
 	glRotatef(angle,0,0,1);
 	glTranslatef(0.3,0.3,0.0);
	glBegin(GL_LINES);
	glVertex2d(1.0,1.0);
 	glVertex2d(0.0,0.0);
 	glEnd();
	glPopMatrix();
 }
 

	

void processMouseClick(int button,int state,int x,int y){
	switch(button | GLUT_DOWN){
		case GLUT_LEFT_BUTTON | GLUT_DOWN:
			if(canShoot && whichScreen<=2 && current == 6){
			fire = 1;
			isbullet = 0;
			PlaySound("gunShot.wav",NULL,SND_ASYNC); //play bullet sound
			shooting();
			}
			
			if(score == 6)
			{
					glutTimerFunc(1500,endScreen,0);
				
				
			}
			break;
			int button = 0;
	}
}
void GetDesktopResolution(){
	//get desktop resolution and store in the variable horizontal and vertical
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
	ostringstream hor;
   	ostringstream ver;
   	hor<<horizontal;
   	ver<<vertical;
   	string hori= hor.str();
   	string verti  = ver.str();
   	cout<<"\n horizontal: "<<horizontal;
   	cout<<"\n vertical: "<<vertical;
   	rinstring=hori+"x"+verti+":32@100";
}


void selectOrder(){
srand(time(0));  // Initialize random number generator.
int random = (rand() % 10); 
for(int i =0;i<=5;i++ )
order[i] = mList[random][i];
cout<<" The Order is : ";
for(int i =0;i<=5;i++ )
cout<<" "<<order[i];

}


void drawGun(){
gun();
}

void shooting(){

	for(float i = 0;i<=1;i+=0.1)
	recoil = i;
	//ALl below if conditions represents the shooting spot of the balloon and the shoot is done with bullseye position
	if(passivex>=-21.7969 && passivex <=-20.3516 && hasShot[0] == 1){increaseScore(0);}   
	if(passivex>=-13.2422 && passivex <=-12.0312 && hasShot[1] == 1){increaseScore(1);}        
	if(passivex>=-4.76562 && passivex <=-3.63281 && hasShot[2] == 1){increaseScore(2);}        
	if(passivex>= 3.63281 && passivex <= 4.76562 && hasShot[3] == 1){increaseScore(3);}       
	if(passivex>= 12.0312 && passivex <= 13.2422 && hasShot[4] == 1){increaseScore(4);}   
	if(passivex>= 20.3516 && passivex <= 21.7969 && hasShot[5] == 1){increaseScore(5);} 
	glutTimerFunc(200,recoilTimer,0);
}

void increaseScore(int balloonNumber){

	
	if(balloonNumber == order[score] && m[balloonNumber] == 1 ){
	m[balloonNumber] = 0;
	rise[balloonNumber] = -5;
	hasShot[balloonNumber] = 0;
	score+=1;
	}
	else
	{
		glutTimerFunc(100,endScreen,0);
	}
	
	}

void gun(){
	glRotatef(gunRotate,0.0,1.0,0.0);
	glTranslatef(recoil,0.0,0.0); 
	bigBlack();
}

void bigBlack(){
//This draws the upper black cylinder of the gun
	GLUquadricObj *p =  gluNewQuadric();
	glRotatef(90,0.0,-1.0,0.0);
	gluQuadricDrawStyle(p,GLU_FILL );
	glColor3f(0.09,0.0,0.0);
	gluCylinder(p,0.2,0.2,4,100,100);

	
	//Small grey cylinder attached to the upper cylinder
	glPushMatrix();
	GLUquadricObj *r =  gluNewQuadric();
	gluQuadricDrawStyle(r,GLU_FILL );
	glTranslatef(0.0,0.0,3.0);
	glColor3f(0.5,0.5,0.5);
	gluCylinder(p,0.21,0.21,0.2,100,100);
	glPopMatrix();
	
	glPushMatrix();
//calling the bottom balck as a child game object 
	smallBlack();
	glPopMatrix();	
	
	glPushMatrix();
	//call to the brown hold of both top and bottom black cylinders
	brownHold();
	glPopMatrix();
	
	//fire spark co-ordinates(during shooting)
	if(fire){
	glPushMatrix();
	glTranslatef(0.1,0.2,4.0);
	glRotatef(180,0,0,1);
 	glBegin(GL_POLYGON);
 	glColor3f(1.0,0.3448,0.0); 
 	
	glVertex2f(0.0,0.5); 	
 	glVertex2f(-0.1,0.2); 	
 	glVertex2f(-0.3,0.3);  	
 	glVertex2f(-0.2,0.15);  
 	glVertex2f(-0.5,0.0); 	
 	
 	glVertex2f(-0.2,-0.15);  
 	glVertex2f(-0.3,-0.3);  
 	glVertex2f(-0.1,-0.2); 	
 	glVertex2f(0.0,-0.5); 	
 	
 	glVertex2f(0.1,-0.2); 	
 	glVertex2f(0.3,-0.3);  
	glVertex2f(0.2,-0.15);  
 	glVertex2f(0.5,0.0); 	

 	glVertex2f(0.2,0.15);  	
  	glVertex2f(0.3,0.3);  
 	glVertex2f(0.1,0.2); 
	  	glEnd();
	glPopMatrix();
	glutTimerFunc(100,fireTimer,0);
	}
}

void smallBlack(){
	//drwas bottom black cylinder of the gun
	glColor3f(0.02,0.0,0.0);
	glTranslatef(0.0,-0.4,0.0);
	GLUquadricObj *q =  gluNewQuadric();
	gluQuadricDrawStyle(q,GLU_FILL );
	gluCylinder(q,0.1,0.1,4,100,100);
	
	//grey cylinder attached to the bottom black cylinder
	glPushMatrix();
	GLUquadricObj *s =  gluNewQuadric();
	gluQuadricDrawStyle(s,GLU_FILL );
	glTranslatef(0.0,0.0,3.0);
	glColor3f(0.5,0.5,0.5);
	gluCylinder(s,0.11,0.11,0.2,100,100);
	glPopMatrix();
	
}


void brownHold(){
	// brown cylinder that hold the black cylinders
	GLUquadricObj *r =  gluNewQuadric();
	gluQuadricDrawStyle(r,GLU_FILL );
	glTranslatef(0.0,-0.1225,0.0);

	glColor3f(0.396,0.263,0.129);
	gluCylinder(r,0.5,0.4,1.5,100,100);

	glPushMatrix();
	goldSystem();
	glPopMatrix();
}


void goldSystem(){
	//golden part of the gun
	GLUquadricObj *r =  gluNewQuadric();
	gluQuadricDrawStyle(r,GLU_FILL );
	glTranslatef(0.0,0.0,-1.403);
	glColor3f(0.7,0.543,0.0);
	gluCylinder(r,0.5,0.5,1.4,100,100);
	
	glPushMatrix();
	GLUquadricObj *h =  gluNewQuadric();
	gluQuadricDrawStyle(r,GLU_FILL );
	glTranslatef(0.25,0.2,0.8);
	glColor3f(0.0,0.0,0.0);
	gluCylinder(h,0.2,0.2,0.5,100,100);
	
	// bullet
	if(isbullet){
	glPushMatrix();
	GLUquadricObj *b =  gluNewQuadric();
	gluQuadricDrawStyle(r,GLU_FILL );
	glTranslatef(0.14,0.1,0.1);
	glColor3f(1.0,0.843,0.0);
	gluCylinder(b,0.05,0.0,0.5,100,100);
	glPopMatrix();
	
	}
	if(!isbullet){
	canShoot = 0;
	glutTimerFunc(500,timer,0);
	}
	glPopMatrix();
}


void timer(int){
	isbullet  = 1;
	canShoot =  1;
	
}

void recoilTimer(int){
	
	recoil = 0;
}

char game[] = "BAllooN SHooTING GAME ";
char createdBy[] = "CREATED BY: ";
char harish[] = "HARISH B";
char instructions[] = "INSTRUCTIONS:";
char iOne[] = "1. Mouse Movement to Rotate Gun";
char iTwo[] = "2. Mouse Left Click To fire";
char iThree[] = "3. 1st balloon out is 1st to shoot";
char iFour[] ="4. q to exit";
char enter[] = "Press SpaceBar to Start The Game";

void welcomeScreen(){

	glClearColor(0.0, 0.0, 0.1, 1.0);
  	glClear(GL_COLOR_BUFFER_BIT);
  	glColor3f(1.0, 1.0, 1.0); 


   	printSentences(3.0 ,450, 2200, game);
  	printSentences(2.0,100,1900,createdBy);
  	printSentences(5.0,100,1700,harish);
  	printSentences(6.0,900,1500,instructions);
  	printSentences(2.0,60,1250,iOne);
  	printSentences(2.0,60,1050,iTwo);
  	printSentences(2.0,60,850,iThree);
  	printSentences(2.0,60,650,iFour);
  	printSentences(1.0,100,200,enter);


	
	
}

void printSentences(float lineWidth , float xt ,float yt , char message[]){
	glPushMatrix();  
	glLineWidth(lineWidth);
  	glTranslatef(xt,yt,0.0);
	for (int i = 0; i < strlen(message); i++) 
    glutStrokeCharacter(GLUT_STROKE_ROMAN, message[i]);
  	glPopMatrix();
	}
	
void endScreen(int)
{
whichScreen = 3;
}

void endGameTimer(){
	
	glClearColor(0.0, 0.0, 0.1, 1.0);
  	glClear(GL_COLOR_BUFFER_BIT);
  	glColor3f(1.0, 1.0, 1.0);  
  
  	
  	char *status;
  	string temp;
  	char *printingScore;
  	char q2e [] = "press q to exit";
  	char tryagain[] = "Try again ! ";
  	bool showtry = false;
	
	if(score  == 6)
	  temp = "Game Completed";
	if(score <6){
	 temp = "Game Over! Wrong balloon was Shot" ;
	 showtry = true;
	 }
	
	int size = temp.length();
	status = (char*)calloc(size,sizeof(char));
	for (int i = 0; i < size; i++) status[i] = temp[i]; 
	
	ostringstream SCORE;
	SCORE<<score;
	temp = "your Game Score is: " + SCORE.str();

	 size = temp.length();
	printingScore = (char*)calloc(size,sizeof(char));
	for (int i = 0; i < size; i++) printingScore[i] = temp[i]; 

  	
	printSentences(2.0,100,1700,status);
	if(showtry)
	printSentences(2.0,100,1500,tryagain);
	printSentences(2.0,100,1300,printingScore);
	printSentences(2.0,700,800,q2e);

	
		

	
}



void restorePerspectiveProjection() {

	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();

	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void setOrthographicProjection() {

	// switch to projection mode
	glMatrixMode(GL_PROJECTION);

	// save previous matrix which contains the
	//settings for the perspective projection
	glPushMatrix();

	// reset matrix
	glLoadIdentity();

	// set a 2D orthographic projection
	gluOrtho2D(0, 2500, 0, 2500);

	// switch back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void fireTimer(int){
fire = 0; 
}

