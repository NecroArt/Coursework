//#include <iostream>
//#include <stdio.h>
//#include "gd.h"

//using namespace std;

//int binarizate (file inputImage);

//int main()
//{
//    cout << "Hello World!" << endl;
//    return 0;
//}

//int binarizate (file inputImage)
//{

//}
// �������� ������ ����������
 #include <src/gd.h>
 #include <src/gd.c>
 #include <stdio.h>

int main(int argc, char **argv) {

    gdImagePtr im,im_clear; // ��������� ���������� ��� �������� ���������� �� ������������ �����������
    int black, white, trans; // ��������� ���������� ��� �������� ������
    FILE *out1; //��������� ��������� �� ����

    im = gdImageCreate(100, 100); //������� ������ ���� �������� 100�100
    im_clear = gdImageCreate(100, 100);

    white = gdImageColorAllocate(im, 255, 255, 255); // ��������� �����
    black = gdImageColorAllocate(im, 0, 0, 0);
    trans = gdImageColorAllocate(im, 1, 1, 1);

    gdImageCopy (im_clear, im, 0,0,0,0, 100, 100); //�������� ���� ��� ������ im � im_clear
    if (argc>1) out1 = fopen(argv[1], "wb"); else out1 = fopen("anim.gif", "wb"); // ��������� ���� ���� �������� ���� �����
    gdImageGifAnimBegin(im, out1, 1, 0); //����� ��������� gif-�

    for (int i=0;i<25;i++)
    {
       gdImageCopy (im, im_clear, 0,0,0,0, 100, 100); //������� ���� im
       gdImageRectangle(im, i*2, i*2, 100-i*2-1, 100-i*2-1, black); // ������ �������
       gdImageGifAnimAdd(im, out1, 0, 0, 0, 10, 1, NULL);//����� ���� � �����
    };

    putc (';', out1); // ����� � ����� �����
    fclose(out1); //��������� ������

    gdImageDestroy(im); // ������� �� �����
    gdImageDestroy(im_clear);

 }
