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
    glBindTexture(GL_TEXTURE_2D, *textureID);//Функция glBindTexture позволяет создать именованную текстуру, привязанную к целевому объекту текстуры.
    //настройки Задает параметры текстуры.Целевая текстура, которая должна быть либо GL_TEXTURE_1D, либо GL_TEXTURE_2D.
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,swarp);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,twarp);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,filter);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,filter);
    /*
    GL_TEXTURE_MIN_FILTER-Функция минификации текстур используется всякий раз, когда текстурируемый пиксель сопоставляется с областью,
                                превышающей один элемент текстуры.
    GL_TEXTURE_MAG_FILTER-Функция увеличения текстуры используется, когда текстурируемый пиксель сопоставляется с областью,
                            меньшей или равной одному элементу текстуры.
    GL_TEXTURE_WRAP_S-Задает для параметра wrap для координат текстуры значение GL_CLAMP или GL_REPEAT. GL_CLAMP приводит к тому,
                    что координаты прижаты к диапазону [0,1]
                    и полезны для предотвращения упаковки артефактов при сопоставлении одного изображения с объектом.
    GL_TEXTURE_WRAP_T -Задает параметру wrap для координаты текстуры t значение GL_CLAMP или GL_REPEAT.
         */

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, twidth, thight,
                 0, tcnt == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);//Функция glTexImage2D указывает двухмерное изображение текстуры.
    /*
    0-Номер уровня детализации. Уровень 0 — базовый уровень образа.
    GL_RGBA - Количество компонентов цвета в текстуре. Должно быть 1, 2, 3 или 4 или одна из следующих символьных констант
    0-Ширина границы. Должно быть либо 0, либо 1.
    tcnt-Формат данных пикселей. Это может предположить одно из девяти символьных значений.
    GL_UNSIGNED_BYTE-Тип данных пиксельных данных.
    */
    /*Функция glBindTexture позволяет создать именованную текстуру, привязанную к целевому объекту текстуры.*/
    glBindTexture(GL_TEXTURE_2D, 0);//задание текстуры

    stbi_image_free(data);//освобождение буфера

}

void ShowBackground(GLuint textureID){

    static float svertix[]= {0,0, 648,0, 648,246, 0,246};        //вектор текстурируемого
                                                                    //многоугольника
    static float TexCord[]= {0,1, 1,1, 1,0, 0,0};    // текстурные координаты

    glPushMatrix();//Функции glPushMatrix и glPopMatrix отправляют и помещают текущий стек матрицы.
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
void ShowMap(GLuint textureID){

    static float svertix[]= {0,0, 700,0,700,500, 0,500};        //вектор текстурируемого
                                                                    //многоугольника
    static float TexCord[]= {0,1, 1,1, 1,0, 0,0};    // текстурные координаты


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

}

void ShowWing(GLuint textureID,GLfloat posX,GLfloat posY){

    float svertix[]= {0+posX,0+posY, 115+posX,0+posY, 115+posX,80+posY, 0+posX,80+posY};
    //static float svertix[]= {0,0, 110,0,110,80, 0,80};        //вектор текстурируемого
                                                                    //многоугольника
    static float TexCord[]= {1,0, 0,0, 0,1, 1,1};    // текстурные координаты


                                                                    //изображения
    glEnable(GL_TEXTURE_2D);                     //разрешение использования
                                                                         //текстуры
    glBindTexture(GL_TEXTURE_2D, textureID);

    glEnable(GL_ALPHA_TEST);                          // проверка на элементы α-канала
                                                                             //(не обязательно)
    glAlphaFunc(GL_GREATER, 0.99);                  // задается тип уровня и его
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

    glDisable(GL_ALPHA_TEST); //отключение проверки α-канал
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

}

void Sprite_animation(GLuint texture, int n, int frameLine, float posX, float posY, bool lookRight)
{
    float svertix[]= {0+posX,0+posY, 80+posX,0+posY, 80+posX,80+posY, 0+posX,80+posY};   //(ЛВх,ЛВу)(ПВх,ПВу)(ПНх,ПНу)(ЛНх,ЛНу) //вектор текстурируемого многоугольника
    static float TexCord[]= {0,0, 1,0, 1,1, 0,1};     // текстурные координаты

    glPushMatrix();//Функции glPushMatrix и glPopMatrix отправляют и помещают текущий стек матрицы.
    glEnable(GL_TEXTURE_2D);//разрешение использования текстуры
    glBindTexture(GL_TEXTURE_2D, texture);
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_BLEND);
    glColor4f(1.0f,1.0f,1.0f,1.0f);
    glEnable(GL_ALPHA_TEST); // проверка на элементы α-канала (не обязательно)
    glAlphaFunc(GL_GREATER, 0.99); // задается типе уровня и его числовая граница


    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(2,GL_FLOAT,0,svertix);//используем вектор координат Функция glVertexPointer
                                        //указывает расположение и данные массива координат вершин для использования при отрисовке.
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

void rectangle(float x,float y,float width,float height,GLfloat red,GLfloat green,GLfloat blue)
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glColor3f(red,green,blue); //цвет
    float arr[8]={x,y,x+width,y,x+width,y+height,x,y+height};
    glPushMatrix(); //матрицу в стек
    glVertexPointer(2, GL_FLOAT, 0, arr); //запись координат в VBO
    glEnableClientState(GL_VERTEX_ARRAY); //разрешение
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4); //отрисовка кнопки
    glLineWidth(1); // толщина обводки кнопки
    glDrawArrays(GL_LINE_LOOP,0,4); //отрисовка обводки
    glLoadIdentity();
    glColor3f(1.0f, 1.0f, 1.0f);
    glPopMatrix();//не влияет на цвета
}

