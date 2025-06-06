#include <stdio.h>
#include <math.h>

float hav(float theta)
{
    float res;
    res = pow(sin(theta / 2), 2);
    return res;
}

float graus2rad(float grau)
{
    float rad;
    rad = (3.1415 * grau) / 180;
    return rad;
}

float distancia_na_terra(float lat1, float lon1, float lat2, float lon2)
{
    float d;

    float cos_lat1 = cos(lat1);
    float cos_lat2 = cos(lat2);
    float hav1 = hav(lat2 - lat1);
    float hav2 = hav(lon2 - lon1);
    d = (2 * 6371) * asin(sqrt(hav2 + cos_lat1 * cos_lat2 * hav1));
    return d;
}

int main()
{
    float lat1, lon1, lat2, lon2, d;
    printf("Digite lat 1 lon 1: ");
    scanf("%f %f", &lat1, &lon1);
    printf("Digite lat 1 lon 1: ");
    scanf("%f %f", &lat2, &lon2);
    d = distancia_na_terra(lat1, lon1, lat2, lon2);
    printf("Distância: %.2f km\n", d);

    return 0;
}