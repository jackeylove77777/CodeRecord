package main
type ListNode struct {
	Val  int
	Next *ListNode
}
func middleNode(head *ListNode) *ListNode {
    if head==nil{
        return nil
    }
	slow, fast := head, head
	for fast != nil && fast.Next != nil{
		
		for i := 0; i < 2; i++ {
			if fast != nil {
				fast = fast.Next
			}
		}
		slow = slow.Next
	}
	return slow
}