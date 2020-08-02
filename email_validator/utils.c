#include <memory.h>
#include <assert.h>
#include "utils.h"

fsm_bool_t
match_any_0_9_match_fn(char *data1, unsigned int size, char *data2, unsigned int user_data_len, unsigned int *length_read){
  if(user_data_len == 0){
    *length_read = 0;
    return FSM_FALSE;
  }
  if(*data2 >= 48 && *data2 <= 57){
    *length_read = 1;
    return FSM_TRUE;
  }
  return FSM_FALSE;
}

fsm_bool_t
match_any_a_z_match_fn(char *data1, unsigned int size, char *data2, unsigned int user_data_len, unsigned int *length_read){
  if(user_data_len == 0){
    *length_read = 0;
    return FSM_FALSE;
  }
  if(*data2 >= 97 && *data2 <= 122){
    *length_read = 1;
    return FSM_TRUE;
  }
  return FSM_FALSE;
}

fsm_bool_t
match_any_A_Z_match_fn(char *data1, unsigned int size, char *data2, unsigned int user_data_len, unsigned int *length_read){
  if(user_data_len == 0){
    *length_read = 0;
    return FSM_FALSE;
  }
  if(*data2 >= 65 && *data2 <= 90){
    *length_read = 1;
    return FSM_TRUE;
  }
  return FSM_FALSE;
}

fsm_bool_t
match_any_character_match_fn(char *data1, unsigned int size, char *data2, unsigned int user_data_len, unsigned int *length_read){
  if(user_data_len == 0){
    *length_read = 0;
    return FSM_FALSE;
  }
  *length_read = 1;
  return FSM_TRUE;
}

fsm_t*
email_validator_fsm(void){
  tt_entry_t *entry = NULL;

  fsm_t *fsm = create_new_fsm("Email validator");
  state_t *q0 = create_new_state("q0", FSM_FALSE);
  state_t *q1 = create_new_state("q1", FSM_FALSE);
  state_t *q2 = create_new_state("q2", FSM_FALSE);
  state_t *q3 = create_new_state("q3", FSM_FALSE);
  state_t *q4 = create_new_state("q4", FSM_TRUE);
  state_t *D  = create_new_state("D", FSM_FALSE);
  set_fsm_initial_state(fsm, q0);

  /* q0 */
  entry = create_and_insert_new_tt_entry(get_state_tt(q0), 0, 0, 0, q1);
  register_input_matching_tt_entry_cb(entry, match_any_0_9_match_fn);
  register_input_matching_tt_entry_cb(entry, match_any_a_z_match_fn);
  register_input_matching_tt_entry_cb(entry, match_any_A_Z_match_fn);
  create_and_insert_new_tt_entry_wild_card(q0, D, 0);

  /* q1 */
  entry = create_and_insert_new_tt_entry(get_state_tt(q1), 0, 0, 0, q2);
  register_input_matching_tt_entry_cb(entry, match_any_0_9_match_fn);
  register_input_matching_tt_entry_cb(entry, match_any_a_z_match_fn);
  register_input_matching_tt_entry_cb(entry, match_any_A_Z_match_fn);
  create_and_insert_new_tt_entry_wild_card(q1, D, 0);

  /* q2 */
  entry = create_and_insert_new_tt_entry(get_state_tt(q2), 0, 0, 0, q2);
  register_input_matching_tt_entry_cb(entry, match_any_0_9_match_fn);
  register_input_matching_tt_entry_cb(entry, match_any_a_z_match_fn);
  register_input_matching_tt_entry_cb(entry, match_any_A_Z_match_fn);
  entry = create_and_insert_new_tt_entry(get_state_tt(q2), "@", 1, 0, q3);
  create_and_insert_new_tt_entry_wild_card(q2, D, 0);

  /* q3 */
  entry = create_and_insert_new_tt_entry(get_state_tt(q3), "gmail.com", strlen("gmail.com"), 0, q4);
  entry = create_and_insert_new_tt_entry(get_state_tt(q3), "yahoo.com", strlen("yahoo.com"), 0, q4);
  entry = create_and_insert_new_tt_entry(get_state_tt(q3), "hotmail.com", strlen("hotmail.com"), 0, q4);
  entry = create_and_insert_new_tt_entry(get_state_tt(q3), "aol.com", strlen("aol.com"), 0, q4);
  entry = create_and_insert_new_tt_entry(get_state_tt(q3), "ut.ac.ir", strlen("ut.ac.ir"), 0, q4);
  entry = create_and_insert_new_tt_entry(get_state_tt(q3), "mcgill.ca", strlen("mcgill.ca"), 0, q4);
  create_and_insert_new_tt_entry_wild_card(q3, D, 0);

  /* q4 */
  create_and_insert_new_tt_entry_wild_card(q4, D, 0);

  /* D */
  create_and_insert_new_tt_entry_wild_card(D, D, 0);

  return fsm;
}
