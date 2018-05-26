/*-
 * Copyright 2018 Nicola Tuveri
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

/*-
 * `ignore` is a dumb version of `tee`/`cat`:
 *     it copies from stdin to stdout, ignoring all CLI arguments.
 *
 * This can be useful to skip stages in a long CLI pipeline of commands,
 * or when it is impossible to use comments.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define BUF_SIZE 8192

int main(int argc, char *argv[])
{
	int ret = EXIT_SUCCESS;
	size_t n, wbytes, bytes_read;
	char *bp;
	char buffer[BUF_SIZE];

	while (1) {
		bytes_read = read(STDIN_FILENO, buffer, sizeof buffer);
		if (bytes_read < 0 && errno == EINTR)
			continue;
		if (bytes_read <= 0)
			break;

		n = bytes_read;
		bp = buffer;
		do {
			wbytes = write(STDOUT_FILENO, bp, n);
			if (wbytes == -1) {
				ret = EXIT_FAILURE;
				break;
			}
			bp += wbytes;
		} while ( n -= wbytes );
	}

	return ret;
}
