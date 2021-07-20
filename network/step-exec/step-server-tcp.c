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
#include <netinet/in.h>
#include <memory.h>

#include "common.h"

int
main()
{
 int server;
 struct sockaddr_in addr;
 int sd;

 /* listen用のソケットの作成 */
 prompt("socket");
 server = socket(AF_INET, SOCK_STREAM, 0);
 if (socket < 0)
   pexit("socket");

 /* 着信アドレス指定 */
 memset( &addr, 0, sizeof(addr) );
 addr.sin_family = AF_INET;
 addr.sin_addr.s_addr = htonl( INADDR_ANY );
 addr.sin_port = htons( PORT );
 prompt("bind");
 if (bind(server, (struct sockaddr *)&addr, sizeof(addr)) < 0)
   pexit("bind");

 /* クライアントからの接続要求を受けつけるよう指示する */
 prompt("listen");
 if (listen(server, 2) < 0)
   pexit("listen");

 next:
 int c = prompt("crash[Y/n]");
 switch (c) {
 case 'Y':
   exit (0);
 }

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

