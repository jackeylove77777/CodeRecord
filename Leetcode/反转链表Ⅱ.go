/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
var houji *ListNode
func reverseBetween(head *ListNode, left int, right int) *ListNode {
    if left==1{
        return reverseN(head,right)
    }
    head.Next=reverseBetween(head.Next,left-1,right-1)
    return head
}
func reverseN(head *ListNode,cnt int)*ListNode{
    if cnt==1{
        houji=head.Next
        return head
    }
    last:=reverseN(head.Next,cnt-1)
    head.Next.Next=head
    head.Next=houji
    return last
}