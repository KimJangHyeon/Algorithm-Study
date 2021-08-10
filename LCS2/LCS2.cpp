/* LCS2 */
#include <iostream>
#include <algorithm>
using namespace std;


int lcs[1001][1001] = {0,};
string s1, s2;
int i,j;
string result = "";

int main() {

   cin >> s1 >> s2;

   for(i = 1; i <= s1.size(); i++){
      for(j = 1; j <= s2.size(); j++){
         if(s1[i-1] == s2[j-1]){
            lcs[i][j] = lcs[i-1][j-1] + 1;
         }
         else{
            lcs[i][j] = max(lcs[i-1][j],lcs[i][j-1]);
         }
      }
   }     
   cout << lcs[i-1][j-1] << endl;

   i = s1.size();
   j = s2.size();
   while(lcs[i][j] != 0){
      if(s1[i-1] == s2[j-1]){
         result = result + s1[i-1];
         i -= 1;
         j -= 1;
      }
      else{
         if(lcs[i-1][j] >= lcs[i][j-1]){
            i -= 1;
         }
         else{
            j -= 1;
         }
      }
   }

   reverse(result.begin(), result.end());

   cout << result << endl;

}
