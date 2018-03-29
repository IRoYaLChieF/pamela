#include <stdlib.h>
#include <string.h>

#include "pamela.h"

void clean_pam_data(pam_handle_t *pamh, void *data, int error)
{
	if (data != NULL)
	{
		memset(data, 0, strlen(data));
		free(data);
	}
}

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int ac, const char **av)
{
	int			ret;
	const char	*pUsername;
	const char	*pPass;

	if ((ret = pam_get_user(pamh, &pUsername, "Username: ")) != PAM_SUCCESS)
		return (ret);
	else if ((ret = pam_get_item(pamh, PAM_AUTHTOK, (const void **)&pPass)) != PAM_SUCCESS)
		return (ret);
	else if ((ret = pam_set_data(pamh, "pam_user_pass", strdup(pPass), &clean_pam_data)) != PAM_SUCCESS)
		return (ret);
	return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_open_session(pam_handle_t *pamh, int flags, int ac, const char **av)
{
	int			ret;
	const char	*pUsername;
	const char	*pPass;

	if ((ret = pam_get_user(pamh, &pUsername, "Username: ")) != PAM_SUCCESS)
		return (ret);
	else if ((ret = pam_get_data(pamh, "pam_user_pass", (const void **)&pPass)) != PAM_SUCCESS)
		return (ret);
	return (PAM_SUCCESS);
}

PAM_EXTERN int pam_sm_close_session(pam_handle_t *pamh, int flags, int ac, const char **av)
{
	return (PAM_SUCCESS);
}