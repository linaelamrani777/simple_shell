#include "shell.h"

/**
 * custom_realloc - Reallocates a pointer to double the space.
 * @ptr: Pointer to the old array
 * @size: Pointer to the number of elements in the old array
 *
 * Return: Pointer to the new array
 */
char **custom_realloc(char **ptr, size_t *size)
{
    const size_t increment = 10;
    char **new_ptr;
    size_t x;

    new_ptr = malloc(sizeof(char *) * ((*size) + increment));
    if (new_ptr == NULL)
    {
        return (NULL);
    }

    for (x = 0; x < (*size); x++)
    {
        new_ptr[x] = ptr[x];
    }

    *size += increment;
    free(ptr);
    return (new_ptr);
}
