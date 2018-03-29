#ifndef PAMELA_H_
#define PAMELA_H_

#define PAM_SM_AUTH
#define PAM_SM_SESSION

#include <security/pam_modules.h>

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int ac, const char **av);
PAM_EXTERN int pam_sm_open_session(pam_handle_t *pamh, int flags, int ac, const char **av);
PAM_EXTERN int pam_sm_close_session(pam_handle_t *pamh, int flags, int ac, const char **av);

#endif /* !PAMELA_H_ */