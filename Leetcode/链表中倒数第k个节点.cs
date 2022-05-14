/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     public int val;
 *     public ListNode next;
 *     public ListNode(int x) { val = x; }
 * }
 */
public class Solution {
    public ListNode GetKthFromEnd(ListNode head, int k)
    {
        if (head is null || k <= 0) return null;
        (var p,var ans) = (head,head);
        for(int i = 0; i < k; ++i)
        {   
            if(p==null)return null;
            p = p.next;
        }
        while (p != null)
        {
            p = p.next;
            ans = ans.next;
        }
        return ans;
    }      
}