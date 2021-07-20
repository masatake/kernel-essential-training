/* Copyright 2018 Red Hat, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
 */

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "common.h"

int
main()
{
 int server;
 struct sockaddr_un addr;
 struct sockaddr_un peer; 
 int sd;

 /* listen用のソケットの作成 */
 prompt("socket");
 server = socket(AF_UNIX, SOCK_STREAM, 0);
 if (socket < 0)
   pexit("socket");

 /* 着信アドレス指定 */
 addr.sun_family = AF_UNIX;
 unlink(PATH);
 memcpy(addr.sun_path, PATH, strlen(PATH)+1);
 prompt("bind");
 if (bind(server, (struct sockaddr *)&addr, sizeof(addr)) < 0)
   pexit("bind");

 /* クライアントからの接続要求を受けつけるよう指示する */
 prompt("listen");
 if (listen(server, 2) < 0)
   pexit("listen");

 next:

 /* 確立した接続に対するソケット記述子を得る。*/
 prompt("accept");
 sd = accept(server, NULL, 0);
 if (sd < 0)
   pexit("accept");

 /* 接続を切断する。*/
 prompt("shutdown");
 if (shutdown(sd, SHUT_RDWR) < 0)
   pexit("shutdown");

 /* ソケット記述子を破棄する。*/
 prompt("close");
 if (close(sd) < 0)
   pexit("close");

 goto next;

 return 0;
}

