#include <iostream>
#include <math.h>
#include <random>


double f(double x)
{
    return 1 / (1 + exp(-1*x));
}

int main()
{
    srand(time(NULL));
    int p1[35] = { 1,1,1,1,1, 1,0,0,0,1, 1,0,0,0,1, 1,1,1,1,1, 1,0,0,0,1, 1,0,0,0,1, 1,0,0,0,1 }; //A
    int p2[35] = { 1,1,1,1,1, 1,0,0,0,0, 1,0,0,0,0, 1,0,0,0,0, 1,0,0,0,0, 1,0,0,0,0, 1,1,1,1,1 }; //C
    double n = 0.5;
    double Emin = 0.001;
    double Cmax = 2000;
    double weights[35];
    int target;
    int k = 0;

    std::cout << "----------------ZBIOR UCZACY---------------------" << std::endl;

    while (k < 35)
    {
        for (int j = 0; j < 5; j++)
        {
            if (p1[k + j] == 1)
                std::cout << "*" << " ";                              // WYSWIETLANIE 1 LITERY Z UCZENIA
            else
                std::cout << "  ";
        }
        std::cout << std::endl;
        k += 5;
    }
    std::cout << std::endl;

    k = 0;
    while (k < 35)
    {
        for (int j = 0; j < 5; j++)
        {
            if (p2[k + j] == 1)
                std::cout << "*" << " ";                             // WYSWIETLANIE 2 LITERY Z UCZENIA
            else
                std::cout << "  ";
        }
        std::cout << std::endl;
        k += 5;
    }
    std::cout << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-0.5, 0.5);

    for (int i = 0; i < 35; i++) {
        weights[i] = dis(gen);
    }

    int c = 0;
    double Err = 0;
    while (c < Cmax)
    {
        double input = 0;
        double output = 0;
        Err = 0;

        if (c%2==0)
        {
            target = 0;
            for (int i = 0; i < 35; i++)
            {
                input += p1[i] * weights[i];
            }
            output = f(input);
            for (int i = 0; i < 35; i++)
            {
                weights[i] += n * (target - output) * (1 - output) * p1[i] * output;
            }
            Err += 0.5 * (pow((target - output), 2));
        }
        else
        {
            target = 1;
            for (int i = 0; i < 35; i++)
            {
                input += p2[i] * weights[i];
            }
            output = f(input);
            for (int i = 0; i < 35; i++)
            {
                weights[i] += n * (target - output) * (1 - output) * p2[i] * output;
            }
            Err += 0.5 * pow((target - output), 2);
        }
        n *= 0.98;
        if (Err < 0.001)
            break;
        c++;
    }
    std::cout << "FINAL ERROR: " << Err << std::endl;
    int p3[35] = { 1,1,1,1,1, 0,0,0,0,1, 1,1,0,0,1, 1,1,1,1,1, 1,0,1,0,1, 1,0,1,1,0, 1,0,0,0,1 }; //A
    int p4[35] = { 1,1,0,1,1, 1,0,1,0,0, 1,0,0,0,0, 0,0,0,0,0, 1,0,0,0,0, 1,0,1,1,0, 1,1,0,1,1 }; //C 


    std::cout << "----------------ZBIOR TESTUJACY---------------------" << std::endl << std::endl;

    k = 0;
    while (k < 35)
    {
        for (int j = 0; j < 5; j++)
        {
            if (p3[k + j] == 1)
                std::cout << "*" << " ";                   // WYSWIETLANIE 1 LITERY Z TESTU
            else
                std::cout << "  ";
        }
        std::cout << std::endl;
        k += 5;
    }
    std::cout << std::endl;

    double input2 = 0.0;
    for (int i = 0; i < 35; i++)
    {
        input2 += p3[i] * weights[i];
    }
    double output2 = f(input2);

    if (output2 < 0.5)
        std::cout << output2 << " : " << "A" << std::endl << std::endl;
    else
        std::cout << output2 << " : " << "C" << std::endl << std::endl;

    double input3 = 0.0;

    k = 0;
    while (k < 35)
    {
        for (int j = 0; j < 5; j++)
        {
            if (p4[k + j] == 1)
                std::cout << "*" << " ";                    // WYSWIETLANIE 2 LITERY Z TESTU
            else
                std::cout << "  ";
        }
        std::cout << std::endl;
        k += 5;
    }
    std::cout << std::endl;

    for (int i = 0; i < 35; i++)
    {
        input3 += p4[i] * weights[i];
    }
    double output3 = f(input3);

    if (output3 < 0.5)
        std::cout << output3 << " : " << "A" << std::endl;
    else
        std::cout << output3 << " : " << "C" << std::endl;

    return 0;
}

