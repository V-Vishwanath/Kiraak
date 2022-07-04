
#ifndef KIRAAK_UTILS_H
#define KIRAAK_UTILS_H

template <typename ...Func>
struct VariantVisit: Func... {
    using Func::operator()...;
};

template<typename...Func> VariantVisit(Func...) -> VariantVisit<Func...>;

#endif //KIRAAK_UTILS_H
