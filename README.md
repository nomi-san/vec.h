<p>
    <h1 align="center">vec.h</h1>
    <p align="center">
        Single header supports generic vector in pure C, under 50 sloc.<br />
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
    // Initialize
    vec_init(arr);

    // Push a value
    vec_push(arr, 20);
    vec_push(arr, 30);

    vec_foreach(arr, int, i) {
        printf("%d\n", i);
    }
    
    // Pop the last element
    printf("%d\n", vec_pop(arr));

    // Release
    vec_free(arr);
}
```
