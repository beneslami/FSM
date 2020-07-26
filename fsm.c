#include "fsm.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

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

struct fsm_output_buff_{
  char output_buffer[MAX_FSM_OUTPUT_BUFFER];
  unsigned int curr_pos;
};

char*
get_state_name(state_t *s){
  return s->state_name;
}

void
set_state_name(state_t *s, char *name){
  strcpy(s->state_name, name);
}

tt_t
get_state_transition_table(state_t *s){
  return s->state_transition_table;
}

fsm_bool_t
get_state_fsm_bool(state_t *s){
  return s->is_final;
}

state_t*
get_fsm_initial_state(fsm_t* fsm){
  return fsm->initial_state;
}

void
set_fsm_name(fsm_t* fsm, char *name){
  strcpy(fsm->fsm_name, name);
}

char*
get_fsm_name(fsm_t* fsm){
  return fsm->fsm_name;
}

char*
get_fsm_input_buffer(fsm_t *fsm){
  return fsm->input_buffer;
}

void
set_fsm_input_buffer(fsm_t* fsm, char *buffer){
  strcpy(fsm->input_buffer, buffer);
}

unsigned int
get_fsm_input_buffer_size(fsm_t *fsm){
  return fsm->input_buffer_size;
}

void set_fsm_input_buffer_size(fsm_t* fsm, int size){
  fsm->input_buffer_size = size;
}

char*
fsm_output_buffer(fsm_output_buff_t *fsm){
  return fsm->output_buffer;
}

unsigned int
fsm_curser_position(fsm_output_buff_t *fsm){
  retrun fsm->curr_pos;
}

char*
get_fsm_output_string(fsm_t *fsm){
  return fsm->input_buffer;
}

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

static tt_entry_t*
get_next_empty_tt_entry(tt_t *transition_table){
  tt_entry_t *entry_ptr = NULL;
  assert(transition_table);
  FSM_ITERATE_BEGIN(transition_table, entry_ptr){

  }FSM_ITERATE_END(transition_table, entry_ptr);
  if(is_tt_entry_empty(entry_ptr) == FSM_TRUE)
    return entry_ptr;
  return NULL;
}

tt_entry_t*
create_and_insert_new_tt_entry(tt_t *transition_table, char *transition_key, unsigned int sizeof_key, state_t *next_state){
  assert(sizeof_key < MAX_TRANSITION_KEY_SIZE);
  tt_entry_t *tt_entry_ptr = get_next_empty_tt_entry(transition_table);
  if(!tt_entry_ptr){
    printf("FATAL : Transition Table is Full\n");
    return;
  }
  set_transition_table_entry_key(tt_entry_ptr->transition_key, transition_key, sizeof_key);
  tt_entry_ptr->transition_key_size = sizeof_key;
  tt_entry_ptr->next_state = next_state;
}

fsm_error_t
execute_fsm(fsm_t *fsm, char * input_buffer, unsigned int size, fsm_bool_t *fsm_result){
  state_t *initial_state = fsm->initial_state;
  assert(initial_state);
  state_t *current_state = fsm->initial_state;
  state_t *next_state = NULL;
  fsm->input_buffer_curser = 0;
  unsigned int length_read = 0;
  unsigned int input_buffer_len = size;
  if(fsm_result){
    *fsm_result = FSM_FALSE;
  }

  while(fsm->input_buffer_curser < MAX_INPT_BUFFER_LEN){
    length_read = 0;
    next_state = fsm_appl_transition(fsm, current_state, input_buffer + fsm->input_buffer_curser, input_buffer_len - fsm->input_buffer_curser, &length_read);
    if(!next_state){
      return FSM_NO_TRANSITION;
    }
    if(length_read){
      fsm->input_buffer_curser += length_read;
      current_state = next_state;
      if(fsm->input_buffer_curser == input_buffer_len){
        break;
      }
      continue;
    }
    break;
  }
  if(fsm_result){
    *fsm_result = current_state->is_final;
  }
  return FSM_NO_ERROR;
}
