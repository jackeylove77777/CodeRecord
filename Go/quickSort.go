package main

import "fmt"

func main() {
	nums := []int{5, 8, 6, 4, 7, 0, 10, -1, 66, 100, -5}
	quickSort(nums, 0, len(nums)-1)
	fmt.Println(nums)
}

func quickSort(arr []int, low int, high int) {
	if low < high {
		mid := adjustArr(arr, low, high)
		quickSort(arr, low, mid-1)
		quickSort(arr, mid+1, high)
	}
}
func adjustArr(arr []int, low int, high int) int {
	i, j := low, high
	x := arr[i]
	for {
		if i >= j {
			break
		}
		for {
			if i >= j || arr[j] < x {
				break
			}
			j--
		}
		if i < j {
			arr[i] = arr[j]
			i++
		}
		for {
			if i >= j || arr[i] >= x {
				break
			}
			i++
		}
		if i < j {
			arr[j] = arr[i]
			j--
		}
	}
	arr[i] = x
	return i
}
