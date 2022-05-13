/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     public int val;
 *     public ListNode next;
 *     public ListNode(int val=0, ListNode next=null) {
 *         this.val = val;
 *         this.next = next;
 *     }
 * }
 */
using System.Collections.Generic;
public class Solution {
    public ListNode MergeKLists(ListNode[] lists) {
        if(lists.Length<=0)return null;
        var pqueue = new PriorityQueue<ListNode, int>();
        var dummy = new ListNode(-1);
        var p = dummy;
        for(int i = 0; i < lists.Length; ++i)
        {
            if(lists[i]!=null)pqueue.Enqueue(lists[i], lists[i].val);
        }
        while(pqueue.TryDequeue(out var node,out var _))
        {
            p.next = node;
            p = p.next;
            if (node.next != null)
            {
                node = node.next;
                pqueue.Enqueue(node, node.val);
            }
        }
        return dummy.next;
    }
}