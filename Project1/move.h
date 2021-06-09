//Этот файл является подключаемой пользовательский библиотекой.
//Так часто делают, чтоб не писать много кода в одном файле
//Он отвечает за малипуляцию получееного графического объектра с клавиатуры
#pragma once
#include <iostream>
#include <iomanip>
#include "windows.h"
#include <conio.h>
#include "glut.h"
#include "glaux.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glaux.lib")


double w1 = 600.0, h1 = 600.0;							//размер окна графики по умолчанию
float vx = 0.0, vy = 0.0, vz = 0.0;						// углы поворота по каждой оси по умолчанию
double Zoom = 70.0;										//отдаление по умолчанию (коорд-та по z)
double a, b;											// коор-ты изображения по х и у


void Read_kb(unsigned char key, int, int)				// функция восприятия нажатий на клавиши пользователем
{
	//проверяем нажатую клавифу. Если она равно какому-то из следующий символов, то
	if (key == 's')
		vx -= 2.0;										//вращаем по х
	if (key == 'w')
		vx += 2.0;
	if (key == 'a')
		vy -= 2.0;										//вращаем по у
	if (key == 'd')
		vy += 2.0;
	if (key == '1')
		vz -= 2.0;										//вращаем по  z
	if (key == '3')
		vz += 2.0;
	if (key == '+')										//приближаем
		Zoom -= 2.0;
	if (key == '-')										//отдаляем
		Zoom += 2.0;
	if (key == 27)
		exit(0);										//на клавишу эскейп программа закроется
	glutPostRedisplay();								//что-то типа "Объявляем функцию доверительной
}

void  ReadSpec(int key, int, int)						// восприятия нажатий на специальные клавиши пользователем
{
	//перемещение сцены по х и у стрелочками
	if (key == GLUT_KEY_UP)
		b += 1.0;
	if (key == GLUT_KEY_DOWN)
		b -= 1.0;
	if (key == GLUT_KEY_RIGHT)
		a += 1.0;
	if (key == GLUT_KEY_LEFT)
		a -= 1.0;
	glutPostRedisplay();								//что-то типа "Объявляем функцию доверительной
}

void reshape(int w, int h)								//какая-то обязательная функция для правильно отрисовки окна
{
	//ширина и высота окна
	w1 = w;
	h1 = h;
	glutPostRedisplay();
}
