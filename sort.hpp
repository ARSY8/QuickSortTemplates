#pragma once
#include <concepts>
#include <iterator>
#include <algorithm>

template <typename Iter, typename Compare>
concept SortableWithComparator =
    std::random_access_iterator<Iter> &&
    std::predicate<Compare, typename std::iterator_traits<Iter>::value_type,
                          typename std::iterator_traits<Iter>::value_type>;

template <class RandomAccessIterator, class Compare>
requires SortableWithComparator<RandomAccessIterator, Compare>
void quick_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {

	//проверка на итератор
	//проверка комп на круглые скобки

	if (first >= last || first + 1 == last)
		return;

	auto pivot = *(first + (last - first) / 2);

	RandomAccessIterator i = first;
	RandomAccessIterator j = last - 1;

	while (i < j) {
		while (comp(*i, pivot))
			++i;
		while (comp(pivot, *j))
			--j;
		

		if (i <= j) {
			std::iter_swap(i, j);
			++i;
			--j;
		}
	}

	if (first < j)
		quick_sort(first, j + 1, comp);

	if (i < last)
		quick_sort(i, last, comp);

}
