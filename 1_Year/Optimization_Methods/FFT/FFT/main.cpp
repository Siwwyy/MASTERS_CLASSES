#define _CRT_SECURE_NO_WARNINGS

#include <math.h>

#include <time.h>

#include <string.h>
#include <stdio.h>
#include <conio.h>

#include <windows.h>
#include <iostream>

#define _2PI   					   6.28318530717959
#define	M_PI 			           3.1415926535897932384626433832795
#define LEN                      16384
#define SMPL                     200
#define freq1                     45.37
#define freq2                     71.37
#define freq3                     75.37
#define freq4                     86.37


using namespace std;

double data[2 * LEN];

/***************************************************************************************/
/***************************************************************************************/
void FFT(double* data, unsigned long nn)
{
    unsigned long n, mmax, m, j, istep, i;
    double wtemp, wr, wpr, wpi, wi, theta;
    double tempr, tempi;

    // reverse-binary reindexing
    n = nn << 1;
    j = 1;
    for (i = 1; i < n; i += 2) {
        if (j > i) {
            swap(::data[j - 1], ::data[i - 1]);
            swap(::data[j], ::data[i]);
        }
        m = nn;
        while (m >= 2 && j > m) {
            j -= m;
            m >>= 1;
        }
        j += m;
    };

    // here begins the Danielson-Lanczos section 
    mmax = 2;
    while (n > mmax) {
        istep = mmax << 1;
        theta = -(2 * M_PI / mmax);
        wtemp = sin(0.5 * theta);
        wpr = -2.0 * wtemp * wtemp;
        wpi = sin(theta);
        wr = 1.0;
        wi = 0.0;
        for (m = 1; m < mmax; m += 2) {
            for (i = m; i <= n; i += istep) {
                j = i + mmax;
                tempr = wr * ::data[j - 1] - wi * ::data[j];
                tempi = wr * ::data[j] + wi * ::data[j - 1];

                ::data[j - 1] = ::data[i - 1] - tempr;
                ::data[j] = ::data[i] - tempi;
                ::data[i - 1] += tempr;
                ::data[i] += tempi;
            }
            wtemp = wr;
            wr += wr * wpr - wi * wpi;
            wi += wi * wpr + wtemp * wpi;
        }
        mmax = istep;
    }
}
/***************************************************************************************/
/***************************************************************************************/
int main(int argc, char* argv[])
{
    int   k, n;
    FILE* txt;
    char  buf[64];
    double freq;

    strcpy(buf, "fft.txt");
    if ((txt = fopen(buf, "wt")) == NULL)
    {
        printf("txt ERROR - %s\n", buf);
        system("PAUSE");
        exit(1);
    }
    fseek(txt, 0L, 0);

    n = LEN;

    for (k = 0; k < LEN; k++)
    {
        ::data[2 * k] = 1000.0 * cos(_2PI * k * freq1 / SMPL) + 800.0 * cos(_2PI * k * freq2 / SMPL) + 700.0 * cos(_2PI * k * freq3 / SMPL) + 1100.0 * cos(_2PI * k * freq4 / SMPL);
        ::data[2 * k + 1] = 0.0;
        //     printf("%4d %12.6f %12.6f\n",k,::data[2*k],::data[2*k+1]);
       //      fprintf(txt,"%4d %12.6f %12.6f\n",k,::data[2*k],::data[2*k+1]);
    }

    FFT(::data, n);
    printf("\n\n");

    for (k = 0; k <= LEN / 2; k++)
    {
        freq = 1.0 * k * SMPL / LEN;
        printf("%5d %12.4f %12.4f %15.6f\n", k, ::data[2 * k], ::data[2 * k + 1], sqrt(::data[2 * k] * ::data[2 * k] + ::data[2 * k + 1] * ::data[2 * k + 1]));
        fprintf(txt, "%5d %12.4f %12.4f %12.4f %15.6f\n", k, freq, ::data[2 * k], ::data[2 * k + 1], sqrt(::data[2 * k] * ::data[2 * k] + ::data[2 * k + 1] * ::data[2 * k + 1]));
    }

    //    k/64.0
    fflush(txt); fclose(txt);
    //    system("PAUSE");
    std::cin.get();
    return 0;
}
/***************************************************************************************/
/***************************************************************************************/
