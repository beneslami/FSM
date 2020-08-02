#ifndef FSM_H
#define FSM_H

#include <assert.h>

#define MAX_FSM_OUTPUT_BUFFER 1024
#define MAX_FSM_NAME_SIZE 32
#define MAX_INPT_BUFFER_LEN 128
#define MAX_STATE_NAME_SIZE 32
#define MAX_TRANSITION_TABLE_SIZE 128
#define MAX_TRANSITION_KEY_SIZE 64
#define MAX_TT_ENTRY_CALLBACKS 32

#define FSM_ITERATE_BEGIN(transition_table, entry_ptr)      \
  do{                                                       \
      unsigned int index = 0;                               \
      for(; index < MAX_TRANSITION_TABLE_SIZE; index++){    \
        entry_ptr = &(transition_table->tt_entry_t[index]); \
        if(is_tt_entry_empty(entry_ptr) == FSM_TRUE)        \
        break;                                              \

#define FSM_ITERATE_END(transition_table, entry_ptr)        \
}}while(0);

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
typedef fsm_bool_t (*input_fn)(     /* Returns the size of input buffer read */
  char*,                            /* Input Buffer */
  unsigned int,                     /* Size of Input Buffer */
  unsigned int,                    /* Starting position to read the buffer */
  char*,
  unsigned int,
  unsigned int);
  
typedef void (*output_fn)(
  state_t*,
  state_t*,
  char*,                            /* Input buff */
  unsigned int,                    /* size of Input buffer */
  fsm_output_buff_t*
  );            /* Output buffer */

/* API declaration */
tt_t*
get_state_tt(state_t*);

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
execute_fsm(fsm_t*, char*, unsigned int, fsm_output_buff_t*, fsm_bool_t* /*result*/);

void
init_fsm_output_buffer(fsm_output_buff_t*);

fsm_output_buff_t*
get_fsm_output_buff_t(fsm_t*);

void
set_fsm_output_buffer_cursor(fsm_t*, state_t*, state_t*, char, char*);

state_t*
get_next_entry(tt_entry_t*);

fsm_output_buff_t*
get_fsm_output_buff_t(fsm_t*);

unsigned int
get_fsm_out_buff_curr_pos(fsm_output_buff_t*);

char*
get_fsm_out_buff_buffer(fsm_output_buff_t*);

void
set_fsm_out_buff_curr_pos(fsm_output_buff_t*, int);

char*
get_state_name(state_t*);

unsigned int
get_fsm_output_buff_size();

void
set_fsm_input_buffer_size(fsm_t*, unsigned int);

void
register_input_matching_tt_entry_cb(tt_entry_t*, input_fn);

void
fsm_register_input_matching_fn_cb(fsm_t*, input_fn);

void
create_and_insert_new_tt_entry_wild_card(state_t*, state_t*, output_fn);

static inline fsm_bool_t
is_tt_entry_empty(tt_entry_t *entry){
  if(!get_next_entry(entry)){
    return FSM_TRUE;
  }
  return FSM_FALSE;
}

#endif
