#include <stdio.h>

float areaCircle(float radius) {
return radius*radius*3.14f;
}

int main() {
float radius = 0;
printf("L'indirizzo di radius in memoria attualmente è: %u \n", &radius);
printf("Fornire il raggio prego: ");
printf("Risultato operazione scanf %d \n", scanf("%f", &radius));
printf("L'area di un cerchio di raggio %f ipotizzando che il pi greco sia %f è %f \n", radius, 3.14f, areaCircle(radius));
}


