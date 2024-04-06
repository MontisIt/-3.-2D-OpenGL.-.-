#include <gl/gl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <malloc.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb-master/stb_image.h"

using namespace std;

typedef struct
{
    float left, right, top, bottom;
} spriteCoord;
spriteCoord vrtcoord;


void LoadTexture(char *filename, GLuint *textureID, GLfloat swarp, GLfloat twarp, GLfloat filter){


    int twidth, thight, tcnt;                         //переменные ширины, высоты,
    unsigned char *data=stbi_load(filename,&twidth,&thight,&tcnt,0);
                                                                // в поле filename прописывается имя
                                                               //файла “image.png”, а файл хранится в
                                                        //директории проекта
    glGenTextures(1, textureID);            //генерация текстуры
    glBindTexture(GL_TEXTURE_2D, *textureID);

    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,swarp); //настройки
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,twarp);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,filter);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,filter);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, twidth, thight,
                 0, tcnt == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0);//задание текстуры
    stbi_image_free(data);//освобождение буфера

}

void ShowBackground(GLuint textureID){

    static float svertix[]= {0,0, 648,0, 648,246, 0,246};        //вектор текстурируемого
                                                                    //многоугольника
    static float TexCord[]= {0,1, 1,1, 1,0, 0,0};    // текстурные координаты

    glPushMatrix();
                                                                    //изображения
    glEnable(GL_TEXTURE_2D);                     //разрешение использования
                                                                         //текстуры
    glBindTexture(GL_TEXTURE_2D, textureID);

    //glEnable(GL_ALPHA_TEST);                          // проверка на элементы α-канала
                                                                             //(не обязательно)
    //glAlphaFunc(GL_GREATER, 0.99);                  // задается тип уровня и его
                                                                              //числовая граница
    glEnableClientState(GL_VERTEX_ARRAY);   //использование вектора
                                                                            //координат
    glEnableClientState(GL_TEXTURE_COORD_ARRAY); //использование
                                                                        //вектора текстурных координат
            //glLoadIdentity();
            //glOrtho(0, rct.right, 0,rct.bottom, 1, -1);
        glVertexPointer(2, GL_FLOAT, 0, svertix);       //используем вектор координат
        glTexCoordPointer(2, GL_FLOAT, 0, TexCord);  //используем вектор
                                                                                 //текстурных координат
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

   // glDisable(GL_ALPHA_TEST); //отключение проверки α-канал
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glPopMatrix();
}

void Sprite_animation(GLuint texture, int n, int frameLine, float posX, float posY, bool lookRight)
{
    float svertix[]= {0+posX,0+posY, 80+posX,0+posY, 80+posX,80+posY, 0+posX,80+posY};   //(ЛВх,ЛВу)(ПВх,ПВу)(ПНх,ПНу)(ЛНх,ЛНу)
    static float TexCord[]= {0,0, 1,0, 1,1, 0,1};

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);//разрешение использования текстуры
    glBindTexture(GL_TEXTURE_2D, texture);
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_BLEND);
    glColor4f(1.0f,1.0f,1.0f,1.0f);
    glEnable(GL_ALPHA_TEST); // проверка на элементы α-канала (не обязательно)
    glAlphaFunc(GL_GREATER, 0.99); // задается типе уровня и его числовая граница


    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(2,GL_FLOAT,0,svertix);
    glTexCoordPointer(2,GL_FLOAT,0,TexCord);

    static float spriteXsize=640;
    static float spriteYsize=240;
    static float charsizey=80;
    static float charsizex=80;

    vrtcoord.left=(charsizex*n)/spriteXsize;
    vrtcoord.right=vrtcoord.left+(charsizex/spriteXsize);
    vrtcoord.top=(charsizey*frameLine)/spriteYsize;
    vrtcoord.bottom=vrtcoord.top+(charsizey/spriteYsize);

    TexCord[5] = TexCord[7] = vrtcoord.bottom;
    TexCord[1] = TexCord[3] = vrtcoord.top;

    if (lookRight)
    {
        TexCord[0] = TexCord[6] = vrtcoord.left;
        TexCord[2] = TexCord[4] = vrtcoord.right;
    }
    else
    {
        TexCord[2] = TexCord[4] = vrtcoord.left;
        TexCord[0] = TexCord[6] = vrtcoord.right;
    }

    glDrawArrays(GL_TRIANGLE_FAN,0,4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_ALPHA_TEST); //отключение проверки α-канал
    glDisable(GL_BLEND);
    glPopMatrix();
   glBindTexture(GL_TEXTURE_2D, 0);
}
