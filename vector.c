/*******************************************************************************
* vector.c: Inneh�ller funktioner f�r implementering av dynamiska vektorer
*           av olika datatyper via strukten vector.
*******************************************************************************/
#include "vector.h"

/* Statiska funktioner: */
static inline void vector_ptr_init(union vector_ptr* self);
static void vector_ptr_free(union vector_ptr* self,
                            const enum vector_type type);

/*******************************************************************************
* vector_new: Initierar ny tom vektor till angiven datatyp.
*             - self: Pekare till vektorn som skall initieras.
*             - type: Vektorns datatyp.
*******************************************************************************/
void vector_new(struct vector* self,
                const enum vector_type type)
{
   self->type = type;
   vector_ptr_init(&self->data);
   self->size = 0;
   return;
}

/*******************************************************************************
* vector_delete: Nollst�ller angiven vektor och frig�r heapallokerat f�lt.
*                - self: Pekare till vektorn.
*******************************************************************************/
void vector_delete(struct vector* self)
{
   vector_ptr_free(&self->data, self->type);
   self->size = 0;
   self->type = VECTOR_TYPE_NONE;
   return;
}

/*******************************************************************************
* vector_ptr_new: Returnerar pekare till en ny heapallokerad vektor med angiven
*                 storlek. Vid start �r samtliga element oinitierade.
*                 - type: Vektorns datatyp.
*                 - size: Vektorns storlek vid start (antalet element).
*******************************************************************************/
struct vector* vector_ptr_new(const enum vector_type type,
                              const size_t size)
{
   struct vector* self = (struct vector*)malloc(sizeof(struct vector));
   if (!self) return 0;
   vector_new(self, type);
   vector_resize(self, size);
   return self;
}

/*******************************************************************************
* vector_ptr_delete: Raderar heapallokerad vektor genom att frig�ra allt minne.
*                    Adressen till vektorpekaren passeras f�r att b�de kunna
*                    frig�ra allokerat minne samt s�tta vektorpekaren till noll
*                    efter deallokeringen �r genomf�rd.
*                    - self: Adressen till vektorpekaren.
*******************************************************************************/
void vector_ptr_delete(struct vector** self)
{
   vector_delete(*self);
   *self = 0;
   return;
}

/*******************************************************************************
* vector_begin: Returnerar adressen till f�rsta elementet i angiven vektor.
*               - self: Pekare till vektorn.
*******************************************************************************/
void* vector_begin(const struct vector* self)
{
   if (self->type == VECTOR_TYPE_INTEGER)
   {
      return self->data.integer;
   }
   else if (self->type == VECTOR_TYPE_DOUBLE)
   {
      return self->data.decimal;
   }
   else if (self->type == VECTOR_TYPE_UNSIGNED)
   {
      return self->data.natural;
   }
   else
   {
      return 0;
   }
}

/*******************************************************************************
* vector_end: Returnerar pekare till slutet p� angiven vektor, allts� adressen
*             direkt efter sista befintliga element.
*             - self: Pekare till vektorn.
*******************************************************************************/
void* vector_end(const struct vector* self)
{
   if (self->type == VECTOR_TYPE_INTEGER)
   {
      return self->data.integer + self->size;
   }
   else if (self->type == VECTOR_TYPE_DOUBLE)
   {
      return self->data.decimal + self->size;
   }
   else if (self->type == VECTOR_TYPE_UNSIGNED)
   {
      return self->data.natural + self->size;
   }
   else
   {
      return 0;
   }
}

/*******************************************************************************
* vector_resize: �ndrar storlek/kapacitet p� given vektor.
*                - self: Pekare till vektorn.
*                - new_size: Vektorns nya storlek/kapacitet.
*******************************************************************************/
int vector_resize(struct vector* self,
                  const size_t new_size)
{
   if (!new_size)
   {
      vector_delete(self);
   }
   else
   {
      if (self->type == VECTOR_TYPE_INTEGER)
      {
         int* copy = (int*)realloc(self->data.integer, sizeof(int) * new_size);
         if (!copy) return 1;
         self->data.integer = copy;
         self->size = new_size;
      }
      else if (self->type == VECTOR_TYPE_DOUBLE)
      {
         double* copy = (double*)realloc(self->data.decimal, sizeof(double) * new_size);
         if (!copy) return 1;
         self->data.decimal = copy;
         self->size = new_size;
      }
      else if (self->type == VECTOR_TYPE_UNSIGNED)
      {
         size_t* copy = (size_t*)realloc(self->data.natural, sizeof(size_t) * new_size);
         if (!copy) return 1;
         self->data.natural = copy;
         self->size = new_size;
      }
      else
      {
         return 1;
      }
   }
   return 0;
}

/*******************************************************************************
* vector_push: L�gger till ett nytt element l�ngst bak i angiven vektor.
*              - self: Pekare till vektorn.
*              - new_element: Pekare till det nya elementet.
*******************************************************************************/
int vector_push(struct vector* self,
                const void* new_element)
{
   if (self->type == VECTOR_TYPE_INTEGER)
   {
      int* copy = (int*)realloc(self->data.integer, sizeof(int) * (self->size + 1));
      if (!copy) return 1;
      copy[self->size++] = *(int*)new_element;
      self->data.integer = copy;
   }
   else if (self->type == VECTOR_TYPE_DOUBLE)
   {
      double* copy = (double*)realloc(self->data.decimal, sizeof(double) * (self->size + 1));
      if (!copy) return 1;
      copy[self->size++] = *(double*)new_element;
      self->data.decimal = copy;
   }
   else if (self->type == VECTOR_TYPE_UNSIGNED)
   {
      size_t* copy = (size_t*)realloc(self->data.natural, sizeof(size_t) * (self->size + 1));
      if (!copy) return 1;
      copy[self->size++] = *(size_t*)new_element;
      self->data.natural = copy;
   }
   else
   {
      return 1;
   }
   return 0;
}

/*******************************************************************************
* vector_pop: Tar bort sista lagrade element i angiven vektor.
*             - self: Pekare till vektorn.
*******************************************************************************/
int vector_pop(struct vector* self)
{
   if (self->size <= 1)
   {
      vector_delete(self);
   }
   else
   {
      if (self->type == VECTOR_TYPE_INTEGER)
      {
         int* copy = (int*)realloc(self->data.integer, sizeof(int) * (self->size - 1));
         if (!copy) return 1;
         self->data.integer = copy;
         self->size--;
      }
      else if (self->type == VECTOR_TYPE_DOUBLE)
      {
         double* copy = (double*)realloc(self->data.decimal, sizeof(double) * (self->size - 1));
         if (!copy) return 1;
         self->data.decimal = copy;
         self->size--;
      }
      else if (self->type == VECTOR_TYPE_UNSIGNED)
      {
         size_t* copy = (size_t*)realloc(self->data.natural, sizeof(size_t) * (self->size - 1));
         if (!copy) return 1;
         self->data.natural = copy;
         self->size--;
      }
      else
      {
         return 1;
      }
   }
   return 0;
}

/*******************************************************************************
* vector_set: L�gger in ett nytt element p� angivet index.
*             - self: Pekare till vektorn.
*             - index: Index d�r det nya elementet skall placeras.
*             - val: Pekare till det nya elementet.
*******************************************************************************/
void vector_set(struct vector* self,
                const size_t index,
                const void* val)
{
   if (index < self->size)
   {
      if (self->type == VECTOR_TYPE_INTEGER)
      {
         self->data.integer[index] = *(int*)val;
      }
      else if (self->type == VECTOR_TYPE_DOUBLE)
      {
         self->data.decimal[index] = *(double*)val;
      }
      else if (self->type == VECTOR_TYPE_UNSIGNED)
      {
         self->data.natural[index] = *(size_t*)val;
      }
   }
   return;
}

/*******************************************************************************
* vector_get: Returnerar pekare till elementet lagrat p� angivet index i
*             angiven vektor. D�rmed returneras elementets adress.
*             - self: Pekare till vektorn.
*             - index: Index till elementet som skall returneras.
*******************************************************************************/
void* vector_get(struct vector* self,
                 const size_t index)
{
   if (index >= self->size)
   {
      return 0;
   }
   else
   {
      if (self->type == VECTOR_TYPE_INTEGER)
      {
         return &self->data.integer[index];
      }
      else if (self->type == VECTOR_TYPE_DOUBLE)
      {
         return &self->data.decimal[index];
      }
      else if (self->type == VECTOR_TYPE_UNSIGNED)
      {
         return &self->data.natural[index];
      }
   }
   return 0;
}

/*******************************************************************************
* vector_print: Skriver ut samtliga element lagrade i vektor p� var sin rad
*               via angiven utstr�m, d�r standardutenhet stdout anv�nds som
*               default f�r utskrift i terminalen. Vektorns inneh�ll kan vid
*               behov skrivas till en fil genom att �ppna en fil f�r skrivning
*               eller bifogning via en filpekare och passera denna pekare.
*               - self: Pekare till vektorn.
*               - ostream: Pekare till angiven utstr�m.
*******************************************************************************/
void vector_print(const struct vector* self,
                  FILE* ostream)
{
   if (!self->size) return;
   if (!ostream) ostream = stdout;
   fprintf(ostream, "--------------------------------------------------------------------------------\n");

   for (size_t i = 0; i < self->size; ++i)
   {
      if (self->type == VECTOR_TYPE_INTEGER)
      {
         fprintf(ostream, "%d\n", self->data.integer[i]);
      }
      else if (self->type == VECTOR_TYPE_DOUBLE)
      {
         fprintf(ostream, "%g\n", self->data.decimal[i]);
      }
      else if (self->type == VECTOR_TYPE_UNSIGNED)
      {
         fprintf(ostream, "%zu\n", self->data.natural[i]);
      }
   }

   fprintf(ostream, "--------------------------------------------------------------------------------\n\n");
   return;
}

/*******************************************************************************
* vector_clear: Nollst�ller angiven vektor och frig�r heapallokerat f�lt.
*               - self: Pekare till vektorn.
*******************************************************************************/
void (*vector_clear)(struct vector* self) = &vector_delete;

/*******************************************************************************
* vector_ptr_init: Initierar pekare implementering av en polymorf vektor.
*                  - self: Pekare till en union inneh�llande multipla pekare.
*******************************************************************************/
static inline void vector_ptr_init(union vector_ptr* self)
{
   self->integer = 0;
   self->decimal = 0;
   self->natural = 0;
   return;
}

/*******************************************************************************
* vector_ptr_free: Frig�r minne f�r dynamiskt f�lt.
*                  - self: Unionpekare till minnet som skall frig�ras.
*                  - type: F�ltets datatyp (avg�r vilken av unionpekarens
*                          pekar som pekar p� det allokerade minnet).
*******************************************************************************/
static void vector_ptr_free(union vector_ptr* self,
                            const enum vector_type type)
{
   if (type == VECTOR_TYPE_INTEGER)
   {
      free(self->integer);
   }
   else if (type == VECTOR_TYPE_DOUBLE)
   {
      free(self->decimal);
   }
   else if (type == VECTOR_TYPE_UNSIGNED)
   {
      free(self->natural);
   }

   self->integer = 0;
   self->decimal = 0;
   self->natural = 0;
   return;
}