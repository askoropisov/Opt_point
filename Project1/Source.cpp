#include <iomanip>
#include <iostream>
#include <fstream>
#include <math.h>
#include <stack> 
#include <queue>
#include <vector>
#include <ctime>
#include "glut.h"
#include "glaux.h"
#include <chrono>
#include "move.h"
#include "image.h"


#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glaux.lib")

using namespace std;


//int newDRP[100][100];
//char Lboard[100][100], Sboard[100][100];
int bx, by, cx, cy, px, py;
bool Lblock[10000], Sblock[10000];
int Lpath[10000], Spath[10000];

int startX_mass[100], startY_mass[100], target_X_mass[100], target_Y_mass[100];
int super_id;
int count_city, count_barrier, count_point;

class Timer {
private: 
    using clock_t = chrono::high_resolution_clock;
    using second_t = chrono::duration<double, std::ratio<1> >;
    chrono::time_point<clock_t> m_beg;
public:
    Timer() : m_beg(clock_t::now()) {}
    void reset() { m_beg = clock_t::now(); }
    double elapsed() const {
        return chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
    }
};


void print_termenal_and_barrier();
void print_DRP();
void Print_newDRP(char Sboard[100][100]);
void RenderScene();

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");

    ifstream in("input.txt");    
    if (!in.is_open()) // если файл не открыт
        cout << "Файл не может быть открыт!\n"; // сообщить об этом
    else {
        //ofstream out2("soukup.txt");
        in >> n;
        in >> count_barrier;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                Lboard[i][j] = '0';
                Sboard[i][j] = '0';
            }
        }
        memset(Lblock, false, (n * n) + 1);                                                                 //заполняем блоки памяти Lblock и Sblock 0
        memset(Sblock, false, (n * n) + 1);

        for (int i = 0; i < count_barrier; i++)
        {
            in >> bx >> by;
            Lboard[bx][by] = '#';
            Sboard[bx][by] = '#';
            Lblock[bx * n + by] = true;
            Sblock[bx * n + by] = true;
        }

        in >> count_city;
        for (int i = 0; i < count_city; i++) {
            in >> cx >> cy;
            Lboard[cx][cy] = 'C';
            Sboard[cx][cy] = 'C';
        }

        in >> count_point;
        for (int i = 0; i < count_point; i++) {
            in >> px >> py;
            Lboard[px][py] = 'P';
            Sboard[px][py] = 'P';
        }
    }


    print_termenal_and_barrier();
    cout << endl << endl;

    print_DRP();
    cout << endl << endl;


    Print_newDRP(Sboard);



    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Даня");
    glEnable(GL_DEPTH_TEST);
    glClearColor(0, 0, 0, 1);
    glutReshapeFunc(reshape);
    glutDisplayFunc(RenderScene);
    glutKeyboardFunc(Read_kb);
    glutSpecialFunc(ReadSpec);
    glutMainLoop();
    return 0;
}