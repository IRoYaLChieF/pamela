#include <string.h>
#include <stdlib.h>
#include "pamela.h"

static void clean_pam_data(pam_handle_t *pamh, void *data, int error)
{
	if (data)
	{
		memset(data, 0, strlen(data));
		free(data);
	}
}

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int ac, const char **av)
{
	int retval;
	const char *pass;

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