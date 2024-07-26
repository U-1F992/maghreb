#include <maghreb.h>

#include <assert.h>

static maghreb_deserialize_result_t print(unsigned char *buffer, size_t count,
                                          void *output) {
    size_t i = 0;
    maghreb_unused(output);
    printf("count:%d,buffer:{", count);
    for (i = 0; i < count; i++) {
        printf("%d%s", buffer[i], i != count - 1 ? "," : "}");
    }
    printf("\n");
    return MAGHREB_DESERIALIZE_SUCCESS;
}

static void *accept_0(unsigned char input,
                      maghreb_deserializer_t *out_deserializer) {
    return input == 0 ? (*out_deserializer = print, maghreb_accepted)
                      : maghreb_rejected;
}

static void *accept_1(unsigned char input,
                      maghreb_deserializer_t *out_deserializer) {
    return input == 1 ? (*out_deserializer = print, maghreb_accepted)
                      : maghreb_rejected;
}

static void *accept_0_0(unsigned char input,
                        maghreb_deserializer_t *out_deserializer) {
    maghreb_unused(out_deserializer);
    return input == 0 ? accept_0 : maghreb_rejected;
}

static void *accept_1_0(unsigned char input,
                        maghreb_deserializer_t *out_deserializer) {
    maghreb_unused(out_deserializer);
    return input == 1 ? accept_0 : maghreb_rejected;
}

static void *accept_1_1(unsigned char input,
                        maghreb_deserializer_t *out_deserializer) {
    maghreb_unused(out_deserializer);
    return input == 1 ? accept_1 : maghreb_rejected;
}

static void *accept_0_1_0(unsigned char input,
                          maghreb_deserializer_t *out_deserializer) {
    maghreb_unused(out_deserializer);
    return input == 0 ? accept_1_0 : maghreb_rejected;
}

static void *accept_0_1_1(unsigned char input,
                          maghreb_deserializer_t *out_deserializer) {
    maghreb_unused(out_deserializer);
    return input == 0 ? accept_1_1 : maghreb_rejected;
}

int main(void) {
    unsigned char buffer_0[] = {0};
    unsigned char buffer_0_0[] = {0, 0};
    unsigned char buffer_0_1_1[] = {0, 1, 1};

    maghreb_transition_t transition = accept_0;
    maghreb_deserializer_t deserializer = NULL;
    assert((transition = transition(1, &deserializer)) == maghreb_rejected &&
           deserializer == NULL);

    transition = accept_0;
    deserializer = NULL;
    assert((transition = transition(buffer_0[0], &deserializer)) ==
               maghreb_accepted &&
           deserializer != NULL);
    deserializer(buffer_0, sizeof(buffer_0), NULL);

    transition = accept_0_0;
    deserializer = NULL;
    assert((transition = transition(buffer_0_0[0], &deserializer)) ==
               accept_0 &&
           deserializer == NULL);
    assert((transition = transition(buffer_0_0[1], &deserializer)) ==
               maghreb_accepted &&
           deserializer != NULL);
    deserializer(buffer_0_0, sizeof(buffer_0_0), NULL);

    maghreb_register_initial_transitions(
        (maghreb_transition_t[]){accept_0_0, accept_0_1_0, accept_0_1_1}, 3);
    transition = maghreb_initial;
    deserializer = NULL;
    assert((transition = transition(buffer_0_1_1[0], &deserializer)) ==
               maghreb_initial &&
           deserializer == NULL);
    assert((transition = transition(buffer_0_1_1[1], &deserializer)) ==
               maghreb_initial &&
           deserializer == NULL);
    assert((transition = transition(buffer_0_1_1[2], &deserializer)) ==
               maghreb_accepted &&
           deserializer != NULL);
    deserializer(buffer_0_1_1, sizeof(buffer_0_1_1), NULL);

    return 0;
}
