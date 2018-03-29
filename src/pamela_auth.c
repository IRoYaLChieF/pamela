#include <string.h>
#include "pamela.h"

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int ac, const char **av)
{
	int retval;
	const char *user;
	const char *pass;

	if ((retval = pam_get_user(pamh, &user, "Username: ")) != PAM_SUCCESS)
		return (retval);
	if ((retval = pam_get_item(pamh, PAM_AUTHTOK, (const void **)&pass)) != PAM_SUCCESS)
		return (retval);
	if ((retval = pam_set_data(pamh, "pamela_pass", strdup(pass), &clean_pam_data)) != PAM_SUCCESS)
		return (retval);
	return (PAM_SUCCESS);
}

PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int ac, const char **av)
{
	return (PAM_SUCCESS);
}

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int ac, const char **av)
{
	return (PAM_SUCCESS);
}