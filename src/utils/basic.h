#ifndef BASIC_H
#define BASIC_H
#include <glad/glad.h>

typedef struct Vector2f {
    GLfloat x;
    GLfloat y;
} Vector2f;

typedef struct Colour {
    GLfloat r, g, b, a;
} Colour;

typedef struct Vertex {
    Vector2f pos;
    Colour colour;
} Vertex;

Vector2f add_vectors(Vector2f addend1, Vector2f addend2);

Vector2f sub_vectors(Vector2f minuend, Vector2f subtrahend);

Vector2f scalar_mul(Vector2f vec, float scalar);

float magnitude(Vector2f self); 

float dot_product(Vector2f u, Vector2f v);

#endif
