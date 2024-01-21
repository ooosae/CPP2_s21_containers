//
// Created by Глеб Писарев on 30.10.2023.
//

#ifndef CPP2_S21_CONTAINERS_1_S21_MAP_H
#define CPP2_S21_CONTAINERS_1_S21_MAP_H

#include "BinaryTree.h"

namespace s21 {
template <class Key, class T, class Compare = std::less<Key>>
class map {
 private:
  class Comparator;

 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using tree_type = BinaryTree::BinaryTree<value_type, Comparator>;
  using iterator = typename tree_type::iterator;
  using const_iterator = typename tree_type::const_iterator;

  map() : tree_() {}
  explicit map(std::initializer_list<value_type> const &items) : tree_(items) {}
  map(const map &m) : tree_(m.tree_) {}
  map(map &&m) noexcept : tree_(std::move(m.tree_)) {}
  ~map() { clear(); }

  std::pair<iterator, bool> insert(const value_type &value) {
    return tree_.insert(value);
  }
  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    return tree_.insert(std::make_pair(key, obj));
  }
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    return tree_.insert_or_assign(std::make_pair(key, obj));
  }
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<iterator, bool>> results;
    (results.emplace_back(insert(std::forward<Args>(args))), ...);
    return results;
  }

  void swap(map &other) noexcept { std::swap(tree_, other.tree_); }

  void merge(map &other) { tree_.merge(other.tree_); }

  iterator begin() { return tree_.begin(); }
  const_iterator begin() const { return tree_.begin(); }
  iterator end() { return tree_.end(); }
  const_iterator end() const { return tree_.end(); }
  void erase(iterator pos) noexcept { tree_.erase(pos); }
  T &at(const Key &key) & {
    const mapped_type value{};
    return (tree_.at(std::make_pair(key, value))).second;
  }
  const T &at(const Key &key) const & {
    const mapped_type value{};
    return (tree_.at(std::make_pair(key, value))).second;
  }
  T &operator[](const Key &key) &noexcept {
    mapped_type value{};
    return (tree_[std::make_pair(key, value)]).second;
  }

  map &operator=(map &&m) &noexcept {
    if (this == &m) return *this;
    tree_ = std::move(m.tree_);
    return *this;
  }
  map &operator=(const map &m) & {
    if (this == &m) return *this;
    tree_ = m.tree_;
    return *this;
  }
  iterator find(const Key &key) noexcept {
    mapped_type value{};
    return tree_.find(std::make_pair(key, value));
  }
  const_iterator find(const Key &key) const noexcept {
    mapped_type value{};
    return tree_.find(std::make_pair(key, value));
  }
  void clear() noexcept { tree_.clear(); }

  [[nodiscard]] bool empty() const noexcept { return tree_.empty(); }
  [[nodiscard]] size_type size() const noexcept { return tree_.size(); }
  [[nodiscard]] size_type max_size() const noexcept { return tree_.max_size(); }

  bool contains(const Key &key) const noexcept {
    mapped_type value{};
    return tree_.contains(std::make_pair(key, value));
  }

 private:
  tree_type tree_;

  class Comparator {
   public:
    bool operator()(const value_type &left,
                    const value_type &right) const noexcept {
      return Compare{}(left.first, right.first);
    }
  };
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_S21_MAP_H
