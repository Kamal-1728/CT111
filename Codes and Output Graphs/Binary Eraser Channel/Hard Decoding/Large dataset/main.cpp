#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int m=3792,n=5056;
int **h;

void create_Hmatrix()
{
    h = new int *[m];

    for (int i = 0; i < m; i++)
        h[i] = new int[n];

    ifstream fin;
    fin.open("Hmatrix1.txt");

    if (!fin)
    {
        cout << "Cannot open the file" << endl;
        exit(0);
    }

    int inRow = 0, inCol = 0;

    char data;
    while (!fin.eof()) // Here I want to fill the H matrix with values given in text file,
        //keeping in mind the size of each row and column of H
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

            if(inRow == m-1 && inCol == n)
                break;


        }
    }
    fin.close();
}

int main()
{
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

    srand(time(0));
    int noise[n];
    int cc_update[n]= {0};
    float p=0;
    int chk=0,kk=0;
    float psucc[101]= {0};
    while(p<=1)
    {
        int nsim=0,nsucc=0;
        while(nsim<=10)
        {
            int cc[n]= {0};
            for(int i=0; i<n; i++)
            {
                double y = ((double)( rand()%10000)/10000 );
                int x = (y > (1- p));
                noise[i] = x ;
            }

            for(int i =0; i<n; i++)
            {
                if(noise[i] == 1)
                {
                    cc[i] =- 1;
                    cc_update[i]=-1;
                }
            }

            int ite=0;
            while(1)
            {
                int  cn_value[m][cn];

                for(int i=0; i<m; i++)
                {
                    for(int j=0; j<cn; j++)
                    {
                        cn_value[i][j]=cc[ch_conn[i][j]];
                    }
                }

                int err=0,key=-1;
                for(int i=0; i<m; i++)
                {
                    int sum=0;
                    err=0;
                    for(int j=0; j<cn; j++)
                    {
                        if(cn_value[i][j]==-1)
                        {
                            err++;
                            key=j;
                        }
                    }
                    if(err==1)
                    {
                        for(int j=0; j<cn; j++)
                        {
                            if(j!=key)
                            {
                                sum=sum+cn_value[i][j];
                            }
                        }
                        cn_value[i][key]=sum%2;
                    }
                }

              int vn_value[n][vn]= {0};
                int x;
                int arr3[m]= {0};

                for(int i=0; i<n; i++)
                {
                    for(int j=0; j<vn; j++)
                    {
                        vn_value[i][j]=cn_value[vn_conn[i][j]][arr3[vn_conn[i][j]]];
                        arr3[vn_conn[i][j]]++;
                    }
                }

                for(int i=0; i<n; i++)
                {
                    if(cc_update[i]==-1)
                    {
                        for(int j=0; j<vn; j++)
                        {
                            if(vn_value[i][j]!=-1)
                            {
                                cc_update[i]=vn_value[i][j];
                            }
                        }
                    }

                }
                chk=0;
                for(int i=0; i<n; i++)
                {
                    if(cc_update[i]!=cc[i])
                    {
                        cc[i]=cc_update[i];
                        chk=-2;
                    }
                }
                if(chk==0)
                {
                    break;
                }
                if(ite==30)
                    ite++;
            }
            int pe=0;
            if(ite==30)
            {
                pe++;
            }
            else
            {
                for(int i=0; i<n; i++)
                {
                    if(cc_update[i]==-1)
                    {
                        pe++;
                    }
                }
            }


            nsim++;
            if(pe==0)
            {
                nsucc++;
            }
        }

        psucc[kk]=(float)nsucc/nsim;
        kk++;
        p=p+0.01;
    }
    for(int i=0; i<101; i++)
    {
        cout<<psucc[i]<<" ,";
    }
    return 0;
}
