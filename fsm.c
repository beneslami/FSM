#include "fsm.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

struct transition_table_entry_ {
  char transition_key[MAX_TRANSITION_KEY_SIZE];
  unsigned int transition_key_size;
  outp_fn outp_fn;
  state_t *next_state;
};

struct transition_table_{
  tt_entry_t tt_entry_t[MAX_TRANSITION_TABLE_SIZE];
};

struct state_ {
  char state_name[MAX_STATE_NAME_SIZE]; /* Name of the state. must be unique within FSM */
  tt_t state_transition_table; /* Transition table of the state */
  fsm_bool_t is_final;  /* boolean if the state is final or not */
};

struct fsm_{
  state_t *initial_state;  /* initial state of FSM to start with */
  char fsm_name[MAX_FSM_NAME_SIZE];  /* Name of FSM */
  char input_buffer[MAX_INPT_BUFFER_LEN]; /* Application provided input data to parse by FSM */
  unsigned int input_buffer_size; /* Length of above data */
};

struct fsm_output_buff_{
  char output_buffer[MAX_FSM_OUTPUT_BUFFER];
  unsigned int curr_pos;
};

fsm_t*
create_new_fsm(const char *fsm_name){

}

state_t*
create_new_state(char *state_name, fsm_bool_t is_final){

}

void
set_fsm_initial_state(fsm_t *fsm, state_t *state){

}

static tt_entry_t*
get_next_empty_tt_entry(tt_t *transition_table){

}

tt_entry_t*
create_and_insert_new_tt_entry(tt_t *transition_table, char *transition_key, unsigned int sizeof_key, output_fn outp_fn, state_t *next_state){

}

fsm_error_t
execute_fsm(fsm_t *fsm, char *input_buffer, unsigned int size, fsm_bool_t *fsm_result){

}
