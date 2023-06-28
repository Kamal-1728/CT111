#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//int m=3792,n=5056;
int m=9,n=12;
double *spc(double arr[])
{
    float p1=arr[0],p2=arr[1],p3=arr[2],p4=arr[3];
    static double temp[4]= {1};
    temp[0]=((p2*(1-p3)*(1-p4))+(1-p2)*(1-p3)*p4+(1-p2)*p3*(1-p4)+p2*p3*p4)/(p2*p3*(1-p4)+p2*(1-p3)*p4+(1-p2)*p3*p4+(1-p2)*(1-p3)*(1-p4));
    temp[1]=((p1*(1-p3)*(1-p4))+(1-p1)*(1-p3)*p4+(1-p1)*p3*(1-p4)+p1*p3*p4)/(p1*p3*(1-p4)+p1*(1-p3)*p4+(1-p1)*p3*p4+(1-p1)*(1-p3)*(1-p4));
    temp[2]=((p2*(1-p1)*(1-p4))+(1-p2)*(1-p1)*p4+(1-p2)*p1*(1-p4)+p2*p1*p4)/(p2*p1*(1-p4)+p2*(1-p1)*p4+(1-p2)*p1*p4+(1-p2)*(1-p1)*(1-p4));
    temp[3]=((p2*(1-p3)*(1-p1))+(1-p2)*(1-p3)*p1+(1-p2)*p3*(1-p1)+p2*p3*p1)/(p2*p3*(1-p1)+p2*(1-p3)*p1+(1-p2)*p3*p1+(1-p2)*(1-p3)*(1-p1));

    return temp;
}

int **h;

int main()
{
    int h[m][n]= {{1,0,0,0,0,1,0,1,0,1,0,0},
        {1,0,0,1,1,0,0,0,0,0,1,0},
        {0,1,0,0,1,0,1,0,1,0,0,0},
        {0,0,1,0,0,1,0,0,0,0,1,1},
        {0,0,1,0,0,0,1,1,0,0,0,1},
        {0,1,0,0,1,0,0,0,1,0,1,0},
        {1,0,0,1,0,0,1,0,0,1,0,0},
        {0,1,0,0,0,1,0,1,0,1,0,0},
        {0,0,1,1,0,0,0,0,1,0,0,1}
    };

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

    int noise[n],ite=0,count=0;
    float cc[n]= {0.0};
    float p=0;
    srand(time(0));
    int perr=0;
    int Nsim=0;
    int kk=0;
    float arr[101];

    while(p<=1)
    {
        Nsim=0;
        perr=0;
        while(Nsim<=1000)
        {
            float cc2[n][vn],in[n];
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
                    cc[i] = (p);
                    in[i]=p;
                }
                else
                {
                    cc[i]=1-p;
                    in[i]=1-p;
                }

            }
            for(int i=0; i<n; i++)
            {
                for(int j=0; j<vn; j++)
                {
                    cc2[i][j]=cc[i];
                }
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
                int arr4[n]= {0};
                for(int i=0; i<m; i++)
                {
                    for(int j=0; j<cn; j++)
                    {
                        cn_value[i][j]=cc2[ch_conn[i][j]][arr4[ch_conn[i][j]]];
                        arr4[ch_conn[i][j]]++;
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
                    vn_update[i]=(cc[i])/(1-cc[i]);
                    for(int j=0; j<vn; j++)
                    {
                        vn_update[i]=vn_update[i]*vn_value[i][j];
                    }
                }

                count=0;

                for(int i=0; i<n; i++)
                {
                    if(vn_update[i]>500000)
                        vn_update[i]=500000;
                }
                for(int i=0; i<n; i++)
                {
                    if(vn_update[i]<0.00001)
                        vn_update[i]=0.001;
                }

                for(int i=0; i<n; i++)
                {
                    float su1,su2,su3;
                    //su1=vn_value[i][0],su2=vn_value[i][1],su3=vn_value[i][2];
                    su1=(float)in[i]/(1-in[i]),su2=(float)in[i]/(1-in[i]),su3=(float)in[i]/(1-in[i]);
                    su1=su1*vn_value[i][1]*vn_value[i][2];
                    su2=su2*vn_value[i][0]*vn_value[i][2];
                    su3=su3*vn_value[i][1]*vn_value[i][0];

                    cc2[i][0]=(float)su1/(1+su1);

                    cc2[i][1]=(float)su2/(1+su2);

                    cc2[i][2]=(float)su3/(1+su3);

                }

                count=0;

                for(int i=0; i<n; i++)
                {
                    if(((cc[i]/(1-cc[i]))/vn_update[i])>=1)
                        count++;
                }
                for(int i=0; i<n; i++)
                {
                    cc[i]=(vn_update[i])/(1+vn_update[i]);
                }
                if(count==0||count==n)
                    break;
                if(ite==25)
                    break;


                ite++;


            }
            for(int i=0; i<n; i++)
            {
                if((cc[i]/(1-cc[i]))<1)
                {
                    perr++;
                    break;
                }
            }
            Nsim++;
        }
        p=p+0.01;
        arr[kk]=(float)perr/Nsim;
        kk++;
    }
    for(int i=0; i<101; i++)
    {
        cout<<1-arr[i]<<",";
    }
    return 0;
}


