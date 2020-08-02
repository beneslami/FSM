#include <stdio.h>
#include <string.h>
#include "utils.h"

int main(int argc, char **argv){
  char *email = argv[1];
  fsm_bool_t fsm_result;
  fsm_t *email_fsm = email_validator_fsm();
  fsm_error_t fsm_error = execute_fsm(email_fsm, email, strlen(email), 0, &fsm_result);
  if(fsm_error == FSM_NO_ERROR){
      if(fsm_result == FSM_TRUE){
        printf("Valid Email\n");
      }
      else{
        printf("Invalid Email\n");
      }
  }
  else{
    printf("FSM failed\n");
  }
  return 0;
}
