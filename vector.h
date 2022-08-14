/*******************************************************************************
* vector.h: Implementering av dynamiska vektorer, som kan lagra b�de signerade
*           och osignerade heltal samt flyttal.
*******************************************************************************/
#ifndef VECTOR_H_
#define VECTOR_H_

/* Inkluderingsdirektiv: */
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
* vector_type: Datatyp f�r dynamisk vektor, som kan v�ljas mellan signerade
*              och osignerade heltal samt flyttal.
*******************************************************************************/
enum vector_type
{
   VECTOR_TYPE_INTEGER,  /* F�lt f�r lagring av signerade heltal. */
   VECTOR_TYPE_DOUBLE,   /* F�lt f�r lagring av flyttal. */
   VECTOR_TYPE_UNSIGNED, /* F�lt f�r lagring av osignerade heltal. */
   VECTOR_TYPE_NONE      /* Icke angiven datatyp. */
};

/*******************************************************************************
* vector_ptr: Union inneh�llande pekare f�r dynamiska f�lt av olika datatyper,
*             men allokerar enbart minne f�r en pekare.
*******************************************************************************/
union vector_ptr
{
   int* integer;    /* Pekare till f�lt inneh�llande signerade heltal. */
   double* decimal; /* Pekare till f�lt inneh�llande flyttal. */
   size_t* natural; /* Pekare till f�lt inneh�llande osignerade heltal. */
};

/*******************************************************************************
* vector: Implementering av dynamisk vektor, som kan lagra element av multipla
*         datatyper; signerade heltal (int), flyttal (double) samt signerade
*         heltal (size_t / unsigned long long).
*******************************************************************************/
struct vector
{
   union vector_ptr data; /* Pekare till dynamiskt f�lt. */
   enum vector_type type; /* Vektorns datatyp. */
   size_t size;           /* Vektorns storlek (antalet lagrade element). */
};

/* Externa funktioner: */
void vector_new(struct vector* self, 
                const enum vector_type type);
void vector_delete(struct vector* self);
struct vector* vector_ptr_new(const enum vector_type type,
                              const size_t size);
void vector_ptr_delete(struct vector** self);
void* vector_begin(const struct vector* self);
void* vector_end(const struct vector* self);
int vector_resize(struct vector* self,
                  const size_t new_size);
int vector_push(struct vector* self,
                const void* new_element);
int vector_pop(struct vector* self);
void vector_set(struct vector* self,
                const size_t index,
                const void* val);
void* vector_get(struct vector* self,
                 const size_t index);
void vector_print(const struct vector* self,
                  FILE* ostream);

/* Funktionspekare: */
extern void (*vector_clear)(struct vector* self);

#endif /* VECTOR_H_ */