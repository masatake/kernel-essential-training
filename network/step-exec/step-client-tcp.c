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

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>

#include "common.h"

int
main()
{
  int client;
  struct sockaddr_in addr;


 retry:
  /* ソケットの作成 */
  prompt("socket");
  client = socket(AF_INET, SOCK_STREAM, 0);
  if (client < 0)
    pexit("socket");

#if 0
  /* 送信元アドレス指定 */
  memset( &addr, 0, sizeof(addr) );
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl( INADDR_LOOPBACK );
  addr.sin_port = htons( PORT + 1 );
  prompt("bind");
  if (bind(client, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    pexit("bind");
#endif

  /* サーバへ接続するよう指示する */
  prompt("connect");
  memset( &addr, 0, sizeof(addr) );
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl( INADDR_LOOPBACK );
  addr.sin_port = htons( PORT );
  if (connect(client, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    pexit("connect");
  

 /* 接続を切断する。*/
 prompt("shutdown");
 if (shutdown(client, SHUT_RDWR) < 0)
   pexit("shutdown");

 /* ソケット記述子を破棄する。*/
 prompt("close");
 if (close(client) < 0)
   pexit("close");

  prompt("retry");
  goto retry;
  return 0;
}

