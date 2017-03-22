/*
 * BSD 2-clause "Simplified" License
 *
 * Copyright (c) 2016-2017, Lans Zhang <jia.zhang@windriver.com>, Wind River Systems, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Author:
 * 	Lans Zhang <jia.zhang@windriver.com>
 */

#ifndef __INTERNAL_H__
#define __INTERNAL_H__

#include <cryptfs_tpm2.h>

struct session_complex {
	TPMI_SH_AUTH_SESSION session_handle;

	TPMS_AUTH_COMMAND sessionData;
	TPMS_AUTH_COMMAND *sessionDataArray[1];
	TSS2_SYS_CMD_AUTHS sessionsData;

	TPMS_AUTH_RESPONSE sessionDataOut;
	TPMS_AUTH_RESPONSE *sessionDataOutArray[1];
	TSS2_SYS_RSP_AUTHS sessionsDataOut;
};

extern TSS2_SYS_CONTEXT *cryptfs_tpm2_sys_context;

int
util_digest_size(TPMI_ALG_HASH hash_alg, UINT16 *alg_size);

void
password_session_create(struct session_complex *s, char *auth_password,
			unsigned int auth_password_size);

int
policy_session_create(struct session_complex *s, TPM_SE type,
                      TPMI_ALG_HASH hash_alg);

void
policy_session_destroy(struct session_complex *s);

void
policy_auth_set(TPMS_AUTH_COMMAND *session, TPMI_SH_AUTH_SESSION handle,
		char *auth_password, unsigned int auth_password_size);

int
pcr_policy_extend(TPMI_DH_OBJECT session_handle, TPML_PCR_SELECTION *pcrs,
		  TPMI_ALG_HASH policy_digest_alg);

int
password_policy_extend(TPMI_DH_OBJECT session_handle);

int
capability_read_public(TPMI_DH_OBJECT handle, TPM2B_PUBLIC *public_out);

int
sha1_digest(BYTE *data, UINT16 data_len, BYTE *hash);

int
hash_digest(TPMI_ALG_HASH hash_alg, BYTE *data, UINT16 data_len, BYTE *hash);

const char *
get_primary_key_secret(char *out, unsigned int *out_size);

const char *
get_passphrase_secret(char *out, unsigned int *out_size);

#endif	/* __INTERNAL_H__ */
