#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "fsm.h"

int
main(int argc, char **argv){
  fsm_t *fsm = create_new_fsm("Bit flopper");
  state_t *s0 = create_new_state("S0", FSM_TRUE);
  set_fsm_initial_state(fsm, S0);
  
  return 0;
}
