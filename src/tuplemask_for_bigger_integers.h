#ifndef TUPLEMASK_FOR_BIGGER_INTEGERS_H
#define TUPLEMASK_FOR_BIGGER_INTEGERS_H

template <std::size_t num, typename Tuple>
constexpr auto tuplemask_for_bigger_integers(Tuple&& tuple) {
  BOOST_HANA_CONSTANT_CHECK(hana::length(tuple) == hana::size_c<32>);
  return hana::transform(
      to_tuple_partition_combinebytes<num>(std::forward<Tuple>(tuple)),
      hana::all);
}

#endif  // TUPLEMASK_FOR_BIGGER_INTEGERS_H
