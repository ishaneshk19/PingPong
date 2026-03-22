#include<iostream>
#include<graphics.h>
#include<thread>



using namespace std;
void runGame();
void gameOver();

bool isRunning=0;
   // paddle's position id defined
   int x1L=20;
   int y1L=200;
   int x2L=20;
   int y2L=300;

   int x1R=780;
   int y1R=200;
   int x2R=780;
   int y2R=300;

   //ball's center
   int cx=400;
   int cy=300;

   int noOfCollision=0;

     int yi=20;



void makePaddle(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        // Plot the pixel at (x1, y1)
        putpixel(x1, y1, WHITE);

        // Break if the end point is reached
        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}
// void makePaddlesRight(int x1,int y1,int x2,int y2){
//     //bresenham's algorithm
// }

void makeCircle(int x1, int y1, int radius) {
    int x = radius, y = 0;
    int err = 1 - radius; // Decision parameter

    // The circle's symmetric points in all 8 octants



    while (x >= y){
        // Plot the points
        putpixel(x1 + x, y1 + y, WHITE); // (x + x1, y + y1)
        putpixel(x1 + y, y1 + x, WHITE); // (y + x1, x + y1)
        putpixel(x1 - y, y1 + x, WHITE); // (-y + x1, x + y1)
        putpixel(x1 - x, y1 + y, WHITE); // (-x + x1, y + y1)
        putpixel(x1 - x, y1 - y, WHITE); // (-x + x1, -y + y1)
        putpixel(x1 - y, y1 - x, WHITE); // (-y + x1, -x + y1)
        putpixel(x1 + y, y1 - x, WHITE); // (y + x1, -x + y1)
        putpixel(x1 + x, y1 - y, WHITE); // (x + x1, -y + y1)

        // Check for decision
        y++;

        if (err <= 0) {
            err += 2 * y + 1; // Move in the y direction
        } else {
            x--;
            err += 2 * (y - x + 1); // Move in the x and y direction
        }
    }
}

void gameLoop() {
    while (isRunning) {
        cleardevice();
        makePaddle(x1L, y1L, x2L, y2L);
        makePaddle(x1R, y1R, x2R, y2R);
        makeCircle(cx, cy, 5);
        delay(50);
    }
}






// Player 1 Up
void player1Up() {
    while (isRunning) {
        if (GetAsyncKeyState('W') & 0x8000) { // W Key

            if(y1L>=0){

            y1L-=yi;
            y2L-=yi;
            delay(100);
        }
        }
        }
    }


// Player 1 Down
void player1Down() {
    while (isRunning) {
        if (GetAsyncKeyState('S') & 0x8000) { // S Key
            if (y2L < 600) {
                y1L += yi;
                y2L += yi;
                delay(100);
            }
        }
    }
}

// Player 2 Up
void player2Up() {
    while (isRunning) {
        if (GetAsyncKeyState(VK_UP) & 0x8000) { // Up Arrow Key
            if (y1R > 0) {
                y1R -= yi;
                y2R -= yi;
                delay(100);
            }
        }
    }
}

// Player 2 Down
void player2Down() {
    while (isRunning) {
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) { // Down Arrow Key
            if (y2R < 600) {
                y1R +=yi;
                y2R += yi;
                delay(100);
            }
        }
    }
}









void moveBall() {
       cx=400;
       cy=300;

    int dx = 2, dy =2;
    while (isRunning) {
            if(noOfCollision==4){
                dx+=1;
                dy+=1;
                noOfCollision=0;
            }
        cx += dx;
        cy += dy;

        if (cx<=x1L || cx>=x1R){

            if ((cy>=y1L && cy<=y2L) ||  (cy>=y1R && cy<=y2R) ){
                dx=-dx;
                noOfCollision++;
            }
        }

        // Ball Collision with Walls

        if (cy <= 0 || cy >= 600) dy = -dy;

        if (cx <= 0 || cx >= 800) {
                  isRunning = 0;
            // Stop the game when the ball reaches the edge
            gameOver();

            //enterChoice();
           int  key=getch();
            if (key==13){
                gameLoop() ;
            }

            else  break;
        }

        delay(10);
    }
}
 void gameOver(){
      cleardevice();
       // isRunning = 0;
      settextstyle(SANS_SERIF_FONT,HORIZ_DIR,5);
      outtextxy(250,200,"GAME OVER!");
      delay(2000);
      runGame();
 }




 void enterChoice(){

    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,5);
     outtextxy(50,200,"MULTIPLAYER PADDLE GAME");


     settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);
     rectangle(360,250,440,280);
    outtextxy(365,255,"START");

    rectangle(360,280,440,310);
    outtextxy(365,285," EXIT");

    while(isRunning==0){
     if (ismouseclick(WM_LBUTTONDOWN)){

        int x,y;
        getmouseclick(WM_LBUTTONDOWN,x,y);

        cout<<"x="<<x<<"y="<<y;
       // if (x>=50 && x<=122 && y<=271 && y>=252){
        if (x>=360 && x<=440 && y<=280 && y>=250){

            cout<<"Hurray";
            isRunning=1;
        }
          if (x>=360 && x<=440 && y<=