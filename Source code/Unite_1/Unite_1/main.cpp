#include <iostream>

using namespace std;

// get_skeleton ();

void print_mask (int **mask); //выводит маску 3x3
int **make_mask (bool num);
void del_mask (int **mask);

int main()
{
//    int mask_1 [3][3] = {0,0,0,2,1,2,1,1,1};
//    маска
//    0|0|0
//    2|1|2
//    1|1|1

//    int mask_2 [3][3];
//    маска
//    2|0|0
//    1|1|0
//    2|1|2
    int **mask = make_mask (0);

    print_mask (mask);

    del_mask (mask);

    //print_mask (mask_1);
    return 0;
}

int **make_mask (bool num)
{
    int **mask = new int *[3];
    for (int i = 0; i < 3; i++)
    {
        mask [i] = new int [3];
    }
    mask [0][1] = mask [0][2] = 0;
//    x|0|0
//    x|x|x
//    x|x|x

    mask [1][1] = mask [2][1] = 1;
//    x|0|0
//    x|1|x
//    x|1|x

    if (num)
    {
        mask [0][0] = mask [2][0] = mask [2][2] = 2;
        mask [1][0] = 1;
        mask [1][2] = 0;
    }
    else
    {
        mask [0][0] = 0;
        mask [2][0] = mask [2][2] = 1;
        mask [1][0] = mask [1][2] = 2;
    }
    return mask;
}

void print_mask (int **mask)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
             cout << mask [i][j];
        }
        cout << endl;
    }
}

void del_mask (int **mask)
{
    for (int i = 0; i < 3; i++)
    {
        delete []mask[i];
    }
    delete []mask;
}
