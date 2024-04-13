#include <gl/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string>


#define nameLen 20
#include "stb-master/stb_easy_font.h"

using namespace std;

typedef struct
{
    char name[nameLen];
    float vert[8];
    char isHover, isDown;
    //text
    float buffer[50*nameLen];// для координат примитивов
    int num_quads;
    float textPosX,textPosY,textS; // координаты расположения текста и
   //масштабный коэфициент
   int id;
} Button;

Button *btn;
int  btnCnt = 0;




float mouseX,mouseY;
bool gameState;
int window=-1;



int Menu_AddButton(char *name, int id, float x, float y, float width, float height, float textS)
{
    btnCnt++;
    btn = (Button*)realloc(btn, sizeof(btn[0])*btnCnt); //выделяем память под нужное
    //количество

    snprintf(btn[btnCnt-1].name, nameLen, "%s", name); //выделение памяти и запись
                                                        //имени
    float *vert = btn[btnCnt-1].vert; //передача координат кнопки
    vert[0]=vert[6]=x;
    vert[2]=vert[4]=x+width;
    vert[1]=vert[3]=y;
    vert[5]=vert[7]=y+height;
    btn[btnCnt-1].isHover=0;
    btn[btnCnt-1].isDown=0;
    btn[btnCnt-1].id=id;


    Button *b= btn + btnCnt - 1;//записываем в буфер данные кнопки
    b->num_quads = stb_easy_font_print(0, 0, name,0,b->buffer, sizeof(b->buffer)); // запись
                                                                                    //координат вершин элементов имени
    b->textPosX = x +(width-stb_easy_font_width(name)*textS)/2.0;
    b->textPosY = y +(height-stb_easy_font_height(name)*textS)/2.0;
    b->textPosY+= textS*2;
    b->textS = textS;



    return btnCnt-1;
}

void ShowButton(int buttonId)
{

    Button btn1 = btn[buttonId];//пересылка всех данных в буфер
    glVertexPointer(2, GL_FLOAT, 0, btn1.vert);//запись координат в VBO //разрешение

    glEnableClientState(GL_VERTEX_ARRAY);

        if(btn1.isDown){
                glColor3f(0.2,0.2,0.2);
        }//цвет кнопки
        else if (btn1.isHover){
                glColor3f(0.7,0.7,0.7);
        }
        else {
                glColor3f(0.6,0.6,0.6);
        }

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);//отрисовка кнопки

    glColor3f(1,1,1); //цвет обводки
    glLineWidth(5);// толщина обводки кнопки
    glDrawArrays(GL_LINE_LOOP,0,4);//отрисовка обводки
    glDisableClientState(GL_VERTEX_ARRAY);

    glPushMatrix();//матрицу в стек
        glColor3f(1,1,1);
        glTranslatef(btn1.textPosX,btn1.textPosY,0);//перенос матрицы для отрисовки текста
        glScalef(btn1.textS,btn1.textS,0);//масштабирование текста
        glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(2, GL_FLOAT, 16, btn1.buffer);
            glDrawArrays(GL_QUADS, 0, btn1.num_quads*4);
        glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
}


char isCordInButton(int buttonID, float x, float y)
{
    float *vert=btn[buttonID].vert;
    return ((x>vert[0]) && (x<vert[4]) && (y>vert[1])  && (y<vert[5]));
}


int Menu_MouseMove (float x, float y)
{

    mouseX = x;
    mouseY = y;
    int movebtn=-1;
    for (int i=0; i<btnCnt; i++)
        if (isCordInButton(i, mouseX, mouseY))
        {
            btn[i].isHover =1;
            movebtn = i;
        }
        else
        {
            btn[i].isDown=0;
            btn[i].isHover=0;
        }

    return movebtn;
}

int Menu_MouseDown()
{
    int downbtn=-1;
    for (int i=0; i<btnCnt; i++)
        if (isCordInButton(i, mouseX, mouseY))
        {
            btn[i].isDown =1;
            downbtn = btn[i].id;
        }
    return downbtn;
}

void Menu_MouseUp(){
for (int i=0; i < btnCnt; i++)
    btn[i].isDown=0;
}

char *Menu_GetButtonName(int buttonID)
{
return btn[buttonID].name;
}

void Menu_Clear()
{
    btnCnt=0;
    free(btn);
    btn=0;
}



void init_Sprite_sheet(){
    Menu_AddButton("Back", 4, 30,50, 300,50, 5);
}


void init_Buttons_menu(){
    Menu_AddButton("Start",         0,   200,90, 340,50, 5);
    Menu_AddButton("Sprite sheet",  1,   200,160, 340,50, 5);
    Menu_AddButton("Test move",     2,   200,230, 340,50, 5);
    Menu_AddButton("Exit",          3,   200,300, 340,50, 5);
}





void MouseDown()
{
    int buttonId = Menu_MouseDown();
    if(buttonId<0) return;
    char *name = Menu_GetButtonName(buttonId);
    //printf("%i\n",name," ", buttonId);
    switch (buttonId)
    {
    case 0:
        //window=0;
        window=0;
        Menu_Clear();

        break;

    case 1:

        window=1;
        Menu_Clear();
        init_Sprite_sheet();
        //printf("%s\n","1");
        break;

    case 2:
        window=2;
        Menu_Clear();
        init_Sprite_sheet();
        break;

    case 3:
        PostQuitMessage(0);
        break;

    case 4:
        window=-1;
        Menu_Clear();
        init_Buttons_menu();
        break;




    }

}





