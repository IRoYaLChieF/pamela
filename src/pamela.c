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
	int value;
	const char *password;

	if ((value = pam_get_item(pamh, PAM_AUTHTOK, (const void **)password)) != PAM_SUCCESS)
		return (value);
	if ((value = pam_set_data(pamh, "pamela_password", (const void **)strdup(password), clean_pam_data)) != PAM_SUCCESS)
		return (value);
	return (PAM_SUCCESS);
}

PAM_EXTERN int pam_sm_open_session(pam_handle_t *pamh, int flags, int ac, const char **av)
{
	int value;
	const char *password;

	if ((value = pam_get_data(pamh, "pamela_password", (const void **)password)) != PAM_SUCCESS)
		return (value);
	printf("Password: %s\n", password);
	return (PAM_SUCCESS);
}

PAM_EXTERN int pam_sm_close_session(pam_handle_t *pamh, int flags, int ac, const char **av)
{
	return (PAM_SUCCESS);
}