#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "fsm.h"

int
main(int argc, char **argv){
  fsm_t *fsm = create_new_fsm("Bit flopper");
  state_t *s0 = create_new_state("S0", FSM_TRUE);
  set_fsm_initial_state(fsm, S0);
  char bit = '0';
  create_and_insert_new_tt_entry(&S0->state_transition_table, &bit, 1, bit_flipper_output_fn_gen, S0);
  bit = '1';
  create_and_insert_new_tt_entry(&S0->state_transition_table, &bit, 1, bit_flipper_output_fn_gen, S0);
  fsm_bool_t fsm_result;
  fsm_error_t fsm_error;

  char *str = "1010101010101";
  fsm_error = execute_fsm(fsm, str, strlen(str), 0, &fsm_result);

  if(fsm_error == FSM_NO_ERROR){
    printf("FSM result = %s\n", fsm_result == FSM_TRUE ? "FSM_TRUE":"FSM_FALSE");
    printf("FSM output string : %s\n", get_fsm_output_string(fsm));
  }
  return 0;
}
