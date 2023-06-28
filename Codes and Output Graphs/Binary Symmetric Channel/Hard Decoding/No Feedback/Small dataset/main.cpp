#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int n=12,m=9;

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

    srand(time(0));
    int noise[n];
    int cc_update[n]= {-1};

    float p=0.0;
    int chk=0,kk=0;
    float psucc[101]= {0};
    while(p<=1)
    {
        int nsim=0,nsucc=0;
        while(nsim<=100)
        {
            int cc[n]= {0};
            int in[n]={0};
            int cc2[n][vn]={0};
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
                    cc[i] =1;
                    in[i]=1;
                }
                else
                   {
                    cc[i]=0;
                    in[i]=0;
                    }

            }
            for(int i=0;i<n;i++)
            {
                for(int j=0;j<vn;j++)
                {
                    cc2[i][j]=cc[i];
                }
            }

            int ite=0;
            while(1)
            {
                int  cn_value[m][cn];

                 int arr2[n]= {0};
                for(int i=0; i<m; i++)
                {
                    for(int j=0; j<cn; j++)
                    {
                        cn_value[i][j]=cc2[ch_conn[i][j]][arr2[ch_conn[i][j]]];
                        arr2[ch_conn[i][j]]++;
                    }
                }

                int sum1=0,sum2,sum3,sum4;

                for(int i=0; i<m; i++)
                {
                    sum1=0,sum2=0,sum3=0,sum4=0;
                    sum1=cn_value[i][1]+cn_value[i][2]+cn_value[i][3];
                    sum2=cn_value[i][0]+cn_value[i][2]+cn_value[i][3];
                    sum3=cn_value[i][0]+cn_value[i][1]+cn_value[i][3];
                    sum4=cn_value[i][0]+cn_value[i][1]+cn_value[i][2];
                    cn_value[i][0]=sum1%2;
                    cn_value[i][1]=sum2%2;
                    cn_value[i][2]=sum3%2;
                    cn_value[i][3]=sum4%2;
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


                 for(int i=0;i<n;i++)
                {
                    int su1,su2,su3;
                    su1=in[i],su2=in[i],su3=in[i];
                    su1=su1+vn_value[i][1]+vn_value[i][2];
                    su2=su2+vn_value[i][0]+vn_value[i][2];
                    su3=su3+vn_value[i][0]+vn_value[i][1];
                    if(su1>=2)
                        cc2[i][0]=1;
                    else
                        cc2[i][0]=0;

                    if(su2>=2)
                        cc2[i][1]=1;
                    else
                        cc2[i][1]=0;

                    if(su3>=2)
                        cc2[i][2]=1;
                    else
                        cc2[i][2]=0;

                }

                for(int i=0; i<n; i++)
                {
                    int sum=cc[i];
                    for(int j=0; j<vn; j++)
                    {
                        sum=sum+vn_value[i][j];
                    }
                    if(sum>=2)
                        cc_update[i]=1;
                    else
                        cc_update[i]=0;
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
                if(ite==100)
                {
                    break;
                }
                ite++;

            }

            int pe=0;
            for(int i=0; i<n; i++)
            {
                if(cc_update[i]==1)
                {
                    pe++;
                    break;
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


// Hard bsc for 12 9 matrix , Kamal ,Dev , Mihir
