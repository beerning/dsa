//
//  leetcode_00.h
//  algorithm
//
//  Created by berning on 2015/7/27.
//

#ifndef leetcode_00_h
#define leetcode_00_h

#include <vector>

//01
vector<int> _1_twoSum(vector<int>& nums, int target) {
    size_t len = nums.size();
    int sum = 0;
    vector<int> v;
    for (int i = 0; i < len - 1; i++){
        for (int j = i + 1; j < len; j++ ){
             sum = nums[i] + nums[j];
            if (target == sum){
                v.push_back(i);
                v.push_back(j);
            }
        }
    }
    return v;
}

//02
struct ListNode{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* _2_addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *list = new ListNode();
        ListNode *current = list;
        int sum = 0;
        bool sumOut = false;
        int v1(0), v2(0);

        while (l1 || l2){
            v1 = l1 ? l1->val : 0;
            v2 = l2 ? l2->val : 0;
            l1 = l1 ? l1->next : nullptr;
            l2 = l2 ? l2->next : nullptr;

            sum = sumOut ? v1 + v2 + 1 : v1 + v2;
            sumOut = sum >= 10 ? true : false;
            current->val = sum >= 10 ? sum - 10 : sum;

            if (l1 || l2 || (!l1  && !l2 && sumOut)){
                current->next = new ListNode();
                current = current->next;
                if (!l1  && !l2 && sumOut) current->val = 1;
            }
        }
        return list;
}

//03
int _3_lengthOfLongestSubstring(string s) {

    int table[128];
    memset(table, -1, sizeof(table));
    unsigned long length = s.length();

    int res = 0;
    int start = 0;
    int idx = 0;
    for (int i = 0; i < length; i++){
        idx = s[i];
        start = max(start, table[idx] + 1);
        res = max(res, i - start + 1);
        table[idx] = i;
    }
    return res;
}

//04
long bSearch(vector<int> v, int x){
    long low = 0;
    long high = long(v.size() - 1);
    long mid = 0;
    while (high >= low){
        mid = low + (high - low) / 2;
        if (x < v[mid]) high = mid - 1;
        else if(x > v[mid]) low = mid + 1;
        else return mid;
    }
    return low;
}

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    vector<int>::iterator it = nums2.begin();
    while (it != nums2.end()){
        long loc = bSearch(nums1, *it);
        
        cout << "loc = " << loc << endl;
        nums1.emplace(nums1.begin() + loc, *it);
        
        for (vector<int>::iterator its = nums1.begin(); its != nums1.end(); ++its)
            cout << *its << " ";
        cout << endl;

        ++it;
    }
    
    
    int remainder = nums1.size() % 2;
    size_t divider = nums1.size() / 2;
    return remainder == 0 ? (nums1[divider] + nums1[divider - 1]) * 0.5 : nums1[divider];
}

//09
bool _9_isPalindrome(int x) {
    if(x < 0)
        return false;
    int cur = 0;
    int num = x;
    while(num != 0) {
        cur = cur * 10 + num % 10;
        num /= 10;
    }
    return cur == x;
}

#pragma mark - test
void test00(){
    
    //9
    cout << _9_isPalindrome(12321) << endl;

}

void test04(){
    int v1[] = {1, 2, 3};
    int v2[] = {1, 2, 2};
    // 1 2 3
    vector<int> num1 (v1, v1 + sizeof(v1) / sizeof(int));
    vector<int> num2 (v2, v2 + sizeof(v2) / sizeof(int) );

    cout << "the midian is: " << endl;
    cout << findMedianSortedArrays(num1, num2) << endl;
}


#endif /* leetcode_00_h */
