#ifndef TEXTUR_H
#define TEXTUR_H
#include "textur.cpp"


extern GLuint background = 0;
extern GLuint player = 1;
extern GLuint sprait = 2;

void LoadTexture(char *filename, GLuint *textureID, GLfloat swarp, GLfloat twarp, GLfloat filter);
void ShowBackground(GLuint textureID);
void Sprite_animation(GLuint texture, int n, int frameLine, float posX, float posY, bool lookRight);

#endif // TEXTUR_H