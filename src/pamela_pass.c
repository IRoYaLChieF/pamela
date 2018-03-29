#include "pamela.h"

PAM_EXTERN int pam_sm_chauthtok(pam_handle_t *pamh, int flags, int ac, const char **av)
{
	return (PAM_SUCCESS);
}