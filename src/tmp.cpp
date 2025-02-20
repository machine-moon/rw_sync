class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) {
            return n;
        }
        int prev = 1;
        int curr = 2;
        int next = curr + prev;

        for (int i = 3; i <= n; i++) {
            next = curr + prev;
            prev = curr;
            curr = next;
        }
        return curr;
    }
};
int main() {
    Solution s;
    int a{s.climbStairs(5)};
    return a;
}
