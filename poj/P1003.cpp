/*
 * Problem: Hangover
 * http://poj.org/problem?id=1003
 */

#include <cstdio>

int main() {
   while(true) {
       double length;
       scanf("%lf", &length);
       if (length == 0.0) break;
       int numCard = 1;
       double sum = 0.0;
       while(sum <= length) {
           ++numCard;
           sum += 1.0 / static_cast<double>(numCard);
       }
       printf("%d card(s)\n", numCard - 1);
   }
   return 0;
}
