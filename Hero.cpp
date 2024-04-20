#include <gl/gl.h>
#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <malloc.h>




#define WALK 0
#define STAY 1
#define JUMP 2
#define RIGHT 0
#define LEFT 1


#include <time.h>
#include "Hero.h"


using namespace std;

typedef struct
{
    public:
    float velocity = 2.5;
    int jumpHeight=-10;
    int gravity=24;
    float posX=100.0;
    float posY=200.0;
    bool isOnFloor = true;
    bool lookRight = true;
    int frameLine = 0;
}Hero;

Hero hero;

float frame;

 bool get_right=false;
 bool get_left=false;
 bool get_jump=false;

int collisionMap[10][18] = {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1},
    { 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1},
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},




};

float checkCollisionHorizontal(){
    int x_rd = floor((hero.posX + 40)/40);//ÏÍ
    int y_rd = floor((hero.posY + 40)/40);

    int x_rup = floor((hero.posX + 40)/40);//ÏÂ
    int y_rup = floor((hero.posY + 0)/40);

    int x_ld = floor((hero.posX + 0)/40);//ËÍ
    int y_ld = floor((hero.posY + 40)/40);

    int x_lup = floor((hero.posX + 0)/40);//ËÂ
    int y_lup = floor((hero.posY + 0)/40);

        //cout<<"checkCollisionHorizontal [y][x]:"<<collisionMap[y][x]<<"\n";
        //cout<<"checkCollisionHorizontal [y][x+side]:"<<collisionMap[y][x+side]<<"\n";
        //cout<<"checkCollisionHorizontal [y][x-side]:"<<collisionMap[y_ld][x_ld-1]<<"\n";
        //cout<<"checkCollisionHorizontal y="<<y<<" x="<<x<<"\n";

        // cout<<"checkcollisionvertical y="<<y<<" x="<<x<<endl;
        //cout<<"checkcollisionvertical y2="<<y_2<<" x2="<<x_2<<endl;
        //cout<<"checkcollisionvertical y_ld="<<y_ld<<" x_ld="<<x_ld<<endl;
        //cout<<"checkcollisionvertical y_lup="<<y_lup<<" x_lup="<<x_lup<<endl;


    if(collisionMap[y_rup][x_rup+1] == 0 && collisionMap[y_rd][x_rd+1] == 0 && get_right==true){
        //cout<<"if";
        return hero.velocity;
    }else if(collisionMap[y_lup][x_lup-1] == 0 && collisionMap[y_ld][x_ld-1] == 0 && get_left==true){
        //cout<<"if2";
        return hero.velocity;
    }else  if (collisionMap[y_rup][x_rup+1] == 1 || collisionMap[y_rd][x_rd+1] == 1){
         // cout<<"else if 3";
        return 0;
    }
    else   if (collisionMap[y_lup][x_lup-1] == 1 || collisionMap[y_ld][x_ld-1] == 1){
         //cout<<"else if 4";
        return 0;
    }
    else
         //cout<<"WARNING!";
        return 0;
}

int checkCollisionVertical(){
    int x_rd = floor((hero.posX + 40)/40);//ÏÍ
    int y_rd = floor((hero.posY + 40)/40);

    int x_rup = floor((hero.posX + 40)/40);//ÏÂ
    int y_rup = floor((hero.posY + 0)/40);

    int x_ld = floor((hero.posX + 0)/40);//ËÍ
    int y_ld = floor((hero.posY + 40)/40);

    int x_lup = floor((hero.posX + 0)/40);//ËÂ
    int y_lup = floor((hero.posY + 0)/40);

        //cout<<"checkCollisionVertical [y][x]:" <<collisionMap[y][x]<<endl;
        //cout<<"checkCollisionVertical [y-2][x]:"<<collisionMap[y-2][x]<<endl;
        //cout<<"checkCollisionVertical [y+1][x]: "<<collisionMap[y+1][x]<<endl;
        //cout<<"checkcollisionvertical y_rd ="<<y_rd <<" x="<<x_rd <<endl;
        //cout<<"checkcollisionvertical y2="<<y_2<<" x2="<<x_2<<endl;
        //cout<<"checkcollisionvertical y_ld="<<y_ld<<" x_ld="<<x_ld<<endl;
        //cout<<"checkcollisionvertical y4="<<y_4<<" x4="<<x_4<<endl;

        if(collisionMap[y_rd][x_rd] == 0 && collisionMap[y_ld][x_ld] == 0  &&
           collisionMap[y_rd+1][x_rd] == 0 && collisionMap[y_ld+1][x_ld] == 0){
           //cout<<"if";
            return 0;
        }

        if(collisionMap[y_rup][x_rup] == 0 && collisionMap[y_lup][x_lup] == 0  &&
           collisionMap[y_rup-2][x_rd] == 1 || collisionMap[y_lup-2][x_ld] == 1){
            //cout<<"if3";
            return 2;
        }

        if(collisionMap[y_rd][x_rd] == 0 && collisionMap[y_ld][x_ld] == 0  &&
           collisionMap[y_rd+1][x_rd] == 1 || collisionMap[y_ld+1][x_ld] == 1){
            //cout<<"if2";


                return 1;
        }
        else
           // cout<<"WARNING!";
            return 0;

}


void Player_Move(){


    if (checkCollisionVertical() == 0) {
        hero.posY+=hero.gravity/2;
    }
    else{
        hero.posY=(floor((hero.posY + 40)/40))*50-80;
        hero.isOnFloor = true;
    }


    if (GetKeyState(VK_RIGHT) < 0 ){
        hero.lookRight = true;
         get_right=true;
        hero.posX += checkCollisionHorizontal();

        if(hero.isOnFloor){
            hero.frameLine = WALK;
        }

            frame >= 9 ? frame=0 : frame+=0.2;
    }else
        get_right=false;
    if (GetKeyState(VK_LEFT) < 0) {
        hero.lookRight = false;
        get_left=true;
        hero.posX -= checkCollisionHorizontal();


        if(hero.isOnFloor){
            hero.frameLine = WALK;
        }

            frame >= 9 ? frame=0 : frame+=0.2;
    }else
       get_left=false;
    if (GetKeyState(VK_UP) < 0 && hero.isOnFloor == true && checkCollisionVertical() == 1 ){

        get_jump=true;

        //if (checkCollisionHorizontal(80, 80, 1)==0)
            //hero.jumpHeight = 55;
        //else
        hero.jumpHeight = 50;
        hero.isOnFloor = false;
        hero.frameLine = JUMP;
        //hero.posY+=hero.gravity/2;
    }else
        get_jump=false;


   if (hero.isOnFloor){
        hero.frameLine = WALK;

    }


    if(hero.isOnFloor == false){
        hero.posY -= hero.jumpHeight - hero.gravity;
        hero.jumpHeight -= 1;
        //cout<<hero.posY<<"\n";
    }

    if(get_jump==false && get_left==false && get_right==false){
        hero.frameLine = STAY;
        frame >= 9 ? frame=0 : frame+=0.08;
    }



}



void LoadWing()
{
    // calculate dimensions
    unsigned int height = 10;
    unsigned int width  = 18;
    float unit_width    = 700 / width;
    float unit_height   = 500 / height;

    for (unsigned int y = 2; y < height-3; ++y)
    {
        for (unsigned int x = 1; x < width-1; ++x)
        {
            // check block type from level data (2D level array)
            if (collisionMap[y][x] == 1 && collisionMap[y][x+1] == 1) // solid
            {

               // glTranslated(unit_width * x - 70, unit_height * y,0);
                //ShowWing(wing,x,y,unit_width * x - 70,unit_height * y);

                ShowWing(wing,unit_width * (x),unit_height * (y-1.7));

                //rectangle(unit_width * (x),unit_height * (y-1.7),5,5,1,1,1);
                //rectangle(hero.posX+80,hero.posY,5,5,1,1,1);
                //rectangle(hero.posX,hero.posY+80,5,5,1,1,1);
                //rectangle(hero.posX+80,hero.posY+80,5,5,1,1,1);

                x+=1;

            }
        }
    }
}
