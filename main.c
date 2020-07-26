#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "fsm.h"

int
main(int argc, char **argv){
  fsm_t *fsm = create_new_fsm("Bit flopper");
  state_t *S_0 = create_new_state("S0", FSM_TRUE);
  set_fsm_initial_state(fsm, S_0);

  char bit = '0';
  create_and_insert_new_tt_entry(/* Invoke a function which returns the transition table of this state */, &bit, 1, bit_flipper_output_fn_gen, S_0);

  bit = '1';
  create_and_insert_new_tt_entry(/* Invoke a function which returns the transition table of this state */, &bit, 1, bit_flipper_output_fn_gen, S_0);

  char *str = "00000000\0";
  sm_bool_t fsm_result;
  fsm_error_t fsm_error = execute_fsm(fsm, str, strlen(str), 0, &fsm_result);

  if(fsm_error == FSM_NO_ERROR){
    printf("FSM result = %s\n", fsm_result == FSM_TRUE ? "FSM_TRUE":"FSM_FALSE");
    printf("FSM Output string : \n%s\n", fsm->fsm_output_buff.output_buffer);
  }

  /*
  TODO: make the application write the result into the output buffer of the FSM
  TODO: make the application to read the input file from input buffer of the FSM
  TODO: Email Validation
  TODO: binary to hex conversion
  */
  return 0;
}
