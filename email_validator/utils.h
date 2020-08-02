#ifndef UTILS_H
#define UTILS_H

#include "../fsm.h"

fsm_t*
email_validator_fsm(void);

fsm_bool_t
match_any_0_9_match_fn(char*, unsigned int, char*, unsigned int, unsigned int*);

fsm_bool_t
match_any_a_z_match_fn(char*, unsigned int, char*, unsigned int, unsigned int*);

fsm_bool_t
match_any_A_Z_match_fn(char*, unsigned int, char*, unsigned int, unsigned int*);

fsm_bool_t
match_any_character_match_fn(char*, unsigned int, char*, unsigned int, unsigned int*);

#endif
