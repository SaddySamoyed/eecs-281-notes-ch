#include <iostream>
using namespace std;
#include <vector>


int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // 选取最后一个元素作为基准
    int i = low - 1;       // i表示小于基准的区域的最后一个元素索引

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) { // 如果当前元素小于基准
            i++;
            std::swap(arr[i], arr[j]); // 交换小元素到前面
        }
    }
    std::swap(arr[i + 1], arr[high]); // 把基准放到正确的位置
    return i + 1; // 返回基准的索引
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // 获取分区点
        quickSort(arr, low, pi - 1);        // 排序左子数组
        quickSort(arr, pi + 1, high);       // 排序右子数组
    }
}

int main() {
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    int n = arr.size();

    std::cout << "排序前数组: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    quickSort(arr, 0, n - 1);

    std::cout << "排序后数组: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
