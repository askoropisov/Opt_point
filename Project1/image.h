//Этот файл является подключаемой пользовательский библиотекой.
//Так часто делают, чтоб не писать много кода в одном файле
//по сути этот файл отвечает как раз таки за визуализацию твоей ДРП
#pragma once
#include <iostream>
#include <iomanip>
#include "windows.h"
#include <conio.h>
#include "glut.h"                                                       //для графики OpenGL
#include "glaux.h"                                                      //тоже для графики (по-моему, это для 3-д графики)

//кусок, отвечающий за то, чтоб пользовательские библиотеки не подгружались рекурсивно
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glaux.lib")

using namespace std;                                                    // рабочее пространство имен

int n;                                                                  //объявление размера ДРП
int newDRP[1000][1000];                                                 //объявление числового ДРП
char Lboard[1000][1000], Sboard[1000][1000];                            //объявление символьного ДРП


void RenderScene() {                                                    //Это основная функция работы с графикой
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, w1, h1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, w1 / h1, 0.1f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(a, b, -Zoom);                                          //функция, отвещающая за перемещение графического объекта (всей сцены) по 3 осям
    glRotatef(vx, 1, 0, 0);                                             //это 3 функции отвещающие за вращение сцены по 3 осям    
    glRotatef(vy, 0, 1, 0);
    glRotatef(vz, 0, 0, 1);

    for (int i = 0; i < n; i++)                                         //двойным циклом пробегаемся по нашему ДРП
    {
        for (int j = 0; j < n; j++)
        {
            switch (newDRP[i][j])                                       //рассматриваем каждый символ поочередно
            {
            case 0: glBegin(GL_QUADS);		                            //если символ является 0, т.е пустой клеткой, по рисуем на его месте белый квадрат					
                glColor3f(1, 1, 1);                                     //задаем цвет рисунка в формате RGB (если все 1, то это белый)
                glVertex3f(2 * j + 1 - 16.5, -2 * i + 16.5, 2);         //4 строчки отвечающие за 4 вершины квадрата
                glVertex3f(2 * j - 16.5, -2 * i + 16.5, 2);
                glVertex3f(2 * j - 16.5, -2 * i - 1 + 16.5, 2);
                glVertex3f(2 * j + 1 - 16.5, -2 * i - 1 + 16.5, 2);
                glEnd();                                                //конец отрисовки одного объекта
                break;
            case 999: glBegin(GL_QUADS);		                        //если встречаем 999, т.е препятствие, то рисуем красный квадрат				
                glColor3f(1, 0, 0);                                     //задаем красный цвет
                glVertex3f(2 * j + 1 - 16.5, -2 * i + 16.5, 2);
                glVertex3f(2 * j - 16.5, -2 * i + 16.5, 2);
                glVertex3f(2 * j - 16.5, -2 * i - 1 + 16.5, 2);
                glVertex3f(2 * j + 1 - 16.5, -2 * i - 1 + 16.5, 2);
                glEnd();
                break;
            case -5: glBegin(GL_QUADS);		                        //если встречаем 999, т.е препятствие, то рисуем красный квадрат				
                glColor3f(0, 0.5, 0.7);                                     //задаем красный цвет
                glVertex3f(2 * j + 1 - 16.5, -2 * i + 16.5, 2);
                glVertex3f(2 * j - 16.5, -2 * i + 16.5, 2);
                glVertex3f(2 * j - 16.5, -2 * i - 1 + 16.5, 2);
                glVertex3f(2 * j + 1 - 16.5, -2 * i - 1 + 16.5, 2);
                glEnd();
                break;
            case -1: glBegin(GL_QUADS);			                        //если встречаем -1, т.е город, то рисуем зеленую пирамиду. Пирамиду рисуем, потому что просто захотелось нарисовать пирамиду
                //рисуем квадрат как основание пирамиды
                glColor3f(0, 1, 0);                                     //задаем цвет
                glVertex3f(2 * j + 1 - 16.5, -2 * i + 16.5, 2);
                glVertex3f(2 * j - 16.5, -2 * i + 16.5, 2);
                glVertex3f(2 * j - 16.5, -2 * i - 1 + 16.5, 2);
                glVertex3f(2 * j + 1 - 16.5, -2 * i - 1 + 16.5, 2);
                glEnd();
                //рисуем 4 треугольника как стороны пирамиды
                glBegin(GL_TRIANGLES);
                glColor3f(0, 1, 0);
                glVertex3f(2 * j + 1 - 16.5, -2 * i + 16.5, 2);
                glVertex3f(2 * j - 16.5, -2 * i + 16.5, 2);
                glVertex3f(2 * j + 0.5 - 16.5, -2 * i + 16, 3);
                glEnd();

                glBegin(GL_TRIANGLES);
                glColor3f(0, 1, 0);
                glVertex3f(2 * j - 16.5, -2 * i + 16.5, 2);
                glVertex3f(2 * j - 16.5, -2 * i - 1 + 16.5, 2);
                glVertex3f(2 * j + 0.5 - 16.5, -2 * i + 16, 3);
                glEnd();

                glBegin(GL_TRIANGLES);
                glColor3f(0, 1, 0);
                glVertex3f(2 * j - 16.5, -2 * i - 1 + 16.5, 2);
                glVertex3f(2 * j + 1 - 16.5, -2 * i - 1 + 16.5, 2);
                glVertex3f(2 * j + 0.5 - 16.5, -2 * i + 16, 3);
                glEnd();

                glBegin(GL_TRIANGLES);
                glColor3f(0, 1, 0);
                glVertex3f(2 * j + 1 - 16.5, -2 * i - 1 + 16.5, 2);
                glVertex3f(2 * j + 1 - 16.5, -2 * i + 16.5, 2);
                glVertex3f(2 * j + 0.5 - 16.5, -2 * i + 16, 3);
                glEnd();
                break;
            case -2: glBegin(GL_QUADS);		                                //если встречаем -2, т.е точку, то рисуем синюю пирамиду					
                glColor3f(0, 0, 1);                                         //задаем цвет
                glVertex3f(2 * j + 1 - 16.5, -2 * i + 16.5, 2);
                glVertex3f(2 * j - 16.5, -2 * i + 16.5, 2);
                glVertex3f(2 * j - 16.5, -2 * i - 1 + 16.5, 2);
                glVertex3f(2 * j + 1 - 16.5, -2 * i - 1 + 16.5, 2);
                glEnd();
                //пирамида рисуется так же как и прошлая
                glBegin(GL_TRIANGLES);
                glColor3f(0, 0, 1);
                glVertex3f(2 * j + 1 - 16.5, -2 * i + 16.5, 2);
                glVertex3f(2 * j - 16.5, -2 * i + 16.5, 2);
                glVertex3f(2 * j + 0.5 - 16.5, -2 * i + 16, 3);
                glEnd();

                glBegin(GL_TRIANGLES);
                glColor3f(0, 0, 1);
                glVertex3f(2 * j - 16.5, -2 * i + 16.5, 2);
                glVertex3f(2 * j - 16.5, -2 * i - 1 + 16.5, 2);
                glVertex3f(2 * j + 0.5 - 16.5, -2 * i + 16, 3);
                glEnd();

                glBegin(GL_TRIANGLES);
                glColor3f(0, 0, 1);
                glVertex3f(2 * j - 16.5, -2 * i - 1 + 16.5, 2);
                glVertex3f(2 * j + 1 - 16.5, -2 * i - 1 + 16.5, 2);
                glVertex3f(2 * j + 0.5 - 16.5, -2 * i + 16, 3);
                glEnd();

                glBegin(GL_TRIANGLES);
                glColor3f(0, 0, 1);
                glVertex3f(2 * j + 1 - 16.5, -2 * i - 1 + 16.5, 2);
                glVertex3f(2 * j + 1 - 16.5, -2 * i + 16.5, 2);
                glVertex3f(2 * j + 0.5 - 16.5, -2 * i + 16, 3);
                glEnd();
                break;
            case 777: glColor3f(1, 0, 1);	                                    //если встречаем 777 или оптимальную точку, то рисуем большой фиолетовый шар					
                glPushMatrix();                                                 //говорим, что будем рисовать объемный объект
                glTranslatef(2 * j - 16, -2 * i + 16, 3);                       //перемещаемся на некий коэфф
                glutSolidSphere(1, 100, 100);                                   //рисуем сферу, радиуса 1. (остальные 2 аргумента отвечают за то, насколько круглым или угловатым будет шар)
                glPopMatrix();                                                  //закончили работу с трехмерной графикой
                break;
            }
        }
    }
    glutSwapBuffers();                                                          //запомнили все изменения, провели рендеринг
}


void print_termenal_and_barrier()                                               //это функция вывода символьного представления нашего ДРП в консоль. По сути это не графика, но я решил перенести в этот файл
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)                                             //пробегаемся 2 циклом по ДРП
        {
            cout << setw(2) << Lboard[i][j];                                    //выводим каждый элемент матрицы с отступами 
        }
        cout << endl;
    }
}

void print_DRP()                                                                //абсолютно такая же функция.....не помню, зачем я ее вводил, но лучше не удалять
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << setw(2) << Sboard[i][j];
        }
        cout << endl;
    }
}

void Print_newDRP(char Sboard[1000][1000])		                                //Функция превращающая ДРП символьного вида в ДРП числового вида							
{
    /*Сопоставляет каждого символу определенное число.
    Это нужно, т.к не все функции могут работать с символами, а с числами могут*/
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)                                             //Просматриваем каждый элемент символьного ДРП
        {
            if (Sboard[i][j] == '0') newDRP[i][j] = 0;                          
            if (Sboard[i][j] == 'C') newDRP[i][j] = -1;                         //если встречаем С, то задаем его значение = -1
            if (Sboard[i][j] == 'w') newDRP[i][j] = -5;                         //если встречаем w, то задаем его значение = -5
            if (Sboard[i][j] == 'P') newDRP[i][j] = -2;                         //аналогично с остальными символами
            if (Sboard[i][j] == '#') newDRP[i][j] = 999;
            if (Sboard[i][j] == '*') newDRP[i][j] = 777;
        }
    }
    //это нужно как раз для того, чтоб функция RenderScene корректно работала с матрицей
}