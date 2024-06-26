#ifndef HASH_MAP
#define HASH_MAP
#include <iostream>
#include <string>
#include <vector>
#include <list>

template <typename T>
class HashMap
{
public:
	HashMap(double max_load = 0.75); // constructor
	~HashMap(); // destructor; deletes all of the items in the hashmap
	int size() const; // return the number of associations in the hashmap
	// The insert method associates one item (key) with another (value).
	// If no association currently exists with that key, this method inserts
	// a new association into the hashmap with that key/value pair. If there is
	// already an association with that key in the hashmap, then the item
	// associated with that key is replaced by the second parameter (value).
	// Thus, the hashmap must contain no duplicate keys.
	void insert(const std::string& key, const T& value);
	// Defines the bracket operator for HashMap, so you can use your map like this:
	// your_map["david"] = 2.99;
	// If the key does not exist in the hashmap, this will create a new entry in
	// the hashmap and map it to the default value of type T. Then it will return a
	// reference to the newly created value in the map.
	T& operator[](const std::string& key);
	// If no association exists with the given key, return nullptr; otherwise,
	// return a pointer to the value associated with that key. This pointer can be
	// used to examine that value within the map.
	const T* find(const std::string& key) const;
	// If no association exists with the given key, return nullptr; otherwise,
	// return a pointer to the value associated with that key. This pointer can be
	// used to examine that value or modify it directly within the map.
	T* find(const std::string& key) {
		const auto& hm = *this;
		return const_cast<T*>(hm.find(key));
	}
private:
	struct Pair {
		std::string key;
		T value;
	};
	void expandHashTable();
	std::vector<std::list<Pair>>pairMap;
	double loadCap;
	int numBuckets;
	double numValues;
};

template <typename T>
HashMap<T>::HashMap(double max_load)
	:loadCap(max_load), numBuckets(10), numValues(0)
{
	for (int i = 0; i < 10; i++) {
		pairMap.push_back(std::list<Pair>());
	}
}

template <typename T>
HashMap<T>::~HashMap() {}

template <typename T>
int HashMap<T>::size() const {
	return numValues;
}

template <typename T>
void HashMap<T>::insert(const std::string& key, const T& value) {
	if (find(key) == nullptr) {
		numValues++;
		if (numValues / numBuckets > loadCap) {
			expandHashTable();
		}
		size_t h = std::hash<std::string>()(key);
		int index = h % numBuckets;
		Pair newPair;
		newPair.key = key;
		newPair.value = value;
		pairMap[index].push_back(newPair);
	}
	else {
		T* ptr = find(key);
		*ptr = value;
	}
}

template <typename T>
void HashMap<T>::expandHashTable() {
	numBuckets *= 2;
	std::vector<std::list<Pair>>newPairMap(numBuckets);
	for (int i = 0; i < numBuckets / 2; i++) {
		typename std::list<Pair>::iterator it = pairMap[i].begin();
		while (it != pairMap[i].end()) {
			size_t h = std::hash<std::string>()((*it).key);
			int newIndex = h % numBuckets;
			Pair newPair;
			newPair.key = (*it).key;
			newPair.value = (*it).value;
			newPairMap[newIndex].push_back(newPair);
			it++;
		}
	}
	pairMap = newPairMap;
}

template <typename T>
T& HashMap<T>::operator[](const std::string& key) {
	if (find(key) == nullptr) {
		insert(key, T());
	}
	return *(find(key));
}

template <typename T>
const T* HashMap<T>::find(const std::string& key) const {
	size_t h = std::hash<std::string>()(key);
	int index = h % numBuckets;
	for (typename std::list<Pair>::const_iterator it = pairMap[index].begin(); it != pairMap[index].end(); it++) {
		if (it->key == key) {
			const T* val = &(it->value);
			return val;
		}
	}
	return nullptr;
}

#endif