#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "fsm.h"

void
bit_flipper_output_fn_gen(fsm_t *fsm, state_t *from, state_t *to, char *input, unsigned int input_size){
  char out;
  out = (*input == '1') ? '0' : '1';
  fsm_output_buff_t *fsm_output_buff = get_fsm_output_buff_t(fsm);
  int temp = get_fsm_out_buff_curr_pos(fsm_output_buff);
  temp += snprintf(get_fsm_out_buff_buffer(fsm_output_buff) + get_fsm_out_buff_curr_pos(fsm_output_buff), (MAX_FSM_OUTPUT_BUFFER - get_fsm_out_buff_curr_pos(fsm_output_buff) - 1), "%s-->%c|%c-->%s\n", get_state_name(from), *input, out, get_state_name(to));
  set_fsm_out_buff_curr_pos(fsm_output_buff, temp);
  printf("%s\n", get_fsm_out_buff_buffer(fsm_output_buff));
}

int
main(int argc, char **argv){
  fsm_t *fsm = create_new_fsm("Bit flopper");
  state_t *S_0 = create_new_state("S0", FSM_TRUE);
  fsm_output_buff_t *fsm_output_buff = calloc(1, get_fsm_output_buff_size());
  set_fsm_initial_state(fsm, S_0);
  init_fsm_output_buffer(fsm_output_buff);

  char bit = '0';
  create_and_insert_new_tt_entry(get_state_tt(S_0), &bit, strlen(&bit), bit_flipper_output_fn_gen, S_0);
  bit = '1';
  create_and_insert_new_tt_entry(get_state_tt(S_0), &bit, strlen(&bit), bit_flipper_output_fn_gen, S_0);

  char *str = "10101010101\0";
  fsm_bool_t fsm_result;
  fsm_error_t fsm_error = execute_fsm(fsm, str, strlen(str), fsm_output_buff, &fsm_result);

  if(fsm_error == FSM_NO_ERROR){
    printf("FSM result = %s\n", fsm_result == FSM_TRUE ? "FSM_TRUE":"FSM_FALSE");
  }
  printf("%s\n", get_fsm_out_buff_buffer(fsm_output_buff));
  /*
  TODO: make the application write the result into the output buffer of the FSM ->done
  TODO: make the application to read the input file from input buffer of the FSM ->done
  TODO: Email Validation
  TODO: binary to hex conversion
  */
  free(fsm_output_buff);
  return 0;
}
