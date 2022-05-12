package leetcode

type ListNode struct {
    Val int
    Next *ListNode
}

//力扣合并两个有序链表
func mergeTwoLists(list1 *ListNode, list2 *ListNode) *ListNode {
    dummy := &ListNode{Val: -1,Next: nil}
	p,p1,p2 :=dummy,list1,list2
	for{
		if p1==nil{
			p.Next=p2
			break
		}else if p2==nil{
			p.Next=p1
			break
		}

		if(p1.Val>p2.Val){
			p.Next=p2
			p2=p2.Next
		}else{
			p.Next=p1
			p1=p1.Next
		}
		p=p.Next
	}

	return dummy.Next
}