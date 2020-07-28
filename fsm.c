#include "fsm.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

struct fsm_output_buff_{
  char output_buffer[MAX_FSM_OUTPUT_BUFFER];
  unsigned int curr_pos;
};

struct fsm_{
  state_t *initial_state;  /* initial state of FSM to start with */
  char fsm_name[MAX_FSM_NAME_SIZE];  /* Name of FSM */
  char input_buffer[MAX_INPT_BUFFER_LEN]; /* Application provided input data to parse by FSM */
  unsigned int input_buffer_size; /* Length of above data */
  fsm_output_buff_t *fsm_output_buff;
};

struct state_ {
  char state_name[MAX_STATE_NAME_SIZE]; /* Name of the state. must be unique within FSM */
  tt_t *state_transition_table; /* Transition table of the state */
  fsm_bool_t is_final;  /* boolean if the state is final or not */
};

struct transition_table_entry_ {
  char transition_key[MAX_TRANSITION_KEY_SIZE];
  unsigned int transition_key_size;
  output_fn outp_fn;
  state_t *next_state;
};

struct transition_table_{
  tt_entry_t tt_entry_t[MAX_TRANSITION_TABLE_SIZE];
};

tt_t*
get_state_tt(state_t* state){
  return state->state_transition_table;
}

fsm_t*
create_new_fsm(const char *fsm_name){
  fsm_t *fsm = calloc(1, sizeof(fsm_t));
  strcpy(fsm->fsm_name, fsm_name);
  fsm->input_buffer_size = 0;
  fsm->fsm_output_buff = calloc(1, sizeof(fsm_output_buff_t));
  return fsm;
}

state_t*
create_new_state(char *state_name, fsm_bool_t is_final){
  assert(state_name);
  state_t *state = calloc(1, sizeof(state_t));
  strcpy(state->state_name, state_name);
  state->is_final = is_final;
  state->state_transition_table = calloc(1, sizeof(tt_t));
  return state;
}

void
set_fsm_initial_state(fsm_t *fsm, state_t *state){
  assert(fsm);
  assert(state);
  fsm->initial_state = state;
}

static tt_entry_t*
get_next_empty_tt_entry(tt_t *transition_table){
  //assert(transition_table);
  tt_entry_t *entry_ptr = NULL;
  FSM_ITERATE_BEGIN(transition_table, entry_ptr){
  }FSM_ITERATE_END(transition_table, entry_ptr);
  if(is_tt_entry_empty(entry_ptr) == FSM_TRUE)
    return entry_ptr;
  return NULL;
}

tt_entry_t*
create_and_insert_new_tt_entry(tt_t *transition_table, char *transition_key, unsigned int sizeof_key, output_fn outp_fn, state_t *next_state){
  tt_entry_t *entry = get_next_empty_tt_entry(transition_table);
  if(!entry){
    printf("FATAL: Transition Table is FULL\n");
    return NULL;
  }
  memcpy(entry->transition_key, transition_key, sizeof_key);
  entry->transition_key[sizeof_key] = '\0';
  entry->transition_key_size = sizeof_key;
  entry->outp_fn = outp_fn;
  entry->next_state = next_state;
  return entry;
}


static state_t*
fsm_apply_transition(fsm_t *fsm, state_t *state, char *input_buffer, unsigned int size, unsigned int *length_read, fsm_output_buff_t *output_buffer){
  tt_entry_t *entry = NULL;
  state_t *next_state = NULL;
  assert(size);
  FSM_ITERATE_BEGIN(state->state_transition_table, entry){
    if(entry->transition_key_size <= size){
      next_state = entry->next_state;
      if(entry->outp_fn){
        entry->outp_fn(fsm, state, next_state, input_buffer, entry->transition_key_size);
      }
      return next_state;
    }
  }FSM_ITERATE_END(state->state_transition_table, entry);
  return NULL;
}

fsm_error_t
execute_fsm(fsm_t *fsm, char *input_buffer, unsigned int size, fsm_output_buff_t *output_buffer, fsm_bool_t *fsm_result){
  state_t *initial_state = fsm->initial_state;
  assert(initial_state);
  state_t *current_state = initial_state;
  state_t *next_state = NULL;
  *fsm_result = FSM_FALSE;
  char *buffer_to_parse;
  unsigned int input_buffer_len = 0, cursor = 0, length_read = 0;

  if(input_buffer && size){
    buffer_to_parse = input_buffer;
    input_buffer_len = size;
  }
  else{
    buffer_to_parse = fsm->input_buffer;
    input_buffer_len = fsm->input_buffer_size;
  }
  if(!output_buffer){
    output_buffer = fsm->fsm_output_buff;
  }
  else{
    init_fsm_output_buffer(output_buffer);
  }
  while(cursor < MAX_INPT_BUFFER_LEN){
    next_state = fsm_apply_transition(fsm, current_state, buffer_to_parse + cursor, input_buffer_len - cursor, &length_read, output_buffer);
    if(!next_state){
      return FSM_NO_TRANSITION;
    }
    if(length_read){
      cursor += length_read;
      current_state = next_state;
      if(cursor == input_buffer_len)
        break;
      continue;
    }
    break;
  }
  if(fsm_result){
    *fsm_result = current_state->is_final;
  }
  return FSM_NO_ERROR;
}

void
init_fsm_output_buffer(fsm_output_buff_t *out){
  memset(out->output_buffer, 0, MAX_FSM_OUTPUT_BUFFER);
  out->curr_pos = 0;
}

fsm_output_buff_t*
get_fsm_output_buff_t(fsm_t *fsm){
  return fsm->fsm_output_buff;
}

void
set_fsm_output_buffer_cursor(fsm_t *fsm, state_t *from, state_t *to, char out, char *input_buff){

}

unsigned int
get_fsm_out_buff_curr_pos(fsm_output_buff_t *fsm_output_buff){
  return fsm_output_buff->curr_pos;
}

char*
get_fsm_out_buff_buffer(fsm_output_buff_t *fsm_output_buff){
  return fsm_output_buff->output_buffer;
}

void
set_fsm_out_buff_curr_pos(fsm_output_buff_t *fsm_output_buff, int temp){
  fsm_output_buff->curr_pos = temp;
}

state_t*
get_next_entry(tt_entry_t *entry){
  return entry->next_state;
}

char*
get_state_name(state_t *state){
  return state->state_name;
}
