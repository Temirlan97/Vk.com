#include <stdio.h>
/*
By: Temirlan Ulugbek uulu
For Vk.com
*/
int bsearch(int * arr, int size, int x){
    if (size == 0 || arr[size-1] <= x){
	return -1;
    }
    int lower = 0, upper = size - 1;
    int mid = 0;
    while(lower <= upper){
	mid = (lower + upper)/2;
	if (arr[mid] == x){
	    break;
	} else if (arr[mid] < x){
	    lower = mid + 1;
	} else {
	    upper = mid - 1;
	}
    }
    while (mid < size - 1 && arr[mid] <= x)
    	mid++;
    return mid;
}

int main(){
    int arr[] = {1, 3, 4, 4, 4, 4, 10, 11};
    int x = 7;
    int idx1 = bsearch(arr, 8, x);
    if (idx1 == -1){
	printf("Can't find number bigger than %d\n", x);
    } else {
	printf("The first number bigger than %d is %d\n", x, arr[idx1]);
    }
    return 0;	
}
