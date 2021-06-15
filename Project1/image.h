//���� ���� �������� ������������ ���������������� �����������.
//��� ����� ������, ���� �� ������ ����� ���� � ����� �����
//�� ���� ���� ���� �������� ��� ��� ���� �� ������������ ����� ���
#pragma once
#include <iostream>
#include <iomanip>
#include "windows.h"
#include <conio.h>
#include "glut.h"                                                       //��� ������� OpenGL
#include "glaux.h"                                                      //���� ��� ������� (��-�����, ��� ��� 3-� �������)

//�����, ���������� �� ��, ���� ���������������� ���������� �� ������������ ����������
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glaux.lib")

using namespace std;                                                    // ������� ������������ ����

int n;                                                                  //���������� ������� ���
int newDRP[1000][1000];                                                 //���������� ��������� ���
char Lboard[1000][1000], Sboard[1000][1000];                            //���������� ����������� ���


void RenderScene() {                                                    //��� �������� ������� ������ � ��������
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, w1, h1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, w1 / h1, 0.1f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(a, b, -Zoom);                                          //�������, ���������� �� ����������� ������������ ������� (���� �����) �� 3 ����
    glRotatef(vx, 1, 0, 0);                                             //��� 3 ������� ���������� �� �������� ����� �� 3 ����    
    glRotatef(vy, 0, 1, 0);
    glRotatef(vz, 0, 0, 1);

    for (int i = 0; i < n; i++)                                         //������� ������ ����������� �� ������ ���
    {
        for (int j = 0; j < n; j++)
        {
            switch (newDRP[i][j])                                       //������������� ������ ������ ����������
            {
            case 0: glBegin(GL_QUADS);		                            //���� ������ �������� 0, �.� ������ �������, �� ������ �� ��� ����� ����� �������					
                glColor3f(1, 1, 1);                                     //������ ���� ������� � ������� RGB (���� ��� 1, �� ��� �����)
                glVertex3f(2 * j + 1 - 16.5, -2 * i + 16.5, 2);         //4 ������� ���������� �� 4 ������� ��������
                glVertex3f(2 * j - 16.5, -2 * i + 16.5, 2);
                glVertex3f(2 * j - 16.5, -2 * i - 1 + 16.5, 2);
                glVertex3f(2 * j + 1 - 16.5, -2 * i - 1 + 16.5, 2);
                glEnd();                                                //����� ��������� ������ �������
                break;
            case 999: glBegin(GL_QUADS);		                        //���� ��������� 999, �.� �����������, �� ������ ������� �������				
                glColor3f(1, 0, 0);                                     //������ ������� ����
                glVertex3f(2 * j + 1 - 16.5, -2 * i + 16.5, 2);
                glVertex3f(2 * j - 16.5, -2 * i + 16.5, 2);
                glVertex3f(2 * j - 16.5, -2 * i - 1 + 16.5, 2);
                glVertex3f(2 * j + 1 - 16.5, -2 * i - 1 + 16.5, 2);
                glEnd();
                break;
            case -5: glBegin(GL_QUADS);		                        //���� ��������� 999, �.� �����������, �� ������ ������� �������				
                glColor3f(0, 0.5, 0.7);                                     //������ ������� ����
                glVertex3f(2 * j + 1 - 16.5, -2 * i + 16.5, 2);
                glVertex3f(2 * j - 16.5, -2 * i + 16.5, 2);
                glVertex3f(2 * j - 16.5, -2 * i - 1 + 16.5, 2);
                glVertex3f(2 * j + 1 - 16.5, -2 * i - 1 + 16.5, 2);
                glEnd();
                break;
            case -1: glBegin(GL_QUADS);			                        //���� ��������� -1, �.� �����, �� ������ ������� ��������. �������� ������, ������ ��� ������ ���������� ���������� ��������
                //������ ������� ��� ��������� ��������
                glColor3f(0, 1, 0);                                     //������ ����
                glVertex3f(2 * j + 1 - 16.5, -2 * i + 16.5, 2);
                glVertex3f(2 * j - 16.5, -2 * i + 16.5, 2);
                glVertex3f(2 * j - 16.5, -2 * i - 1 + 16.5, 2);
                glVertex3f(2 * j + 1 - 16.5, -2 * i - 1 + 16.5, 2);
                glEnd();
                //������ 4 ������������ ��� ������� ��������
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
            case -2: glBegin(GL_QUADS);		                                //���� ��������� -2, �.� �����, �� ������ ����� ��������					
                glColor3f(0, 0, 1);                                         //������ ����
                glVertex3f(2 * j + 1 - 16.5, -2 * i + 16.5, 2);
                glVertex3f(2 * j - 16.5, -2 * i + 16.5, 2);
                glVertex3f(2 * j - 16.5, -2 * i - 1 + 16.5, 2);
                glVertex3f(2 * j + 1 - 16.5, -2 * i - 1 + 16.5, 2);
                glEnd();
                //�������� �������� ��� �� ��� � �������
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
            case 777: glColor3f(1, 0, 1);	                                    //���� ��������� 777 ��� ����������� �����, �� ������ ������� ���������� ���					
                glPushMatrix();                                                 //�������, ��� ����� �������� �������� ������
                glTranslatef(2 * j - 16, -2 * i + 16, 3);                       //������������ �� ����� �����
                glutSolidSphere(1, 100, 100);                                   //������ �����, ������� 1. (��������� 2 ��������� �������� �� ��, ��������� ������� ��� ��������� ����� ���)
                glPopMatrix();                                                  //��������� ������ � ���������� ��������
                break;
            }
        }
    }
    glutSwapBuffers();                                                          //��������� ��� ���������, ������� ���������
}


void print_termenal_and_barrier()                                               //��� ������� ������ ����������� ������������� ������ ��� � �������. �� ���� ��� �� �������, �� � ����� ��������� � ���� ����
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)                                             //����������� 2 ������ �� ���
        {
            cout << setw(2) << Lboard[i][j];                                    //������� ������ ������� ������� � ��������� 
        }
        cout << endl;
    }
}

void print_DRP()                                                                //��������� ����� �� �������.....�� �����, ����� � �� ������, �� ����� �� �������
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

void Print_newDRP(char Sboard[1000][1000])		                                //������� ������������ ��� ����������� ���� � ��� ��������� ����							
{
    /*������������ ������� ������� ������������ �����.
    ��� �����, �.� �� ��� ������� ����� �������� � ���������, � � ������� �����*/
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)                                             //������������� ������ ������� ����������� ���
        {
            if (Sboard[i][j] == '0') newDRP[i][j] = 0;                          
            if (Sboard[i][j] == 'C') newDRP[i][j] = -1;                         //���� ��������� �, �� ������ ��� �������� = -1
            if (Sboard[i][j] == 'w') newDRP[i][j] = -5;                         //���� ��������� w, �� ������ ��� �������� = -5
            if (Sboard[i][j] == 'P') newDRP[i][j] = -2;                         //���������� � ���������� ���������
            if (Sboard[i][j] == '#') newDRP[i][j] = 999;
            if (Sboard[i][j] == '*') newDRP[i][j] = 777;
        }
    }
    //��� ����� ��� ��� ��� ����, ���� ������� RenderScene ��������� �������� � ��������
}