#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>

#include <iomanip> 
#include <numeric>
#include <queue>
#include <tuple>

using namespace std;

// ����С��ƽ��ֵ��Ԫ�ػᱻ�������д���ƽ��ֵ��Ԫ�صĺ���
int partition(){
	std::vector<double> temperatures{ 65, 75, 56, 48, 31, 28, 32, 29, 40, 41, 44, 50 };
	std::copy(std::begin(temperatures), std::end(temperatures), //List the values
		std::ostream_iterator<double>{std::cout, " "});
	std::cout << std::endl;

	auto average = std::accumulate(std::begin(temperatures), std::end(temperatures), 0.0) / temperatures.size();
	std::cout << "Average temperature: " << average << std::endl;

	// ����ԭ�����˳��
	std::stable_partition(std::begin(temperatures), std::end(temperatures), [average](double t) { return t < average; });
	// ������ԭ�����˳��
	//std::partition(std::begin(temperatures), std::end(temperatures), [average](double t) { return t < average; });

	std::copy(std::begin(temperatures), std::end(temperatures), std::ostream_iterator<double>{std::cout, " "});
	std::cout << std::endl;

	using gender = char;
	using monicker = string;
	using type= string;
	using Name = std::tuple<monicker, type, gender>;
	std::vector<Name> names{ std::make_tuple("Dan", "old", 'm'),std::make_tuple("Ann", "old", 'f'),std::make_tuple("Ed", "old",'m'),std::make_tuple("Jan", "old", 'f'), std::make_tuple("Edna", "old", 'f') };
	std::partition(std::begin(names), std::end(names), [](const Name name) { return std::get<2>(name) == 'f'; });

	for (const auto& name : names)
		std::cout << std::get<0>(name) << " " << std::get<1>(name) << " " << std::get<2>(name) << std::endl;

	// ����true��false��Ԫ�طֱ�ŵ���ͬ�Ķ�����
	// ����һ
	std::vector<double> low_t;                       // Stores below average temperatures
	std::vector<double> high_t;                      // Stores average or above temperatures
	std::partition_copy(std::begin(temperatures), std::end(temperatures), std::back_inserter(low_t), 
		std::back_inserter(high_t), [average](double t) { return t < average; });

	// Output below average temperatures
	std::cout << "below average:";
	std::copy(std::begin(low_t), std::end(low_t), std::ostream_iterator<double>{std::cout, " "});
	std::cout << std::endl;
	// Output average or above temperatures
	std::cout << "above average:";
	std::copy(std::begin(high_t), std::end(high_t), std::ostream_iterator<double>{std::cout, " "});
	std::cout << std::endl;

	// ������
	if (std::is_partitioned(std::begin(temperatures), std::end(temperatures), [average](double t) { return t < average; })) // �����Ƿ��Ѿ�������
	{
		// partition_point ��ȡ��һ����������������
		auto iter = std::partition_point(std::begin(temperatures), std::end(temperatures), [average](double t) { return t < average; });
		std::cout << "Elements in the first partition: ";
		std::copy(std::begin(temperatures), iter, std::ostream_iterator<double>{std::cout, " " });
		std::cout << "\nElements in the second partition: ";
		std::copy(iter, std::end(temperatures), std::ostream_iterator<double>{std::cout, " "});
		std::cout << std::endl;
	}
	else
		std::cout << "Range is not partitioned." << std::endl;

	return 0;
}

/*
������������һ����װ��������������ģ�壬����һ�����������Ļ������ṩ��һЩ��ͬ�Ĺ��ܡ�
֮���Գ����������࣬����Ϊ������ͨ�������������еĽӿ����ṩ��ͬ�Ĺ��ܡ�
stack<T>����һ����װ�� deque<T> ��������������ģ�壬Ĭ��ʵ�ֵ���һ�������ȳ���Last-In-First-Out��LIFO����ѹ��ջ
queue<T>����һ����װ�� deque<T> ��������������ģ�壬Ĭ��ʵ�ֵ���һ�������ȳ���First-In-First-Out��LIFO���Ķ��С�
priority_queue<T>����һ����װ�� vector<T> ��������������ģ�壬Ĭ��ʵ�ֵ���һ�����Ԫ�����򣬴Ӷ���֤���Ԫ�����ڶ�����ǰ��Ķ��С�
*/
int Container_adapter() {
	std::vector<double> numbers{ 2.5, 10.0, 3.5, 6.5, 8.0, 12.0, 1.5, 6.0 };

	// partial_sort
	std::partial_sort(std::begin(numbers), std::begin(numbers) + 5, std::end(numbers));
	std::cout << "partial_sort:";
	std::copy(std::begin(numbers), std::is_sorted_until(std::begin(numbers), std::end(numbers)), std::ostream_iterator<double>{std::cout, " " }); // 1.5 2.5 3.5 6 6.5 12
	std::cout << std::endl;

	// heap ������
	std::make_heap(std::begin(numbers), std::end(numbers), std::greater<>());
	std::sort_heap(std::begin(numbers), std::end(numbers), std::greater<>());
	// Result: 12 10 8 6.5 6 3.5 2.5 1.5
	std::cout << "sort_heap:";
	for (auto vec : numbers) {
		std::cout << vec << " ";
	}
	std::cout << std::endl;

	// pop_heap() ��������һ��Ԫ���Ƶ���󣬲���֤ʣ�µ�Ԫ����Ȼ��һ���ѣ��Ժ�����numbers.pop_back()ɾ�����һ��Ԫ��
	std::pop_heap(std::begin(numbers), std::end(numbers), std::greater<>());
	// Result: 1.5 10 8 6.5 6 3.5 2.5 12
	std::cout << "pop_heap:";
	for (auto vec : numbers) {
		std::cout << vec << " ";
	}
	std::cout << std::endl;

	std::cout << "is_heap_until:";
	auto iter = std::is_heap_until(std::begin(numbers), std::end(numbers), std::greater<>());
	if (iter != std::end(numbers))
		std::cout << "numbers is a heap up to " << *iter << std::endl;


	// priority_queue�� ������һ��Ԫ���������еĶ��С�
	std::string wrds[]{ "one", "two", "three", "four" };
	std::priority_queue<std::string, std::vector<std::string>, std::greater<std::string>> words2{ std::begin(wrds) , std::end(wrds) }; //"four" "one" "three" "two"
	std::cout << "priority_queue:";
	while (!words2.empty()) {
		std::cout << words2.top() << " ";
		words2.pop();
	}
	return 0;
}



int main()
{
	//partition();

	std::deque<string> song{ "jingle", "bells","jingle", "all", "the", "way" };
	song.resize(song.size() + 4); // Add 2 elements
	std::copy_backward(std::begin(song), std::begin(song) + 6, std::end(song));
	std::copy(std::begin(song), std::end(song), std::ostream_iterator <string> {std::cout, " "});
	std::cout << std::endl;

	system("pause");
	return 0;
}