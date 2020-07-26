#ifndef FSM_H
#define FSM_H

#include <assert.h>

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
typedef struct fsm_output_buff_ fsm_output_buff_t;   /* opaque data structure */
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
  fsm_output_buff_t*);            /* Output buffer */

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
execute_fsm(fsm_t*, char*, unsigned int, fsm_output_buff_t, fsm_bool_t* /*result*/);

/*char*
get_fsm_output_string(fsm_t*);

char*
get_transition_table_entry_key(tt_entry_t*);

unsigned int
get_transition_table_entry_key(tt_entry_t*);

state_t*
get_transition_table_entry_key(tt_entry_t*);

fsm_bool_t
get_state_fsm_bool(state_t*);

state_t*
get_fsm_initial_state(fsm_t*);

char*
get_fsm_name(fsm_t*);

char*
get_fsm_input_buffer(fsm_t*);

unsigned int
get_fsm_input_buffer_size(fsm_t*);
char*
get_state_name(state_t*);*/

tt_t
get_state_transition_table(state_t*);

char*
fsm_output_buffer(fsm_output_buff_t*);

unsigned int
fsm_curser_position(fsm_output_buff_t*);

#define FSM_ITERATE_BEGIN(transition_table, entry_ptr)      \
  do{                                                       \
      unsigned int index = 0;                               \
      for(; index < MAX_TRANSITION_TABLE_SIZE; index++){    \
        entry_ptr = &(transition_table->tt_entry_t[index]); \
        if(is_tt_entry_empty(entry_ptr) == FSM_TRUE)        \
        break;                                              \

#define FSM_ITERATE_END(transition_table, entry_ptr)        \
}}while(0);

#endif
