/*��� ������� ���� � ����� ���������, ���� ������������ ���������� � ������ �����*/
#include <iomanip>
#include <iostream>                                 //��� ������ � �������
#include <fstream>                                  //����
#include <math.h>                                   //��� ������������� �������������� ��������
#include <vector>                                   //��� ����������� ������������ �������, �.� ��� ������� ��������
#include <ctime>                                    //��� ������ �� ��������
#include "glut.h"                                   //�������
#include "glaux.h"                                  //����
#include <chrono>                                   //��� ������ �� ��������

//���������������� ����������, ������� �� ��� �������
#include "move.h"                                   //���������������� ���������� ��� ���������� ������������� � ����������
#include "image.h"                                  //���������������� ���������� ��� ��������� �������

//�����, ���������� �� ��, ���� ���������� �� ������������ ����������
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glaux.lib")
 
using namespace std;                                // ������� ������������ ����

//������ ������ ����                                //��������� ��������� ����������

int bx, by, cx, cy, px, py;                         //���������� �����������, �������, �����, ��������������
bool Lblock[10000], Sblock[10000];                  // ��� (���������� ������� ����) ����������
int Lpath[10000], Spath[10000];                     //����, ������ ��������
const int MAX_value=10000000;                       //����������, ��� ���������


int count_city, count_barrier, count_point;         //�������� ���������� �������, ����������� � ����� ��� ������������

class Timer {                                       //����� ��� ������ �������, ��� � ��������� �� ����, �.� ��� ��� ������� ����������� ���, ���� ����� ����, �� ��������
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

//������� ��� ������� ��������, ���������� ������� ���������, �.� ����� ������ ������ � ����� ����� ������ ���������� �������
//������ ��� �������� ��������� �����, ������� � ����������� �� � � �, ��������������
vector<int> point_x_pos;
vector<int> point_y_pos;

vector<int> city_x_pos;
vector<int> city_y_pos;

vector<int> barrier_x_pos;
vector<int> barrier_y_pos;

int p_opt_x, p_opt_y;                                                                   //���������� ����������� �����

void print_termenal_and_barrier();
void print_DRP();
void Print_newDRP(char Sboard[1000][1000]);
void RenderScene();

//������� ���������� ��������� �� ����� �� ���������� � ��� ������
int dist_to_city(int p_x, int p_y, vector<int> c_x, vector<int> c_y) {                  //������� ������ ��� ���������� ��������������� ����� � ������� � ������������ ���� �������             

    int dist_all = MAX_value;                                                           //���������, ��� ����������� ���������� ����� ��������� ��������
    for (int i = 0; i < c_x.size(); i++) {                                              //������ ���������� ���������� ���� �������
        /* �� ������ �������� (��� ���� � ������������ ��������)
        ������� ���������������� ���������� (�� ���� ��������� �� 
        ����������� � ���������) ����� ������ � �������. ����������
        ��� ���������� � ����������� (� ��� � ��� �� ������ �������� = 10000000,
        �� ���� ������ ��������� ��������� ����� ����� ������)
        ���� ��� ������ ������������, �� ���������, ��� ������ ��� �����������
        ����������. ����� ������� ��� �������� ���� ��������� �������
        �� ������ ��������� ����� � ���������� �� ����. ������� ����������
        �������� ������ ���������� �� ���������� ������
        */
        if (abs(p_x - c_x[i]) + abs(p_y - c_y[i]) < dist_all) {                         //���������� ����-�� ���� ������� � ���������� ��������� �� ��� � ����������� ����������� �� ������ ��������              
            dist_all = abs(p_x - c_x[i]) + abs(p_y - c_y[i]);                           //��������� ��������� ���������� �����������, ���� ��� ������ ������������.���������� �����
        }
    }
    return dist_all;                                                                    //������������ ��������
}

//������ ���������� ���������� �� ���������� �����������
int dist_to_barier(int p_x, int p_y, vector<int> b_x, vector<int> b_y) {                //������� ������ ��� ���������� ��������������� ����� � ������� � ������������ ���� �����������
    int dist_all = MAX_value;
    /*������� ������ ����� ����� ��, ��� � � ���������� �������, ������
    ������ �� ������������� ���������� ����������� ������ ����-� �������.
    ��������� �� ����, ��� ����� �����. ��������� ������� �������� ��������� 
    �� ����� �� ���������� �����������*/
    for (int i = 0; i < b_x.size(); i++) {
        if (abs(p_x - b_x[i]) + abs(p_y - b_y[i]) < dist_all) {
            dist_all = abs(p_x - b_x[i]) + abs(p_y - b_y[i]);
        }
    }
    return dist_all;
}

int main(int argc, char* argv[])                                                         //��� �������� (��������) ������� ���������, ��� �������� ������ ����� � ���������
{
    setlocale(LC_ALL, "Russian");                                                        //������� � ���, ��� � ����� ������������ ������� ����. ��� ����� ��� ����������� ����������� �������� ������ � ������� (� �� ������)

    int answer = 0;                                                                      //��������� ����������, ������� ����� �������������� ��� ������ ������
    cout << endl << "������� ��������� ������� ������:"                                   //������� ���� � ������� ��������� ������
        << endl << "1) ���������� ������������ �������� ������ �� �����������, ��������� �������������"
        << endl << "2) ��������� ����������� �� �����";

    cout<<endl << endl << "������� ����� ���������� �������: ";
    cin >> answer;                                                                      //�������� �� ������������ �����

    if (answer == 1) {                                                                  //���� �������� 1, �� �������� ����
        //������ ������������ ������ �������������

        cout << "������� ������ ���: "; 
        cin >> n;                                                                       //�������� ������ ���
        cout << endl << "������ ���������� �����������: ";
        cin >> count_barrier;                                                           //�������� ���-�� �����������
        cout << endl << "������� ���������� �������: ";
        cin >> count_city;                                                              //�������� ���-�� �������
        cout << endl << "������� ���������� �����: ";
        cin >> count_point;                                                             //�������� ���-�� �����

        for (int i = 0; i < n; i++)                                                     //�� ������ ����������� ������� ������� ��� ������ ������� (������� ������)
        {
            for (int j = 0; j < n; j++)
            {
                Lboard[i][j] = '0';                                                     //������� ��������� ��� ������ ������ ��� ���� ��� �����)
                Sboard[i][j] = '0';
            }
        }

        for (int i = 0; i < count_barrier; i++) {                                       //����������� �� ���������� ����������� ������� ������� �����������
            bx = rand() % n;                                                            //����-�� �� � � � ��������� ���������
            by = rand() % n;                                                            // % n �������� , ��� �������� ��������� ����� ����� �� 0 �� n.
                                                                                        // � ������ ������ �� ����� ��� ����, ���� ���������� ������������� ������ � ������� ���
            barrier_x_pos.push_back(bx);                                                //��������� ����-�� � ������ ����-� ����������� �� �
            barrier_y_pos.push_back(by);                                                //���������� �� �
            Lboard[bx][by] = '#';                                                       //����������� ����������� �� ���, ��� ����� ��������� �� ����������� �������� #
            Sboard[bx][by] = '#';
        }

        /*����� �� ���������� ���� while ������ ��� �� �����, ������� �������� �������� ������� */
        while (city_x_pos.size() != count_city) {                                       //���� ����� �����������, ���� � ������� ����-� ������� �� ����� ������� �� ��������� ������� ���� ������������
            /*� ������ ����� ����� ����������� �������� �� ��, ��� ���������� ���������� �� ������
            ��� ����� ������� ��� ��������� ���������� � � �*/
            int x, y;                                                                   
            x = rand() % n;                                                             //����������� ����-��� ��������� �������� � ������� �������� ���
            y = rand() % n;
            if (Sboard[x][y] == '0' && Lboard[x][y]=='0') {                             //����� �� ���������, �� ������ �� ������ � ������ ������������
                                                                                        //���� �� ������ �� ��������� ��������� ��������
                cx = x;                                                                 //����������� ���������� ����-��
                cy = y;
                city_x_pos.push_back(cx);                                               //��������� ��� ����-�� � ������ ����-� ������� �� �
                city_y_pos.push_back(cy);                                               // � �� �
                Lboard[cx][cy] = 'C';                                                   //����������� ����������� �� ���, ��� ����� ��������� �� ����������� �������� �
                Sboard[cx][cy] = 'C';
            }
            //���� ��� ������ ��� ������, �� ��������� �������� � �������� ����� ��������� ��������
            //��� ����� �������������, ���� �� ����� �������� ���������� ��������� ����-��
            //(�� ����� ����, ���� �� ������� ������ ��� ,��������, 2, � ���-�� ������� � ����������� 10, �� ����� �������� ��-�� ����� �����, ��� ��� �� ����� ���)
        }

        //���������� �������� ����� ���������� while �.� �� ����� ������� ���-�� ��������
        //� ��������, ����� ��� ���� �����
        while (point_x_pos.size() != count_point) {
            int x, y;
            x = rand() % n;                                                              //��������� �������� ��������
            y = rand() % n;
            if (Sboard[x][y] == '0' && Lboard[x][y] == '0') {                            //���������, ��� ������ � ������ ������������ ��������
                px = x;                                     
                py = y;
                point_x_pos.push_back(px);                                               //���� ��, �� ��������� ��� ����-�� � �������
                point_y_pos.push_back(py);                                               //�������� �� ��� �������� �
                Lboard[px][py] = 'P';
                Sboard[px][py] = 'P';
            }
        }

    }

    //���� �� ������� ���� ������������ ��� ������ ������ ����� ������ ������ 2
    else if (answer == 2) {
        ifstream in("input.txt");                                                               //��������� ������ (����������) ���������� �������� ���������� ����� �� �����
        //����� �������� �� ����������� ������ ����
        //��� �� �����������, �� ��� �������� �������� �������� ����
        if (!in.is_open()) {                                                                    //���������, ����� �� ������� ��� ���� (����� ���� ���, ��� ������ �� ����������)  
            cout << "���� �� ����� ���� ������!\n";                                             //���� ���� ������� ����������, �� �������� �� ���� ������������ � ��������� ���������
            return ERROR_FILE_NOT_FOUND;                                                        //��������� ������ �������� ����� (���� �� ������)
        }
        else {                                                                                  //���� ���� ������, �� ������ ������ �� ����

            in >> n;                                                                            //������ ������ ��� (��� ����� ������ ����������)
            /*������� ���� ��� ����� ���������� 0 (0 - ������ �����)
            �.� ��� ������������ ����� ���� ������ (�������), ��
            ���������� ���������� � ������� ����� - �� �������*/
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    Lboard[i][j] = '0';                                                         //���������� ��� ������ ��� ������ �������
                    Sboard[i][j] = '0';
                }
            }

            in >> count_barrier;                                                                //������ ���-�� �����������
            for (int i = 0; i < count_barrier; i++) {
                in >> bx >> by;                                                                 //������ ����-�� ������� ����������� �� � � �
                barrier_x_pos.push_back(bx);                                                    //��������� ����-�� �� � � ������ ����-� ����������� �� �
                barrier_y_pos.push_back(by);                                                    //���������� ������ �� �
                Lboard[bx][by] = '#';                                                           //����������� ����������� �� ���, ��� ����� ��������� �� ����������� �������� #
                Sboard[bx][by] = '#';
            }

            in >> count_city;                                                                   //������ ���-�� �������
            for (int i = 0; i < count_city; i++) {
                in >> cx >> cy;                                                                 //����� ��� ���������� � �������������
                city_x_pos.push_back(cx);
                city_y_pos.push_back(cy);
                Lboard[cx][cy] = 'C';
                Sboard[cx][cy] = 'C';
            }

            in >> count_point;                                                                   //������ ���-�� �����
            for (int i = 0; i < count_point; i++) {
                in >> px >> py;                                                                  //���� ����������
                point_x_pos.push_back(px);
                point_y_pos.push_back(py);
                Lboard[px][py] = 'P';
                Sboard[px][py] = 'P';
            }
        }
    }
    else {                                                                                  //���� ������������ ���� �� 1 � �� 2 �� ����� ������ ������, �� ��������� ��� �� ������������ ������
        cout << endl << "������� ������������ ������. ���������� ���������";                //�������� �� ����
        return ERROR_INVALID_DATA;                                                          //���������� ��������� ������ ������������ ������
    }
    //�� ���� ��������� ������ ���������

    print_termenal_and_barrier();                                                           //������� ���� ��� ����� ����������� ���� �����������, ������� � �����
    //��� ������� ������� � ������ �����
    cout << endl << endl;                                               

    int min_dist_p_to_c = MAX_value;                                                        //��������� ��� ����������� ���������� = ��������� �����
    int max_dist_p_to_b = 0;                                                                //������������ ���������� ����� 0

    Timer t;                                                                                //������ ������ ������� (����� ��� ������ �������). ����� ������ ������� ������� ������ ���������

    //��� ��� �������� ������� ��� ����������� ���������� �����������... ���� ����, ���� ���������
    //��� � ���� ���� ������ �������
    /*� ����� ���������� ��� �����
    ��� ������ ����� � ������� ���� ������� ��������� ����
    ������� ���������� ��� ���������� ������
    � ���������� �����������. ������� �����, ����������������
    2 ��������:
    1) ���������� �� ����� �� ���������� ����������� �����������
    2) ���������� �� ���������� ������ ����������
    ������ ��� ���������� ����� ������� �� ������������� �����
    �� ������ �������� �� ����� �������� ��� ����� ����������� �����.
    ����� ������� ��� �������� ���� ����� �� ������ �����������
    */
    for (int i = 0; i < point_x_pos.size(); i++) {                                                                  //����������� �� ���� ������. ������� ��������������� ������������ � ������� ����������� AND ( ����������� �)   
        if ((dist_to_city(point_x_pos[i], point_y_pos[i], city_x_pos, city_y_pos) <= min_dist_p_to_c) &&            //������� ����, ��� ���������� �� ������ ����������
            (dist_to_barier(point_x_pos[i], point_y_pos[i], barrier_x_pos, barrier_y_pos) >= max_dist_p_to_b))      //������� ����, ��� ���������� �� ����������� �����������
            //� �������� ����������� ���� ������������ ������� ������/������ ��� �����
            //��� ������ ������, ��� ���� ����-�� ������ ���������, � ������ ����� ��������� �����
        {
            //���� �� �������� ������ ���� ����� �������� �� ������������� ��������
            //���� ����� ������������� ��������, �� ���������� ����� ����������� ���������� �� ������
            //� ����������� �� �����������. ����� ������� �� ������ ����������� �����
            //����� ������� �� �� ������ �������� ������ ������� ���������� ����� (�� ���� ��� � ���� ���� ������������� ��������)
            min_dist_p_to_c = dist_to_city(point_x_pos[i], point_y_pos[i], city_x_pos, city_y_pos);                 //����������� ���������� �� ������ ���������� ����� ������ ������������ ����������
            max_dist_p_to_b = dist_to_barier(point_x_pos[i], point_y_pos[i], barrier_x_pos, barrier_y_pos);         //������������ ���������� �� ���������� ����������� ����� ������ ���� ����������
            p_opt_x = point_x_pos[i];                                                                               //���� ����� ������� �� ��������, �� ���������� �� ����-��
            p_opt_y = point_y_pos[i];
        }
    }

    double time_algotim = t.elapsed();                                                                              //����� ����������� ������ �������

    cout << endl << "���������� ����������� �����: " << p_opt_x << " " << p_opt_y;                                  //������� � ������� ����-�� ��������� ����������� �����

    cout <<endl<<"���������� �� ����� �� ���������� ������: "<< min_dist_p_to_c;                                    //������� � ������� ���������� �� �������� ����������� ����� �� ����������  ������
    cout <<endl<<"���������� �� ����� �� ���������� �����������: " << max_dist_p_to_b;                              //������� � ������� ���������� �� �������� ����������� ����� �� ����������  �����������
    cout <<endl<<"����� ���������� ��������� : " << time_algotim * 100000000 << " ��" << endl;                      //������� �����, ����������� �� ���������� ��������� ������� �� ����� ����������� 
                                                                                                                    //(������ ��� � �� �����, � ����� �������� ��� ���������� =))0) ). ��������� � ������������
    
    Lboard[p_opt_x][p_opt_y] = '*';                                                                                 //�������� �� ��� ��������� ����������� ����� ����������� ��������
    Sboard[p_opt_x][p_opt_y] = '*';                                                                                                       

    Print_newDRP(Sboard);                                                                                           //������� ������������� ��� ����������� ���� � ��� ��������� ���� (��� ����� ��� ���������� ������������)                 
                                                                                                                    //��� ������� ������� � ������ �����

    //����� ���������� �� ���������� ������ �������
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1000, 1000);                                                                                 //������ ���������� ����
    glutCreateWindow("����");                                                                                       //�������� ����
    glEnable(GL_DEPTH_TEST);
    glClearColor(0, 0, 0, 1);
    glutReshapeFunc(reshape);                                                                                       //���������
    glutDisplayFunc(RenderScene);                                                                                   //�������� (��������) ������� ��������� ������� (��� ������ � ���������������� ����������)
    glutKeyboardFunc(Read_kb);                                                                                      //������� ������� ������� �� ����������
    glutSpecialFunc(ReadSpec);                                                                                      //���� �����
    glutMainLoop();
    return 0;                                                                                                       //�������� ������������ ������� ��������� �������� (main). ���� � ��������� ����� ������, �� �������� ����� �� 0.
}                                                                                                                   //����� ������� �������