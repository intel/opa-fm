/* BEGIN_ICS_COPYRIGHT5 ****************************************

Copyright (c) 2015-2020, Intel Corporation

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of Intel Corporation nor the names of its contributors
      may be used to endorse or promote products derived from this software
      without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 * ** END_ICS_COPYRIGHT5   ****************************************/

#include "fm_digest.h"

#include <assert.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "ib_types.h"

fm_digest_t * fm_digest_start(void)
{
	fm_digest_t * ctx = EVP_MD_CTX_create();
	if (!ctx) return NULL;
	if (!EVP_DigestInit_ex(ctx, EVP_sha256(), NULL)) {
		EVP_MD_CTX_destroy(ctx);
		return NULL;
	}
	return ctx;
}

int fm_digest_update(fm_digest_t *ctx, const void *data, size_t len)
{
	return EVP_DigestUpdate(ctx, data, len);
}

int fm_digest_finish(fm_digest_t *ctx, uint8_t *digest)
{
	unsigned int len;
	if (EVP_DigestFinal_ex(ctx, digest, &len) != 1)
		return 0;
	EVP_MD_CTX_destroy(ctx);
	return 1;

}

int fm_digest_len(fm_digest_t *ctx)
{
	return EVP_MD_CTX_size(ctx);
}

