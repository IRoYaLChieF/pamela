#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "pamela.h"

static void create_container(const char *user, const char *pass)
{
	char cmd[BUFF_SIZE];

	sprintf(cmd, "dd if=/dev/urandom bs=1M count=100 of=/home/%s/%sContainer", user, user);
	system(cmd);
	sprintf(cmd, "sudo chown %s /home/%s/%sContainer", user, user, user);
	system(cmd);
	sprintf(cmd, "sudo chmod -R 700 /home/%s/%sContainer", user, user);
	system(cmd);
	sprintf(cmd, "echo -n \"%s\" | sudo cryptsetup luksFormat -c aes -h sha256 /home/%s/%sContainer", pass, user, user);
	system(cmd);
	sprintf(cmd, "echo -n \"%s\" | sudo cryptsetup luksOpen /home/%s/%sContainer %sContainer", pass, user, user, user);
	system(cmd);
	sprintf(cmd, "sudo chown %s /dev/mapper/%sContainer", user, user);
	system(cmd);
	sprintf(cmd, "sudo chmod -R 700 /dev/mapper/%sContainer", user);
	system(cmd);
	sprintf(cmd, "sudo mkfs.ext4 /dev/mapper/%sContainer", user);
	system(cmd);
	sprintf(cmd, "mkdir /home/%s/secure_data-rw", user);
	system(cmd);
	sprintf(cmd, "sudo mount /dev/mapper/%sContainer /home/%s/secure_data-rw", user, user);
	system(cmd);
	sprintf(cmd, "sudo chown -R %s /home/%s/secure_data-rw", user, user);
	system(cmd);
	sprintf(cmd, "sudo chmod -R 700 /home/%s/secure_data-rw", user);
	system(cmd);
}

static void open_container(const char *user, const char *pass)
{
	char cmd[BUFF_SIZE];


	sprintf(cmd, "echo -n \"%s\" | sudo cryptsetup luksOpen /home/%s/%sContainer %sContainer", pass, user, user, user);
	system(cmd);
	sprintf(cmd, "sudo chown %s /dev/mapper/%sContainer", user, user);
	system(cmd);
	sprintf(cmd, "sudo chmod -R 700 /dev/mapper/%sContainer", user);
	system(cmd);
	sprintf(cmd, "mkdir /home/%s/secure_data-rw", user);
	system(cmd);
	sprintf(cmd, "sudo mount /dev/mapper/%sContainer /home/%s/secure_data-rw", user, user);
	system(cmd);
	sprintf(cmd, "sudo chown -R %s /home/%s/secure_data-rw", user, user);
	system(cmd);
	sprintf(cmd, "sudo chmod -R 700 /home/%s/secure_data-rw", user);
	system(cmd);
}

static void close_container(const char *user)
{
	char cmd[BUFF_SIZE];

	sprintf(cmd, "sudo umount /home/%s/secure_data-rw", user);
	system(cmd);
	sprintf(cmd, "sudo cryptsetup luksClose %sContainer", user);
	system(cmd);
	sprintf(cmd, "rmdir /home/%s/secure_data-rw", user);
	system(cmd);
}

PAM_EXTERN int pam_sm_open_session(pam_handle_t *pamh, int flags, int ac, const char **av)
{
	int retval;
	const char *user;
	const char *pass;
	char path[BUFF_SIZE];
	struct stat buffer;
	
	if ((retval = pam_get_user(pamh, &user, "Username: ")) != PAM_SUCCESS)
		return (retval);
	if ((retval = pam_get_data(pamh, "pamela_pass", (const void **)&pass)) != PAM_SUCCESS)
		return (retval);
	sprintf(path, "/home/%s/%sContainer", user, user);
	if (stat(path, &buffer) == -1)
		create_container(user, pass);
	else
		open_container(user, pass);
	return (PAM_SUCCESS);
}

PAM_EXTERN int pam_sm_close_session(pam_handle_t *pamh, int flags, int ac, const char **av)
{
	int retval;
	const char *user;

	if ((retval = pam_get_user(pamh, (const char **)&user, "Username: ")) != PAM_SUCCESS)
		return (retval);
	close_container(user);
	return (PAM_SUCCESS);
}