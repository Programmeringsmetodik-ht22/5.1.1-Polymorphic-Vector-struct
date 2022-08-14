/*******************************************************************************
* main.c: Implementering av vektorer av olika datatyper via anv�ndning av den
*         polymorfa strukten vector.
*
*         Kompilera programmet via GCC-kompilatorn och skapa en k�rbar fil
*         d�pt main.exe med f�ljande kommando:
*         $ gcc main.c vector.c main.exe -o Wall
*
*         F�r att k�ra programmet med vektorstorlekar x, y, och z, mata in
*         f�ljande kommando (ers�tt x, y och z med �nskade storlekar).
*         $ main.exe x y z
*
*         Som exempel, f�r att lagra 10 signerade heltal, 4 flyttal samt
*         6 osignerade heltal via var sin vektor skrivs f�ljande kommando:
*         $ main.exe 10 4 6
*******************************************************************************/
#include "vector.h"

/*******************************************************************************
* main: Initierar tre vektorer av datatyper int, double samt size_t. Storleken
*       f�r respektive vektor l�ses in fr�n terminalen via parametrar passerade
*       vid programk�rning. Vektorerna fylls till bredden med tal av den
*       datatyp de tillh�r, f�ljt av att deras respektive inneh�ll skrivs ut i
*       terminalen.
*       - argc: Antalet argument inl�sta fr�n terminalen vid start.
*       - argv: Array inneh�llande argument inl�sta fr�n terminalen.
*******************************************************************************/
int main(const int argc,
         const char** argv)
{
   struct vector v1, v2, v3;

   struct vector* vectors[] = { &v1, &v2, &v3 };
   const size_t num_vectors = sizeof(vectors) / sizeof(struct vector*);

   int integer = 0;
   double decimal = -100.0;
   size_t natural = 50;

   if (argc != 4)
   {
      fprintf(stderr, "Error! Too few command line arguments were entered!\n");
      return 1;
   }

   vector_new(&v1, VECTOR_TYPE_INTEGER);
   vector_new(&v2, VECTOR_TYPE_DOUBLE);
   vector_new(&v3, VECTOR_TYPE_UNSIGNED);

   vector_resize(&v1, (size_t)(atoi(argv[1])));
   vector_resize(&v2, (size_t)(atoi(argv[2])));
   vector_resize(&v3, (size_t)(atoi(argv[3])));

   for (size_t i = 0; i < v1.size; ++i)
   {
      vector_set(&v1, i, &integer);
      integer += 2;
   }
   for (size_t i = 0; i < v2.size; ++i)
   {
      vector_set(&v2, i, &decimal);
      decimal = decimal / 2;
   }
   for (size_t i = 0; i < v3.size; ++i)
   {
      vector_set(&v3, i, &natural);
      natural--;
   }

   for (struct vector** i = vectors; i < vectors + num_vectors; ++i)
   {
      vector_print(*i, stdout);
   }

   return 0;
}

