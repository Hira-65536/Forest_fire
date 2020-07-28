#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define WIDTH   20
#define HEIGHT  20
#define MAP_WIDTH   WIDTH+2
#define MAP_HEIGHT  HEIGHT+2

void init_cells(int (&a)[MAP_HEIGHT][MAP_WIDTH]);
//printf cells
void print_cells(int (&a)[MAP_HEIGHT][MAP_WIDTH],int cnt);

//counter
int lives_counter(int (&a)[MAP_HEIGHT][MAP_WIDTH],int _x, int _y);

//compare now step => next step
void step_cells(int (&before)[MAP_HEIGHT][MAP_WIDTH], int (&after)[MAP_HEIGHT][MAP_WIDTH]);

int main()
{
    int cnt=1;
    int cell_a[MAP_HEIGHT][MAP_WIDTH]={{}};
    int cell_b[MAP_HEIGHT][MAP_WIDTH]={{}};

    int (*a)[MAP_HEIGHT][MAP_WIDTH] = &cell_a;
    int (*b)[MAP_HEIGHT][MAP_WIDTH] = &cell_b;
        init_cells(*a);
    while(true){
        print_cells(*a,cnt);
        cnt++;
        step_cells(*a,*b);
        print_cells(*b,cnt);
        cnt++;
        step_cells(*b,*a);
    }
    return 0;
}

void init_cells(int (&a)[MAP_HEIGHT][MAP_WIDTH]){
    for (int i = 1; i < MAP_HEIGHT-1; i++)
        {
        for (int j = 1; j < MAP_WIDTH-1; j++)
            {
                  a[i][j]=1;
            }
        }  
}

void print_cells(int (&a)[MAP_HEIGHT][MAP_WIDTH],int cnt)
{
    int x=1, y=1;
    int break_flag=0;
    while(true)
    {
        if(x<=0)x=1;
        if(x>=MAP_WIDTH-1) x=MAP_WIDTH-2;
        if(y<=0)y=1;
        if(y>=MAP_HEIGHT-1) y=MAP_HEIGHT-2;
        system("cls");
        printf("CURSOR MOVE:wasd SET:SPACE NEXT:r \n");
        for (int i = 1; i < MAP_HEIGHT-1; i++)
        {
            for (int j = 1; j < MAP_WIDTH-1; j++)
            {
                if ((x == j) && (y == i))
                    printf("™");
                else{
                    if(a[i][j]==0)printf(" ");
                    else if(a[i][j]==1)printf("–Ø");
                    else if(2<=a[i][j]&&a[i][j]<=4)printf("‰Î");
                    else if(5<=a[i][j]&&a[i][j]<=8)printf("‰Š");
                    else printf("ŠD");
                }
                //else printf("%d",a[i][j]);
                /*if ((x == j) && (y == i))
                    printf("@");
                else
                    printf("%d",lives_counter(a,j,i));*/
            }
            printf("\n");
        }
        printf("GENERATION:%d \n",cnt);
        printf("0:‹ó’n 1:–Ø 2~4:”­‰Î‘O 5~8:”­‰Î 9:ŠD \n");
        switch (_getch()){
            case 'w': y--;break;
            case 's': y++;break;
            case 'a': x--;break;
            case 'd': x++;break;
            case '0': a[y][x] = 0;break;
            case '1': a[y][x] = 1;break;
            case '2': a[y][x] = 2;break;
            case '3': a[y][x] = 3;break;
            case '4': a[y][x] = 4;break;
            case '5': a[y][x] = 5;break;
            case '6': a[y][x] = 6;break;
            case '7': a[y][x] = 7;break;
            case '8': a[y][x] = 8;break;
            case '9': a[y][x] = 9;break;
            case 'r': break_flag=1;break;
        }

        if(break_flag){
            break;
        }
    }
}

int lives_counter(int (&a)[MAP_HEIGHT][MAP_WIDTH],int _x, int _y){
    int count=0;
    for(int y=-1;y<=1;y++){
        for(int x=-1;x<=1;x++){
            if((x==0)&&(y==0)) continue;
            int x2 = _x + x;
            int y2 = _y + y;
            if (5<=a[y2][x2]&&a[y2][x2]<=8)
                count ++;
        }
    }
    return count;
}

void step_cells(int (&before)[MAP_HEIGHT][MAP_WIDTH], int (&after)[MAP_HEIGHT][MAP_WIDTH])
{
    for (int y = 1; y < MAP_HEIGHT-1; y++)
        {
            for (int x = 1; x < MAP_WIDTH-1; x++)
            {
            int n = lives_counter(before,x,y);
            int check = 0;
            if(before[y][x]==1){
                if(n==0)check=1;
                else if(1<=n&&n<=4)check=2;
                else check =3;
            }
            else if(before[y][x]==2){
                if(n==0)check=2;
                else if(1<=n&&n<=2)check=3;
                else if(3<=n&&n<=4)check=4;
                else check =5;
            }
            else if(before[y][x]==3){
                if(n==0)check=3;
                else if(1<=n&&n<=2)check=4;
                else check =5;
            }
            else if(before[y][x]==4){
                if(n==0)check=4;
                else check =5;
            }
            else if(before[y][x]==5){
                check=6;
            }
            else if(before[y][x]==6){
                check =7;
            }
            else if(before[y][x]==7){
                check =8;
            }
            else if(before[y][x]==8 || before[y][x]==9){
                check =9;
            }else{
                check=0;
            }
            after[y][x] = check;
        }
    }
}
