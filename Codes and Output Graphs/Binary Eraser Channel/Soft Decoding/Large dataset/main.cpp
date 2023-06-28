#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int m=3792,n=5056;
//int m=9,n=12;
double *spc(double arr[])
{
    float p1=arr[0],p2=arr[1],p3=arr[2],p4=arr[3];
    static double temp[4]= {1};
    float t1=p2*p3*(1-p4)+p2*(1-p3)*p4+(1-p2)*p3*p4+(1-p2)*(1-p3)*(1-p4);
    if(t1 == 0)
    {
        t1=100000000;
    }
    temp[0]=((p2*(1-p3)*(1-p4))+(1-p2)*(1-p3)*p4+(1-p2)*p3*(1-p4)+p2*p3*p4)/t1;

    t1=p1*p3*(1-p4)+p1*(1-p3)*p4+(1-p1)*p3*p4+(1-p1)*(1-p3)*(1-p4);
    if(t1 == 0)
    {
        t1=100000000;
    }
    temp[1]=((p1*(1-p3)*(1-p4))+(1-p1)*(1-p3)*p4+(1-p1)*p3*(1-p4)+p1*p3*p4)/t1;

    t1=p2*p1*(1-p4)+p2*(1-p1)*p4+(1-p2)*p1*p4+(1-p2)*(1-p1)*(1-p4);
    if(t1 == 0)
    {
        t1=100000000;
    }
    temp[2]=((p2*(1-p1)*(1-p4))+(1-p2)*(1-p1)*p4+(1-p2)*p1*(1-p4)+p2*p1*p4)/t1;

    t1=p2*p3*(1-p1)+p2*(1-p3)*p1+(1-p2)*p3*p1+(1-p2)*(1-p3)*(1-p1);
    if(t1 == 0)
    {
        t1=100000000;
    }
    temp[3]=((p2*(1-p3)*(1-p1))+(1-p2)*(1-p3)*p1+(1-p2)*p3*(1-p1)+p2*p3*p1)/t1;

    return temp;
}

int **h;
void create_Hmatrix()
{
    h = new int *[n];

    for(int i = 0; i < m; i++)
    {
        h[i] = new int[n];

    }
    ifstream fin;
    fin.open("Hmatrix1.txt");

    if (!fin)
    {
        cout << "Cannot open the file" << endl;
        exit(0);
    }

    int inRow = 0, inCol = 0;

    char data;
    while (!fin.eof())
    {
        fin >> data;

        if (data != ',')
        {
            if (inCol == n)
            {

                inCol = 0;
                inRow++;
            }

            h[inRow][inCol] = data - 48;
            inCol++;

            if (inRow == m - 1 && inCol == n)
                break;
        }
    }
    fin.close();
}
int main()
{
//     int h[m][n]= {{1,0,0,0,0,1,0,1,0,1,0,0},
//        {1,0,0,1,1,0,0,0,0,0,1,0},
//        {0,1,0,0,1,0,1,0,1,0,0,0},
//        {0,0,1,0,0,1,0,0,0,0,1,1},
//        {0,0,1,0,0,0,1,1,0,0,0,1},
//        {0,1,0,0,1,0,0,0,1,0,1,0},
//        {1,0,0,1,0,0,1,0,0,1,0,0},
//        {0,1,0,0,0,1,0,1,0,1,0,0},
//        {0,0,1,1,0,0,0,0,1,0,0,1}
//    };
    create_Hmatrix();
    int cn=0,vn=0;
    for (int i = 0; i < m; i++)
    {
        if (h[i][0] == 1)
            vn++;
    }

    for (int i = 0; i < n; i++)
    {
        if (h[0][i] == 1)
            cn++;
    }

    //     cout<<cn<<" "<<vn;

    int  ch_conn[m][cn];
    int kk2;
    for(int i=0; i<m; i++)
    {
        kk2=0;
        for(int j=0; j<n; j++)
        {
            if(h[i][j]==1)
            {
                ch_conn[i][kk2]=j;
                kk2++;
            }
        }
    }

    int  vn_conn[n][vn];
    for(int i=0; i<n; i++)
    {
        kk2=0;
        for(int j=0; j<m; j++)
        {
            if(h[j][i]==1)
            {
                vn_conn[i][kk2]=j;
                kk2++;
            }
        }
    }
    /*    for(int i=0;i<n;i++)
        {
            for(int j=0;j<vn;j++)
            {
               cout<<" "<< vn_conn[i][j];
            }
            cout<<"\n";
        }*/
    int noise[n],ite=0,count=0;
    float cc[n]= {0.0};
    float p=0.01;
    srand(time(0));
    int perr=0;
    int Nsim=0;
    int kk=0;
    float arr[99];
    while(p<0.99)
    {
        Nsim=0;
        perr=0;
        while(Nsim<=10)
        {
            for(int i=0; i<n; i++)
            {
                double y = (double)rand()/RAND_MAX;
                int x = (y > (1- p));

                noise[i] = x ;
            }

            for(int i =0; i<n; i++)
            {
                if(noise[i] == 1)
                {
                    cc[i] =0.5;

                }
                else
                    cc[i]=0;

            }
            ite=0;
            while(1)
            {

                float cn_value[m][cn];
                for(int i=0; i<m; i++)
                {
                    for(int j=0; j<cn; j++)
                    {
                        cn_value[i][j]=cc[ch_conn[i][j]];
                    }
                }

                double cn_value_solve[m][cn]= {0};
                double arr[cn];
                double *arr2;
                for(int i=0; i<m; i++)
                {
                    arr[cn]= {0};
                    for(int j=0; j<cn; j++)
                    {
                        arr[j]=cn_value[i][j];
                    }

                    arr2=spc(arr);

                    for(int j=0; j<cn; j++)
                    {
                        cn_value_solve[i][j]=arr2[j];
                    }
                }

                float vn_value[n][vn]= {0};
                int x;
                int arr3[m]= {0};

                for(int i=0; i<n; i++)
                {
                    for(int j=0; j<vn; j++)
                    {
                        vn_value[i][j]=cn_value_solve[vn_conn[i][j]][arr3[vn_conn[i][j]]];
                        arr3[vn_conn[i][j]]++;
                    }
                }

                float vn_update[n]= {1};
                for(int i=0; i<n; i++)
                {
                    vn_update[i]=cc[i]/(1-cc[i]);
                    for(int j=0; j<vn; j++)
                    {
                        vn_update[i]=vn_update[i]*vn_value[i][j];
                    }
                }
                count=0;
                if(ite==40)
                    break;

                for(int i=0; i<n; i++)
                {
                    if(vn_update[i]==1)
                        count=-1;
                }

                for(int i=0; i<n; i++)
                {
                    cc[i]=vn_update[i]/(1+vn_update[i]);
                }
                if(count==0)
                    break;
                ite++;
            }
            /*     for(int i=0;i<n;i++)
                   {
                       cout<<cc[i]/(1-cc[i])<< " ";
                   }
            */
//cout<<"ite "<<ite<<endl;
            if(ite==40)
            {
                perr++;
            }
            Nsim++;
        }
        p=p+0.01;
        arr[kk]=(float)perr/Nsim;
        kk++;
    }
    for(int i=0; i<99; i++)
    {
        cout<<1-arr[i]<<",";
    }
    return 0;

}


