package main

/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func hasCycle(head *ListNode) bool {
    if head==nil{
        return false
    }
    slow,fast:=head,head
    for fast!=nil{
        for i:=0;i<2;i++{
            fast=fast.Next
            if fast==nil{
                return false
            }
        }
        slow=slow.Next
        if slow==fast{
            return true
        }
    }
    return false
}