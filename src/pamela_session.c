#include "pamela.h"

PAM_EXTERN int pam_sm_open_session(pam_handle_t *pamh, int flags, int ac, const char **av)
{
	int retval;
	const char *user;
	const char *pass;
	
	if ((retval = pam_get_user(pamh, &user, "Username: ")) != PAM_SUCCESS)
		return (retval);
	if ((retval = pam_get_data(pamh, "pamela_pass", (const void **)&pass)) != PAM_SUCCESS)
		return (retval);
	return (PAM_SUCCESS);
}

PAM_EXTERN int pam_sm_close_session(pam_handle_t *pamh, int flags, int ac, const char **av)
{
	return (PAM_SUCCESS);
}