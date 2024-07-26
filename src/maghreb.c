#include <maghreb.h>

void *maghreb_rejected(unsigned char input, maghreb_deserializer_t *output) {
    maghreb_unused(input);
    maghreb_unused(output);
    return maghreb_rejected;
}

void *maghreb_accepted(unsigned char input, maghreb_deserializer_t *output) {
    maghreb_unused(input);
    maghreb_unused(output);
    return maghreb_rejected;
}

static maghreb_transition_t initial_transitions[MAGHREB_INITIAL_TRANSITIONS_MAX];
static size_t initial_transitions_count = 0;
static maghreb_transition_t pending[MAGHREB_INITIAL_TRANSITIONS_MAX];
static size_t pending_count = 0;

void maghreb_register_initial_transitions(maghreb_transition_t *transitions, size_t count) {
    memcpy(
        initial_transitions, transitions,
        (count <= MAGHREB_INITIAL_TRANSITIONS_MAX ? count : MAGHREB_INITIAL_TRANSITIONS_MAX) *
            sizeof(maghreb_transition_t));
    initial_transitions_count = count;
    pending_count = 0;
}
void *maghreb_initial(unsigned char input, maghreb_deserializer_t *output) {
    size_t i = 0;
    size_t new_pending_count = 0;

    maghreb_unused(output);

    if (pending_count == 0) {
        memcpy(pending, initial_transitions,
               initial_transitions_count * sizeof(maghreb_transition_t));
        pending_count = initial_transitions_count;
    }
    for (i = 0; i < pending_count; i++) {
        maghreb_transition_t t = (pending[i])(input, output);
        if (t == maghreb_accepted) {
            pending_count = 0;
            return t;
        } else if (t != maghreb_rejected) {
            pending[new_pending_count++] = t;
        }
    }

    if (new_pending_count == 1) {
        pending_count = 0;
        return pending[0];
    } else {
        pending_count = new_pending_count;
        return maghreb_initial;
    }
}