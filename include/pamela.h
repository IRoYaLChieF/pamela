#ifndef PAMELA_H_
#define PAMELA_H_

#define PAM_SM_AUTH
#define PAM_SM_SESSION
#define PAM_SM_ACCOUNT
#define PAM_SM_PASSWORD

#define BUFF_SIZE 1024

#include <security/pam_modules.h>

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int ac, const char **av);
PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int ac, const char **av);
PAM_EXTERN int pam_sm_chauthtok(pam_handle_t *pamh, int flags, int ac, const char **av);
PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int ac, const char **av);
PAM_EXTERN int pam_sm_open_session(pam_handle_t *pamh, int flags, int ac, const char **av);
PAM_EXTERN int pam_sm_close_session(pam_handle_t *pamh, int flags, int ac, const char **av);

#endif /* !PAMELA_H_ */