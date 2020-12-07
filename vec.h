#ifndef _VEC_H
#define _VEC_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Internal macros, do not use.
#define _vec_H_sz   (sizeof(size_t) * 2)
#define _vec_H(v)   (&(size_t *)(v)[-2])
#define _vec_V(b)   ((void *)&((b)[2]))
#define _vec_Co(v)  ((size_t *)(v))[-2]
#define _vec_Ca(v)  ((size_t *)(v))[-1]
#define _vec_Sz(v)  sizeof(*(v))
#define _vec_B(v)   (v)
#define _vec_E(v)   (&(v)[_vec_Co(v)])

// Growth factor.
#define vec_factor      2
// Initial capacity.
#define vec_init_size   8

/*
    interface vec<T> {
        void init();
        void free();
        size_t count();
        T &at(size_t);
        void push(T);
        T pop();
        void concat(vec<T>);
        vec<T> clone();
        void reverse();
        T shift();

        !foreach(T, var);
    }
*/

/**
 * Vector declaration.
 * @param T the type of the vector
 */
#define vec(T) T *

/**
 * Initialize the vector.
 * @param v - the vector
 */
#define vec_init(v) \
    do {                                    \
        size_t *base = malloc(_vec_H_sz +   \
             _vec_Sz(v) * vec_init_size);   \
        base[0] = 0;                        \
        base[1] = vec_init_size;            \
        (v) = _vec_V(base);                 \
    } while (0)

/**
 * Release allocated memory of the vector.
 * @param v - the vector
 */
#define vec_free(v) \
    ((v) ? free(_vec_H(v)) : (void)0)

/**
 * Get the length of the vector.
 * @param v - the vector
 * @return size_t
 */
#define vec_count(v) \
    (0, _vec_Co(v))

/**
 * Access an element by index (both lvalue and rvalue).
 * @param v - the vector
 * @param idx - the index
 * @return size_t
 */
#define vec_at(v, idx) \
    ((v)[idx])

/**
 * Push a value as the last element.
 * @param v - the vector
 * @param val - the value
 * @return size_t
 */
#define vec_push(v, val) \
    do {                                        \
        size_t *base = &((size_t *)(v))[-2];    \
        if (base[0] + 1 >= base[1])  {          \
            base = realloc(base,                \
                _vec_H_sz + _vec_Sz(v) *        \
                (base[1] *= vec_factor));       \
            (v) = _vec_V(base);                 \
        }                                       \
        (v)[base[0]++] = val;                   \
    } while (0)

/**
 * Pop the last element.
 * @param v - the vector
 * @return the last element
 */
#define vec_pop(v) \
    (0, (v)[--_vec_Co(v)])

/**
 * Merge with another vector.
 * @param v - the vector
 * @param v2 - the vector 2
 */
#define vec_concat(v, v2) \
    do {                                    \
        for (size_t i = 0, e = _vec_Co(v2); \
            i < e; i++) {                   \
            vec_push(v, vec_at(v2, i));     \
        }                                   \
    } while (0)

/**
 * Clone the vector.
 * @param v - the vector
 * @return the new vector
 */
#define vec_clone(v) \
    ((void *)((size_t)memcpy(malloc(                    \
        _vec_H_sz +_vec_Sz(v) * _vec_Ca(v)),            \
        _vec_H(v), _vec_H_sz + _vec_Sz(v) * _vec_Co(v)  \
        ) + _vec_H_sz))

/**
 * Iterate through the vevtor, like a statement.
 * @param v - the vector
 * @param T - the type of vector
 * @param it - the iterator variable name
 */
#define vec_foreach(v, T, it) \
    for (T it, *_vb = _vec_B(v), *_ve = _vec_E(v); \
        it = *_vb, _vb != _ve; ++_vb)

/**
 * Reverse order of all elements.
 * @param v - the vector
 */
#define vec_reverse(v) \
    do {                                            \
        size_t s = _vec_Co(v), e = _vec_Ca(v) - 1;  \
        for (size_t i = 0, m = s / 2; i < m; i++) { \
            vec_at(v, e) = vec_at(v, i);            \
            vec_at(v, i) = vec_at(v, s - 1 - i);    \
            vec_at(v, s - 1 - i) = vec_at(v, e);    \
        }                                           \
    } while (0)

/**
 * Remove the first element.
 * @param v - the vector
 * @return the first element
 */
#define vec_shift(v) \
    (vec_at(v, _vec_Ca(v) - 1) = vec_at(v, 0),      \
        memcpy((v), (v) + 1,                        \
            _vec_Sz(v) * _vec_Co(v)--),             \
        vec_at(v, _vec_Ca(v) - 1))

#endif