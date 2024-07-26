#ifndef MAGHREB_H
#define MAGHREB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>

#define maghreb_unused(x) (void)(x)

typedef enum maghreb_deserialize_result_t {
    MAGHREB_DESERIALIZE_FAILURE,
    MAGHREB_DESERIALIZE_SUCCESS
} maghreb_deserialize_result_t;

typedef maghreb_deserialize_result_t (*maghreb_deserializer_t)(unsigned char *,
                                                               size_t, void *);
/**
 * C language does not allow the declaration of a function pointer type
 * that returns another function pointer of the same type.
 * Consequently, a cast from `void *` is required on each usage.
 */
typedef void *(*maghreb_transition_t)(unsigned char, maghreb_deserializer_t *);

void *maghreb_rejected(unsigned char, maghreb_deserializer_t *);
void *maghreb_accepted(unsigned char, maghreb_deserializer_t *);

#ifndef MAGHREB_INITIAL_TRANSITIONS_MAX
#define MAGHREB_INITIAL_TRANSITIONS_MAX 8
#endif

void maghreb_register_initial_transitions(maghreb_transition_t *, size_t);
void *maghreb_initial(unsigned char, maghreb_deserializer_t *);

#ifdef __cplusplus
}
#endif

#endif /* MAGHREB_H */