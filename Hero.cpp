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

#include "Hero.h"

#include <time.h>

using namespace std;

class Hero
{
    public:
    float velocity = 2.5;
    float jumpHeight=-10.0;
    float gravity=23.0;
    float posX=512.0;
    float posY=100.0;
    bool isOnFloor = true;
    bool lookRight = true;
    int frameLine = 1;
};

Hero hero;

float frame;

int collisionMap[10][16] = {
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1},
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}

};

float checkCollisionHorizontal(float deltaX, float deltaY, int side){
    int x = floor((hero.posX + 0 + deltaX)/50);
    int y = floor((hero.posY + 111 + deltaY)/50);
    if(collisionMap[y][x] == 2){
        printf("%s\n", "hh");
        collisionMap[y][x] = 0;

    }
    if(collisionMap[y][x+side] == 0 || collisionMap[y][x+side] == 2){
        return hero.velocity;
    } else {
        return 0;
    }
}

int checkCollisionVertical(float deltaX, float deltaY, int side){
    int x = floor((hero.posX - 0 + deltaX)/50);
    int y = floor((hero.posY + 0 + deltaY)/50);
    for(int i = 1; i <= 1; i++){
        if (collisionMap[y][x] == 2){
            printf("%s\n", "vv");
            collisionMap[y][x] = 0;


        } else if(collisionMap[y][x] == 1 || collisionMap[y][x+1] == 1 ){
            return 1;
        } else if(collisionMap[y][x] == 0 ){
            return 0;
        } else {
            return -1;
        }
    }
}


void Player_Move(){


    if(checkCollisionVertical(75,150,0) != 1 && checkCollisionVertical(75,150,1) != 2){
        hero.posY+=hero.gravity/2;
    } else {
        hero.isOnFloor = true;
    }

    if (GetKeyState(VK_UP) < 0 && hero.isOnFloor == true && checkCollisionVertical(75,150,LEFT) == 1 ){

        hero.jumpHeight = 50;
       hero.isOnFloor=false;
        hero.frameLine = JUMP;
        //frame >= 9 ? frame=0 : frame+=0.2;
    }

    if (GetKeyState(VK_RIGHT) < 0 ){
        hero.lookRight = true;
        hero.posX += checkCollisionHorizontal(100, 0.0, 1);
        if(hero.isOnFloor){
            hero.frameLine = WALK;
        }
        frame >= 9 ? frame=0 : frame+=0.2;
    }
    else if (GetKeyState(VK_LEFT) < 0) {
        hero.lookRight = false;
        hero.posX -= checkCollisionHorizontal(0, 0.0, LEFT);

        if(hero.isOnFloor){
            hero.frameLine = WALK;
        }
        frame >= 9 ? frame=0 : frame+=0.2;
    }
    else if (hero.isOnFloor){
        hero.frameLine = STAY;

    }

    if(hero.jumpHeight == -1){
        hero.isOnFloor = true;
    } else if(hero.isOnFloor == false){
        hero.posY -= hero.jumpHeight - hero.gravity;
        hero.jumpHeight -= 1;
    }
}


