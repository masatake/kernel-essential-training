/* Derived from https://github.com/michilu/algo-c/blob/master/tarai.c */

/* https://github.com/michilu/algo-c
   ============================================================
   『Ｃ言語による最新アルゴリズム事典』全ソースコード
   ------------------------------------------------------------
   ・『Ｃ言語による最新アルゴリズム事典』掲載の全ソースコード
   です。
   本に載せたものと違って，できるかぎりテスト用の main() を
   補ってあります。本に載っていないソースコードやテストデー
   タも若干ですが含まれています。
   ------------------------------------------------------------
   ご利用についての制限はありません。ただしバグによる損害の賠
   償などには応じかねますのでご了承ください。
   バグを発見されたらお知らせいただければ幸いです.
   ------------------------------------------------------------
   奥村 晴彦 Haruhiko Okumura <okumura@matsusaka-u.ac.jp>
   〒515 松阪市久保町1846 松阪大学
   Phone: (0598)29-1122(代)  Fax: (0598)29-1014
   ============================================================ */

/* gcc cpu-hogging.c
  strace -C -r -T -t ./a.out */

int tarai(int x, int y, int z)
{
  if (x <= y) return y;
  return tarai(tarai(x - 1, y, z),
	       tarai(y - 1, z, x),
	       tarai(z - 1, x, y));
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

int main()
{
  char buf[BUFSIZ];
  int x = 14 , y = 1, z = 0;
  int v;

  
  getpid();
  (void)tarai(x, y, z);
  // snprintf(buf, sizeof(buf), "%d\n", v);
  // write(1, buf, strlen(buf));
  getuid();
  getgid();  
    
  return EXIT_SUCCESS;
}
