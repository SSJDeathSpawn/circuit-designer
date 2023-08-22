#include "basic.h"
#include <math.h>

Vector2f add_vectors(Vector2f addend1, Vector2f addend2) {
    return (Vector2f) {.x = addend1.x+addend2.x, .y = addend1.y+addend2.y};
}

Vector2f sub_vectors(Vector2f minuend, Vector2f subtrahend) {
    return (Vector2f) {.x = minuend.x - subtrahend.x, .y = minuend.y - subtrahend.y};
}

Vector2f scalar_mul(Vector2f vec, float scalar) {
    return (Vector2f) {.x = vec.x*scalar, .y=vec.y*scalar};
}

float magnitude(Vector2f self) {
    return (float) sqrt(self.x*self.x + self.y*self.y);
}

float dot_product(Vector2f u, Vector2f v) { 
    return u.x * v.x + u.y * v.y;
}
