#ifndef FSM_H
#define FSM_H

#define MAX_FSM_NAME_SIZE 32
#define MAX_INPT_BUFFER_LEN 128
#define MAX_STATE_NAME_SIZE 32
#define MAX_TRANSITION_TABLE_SIZE 128
#define MAX_TRANSITION_KEY_SIZE 64

typedef struct fsm_ fsm_t;                           /* opaque data structure */
typedef struct state_ state_t;                       /* opaque data structure */
typedef struct transition_table_entry_ tt_entry_t;   /* opaque data structure */
typedef struct transition_table_ tt_t;               /* opaque data structure */

/* API declaration */
fsm_t*
create_new_fsm(const char*); /* creates new FSM machine and return its pointer */

state_t*
create_new_state(char*, fsm_bool_t);

void
set_fsm_initial_state(fsm_t*, state_t*);

tt_entry_t*
create_and_insert_new_tt_entry(tt_t*, char*, unsigned int, state_t*);

#endif
