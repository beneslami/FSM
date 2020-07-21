#ifndef FSM_H
#define FSM_H

#define MAX_FSM_OUTPUT_BUFFER 1024
#define MAX_FSM_NAME_SIZE 32
#define MAX_INPT_BUFFER_LEN 128
#define MAX_STATE_NAME_SIZE 32
#define MAX_TRANSITION_TABLE_SIZE 128
#define MAX_TRANSITION_KEY_SIZE 64

typedef struct fsm_ fsm_t;                           /* opaque data structure */
typedef struct state_ state_t;                       /* opaque data structure */
typedef struct transition_table_entry_ tt_entry_t;   /* opaque data structure */
typedef struct transition_table_ tt_t;               /* opaque data structure */
typedef enum {
    FSM_FALSE,
    FSM_TRUE
}fsm_bool_t;
typedef enum {
  FSM_NO_TRANSITION,
  FSM_NO_ERROR
}fsm_error_t;
typedef unsigned int (*input_fn)(   /* Returns the size of input buffer read */
  char*,                            /* Input Buffer */
  unsigned int,                     /* Size of Input Buffer */
  unsigned int,                     /* Starting position to read the buffer */
  char*,                            /* Data Read */
  unsigned int*,                    /* Size of Data Read */
  unsigned int);                    /* Max len of read out buffer */
typedef void (*output_fn)(
  state_t*,
  state_t*,
  char*,                            /* Input buff */
  unsigned int,                     /* size of Input buffer */
  fsm_output_buffer_t*);            /* Output buffer */

/* API declaration */
fsm_t*
create_new_fsm(const char*);

state_t*
create_new_state(char*, fsm_bool_t);

void
set_fsm_initial_state(fsm_t*, state_t*);

void
set_fsm_default_input_fn(fsm_t *fsm, input_fn);

void
set_fsm_default_output_fn(fsm_t *fsm, output_fn);

tt_entry_t*
create_and_insert_new_tt_entry(tt_t*, char*, unsigned int, output_fn, state_t*);

fsm_error_t
execute_fsm(fsm_t*, char*, unsigned int, fsm_output_buffer_t, fsm_bool_t* /*result*/);

char*
get_fsm_output_string(fsm_t*);

#endif
