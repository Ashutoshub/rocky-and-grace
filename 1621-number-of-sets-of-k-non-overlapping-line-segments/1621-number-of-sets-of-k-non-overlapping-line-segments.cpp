class Solution {
public:
    int MOD = 1e9 + 7;
    long long power(long long base, long long exp){
        long long res = 1;
        base %= MOD;
        while(exp > 0){
            if(exp % 2 == 1) res = (res * base) % MOD;
            base = (base * base) % MOD;
            exp /= 2;
        }
        return res;
    }
    //fermats little theorem;
    long long modInverse(long long n){
        return power(n, MOD - 2);
    }
    long long nCr(int n, int r){
        if(n < r) return 0;
        if(r == 0) return 1;
        long long num = 1, den = 1;
        for(int i = 0; i < r; i++){
            num = (num * (n - i)) % MOD;
            den = (den * (i + 1)) % MOD; 
        }
        return (num * modInverse(den)) % MOD;
    }
    int numberOfSets(int n, int k) {
        return nCr(n + k - 1, 2 * k);
    }
};