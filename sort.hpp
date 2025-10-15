#pragma once
#include <algorithm>
#include <type_traits>
#include <iterator>


template <class RandomAccessIterator, class Compare>
void quick_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {

	//проверка на итератор
	//проверка комп на круглые скобки

	using category = typename std::iterator_traits<RandomAccessIterator>::iterator_category;
	static_assert(std::is_base_of<std::random_access_iterator_tag, category>::value,
		"нужен RandomAccessIterator");

	using value_type = typename std::iterator_traits<RandomAccessIterator>::value_type;
	static_assert(
		std::is_invocable_r<bool, Compare, value_type, value_type>::value,
		"компоратор должен вызываться comp(a, b) и возвращать тип bool");

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