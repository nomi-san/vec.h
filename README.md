<p>
    <h1 align="center">vec.h</h1>
    <p align="center">
        Single header supports generic vector in pure C, under 80 sloc.<br />
        Inspired by C++ and JavaScript.
    </p>
</p>

### Docs

See [vec.h](https://github.com/nomi-san/vec.h/blob/main/vec.h) for details.

### Example

```c
#include "vec.h"

int main() {
    // Declare int vector
    vec(int) arr;
    // Initizlize
    vec_init(arr);

    // Push value
    vec_push(arr, 20);
    vec_push(arr, 30);
    vec_push(arr, 40);
    vec_push(arr, 50);
    vec_push(arr, 60);
    vec_push(arr, 70);
    vec_push(arr, 80);
    vec_push(arr, 90);

    // Clone new vector
    vec(int) arr2 = vec_clone(arr);
    
    // Remove the first element
    printf("%d\n", vec_shift(arr))
    // Remove the last element
    printf("%d\n", vec_pop(arr))
    
    // Reverse arr
    vec_reverse(arr);
    // Merge arr2 -> arr
    vec_concat(arr, arr2);

    vec_foreach(arr, int, i) {
        printf("%d\n", i);
    }

    // Release
    vec_free(arr);
    vec_free(arr2);
}
```
