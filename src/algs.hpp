#pragma once

#include <iostream>
// #include <assert.h>
#include <vector>
#include <utility>

using namespace std;

template <typename Tout, typename Tin>
std::vector<std::pair<Tout, Tout>> f(Tin low, Tin high, Tin k);

template <typename Tout=uint8_t, typename Tin>
vector<pair<Tout, Tout>> alg_A(Tin low, Tin high, Tin k) {
    vector<pair<Tout, Tout>> markers(high, {0, 0}); // Initialize with a suitable size and default values

    Tin marker = 1;
    for (Tout i = 0; marker < high; ++i) {
        markers[marker] = std::make_pair(1, i);
        for (Tout j = 2; j < 10 && marker*j < high; ++j) {
            if (j % 2 == 0) {
                // markers[marker*j] = std::make_pair(markers[marker].first - 1, markers[marker].second + 1);
                markers[marker*j].first = markers[marker].first - 1;
                markers[marker*j].second = markers[marker].second + 1;
            } else {
                // markers[marker*j] = std::make_pair(markers[marker].first, markers[marker].second);
                markers[marker*j].first = markers[marker].first;
                markers[marker*j].second = markers[marker].second;
            }
        }
        marker *= 10;
    }

    for (Tin num = 1; num < high; ++num) {
        if (markers[num].first > 0 || markers[num].second > 0) {
            marker = num;
        } else {
            markers[num].first = markers[marker].first + markers[num-marker].first;
            markers[num].second = markers[marker].second + markers[num-marker].second - markers[num-marker].first - markers[num-marker].second;
        }
        if (num>=low && markers[num].first == markers[num].second && num % k == 0) {
            cout << num << ": (" << (uint16_t)markers[num].first << " " << (uint16_t)markers[num].second << ")" << endl;
        }
    }

    return markers;
}
