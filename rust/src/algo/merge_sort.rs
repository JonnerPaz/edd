use std::vec::Vec;
// Generic sorting for arrays
pub fn gen_sort<T: Ord>(arr: &mut [T]) {
    arr.sort_unstable();
}

pub fn merge<T: Ord + Clone>(left: &[T], right: &[T]) -> Vec<T> {
    let mut result = Vec::with_capacity(left.len() + right.len());
    let mut i = 0;
    let mut j = 0;

    while i < left.len() && j < right.len() {
        if left[i] <= right[j] {
            result.push(left[i].clone());
            i += 1;
        } else {
            result.push(right[j].clone());
            j += 1;
        }
    }

    // add the remaining left elements
    while i < left.len() {
        result.push(left[i].clone());
        i += 1;
    }

    // add the remaining right elements
    while j < right.len() {
        result.push(right[j].clone());
        j += 1;
    }

    result
}

pub fn merge_sort<T: Ord + Clone>(arr: &mut Vec<T>) -> Vec<T> {
    // base case: if the length is 0 or 1, it's already sorted
    if arr.len() <= 1 {
        return arr.to_vec();
    }

    let mid = arr.len() / 2;

    let (left, right) = arr.split_at_mut(mid);

    gen_sort(left);
    gen_sort(right);

    return merge(left, right);
}
