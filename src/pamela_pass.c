#include <stdio.h>
#include <stdlib.h>
#include "pamela.h"

static void change_container_pass(const char *user, const char *pass, const char *old_pass)
{
	char cmd[BUFF_SIZE];

	sprintf(cmd, "echo -n \"%s\n%s\n%s\n\" | sudo cryptsetup luksAddKey /home/%s/%sContainer",
		old_pass, pass, pass, user, user);
	system(cmd);
	sprintf(cmd, "echo -n \"%s\" | sudo cryptsetup luksRemoveKey /home/%s/%sContainer", old_pass, user, user);
	system(cmd);
}

PAM_EXTERN int pam_sm_chauthtok(pam_handle_t *pamh, int flags, int ac, const char **av)
{
	int retval;
	const char *user;
	const char *pass;
	const char *old_pass;

	if ((retval = pam_get_user(pamh, &user, "Username: ")) != PAM_SUCCESS)
		return (retval);
	if ((retval = pam_get_item(pamh, PAM_AUTHTOK, (const void **)&pass)) != PAM_SUCCESS)
		return (retval);
	if (pass) {
		if ((retval = pam_get_item(pamh, PAM_OLDAUTHTOK, (const void **)&old_pass)) != PAM_SUCCESS)
			return (retval);
		change_container_pass(user, pass, old_pass);
	}
	return (PAM_SUCCESS);
}