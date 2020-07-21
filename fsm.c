#include "fsm.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef enum {
    FSM_FALSE,
    FSM_TRUE
}fsm_bool_t;

struct transition_table_entry_ {
  char transition_key[MAX_TRANSITION_KEY_SIZE];
  unsigned int transition_key_size;
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
  char input_buffer[MAX_INPT_BUFFER_LENG]; /* Application provided input data to parse by FSM */
  unsigned int input_buffer_size; /* Length of above data */
};

fsm_t*
create_new_fsm(const char *fsm_name){
  fsm_t *fsm = calloc(1, sizeof(fsm_t));
  strncpy(fsm->fsm_name, fsm_name, MAX_FSM_NAME_SIZE - 1);
  fsm->fsm_name[MAX_FSM_NAME_SIZE] = '\0';
  return fsm;
}

state_t*
create_new_state(char *state_name, fsm_bool_t is_final){
  assert(state_name);
  state_t *state = calloc(1, sizeof(state_t));
  strncpy(state->state_name, state_name, MAX_STATE_NAME_SIZE - 1);
  state->state_name[MAX_STATE_NAME_SIZE] = '\0';
  state->final = is_final;
  return state;
}

void
set_fsm_initial_state(fsm_t *fsm, state_t *state){
  assert(!fsm->initial_state);
  fsm->initial_state = state;
}

tt_entry_t*
create_and_insert_new_tt_entry(tt_t *transition_table, char *transition_key, unsigned int sizeof_key, state_t *next_state){
  assert(sizeof_key < MAX_TRANSITION_KEY_SIZE);
  tt_entry_t *tt_entry_ptr = get_next_empty_tt_entry(trans_table);
  if(!tt_entry_ptr){
    printf("FATAL : Transition Table is Full\n");
    return;
  }
  memcpy(tt_entry_ptr->transition_key, transition_key, sizeof_key);
  tt_entry_ptr->transition_key[sizeof_key]= '\0';
  tt_entry_ptr->transition_key_size = sizeof_key;
  tt_entry_ptr->next_state = next_state;
}
